/**
 * HyperBus Leader Controller
 *
 * Copyright (C) 2020 Matt Thompson <mthompson@hexwave.com>
 *
 */

module hyperbus
#(
    parameter TARGET = "ALTERA",
    parameter WIDTH = 8,
    parameter TACC_COUNT = 5,
    parameter RESET_COUNT = 2,
    parameter ADDR_LENGTH = 32
)
(
    // Memory clock
    input                       clk,
    // 90 degree phase shifted clock
    input                       clk90,
    input                       rst,

    input   [ADDR_LENGTH-1:0]   adr_i,
    input   [(WIDTH<<1)-1:0]    dat_i,
    input   [((WIDTH<<1)/8):0]  mask_i,
    output  [(WIDTH<<1)-1:0]    dat_o,

    // Ready to accept a new input word on dat_i
    output                      ready,

    // Output word is valid on dat_o
    output reg                  valid,

    // Read from HyperRAM register space
    input                       reg_space_i,

    // Write request. Hold high until transaction complete.
    input                       wrq,

    // Read request. Hold high until transaction complete.
    input                       rrq,

    // Hyperbus Interface
    output                      hbus_clk,
    output                      hbus_rstn,
    output                      hbus_csn,
    inout   [WIDTH-1:0]         hbus_dq,
    inout                       hbus_rwds
);

localparam COUNTER_WIDTH = $clog2(TACC_COUNT*2);

localparam NSTATES =        6;

localparam STATE_IDLE =     6'b000001;
localparam STATE_RESET =    6'b000010;
localparam STATE_COMMAND =  6'b000100;
localparam STATE_LATENCY =  6'b001000;
localparam STATE_READ =     6'b010000;
localparam STATE_WRITE =    6'b100000;

reg [NSTATES-1:0] state;

assign ready = (state == STATE_WRITE) ? 1'b1 : 1'b0;

// Double width input, output, and rwds signals
// at half the DDR clock rate.
wire [(WIDTH<<1)-1:0]   dataw;
wire [(WIDTH<<1)-1:0]   datar;
wire [1:0]              rwdsr;

wire [((WIDTH<<1)/8):0] rwdsw;
//reg [1:0]               rwdsw;

reg [(WIDTH<<1)-1:0]    read_reg;

assign dat_o = read_reg;

// Bidirectional DDR output enable
reg data_oe;
reg rwds_oe;

reg clk_oe;
reg clk_oe90;

/**
 * Bidirectional DDR IO.
 * Provides 2*WIDTH signal on each rising edge of the clock
 */

// Output data is clocked from the 200MHz clock
// Input data is clocked using the 200MHz clock, and valid on RWDS strobes
ioddr
#(
    .TARGET(TARGET),
    .WIDTH(WIDTH)
) ddr_data (
    .inclk(clk),
    .outclk(clk),
    .dat_i(dataw),
    .dat_o(datar),
    .dq(hbus_dq),
    .oe(data_oe)
);

ioddr
#(
    .TARGET(TARGET),
    .WIDTH(1)
) ddr_rwds (
    .inclk(clk),
    .outclk(clk),
    .dat_i(rwdsw),
    .dat_o(rwdsr),
    .dq(hbus_rwds),
    .oe(rwds_oe)
);

assign hbus_rstn = (state == STATE_RESET) ? 1'b0 : 1'b1;
assign hbus_csn = (
    (state == STATE_IDLE) || (state == STATE_RESET) || (state == {NSTATES{1'b0}})) ? 1'b1 : 1'b0;

// Clock gate
assign hbus_clk = clk_oe90 ? clk90 : 1'b0;

// Command/Address register
reg [47:0] ca;

reg timeout_error;

// Clock counter
reg [COUNTER_WIDTH-1:0] count;

assign dataw = (state == STATE_WRITE) ? dat_i : ca[47:32];
assign rwdsw = (state == STATE_WRITE) ? mask_i : 0;


// Cross clocks. This prevents the 90 degree clock from rising early for a half cycle.
// The first rising edge of clk90 is half way through the high period of the input clock,
// after the output data has been driven on DQ.
always @(posedge clk90 or posedge rst) begin
    if(rst) begin
        clk_oe90 <= 1'b0;
    end else begin
        clk_oe90 <= clk_oe;
    end
end

/** Read strobe logic */
always @(posedge clk) begin
    valid <= 1'b0;

    if((state == STATE_READ) && rrq) begin
        // The RWDS DDR output will contain the
        // bit pattern 2'b01 on valid read strobes.
        // The RAM chip may hold RWDS low, and we will
        // ignore the DQ signals until the next strobe

        if(rwdsr == 2'b10) begin
            valid <= 1'b1;
            read_reg <= datar;
        end
    end else begin
        valid <= 1'b0;
    end
end

always @(posedge clk or posedge rst) begin
    if(rst) begin
        clk_oe <= 1'b0;
        rwds_oe <= 1'b0;
        data_oe <= 1'b0;
        state <= STATE_RESET;
        count <= RESET_COUNT;
    end else begin
        case(state)
            STATE_RESET: begin
                count <= count - 1;
                clk_oe <= 1'b0;
                rwds_oe <= 1'b0;
                data_oe <= 1'b0;
                if(count == {COUNTER_WIDTH{1'b0}}) begin
                    count <= 0;
                    state <= STATE_IDLE;
                end
            end
            STATE_IDLE: begin
                rwds_oe <= 1'b0;
                data_oe <= 1'b0;

                if(count != {COUNTER_WIDTH{1'b0}}) begin
                    count <= count - 1;
                end

                if((count == {COUNTER_WIDTH{1'b0}}) && (rrq | wrq)) begin

                    // Load the command/address register

                    // R/W# = 1 for read, 0 for write
                    ca[47] <= rrq ? 1'b1 : 1'b0;

                    // Address Space = 0 for memory, 1 for registers
                    ca[46] <= reg_space_i;

                    // Burst Type = 0: wrapped, 1: linear
                    ca[45] <= 1'b1;

                    ca[44:16] <= adr_i[ADDR_LENGTH-1:3];
                    ca[15:3] <= 13'd0;
                    ca[2:0] <= adr_i[2:0];

                    // 3 cycles to write 48 bits
                    count <= 4'd3;

                    // Transition to command state
                    state <= STATE_COMMAND;

                end else begin
                    clk_oe <= 1'b0;

                    state <= STATE_IDLE;
                end
            end
            STATE_COMMAND: begin
                clk_oe <= 1'b1;
                data_oe <= 1'b1;

                if(count == 4'd0) begin
                    if(rrq) begin
                        // When reading, using a short latency and time reads from the RWDS strobe
                        count <= TACC_COUNT - 1;
                        data_oe <= 1'b0;
                        rwds_oe <= 1'b0;
                    end else if(wrq) begin

                        //count <= (rwdsr == 2'b11) ? (TACC_COUNT<<1) - 1 : (TACC_COUNT-1);

                        if(rwdsr == 2'b11) begin
                            $display("2x latency");
                            count <= (TACC_COUNT<<1) - 1;
                        end else begin
                            $display("1x latency");
                            count <= TACC_COUNT - 1;
                        end


                        // The master must drive RWDS to a valid LOW
                        // before the end of the initial latency to
                        // provide a data mask preamble period to the slave
                        rwds_oe <= 1'b1;
                        data_oe <= 1'b1;
                    end

                    state <= STATE_LATENCY;
                end else begin
                    // Shift CA register
                    ca <= ca << 16;

                    // Decrement the counter
                    count <= count - 1;
                end

            end

            STATE_LATENCY: begin
                rwds_oe <= 1'b0;
                data_oe <= 1'b0;
                count <= count - 1;

                if(count == {COUNTER_WIDTH{1'b0}}) begin
                    if(wrq) begin
                        //rwds_oe <= 1'b1;
                        //data_oe <= 1'b1;
                        state <= STATE_WRITE;
                    end else if(rrq) begin
                        state <= STATE_READ;
                    end else begin
                        state <= STATE_IDLE;
                    end
                end
            end

            STATE_READ: begin
                data_oe <= 1'b0;
                rwds_oe <= 1'b0;

                if(!rrq) begin
                    count <= 4'd1;
                    state <= STATE_IDLE;
                end
            end

            STATE_WRITE: begin
                data_oe <= 1'b1;
                rwds_oe <= 1'b1;

                if(!wrq) begin
                    data_oe <= 1'b0;
                    rwds_oe <= 1'b0;
                    count <= 4'd1;
                    state <= STATE_IDLE;
                end
            end

            default: begin
                count <= RESET_COUNT;
                state <= STATE_RESET;
            end
        endcase
    end
end

endmodule

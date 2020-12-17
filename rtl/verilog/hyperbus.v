/**
 * HyperBus Primary Controller
 *
 * Copyright (C) 2020 Matt Thompson <mthompson@hexwave.com>
 *
 * Input Clock = 200MHz
 * tACC = 35ns or 7 clocks
 * tVCS = 150us (reset initialization time)
 */

module hyperbus
#(
    parameter TARGET = "ALTERA",
    parameter WIDTH = 8,
    parameter TACC_COUNT = 5,
    parameter RESET_COUNT = 2
)
(
    // Memory clock
    input                       clk,
    // 90 degree phase shifted clock
    input                       clk90,
    input                       rst,

    input   [31:0]              adr_i,
    input   [(WIDTH<<1)-1:0]    dat_i,
    output  [(WIDTH<<1)-1:0]    dat_o,

    // Ready to accept a new input word on dat_i
    output                      ready,

    // Output word is valid on dat_o
    output                      valid,

    output                      busy,

    // Read from HyperRAM register space
    input                       reg_space_i,

    // Write request. Hold high until transaction complete.
    input                       wrq,

    // Read request. Hold high until transaction complete.
    input                       rrq,

    output                      hbus_clk,
    output                      hbus_rstn,
    output                      hbus_csn,
    inout   [WIDTH-1:0]         hbus_dq,
    inout                       hbus_rwds,

    output                      error_o,

    // Debug outputs
    output [1:0]                dbg_rwds
);

localparam COUNTER_WIDTH = $clog2(TACC_COUNT*2);

`define NSTATES 7

localparam STATE_IDLE =     `NSTATES'b0000001;
localparam STATE_RESET =    `NSTATES'b0000010;
localparam STATE_COMMAND =  `NSTATES'b0000100;
localparam STATE_LATENCY =  `NSTATES'b0001000;
localparam STATE_READ =     `NSTATES'b0010000;
localparam STATE_WRITE =    `NSTATES'b0100000;
localparam STATE_ERROR =    `NSTATES'b1000000;

reg [`NSTATES-1:0] state;

assign ready = (state == STATE_WRITE) ? 1'b1 : 1'b0;
assign valid = (state == STATE_READ) ? 1'b1 : 1'b0;

// Double width input, output, and rwds signals
// at half the DDR clock rate.
wire [(WIDTH<<1)-1:0]   dataw;
wire [(WIDTH<<1)-1:0]   datar;
wire [1:0]              rwdsr;
reg [1:0]               rwdsw;

reg [(WIDTH<<1)-1:0]    read_reg;

assign dat_o = read_reg;
assign dbg_rwds = rwdsr;

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
    (state == STATE_IDLE) || (state == STATE_ERROR) || (state == STATE_RESET) || (state == {`NSTATES{1'b0}})) ? 1'b1 : 1'b0;
assign busy = state == STATE_IDLE ? 1'b0 : 1'b1;

// Clock gate
assign hbus_clk = clk_oe90 ? clk90 : 1'b0;

// Command/Address register
reg [47:0] ca;

reg timeout_error;

assign error_o = state == STATE_ERROR ? 1'b1 : 1'b0;

// Clock counter
reg [COUNTER_WIDTH-1:0] count;

assign dataw = (state == STATE_WRITE) ? dat_i : ca[47:32];


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
    if(state == STATE_READ) begin
        // The RWDS DDR output will contain the
        // bit pattern 2'b01 on valid read strobes.
        // The RAM chip may hold RWDS low, and we will
        // ignore the DQ signals until the next strobe
        if(rwdsr == 2'b01) begin
            read_reg <= datar;
        end
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
                    state <= STATE_IDLE;
                end
            end
            STATE_IDLE: begin
                $display("Idle");

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
                    ca[45] <= 1'b0;

                    ca[44:16] <= adr_i[31:3];
                    ca[15:3] <= 13'd0;
                    ca[2:0] <= adr_i[2:0];

                    // Enable DQ output
                    //data_oe <= 1'b1;
                    
                    // Enable the output clock
                    //clk_oe <= 1'b1;

                    // RWDS input
                    rwds_oe <= 1'b0;

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
                $display("Send command");
                clk_oe <= 1'b1;
                data_oe <= 1'b1;

                if(count == 4'd0) begin
                    $display("Command sent");

                    if(rwdsr == 2'b11) begin
                        $display("2x latency");
                        wrq ? 16 : count <= (TACC_COUNT<<1) - 1;
                    end else begin
                        $display("1x latency");
                        wrq ? 8 : count <= TACC_COUNT - 1;
                    end

                    data_oe <= 1'b0;
                    state <= STATE_LATENCY;
                end else begin
                    // Shift CA register
                    ca <= ca << 16;

                    // Decrement the counter
                    count <= count - 1;
                end

            end

            STATE_LATENCY: begin
                $display("Latency state");

                rwds_oe <= 1'b0;
                count <= count - 1;

                if(count == {COUNTER_WIDTH{1'b0}}) begin
                    if(rrq) begin
                        // Set a timeout counter
                        count <= {COUNTER_WIDTH{1'b1}};
                        state <= STATE_READ;
                    end else if(wrq) begin
                        count <= 1;
                        rwdsw <= 2'b00;
                        rwds_oe <= 1'b1;
                        state <= STATE_WRITE;
                    end else begin
                        state <= STATE_IDLE;
                    end
                end
            end

            STATE_READ: begin
                $display("Read state");
                data_oe <= 1'b0;
                rwds_oe <= 1'b0;

                count <= count - 1;

                if(count == {COUNTER_WIDTH{1'b0}}) begin
                    timeout_error <= 1'b1;
                    state <= STATE_ERROR;
                end

                if(rwdsr != 2'b00) begin
                    // Minimum cycles to remain idle with CSn high
                    count <= 4'd1;
                    state <= STATE_IDLE;
                end
            end

            STATE_WRITE: begin
                $display("Write state");
                data_oe <= 1'b1;
                rwds_oe <= 1'b1;

                count <= count - 1;
                if(count == {COUNTER_WIDTH{1'b0}}) begin
                    data_oe <= 1'b0;
                    count <= 4'd1;
                    state <= STATE_IDLE;
                end
            end

            STATE_ERROR: begin
                $display("Error state");
                state <= STATE_ERROR;
            end

            default: begin
                $display("UNHANDLED STATE");
                count <= RESET_COUNT;
                state <= STATE_RESET;
            end
        endcase
    end
end

endmodule

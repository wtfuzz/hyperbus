module hyperbus
#(
    parameter TARGET = "ALTERA",
    parameter WIDTH = 8
)
(
    input               clk,
    input               rst,

    input   [31:0]      addr,
    input   [31:0]      din,
    output  [31:0]      dout,
    output              busy,

    // Write request
    input               wrq,

    // Read request
    input               rrq,

    output              hbus_clk,
    output              hbus_rstn,
    output              hbus_csn,
    inout   [WIDTH-1:0] hbus_dq,
    inout               hbus_rwds
);

`define NSTATES 6

localparam STATE_IDLE =     `NSTATES'b000001;
localparam STATE_COMMAND =  `NSTATES'b000010;
localparam STATE_WAIT1 =    `NSTATES'b000100;
localparam STATE_WAIT2 =    `NSTATES'b001000;
localparam STATE_READ =     `NSTATES'b010000;
localparam STATE_WRITE =    `NSTATES'b100000;

reg [`NSTATES-1:0] state;

// Double width input, output, and rwds signals
// at half the DDR clock rate.
wire [(WIDTH<<1)-1:0]   dataw;
wire [(WIDTH<<1)-1:0]   datar;
wire [1:0]              rwdsr;
wire [1:0]              rwdsw;

// Bidirectional DDR output enable
reg                     data_oe;
reg                     rwds_oe;

reg                     clk_oe;


/**
 * Bidirectional DDR IO.
 * The in and out ports provide 2*WIDTH on one edge of the clock
 */
ioddr
#(
    .TARGET(TARGET),
    .WIDTH(WIDTH)
) ddr_data (
    .clk(clk),
    .dataw(dataw),
    .datar(datar),
    .dq(hbus_dq),
    .oe(data_oe)
);

ioddr
#(
    .TARGET(TARGET),
    .WIDTH(1)
) ddr_rwds (
    .clk(clk),
    .dataw(rwdsw),
    .datar(rwdsr),
    .dq(hbus_rwds),
    .oe(rwds_oe)
);

assign hbus_rstn = 1'b1;
assign hbus_csn = state == STATE_IDLE ? 1'b1 : 1'b0;
assign busy = state == STATE_IDLE ? 1'b0 : 1'b1;

// Clock gate
assign hbus_clk = clk_oe ? ~clk : 1'b0;

// Command/Address register
reg [47:0]              ca;

// Clock counter
reg [3:0]               count;

assign dataw = ca[47:32];

always @(posedge clk) begin
    if(rst) begin
        state <= STATE_IDLE;
    end else begin
        case(state)
            STATE_IDLE: begin
                $display("Idle");

                if(rrq | wrq) begin
                    // Transition to command state
                    state <= STATE_COMMAND;

                    // Load the command/address register

                    // R/W# = 1 for read, 0 for write
                    ca[47] <= rrq ? 1'b1 : 1'b0;

                    // Address Space = 0 for memory, 1 for registers
                    ca[46] <= 1'b0;

                    // Burst Type = 0: wrapped, 1: linear
                    ca[45] <= 1'b0;

                    ca[44:16] <= addr[31:3];
                    ca[15:3] <= 13'd0;
                    ca[2:0] <= addr[2:0];

                    // Prime the write register 
                    //dataw <= ca[47:32];

                    // Enable DQ output
                    data_oe <= 1'b1;

                    // RWDS input
                    rwds_oe <= 1'b0;

                    // 3 cycles to write 48 bits
                    count <= 4'd3;

                    clk_oe <= 1'b1;
                end else begin
                    clk_oe <= 1'b0;
                    state <= STATE_IDLE;
                end
            end
            STATE_COMMAND: begin
                $display("Send command");
                //dataw <= ca[47:32];
                data_oe <= 1'b1;

                if(count == 4'd0) begin
                    $display("Command sent");
                    state <= rrq ? STATE_READ : STATE_WRITE;
                    data_oe <= rrq ? 1'b0 : 1'b1;
                    rwds_oe <= 1'b0;
                end else begin
                    // Shift CA register
                    ca <= ca << 16;

                    // Decrement the counter
                    count <= count - 4'd1;
                end

            end

            STATE_READ: begin
                $display("Read state");
            end

            STATE_WRITE: begin
                $display("Write state");
            end

            default: begin
                $display("UNHANDLED STATE");
                state <= STATE_IDLE;
            end
        endcase
    end
end

endmodule
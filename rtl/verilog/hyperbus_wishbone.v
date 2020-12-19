module hyperbus_wishbone
#(
    parameter WB_DATA_WIDTH = 32,
    parameter WB_ADDR_WIDTH = 32,
    parameter HBUS_ADDR_WIDTH = 32,
    parameter HBUS_DATA_WIDTH = 16
)
(
    input                           hbus_clk,
    input                           hbus_rst,
    output [HBUS_ADDR_WIDTH-1:0]    hbus_adr_o,
    input  [HBUS_DATA_WIDTH-1:0]    hbus_dat_i,
    output [HBUS_DATA_WIDTH-1:0]    hbus_dat_o,
    output [(HBUS_DATA_WIDTH/8)-1:0] hbus_mask_o,
    output                          hbus_rrq,
    output                          hbus_wrq,
    input                           hbus_ready,
    input                           hbus_valid,
    input                           hbus_busy,

    /* Wishbone Interface */
    input                           wb_clk,
    input                           wb_rst,
    input [WB_ADDR_WIDTH-1:0]       wb_adr_i,
    input [WB_DATA_WIDTH-1:0]       wb_dat_i,
    input                           wb_we_i,
    input [3:0]                     wb_sel_i,
    input                           wb_cyc_i,
    input                           wb_stb_i,
    input         [2:0]             wb_cti_i,
    input         [1:0]             wb_bte_i,
    output [WB_DATA_WIDTH-1:0]      wb_dat_o,
    output reg                      wb_ack_o,
    output                          wb_err_o,
    output                          wb_rty_o
);

`define NSTATES 7

localparam STATE_IDLE =     `NSTATES'b0000001;
localparam STATE_WRITE =    `NSTATES'b0000010;
localparam STATE_READ =     `NSTATES'b0000100;
localparam STATE_WAIT =     `NSTATES'b0001000;

reg [`NSTATES-1:0] state;

reg rrq;
reg wrq;

wire tx_ready;
wire rx_valid;

hyperbus_fifo fifo_inst (
  .hbus_clk(hbus_clk),
  .hbus_rst(hbus_rst),
  .hbus_adr_o(hbus_adr_o),
  .hbus_dat_i(hbus_dat_i),
  .hbus_dat_o(hbus_dat_o),
  .hbus_mask_o(hbus_mask_o),
  .hbus_rrq(hbus_rrq),
  .hbus_wrq(hbus_wrq),
  .hbus_ready(hbus_ready),
  .hbus_valid(hbus_valid),
  .hbus_busy(hbus_busy),

  .clk(wb_clk),
  .rst(hbus_rst),

  .rrq(rrq),
  .wrq(wrq),

  .adr_i({wb_adr_i[31:2], 2'b00}),
  .tx_dat_i(wb_dat_i),
  .tx_mask_i(~wb_sel_i),
  .rx_dat_o(wb_dat_o),

  .tx_ready(tx_ready),
  .rx_valid(rx_valid)
);

always @(posedge wb_clk) begin
  if(wb_rst) begin
    rrq <= 1'b0;
    wrq <= 1'b0;
    state <= STATE_IDLE;
  end else begin

    wb_ack_o <= 1'b0;
    rrq <= 1'b0;
    wrq <= 1'b0;

    case(state)
      STATE_IDLE: begin
        state <= STATE_IDLE;

        if (~wb_ack_o & wb_cyc_i & wb_stb_i & wb_we_i) begin
          wrq <= 1'b1;
          state <= STATE_WRITE;
        end else if (~wb_ack_o & wb_cyc_i & wb_stb_i & ~wb_we_i) begin
          rrq <= 1'b1;
          state <= STATE_READ;
        end
      end

      STATE_READ: begin
        if(rx_valid) begin
          state <= STATE_IDLE;
          wb_ack_o <= 1'b1;
        end
      end

      STATE_WRITE: begin
        if(tx_ready) begin
          state <= STATE_IDLE;
          wb_ack_o <= 1'b1;
        end
      end

      default: state <= STATE_IDLE;
    endcase
  end
end

assign wb_err_o = 0;
assign wb_rty_o = 0;

endmodule
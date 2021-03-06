/**
 * Copyright Matt Thompson <mthompson@hexwave.com> 2020.
 * This source describes Open Hardware and is licensed under the CERN-OHL-P v2
 *
 * You may redistribute and modify this documentation and make products
 * using it under the terms of the CERN-OHL-P v2 (https:/cern.ch/cern-ohl).
 * This documentation is distributed WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY
 * AND FITNESS FOR A PARTICULAR PURPOSE. Please see the CERN-OHL-P v2
 * for applicable conditions
 */

module hyperbus_wishbone
#(
    parameter WB_DATA_WIDTH = 32,
    parameter WB_ADDR_WIDTH = 32,
    parameter HBUS_ADDR_WIDTH = 32,
    parameter HBUS_DATA_WIDTH = 16
)
(
  /** FIFO Interface */
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

localparam NSTATES =        4;

localparam STATE_IDLE =     4'b0001;
localparam STATE_WRITE =    4'b0010;
localparam STATE_READ =     4'b0100;
localparam STATE_WAIT =     4'b1000;

reg [NSTATES-1:0] state;

reg rrq;
reg wrq;

wire tx_done;
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

  .clk(wb_clk),
  .rst(wb_rst),

  .rrq(rrq),
  .wrq(wrq),

  .adr_i({wb_adr_i[31:2], 2'b00}),
  .tx_dat_i(wb_dat_i),
  .tx_mask_i(~wb_sel_i),
  .rx_dat_o(wb_dat_o),

  .tx_done(tx_done),
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
        if(tx_done) begin
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
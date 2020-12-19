
module hyperbus_fifo_test_top(
    input       clk,
    input       clk90,
    input       rst,

    output      tx_fifo_ready,
    output      rx_fifo_valid,
    output [31:0] rx_fifo_data,

    input       rrq,
    input       wrq
);

wire        hbus_clk;
wire        hbus_csn;
wire        hbus_rstn;
wire [7:0]  hbus_dq;
wire        hbus_rwds;

wire [31:0] hbus_adr_i;
wire [15:0] hbus_dat_i;
wire [15:0] hbus_dat_o;
wire hbus_mask_o;

wire        hbus_rrq;
wire        hbus_wrq;

wire        hbus_ready;
wire        hbus_valid;

hyperbus #(
    .TARGET("SIM"),
    .WIDTH(8)
) hbus0 (
    .clk        (clk),
    .clk90      (clk90),
    .rst        (rst),
    .hbus_clk   (hbus_clk),
    .hbus_rstn  (hbus_rstn),
    .hbus_csn   (hbus_csn),
    .hbus_dq    (hbus_dq),
    .hbus_rwds  (hbus_rwds),

    .ready      (hbus_ready),
    .valid      (hbus_valid),

    .mask_i     (hbus_mask_o),

    .reg_space_i (1'b0),
    .adr_i       (hbus_adr_i),
    .dat_i       (hbus_dat_i),
    .dat_o       (hbus_dat_o),
    .wrq        (hbus_wrq),
    .rrq        (hbus_rrq)
);

hyperbus_fifo fifo_inst (
  .hbus_clk(clk),
  .hbus_rst(rst),
  .hbus_adr_o(hbus_adr_i),
  .hbus_dat_i(hbus_dat_o),
  .hbus_dat_o(hbus_dat_i),
  .hbus_mask_o(hbus_mask_o),
  .hbus_rrq(hbus_rrq),
  .hbus_wrq(hbus_wrq),
  .hbus_ready(hbus_ready),
  .hbus_valid(hbus_valid),

  .clk(clk),
  .rst(rst),

  .rrq(rrq),
  .wrq(wrq),

  .adr_i(32'haaaaaaaa),
  .tx_dat_i(32'hdeadbeef),
  .tx_mask_i(4'b0000),
  .rx_dat_o(rx_fifo_data),

  .tx_ready(tx_fifo_ready),
  .rx_valid(rx_fifo_valid),
);

endmodule

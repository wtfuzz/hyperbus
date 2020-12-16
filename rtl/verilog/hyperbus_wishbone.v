module hyperbus_wishbone
#(
    parameter WB_DATA_WIDTH = 32,
    parameter WB_ADDR_WIDTH = 32,
    parameter HBUS_DATA_WIDTH = 16
)
(
    input                           hbus_clk,
    input [HBUS_DATA_WIDTH-1:0]     hbus_dat_i,
    output [HBUS_DATA_WIDTH-1:0]    hbus_dat_o,
    output                          hbus_rrq,
    output                          hbus_wrq,
    input                           hbus_busy,

    /* Wishbone Interface */
    input                           wb_clk,
    input                           wb_rst,
    input [WB_ADDR_WIDTH-1:0]       wb_adr_i,
    input [WB_DATA_WIDTH-1:0]       wb_dat_i,
    input                           wb_we_i,
    input                           wb_cyc_i,
    input                           wb_stb_i,
    input         [2:0]             wb_cti_i,
    input         [1:0]             wb_bte_i,
    output [WB_DATA_WIDTH-1:0]      wb_dat_o,
    output reg                      wb_ack_o,
    output                          wb_err_o,
    output                          wb_rty_o
);

always @(posedge wb_clk) begin
    
end

/* Wishbone Writes */
always @(posedge wb_clk) begin
  if (wb_rst) begin
    datar <= INITIAL_DATAR;
    dir <= INITIAL_DIR;
    ddr <= INITIAL_DDR;
    imr <= {WIDTH{1'b0}};
    ifr <= {WIDTH{1'b0}}; 
    ier <= {WIDTH{1'b0}}; 
  end

  else if (wb_cyc_i & wb_stb_i && wb_we_i) begin

  end
end

/* Wishbone Reads */
always @(posedge wb_clk) begin
  if (wb_cyc_i & wb_stb_i & !wb_we_i) begin
  end
end

always @(posedge wb_clk) begin
  if (wb_rst)
    wb_ack_o <= 0;
  else if (wb_cyc_i & wb_stb_i)
    wb_ack_o <= 1;
  else
    wb_ack_o <= 0;
end

assign wb_err_o = 0;
assign wb_rty_o = 0;

endmodule
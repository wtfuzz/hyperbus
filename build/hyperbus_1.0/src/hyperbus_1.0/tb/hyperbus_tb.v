module hyperbus_test_top(
    input       clk,
    input       clk90,
    input       rst,

    output      hbus_clk,
    output      hbus_csn,
    output      hbus_rstn,
    inout [7:0] hbus_dq,
    inout       hbus_rwds,

    input [31:0] addr,
    input [15:0] datar,
    output [15:0] dataw,

    input wrq,
    input rrq,

    output busy
);

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

    .dready     (),
    .dvalid     (),
    .error_o    (),

    .reg_space_i (1'b0),
    .adr_i       (addr),
    .dat_i       (datar),
    .dat_o       (dataw),
    .busy       (busy),
    .wrq        (wrq),
    .rrq        (rrq)
);

endmodule

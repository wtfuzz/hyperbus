module hyperbus_test_top(
    input       clk,
    input       rst,

    output      hbus_clk,
    output      hbus_csn,
    output      hbus_rstn,
    inout [7:0] hbus_dq,
    inout       hbus_rwds,

    input [31:0] addr,
    input [31:0] datar,
    output [31:0] dataw,

    input wrq,
    input rrq,

    output busy
);

hyperbus #(
    .TARGET("SIM"),
    .WIDTH(8)
) ram0 (
    .clk        (clk),
    .rst        (rst),
    .hbus_clk   (hbus_clk),
    .hbus_rstn  (hbus_rstn),
    .hbus_csn   (hbus_csn),
    .hbus_dq    (hbus_dq),
    .hbus_rwds  (hbus_rwds),

    .addr       (addr),
    .din        (datar),
    .dout       (dataw),
    .busy       (busy),
    .wrq        (wrq),
    .rrq        (rrq)
);

endmodule
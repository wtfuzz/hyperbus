module ioddr_test_top
(
    input clk,
    input oe,
    input [15:0] dataw,
    output [15:0] datar,
    inout [7:0] dq
);

ioddr #(
    .TARGET("SIM")
) io0 (
    .clk(clk),
    .oe(oe),
    .dataw(dataw),
    .datar(datar),
    .dq(dq)
);

endmodule
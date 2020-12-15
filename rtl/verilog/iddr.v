/**
 * Input DDR Module
 */

module iddr
#(
    parameter TARGET = "ALTERA",
    parameter WIDTH = 8
)
(
    input                       clk,
    input                       en,
    output  [(WIDTH<<1)-1:0]    dat_o,
    input   [WIDTH-1:0]         d
);

// TODO: Add additional DDR implementations.
// Currently only Altera ALTDDR is supported.
/* verilator lint_off WIDTH */
generate
if(TARGET == "ALTERA") begin : altera_ioddr_gen
    // https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/ug/mfug_ddio.pdf

    altddio_in #(
        .WIDTH(WIDTH),
        .POWER_UP_HIGH("OFF"),
        .OE_REG("UNUSED")
    ) ddr0 (
        .inclock(clk),
        .inclocken(en),
        .aset(1'b0),
        .dataout_h(dat_o[(WIDTH<<1)-1 : (WIDTH)]),
        .dataout_l(dat_o[WIDTH-1:0]),
        .datain(d)
    );

end else begin
    // Fallback to pure verilog for simulation

    reg [(WIDTH<<1)-1:0] q;
    assign dat_o = q;

    always @(posedge clk) begin
        if(en) begin
            q[(WIDTH<<1)-1:WIDTH] <= d;
        end
    end

    always @(negedge clk) begin
        if(en) begin
            q[WIDTH-1:0] <= d;
        end
    end
    /* verilator lint_on MULTIDRIVEN */
end

endgenerate

endmodule

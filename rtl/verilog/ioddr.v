module ioddr
#(
    parameter TARGET = "ALTERA",
    parameter WIDTH = 8
)
(
    input                       inclk,
    input                       outclk,
    input                       oe,
    input   [(WIDTH<<1)-1:0]    dat_i,
    output  [(WIDTH<<1)-1:0]    dat_o,
    inout   [WIDTH-1:0]         dq
);

// TODO: Add additional DDR implementations.
// Currently only Altera ALTDDR is supported.
/* verilator lint_off WIDTH */
generate
if(TARGET == "ALTERA") begin : altera_ioddr_gen
    // https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/ug/ug_altddio.pdf

    altddio_bidir #(
        .WIDTH(WIDTH),
        .POWER_UP_HIGH("OFF"),
        .OE_REG("UNUSED")
    ) ddr0 (
        .inclock(inclk),
        .outclock(outclk),
        .oe(oe),
        .outclocken(1'b1),
        .aset(1'b0),
        .datain_h(dataw[(WIDTH<<1)-1 : (WIDTH)]),
        .datain_l(dataw[WIDTH-1:0]),
        .dataout_h(datar[(WIDTH<<1)-1 : (WIDTH)]),
        .dataout_l(datar[WIDTH-1:0]),
        .padio(dq)
    );

end else begin
    // Fallback to pure verilog for simulation

    /* verilator lint_off MULTIDRIVEN */
    reg [(WIDTH<<1)-1:0] d;
    reg [WIDTH-1:0] q;

    // Tristate
    assign dq = oe ? q : {WIDTH{1'bz}};
    assign datar = d;

    always @(posedge clk) begin
        q <= dataw[WIDTH-1:0];
        if(oe) begin
        end else begin
            d[(WIDTH<<1)-1:WIDTH] <= dq;
        end
    end

    always @(negedge clk) begin
        if(oe) begin
            q <= dataw[(WIDTH<<1)-1 : WIDTH];
        end else begin
            d[WIDTH-1:0] <= dq;
        end
    end
    /* verilator lint_on MULTIDRIVEN */
end

endgenerate

endmodule


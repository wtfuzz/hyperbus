/**
 * Hyperbus dual port FIFO interface
 */

module hyperbus_fifo
#(
    parameter FIFO_DATA_WIDTH = 32,
    parameter FIFO_ADDR_WIDTH = 32,
    parameter HBUS_ADDR_WIDTH = 32,
    parameter HBUS_DATA_WIDTH = 16
)
(
    /** Hyperbus native memory interface */
    input                               hbus_clk,
    input                               hbus_rst,
    output reg [HBUS_ADDR_WIDTH-1:0]    hbus_adr_o,
    input  [HBUS_DATA_WIDTH-1:0]        hbus_dat_i,
    output [HBUS_DATA_WIDTH-1:0]        hbus_dat_o,
    output reg                          hbus_rrq,
    output reg                          hbus_wrq,
    input                               hbus_ready,
    input                               hbus_valid,
    input                               hbus_busy,


    /** User FIFO clock and reset */
    input                               clk,
    input                               rst,

    input                               rrq,
    input                               wrq,

    input [FIFO_ADDR_WIDTH-1:0]         adr_i,

    /** TX FIFO interface */
    input [FIFO_DATA_WIDTH-1:0]         tx_dat_i,
    output reg                          tx_ready,

    /** RX FIFO interface */
    output [FIFO_DATA_WIDTH-1:0]        rx_dat_o,
    output reg                          rx_valid
);

localparam NSTATES = 3;
localparam STATE_IDLE =     3'b001;
localparam STATE_READ =     3'b010;
localparam STATE_WRITE =    3'b100;

localparam CMD_READ =       1'b1;
localparam CMD_WRITE =      1'b0;

// Number of hbus transfers per FIFO transfer
localparam CYCLES = (FIFO_DATA_WIDTH / HBUS_DATA_WIDTH);

reg [NSTATES-1:0] state;
reg [7:0] count;

/** FIFO Signals */
reg [32:0] cmd_wdata;
wire [32:0] cmd_rdata;
reg cmd_rinc;
reg cmd_winc;

reg [31:0] tx_wdata;
wire [31:0] tx_rdata;
reg tx_rinc;
reg tx_winc;

reg [31:0] rx_wdata;
wire [31:0] rx_rdata;
reg rx_rinc;
reg rx_winc;

reg [FIFO_DATA_WIDTH-1:0] tx_shift;

assign hbus_dat_o = tx_shift[HBUS_DATA_WIDTH-1:0];
assign rx_dat_o = rx_rdata;

/** Command FIFO carries R/W bit and address */
async_fifo
#(
  .DSIZE(HBUS_ADDR_WIDTH + 1),
  .ASIZE(2)
) cmd_fifo (
  .wclk(clk),
  .wrst_n(~rst),
  .winc(cmd_winc),
  .wdata(cmd_wdata),
  .wfull(cmd_wfull),
  .awfull(),

  .rclk(hbus_clk),
  .rrst_n(~hbus_rst),
  .rinc(cmd_rinc),
  .rdata(cmd_rdata),
  .rempty(cmd_rempty),
  .arempty()
);

async_fifo
#(
  .DSIZE(32),
  .ASIZE(2)
) tx_fifo (
  .wclk(clk),
  .wrst_n(~rst),
  .winc(tx_winc),
  .wdata(tx_wdata),
  .wfull(tx_wfull),
  .awfull(),

  .rclk(hbus_clk),
  .rrst_n(~hbus_rst),
  .rinc(tx_rinc),
  .rdata(tx_rdata),
  .rempty(tx_rempty),
  .arempty()
);

async_fifo
#(
  .DSIZE(32),
  .ASIZE(2)
) rx_fifo (
  .wclk(hbus_clk),
  .wrst_n(~hbus_rst),
  .winc(rx_winc),
  .wdata(rx_wdata),
  .wfull(rx_wfull),
  .awfull(),

  .rclk(clk),
  .rrst_n(~rst),
  .rinc(rx_rinc),
  .rdata(rx_rdata),
  .rempty(rx_rempty),
  .arempty()
);

/** Hyperbus clock domain state machine */
always @(posedge hbus_clk or posedge hbus_rst) begin

    if(hbus_rst) begin
        hbus_rrq <= 1'b0;
        hbus_wrq <= 1'b0; 
        cmd_rinc <= 1'b0;
        tx_rinc <= 1'b0;
        
        state <= STATE_IDLE;
    end else begin

        cmd_rinc <= 1'b0;
        tx_rinc <= 1'b0;

        case(state)
            STATE_IDLE: begin
                // Check if there is an available command in the Command FIFO

                hbus_wrq <= 1'b0;
                hbus_rrq <= 1'b0;

                if(!cmd_rempty) begin
                    cmd_rinc <= 1'b1;
                    hbus_adr_o <= cmd_rdata[31:0];

                    // TODO: support streaming read/writes for DMA, burst transfers
                    count <= CYCLES;

                    // Check the R/W bit
                    if(cmd_rdata[32] == CMD_WRITE) begin
                        hbus_wrq <= 1'b1;
                        tx_shift <= tx_rdata;
                        state <= STATE_WRITE;
                    end else begin
                        hbus_rrq <= 1'b1;
                        state <= STATE_READ;
                    end
                end
            end

            STATE_READ: begin
                if(count == 0) begin
                    // Write to the RX FIFO 
                    rx_winc <= 1'b1;
                    state <= STATE_IDLE;
                end else begin
                    if(hbus_valid && rx_rempty) begin
                        count <= count - 1;

                        // Shift the valid data into the RX shift register
                        rx_wdata <= (rx_wdata << HBUS_DATA_WIDTH) | hbus_dat_i;
                    end else begin
                        state <= STATE_READ;
                    end
                end
            end

            STATE_WRITE: begin
                if(count == 0) begin
                    tx_rinc <= 1'b1;
                    state <= STATE_IDLE;
                end else begin
                    //if(hbus_ready && ~tx_rempty) begin
                    if(~tx_rempty) begin
                        count <= count - 1;

                        // Shift the TX register
                        tx_shift <= tx_shift << HBUS_DATA_WIDTH;
                    end      
                end
            end
        endcase
    end
end

/** User clock domain */
always @(posedge clk or posedge rst) begin
    if(rst) begin
        cmd_winc <= 1'b0;
        tx_winc <= 1'b0;
    end else begin
        cmd_winc <= 1'b0;
        tx_winc <= 1'b0;
        if(rrq) begin
            // Write a read request to the command FIFO
            cmd_winc <= 1'b1;
            cmd_wdata <= {CMD_READ, adr_i};
        end else if(wrq) begin
            // Write a write request to the command FIFO
            cmd_winc <= 1'b1;
            cmd_wdata <= {CMD_WRITE, adr_i};

            // Write the data to be written into the TX FIFO
            tx_winc <= 1'b1;
            tx_wdata <= tx_dat_i;
        end
    end
end

/** Data FIFO control */
always @(posedge clk) begin
    tx_ready <= 1'b0;
    rx_valid <= 1'b0;
    rx_rinc <= 1'b0;

    if(tx_rempty) begin
        tx_ready <= 1'b1;
    end

    if(~rx_rempty) begin
        rx_valid <= 1'b1;
        rx_rinc <= 1'b1;
    end
end

endmodule
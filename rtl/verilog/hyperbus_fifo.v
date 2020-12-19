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
    output [(HBUS_DATA_WIDTH/8)-1:0]    hbus_mask_o,
    output reg                          hbus_rrq,
    output reg                          hbus_wrq,
    input                               hbus_ready,
    input                               hbus_valid,

    /** User FIFO clock and reset */
    input                               clk,
    input                               rst,

    input                               rrq,
    input                               wrq,

    input [FIFO_ADDR_WIDTH-1:0]         adr_i,

    /** TX FIFO interface */
    input [FIFO_DATA_WIDTH-1:0]         tx_dat_i,
    input [(FIFO_DATA_WIDTH/8)-1:0]     tx_mask_i,
    output reg                          tx_done,

    /** RX FIFO interface */
    output reg [FIFO_DATA_WIDTH-1:0]    rx_dat_o,
    output reg                          rx_valid
);

localparam NSTATES = 3;
localparam STATE_IDLE =     3'b001;
localparam STATE_READ =     3'b010;
localparam STATE_WRITE =    3'b100;

localparam CMD_READ =       1'b1;
localparam CMD_WRITE =      1'b0;

localparam FIFO_ASIZE = 2;
localparam FIFO_MASK_BITS = (FIFO_DATA_WIDTH / 8);
localparam HBUS_MASK_BITS = (HBUS_DATA_WIDTH / 8);

// Number of hbus transfers per FIFO transfer
localparam CYCLES = (FIFO_DATA_WIDTH / HBUS_DATA_WIDTH);

reg [NSTATES-1:0] state;
reg [7:0] count;

/** FIFO Signals */
reg [HBUS_ADDR_WIDTH:0] cmd_wdata;
wire [HBUS_ADDR_WIDTH:0] cmd_rdata;
reg cmd_rinc;
reg cmd_winc;
wire cmd_wfull;
wire cmd_rempty;
wire cmd_arempty;

reg [FIFO_DATA_WIDTH + FIFO_MASK_BITS - 1:0] tx_wdata;
wire [FIFO_DATA_WIDTH + FIFO_MASK_BITS - 1:0] tx_rdata;
reg tx_rinc;
reg tx_winc;
wire tx_wfull;
wire tx_rempty;

reg [FIFO_DATA_WIDTH-1:0] rx_wdata;
wire [FIFO_DATA_WIDTH-1:0] rx_rdata;
reg rx_rinc;
reg rx_winc;
wire rx_wfull;
wire rx_rempty;

reg ack_wdata;
wire ack_rdata;
reg ack_rinc;
reg ack_winc;
wire ack_wfull;
wire ack_rempty;

reg [FIFO_MASK_BITS-1:0] tx_mask;
reg [FIFO_DATA_WIDTH-1:0] tx_shift;

assign hbus_dat_o = tx_shift[FIFO_DATA_WIDTH-1:FIFO_DATA_WIDTH-HBUS_DATA_WIDTH];
assign hbus_mask_o = tx_mask[FIFO_MASK_BITS-1:FIFO_MASK_BITS-HBUS_MASK_BITS];

/** Command FIFO carries R/W bit and address */
async_fifo
#(
  .DSIZE(HBUS_ADDR_WIDTH + 1),
  .ASIZE(FIFO_ASIZE)
) cmd_fifo (
  .wclk(clk),
  .wrst_n(~rst),
  .winc(cmd_winc),
  .wdata(cmd_wdata),
  .wfull(cmd_wfull),
  .awfull(),

  .rclk(hbus_clk),
  .rrst_n(~rst),
  .rinc(cmd_rinc),
  .rdata(cmd_rdata),
  .rempty(cmd_rempty),
  .arempty(cmd_arempty)
);

/** TX FIFO carries TX data and mask */
async_fifo
#(
  .DSIZE(FIFO_DATA_WIDTH + FIFO_MASK_BITS),
  .ASIZE(FIFO_ASIZE)
) tx_fifo (
  .wclk(clk),
  .wrst_n(~rst),
  .winc(tx_winc),
  .wdata(tx_wdata),
  .wfull(tx_wfull),
  .awfull(),

  .rclk(hbus_clk),
  .rrst_n(~rst),
  .rinc(tx_rinc),
  .rdata(tx_rdata),
  .rempty(tx_rempty),
  .arempty()
);

async_fifo
#(
  .DSIZE(FIFO_DATA_WIDTH),
  .ASIZE(FIFO_ASIZE)
) rx_fifo (
  .wclk(hbus_clk),
  .wrst_n(~rst),
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

// TX ACK fifo
async_fifo
#(
  .DSIZE(1),
  .ASIZE(FIFO_ASIZE)
) ack_fifo (
  .wclk(hbus_clk),
  .wrst_n(~rst),
  .winc(ack_winc),
  .wdata(ack_wdata),
  .wfull(ack_wfull),
  .awfull(),

  .rclk(clk),
  .rrst_n(~rst),
  .rinc(ack_rinc),
  .rdata(ack_rdata),
  .rempty(ack_rempty),
  .arempty()
);

/** Hyperbus clock domain state machine */
always @(posedge hbus_clk or posedge hbus_rst) begin
    if(hbus_rst) begin
        hbus_rrq <= 1'b0;
        hbus_wrq <= 1'b0; 
        cmd_rinc <= 1'b0;
        tx_rinc <= 1'b0;
        rx_winc <= 1'b0;
        
        state <= STATE_IDLE;
    end else begin

        cmd_rinc <= 1'b0;
        tx_rinc <= 1'b0;
        rx_winc <= 1'b0;
        ack_winc <= 1'b0;

        case(state)
            STATE_IDLE: begin
                // Check if there is an available command in the Command FIFO

                hbus_wrq <= 1'b0;
                hbus_rrq <= 1'b0;

                if(~cmd_rempty) begin
                    ack_winc <= 1'b1;
                    
                    cmd_rinc <= 1'b1;
                    hbus_adr_o <= cmd_rdata[31:0];

                    // TODO: support streaming read/writes for DMA, burst transfers
                    count <= CYCLES;

                    // Check the R/W bit
                    if(cmd_rdata[FIFO_DATA_WIDTH] == CMD_WRITE) begin
                        hbus_wrq <= 1'b1;
                        tx_mask <= tx_rdata[FIFO_DATA_WIDTH+FIFO_MASK_BITS-1:FIFO_DATA_WIDTH];
                        tx_shift <= tx_rdata[FIFO_DATA_WIDTH-1:0];
                        state <= STATE_WRITE;
                    end else begin
                        hbus_rrq <= 1'b1;
                        rx_wdata <= {FIFO_DATA_WIDTH{1'b0}};
                        state <= STATE_READ;
                    end
                end
            end

            STATE_READ: begin
                if(count == 0) begin
                    // Write to the RX FIFO 
                    rx_winc <= 1'b1;
                    hbus_rrq <= 1'b0;
                    state <= STATE_IDLE;
                end else begin
                    //if(hbus_valid && rx_rempty) begin
                    if(hbus_valid) begin
                        if(count == 1) begin
                            hbus_rrq <= 1'b0;
                        end
                        count <= count - 8'd1;

                        // Shift the valid data into the RX shift register
                        rx_wdata <= (rx_wdata << HBUS_DATA_WIDTH) | {{HBUS_DATA_WIDTH{1'b0}}, hbus_dat_i};
                    end
                end
            end

            STATE_WRITE: begin
                if(count == 0) begin
                    tx_rinc <= 1'b1;

                    // Write an ack to the ACK FIFO to sync to the user clock
                    ack_wdata <= 1'b1;
                    ack_winc <= 1'b1;

                    hbus_wrq <= 1'b0;
                    state <= STATE_IDLE;
                end else begin
                    //if(hbus_ready) begin
                        if(count == 1) begin
                            hbus_wrq <= 1'b0;
                        end
                        count <= count - 8'd1;

                        // Shift the TX register
                        tx_shift <= tx_shift << HBUS_DATA_WIDTH;

                        // Shift the mask register
                        tx_mask <= tx_mask << (HBUS_DATA_WIDTH/8);
                    //end      
                end
            end

            default: state <= STATE_IDLE;
        endcase
    end
end

reg [NSTATES-1:0] user_state;

/** User clock domain */
always @(posedge clk or posedge rst) begin
    if(rst) begin
        cmd_winc <= 1'b0;
        tx_winc <= 1'b0;
        tx_done <= 1'b0;
        rx_valid <= 1'b0;
        rx_rinc <= 1'b0;
        ack_rinc <= 1'b0;

        user_state <= STATE_IDLE;
    end else begin

        cmd_winc <= 1'b0;
        tx_winc <= 1'b0;
        tx_done <= 1'b0;
        rx_valid <= 1'b0;
        rx_rinc <= 1'b0;
        ack_rinc <= 1'b0;

        case(user_state)

            STATE_IDLE: begin
                if(rrq) begin
                    // Write a read request to the command FIFO
                    cmd_winc <= 1'b1;
                    cmd_wdata <= {CMD_READ, adr_i[31:0]};

                    user_state <= STATE_READ;
                end else if(wrq) begin
                    // Write a write request to the command FIFO
                    cmd_winc <= 1'b1;
                    cmd_wdata <= {CMD_WRITE, adr_i[31:0]};

                    // Write the data to be written into the TX FIFO
                    tx_winc <= 1'b1;
                    tx_wdata <= {tx_mask_i, tx_dat_i};

                    user_state <= STATE_WRITE;
                end
            end

            STATE_READ: begin
                //if(~rx_rempty) begin
                    rx_valid <= 1'b1;
                    rx_dat_o <= rx_rdata;
                    rx_rinc <= 1'b1;
                    user_state <= STATE_IDLE;
                //end
            end

            STATE_WRITE: begin
                if(~ack_rempty) begin
                    tx_done <= 1'b1;
                    ack_rinc <= 1'b1;
                    user_state <= STATE_IDLE;
                end          
            end

            default: user_state <= STATE_IDLE;
        endcase

    end
end

endmodule
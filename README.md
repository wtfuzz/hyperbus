# HyperBus Controller

This is a HyperBus leader for accessing external HyperRAM devices from an FPGA. Developed and tested up to 100MHz on an Intel Cyclone 10 LP Evaluation board with onboard 16MB HyperRAM chip and VexRiscv RISC-V CPU.

A clock crossing FIFO and Wishbone interface are provided. The core is implemented in Verilog and is easily integrated into [FuseSoC](https://github.com/olofk/fusesoc) designs by the provided CAPI2 core file.

The RAM clock and wishbone clock are independent and each side is driven by its own clock with synronization using a [dual clock async FIFO](https://github.com/dpretet/async_fifo). Requests from the wishbone bus are queued into a command and data FIFO, and the HyberBus core will queue response data and acks back to the wishbone side.

## TODO
* Test 166MHz
* Add stream support to the FIFO interface for DMA
* Add support for Wishbone burst transfers
* Integrate an internal cache to reduce HyperBus command/address bytes and latency overhead
* Fix SDC constraints
* Add additional bus interfaces

## Requirements

* Currently only Intel FPGAs are supported
    * Intel `ALTDDIO_BIDIR` is used internally for DDR IO on the `DQ` and `RWDS` signals
    * Other DDR primitives may be added for additional target FPGAs
* A 100MHz clock, as well as a 90 degree phase shifted clock (2500ps shift) must be provided by a PLL
* Call SDC function included in `data/hyperbus.sdc` for assigning clock and data pin constrains

## Test Environment

* Tested on an Intel Cyclone 10 LP Evaluation Kit board
    * Includes onboard 128Mbit HyperRAM chip

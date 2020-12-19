# HyperBus Controller

This is a HyperBus leader for accessing external HyperRAM devices from an FPGA. Developed and tested up to 200MHz on an Intel Cyclone 10 LP Evaluation board with onboard 16MB HyperRAM chip.

A clock crossing FIFO and Wishbone interfaces are provided. The core is implemented in Verilog and is easily integrated into [FuseSoC](https://github.com/olofk/fusesoc) designs by the provided CAPI2 core file.

## Requirements

* Currently only Intel FPGAs are supported
    * Intel `ALTDDIO_BIDIR` is used internally for DDR IO on the `DQ` and `RWDS` signals
    * Other DDR primitives may be added for additional target FPGAs
* A 200MHz clock, as well as a 90 degree phase shifted clock (1250ps shift) must be provided by a PLL
* Function included in `data/hyperbus.sdc` for creating constrains using a 200MHz clock

## Test Environment

* Tested on an Intel Cyclone 10 LP Evaluation Kit board
    * Includes onboard 128Mbit HyperRAM chip

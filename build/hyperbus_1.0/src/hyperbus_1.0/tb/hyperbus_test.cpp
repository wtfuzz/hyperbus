#include <stdlib.h>
#include "Vhyperbus_test_top.h"
#include "verilated.h"
#include "verilated_vcd_c.h"


#define STEPS 256

int main(int argc, char **argv) {
  // Initialize Verilators variables
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);

  VerilatedVcdC *tfp = new VerilatedVcdC;
  Vhyperbus_test_top *tb = new Vhyperbus_test_top;

  tb->trace(tfp, 99);
  tfp->open("trace.vcd");

  // Write 16 bit SDR data, expect 8 bit DDR output on DQ
  tb->rrq = 1;
  tb->addr = 0xaaaa;
  tb->clk = 0;
  tb->clk90 = 1;
  tb->eval();

  for(int step=0;step<STEPS;step+=4)
  {
    tb->clk = 1;
    tb->eval();
    tfp->dump(10*step);
    tb->clk90 = 0;
    tb->eval();
    tfp->dump(10*(step+1));
    tfp->flush();

    printf("clk=%d hbus_dq=%02X\n", tb->clk, tb->hbus_dq);

    tb->clk = 0;
    tb->eval();
    tfp->dump(10*(step+2));
    tb->clk90 = 1;
    tb->eval();
    tfp->dump(10*(step+3));
    printf("clk=%d hbus_dq=%02X\n", tb->clk, tb->hbus_dq);

    tfp->flush();
  }

  tfp->close();

}
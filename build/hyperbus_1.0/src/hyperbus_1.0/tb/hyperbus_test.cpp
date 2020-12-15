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

  int step = 0;

  tb->trace(tfp, 99);
  tfp->open("trace.vcd");

  // Reset
  tb->rst = 1;
  while(step <= 2)
  {
    tb->clk = 1;
    tb->eval();
    tfp->dump(10*(step++));

    tb->clk90 = 0;
    tb->eval();
    tfp->dump(10*(step++));
    
    tb->clk = 0;
    tb->eval();
    tfp->dump(10*(step++));

    tb->clk90 = 1;
    tb->eval();
    tfp->dump(10*(step++));
  }
  tb->rst = 0;

  // Write 16 bit SDR data, expect 8 bit DDR output on DQ
  tb->rrq = 1;
  tb->addr = 0xaaaa;
  /*
  tb->clk = 0;
  tb->eval();
  tfp->dump(10*(step++));
  
  tb->clk90 = 1;
  tb->eval();
  tfp->dump(10*(step++));
  */

  while(step <= STEPS)
  {
    tb->clk = 1;
    tb->eval();
    tfp->dump(10*(step++));
    tb->clk90 = 0;
    tb->eval();
    tfp->dump(10*(step++));
    tfp->flush();

    printf("clk=%d hbus_dq=%02X\n", tb->clk, tb->hbus_dq);

    tb->clk = 0;
    tb->eval();
    tfp->dump(10*(step++));
    tb->clk90 = 1;
    tb->eval();
    tfp->dump(10*(step++));
    printf("clk=%d hbus_dq=%02X\n", tb->clk, tb->hbus_dq);

    tfp->flush();
  }

  tfp->close();

}
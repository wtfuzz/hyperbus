#include <stdlib.h>
#include "Vhyperbus_fifo_test_top.h"
#include "verilated.h"
#include "verilated_vcd_c.h"


#define STEPS 256

int main(int argc, char **argv) {
  // Initialize Verilators variables
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);

  VerilatedVcdC *tfp = new VerilatedVcdC;
  Vhyperbus_fifo_test_top *tb = new Vhyperbus_fifo_test_top;

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

  while(step <= STEPS)
  {
    tb->wrq = 1;
    tb->clk = 1;
    tb->eval();
    tfp->dump(10*(step++));
    tb->clk90 = 0;
    tb->eval();
    tfp->dump(10*(step++));
    tfp->flush();

    tb->clk = 0;
    tb->eval();
    tfp->dump(10*(step++));
    tb->clk90 = 1;
    tb->eval();
    tfp->dump(10*(step++));

    tfp->flush();
  }

  tfp->close();

}
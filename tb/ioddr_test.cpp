#include <stdlib.h>
#include "Vioddr_test_top.h"

#define STEPS 16

int main(int argc, char **argv) {
  // Initialize Verilators variables
  Verilated::commandArgs(argc, argv);

  Vioddr_test_top *tb = new Vioddr_test_top;

  // Write 16 bit SDR data, expect 8 bit DDR output on DQ
  tb->oe = 1;
  tb->dataw = 0xdead;
  tb->clk = 0;
  tb->eval();

  for(int step=0;step<STEPS;step++)
  {
    tb->dataw = 0xdead + step;
    tb->clk = 1;
    tb->eval();
    printf("clk=%d dq=%02X\n", tb->clk, tb->dq);

    tb->clk = 0;
    tb->eval();
    printf("clk=%d dq=%02X\n", tb->clk, tb->dq);
  }

  // Write 8 bit DQ at DDR, expecting 16 bits recovered on a single edge
  tb->oe = 0;
  tb->clk = 0;
  tb->eval();
  for(int step=0;step<STEPS;step++)
  {
    tb->dq = 0xd0+step;
    tb->clk = 1;
    tb->eval();
    tfp->dump(10*step);
    //printf("clk=%d datar=%04X\n", tb->clk, tb->datar);


    tb->dq = 0x0d+step;
    tb->clk = 0;
    tb->eval();
    tfp->dump(10*step);
    printf("clk=%d datar=%04X\n", tb->clk, tb->datar);

    tfp->flush();
  }

  tfp->close();
}
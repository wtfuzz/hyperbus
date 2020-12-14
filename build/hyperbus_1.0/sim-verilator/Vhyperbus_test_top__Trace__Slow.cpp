// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vhyperbus_test_top__Syms.h"


//======================

void Vhyperbus_test_top::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vhyperbus_test_top::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vhyperbus_test_top__Syms* __restrict vlSymsp = static_cast<Vhyperbus_test_top__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vhyperbus_test_top::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vhyperbus_test_top::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vhyperbus_test_top__Syms* __restrict vlSymsp = static_cast<Vhyperbus_test_top__Syms*>(userp);
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vhyperbus_test_top::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vhyperbus_test_top__Syms* __restrict vlSymsp = static_cast<Vhyperbus_test_top__Syms*>(userp);
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+9,"clk", false,-1);
        tracep->declBit(c+10,"clk90", false,-1);
        tracep->declBit(c+11,"rst", false,-1);
        tracep->declBit(c+12,"hbus_clk", false,-1);
        tracep->declBit(c+13,"hbus_csn", false,-1);
        tracep->declBit(c+14,"hbus_rstn", false,-1);
        tracep->declBus(c+15,"hbus_dq", false,-1, 7,0);
        tracep->declBit(c+16,"hbus_rwds", false,-1);
        tracep->declBus(c+17,"addr", false,-1, 31,0);
        tracep->declBus(c+18,"datar", false,-1, 15,0);
        tracep->declBus(c+19,"dataw", false,-1, 15,0);
        tracep->declBit(c+20,"wrq", false,-1);
        tracep->declBit(c+21,"rrq", false,-1);
        tracep->declBit(c+22,"busy", false,-1);
        tracep->declBit(c+9,"hyperbus_test_top clk", false,-1);
        tracep->declBit(c+10,"hyperbus_test_top clk90", false,-1);
        tracep->declBit(c+11,"hyperbus_test_top rst", false,-1);
        tracep->declBit(c+12,"hyperbus_test_top hbus_clk", false,-1);
        tracep->declBit(c+13,"hyperbus_test_top hbus_csn", false,-1);
        tracep->declBit(c+14,"hyperbus_test_top hbus_rstn", false,-1);
        tracep->declBus(c+15,"hyperbus_test_top hbus_dq", false,-1, 7,0);
        tracep->declBit(c+16,"hyperbus_test_top hbus_rwds", false,-1);
        tracep->declBus(c+17,"hyperbus_test_top addr", false,-1, 31,0);
        tracep->declBus(c+18,"hyperbus_test_top datar", false,-1, 15,0);
        tracep->declBus(c+19,"hyperbus_test_top dataw", false,-1, 15,0);
        tracep->declBit(c+20,"hyperbus_test_top wrq", false,-1);
        tracep->declBit(c+21,"hyperbus_test_top rrq", false,-1);
        tracep->declBit(c+22,"hyperbus_test_top busy", false,-1);
        tracep->declBus(c+28,"hyperbus_test_top hbus0 TARGET", false,-1, 23,0);
        tracep->declBus(c+29,"hyperbus_test_top hbus0 WIDTH", false,-1, 31,0);
        tracep->declBus(c+30,"hyperbus_test_top hbus0 TACC_COUNT", false,-1, 31,0);
        tracep->declBit(c+9,"hyperbus_test_top hbus0 clk", false,-1);
        tracep->declBit(c+10,"hyperbus_test_top hbus0 clk90", false,-1);
        tracep->declBit(c+11,"hyperbus_test_top hbus0 rst", false,-1);
        tracep->declBus(c+17,"hyperbus_test_top hbus0 addr", false,-1, 31,0);
        tracep->declBus(c+18,"hyperbus_test_top hbus0 din", false,-1, 15,0);
        tracep->declBus(c+19,"hyperbus_test_top hbus0 dout", false,-1, 15,0);
        tracep->declBit(c+31,"hyperbus_test_top hbus0 dready", false,-1);
        tracep->declBit(c+32,"hyperbus_test_top hbus0 dvalid", false,-1);
        tracep->declBit(c+22,"hyperbus_test_top hbus0 busy", false,-1);
        tracep->declBit(c+20,"hyperbus_test_top hbus0 wrq", false,-1);
        tracep->declBit(c+21,"hyperbus_test_top hbus0 rrq", false,-1);
        tracep->declBit(c+12,"hyperbus_test_top hbus0 hbus_clk", false,-1);
        tracep->declBit(c+14,"hyperbus_test_top hbus0 hbus_rstn", false,-1);
        tracep->declBit(c+13,"hyperbus_test_top hbus0 hbus_csn", false,-1);
        tracep->declBus(c+15,"hyperbus_test_top hbus0 hbus_dq", false,-1, 7,0);
        tracep->declBit(c+16,"hyperbus_test_top hbus0 hbus_rwds", false,-1);
        tracep->declBus(c+33,"hyperbus_test_top hbus0 COUNTER_WIDTH", false,-1, 31,0);
        tracep->declBus(c+34,"hyperbus_test_top hbus0 STATE_IDLE", false,-1, 5,0);
        tracep->declBus(c+35,"hyperbus_test_top hbus0 STATE_COMMAND", false,-1, 5,0);
        tracep->declBus(c+36,"hyperbus_test_top hbus0 STATE_LATENCY", false,-1, 5,0);
        tracep->declBus(c+37,"hyperbus_test_top hbus0 STATE_READ", false,-1, 5,0);
        tracep->declBus(c+38,"hyperbus_test_top hbus0 STATE_WRITE", false,-1, 5,0);
        tracep->declBus(c+39,"hyperbus_test_top hbus0 STATE_ERROR", false,-1, 5,0);
        tracep->declBus(c+1,"hyperbus_test_top hbus0 state", false,-1, 5,0);
        tracep->declBus(c+2,"hyperbus_test_top hbus0 dataw", false,-1, 15,0);
        tracep->declBus(c+23,"hyperbus_test_top hbus0 datar", false,-1, 15,0);
        tracep->declBus(c+24,"hyperbus_test_top hbus0 rwdsr", false,-1, 1,0);
        tracep->declBus(c+40,"hyperbus_test_top hbus0 rwdsw", false,-1, 1,0);
        tracep->declBit(c+3,"hyperbus_test_top hbus0 data_oe", false,-1);
        tracep->declBit(c+25,"hyperbus_test_top hbus0 rwds_oe", false,-1);
        tracep->declBit(c+4,"hyperbus_test_top hbus0 clk_oe", false,-1);
        tracep->declQuad(c+5,"hyperbus_test_top hbus0 ca", false,-1, 47,0);
        tracep->declBit(c+7,"hyperbus_test_top hbus0 timeout_error", false,-1);
        tracep->declBus(c+8,"hyperbus_test_top hbus0 count", false,-1, 3,0);
        tracep->declBus(c+28,"hyperbus_test_top hbus0 ddr_data TARGET", false,-1, 23,0);
        tracep->declBus(c+29,"hyperbus_test_top hbus0 ddr_data WIDTH", false,-1, 31,0);
        tracep->declBit(c+9,"hyperbus_test_top hbus0 ddr_data clk", false,-1);
        tracep->declBit(c+3,"hyperbus_test_top hbus0 ddr_data oe", false,-1);
        tracep->declBus(c+2,"hyperbus_test_top hbus0 ddr_data dataw", false,-1, 15,0);
        tracep->declBus(c+23,"hyperbus_test_top hbus0 ddr_data datar", false,-1, 15,0);
        tracep->declBus(c+15,"hyperbus_test_top hbus0 ddr_data dq", false,-1, 7,0);
        tracep->declBus(c+23,"hyperbus_test_top hbus0 ddr_data genblk1 d", false,-1, 15,0);
        tracep->declBus(c+26,"hyperbus_test_top hbus0 ddr_data genblk1 q", false,-1, 7,0);
        tracep->declBus(c+28,"hyperbus_test_top hbus0 ddr_rwds TARGET", false,-1, 23,0);
        tracep->declBus(c+41,"hyperbus_test_top hbus0 ddr_rwds WIDTH", false,-1, 31,0);
        tracep->declBit(c+9,"hyperbus_test_top hbus0 ddr_rwds clk", false,-1);
        tracep->declBit(c+25,"hyperbus_test_top hbus0 ddr_rwds oe", false,-1);
        tracep->declBus(c+40,"hyperbus_test_top hbus0 ddr_rwds dataw", false,-1, 1,0);
        tracep->declBus(c+24,"hyperbus_test_top hbus0 ddr_rwds datar", false,-1, 1,0);
        tracep->declBus(c+16,"hyperbus_test_top hbus0 ddr_rwds dq", false,-1, 0,0);
        tracep->declBus(c+24,"hyperbus_test_top hbus0 ddr_rwds genblk1 d", false,-1, 1,0);
        tracep->declBus(c+27,"hyperbus_test_top hbus0 ddr_rwds genblk1 q", false,-1, 0,0);
    }
}

void Vhyperbus_test_top::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vhyperbus_test_top::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vhyperbus_test_top__Syms* __restrict vlSymsp = static_cast<Vhyperbus_test_top__Syms*>(userp);
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vhyperbus_test_top::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vhyperbus_test_top__Syms* __restrict vlSymsp = static_cast<Vhyperbus_test_top__Syms*>(userp);
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullCData(oldp+1,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state),6);
        tracep->fullSData(oldp+2,((0xffffU & (IData)(
                                                     (vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                                      >> 0x20U)))),16);
        tracep->fullBit(oldp+3,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe));
        tracep->fullBit(oldp+4,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__clk_oe));
        tracep->fullQData(oldp+5,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca),48);
        tracep->fullBit(oldp+7,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__timeout_error));
        tracep->fullCData(oldp+8,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count),4);
        tracep->fullBit(oldp+9,(vlTOPp->clk));
        tracep->fullBit(oldp+10,(vlTOPp->clk90));
        tracep->fullBit(oldp+11,(vlTOPp->rst));
        tracep->fullBit(oldp+12,(vlTOPp->hbus_clk));
        tracep->fullBit(oldp+13,(vlTOPp->hbus_csn));
        tracep->fullBit(oldp+14,(vlTOPp->hbus_rstn));
        tracep->fullCData(oldp+15,(vlTOPp->hbus_dq),8);
        tracep->fullBit(oldp+16,(vlTOPp->hbus_rwds));
        tracep->fullIData(oldp+17,(vlTOPp->addr),32);
        tracep->fullSData(oldp+18,(vlTOPp->datar),16);
        tracep->fullSData(oldp+19,(vlTOPp->dataw),16);
        tracep->fullBit(oldp+20,(vlTOPp->wrq));
        tracep->fullBit(oldp+21,(vlTOPp->rrq));
        tracep->fullBit(oldp+22,(vlTOPp->busy));
        tracep->fullSData(oldp+23,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d),16);
        tracep->fullCData(oldp+24,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d),2);
        tracep->fullBit(oldp+25,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe));
        tracep->fullCData(oldp+26,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__q),8);
        tracep->fullBit(oldp+27,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__q));
        tracep->fullIData(oldp+28,(0x53494dU),24);
        tracep->fullIData(oldp+29,(8U),32);
        tracep->fullIData(oldp+30,(7U),32);
        tracep->fullBit(oldp+31,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__dready));
        tracep->fullBit(oldp+32,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__dvalid));
        tracep->fullIData(oldp+33,(4U),32);
        tracep->fullCData(oldp+34,(1U),6);
        tracep->fullCData(oldp+35,(2U),6);
        tracep->fullCData(oldp+36,(4U),6);
        tracep->fullCData(oldp+37,(8U),6);
        tracep->fullCData(oldp+38,(0x10U),6);
        tracep->fullCData(oldp+39,(0x20U),6);
        tracep->fullCData(oldp+40,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwdsw),2);
        tracep->fullIData(oldp+41,(1U),32);
    }
}

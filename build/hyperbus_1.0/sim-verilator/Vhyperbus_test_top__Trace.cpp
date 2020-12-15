// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vhyperbus_test_top__Syms.h"


void Vhyperbus_test_top::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vhyperbus_test_top__Syms* __restrict vlSymsp = static_cast<Vhyperbus_test_top__Syms*>(userp);
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vhyperbus_test_top::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vhyperbus_test_top__Syms* __restrict vlSymsp = static_cast<Vhyperbus_test_top__Syms*>(userp);
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[1U])) {
            tracep->chgBit(oldp+0,((0x40U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))));
            tracep->chgCData(oldp+1,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state),7);
            tracep->chgSData(oldp+2,((0xffffU & (IData)(
                                                        (vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                                         >> 0x20U)))),16);
            tracep->chgBit(oldp+3,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe));
            tracep->chgBit(oldp+4,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__clk_oe));
            tracep->chgQData(oldp+5,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca),48);
            tracep->chgBit(oldp+7,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__timeout_error));
            tracep->chgCData(oldp+8,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count),4);
        }
        tracep->chgBit(oldp+9,(vlTOPp->clk));
        tracep->chgBit(oldp+10,(vlTOPp->clk90));
        tracep->chgBit(oldp+11,(vlTOPp->rst));
        tracep->chgBit(oldp+12,(vlTOPp->hbus_clk));
        tracep->chgBit(oldp+13,(vlTOPp->hbus_csn));
        tracep->chgBit(oldp+14,(vlTOPp->hbus_rstn));
        tracep->chgCData(oldp+15,(vlTOPp->hbus_dq),8);
        tracep->chgBit(oldp+16,(vlTOPp->hbus_rwds));
        tracep->chgIData(oldp+17,(vlTOPp->addr),32);
        tracep->chgSData(oldp+18,(vlTOPp->datar),16);
        tracep->chgSData(oldp+19,(vlTOPp->dataw),16);
        tracep->chgBit(oldp+20,(vlTOPp->wrq));
        tracep->chgBit(oldp+21,(vlTOPp->rrq));
        tracep->chgBit(oldp+22,(vlTOPp->busy));
        tracep->chgSData(oldp+23,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d),16);
        tracep->chgCData(oldp+24,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d),2);
        tracep->chgBit(oldp+25,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe));
        tracep->chgCData(oldp+26,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__q),8);
        tracep->chgBit(oldp+27,(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__q));
    }
}

void Vhyperbus_test_top::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vhyperbus_test_top__Syms* __restrict vlSymsp = static_cast<Vhyperbus_test_top__Syms*>(userp);
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
        vlTOPp->__Vm_traceActivity[1U] = 0U;
    }
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vhyperbus_test_top.h for the primary calling header

#include "Vhyperbus_test_top.h"
#include "Vhyperbus_test_top__Syms.h"

//==========

VL_CTOR_IMP(Vhyperbus_test_top) {
    Vhyperbus_test_top__Syms* __restrict vlSymsp = __VlSymsp = new Vhyperbus_test_top__Syms(this, name());
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vhyperbus_test_top::__Vconfigure(Vhyperbus_test_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vhyperbus_test_top::~Vhyperbus_test_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = nullptr);
}

void Vhyperbus_test_top::_initial__TOP__8(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_initial__TOP__8\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe = 1U;
}

void Vhyperbus_test_top::_settle__TOP__9(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_settle__TOP__9\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->dataw = vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d;
    vlTOPp->hbus_clk = ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__clk_oe90) 
                        & (IData)(vlTOPp->clk90));
    vlTOPp->hbus_rstn = (2U != (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state));
    vlTOPp->hbus_csn = ((((1U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)) 
                          | (0x40U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) 
                         | (2U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) 
                        | (0U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)));
    vlTOPp->busy = (1U != (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state));
    vlTOPp->hbus_rwds = ((((((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe) 
                             & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__q)) 
                            & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe)) 
                           & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe)) 
                          & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe)) 
                         & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe));
    vlTOPp->hbus_dq = ((((((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe)
                            ? (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__q)
                            : 0U) & ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe)
                                      ? 0xffU : 0U)) 
                         & ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe)
                             ? 0xffU : 0U)) & ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe)
                                                ? 0xffU
                                                : 0U)) 
                       & ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe)
                           ? 0xffU : 0U));
}

void Vhyperbus_test_top::_eval_initial(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_eval_initial\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__clk90 = vlTOPp->clk90;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__hbus_rwds 
        = vlTOPp->__VinpClk__TOP__hbus_rwds;
    vlTOPp->_initial__TOP__8(vlSymsp);
    vlTOPp->__Vm_traceActivity[1U] = 1U;
    vlTOPp->__Vm_traceActivity[0U] = 1U;
}

void Vhyperbus_test_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::final\n"); );
    // Variables
    Vhyperbus_test_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vhyperbus_test_top::_eval_settle(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_eval_settle\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__9(vlSymsp);
}

void Vhyperbus_test_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    clk90 = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    hbus_clk = VL_RAND_RESET_I(1);
    hbus_csn = VL_RAND_RESET_I(1);
    hbus_rstn = VL_RAND_RESET_I(1);
    hbus_dq = VL_RAND_RESET_I(8);
    hbus_rwds = VL_RAND_RESET_I(1);
    addr = VL_RAND_RESET_I(32);
    datar = VL_RAND_RESET_I(16);
    dataw = VL_RAND_RESET_I(16);
    wrq = VL_RAND_RESET_I(1);
    rrq = VL_RAND_RESET_I(1);
    busy = VL_RAND_RESET_I(1);
    hyperbus_test_top__DOT__hbus0__DOT__dready = VL_RAND_RESET_I(1);
    hyperbus_test_top__DOT__hbus0__DOT__dvalid = VL_RAND_RESET_I(1);
    hyperbus_test_top__DOT__hbus0__DOT__state = VL_RAND_RESET_I(7);
    hyperbus_test_top__DOT__hbus0__DOT__rwdsw = VL_RAND_RESET_I(2);
    hyperbus_test_top__DOT__hbus0__DOT__data_oe = VL_RAND_RESET_I(1);
    hyperbus_test_top__DOT__hbus0__DOT__rwds_oe = VL_RAND_RESET_I(1);
    hyperbus_test_top__DOT__hbus0__DOT__clk_oe = VL_RAND_RESET_I(1);
    hyperbus_test_top__DOT__hbus0__DOT__clk_oe90 = VL_RAND_RESET_I(1);
    hyperbus_test_top__DOT__hbus0__DOT__ca = VL_RAND_RESET_Q(48);
    hyperbus_test_top__DOT__hbus0__DOT__timeout_error = VL_RAND_RESET_I(1);
    hyperbus_test_top__DOT__hbus0__DOT__count = VL_RAND_RESET_I(4);
    hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d = VL_RAND_RESET_I(16);
    hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__q = VL_RAND_RESET_I(8);
    hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d = VL_RAND_RESET_I(2);
    hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__q = VL_RAND_RESET_I(1);
    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = VL_RAND_RESET_I(7);
    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count = VL_RAND_RESET_I(4);
    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__rwds_oe = VL_RAND_RESET_I(1);
    __VinpClk__TOP__hbus_rwds = VL_RAND_RESET_I(1);
    __Vchglast__TOP__hbus_rwds = VL_RAND_RESET_I(1);
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }
}

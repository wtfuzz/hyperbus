// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vhyperbus_test_top.h for the primary calling header

#include "Vhyperbus_test_top.h"
#include "Vhyperbus_test_top__Syms.h"

//==========

void Vhyperbus_test_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vhyperbus_test_top::eval\n"); );
    Vhyperbus_test_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("../src/hyperbus_1.0/tb/hyperbus_tb.v", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vhyperbus_test_top::_eval_initial_loop(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("../src/hyperbus_1.0/tb/hyperbus_tb.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vhyperbus_test_top::_combo__TOP__1(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_combo__TOP__1\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->hbus_rstn = (1U & (~ (IData)(vlTOPp->rst)));
}

VL_INLINE_OPT void Vhyperbus_test_top::_sequent__TOP__4(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_sequent__TOP__4\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*5:0*/ __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state;
    CData/*3:0*/ __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count;
    // Body
    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count 
        = vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count;
    vlTOPp->__Vdly__hyperbus_test_top__DOT__hbus0__DOT__rwds_oe 
        = vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe;
    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state 
        = vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state;
    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__q 
        = (1U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwdsw));
    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__q 
        = (0xffU & (IData)((vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                            >> 0x20U)));
    if ((1U & (~ (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe)))) {
        vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d 
            = ((0xffU & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d)) 
               | ((IData)(vlTOPp->hbus_dq) << 8U));
    }
    if (vlTOPp->rst) {
        __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
        vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__timeout_error = 0U;
        vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__clk_oe = 0U;
        __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count = 0U;
    } else {
        if ((0x20U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
            if (VL_UNLIKELY((0x10U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                VL_WRITEF("UNHANDLED STATE\n");
                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
            } else {
                if (VL_UNLIKELY((8U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                    VL_WRITEF("UNHANDLED STATE\n");
                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                } else {
                    if (VL_UNLIKELY((4U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                        VL_WRITEF("UNHANDLED STATE\n");
                        __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                    } else {
                        if (VL_UNLIKELY((2U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                            VL_WRITEF("UNHANDLED STATE\n");
                            __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                        } else {
                            if ((1U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                                VL_WRITEF("UNHANDLED STATE\n");
                                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                            } else {
                                VL_WRITEF("Error state\n");
                                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 0x20U;
                            }
                        }
                    }
                }
            }
        } else {
            if ((0x10U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                if (VL_UNLIKELY((8U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                    VL_WRITEF("UNHANDLED STATE\n");
                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                } else {
                    if (VL_UNLIKELY((4U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                        VL_WRITEF("UNHANDLED STATE\n");
                        __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                    } else {
                        if (VL_UNLIKELY((2U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                            VL_WRITEF("UNHANDLED STATE\n");
                            __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                        } else {
                            if ((1U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                                VL_WRITEF("UNHANDLED STATE\n");
                                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                            } else {
                                VL_WRITEF("Write state\n");
                                vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe = 1U;
                            }
                        }
                    }
                }
            } else {
                if ((8U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                    if (VL_UNLIKELY((4U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                        VL_WRITEF("UNHANDLED STATE\n");
                        __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                    } else {
                        if (VL_UNLIKELY((2U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                            VL_WRITEF("UNHANDLED STATE\n");
                            __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                        } else {
                            if ((1U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                                VL_WRITEF("UNHANDLED STATE\n");
                                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                            } else {
                                VL_WRITEF("Read state\n");
                                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count 
                                    = (0xfU & ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count) 
                                               - (IData)(1U)));
                                vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe = 0U;
                                vlTOPp->__Vdly__hyperbus_test_top__DOT__hbus0__DOT__rwds_oe = 0U;
                                if ((0U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count))) {
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__timeout_error = 1U;
                                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 0x20U;
                                }
                                if ((0U != (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d))) {
                                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                                }
                            }
                        }
                    }
                } else {
                    if ((4U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                        if (VL_UNLIKELY((2U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)))) {
                            VL_WRITEF("UNHANDLED STATE\n");
                            __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                        } else {
                            if ((1U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                                VL_WRITEF("UNHANDLED STATE\n");
                                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                            } else {
                                VL_WRITEF("Latency state\n");
                                vlTOPp->__Vdly__hyperbus_test_top__DOT__hbus0__DOT__rwds_oe = 0U;
                                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count 
                                    = (0xfU & ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count) 
                                               - (IData)(1U)));
                                if ((0U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count))) {
                                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state 
                                        = ((IData)(vlTOPp->rrq)
                                            ? 8U : 0x10U);
                                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count = 0xfU;
                                }
                            }
                        }
                    } else {
                        if ((2U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                            if ((1U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                                VL_WRITEF("UNHANDLED STATE\n");
                                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                            } else {
                                VL_WRITEF("Send command\n");
                                vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe = 1U;
                                if (VL_UNLIKELY((0U 
                                                 == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count)))) {
                                    VL_WRITEF("Command sent\n");
                                    if ((3U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d))) {
                                        VL_WRITEF("2x latency\n");
                                        __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count = 0xdU;
                                    } else {
                                        VL_WRITEF("1x latency\n");
                                        __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count = 6U;
                                    }
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe = 0U;
                                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 4U;
                                } else {
                                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count 
                                        = (0xfU & ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count) 
                                                   - (IData)(1U)));
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                        = (0xffffffffffffULL 
                                           & (vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                              << 0x10U));
                                }
                            }
                        } else {
                            if ((1U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state))) {
                                VL_WRITEF("Idle\n");
                                if (((IData)(vlTOPp->rrq) 
                                     | (IData)(vlTOPp->wrq))) {
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                        = ((0x7fffffffffffULL 
                                            & vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca) 
                                           | ((QData)((IData)(vlTOPp->rrq)) 
                                              << 0x2fU));
                                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 2U;
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                        = (0xbfffffffffffULL 
                                           & vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca);
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe = 1U;
                                    vlTOPp->__Vdly__hyperbus_test_top__DOT__hbus0__DOT__rwds_oe = 0U;
                                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count = 3U;
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__clk_oe = 1U;
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                        = (0xdfffffffffffULL 
                                           & vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca);
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                        = ((0xe0000000ffffULL 
                                            & vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca) 
                                           | ((QData)((IData)(
                                                              (0x1fffffffU 
                                                               & (vlTOPp->addr 
                                                                  >> 3U)))) 
                                              << 0x10U));
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                        = (0xffffffff0007ULL 
                                           & vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca);
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                        = ((0xfffffffffff8ULL 
                                            & vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca) 
                                           | (IData)((IData)(
                                                             (7U 
                                                              & vlTOPp->addr))));
                                } else {
                                    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__clk_oe = 0U;
                                    __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                                }
                            } else {
                                VL_WRITEF("UNHANDLED STATE\n");
                                __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__count 
        = __Vdly__hyperbus_test_top__DOT__hbus0__DOT__count;
    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state 
        = __Vdly__hyperbus_test_top__DOT__hbus0__DOT__state;
    vlTOPp->hbus_csn = ((1U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)) 
                        | (0x20U == (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state)));
    vlTOPp->busy = (1U != (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__state));
}

VL_INLINE_OPT void Vhyperbus_test_top::_sequent__TOP__5(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_sequent__TOP__5\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe) {
        vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__q 
            = (1U & ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwdsw) 
                     >> 1U));
    }
    if (vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe) {
        vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__q 
            = (0xffU & (IData)((vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ca 
                                >> 0x28U)));
    }
    if ((1U & (~ (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__data_oe)))) {
        vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d 
            = ((0xff00U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d)) 
               | (IData)(vlTOPp->hbus_dq));
    }
}

VL_INLINE_OPT void Vhyperbus_test_top::_sequent__TOP__6(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_sequent__TOP__6\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
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
    vlTOPp->dataw = vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d;
}

VL_INLINE_OPT void Vhyperbus_test_top::_combo__TOP__7(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_combo__TOP__7\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->hbus_clk = ((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__clk_oe) 
                        & (IData)(vlTOPp->clk90));
}

VL_INLINE_OPT void Vhyperbus_test_top::_sequent__TOP__8(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_sequent__TOP__8\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((1U & (~ (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe)))) {
        vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d 
            = ((1U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d)) 
               | ((IData)(vlTOPp->hbus_rwds) << 1U));
    }
    vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe 
        = vlTOPp->__Vdly__hyperbus_test_top__DOT__hbus0__DOT__rwds_oe;
}

VL_INLINE_OPT void Vhyperbus_test_top::_sequent__TOP__9(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_sequent__TOP__9\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((1U & (~ (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe)))) {
        vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d 
            = ((2U & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d)) 
               | (IData)(vlTOPp->hbus_rwds));
    }
}

VL_INLINE_OPT void Vhyperbus_test_top::_sequent__TOP__10(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_sequent__TOP__10\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->hbus_rwds = ((((((IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe) 
                             & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__q)) 
                            & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe)) 
                           & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe)) 
                          & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe)) 
                         & (IData)(vlTOPp->hyperbus_test_top__DOT__hbus0__DOT__rwds_oe));
}

void Vhyperbus_test_top::_eval(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_eval\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
        vlTOPp->__Vm_traceActivity[1U] = 1U;
    }
    if (((~ (IData)(vlTOPp->clk)) & (IData)(vlTOPp->__Vclklast__TOP__clk))) {
        vlTOPp->_sequent__TOP__5(vlSymsp);
    }
    if (((IData)(vlTOPp->clk) ^ (IData)(vlTOPp->__Vclklast__TOP__clk))) {
        vlTOPp->_sequent__TOP__6(vlSymsp);
    }
    vlTOPp->_combo__TOP__7(vlSymsp);
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__8(vlSymsp);
    }
    if (((~ (IData)(vlTOPp->clk)) & (IData)(vlTOPp->__Vclklast__TOP__clk))) {
        vlTOPp->_sequent__TOP__9(vlSymsp);
    }
    if (((IData)(vlTOPp->clk) ^ (IData)(vlTOPp->__Vclklast__TOP__clk))) {
        vlTOPp->_sequent__TOP__10(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

VL_INLINE_OPT QData Vhyperbus_test_top::_change_request(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_change_request\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vhyperbus_test_top::_change_request_1(Vhyperbus_test_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_change_request_1\n"); );
    Vhyperbus_test_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vhyperbus_test_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhyperbus_test_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((clk90 & 0xfeU))) {
        Verilated::overWidthError("clk90");}
    if (VL_UNLIKELY((rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((hbus_rwds & 0xfeU))) {
        Verilated::overWidthError("hbus_rwds");}
    if (VL_UNLIKELY((wrq & 0xfeU))) {
        Verilated::overWidthError("wrq");}
    if (VL_UNLIKELY((rrq & 0xfeU))) {
        Verilated::overWidthError("rrq");}
}
#endif  // VL_DEBUG

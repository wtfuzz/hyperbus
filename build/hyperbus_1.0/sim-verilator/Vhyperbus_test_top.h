// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VHYPERBUS_TEST_TOP_H_
#define _VHYPERBUS_TEST_TOP_H_  // guard

#include "verilated_heavy.h"

//==========

class Vhyperbus_test_top__Syms;
class Vhyperbus_test_top_VerilatedVcd;


//----------

VL_MODULE(Vhyperbus_test_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(clk90,0,0);
    VL_IN8(rst,0,0);
    VL_OUT8(hbus_clk,0,0);
    VL_OUT8(hbus_csn,0,0);
    VL_OUT8(hbus_rstn,0,0);
    VL_INOUT8(hbus_dq,7,0);
    VL_INOUT8(hbus_rwds,0,0);
    VL_IN8(wrq,0,0);
    VL_IN8(rrq,0,0);
    VL_OUT8(busy,0,0);
    VL_IN16(datar,15,0);
    VL_OUT16(dataw,15,0);
    VL_IN(addr,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*0:0*/ hyperbus_test_top__DOT__hbus0__DOT__dready;
    CData/*0:0*/ hyperbus_test_top__DOT__hbus0__DOT__dvalid;
    CData/*5:0*/ hyperbus_test_top__DOT__hbus0__DOT__state;
    CData/*1:0*/ hyperbus_test_top__DOT__hbus0__DOT__rwdsw;
    CData/*0:0*/ hyperbus_test_top__DOT__hbus0__DOT__data_oe;
    CData/*0:0*/ hyperbus_test_top__DOT__hbus0__DOT__rwds_oe;
    CData/*0:0*/ hyperbus_test_top__DOT__hbus0__DOT__clk_oe;
    CData/*0:0*/ hyperbus_test_top__DOT__hbus0__DOT__timeout_error;
    CData/*3:0*/ hyperbus_test_top__DOT__hbus0__DOT__count;
    CData/*7:0*/ hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__q;
    CData/*1:0*/ hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__d;
    CData/*0:0*/ hyperbus_test_top__DOT__hbus0__DOT__ddr_rwds__DOT__genblk1__DOT__q;
    SData/*15:0*/ hyperbus_test_top__DOT__hbus0__DOT__ddr_data__DOT__genblk1__DOT__d;
    QData/*47:0*/ hyperbus_test_top__DOT__hbus0__DOT__ca;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vdly__hyperbus_test_top__DOT__hbus0__DOT__rwds_oe;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vm_traceActivity[2];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vhyperbus_test_top__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vhyperbus_test_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vhyperbus_test_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vhyperbus_test_top();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
    static void _eval_initial_loop(Vhyperbus_test_top__Syms* __restrict vlSymsp);
    void __Vconfigure(Vhyperbus_test_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vhyperbus_test_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vhyperbus_test_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__7(Vhyperbus_test_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vhyperbus_test_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vhyperbus_test_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vhyperbus_test_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vhyperbus_test_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__10(Vhyperbus_test_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__3(Vhyperbus_test_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__4(Vhyperbus_test_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__6(Vhyperbus_test_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__8(Vhyperbus_test_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__9(Vhyperbus_test_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__5(Vhyperbus_test_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
  private:
    static void traceChgSub0(void* userp, VerilatedVcd* tracep);
    static void traceChgTop0(void* userp, VerilatedVcd* tracep);
    static void traceCleanup(void* userp, VerilatedVcd* /*unused*/);
    static void traceFullSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceFullTop0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitTop(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    void traceRegister(VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard

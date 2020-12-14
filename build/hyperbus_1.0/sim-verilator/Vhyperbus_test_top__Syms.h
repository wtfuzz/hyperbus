// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VHYPERBUS_TEST_TOP__SYMS_H_
#define _VHYPERBUS_TEST_TOP__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vhyperbus_test_top.h"

// SYMS CLASS
class Vhyperbus_test_top__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_activity;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode;  ///< Used by trace routines when tracing multiple models
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vhyperbus_test_top*            TOPp;
    
    // CREATORS
    Vhyperbus_test_top__Syms(Vhyperbus_test_top* topp, const char* namep);
    ~Vhyperbus_test_top__Syms() = default;
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard

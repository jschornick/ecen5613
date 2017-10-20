// File       : debug.h
// Author     : Jeff Schornick
//
// A virtual debug port macros.
//
// These macros can be used to efficiently send an address/byte combination to a
// range of XRAM addresses reserved for debugging. An external write signal will
// be produced for such an address, with the debug value on the data bus.
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdint.h>

// Unused XRAM addresses that can be read via logic analyzer to
// read debug values
#define DEBUG_ADDR       0xFFFF
#define DEBUG_ERROR_ADDR 0xFFFE
#define DEBUG_WARN_ADDR  0xFFFD
#define DEBUG_INFO_ADDR  0xFFFC

#define DEBUGPORT(x) DP_X(DEBUG_ADDR,x)
#define DP_ERROR(x)  DP_X(DEBUG_ERROR_ADDR,x)
#define DP_WARN(x)   DP_X(DEBUG_WARN_ADDR,x)
#define DP_INFO(x)   DP_X(DEBUG_INFO_ADDR,x)

#ifdef DEBUG
#define DP_X(addr,x) ( *((__xdata uint8_t *) addr) = x)
#else
#define DP_X(addr,x)  /* NOP */
#endif /* DEBUG */

#endif /* __DEBUG_H */

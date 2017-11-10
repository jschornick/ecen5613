// File       : delay.h
// Author     : Jeff Schornick
//
// Delay routines for 8051
//
// 11.0592MHz / 12 osc/cycle = 921600 cycles/second = 1.0850694 us/cycle
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#ifndef __DELAY_H
#define __DELAY_H

#pragma sdcc_hash +  /* allow # in macro defintion */

// Single cycle no-operation macro
#define nop()   \
  __asm         \
    nop         \
  __endasm;

// Five nops: 5 * 1.085 us = 5.425us
#define delay_5_5us() nop(); nop(); nop(); nop(); nop(); nop();

// Delay approximately 100us
//   921600 (cycles/s) / 1000000 (us/s) * 100 us = 92.16 cycles per 100us
//   45 * djnz + 1 mov + 1 nop = 45*2 + 1*1 + 1*1 = 92 cycles
//   92 cyclese = 99.826us
#define delay_100us()                           \
  __asm                                         \
  mov r0,#45                                    \
    0001$:                                      \
    djnz r0,0001$                               \
    nop                                         \
    __endasm ;

// Dealy approximate 250us, 1/4 ms
//   250 * 0.9216 = 230.4 cycles
//   114*2 + 2 = 230 cycles
//   230 cycles = 249.566us
#define delay_250us()                           \
  __asm                                         \
  mov r0,#114                                   \
    0001$:                                      \
    djnz r0,0001$                               \
    nop                                         \
    __endasm ;

// Delay for ms milliseconds
// Maximum of 63 ms
void delay_ms(uint8_t ms);

// re-enable normal macro processing of # symbol
#pragma sdcc_hash -

#endif /* __DELAY_H */

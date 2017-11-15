// File       : serial.c
// Author     : Jeff Schornick
//
// Timer initialization
//
// Assumes F_CLK = 11.0592 MHz, for an instruction cycle of 12/F_CLK seconds
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include "timer.h"

// 0.050 / (12/11.0592 MHz)
#define TICKS_PER_50MS 46080U
#define T2_RELOAD (0x0 - TICKS_PER_50MS) /* T2 counts up, overflows from 0xffff-0x0 */

// timer 2, 16-bit autoreload up-down
void timer2_init()
{
  T2MOD = 0;  // No output, count using standard 80C52 behavior

  T2CON_CP = 0; // auto-reload
  T2CON_C = 0;  // timer mode
  T2CON_RCLK = 0; // not acting as RX clock
  T2CON_TCLK = 0; // not acting as TX clock

  // configure 16-bit reload value (50ms)
  RCAP2H = (T2_RELOAD >> 8);   // upper 8-bits
  RCAP2L = (T2_RELOAD & 0xFF); // lower 8-bits

  TH2 = RCAP2H;
  TL2 = RCAP2L;

  T2CON_TF2 = 0; // clear overflow flag

  ET2 = 1; // enable T2 interrupt
  EA = 1; // enable interrupts

  // run timer
  T2CON_TR2 = 1;
}



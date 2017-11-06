// File       : delay.c
// Author     : Jeff Schornick
//
// Delay routines for 8051
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdint.h>
#include "delay.h"

void delay_ms(uint8_t ms)
{
  uint8_t i = ms<<2;  // 250us * 4 = 1 ms
  while (i>0) {
    delay_250us();
    i--;
  }
}

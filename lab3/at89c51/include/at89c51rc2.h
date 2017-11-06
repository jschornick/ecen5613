// File       : at89c51rc2.h
// Author     : Jeff Schornick
//
// Additional register definitions for the Atmel AT89C51RC2
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Register definitions collected from the Atmel AT89C51RC2 datasheet.

#ifndef __AT89C51RC2_H
#define __AT89C51RC2_H

// Use a similar bundled register definition file as a base
#include <at89c51ed2.h>

// AUXR: Auxillary Register (reset: XX0X00Y0, Y=HSB.XRAM bit)
#define AUXR_AO_NORMAL   0x00      // Normal 8051 ALE signal
#define AUXR_AO_EXT      0x01      // ALE onnly on MOVX/MOVC
#define AUXR_EXTRAM_INT  0x00      // Use internal XRAM
#define AUXR_EXTRAM_EXT  0x02      // All XRAM external
#define AUXR_XSR_256     0x00      // 256 byte internal XRAM
#define AUXR_XSR_512     0x04      // 512 byte internal XRAM
#define AUXR_XSR_768     0x08      // 768 byte internal XRAM
#define AUXR_XSR_1024    0x0C      // 1024 byte internal XRAM
#define AUXR_M0_6CLK     0x00      // 6 clock RD/WR for MOVX
#define AUXR_M0_30CLK    0x20      // 30 clock RD/WR for MOVX
#define AUXR_DPU_ON      0x00      // Enable weak pullups
#define AUXR_DPU_OFF     0x80      // Disable weak pullups

// PCON: Power Control (87h)
#define PCON_IDLE_ENABLE  0x01     // Idle mode enabled
#define PCON_PDE_ENABLE   0x02     // Power down enable

#define INTR_EXT0   0
#define INTR_TIMER0 1
#define INTR_EXT1   2
#define INTR_TIMER1 3
#define INTR_SERIAL 4
#define INTR_TIMER2 5

#endif /* __AT89C51RC2_H */

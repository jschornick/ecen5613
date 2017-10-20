// File:   timer.h
// Author: Jeff Schornick
//
// Additional register definitions for 8051 timers
//
// Register data collected from the Siemens C501 users guide.

#ifndef __TIMER_H
#define __TIMER_H

#include <8052.h>

// or use tmod bits from 8051.h...
#define TMOD_T0_8BIT      0x00  // 8-bit mode
#define TMOD_T0_16BIT     0x01  // 16-bit mode
#define TMOD_T0_8BITR     0x02  // 8-bit mode w/reload
#define TMOD_T0_MODE3     0x03  // Mode 3
#define TMOD_T0_TIMER     0x00  // Timer mode
#define TMOD_T0_COUNTER   0x04  // Counter mode
#define TMOD_T0_NOGATE    0x00  // Timer 0 not gated
#define TMOD_T0_GATED     0x08  // Timer 0 gated by INT0

#define TMOD_T1_8BIT      0x00  // 8-bit mode
#define TMOD_T1_16BIT     0x10  // 16-bit mode
#define TMOD_T1_8BITR     0x20  // 8-bit mode w/reload
#define TMOD_T1_MODE3     0x30  // Mode 3
#define TMOD_T1_TIMER     0x00  // Timer mode
#define TMOD_T1_COUNTER   0x40  // Counter mode
#define TMOD_T1_NOGATE    0x00  // Timer 0 not gated
#define TMOD_T1_GATED     0x80  // Timer 0 gated by INT0

// TCON
#define TCON_TR_ON  1
#define TCON_TR_OFF 0

// T2CON: Timer 2 Control (C8h)
#define T2CON_C_TIMER     0x00  // Timer mode
#define T2CON_C_COUNTER   0x02  // Counter mode
#define T2CON_TR2OUNTER   0x02  // Counter mode

// TCON2 bit-addressable mapping (see 8052.h)
#define T2CON_CP    T2CON_0
#define T2CON_C     T2CON_1
#define T2CON_TR2   T2CON_2
#define T2CON_EXEN2 T2CON_3
#define T2CON_TCLK  T2CON_4
#define T2CON_RCLK  T2CON_5
#define T2CON_EXF2  T2CON_6
#define T2CON_TF2   T2CON_7

#endif /* __TIMER_H */

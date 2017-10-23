// File       : pca.h
// Author     : Jeff Schornick
//
// PCA macros and function declarations
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Register information was collected from the Atmel A89C51RC2 datasheet.

#ifndef __PCA_H
#define __PCA_H

// Partial SFR definitions for CMOD, CCON, and CCAPxy
#include <at89c51ed2.h>

// CMOD: PCA Counter Mode Register (0xD9)
//       Resets to 00XX_X000b
//       See AT89C51 datasheet p33
#define CMOD_CIDL_RUN     0x00  // PCA runs during idle
#define CMOD_CIDL_IDLE    0x80  // PCA does not run during idle
#define CMOD_WDTE_WDOFF   0x00  // Watchdog disabled
#define CMOD_WDTE_WDON    0x40  // Watchdog enabled
#define CMOD_CPS_FDIV6    0x00  // PCA clock counts at F_PERIPH/6
#define CMOD_CPS_FDIV2    0x02  // PCA clock counts at F_PERIPH/2
#define CMOD_CPS_T0       0x04  // PCA clock counts Timer 0 overflows
#define CMOD_CPS_EXT      0x06  // PCA clock counts an external signal on ECI
#define CMOD_ECF_OFF      0x00  // PCA overflow ignored
#define CMOD_ECF_ON       0x01  // PCA overflow sets CF bit (for interrupt)

// CCON bit settings, actual SFR defined in at89c51ed2.h
#define CCON_CR_PCA_ON   1
#define CCON_CR_PCA_OFF  0

// CCAPMn: PCA module x Compare/Capture Control Register (0xDA + n)
//         Resets to X000_0000b
//         See AT89C51 datasheet p36
#define CCAPM_ECOM_COMPARATOR   0x40  // Comparator enabled
#define CCAPM_CAPP_POS_EDGE     0x20  // Positive edge CEXn capture enabled
#define CCAPM_CAPN_NEG_EDGE     0x10  // Negative edge CEXn capture enabled
#define CCAPM_MAT_SET_CCF       0x08  // Match sets CFFn (interrupt)
#define CCAPM_TOG_TOGGLE_CEX    0x04  // Match toggles CEXn (output)
#define CCAPM_PWM_CEX           0x02  // CEXn used as PWM output
#define CCAPM_CCF_INT           0x01  // Intterupts enabled for module
#define CCAPM_CCF_NOINT         0x00  // Interrupts disabled for module

#define CCAPM_NO_OPERATION  0x0
#define CCAPM_PWM_MODE      (CCAPM_ECOM_COMPARATOR | CCAPM_PWM_CEX)

// Calculate a reset value for CCAPL to produce the desired duty cycle
//   CCAPH->CCAPL when lower 8-bits of PCA counter overflow
//   Output is low  when CL <  CCAPL
//   Output is high when CL >= CCAPL
//   Thus setting CCAPH = 0x00 is 100% duty
//                CCAPH = 0xFF is 1/256 = 0.39% duty
//   A duty cycle of 0 is not possible, but instead CCAPM_PWM should be disabled
#define DUTY_CYCLE(x) ( (uint8_t) 256 - (((x * (256UL*256)/100)) / 256) )


#endif /* __PCA_H */

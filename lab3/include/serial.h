// File       : serial.h
// Author     : Jeff Schornick
//
// Serial port macros and function declarations
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Register information was collected from the Atmel A89C51RC2 datasheet.
// Baud rate formula taken from the Siemens C501 datasheet.

#ifndef __SERIAL_H
#define __SERIAL_H

// SCON: Serial Control Register (98h)
//       Resets to 0x00
//       See AT89C51 datasheet p44
#define SCON_SM_SHIFT     0x00  // Mode 0, shift register
#define SCON_SM_8BIT      0x40  // Mode 1, 8-bit UART, variable baud
#define SCON_SM_9BIT_FIX  0x80  // Mode 2, 9-bit UART, fixed baud
#define SCON_SM_9BIT      0xC0  // Mode 3, 2-bit UART, variable baud
#define SCON_REN_DISABLE  0x00  // Disable receiver
#define SCON_REN_ENABLE   0x10  // Enable reciever

// PCON: Power Control (87h)
#define PCON_SMOD_1X      0x00  // Normal baud rate
#define PCON_SMOD_2X      0x80  // Double baud rate

// Baud rate timer reset calculation
//
// C501 user manual, page 6-33
//   Baud_rate =  (2^SMOD / 32) * (f_osc / (12*(256-TH1)))
//
//  With for baud_rate = 57.k with SMOD=1:
//       (256-TH1) = (2/32) * 11059200 / (12 * 57600)
//       TH1 = 255
//
#define TH1_57600_BAUD  255
#define TH1_28800_BAUD  254

// Determine the reset value for the internal baud rate generator,
// given a target rate and the peripheral clock frequncy.
//
// From AT89C51 datasheet p48:
//   Baud = 2^SMOD * F_periph / (6^(1-SPD) * 32 *(256-BRL))
//   BRL = 256 - (2*F_periph) / (32*baud)
#define BRL(baud,freq) ( 256U - freq / (16UL*baud) )


// Timer 2 reset values when running with f_periph = (11.0592MHz / 2)
#define RCAPL_57600_BAUD  0xFA  /* 250 */
#define RCAPH_57600_BAUD  0xFF
#define RCAPL_115200_BAUD 0xFD  /* 253 */
#define RCAPH_115200_BAUD 0xFF


// Function: serial_init_t1
//
// Initialize the serial port to 57.6k baud, 8 data bits, no parity.
// Timer 1 will be configured as the baud rate source.
//
// Assumes that F_OSC = 11.0592MHz
void serial_init_t1(void);

// Function: serial_init_t2
//
// Initialize the serial port to 57.6k baud, 8 data bits, no parity.
// Timer 2 will be configured as the baud rate source.
//
// Assumes that F_OSC = 11.0592MHz
void serial_init_t2(void);


// Function: serial_init_brg
//
// Initialize the serial port to 57.6k baud, 8 data bits, no parity.
// Timer 2 will be configured as the baud rate source.
void serial_init_brg(void);


#endif /* __SERIAL_H */

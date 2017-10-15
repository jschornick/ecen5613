// File       : lab3.c
// Author     : Jeff Schornick
//
// Implements the required functionality for ECEN5613 Lab 3.
//
// Specifically, ...
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Attribution for leveraged code...

#include <at89c51ed2.h>
#include <stdio.h>
#include "timer.h"

// SCON: Serial Control Register (98h)
//       Resets to 0x00
//       See datasheet p44
#define SCON_SM_SHIFT     0x00  // Mode 0, shift register
#define SCON_SM_8BIT      0x40  // Mode 1, 8-bit UART, variable baud
#define SCON_SM_9BIT_FIX  0x80  // Mode 2, 9-bit UART, fixed baud
#define SCON_SM_9BIT      0xC0  // Mode 3, 2-bit UART, variable baud
#define SCON_REN_DISABLE  0x00  // Disable receiver
#define SCON_REN_ENABLE   0x10  // Enable reciever

// PCON: Power Control (87h)
#define PCON_SMOD_1X      0x00  // Normal baud rate
#define PCON_SMOD_2X      0x80  // Double baud rate

void serial_init() {

  PCON |= PCON_SMOD_2X;

  // Configure serial port as an 8-bit UART
  SCON = SCON_SM_8BIT|SCON_REN_ENABLE;

  // TODO: user Timer2 to get 115.2k?
  // Timer 1, 8-bit auto-reload
  TMOD = TMOD_T1_8BITR | TMOD_T1_TIMER | TMOD_T1_NOGATE;
  // Baud_rate =  (2^SMOD / 32) * (f_osc / (12*(256-TH1)))
  //  With SMOD=1
  //       (256-TH1) = (2/32) * 11059200 / (12 * baud_rate)
  //       TH1=255
  // See; C501 user manual, page 6-33
  TH1 = 255;
  TR1 = TCON_TR_ON;  // Start timer
  TI  = 1;           // force ready to send
}

void putchar(char c) {
  while(!TI);  // Wait for transmit clear
  SBUF = c;
  TI = 0;
}

char getchar() {
  char c;
  while(!RI);  // Block until received data
  c = SBUF;    // grab character before resetting RI
  RI = 0;
  return c;
}

void main() {

  char c = 0;

  serial_init();

  printf_tiny("\n\rHello!\n\r");

  while(c != '\r') {
    c = getchar() & ~0x20;
    putchar(c);
  }
  putchar('\n');

}

// File       : serial.c
// Author     : Jeff Schornick
//
// Serial port initialization
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include "timer.h"
#include "serial.h"

void serial_init() {

  // Enable baud rate doubler
  PCON |= PCON_SMOD_2X;

  // Configure serial port as an 8-bit UART and enable receiver
  SCON = SCON_SM_8BIT|SCON_REN_ENABLE;

  // TODO: consider using Timer2 to operate at 115.2k?

  // Timer 1, 8-bit auto-reload
  TMOD = TMOD_T1_8BITR | TMOD_T1_TIMER | TMOD_T1_NOGATE;
  // Baud_rate =  (2^SMOD / 32) * (f_osc / (12*(256-TH1)))
  //  With SMOD=1
  //       (256-TH1) = (2/32) * 11059200 / (12 * baud_rate)
  //       TH1=255
  // See; C501 user manual, page 6-33
  TH1 = TH1_57600_BAUD;
  TR1 = TCON_TR_ON;  // Start timer
  TI  = 1;           // force ready to transmit
  RI  = 0;           // clear received flag
}


void putchar(char c) {
  while(!TI);  // Block until transmitter is ready
  SBUF = c;
  TI = 0;
}

char getchar() {
  char c;
  while(!RI);  // Block until data received
  c = SBUF;    // grab character before resetting RI
  RI = 0;
  return c;
}

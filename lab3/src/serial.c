// File       : serial.c
// Author     : Jeff Schornick
//
// Serial port initialization
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Baud rate formula taken from the Siemens C501 users guide.
// The putchar/getchar commands are based on examples from ECEN5613 class notes.

#include "at89c51rc2.h"
#include "timer.h"
#include "serial.h"

void serial_init_t1() {

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
  // See: C501 user manual, page 6-33
  TH1 = TH1_57600_BAUD;
  TR1 = TCON_TR_ON;  // Start timer
  TI  = 1;           // force ready to transmit
  RI  = 0;           // clear received flag
}

void serial_init_t2() {
  // Enable baud rate doubler
  PCON |= PCON_SMOD_2X;

  // Configure serial port as an 8-bit UART and enable receiver
  SCON = SCON_SM_8BIT|SCON_REN_ENABLE;

  BDRCON = 0;

  RCAP2H = RCAPH_57600_BAUD;
  RCAP2L = RCAPL_57600_BAUD;

  //RCAP2H = RCAPH_115200_BAUD;
  //RCAP2L = RCAPL_115200_BAUD;

  T2CON_C = 0; // counter
  T2MOD = T2OE;  // clock output
  T2CON_RCLK = 1;
  T2CON_TCLK = 1;
  TR2 = 1;

  TI  = 1;           // force ready to transmit
  RI  = 0;           // clear received flag
}


void serial_init_brg() {
  // Enable baud rate doubler
  PCON |= PCON_SMOD_2X;

  // Configure serial port as an 8-bit UART and enable receiver
  SCON = SCON_SM_8BIT|SCON_REN_ENABLE;

  BRL = BRL_57600_BAUD;

  // use internal baud generator, fast mode
  BDRCON = TBCK | RBCK | SPD | BRR;
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

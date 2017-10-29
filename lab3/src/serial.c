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
#include "clock.h"
#include "timer.h"
#include "serial.h"


// Function: serial_init_t1
//
// Initialize the serial port to 57.6k baud, 8 data bits, no parity.
// Timer 1 will be configured as the baud rate source.
//
// Assumes that F_OSC = 11.0592MHz
void serial_init_t1()
{
  // Enable baud rate doubler
  PCON |= PCON_SMOD_2X;

  // Configure serial port as an 8-bit UART and enable receiver
  SCON = SCON_SM_8BIT|SCON_REN_ENABLE;

  // Timer 1, 8-bit auto-reload
  TMOD = TMOD_T1_8BITR | TMOD_T1_TIMER | TMOD_T1_NOGATE;

  TH1 = TH1_57600_BAUD;
  TR1 = TCON_TR_ON;  // Start timer
  TI  = 1;           // force ready to transmit
  RI  = 0;           // clear received flag
}


// Function: serial_init_t2
//
// Initialize the serial port to 57.6k baud, 8 data bits, no parity.
// Timer 2 will be configured as the baud rate source.
//
// Assumes that F_OSC = 11.0592MHz
void serial_init_t2()
{
  // Enable baud rate doubler
  PCON |= PCON_SMOD_2X;

  // Configure serial port as an 8-bit UART and enable receiver
  SCON = SCON_SM_8BIT|SCON_REN_ENABLE;

  BDRCON = 0;

  RCAP2H = RCAPH_57600_BAUD;
  RCAP2L = RCAPL_57600_BAUD;

  T2CON_C = 0;  // timer mode
  T2MOD = T2OE; // clock output enabled
  T2CON_RCLK = 1;  // timer2 provides receiver clock
  T2CON_TCLK = 1;  // ...and transmitter clock

  TR2 = 1;  // start timer
  TI  = 1;  // force ready to transmit
  RI  = 0;  // clear received flag
}


// Function: serial_init_brg
//
// Initialize the serial port to 57.6k baud, 8 data bits, no parity.
// The internal baud rate generator will be configured as the baud rate source.
void serial_init_brg()
{
  // Enable baud rate doubler
  PCON |= PCON_SMOD_2X;

  // Configure serial port as an 8-bit UART and enable receiver
  SCON = SCON_SM_8BIT|SCON_REN_ENABLE;

  BRL = BRL(57600, F_OSC/2);

  // use internal baud generator for rx/tx, fast mode, enable
  BDRCON = TBCK | RBCK | SPD | BRR;

  TI  = 1;  // force ready to transmit
  RI  = 0;  // clear received flag
}


// Function: putchar
//
// Blocking version of putchar
//
// Sends a character out the serial port
void putchar(char c) {
  while(!TI);  // Block until transmitter is ready
  SBUF = c;
  TI = 0;
}

// Function: getchar_nb
//
// Blocking version of getchar
//
// Return a character from the serial port
char getchar() {
  char c;
  while(!RI);  // Block until data received
  c = SBUF;    // grab character before resetting RI
  RI = 0;
  return c;
}

// Function: getchar_nb
//
// Non-blocking version of getchar
//
// Return a character if one was available, 0 otherwise
char getchar_nb() {
  char c = 0;
  // only read a character if available
  if (RI) {
    c = SBUF;    // grab character before resetting RI
    RI = 0;
  }
  return c;
}

// File       : lcd.c
// Author     : Jeff Schornick
//
// Functions for an HD44780U LCD controller
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdint.h>
#include "lcd.h"

// Memory mapped addresses
//
// The HD44780U LCD controller is attached to the 8051 as follows:
//
//    LCD     8051
//   -----   ------
//     RW      A0  (latched AD0)
//     RS      A1  (latched AD1)
//      E    LCDEN (A15 & A14 & A13 & A12 & (~nRD + ~nWR))
//    DB0-7  AD0-7
//
volatile __xdata __at (0xF000) uint8_t LCD_CMD;      // Send command (RW=0, RS=0), write only
volatile __xdata __at (0xF001) uint8_t LCD_STAT;     // Read status (RW=1, RS=0), read only
volatile __xdata __at (0xF002) uint8_t LCD_DATA_WR;  // Write data, (RW=0, RS=1)
volatile __xdata __at (0xF003) uint8_t LCD_DATA_RD;  // Read data (RW=1, RS=1)

// Function: lcdinit
//
// Initializes the LCD
// Refer to Figure 25 on page 212 of the HD44780U data sheet.
void lcdinit(void)
{
}

// Function: lcdbusywait
//
// Polls the LCD busy flag, blocks until until the LCD controller is ready to
// accept another command.
void lcdbusywait(void)
{
}

// Function: lcdgotoaddr
//
// Sets the cursor to the specified LCD DDRAM address.
void lcdgotoaddr(unsigned char addr)
{
  // Should call lcdbusywait
  addr = addr;
}

// Function: lcdgotoxy
//
// Sets the cursor to the LCD DDRAM address corresponding to the specified row
// and column. Location (0,0) is the top left corner of the LCD screen.
void lcdgotoxy(unsigned char row, unsigned char column)
{
  // Must call lcdgotoaddr
  row = row;
  column = column;
}

// Function: lcdputch
//
// Writes the specified character to the current LCD cursor position.
void lcdputch(char cc)
{
  //  Should call lcdbusywait
  cc = cc;
}

// Function: lcdputstr
//
// Writes the specified null-terminated string to the LCD starting at the
// current LCD cursor position. Automatically wraps long strings to the next LCD
// line after the right edge of the display screen has been reached.
void lcdputstr(char *ss)
{
  // Must call lcdputch
  ss = ss;
}


// Function: lcdclear
//
// Clears the LCD using the HD44780 Clear display instruction.
void lcdclear(void)
{
}


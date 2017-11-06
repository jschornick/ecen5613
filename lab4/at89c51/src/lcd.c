// File       : lcd.c
// Author     : Jeff Schornick
//
// Functions for an HD44780U LCD controller
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdint.h>
#include "lcd.h"
#include "delay.h"

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

// Function: lcd_init
//
// Initializes the LCD
// Refer to Figure 25 on page 212 of the HD44780U data sheet.
void lcd_init(void)
{
  // wait >40 ms after power on
  delay_ms(40);
  // Switch to 8-bit interface mode
  LCD_CMD = LCD_CMD_FUNC | LCD_FUNC_8BIT;
  delay_ms(5);  // wait at least 4.1ms
  LCD_CMD = LCD_CMD_FUNC | LCD_FUNC_8BIT;
  delay_ms(1);  // wait at least 100us
  LCD_CMD = LCD_CMD_FUNC | LCD_FUNC_8BIT;
  lcd_busywait();

  // Set display lines and font
  LCD_CMD = LCD_CMD_FUNC | LCD_FUNC_8BIT | LCD_FUNC_2LINE | LCD_FUNC_5X8;
  lcd_busywait();

  // Display on/off here?

  // Writes increment address and move the cursor
  LCD_CMD = LCD_CMD_MODE | LCD_MODE_INC | LCD_MODE_NOSHIFT;
  lcd_busywait();

  // Turn on display
  LCD_CMD = LCD_CMD_DISPLAY | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_BLINK_ON;
  lcd_busywait();

  // Clear screen
  LCD_CMD = LCD_CMD_CLEAR;

}

// Function: lcd_busywait
//
// Polls the LCD busy flag, blocks until until the LCD controller is ready to
// accept another command.
void lcd_busywait(void)
{
  while (LCD_STAT & LCD_BUSY_MASK);
}

// Function: lcdgotoaddr
//
// Sets the cursor to the specified LCD DDRAM address.
void lcd_gotoaddr(uint8_t addr)
{
  lcd_busywait();
  LCD_CMD = LCD_CMD_DDRAM | (addr & LCD_DDRAM_MASK);
}

// Function: lcd_gotoxy
//
// Sets the cursor to the LCD DDRAM address corresponding to the specified row
// and column. Location (0,0) is the top left corner of the LCD screen.
void lcd_gotoxy(uint8_t row, uint8_t column)
{
  switch (row) {
  case 0:
    lcd_gotoaddr(column);
    break;
  case 1:
    lcd_gotoaddr(column+0x40);
    break;
  case 2:
    lcd_gotoaddr(column+0x14);
    break;
  case 3:
    lcd_gotoaddr(column+0x54);
    break;
  }
}

// Function: lcd_putch
//
// Writes the specified character to the current LCD cursor position.
void lcd_putch(char cc)
{
  lcd_busywait();
  LCD_DATA_WR = cc;
}

// Function: lcd_putstr
//
// Writes the specified null-terminated string to the LCD starting at the
// current LCD cursor position. Automatically wraps long strings to the next LCD
// line after the right edge of the display screen has been reached.
void lcd_putstr(char *ss)
{
  uint8_t column;
  uint8_t row = 0;

  column = LCD_STAT & LCD_DDRAM_MASK;

  if (column >= 0x40) {
    column -= 0x40;
    row++;
  }
  if (column >= 0x14) {
    column -= 0x14;
    row += 2;
  }

  while(ss) {
    if (column == 20) {
      column = 0;
      row = (row+1) % 4;
      lcd_gotoxy(row, column);
    }
    lcd_putch(*ss++);
    column++;
  }
}

// Function: lcd_clear
//
// Clears the LCD using the HD44780 Clear display instruction.
// DDRAM address is set to 0x00 automatically.
void lcd_clear(void)
{
  lcd_busywait();
  LCD_CMD = LCD_CMD_CLEAR;
}

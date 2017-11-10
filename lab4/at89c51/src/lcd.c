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

#include <stdio.h>

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
//
// 16x4 LCD memory layout:
//        0           15
//      ----         ----
//  0:  0x00   ...   0x0F
//  1:  0x40   ...   0x4F
//  2:  0x10   ...   0x1F
//  3:  0x50   ...   0x5F
//
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
    lcd_gotoaddr(column+0x10);
    break;
  case 3:
    lcd_gotoaddr(column+0x50);
    break;
  }
}


// Function: lcd_putch
//
// Writes the specified character to the current LCD cursor position.
void lcd_putchar(char cc)
{
  lcd_busywait();
  LCD_DATA_WR = cc;
}

uint8_t lcd_getchar()
{
  lcd_busywait();
  return LCD_DATA_RD;
}

void lcd_getxy(uint8_t *row, uint8_t *col)
{
  uint8_t addr;
  addr = lcd_getaddr();

  *row = 0;
  if (addr >= 0x40) {
    addr -= 0x40;
    (*row)++;
  }
  if (addr >= 0x10) {
    addr -= 0x10;
    *row += 2;
  }
  *col = addr;
}



// Function: lcd_getaddr
//
// Gets the current address pointer
uint8_t lcd_getaddr()
{
  lcd_busywait();
  // wait t_add = 5.5us for address to be valid
  // (see HD44780U datasheet p192)
  delay_5_5us();
  return (LCD_STAT & LCD_DDRAM_MASK);
}


// Function: lcd_cgram_addr
//
// Sts the current address pointer to a CGRAM address
void lcd_cgram_addr(uint8_t addr)
{
  lcd_busywait();
  LCD_CMD = LCD_CMD_CGRAM | (addr & LCD_CGRAM_MASK);
}


// Function: lcd_putstr
//
// Writes the specified null-terminated string to the LCD starting at the
// current LCD cursor position. Automatically wraps long strings to the next LCD
// line after the right edge of the display screen has been reached.
void lcd_putstr(char *ss)
{
  uint8_t row = 0;
  uint8_t col = 0;
  lcd_getxy(&row, &col);

  while(*ss) {
    lcd_putchar(*ss++);
    if (++col == LCD_COLS) {
      col = 0;
      row = (row+1) % LCD_ROWS;
      lcd_gotoxy(row, col);
    }
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


// Function: lcd_load_char
//
// Loads a 5x8 custom character from CGRAM and returns it
// in an 8-byte array.
//
// Params:
//   ccode: the custom character code, 0-7
//   row_vals: array (address) where the character data is returned
void lcd_load_char(uint8_t ccode, uint8_t row_vals[]) {
  uint8_t i;
  // CGRAM addresses are in the form ABC DEF, where
  // where ABC is the character code, and DEF are the individual rows.
  lcd_cgram_addr(ccode<<3);
  for(i=0; i<8; i++) {
    row_vals[i] = lcd_getchar();
  }
}


// Function: lcd_create_char
//
// Saves a 5x8 custom character into CGRAM
//
// Params:
//   ccode: the custom character code, 0-7
//   row_vals: 8-byte array (address) of character data
void lcd_create_char(uint8_t ccode, uint8_t row_vals[]) {
  uint8_t i;
  // CGRAM addresses are in the form ABC DEF, where
  // where ABC is the character code, and DEF are the individual rows.
  lcd_cgram_addr(ccode<<3);
  for(i=0; i<8; i++) {
    lcd_putchar(row_vals[i]);
  }
}

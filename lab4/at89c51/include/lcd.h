// File       : lcd.h
// Author     : Jeff Schornick
//
// LCD register definitions and function declarations
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Register definitions were collected from the Hitachi HD44780U datasheet

#ifndef __LCD_H
#define __LCD_H

#include <stdint.h>

extern volatile __xdata __at (0xF000) uint8_t LCD_CMD;
extern volatile __xdata __at (0xF001) uint8_t LCD_STAT;
extern volatile __xdata __at (0xF002) uint8_t LCD_DATA_WR;
extern volatile __xdata __at (0xF003) uint8_t LCD_DATA_RD;

#define LCD_ROWS 4
#define LCD_COLS 16

/////////////////////////////////
// Send command via LCD_CMD_ADDR

#define LCD_CMD_CLEAR     0x01

#define LCD_CMD_HOME      0x02

// Entry mode
// 0  0  0  0  0  1  I/D  S
#define LCD_CMD_MODE      0x04
#define LCD_MODE_INC      0x02  /* Increment address on write */
#define LCD_MODE_DEC      0x00  /* Decrement address on write */
#define LCD_MODE_SHIFT    0x01  /* Shift display */
#define LCD_MODE_NOSHIFT  0x00  /* Don't shift display (move cursor)  */

// Display control
// 0  0  0  0  1  D  C  B
#define LCD_CMD_DISPLAY   0x08
#define LCD_DISPLAY_ON    0x04  /* Entire display on */
#define LCD_DISPLAY_OFF   0x00  /* Entire display off */
#define LCD_CURSOR_ON     0x02  /* Cursor display on */
#define LCD_CURSOR_OFF    0x00  /* Cursor display off */
#define LCD_BLINK_ON      0x01  /* Blink cursor */
#define LCD_BLINK_OFF     0x00  /* Don't blink cursor */

// Cursor/display shift
// 0  0  0  1  S/C  R/L  x  x
#define LCD_CMD_SHIFT     0x10
#define LCD_SHIFT_DISPLAY 0x80  /* Display shifts, no cursor movement */
#define LCD_SHIFT_CURSOR  0x00  /* Cursor moves, no display shift */
#define LCD_SHIFT_RIGHT   0x40  /* Shift/move right */
#define LCD_SHIFT_LEFT    0x00  /* Shift/move left */

// Funciton set
// 0  0  1  DL  N  F  x  x
#define LCD_CMD_FUNC      0x20
#define LCD_FUNC_8BIT     0x10
#define LCD_FUNC_4BIT     0x00
#define LCD_FUNC_2LINE    0x08
#define LCD_FUNC_1LINE    0x00
#define LCD_FUNC_5X10     0x04
#define LCD_FUNC_5X8      0x00

// Set CGRAM address
#define LCD_CMD_CGRAM     0x40
#define LCD_CGRAM_MASK    0x3f

// Set DDRAM address
#define LCD_CMD_DDRAM     0x80
#define LCD_DDRAM_MASK    0x7f


/////////////////////////////////
// Read status via LCD_STAT_ADDR

#define LCD_BUSY_MASK     0x80  /* busy flag */
#define LCD_COUNTER_MASK  0x7F  /* address counter */


// Function: lcd_init
//
// Initializes the LCD
// Refer to Figure 25 on page 212 of the HD44780U data sheet.
void lcd_init(void);


// Function: lcd_busywait
//
// Polls the LCD busy flag, blocks until until the LCD controller is ready to
// accept another command.
void lcd_busywait(void);


// Function: lcd_gotoaddr
//
// Sets the cursor to the specified LCD DDRAM address.
void lcd_gotoaddr(uint8_t addr);


// Function: lcd_getaddr
//
// Gets the current LCD DDRAM/CGRAM address
uint8_t lcd_getaddr(void);

uint8_t lcd_getchar(void);

void lcd_getxy(uint8_t *row, uint8_t *col);


// Function: lcd_gotoxy
//
// Sets the cursor to the LCD DDRAM address corresponding to the specified row
// and column. Location (0,0) is the top left corner of the LCD screen.
void lcd_gotoxy(uint8_t row, uint8_t column);


// Function: lcd_putch
//
// Writes the specified character to the current LCD cursor position.
void lcd_putchar(char cc);


// Function: lcd_putstr
//
// Writes the specified null-terminated string to the LCD starting at the
// current LCD cursor position. Automatically wraps long strings to the next LCD
// line after the right edge of the display screen has been reached.
void lcd_putstr(char *ss);


// Function: lcd_clear
//
// Clears the LCD using the HD44780 Clear display instruction.
void lcd_clear(void);


// Function: lcd_cgram_addr
//
// Sts the current address pointer to a CGRAM address
void lcd_cgram_addr(uint8_t addr);


// Function: lcd_load_char
//
// Loads a 5x8 custom character from CGRAM and returns it
// in an 8-byte array.
//
// Params:
//   ccode: the custom character code, 0-7
//   row_vals: array (address) where the character data is returned
void lcd_load_char(uint8_t ccode, uint8_t row_vals[]);


// Function: lcd_create_char
//
// Saves a 5x8 custom character into CGRAM
//
// Params:
//   ccode: the custom character code, 0-7
//   row_vals: 8-byte array (address) of character data
void lcd_create_char(uint8_t ccode, uint8_t row_vals[]);

#endif /* __LCD_H */

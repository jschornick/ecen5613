// File       : lcd.h
// Author     : Jeff Schornick
//
// LCD register definitions and function declarations
//
// The HD44780U LCD controller is attached to the 8051 as follows:
//
//    LCD     8051
//   -----   ------
//     RW      A0  (latched AD0)
//     RS      A1  (latched AD1)
//      E    LCDEN (!RD + !WR + A15 + A14 + A13 + A12)
//    DB0-7  AD0-7
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Register definitions were collected from the Hitachi HD44780U datasheet

#ifndef __LCD_H
#define __LCD_H

/////////////////////////////////
// Memory mapped addresses

/* #define LCD_CMD_ADDR    0xF000   /\* Send command (RW=0, RS=0), write only *\/ */
/* #define LCD_STAT_ADDR   0xF001   /\* Read status (RW=1, RS=0), read only *\/ */
/* #define LCD_DATA_WR     0xF002   /\* Write data, (RW=0, RS=1) *\/ */
/* #define LCD_DATA_RD     0xF003   /\* Read data (RW=1, RS=1) *\/ */

// TODO: may need to change to extern and move definition to lcd.c
// See SDCC section 3.5.5 (Absolute addressing) for syntax
volatile __xdata __at (0xF000) uint8_t LCD_CMD;      // Send command (RW=0, RS=0), write only
volatile __xdata __at (0xF001) uint8_t LCD_STAT;     // Read status (RW=1, RS=0), read only
volatile __xdata __at (0xF002) uint8_t LCD_DATA_WR;  // Write data, (RW=0, RS=1)
volatile __xdata __at (0xF003) uint8_t LCD_DATA_RD;  // Read data (RW=1, RS=1)


/////////////////////////////////
// Send command via LCD_CMD_ADDR

#define LCD_CMD_CLEAR     0x01

#define LCD_CMD_HOME      0x02

// Entry mode
// 0  0  0  0  0  1  I/D  S
#define LCD_CMD_MODE      0x04
#define LCD_MODE_INC      0x02  /* Increment */
#define LCD_MODE_DEC      0x00  /* Decrement */
#define LCD_MODE_SHIFT    0x01  /* Shift display  */
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
#define LCD_FUNC          0x20
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


#endif /* __LCD_H */

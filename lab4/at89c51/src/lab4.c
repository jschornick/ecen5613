// File       : lab4.c
// Author     : Jeff Schornick
//
// Implements the required functionality for ECEN5613 Lab 4.
//
// Specifically, ...
//
// Compilation: Supports SDCC v3.6+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdio.h>  // printf
#include <stdint.h>
#include "serial.h"
#include "at89c51rc2.h"
#include "lcd.h"
#include "eeprom.h"

#define printf printf_tiny

#define NIBBLE_TO_ASCII(x) ( (x)<10 ? (x)+'0' : (x)+'A'-10 )

void dump_screen(void)
{
  uint8_t row, col;
  uint8_t c;
  uint8_t addr;

  printf("  0123456789ABCDEF\r\n");
  printf(" ------------------\r\n");

  addr = lcd_getaddr();
  for(row=0; row<LCD_ROWS; row++) {
    lcd_gotoxy(row,0);
    putchar(row+'0');
    putchar('|');
    for(col=0; col<LCD_COLS; col++) {
      c = lcd_getchar();
      if( (c>=32) && (c<=126) ) {
        putchar(c);
      } else {
        putchar('~');
      }
    }
    putchar('|');
    putchar('\r');
    putchar('\n');
  }
  printf(" ------------------\r\n");
  lcd_gotoaddr(addr);
}

void dump_ddram(void)
{
  uint8_t addr = 0;
  uint8_t c = 0;

  printf("\r\nLCD DDRAM:\r\n");
  printf("----------");

  for(addr = 0; addr <= 0x7f; addr++) {
    // Seek every time since reading out-of-bounds memory does
    // not advance the internal address pointer
    lcd_gotoaddr(addr);
    if ((addr & 0xf) == 0) {
      putchar('\r');
      putchar('\n');
      putchar(NIBBLE_TO_ASCII(addr>>4));
      putchar(NIBBLE_TO_ASCII(addr&0xf));
      putchar(':');
    }
    c = lcd_getchar();
    putchar(' ');
    putchar(NIBBLE_TO_ASCII(c>>4));
    putchar(NIBBLE_TO_ASCII(c&0xf));
  }
  putchar('\r');
  putchar('\n');
}

void dump_cgram(void)
{
  uint8_t i;
  uint8_t c = 0;

  printf("\r\nLCD CGRAM:\r\n");
  printf("----------");

  lcd_cgram_addr(0x0);
  for(i=0; i<64; i++) {
    if ((i & 0xf) == 0) {
      putchar('\r');
      putchar('\n');
      putchar(NIBBLE_TO_ASCII(i>>4));
      putchar(NIBBLE_TO_ASCII(i&0xf));
      putchar(':');
    }
    c = lcd_getchar();
    putchar(' ');
    putchar(NIBBLE_TO_ASCII(c>>4));
    putchar(NIBBLE_TO_ASCII(c&0xf));
  }
  putchar('\r');
  putchar('\n');
}


#define ASCII_ESC 0x1b
#define ASCII_ETX 0x03
#define ASCII_CR  0x0d

#define CS_UP    'A'
#define CS_DOWN  'B'
#define CS_LEFT  'D'
#define CS_RIGHT 'C'

#define TYPE_MODE_NORM 0
#define TYPE_MODE_ESC  1
#define TYPE_MODE_CS   2

void cmd_type(void)
{
  __data uint8_t mode = TYPE_MODE_NORM;
  __data char c = 0 ;
  __data char str[2] = {'\0', '\0'};
  __data uint8_t row, col;

  printf("Type a message on the LCD, ^C to exit...\r\n");
  lcd_gotoaddr(0x0);
  while (c != ASCII_ETX) {
    c = getchar();  // block until input
    switch (mode) {
    case TYPE_MODE_NORM:
      if( (c>=32) && (c<=126)) {
        *str = c;
        lcd_putstr(str);
      } else if (c == ASCII_ESC) {
        mode = TYPE_MODE_ESC;
      }
      break;
    case TYPE_MODE_ESC:
      /* reading escape character */
      switch (c) {
      case '[':
        mode = TYPE_MODE_CS;
        break;
      case 'c':
        lcd_clear();
        mode = TYPE_MODE_NORM;
        break;
      case ASCII_ESC:
        printf("! Double-escape\r\n");
        break;
      default:
        if( (c>='0') && (c<='7')) {
          lcd_putchar(c-'0');  // CGRAM character
        } else {
          printf("! Unknown escape sequence: %u ('%c')\r\n",c,c);
        }
        mode = TYPE_MODE_NORM;
        break;
      }
      break;
    case 2:
      /* reading control sequeunce */
      lcd_getxy(&row, &col);
      //printf("Old pos: (%u,%u)\r\n", row, col);
      switch (c) {
      case CS_UP:
        row = (row + (LCD_ROWS-1)) % LCD_ROWS;
        lcd_gotoxy(row, col);
        break;
      case CS_DOWN:
        row = (row+1) % LCD_ROWS;
        lcd_gotoxy(row, col);
        break;
      case CS_RIGHT:
        col = (col+1) % LCD_COLS;
        lcd_gotoxy(row, col);
        break;
      case CS_LEFT:
        col = (col + (LCD_COLS-1)) % LCD_COLS;
        lcd_gotoxy(row, col);
        break;
      default:
        printf("! Unknown control sequence: %u ('%c')\r\n",c,c);
      }
      //printf("New pos: (%u,%u) @ %02x\r\n", row, col, lcd_getaddr());
      mode = TYPE_MODE_NORM;
    }
  } /* while !ETX */

}


// Command key definitions for the menu
#define KEY_DDRAM    'D'  // Dump LCD DDRAM
#define KEY_CGRAM    'G'  // Dump LCD CGRAM
#define KEY_SCREEN   'S'  // Dump LCD Screen contents
#define KEY_TYPE     'T'  // Type on LCD
#define KEY_CLEAR    'C'  // Clear the LCD
#define KEY_CUSTOM   'N'  // New custom character
#define KEY_EE_WRITE 'W'  // Write byte to EEPROM
#define KEY_EE_READ  'R'  // Read byte from EEPROM
#define KEY_EE_DUMP  'E'  // Dump EEPROM
#define KEY_SAVE     'V'  // Save LCD data to EEPROM
#define KEY_LOAD     'L'  // Load LCD data from EEPROM


void lcd_welcome(void)
{
  // Smiley face
  lcd_cgram_addr(0x0);
  lcd_putchar(0x1b);
  lcd_putchar(0x1b);
  lcd_putchar(0x00);
  lcd_putchar(0x04);
  lcd_putchar(0x04);
  lcd_putchar(0x11);
  lcd_putchar(0x0e);
  lcd_putchar(0x00);
  lcd_putchar(0x1b);

  // Corner decorations
  lcd_gotoxy(0,0);
  lcd_putchar(0);
  lcd_gotoxy(1,1);
  lcd_putchar(0);
  lcd_gotoxy(2,1);
  lcd_putchar(0);
  lcd_gotoxy(3,0);
  lcd_putchar(0);
  lcd_gotoxy(0,15);
  lcd_putchar(0);
  lcd_gotoxy(1,14);
  lcd_putchar(0);
  lcd_gotoxy(2,14);
  lcd_putchar(0);
  lcd_gotoxy(3,15);
  lcd_putchar(0);

  lcd_gotoxy(1,3);
  lcd_putstr("Welcome to");
  lcd_gotoxy(2,4);
  lcd_putstr("Lab # 4!");

}

// Function: read_hex
//
// Reads a hex value (0-9a-f) from the serial port.
//
// Returns: A 8-bit value (0-15) read from serial
uint8_t read_hex(void) {
  uint8_t val = 0xff;
  char c;
  while( val == 0xff ) {
    c = getchar();
    if ( (c >= '0') && (c <= '9') ) {
      putchar(c);
      val = c - '0';
    }
    c &= ~0x20;  // capitalize
    if ( (c >= 'A') && (c <= 'F') ) {
      val = c - ('A' - 10);
      putchar(c);
    }
  }
  return val;
}

uint16_t read_hex_n(uint8_t n)
{
  uint8_t i = 0;
  uint16_t val = 0;
  for(i = 0; i<n; i++) {
    val <<= 4;
    val += read_hex();
  }
  return val;
}

void display_char(uint8_t rows[])
{
  uint8_t i;
  uint8_t bitmask;
  uint8_t byte;
  for(i=0; i<8; i++) {
    putchar(i+'0');
    putchar(':');
    putchar(' ');
    byte = rows[i];
    for(bitmask=1; bitmask <= 16 ; bitmask <<= 1) {
      if(byte & bitmask) {
        putchar('x');
      } else {
        putchar(' ');
      }
    }
    putchar('\r');
    putchar('\n');
  }
}

void display_all_chars()
{
  uint8_t row;
  uint8_t charnum;
  uint8_t bitmask;
  uint8_t byte;

 printf("    0      1      2      3      4      5      6      7\r\n");
 printf("  -----  -----  -----  -----  -----  -----  -----  -----\r\n");
  for(row=0; row<8; row++) {
    for(charnum = 0; charnum<8; charnum++) {
      putchar(' ');
      putchar(' ');
      lcd_cgram_addr( (charnum<<3) + row);
      byte = lcd_getchar();
      for(bitmask=1; bitmask <= 16 ; bitmask <<= 1) {
        if(byte & bitmask) {
          putchar('x');
        } else {
          putchar(' ');
        }
      }
    }
    putchar('\r');
    putchar('\n');
  }
}

void cmd_new_char(void)
{
  char c;
  uint8_t charnum = 0xff;
  uint8_t row;
  uint8_t bits;
  uint8_t bitval;
  uint8_t rows[8];

  display_all_chars();
  printf("\r\nChoose a character code (0-7): ");
  while( charnum == 0xff ) {
    c = getchar();
    if ( (c >= '0') && (c <= '7') ) {
      charnum = c - '0';
    }
  }
  printf("\r\n");
  lcd_load_char(charnum, rows);

  do {
    printf("\r\nCharacter #%u", charnum);
    printf("\r\n");
    display_char(rows);
    printf("\r\nSelect row to edit (0-7), or return when done: ");
    c = getchar();
    if ( (c >= '0') && (c <= '7') ) {
      putchar(c);
      row = c - '0';
      printf("\r\nEnter 5 new bits (e.g., 01010): ");
      bits = 0;
      bitval = 0;
      do {
        c = getchar();
        if( (c == '0') ||  (c == '1') ) {
          putchar(c);
          bitval >>= 1;
          bitval += (c - '0')<<4;
          bits++;
        }
      } while (bits < 5);
      printf("\r\n");
      rows[row] = bitval;
    }
  } while( c != ASCII_CR );
  lcd_create_char(charnum, rows);
  printf("\r\nSaved character #%u:\r\n", charnum);
}

void cmd_ee_write(void)
{
  uint16_t addr;
  uint8_t val;
  printf("\r\nEEPROM address to write (0xABC) ? 0x");
  addr = read_hex_n(3);
  printf("\r\nEEPROM value (0xDE) ? 0x");
  val = read_hex_n(2);
  printf("\r\nWriting %x to address %x... ", val, addr);
  eeprom_write(addr,val);
  printf("done\r\n");
}

void cmd_ee_read(void)
{
  uint16_t addr;
  uint8_t data;

  printf("\r\nEEPROM address to read (0xABC) ? 0x");
  addr = read_hex_n(3);
  data = 0;
  eeprom_busy();
  eeprom_read(addr,&data);
  printf("\r\n");
  putchar(NIBBLE_TO_ASCII(addr>>8));
  putchar(NIBBLE_TO_ASCII((addr&0xff)>>4));
  putchar(NIBBLE_TO_ASCII(addr&0xf));
  printf(": ");
  putchar(NIBBLE_TO_ASCII(data>>4));
  putchar(NIBBLE_TO_ASCII(data&0xf));
  printf("\r\n");
}

void cmd_ee_dump(void)
{
  uint16_t addr = 0;
  uint16_t start_addr = 0;
  uint16_t end_addr = 0;
  uint8_t data;

  printf("\r\nEEPROM start address: 0xABC = 0x");
  start_addr = read_hex_n(3);
  printf("\r\nEEPROM end address  : 0xDEF = 0x");
  end_addr = read_hex_n(3);

  printf("\r\n      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
  printf("\r\n     -----------------------------------------------");
  for( addr = start_addr & 0xff0 ; addr <= end_addr; addr++) {
    if ((addr & 0xf) == 0) {
      putchar('\r');
      putchar('\n');
      putchar(NIBBLE_TO_ASCII(addr>>8));
      putchar(NIBBLE_TO_ASCII((addr&0xff)>>4));
      putchar(NIBBLE_TO_ASCII(addr&0xf));
      putchar(':');
    }
    putchar(' ');
    eeprom_read(addr, &data);
    if(addr >= start_addr) {
      putchar(NIBBLE_TO_ASCII(data>>4));
      putchar(NIBBLE_TO_ASCII(data&0xf));
    } else {
      putchar('.');
      putchar('.');
    }
  }
  putchar('\r');
  putchar('\n');
}

void cmd_save(void)
{
  uint16_t ee_addr;
  uint8_t i;

  printf("\r\nSave LCD data to EEPROM\r\n");
  printf("\r\nEEPROM address: 0xABC = 0x");
  ee_addr = read_hex_n(3);
  printf("\r\nSaving... ");
  lcd_gotoaddr(0x0);
  for(i=0; i < LCD_COLS*2; i++) {
    eeprom_write(ee_addr++, lcd_getchar());
  }
  lcd_gotoaddr(0x40);
  for(i=0; i < LCD_COLS*2; i++) {
    eeprom_write(ee_addr++, lcd_getchar());
  }
  lcd_cgram_addr(0x0);
  for(i=0; i<= 64; i++) {
    eeprom_write(ee_addr++, lcd_getchar());
  }
  printf("done!\r\n");
}

void cmd_load(void)
{
  uint16_t ee_addr;
  uint8_t i;
  uint8_t data;

  printf("\r\nLoad LCD data from EEPROM\r\n");
  printf("\r\nEEPROM address: 0xABC = 0x");
  ee_addr = read_hex_n(3);
  printf("\r\nLoading... ");
  lcd_gotoaddr(0x0);
  for(i=0; i < LCD_COLS*2; i++) {
    eeprom_read(ee_addr++, &data);
    lcd_putchar(data);
  }
  lcd_gotoaddr(0x40);
  for(i=0; i < LCD_COLS*2; i++) {
    eeprom_read(ee_addr++, &data);
    lcd_putchar(data);
  }
  lcd_cgram_addr(0x0);
  for(i=0; i< 64; i++) {
    eeprom_read(ee_addr++, &data);
    lcd_putchar(data);
  }
  printf("done!\r\n");
}

// Function: display_menu
//
// Presents the user a simple menu of commands to choose from.
void display_menu(void)
{
  printf("\r\n=== Lab 4 Menu ===\r\n\r\n");
  printf(" %c - LCD: Type on screen\r\n", KEY_TYPE);
  printf(" %c - LCD: Screen contents\r\n", KEY_SCREEN);
  printf(" %c - LCD: Custom character\r\n", KEY_CUSTOM);
  printf(" %c - LCD: Dump DDRAM\r\n", KEY_DDRAM);
  printf(" %c - LCD: Dump CGRAM\r\n", KEY_CGRAM);
  printf(" %c - LCD: Clear\r\n", KEY_CLEAR);
  printf(" %c - EEPROM: Write byte\r\n", KEY_EE_WRITE);
  printf(" %c - EEPROM Read byte\r\n", KEY_EE_READ);
  printf(" %c - EEPROM: Dump memory\r\n", KEY_EE_DUMP);
  printf(" %c - COMBO: Save LCD -> EEPROM\r\n", KEY_SAVE);
  printf(" %c - COMBO: Load LCD <- EEPROM\r\n", KEY_LOAD);
}

// Function: main
//
// ...
void main()
{
  char c;

  P1_2 = 0; // led on
  serial_init_brg();

  printf("\r\n");
  printf("-----------------------\n\r");
  printf("|  Welcome to Lab 4!  |\r\n");
  printf("----------------------- \r\n");
  printf("\r\n");
  printf("Built on %s (%s)\r\n", BUILD_DATE, GIT_COMMIT);
  printf("\r\n");

  printf("Initializing LCD... ");
  lcd_init();
  printf("done!\r\n");

  lcd_welcome();

  display_menu();
  while(1) {

    printf("-> ");
    c = getchar() & ~0x20;
    printf("\r\n");

    // Run a command based on the received character, or display the menu
    // after an invalid selection
    switch(c) {
    case KEY_SCREEN:
      dump_screen();
      break;
    case KEY_DDRAM:
      dump_ddram();
      break;
    case KEY_CGRAM:
      dump_cgram();
      break;
    case KEY_TYPE:
      cmd_type();
      break;
    case KEY_CLEAR:
      lcd_clear();
      printf("\r\nLCD cleared\r\n");
      break;
    case KEY_CUSTOM:
      cmd_new_char();
      break;
    case KEY_EE_WRITE:
      cmd_ee_write();
      break;
    case KEY_EE_READ:
      cmd_ee_read();
      break;
    case KEY_EE_DUMP:
      cmd_ee_dump();
      break;
    case KEY_SAVE:
      cmd_save();
      break;
    case KEY_LOAD:
      cmd_load();
      break;
    default:
      display_menu();
      break;
    }
  }

}

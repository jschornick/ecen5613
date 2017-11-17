// File       : lab4.c
// Author     : Jeff Schornick
//
// Implements the required functionality for ECEN5613 Lab 4.
//
// Specifically, this program presents a menu over serial which
// can be used to interact with the LCD and I2C EEPROM.
//
// LCD features include a typing interface, mirroring of screen contents,
// dumping DDRAM, dumping CGRAM, and custom character creation.
//
// EEPROM features include reading and writing of individual bytes, as well
// as dumping a memory range.
//
// Two final commands allow the LCD RAM to be saved to EEPROM and reloaed
// at a later time.
//
// Compilation: Supports SDCC v3.6+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdio.h>  // printf
#include <stdint.h>
#include "serial.h"
#include "at89c51rc2.h"
#include "lcd.h"
#include "eeprom.h"
#include "io_expander.h"
#include "timer.h"

// Only load the simplest printf since we're doing hex padding manually.
#define printf printf_tiny

// Quickly convert a 4-bit value (0x0-0xF) into ASCII
#define NIBBLE_TO_ASCII(x) ( (x)<10 ? (x)+'0' : (x)+'A'-10 )

// Command key definitions for the menu
#define KEY_DDRAM    'D'  // Dump LCD DDRAM
#define KEY_CGRAM    'G'  // Dump LCD CGRAM
#define KEY_SCREEN   'S'  // Dump LCD Screen contents
#define KEY_TYPE     'T'  // Type on LCD
#define KEY_CLEAR    'X'  // Clear the LCD
#define KEY_CUSTOM   'N'  // New custom character
#define KEY_EE_WRITE 'W'  // Write byte to EEPROM
#define KEY_EE_READ  'R'  // Read byte from EEPROM
#define KEY_EE_DUMP  'E'  // Dump EEPROM
#define KEY_SAVE     'V'  // Save LCD data to EEPROM
#define KEY_LOAD     'L'  // Load LCD data from EEPROM
#define KEY_CLOCK    'C'  // Stop/start clock
#define KEY_CLOCK_ZERO 'Z'  // Reset clock to 00:00.0

// Useful ASCII values
#define ASCII_ESC 0x1b  /* escape */
#define ASCII_ETX 0x03  /* control-C */
#define ASCII_CR  0x0d  /* carriage return */

// Control sequences for arrow keys
#define CS_UP    'A'
#define CS_DOWN  'B'
#define CS_LEFT  'D'
#define CS_RIGHT 'C'

// Typing mode input state machine
#define TYPE_MODE_NORM 0  /* normal typing */
#define TYPE_MODE_ESC  1  /* escape sequence */
#define TYPE_MODE_CS   2  /* control sequence */

// Clock pin (input from JP1)
//   0 : Clock runs   (JP1 connected)
//   1 : Clock paused (JP1 disconnected)
#define CLOCK_CTL P1_3
#define CLOCK_CTL_ON  0
#define CLOCK_CTL_OFF 1

uint8_t clock_run;   // software clock control
volatile uint8_t clock_ticks;   // clock ticks (0..19, 50ms each)
volatile uint8_t clock_secs; // clock seconds, BCD format
volatile uint8_t clock_mins; // clock minutes, BCD format

#define IO_EXP_BUTTON  0  /* P0 */
#define IO_EXP_LED     1  /* P1 */

// Funciton: init_clock
//
// Initialize the clock by resetting the counters and initializing Timer 2 to
// interrupt every 50ms.
void init_clock(void)
{
  // Set GPIO for clock control to be an input, reading JP1
  CLOCK_CTL = 1;

  // Reset all counters
  clock_ticks = 0;
  clock_secs = 0;
  clock_mins = 0;

  // Timer 2 will interrupt every 50ms. This is twice the required 0.1s
  // resolution, but is as slow as we can get with a 16-bit timer
  timer2_init();

  clock_run = 1; // run clock (unless gated by JP1)
}

// Function: dump_screen
//
// Show the screen contents of the LCD over the serial port.
// The original LCD address will be restored after reading.
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


// Function: dump_ddram
//
// Dump the LCD DDRAM as hex, 16 bytes per line. Each line is prefaced with the
// 8-bit starting address. The original LCD address will be restored after
// reading.
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


// Function: dump_cgram
//
// Dump the LCD CGRAM as hex, 16 bytes per line. Each line is prefaced with the
// 8-bit starting address. The original LCD address will be restored after
// reading.
void dump_cgram(void)
{
  uint8_t i;
  uint8_t c = 0;

  printf("\r\nLCD CGRAM:\r\n");
  printf("----------");

  __critical {
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
  }
  putchar('\r');
  putchar('\n');
}


// Function: cmd_type
//
// Allow the user to type onto the LCD by inputing characters over serial.
//
// Printable ASCII characters are send directly to the LCD. A escape sequences
// are included for clearing the screen and inputting the LCD's custom
// characters. Navigation is supported by interpretting control sequences for
// the arrow keys.
//
// Escape and control sequences are handled via a rudimentary state machine.
void cmd_type(void)
{
  // Use fast data access so that we minimize character loss at high input rates
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
      /* Normal mode, not in the middle of a sequence */
      if( (c>=32) && (c<=126)) {
        // Printable ASCII, so send it out
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
        // Beginning of a control sequence
        mode = TYPE_MODE_CS;
        break;
      case 'c':
        // Custom escape sequence for clear screen
        lcd_clear();
        mode = TYPE_MODE_NORM;
        break;
      case ASCII_ESC:
        printf("! Double-escape\r\n");
        break;
      default:
        // Map each of the custom characters to a numeric escape sequence
        if( (c>='0') && (c<='7')) {
          lcd_putchar(c-'0');  // CGRAM characters have value 0x0 to 0x7
        } else {
          printf("! Unknown escape sequence: %u ('%c')\r\n",c,c);
        }
        mode = TYPE_MODE_NORM;
        break;
      }
      break;
    case 2:
      /* reading control sequeunce, escape+[+CSI */
      lcd_getxy(&row, &col);
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
      mode = TYPE_MODE_NORM;
    }
  } /* while !ETX */

}


// Function: lcd_welcome
//
// Print a friendly welcome message on the LCD.
void lcd_welcome(void)
{
  // A 2x4 character smiley face as custom characters
  uint8_t smiley[][] = {{0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02},
                        {0x03, 0x0C, 0x10, 0x00, 0x00, 0x1F, 0x1D, 0x0E},
                        {0x18, 0x06, 0x01, 0x00, 0x00, 0x1F, 0x1D, 0x0E},
                        {0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x18, 0x08},
                        {0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00},
                        {0x00, 0x00, 0x08, 0x07, 0x00, 0x10, 0x0C, 0x03},
                        {0x00, 0x06, 0x0C, 0x18, 0x00, 0x01, 0x06, 0x18},
                        {0x08, 0x08, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00} };
  uint8_t i;

  for(i = 0; i<8; i++) {
    lcd_create_char(i, smiley[i]);
  }

  lcd_gotoxy(0,0);
  lcd_putstr("Stay cool...");
  lcd_gotoxy(1,5);
  lcd_putchar(0);
  lcd_putchar(1);
  lcd_putchar(2);
  lcd_putchar(3);
  lcd_gotoxy(2,5);
  lcd_putchar(4);
  lcd_putchar(5);
  lcd_putchar(6);
  lcd_putchar(7);
  lcd_gotoxy(3,0);
}


// Function: read_hex
//
// Reads a hex value (0-9a-f) from the serial port. Accepts both upper and
// lowercase hex characters.
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


// Function: read_hex_n
//
// Reads n hex digits from the serial port, where n is from 1 to 4.
//
// Returns: A 16-bit value (0-16^n-1) read from serial
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


// Function: display_char
//
// Displays a character from 8 bytes of character row data, using the same
// format as an LCD custom character.
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
    for(bitmask=16; bitmask > 0; bitmask >>= 1) {
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


// Function: display_custom_chars
//
// Displays all 8 custom characters stored in CGRAM.
void display_custom_chars()
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
      __critical {
        lcd_cgram_addr( (charnum<<3) + row);
        byte = lcd_getchar();
        for(bitmask=16; bitmask > 0; bitmask >>= 1) {
          if(byte & bitmask) {
            putchar('x');
          } else {
            putchar(' ');
          }
        }
      }
    }
    putchar('\r');
    putchar('\n');
  }
}


// Function: display_custom_chars
//
// Displays all 8 custom characters stored in CGRAM.
void cmd_new_char(void)
{
  char c;
  uint8_t charnum = 0xff;
  uint8_t row;
  uint8_t bits;
  uint8_t bitval;
  uint8_t rows[8];

  display_custom_chars();
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
          bitval <<= 1;
          bitval += (c - '0');
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


// Function cmd_ee_write
//
// Prompt the user for a 16-bit address and an 8-bit value in hex, then store
// that value at the EEPROM address.
void cmd_ee_write(void)
{
  uint16_t addr;
  uint8_t val;
  printf("\r\nEEPROM address to write (0xABC) ? 0x");
  addr = read_hex_n(3);
  if(addr > EEPROM_ADDR_MAX) {
    printf("\r\nAddress out of range!\r\n");
    return;
  }

  printf("\r\nEEPROM value (0xDE) ? 0x");
  val = read_hex_n(2);
  printf("\r\nWriting %x to address %x... ", val, addr);
  eeprom_write(addr,val);
  printf("done\r\n");
}


// Function cmd_ee_read
//
// Prompt the user for a 16-bit address in hex, read the address location from
// EEPROM and display the result.
void cmd_ee_read(void)
{
  uint16_t addr;
  uint8_t data;

  printf("\r\nEEPROM address to read (0xABC) ? 0x");
  addr = read_hex_n(3);
  if(addr > EEPROM_ADDR_MAX) {
    printf("\r\nAddress out of range!\r\n");
    return;
  }

  data = 0;
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


// Function: cmd_ee_dump
//
// Prompt the user for an address range and display the EEPROM contents in that
// range. Contents are displayed in the format AAA: DD DD ..., with a maximum of
// 16 values per line.
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
  if(end_addr > EEPROM_ADDR_MAX) {
    printf("\r\nEnd address out of range!\r\n");
    return;
  }
  if(start_addr > end_addr) {
    printf("\r\nStart address must be less than end address!\r\n");
    return;
  }

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


// Function: cmd_save
//
// Prompt the user for a memory address and write all LCD RAM (DDRAM and CGRAM)
// to EEPROM starting at that address.
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
  __critical {
    lcd_cgram_addr(0x0);
    for(i=0; i<= 64; i++) {
      eeprom_write(ee_addr++, lcd_getchar());
    }
  }
  printf("done!\r\n");
}

// Function: cmd_load
//
// Prompt the user for a memory address and load all LCD RAM (DDRAM and CGRAM)
// from EEPROM starting at that address.
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
  // The entire CGRAM write has to be in a critical section since the clock update
  // can't restore a CGRAM address due to address space ambiguity of the LCD.
  __critical {
    lcd_cgram_addr(0x0);
    for(i=0; i< 64; i++) {
      eeprom_read(ee_addr++, &data);
      lcd_putchar(data);
    }
  }
  printf("done!\r\n");
}

// Function: display_status
//
// Display a sumamry of key system variables, specifically clock status and
// the state of the I/O expander.
void display_status(void)
{
  uint8_t io_pins;
  uint8_t i;
  uint8_t ticks, mins, secs;

  printf( "\r\nClock status: ");
  if(CLOCK_CTL == CLOCK_CTL_OFF) {
    printf( "Disabled by JP1\r\n" );
  } else {
    if(clock_run) {
      printf( "Running\r\n" );
    } else {
      printf( "Disabled by software\r\n" );
    }
  }

  __critical {
    ticks = clock_ticks;
    secs = clock_secs;
    mins = clock_mins;
  }
  printf( "Time: %u%u:%u%u.%u\r\n", mins>>4, mins&0xf, secs>>4, secs&0xf, ticks>>1);

  io_pins = io_exp_read();
  printf( "I/O port: ");
  for(i=0x80; i>0; i>>=1) {
    putchar('0' + ((io_pins & i) != 0));
  }
  printf( "\r\n");
  printf( "Inputs  : ");
  for(i=0x80; i>0; i>>=1) {
    putchar('0' + ((io_exp_input_pins & i) != 0));
  }

  printf( "\r\n");
}


// Function: display_menu
//
// Presents the user a simple menu of commands to choose from.
void display_menu(void)
{
  printf("\r\n=== Lab 4 Menu ===\r\n\r\n");
  printf(" %c - LCD: Type on screen\r\n", KEY_TYPE);
  printf(" %c - LCD: Show screen contents\r\n", KEY_SCREEN);
  printf(" %c - LCD: Custom character\r\n", KEY_CUSTOM);
  printf(" %c - LCD: Dump DDRAM\r\n", KEY_DDRAM);
  printf(" %c - LCD: Dump CGRAM\r\n", KEY_CGRAM);
  printf(" %c - LCD: Clear\r\n", KEY_CLEAR);
  printf(" %c - EEPROM: Write byte\r\n", KEY_EE_WRITE);
  printf(" %c - EEPROM: Read byte\r\n", KEY_EE_READ);
  printf(" %c - EEPROM: Dump memory\r\n", KEY_EE_DUMP);
  printf(" %c - COMBO: Save LCD -> EEPROM\r\n", KEY_SAVE);
  printf(" %c - COMBO: Load LCD <- EEPROM\r\n", KEY_LOAD);
  printf(" %c - CLOCK: Start/stop\r\n", KEY_CLOCK);
  printf(" %c - CLOCK: Reset to 0:00.0\r\n", KEY_CLOCK_ZERO);
}


// Function: main
//
// Initialize hardware, then loop continuously while processesing serial input.
void main()
{
  char c;

  P1_2 = 0; // green led on right awawy
  serial_init_brg(); // use the internal baud rate generator for serial

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

  printf("Initializing clock... ");
  init_clock();
  printf("done!\r\n");

  printf("Performimg EEPROM reset... ");
  eeprom_reset();
  printf("done!\r\n");

  printf("Configuring I/O expander... ");
  io_exp_set_inputs(1<<IO_EXP_BUTTON);
  IT0=1; // set INT0 to be (falling) edge triggered
  EX0=1; // enable INT0 interrupt for I/O expander
  EA=1;  // ensure interrupts are enabled
  printf("done!\r\n");

  lcd_welcome();
  display_menu();

  while(1) {

    printf("-> ");
    c = getchar() & ~0x20;  // upper or lowercase accepted
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
    case KEY_CLOCK:
      if(clock_run) {
        clock_run = 0;
        printf("\r\nClock disbled\r\n");
      } else {
        clock_run = 1;
        printf("\r\nClock enabled\r\n");
      }
      break;
    case KEY_CLOCK_ZERO:
      __critical {
        clock_ticks = 0;
        clock_secs = 0;
        clock_mins = 0;
      }
      printf("\r\nClock reset\r\n");
      break;
    default:
      display_status();
      display_menu();
      break;
    }
  }

}


// Function: timer2_isr
//
// Interrupt service routine for Timer 2.
//
// Timer 2 interrupts every 50ms, representing a 1/20s clock tick. Ticks are
// only incremented if the clock is enabled in both software and hardware.
//
// The LCD is modified, but the address is restored before exit. However, CGRAM
// accesses must still be handled as a critical section, due to the ambigious
// LCD addressing scheme.
void timer2_isr(void) __interrupt (INTR_TIMER2)
{
  uint8_t lcd_addr;

  TF2 = 0; // clear flag

  if (clock_run && (CLOCK_CTL == CLOCK_CTL_ON)) {
    clock_ticks++;

    // Each tick is 50ms, 20 ticks = 1s
    if (clock_ticks >= 20) {
      clock_ticks = 0;
      clock_secs++;
    }

    // Minutes and seconds are two 8-bit binary-coded decimals
    if ((clock_secs&0x0f) == 0x0A) {
      clock_secs &= 0xf0; // clear 1s digit
      clock_secs += 0x10; // increase 10s digit
    }
    if ((clock_secs&0xf0) == 0x60) {
      clock_secs = 0; // reset
      clock_mins++;
    }
    if ((clock_mins&0x0f) == 0x0A) {
      clock_mins &= 0xf0; // clear 1s digit
      clock_mins += 0x10; // increase 10s digit
    }
    if ((clock_mins&0xf0) == 0xA0) {
      clock_mins = 0; // reset
    }

    // Print human-readable time to bottom right of LCD
    if( (clock_ticks & 0x01) == 0 ) {
      lcd_addr = lcd_getaddr();  // save LCD address before changing
      lcd_gotoxy(3,3);
      lcd_putstr("Time: ");
      lcd_putchar('0' + (clock_mins>>4));
      lcd_putchar('0' + (clock_mins&0xf));
      lcd_putchar(':');
      lcd_putchar('0' + (clock_secs>>4));
      lcd_putchar('0' + (clock_secs&0xf));
      lcd_putchar('.');
      lcd_putchar('0' + (clock_ticks>>1));
      lcd_gotoaddr(lcd_addr);  // restore LCD address before returning
    }
  }
}


// Function: int0_isr
//
// External INT0 interrupt service routine.
//
// The interrupt is generated when the I/O expander detects a change in
// inputs. The button pin is rechecked and used to set the appropriate LED pin
// state.
void int0_isr(void) __interrupt (INTR_EXT0)
{
  // flag is automatically cleared by hardware

  // button: high = not pressed, low = pressed
  // LED   : high = off, low = on
  io_exp_write_pin(IO_EXP_LED, io_exp_read_pin(IO_EXP_BUTTON));
}

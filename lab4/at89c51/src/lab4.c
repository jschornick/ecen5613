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
#include "lcd.h"
#include "eeprom.h"

// Use a printf implementation that handles hex field spacing properly
#define printf printf

void dump_ddram(void)
{
  uint8_t i;

  printf("\r\nLCD DDRAM:\r\n");
  printf("----------");

  lcd_gotoaddr(0x0);
  for(i=0; i<128; i++) {
    if ((i & 0xf) == 0) {
      printf("\r\n");
      printf("%02x:", i);
    }
    lcd_busywait();
    printf(" %02x", LCD_DATA_RD);
  }
  printf("\r\n");
}

void dump_cgram(void)
{
  uint8_t i;

  printf("\r\nLCD CGRAM:\r\n");
  printf("----------");

  lcd_busywait();
  LCD_CMD = LCD_CMD_CGRAM; // goto CGRAM addr 0

  for(i=0; i<64; i++) {
    if ((i & 0xf) == 0) {
      printf("\r\n");
      printf("%02x:", i);
    }
    lcd_busywait();
    printf(" %02x", LCD_DATA_RD);
  }
  printf("\r\n");
}

// Function: main
//
// ...
void main()
{
  uint8_t data;
  uint16_t i = 0;

  serial_init_brg();
  printf("\r\nWelcome!\r\n");

  printf("Performing eeprom write/read... ");
  eeprom_write(0,0x42,0x23);
  //printf("done\r\n");
  //printf("Performing eeprom write... ");
  data = 0;
  while( eeprom_busy() ) {i++; };
  eeprom_read(0,0x42,&data);
  printf("got: %02x after %u NACKs\r\n", data, i);

  printf("Initializing LCD... ");
  lcd_init();
  printf("done!\r\n");

  lcd_putch('x');
  lcd_putstr("Hello cruel word!");

  dump_ddram();
  dump_cgram();

  while(1) {
    data = LCD_DATA_RD;
  };
}

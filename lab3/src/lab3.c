// File       : lab3.c
// Author     : Jeff Schornick
//
// Implements the required functionality for ECEN5613 Lab 3.
//
// Specifically, ...
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Attribution for leveraged code...

#include <at89c51ed2.h>
#include <stdio.h>  // printf_tiny
#include <stdlib.h> // malloc
#include <stdint.h>
#include "serial.h"
#include "paulmon.h"

#define MAIN_BUF_MIN 32
#define MAIN_BUF_MAX 2800

#define NEW_BUF_MIN 20
#define NEW_BUF_MAX 400

#define printf printf_tiny

#ifdef PAULMON
__code __at (PM_HEADER_ADDR) uint8_t paulmon_header[] = {
  PM_SIGNATURE,
  PM_TYPE_PROGRAM,255,0,0,
  PM_RESERVED,
  PM_NO_CHECKSUM };

__code __at (PM_NAME_ADDR) char paulmon_name[] = "Lab #3";
#endif /* PAULMON */


// TODO: convert to read_range?
uint16_t read_uint16()
{
  uint16_t val = 0;
  uint16_t new_val;
  char c;

  while(1) {
    c = getchar();
    if (c == '\r') {
      break;
    }
    if ( (c >= '0') && (c <= '9') ) {
      putchar(c);
      new_val = (val*10) + (c - '0');
      if( new_val < val ) {
        return 0xFFFF; // input overflow, return max
      }
      val = new_val;
    }
  }
  printf("\r\n");
  return val;
}

void main() {

  uint16_t buf_size = 0;

  serial_init();

  printf("\n\rWelcome to Lab #3!\n\r");

  while( buf_size == 0 ) {
    printf("\n\rEnter a buffer size in bytes (%u-%u), divisible by 16: ", MAIN_BUF_MIN, MAIN_BUF_MAX);
    buf_size = read_uint16();
    if( (buf_size < MAIN_BUF_MIN) || (buf_size > MAIN_BUF_MAX) ) {
      printf("Buffer size %u out of range!\r\n", buf_size);
      buf_size = 0;
    }
    if( buf_size & 0xF ) {
      printf("Buffer size must be divisible by 16!\r\n");
      buf_size = 0;
    }
  }

  printf("\r\nHorray!\r\n");

}

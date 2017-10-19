// File       : lab3.c
// Author     : Jeff Schornick
//
// Implements the required functionality for ECEN5613 Lab 3.
//
// Specifically, ...
//
// Compilation: Supports SDCC v3.6+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Attribution for leveraged code...

#include <at89c51ed2.h>
#include <stdio.h>  // printf_tiny
#include <stdlib.h> // malloc
#include <string.h> // memset
#include <stdint.h>
#include "serial.h"
#include "paulmon.h"

#define MAIN_BUF_MIN 32
#define MAIN_BUF_MAX 2800

#define NEW_BUF_MIN 20
#define NEW_BUF_MAX 400

// Determine the upper limit on the number of buffers based on the heap size
// and the smallest allowed buffer sizes.
#define MAX_BUFFERS ( (HEAP_SIZE - (2 * MAIN_BUF_MIN)) / NEW_BUF_MIN )

// Need printf with hexadecimal field width support
//#define printf printf_fast
#define printf printf

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


extern __xdata char __sdcc_heap;

// Array of buffer pointers to track all possible buffers
__xdata void * __xdata buffer[MAX_BUFFERS] = {0};
__xdata uint16_t buffer_size[MAX_BUFFERS] = {0};
uint16_t next_buffer = 0;

void print_buffer_stats()
{
  uint16_t i;

  printf("\n\rHeap and buffer statistics\n\r");
  printf("--------------------------\n\r");
  printf("\n\rHeap size : %u bytes\n\r", HEAP_SIZE);
  printf("Heap start: 0x%04x\n\r", __sdcc_heap);
  printf("Heap end  : 0x%04x\n\r", __sdcc_heap + HEAP_SIZE - 1);

  printf("\r\n Buffer # |  Size |  Start |    End |  Chars |  Free");
  printf("\r\n----------+-------+--------+--------+--------+-------\r\n");
  for(i = 0; i<MAX_BUFFERS; i++) {
    if (buffer[i] != 0) {
      printf("      %3u | %5u | 0x%04x | 0x%04x |  %5u | %5u\r\n", i, buffer_size[i], (uint16_t) buffer[i], (uint16_t)buffer[i] + buffer_size[i] - 1, 0, 0);
    }
  }

  printf("\r\nStorage characters since last report: \r\n");

  printf("\r\nStored characters:\r\n");

  // empty buffers
}


uint8_t new_buffer(uint16_t buf_size)
{
  buffer[next_buffer] = malloc(buf_size);
  if( buffer[next_buffer] == NULL ) {
    printf("\r\nCouldn't allocate buffer %u!\r\n", next_buffer);
    return 0;
  }
  buffer_size[next_buffer] = buf_size;
  next_buffer++;
  return 1;
}


void main()
{
  uint16_t buf_size = 0;
  char c;

  serial_init();

  printf("\n\rWelcome to Lab #3!\n\r");

  printf("\n\rHEAP_SIZE = %u bytes\n\r", HEAP_SIZE);

  // Initialize all buffer pointers to NULL
  //memset(buffer, 0, MAX_BUFFERS * sizeof(*buffer) );

  while( !buffer[1] ) {
    buf_size = 0;
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

    printf("Main buffer size is: %u\r\n", buf_size);

    buffer[0] = malloc(buf_size);
    if( buffer[0] == NULL ) {
      printf("\r\nCouldn't allocate buffer 0!\r\n");
      continue;
    }
    buffer_size[0] = buf_size;

    buffer[1] = malloc(buf_size);
    if( buffer[1] == NULL ) {
      printf("\r\nCouldn't allocate buffer 1!\r\n");
      free(buffer[0]);
      buffer[0] = 0;
    }
    buffer_size[1] = buf_size;
    next_buffer = 2;
  }

  printf("\r\nPrimary buffers (0 and 1) successfully allocated\r\n");

  print_buffer_stats();

  while(1) {
    c = getchar();
    if(c == '+') {
      printf("\n\rEnter a buffer size in bytes (%u-%u): ", NEW_BUF_MIN, NEW_BUF_MAX);
      buf_size = read_uint16();
      new_buffer(buf_size);
    }
    if(c == '?') {
      print_buffer_stats();
    }
  }

}

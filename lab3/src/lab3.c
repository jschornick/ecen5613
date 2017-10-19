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

extern __xdata char __sdcc_heap;

// Array of buffer pointers to track all possible buffers
__xdata void * __xdata buffer[MAX_BUFFERS] = {0};
// Also track all buffer sizes
__xdata uint16_t buffer_size[MAX_BUFFERS] = {0};
uint16_t next_buffer = 0;

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



uint8_t new_buffer(uint16_t buf_size)
{
  buffer[next_buffer] = malloc(buf_size);
  if( buffer[next_buffer] == NULL ) {
    return 0;
  }
  buffer_size[next_buffer] = buf_size;
  next_buffer++;
  return 1;
}

uint16_t read_size(uint16_t min, uint16_t max)
{
  uint16_t val = 0;
  uint16_t new_val;
  char c;

  while ((val < min) || (val > max)) {
    printf("\n\rEnter buffer size in bytes (%u-%u): ", min, max);
    while( (c = getchar()) != '\r' ) {
      if ( (c >= '0') && (c <= '9') ) {
        putchar(c);
        new_val = (val*10) + (c - '0');
        // check for overflow
        if( new_val < val ) {
          val =  0xFFFF;
          break;
        }
        val = new_val;
      }
    }
    // Received EOL, verify value
    if (val < min) {
      printf("Buffer size is too small!\r\n");
      val = 0;
    } else if (val > max) {
      printf("Buffer size is too large!\r\n");
      val = 0;
    }
  }
  return val;
}


void init_storage_buffers(void)
{
  uint16_t buf_size;
  //printf("\n\rCreating primary buffers...\r\n");
  buf_size = read_size(MAIN_BUF_MIN, MAIN_BUF_MAX);
  if( buf_size & 0xF ) {
    printf("Buffer size must be divisible by 16!\r\n");
    return;
  }

  printf("Selected buffer size is: %u\r\n", buf_size);

  new_buffer(buf_size);
  if( buffer[0] == NULL ) {
    printf("\r\nUnable to allocate storage buffer 0 with size %u!\r\n", buf_size);
    return;
  }

  new_buffer(buf_size);
  if( buffer[1] == NULL ) {
    printf("\r\nUnable to allocate two storage buffers with size %u!\r\n", buf_size);
    free(buffer[0]);
    next_buffer = 0;
    return;
  }

  printf("\r\nPrimary buffers (0 and 1) successfully allocated.\r\n");
}

void cmd_report()
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


void cmd_add(void) {
  uint16_t buf_size;
  printf("\n\rEnter a buffer size in bytes (%u-%u): ", NEW_BUF_MIN, NEW_BUF_MAX);
  buf_size = read_size(NEW_BUF_MIN, NEW_BUF_MAX);
  if( (buf_size < NEW_BUF_MIN) || (buf_size > NEW_BUF_MAX) ) {
    printf("Buffer size %u is out of range!\r\n", buf_size);
  } else if( !new_buffer(buf_size) ) {
    printf("Unable to allocate buffer of %u bytes.", buf_size);
  } else {
    printf("Added new buffer # %u, size %u bytes at address 0x%04x.", next_buffer-1, buf_size, buffer[next_buffer-1]);
  }
}

void cmd_reset()
{
  uint16_t i;
  printf("Freeing all buffers...");
  for(i = 0; i<next_buffer; i++) {
    if (buffer[i] != 0) {
      free(buffer[i]);
      buffer[i] = 0;
    }
  }
  next_buffer = 0;
}

void cmd_del()
{}

void cmd_show()
{}

#define KEY_ADD    '+'
#define KEY_DEL    '-'
#define KEY_REPORT '?'
#define KEY_SHOW   '='
#define KEY_RESET  '@'

void display_menu(void)
{
  printf("\r\n=== BufferMaster 3000 Menu ===\r\n\r\n");
  printf("  %c - Add a new buffer\r\n", KEY_ADD);
  printf("  %c - Delete a buffer\r\n", KEY_DEL);
  printf("  %c - Buffer report and storage clear\r\n", KEY_REPORT);
  printf("  %c - Storage buffer contents\r\n", KEY_SHOW);
  printf("  %c - Reset all buffers\n", KEY_RESET);
  printf("\r\n  Otherwise, press capital letters or numbers to store.\r\n");
  printf("-> ");

}

void store_key(char c)
{
  if ((c >= 'A') && (c <= 'Z')) {
    printf("Storing capital...");
  } else if ((c>= '0') && (c <= '9')) {
    printf("Storing number...");
  }
}

uint16_t stored_upper = 0;
uint16_t stored_number = 0;

void main()
{
  uint16_t buf_size = 0;
  char c;

  serial_init();

  printf("\r\n");
  printf("---------------------------------\n\r");
  printf("| Welcome to BufferMaster 3000! |\r\n");
  printf("---------------------------------\r\n");
  printf("\r\n");
  printf("Built on %s (%s)\r\n", BUILD_DATE, GIT_COMMIT);
  printf("Compiled with heap size %u bytes\n\r", HEAP_SIZE);
  printf("\r\n");

  while(1) {
    while (!next_buffer) {
      init_storage_buffers();
      if (next_buffer) {
        display_menu();
      }
    }

    c = getchar();
    putchar(c);

    switch(c) {
    case KEY_ADD:
      cmd_add();
      display_menu();
      break;
    case KEY_DEL:
      cmd_del();
      display_menu();
      break;
    case KEY_REPORT:
      cmd_report();
      display_menu();
      break;
    case KEY_SHOW:
      cmd_show();
      display_menu();
      break;
    case KEY_RESET:
      cmd_reset();
      break;
    default:
      store_key(c);
      break;
    }
  }

}

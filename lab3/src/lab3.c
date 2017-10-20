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

//#include <at89c51ed2.h>
#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <string.h> // memset
#include <stdint.h>
#include "serial.h"
#include "debug.h"

// Command key definitions
#define KEY_ADD    '+'
#define KEY_DEL    '-'
#define KEY_REPORT '?'
#define KEY_SHOW   '='
#define KEY_RESET  '@'

// Define the valid size range for storage buffers
#define MAIN_BUF_MIN 32
#define MAIN_BUF_MAX 2800

// Define the valid size range for additional buffers
#define NEW_BUF_MIN 20
#define NEW_BUF_MAX 400

// Determine the upper limit on the number of buffers based on the heap size
// and the smallest allowed buffer sizes.
#define MAX_BUFFERS ( (HEAP_SIZE - (2 * MAIN_BUF_MIN)) / NEW_BUF_MIN )

// SDCC's heap pointer, linked from heap.c
extern __xdata char __sdcc_heap[];

// Arrays to track all buffer pointers and sizes
__xdata char * buffer[MAX_BUFFERS];
__xdata uint16_t buffer_size[MAX_BUFFERS];

uint16_t next_buffer;     // Number of the next buffer to create
uint16_t stored_capitals; // Count of stored capital characters
uint16_t stored_numbers;  // Count of stored numeric characters
uint16_t total_chars;     // Count of all characters received between reports

// Use a printf with hexadecimal field width support
#define printf printf


// Attempt to dynamically create a new buffer of the specified size.
// Returns 1 on success, 0 if allocation fails.
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

uint16_t read_uint16(void) {
  uint16_t val = 0;
  uint16_t new_val;
  char c;
  while( (c = getchar()) != '\r' ) {
    if ( (c >= '0') && (c <= '9') ) {
      putchar(c);
      new_val = (val*10) + (c - '0');
      // check for overflow
      if( new_val < val ) {
        return 0xFFFF;
      }
      val = new_val;
    }
  }
  return val;
}

uint16_t read_size(uint16_t min, uint16_t max)
{
  uint16_t size = 0;

  while ((size < min) || (size > max)) {
    printf("\n\rEnter buffer size in bytes (%u-%u): ", min, max);
    size = read_uint16();
    if (size < min) {
      printf("\r\nBuffer size is too small!\r\n");
      size = 0;
    } else if (size > max) {
      printf("\r\nBuffer size is too large!\r\n");
      size = 0;
    }
  }
  return size;
}


void init_storage_buffers(void)
{
  uint16_t buf_size;
  //printf("\n\rCreating primary buffers...\r\n");
  buf_size = read_size(MAIN_BUF_MIN, MAIN_BUF_MAX);
  if( buf_size & 0xF ) {
    printf("\r\nBuffer size must be divisible by 16!\r\n");
    return;
  }

  //printf("Selected buffer size is: %u\r\n", buf_size);

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

  printf("\r\nStorage buffers (0 and 1) successfully allocated with %u bytes each.\r\n", buf_size);
}

void dump_buffer(uint16_t buf_num, uint16_t count)
{
  uint16_t i;
  printf("\r\nBuffer #%u\r\n", buf_num);
  printf("----------");
  for(i=0; i<count; i++) {
    if ((i & 0x3f) == 0) {
      printf("\r\n");
    }
    printf("%c", *(buffer[buf_num] + i));
  }
  printf("\r\n");
}

void dump_buffer_hex(uint16_t buf_num, uint16_t count)
{
  uint16_t i;
  printf("\r\nBuffer #%u\r\n", buf_num);
  printf("----------");
  for(i=0; i<count; i++) {
    if ((i & 0xf) == 0) {
      printf("\r\n");
      printf("%04x:", (uint16_t) buffer[buf_num] + i);
    }
    printf(" %02x", *(buffer[buf_num] + i));
  }
  printf("\r\n");
}

void cmd_report()
{
  uint16_t i;

  printf("\n\rHeap and buffer statistics\n\r");
  printf("--------------------------\n\r");
  printf("\n\r  Heap size : %u bytes\n\r", HEAP_SIZE);
  printf("  Heap start: 0x%04x\n\r", (uint16_t) __sdcc_heap);
  printf("  Heap end  : 0x%04x\n\r", (uint16_t) __sdcc_heap + HEAP_SIZE - 1);
  //printf("Next ptr  : 0x%04x\n\r", *(uint16_t *) __sdcc_heap);

  printf("\r\n Buffer # |  Size |  Start |    End | Chars |  Free");
  printf("\r\n----------+-------+--------+--------+-------+-------\r\n");
  printf("        0 | %5u | 0x%04x | 0x%04x | %5u | %5u\r\n", buffer_size[0], (uint16_t) buffer[0], (uint16_t)buffer[0] + buffer_size[0] - 1, stored_capitals, buffer_size[0] - stored_capitals);
  printf("        1 | %5u | 0x%04x | 0x%04x | %5u | %5u\r\n", buffer_size[1], (uint16_t) buffer[1], (uint16_t)buffer[1] + buffer_size[1] - 1, stored_numbers, buffer_size[1] - stored_numbers);
  for(i = 2; i<MAX_BUFFERS; i++) {
    if (buffer[i] != 0) {
      printf("      %3u | %5u | 0x%04x | 0x%04x |     0 | %5u\r\n", i, buffer_size[i], (uint16_t) buffer[i], (uint16_t)buffer[i] + buffer_size[i] - 1, buffer_size[i]);
    }
  }

  printf("\r\nTotal characters received since last report: %u \r\n", total_chars);

  dump_buffer(0, stored_capitals);
  dump_buffer(1, stored_numbers);

  total_chars = 0;
  stored_capitals = 0;
  stored_numbers = 0;

}


void cmd_add(void) {
  uint16_t buf_size;
  buf_size = read_size(NEW_BUF_MIN, NEW_BUF_MAX);
  if( (buf_size < NEW_BUF_MIN) || (buf_size > NEW_BUF_MAX) ) {
    printf("\r\nBuffer size %u is out of range!\r\n", buf_size);
  } else if( !new_buffer(buf_size) ) {
    printf("\r\nUnable to allocate buffer of %u bytes.\r\n", buf_size);
  } else {
    printf("\r\nAdded buffer #%u, size %u bytes, at address 0x%04x.\r\n", next_buffer-1, buf_size, (uint16_t) buffer[next_buffer-1]);
  }
}

void cmd_reset()
{
  uint16_t i;
  printf("\r\nFreeing all buffers and restarting...\r\n");
  for(i = 0; i<next_buffer; i++) {
    if (buffer[i] != 0) {
      free(buffer[i]);
      buffer[i] = 0;
    }
  }
  next_buffer = 0;
}

void cmd_del()
{
  uint16_t buf_num;
  uint16_t i;
  uint8_t available = 0;

  printf("\r\nAvailable buffers: ");
  for(i = 2; i<next_buffer; i++) {
    if( buffer[i] ) {
      printf("%d ", i);
      available = 1;
    }
  }
  if (!available) {
    printf("NONE\r\n");
    return;
  }

  printf("\r\n");
  printf("\r\nChoose buffer to delete: ");
  buf_num = read_uint16();

  if ( (buf_num >=2) && buffer[buf_num] ) {
    free(buffer[buf_num]);
    buffer[buf_num] = 0;
    printf("\r\nFreed buffer #%d.\r\n", buf_num);
  } else {
    printf("\r\nInvalid buffer choice.\r\n");
  }
}

void cmd_show()
{
  dump_buffer_hex(0, stored_capitals);
  dump_buffer_hex(1, stored_numbers);
}

void display_menu(void)
{
  printf("\r\n=== BuffMaster 3000 Menu ===\r\n\r\n");
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
    if(stored_capitals < buffer_size[0]) {
      *(buffer[0] + stored_capitals) = c;
      stored_capitals++;
    }
  } else if ((c>= '0') && (c <= '9')) {
    if(stored_numbers < buffer_size[1]) {
      *(buffer[1] + stored_numbers) = c;
      stored_numbers++;
    }
  }
}

void main()
{
  char c;
  next_buffer = 0;
  stored_capitals = 0;
  stored_numbers = 0;
  total_chars = 0;

  DEBUGPORT(0x23);

  memset(buffer, 0, sizeof(__xdata void *));
  //memset(buffer_size, 0, sizeof(uint16_t));

  #ifndef PAULMON
  serial_init();
  #endif

  printf("\r\n");
  printf("-------------------------------\n\r");
  printf("| Welcome to BuffMaster 3000! |\r\n");
  printf("-------------------------------\r\n");
  printf("\r\n");
  printf("Built on %s (%s)\r\n", BUILD_DATE, GIT_COMMIT);
  printf("Compiled with heap size %u bytes\n\r", HEAP_SIZE);
  printf("\r\n");

  while(1) {
    DP_INFO(0x42);
    while (!next_buffer) {
      init_storage_buffers();
      if (next_buffer) {
        display_menu();
      }
    }

    c = getchar();
    total_chars++;
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

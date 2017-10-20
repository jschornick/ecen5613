// File       : lab3.c
// Author     : Jeff Schornick
//
// Implements the required functionality for ECEN5613 Lab 3.
//
// Specifically, Lab 3 presents an interactive interface to manage dynamic
// buffers created on the heap. Two reserved buffers also record statistics
// about data received over the serial port.
//
// Compilation: Supports SDCC v3.6+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <string.h> // memset
#include <stdint.h>
#include "serial.h"
#include "debug.h"

// Command key definitions for the menu
#define KEY_ADD    '+'  // Add a buffer command
#define KEY_DEL    '-'  // Delete a buffer
#define KEY_REPORT '?'  // Heap report and empty storage
#define KEY_SHOW   '='  // Storage contents in hex
#define KEY_RESET  '@'  // Reset all buffers

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

// Place frequently accessed counters in faster IRAM.
// Leaving these in XRAM makes the mainloop slow enough to miss characters
// when reading from serial.
__data uint16_t stored_capitals; // Count of stored capital characters
__data uint16_t stored_numbers;  // Count of stored numeric characters
__data uint16_t total_chars;     // Count of all characters received between reports
__data uint16_t next_buffer;     // Number of the next buffer to create

// Use a printf with hexadecimal field width support
// Can be redefined to use a faster/smaller printf (e.g. printf_tiny)
#define printf printf


// Function: new_buffer
//
// Attempt to dynamically create a new buffer of the specified size
// on the heap.
//
// Inputs : buf_size, the size of the newbuffer to allocate
// Returns: 1 on success, 0 if allocation fails.
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

// Function: read_uint16
//
// Reads a 16-bit unsigned value from the serial port. Non-numeric inputs are
// ignored, and overflow is handled by returning a maximum value.
//
// Returns: A 16-bit value read from serial or 0xFFFF on overflow
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

// Function: read_size
//
// Attempts to read a buffer size from the user.
//
// Inputs : min, the minimum buffer size
//          max, the maximum buffer size
// Returns: A value size between min and max, 0 otherwise.
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


// Function: init_storage_buffers
//
// Attempts to create the two required storage buffers buffer[0] and buffer[1],
// based on parameters from the user. The size is limited based on
// MAIN_BUF_MIN and MAIN_BUF_MAX, and a hardcoded restriction on being divisible
// by 16. Either both buffers are created on success or none are allocated.
//
// Returns: Nothing, but the storage buffers are allocated on success.
void init_storage_buffers(void)
{
  uint16_t buf_size;
  buf_size = read_size(MAIN_BUF_MIN, MAIN_BUF_MAX);
  if( buf_size & 0xF ) {
    printf("\r\nBuffer size must be divisible by 16!\r\n");
    return;
  }

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

// Function: dump_buffer
//
// Dumps the ASCII contents of one buffer, max 64 characters per line.
//
// Inputs: buf_num, the buffer to dump
//         count, the number of characters to dump
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

// Function: dump_buffer_hex
//
// Dumps the ASCII contents of one buffer as hex, in the format:
//   AAAA: DD DD DD DD DD DD DD DD DD DD DD DD DD DD DD DD
//   AAAA: DD DD DD DD DD DD DD DD DD DD DD DD DD DD DD DD
// ...where AAAA is the hex address and DD is the hex data.
//
// Inputs: buf_num, the buffer to dump
//         count, the number of characters to dump
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

// Function: cmd_report
//
// Produces a report on the heap configuration and each allocated buffer.
// Dumps the ASCII contents of the storage buffers and resets them to empty.
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

// Function: cmd_add
//
// Queries the user for new buffer paramters and attempts to allocate the requested buffer.
// New buffer size is limited by the NEW_BUF_MIN and NEW_BUF_MAX paramters, as well as the
// space available on the heap.
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

// Function: cmd_reset
//
// Frees all buffers on the heap (including storage), forcing the program to restart.
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

// Function: cmd_del
//
// Presents the user with a list of buffers and attempts to remove the selected
// buffer by number. Deleted buffers will have their space deallocated from the
// heap. Storage buffers cannot be deleted this way.
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

// Function: cmd_show
//
// Shows the contents of the storage buffers in hexadecimal.
void cmd_show()
{
  dump_buffer_hex(0, stored_capitals);
  dump_buffer_hex(1, stored_numbers);
}

// Function: display_menu
//
// Presents the user a simple menu of commands to choose from.
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

// Function: store_key
//
// Filters a character previously input by the user into the storage buffers.
// Capital letters are stored in buffer[0].
// Numbers are stored in buffer[1].
// All other characters are ignored.
//
// If the respecteive buffer is out of space, the character is not stored.
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

// Function: main
//
// Initializes the system by clearing all buffer pointers and reseting all counters.
//
// After initialization, the main loop runs interactively, reading and
// responding to user input. Commands are executed in response to a predefined
// list of command characters. All other charactesr are considered for storage.
void main()
{
  __data char c;
  next_buffer = 0;
  stored_capitals = 0;
  stored_numbers = 0;
  total_chars = 0;

  DEBUGPORT(0x23);

  memset(buffer, 0, sizeof(__xdata void *));

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

    // If storage buffers haven't been successfully initialized (or reset),
    // attempt to intialize them.
    while (!next_buffer) {
      init_storage_buffers();
      // Display a menu once initialization succeeds.
      if (next_buffer) {
        display_menu();
      }
    }

    // Get a character from the user and echo it back.
    c = getchar();
    total_chars++;
    putchar(c);

    DP_INFO(0xAA);
    DP_INFO(c);

    // Launch a command based on the received character, or consider it for
    // storage.
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

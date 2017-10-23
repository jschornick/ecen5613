// File       : lab3_sup.c
// Author     : Jeff Schornick
//
// Implements the supplemental functionality for ECEN5613 Lab 3.
//
// Specifically, ...
//
// Compilation: Supports SDCC v3.6+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

// TODO: Watchdog, alt PCA mode

#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <string.h> // memset
#include <stdint.h>
#include "serial.h"

// Use a compact printf implementation
#define printf printf_tiny

#define KEY_RUN 'R'
#define KEY_STOP 'S'
#define KEY_MIN '-'
#define KEY_MAX '+'
#define KEY_IDLE 'I'
#define KEY_POWER 'P'


// Function: display_menu
//
// Presents the user a simple menu of commands to choose from.
void display_menu(void)
{
  printf("\r\n=== PCA Menu ===\r\n\r\n");
  printf("  %c - Start the PWM\r\n", KEY_RUN);
  printf("  %c - Stop the PWM\r\n", KEY_STOP);
  printf("  %c - Set minimum F_CLK frequency\r\n", KEY_MIN);
  printf("  %c - Set maximum F_CLK frequency\r\n", KEY_MAX);
  printf("  %c - Enter Idle mode\r\n", KEY_IDLE);
  printf("  %c - Enter Power Down mode\r\n", KEY_POWER);
  printf("-> ");
}


// Function: cmd_run_pwm
void cmd_run_pwm()
{
}

// Function: cmd_stop_pwm
void cmd_stop_pwm()
{
}

// Function: cmd_min_freq
void cmd_min_freq()
{
}

// Function: cmd_max_freq
void cmd_max_freq()
{
}

// Function: cmd_idle
void cmd_idle()
{
}

// Function: cmd_power_down
void cmd_power_down()
{
}


// Function: main
//
// ...
void main()
{
  __data char c;

  #ifndef PAULMON
  serial_init();
  #endif

  printf("\r\n");
  printf("-------------------------------\n\r");
  printf("| Welcome to the PCA Tester!  |\r\n");
  printf("-------------------------------\r\n");
  printf("\r\n");
  printf("Built on %s (%s)\r\n", BUILD_DATE, GIT_COMMIT);
  printf("Compiled with heap size %u bytes\n\r", HEAP_SIZE);
  printf("\r\n");

  display_menu();

  while(1) {

    // Get a character from the user and echo it back.
    c = getchar();
    putchar(c);

    // Launch a command based on the received character
    switch(c) {
    case KEY_RUN:
      cmd_run_pwm();
      display_menu();
      break;
    case KEY_STOP:
      cmd_stop_pwm();
      display_menu();
      break;
    case KEY_MIN:
      cmd_min_freq();
      display_menu();
      break;
    case KEY_MAX:
      cmd_max_freq();
      display_menu();
      break;
    case KEY_IDLE:
      cmd_idle();
      display_menu();
      break;
    case KEY_POWER:
      cmd_power_down();
      display_menu();
      break;
    default:
      break;
    }
  }

}

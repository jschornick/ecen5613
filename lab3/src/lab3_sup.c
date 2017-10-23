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
#include "pca.h"

// Use a printf implementation with long support
#define printf printf_fast

#define KEY_RUN 'r'
#define KEY_STOP 's'
#define KEY_MIN '-'
#define KEY_MAX '+'
#define KEY_IDLE 'i'
#define KEY_POWER 'p'

#define F_OSC 11059200UL
#define F_PERIPH_MIN (F_OSC / 1020)
#define F_PERIPH_MAX (F_OSC / 2)

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
  printf("  %c - Idle mode\r\n", KEY_IDLE);
  printf("  %c - Power Down mode\r\n", KEY_POWER);
}


// Function: cmd_run_pwm
void cmd_run_pwm()
{
  // Set module 0 PWM to a 70% duty cycle
  CCAP0H = DUTY_CYCLE(70);
  // Run module 0 in PWM mode
  CCAPM0 = CCAPM_PWM_MODE;
  printf("\r\nPWM enabled on CEX0 (P1.3)\r\n");
}

// Function: cmd_stop_pwm
void cmd_stop_pwm()
{
  CCAPM0 = CCAPM_NO_OPERATION;
  printf("\r\nPWM disabled\r\n");
}

// Function: cmd_min_freq
void cmd_min_freq()
{
  // F_CPU = F_PERIPH = F_OSC/(4x(255-CKRL))
  //                  = F_OSC/1020
  printf("\r\nSetting CPU/peripheral clock to %lu Hz...\r\n", F_PERIPH_MIN);
  printf("PCA clock (w/FDIV2) = %lu Hz\r\n", F_PERIPH_MIN/2);
  printf("PWM frequency (F_PCA/256) = %lu Hz\r\n", F_PERIPH_MIN/(512));
  printf("\r\nBaud rate will be 75! ");
  CKRL = 0x00;
  BRL = 247;
  //RCAP2L = 247;
}

// Function: cmd_max_freq
void cmd_max_freq()
{
  // F_CPU = F_PERIPH = F_OSC/2
  printf("\r\nSetting CPU/peripheral clock to %lu Hz...\r\n", F_PERIPH_MAX);
  printf("PCA clock (w/FDIV2) = %lu Hz\r\n", F_PERIPH_MAX/2);
  printf("PWM frequency (F_PCA/256) = %lu Hz\r\n", F_PERIPH_MAX/(512));
  printf("\r\nBaud rate will be 57600! ");
  CKRL = 0xFF;
  BRL = BRL_57600_BAUD;
  //RCAP2L = RCAPL_57600_BAUD;
}

// Function: cmd_idle
void cmd_idle()
{
}

// Function: cmd_power_down
void cmd_power_down()
{
}

// Funciton: init_pca
void init_pca()
{
  // Run during idle with the peripheral clock/2 as a source
  CMOD = CMOD_CIDL_RUN | CMOD_CPS_FDIV2 | CMOD_WDTE_WDOFF;

  // Module 0 initially disabled
  CCAPM0 = CCAPM_NO_OPERATION;

  // Turn on PCA
  CR = CCON_CR_PCA_ON;

}


// Function: main
//
// ...
void main()
{
  __data char c;

  #ifndef PAULMON
  //serial_init_t1();
  serial_init_brg();
  //serial_init_t2();
  #endif

  printf("\r\n");
  printf("-------------------------------\n\r");
  printf("| Welcome to the PCA Tester!  |\r\n");
  printf("-------------------------------\r\n");
  printf("\r\n");
  printf("Built on %s (%s)\r\n", BUILD_DATE, GIT_COMMIT);
  printf("Compiled with heap size %u bytes\n\r", HEAP_SIZE);
  printf("\r\n");

  init_pca();

  display_menu();

  while(1) {

    printf("-> ");
    // Get a character from the user and echo it back.
    c = getchar();
    //putchar(c);

    // Launch a command based on the received character
    switch(c) {
    case KEY_RUN:
      cmd_run_pwm();
      break;
    case KEY_STOP:
      cmd_stop_pwm();
      break;
    case KEY_MIN:
      cmd_min_freq();
      break;
    case KEY_MAX:
      cmd_max_freq();
      break;
    case KEY_IDLE:
      cmd_idle();
      break;
    case KEY_POWER:
      cmd_power_down();
      break;
    default:
      display_menu();
      break;
    }
  }

}

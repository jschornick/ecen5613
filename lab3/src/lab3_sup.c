// File       : lab3_sup.c
// Author     : Jeff Schornick
//
// Implements the supplemental functionality for ECEN5613 Lab 3.
//
// Specifically, ...
//
// Compilation: Supports SDCC v3.6+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

// TODO: additional PCA mode?

#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <string.h> // memset
#include <stdint.h>
#include "at89c51rc2.h"
#include "clock.h"
#include "serial.h"
#include "pca.h"

// Use a printf implementation with long support
#define printf printf_fast

#define KEY_RUN      'P'
#define KEY_STOP     'p'
#define KEY_MIN      'f'
#define KEY_MAX      'F'
#define KEY_WD_ON    'W'
#define KEY_WD_OFF   'w'
#define KEY_FEED_ON  'D'
#define KEY_FEED_OFF 'd'
#define KEY_IDLE     'z'
#define KEY_POWER    'x'

#define F_PERIPH_MIN (F_OSC / 1020)
#define F_PERIPH_MAX (F_OSC / 2)

uint32_t freq = F_PERIPH_MAX;
__data uint8_t feed_dog = 0;

// Function: display_menu
//
// Presents the user a simple menu of commands to choose from.
void display_menu(void)
{
  printf("\r\n=== PCA Menu ===\r\n\r\n");
  printf(" %c/%c - Start/Stop the PWM\r\n", KEY_RUN, KEY_STOP);
  printf(" %c/%c - Set max/min F_periph\r\n", KEY_MAX, KEY_MIN);
  printf(" %c/%c - Enable/disable PCA watchdog\r\n", KEY_WD_ON, KEY_WD_OFF);
  printf(" %c/%c - Enable/disable dog feeding\r\n", KEY_FEED_ON, KEY_FEED_OFF);
  printf("  %c  - Idle mode\r\n", KEY_IDLE);
  printf("  %c  - Power Down mode\r\n", KEY_POWER);
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
  printf("\r\nBaud rate will be 75!\r\n ");
  CKRL = 0x00;
  freq = F_PERIPH_MIN;
  // Reconfigure for the fastest baud rate at this frequency... 75 baud!
  BRL = BRL(75,F_PERIPH_MIN);
}

// Function: cmd_max_freq
void cmd_max_freq()
{
  // F_CPU = F_PERIPH = F_OSC/2
  printf("\r\nSetting CPU/peripheral clock to %lu Hz...\r\n", F_PERIPH_MAX);
  printf("PCA clock (w/FDIV2) = %lu Hz\r\n", F_PERIPH_MAX/2);
  printf("PWM frequency (F_PCA/256) = %lu Hz\r\n", F_PERIPH_MAX/(512));
  printf("\r\nBaud rate will be 57600!\r\n ");
  CKRL = 0xFF;
  freq = F_PERIPH_MAX;
  // Frequency is high enough to support a baud rate for 57.6k
  BRL = BRL(57600,F_PERIPH_MAX);
}

//Function: cmd_watchdog_on
void cmd_watchdog_on()
{
  printf("\r\nEnabling PCA watchdog timer\r\n");
  CCAP4L = 0xFF;
  CCAP4H = 0xFF;
  CCAPM4 = CCAPM_WATCHDOG_MODE;
  CMOD |= CMOD_WDTE_WDON;
}

//Function: cmd_watchdog_off
void cmd_watchdog_off()
{
  //CCAPM4 = CCAPM_NO_OPERATION;
  CMOD &= ~WDTE;
  printf("\r\nPCA watchdog timer disabled\r\n");
}

// Function: cmd_idle
void cmd_idle()
{
  printf("\r\nEntering idle mode.\r\n");
  printf("\r\nPress a key to wake...");
  while(!TI); // wait for transmit to finish
  TI = 0;     // clear flag to avoid tripping interrupt early

  P1_2 = 1; // led off
  ES = 1;   // enable serial interrupts
  PCON |= PCON_IDLE_ENABLE;
  RI = 0;  // ignore wake up character
  TI = 1;  // reenable transmitter
  printf(" and we're back!\r\n");
}


//void serial_isr(void) __interrupt (INTR_SERIAL) __using (1)
void serial_isr(void) __interrupt (INTR_SERIAL)
{
  ES = 0; // disable UART interrupts
}


// Function: cmd_power_down
void cmd_power_down()
{
  printf("\r\nPowering down.\r\n");
  while(!TI); // wait for transmit to finish
  P1_2 = 1; // led off
  PCON |= PCON_PDE_ENABLE;
  // Program is now stopped!
  P1_2 = 0; // led on
}

// Function: watchdog_reset
//
// Set the watchdog counter to a value that won't match the PCA counter for
// another full cycle.
void watchdog_reset()
{
  uint16_t new_wd;

  // Calculate a value right before the current PCA counter
  new_wd = ( (uint16_t) (CH << 8) + CL) - 1;

  // Reset the watchdog to this far away value
  CCAP4L = (new_wd & 0xff);
  CCAP4H = (new_wd >> 8);
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

  serial_init_brg();
  EA = 1; // enable interrupts

  printf("\r\n");
  printf("--------------------------------\n\r");
  printf("|  Welcome to the PCA Tester!  |\r\n");
  printf("--------------------------------\r\n");
  printf("\r\n");
  printf("Built on %s (%s)\r\n", BUILD_DATE, GIT_COMMIT);
  printf("\r\n");

  init_pca();

  display_menu();

  while(1) {

    P1_2 = 0; // led on
    printf("-> ");
    do {
      if (feed_dog) {
        watchdog_reset();
      }
    } while( ! (c = getchar_nb()) );
    printf("\r\n");

    // Run a command based on the received character, or display the menu
    // after an invalid selection
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
    case KEY_WD_ON:
      cmd_watchdog_on();
      break;
    case KEY_WD_OFF:
      cmd_watchdog_off();
      break;
    case KEY_FEED_ON:
      printf("Keeping watchdog fed...\r\n");
      feed_dog = 1;
      break;
    case KEY_FEED_OFF:
      printf("No longer feeding watchog...\r\n");
      feed_dog = 0;
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

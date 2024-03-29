// File       : demo.c
// Author     : Jeff Schornick
//
// Lab 3 demo of MSP432 features.
//
// Includes reading buttons via GPIO interrupts, basic timer interrupts,
// GPIO-based LED control, PWM-based control of the RGB LED, and an FIFO-based
// UART driver using interrupts.
//
// Compilation: GCC cross compiler for ARM, v4.9.3+
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdint.h>
#include "uart.h"
#include "msp432p401r.h"

// MSP-EXP432 board layout
//
// P1.0 : LED1+
// P2.0 : LED2_RED+
// P2.1 : LED2_GREEN+
// P2.2 : LED2_BLUE+
//
// P1.1 : S1 : N-O, closed->GND
// P1.4 : S2 : N-O, closed->GND

// Function: timer_init
//
// Initializes two timers, one fast, one slow.
// The fast timer (A0) is configured with a short period to be used for PWM.
// The slow timer (A1) is configured to interrupt every 1 second.
void timer_init(void)
{
  // ACLK = auxillary clock, set to LFXT = 32768 KHz
  // SMCLK =  DCO freq (3MHz)

  // Timer A0, fast clock
  //----------------------

  // Up counting mode (0 -> CCR0)
  TIMER_A0->CTL = TIMER_A_CTL_MC__UP | TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_CLR;

  // Set a short period (in timer ticks) for PWM
  //   ...then the duty cycle can be set as a fraction of this value in CCR[1..3]
  TIMER_A0->CCR[0] = 200;


  // Timer A1, slow clock
  //---------------------

  // Up counting mode (0 -> CCR0)
  TIMER_A1->CTL = TIMER_A_CTL_MC__UP | TIMER_A_CTL_SSEL__ACLK | TIMER_A_CTL_CLR;

  // capture control interrupt enable (CCIFG set when TA0R counts to CCR0)
  TIMER_A1->CCTL[0] |= TIMER_A_CCTLN_CCIE;
  TIMER_A1->CCR[0] = 32767;  // once per second for blink

  // enable interrupt associated with CCR0 match
  __NVIC_EnableIRQ(TA1_0_IRQn);
}

// Function: button_init
//
// Initializes GPIOs attached to the two hardware buttons on the MSP432
// board to trigger an interupt when either button is pressed.
void button_init(void)
{
  P1->DIR &= ~(BIT1 | BIT4); // input
  P1->OUT |= BIT1 | BIT4; // pull up (vs pull down)
  P1->REN |= BIT1 | BIT4; // enable pull up
  P1->IES |= BIT1 | BIT4; // high-to-low edge select
  P1->IE |= BIT1 | BIT4;  // interrupt enabled

  P1->IFG &= ~(BIT1 | BIT4);
  __NVIC_EnableIRQ(PORT1_IRQn);
}


// Function: pwm_init
//
// Initializes the fast timer (A0) to produce PWM signals for the RGB LED.
// Since the LED is not attached to the default outputs, these are remapped
// to pins 2.0-2.2.
void pwm_init(void)
{
  // Remap three of the TA0 outputs to the RGB LED
  PMAP->KEYID = PMAP_KEYID_VAL;
  PMAP->CTL = PMAP_CTL_PRECFG;
  P2MAP->PMAP_REGISTER0 = PMAP_TA0CCR1A;
  P2MAP->PMAP_REGISTER1 = PMAP_TA0CCR2A;
  P2MAP->PMAP_REGISTER2 = PMAP_TA0CCR3A;

  // Select the mapped (timer) module as the GPIO output for each
  P2->SEL0 |= BIT0 | BIT1 | BIT2;
  P2->SEL1 &= ~(BIT0 | BIT1 |BIT2);
  P2->DIR |= BIT0 | BIT1 | BIT2;

  // Use set/reset mode to define a duty cycle for each color
  TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
  TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;
  TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
}

volatile uint8_t S1_FLAG = 0;
volatile uint8_t S2_FLAG = 0;

uint16_t red = 0;
uint16_t green = 0x5555;
uint16_t blue = 0xAAAA;
int16_t speed = 1;

int main(void) {

  // clocks/watchdog configured via SystemInit() on reset (see: system_msp432p401r.c)

  char c;

  P1->DIR |= BIT0; // set LED1 pin as output
  P1->OUT |= BIT0; // turn on immediately

  timer_init();
  button_init();
  pwm_init();
  uart_init();

  __enable_irq();

  uart_putc('\r');
  uart_putc('\n');
  uart_send_str("Exciting message from the UART FIFO!\r\n");
  uart_send_str("Ready to echo characters...\r\n");
  while(1) {
    if(S1_FLAG) {
      speed -= 1;
      uart_putc('-');
      S1_FLAG = 0;
    }
    if(S2_FLAG) {
      speed += 1;
      uart_putc('+');
      S2_FLAG = 0;
    }

    // Cycle the colors one step based on speed setting
    red += speed;
    green += speed;
    blue += speed;

    // Set new color
    //   RGB intensities above 2^15 are aliased to (2^16 - value) to make
    //   a smooth transition when the 16-bit value rolls over
    TIMER_A0->CCR[1] = (red < 1<<15) ? (red >> 11) : (0xffff-red) >> 11;
    TIMER_A0->CCR[2] = (green < 1<<15) ? (green >> 11) : (0xffff-green) >> 11;
    TIMER_A0->CCR[3] = (blue < 1<<15) ? (blue >> 11) : (0xffff-blue) >> 11;

    // Pop received characters off the FIFO and echo back
    if(rx_fifo.count) {
      fifo_pop(&rx_fifo, &c);
      uart_putc(c);
    }

  };
}


// Interrupt handler for timer compare TA1CCR0 (blinker)
void TA1_0_IRQHandler(void)
{
  // reset timer interrupt flag
  TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
  // toggle LED1
  P1->OUT ^= BIT0;
}

// Interrupt handler for Port 1 (buttons)
void PORT1_IRQHandler(void)
{
  // check if it was S1 or S2
  if (P1->IFG & BIT1) {
    // clear interrupt flag
    P1->IFG &= ~BIT1;
    S1_FLAG = 1;
  }
  if (P1->IFG & BIT4) {
    P1->IFG &= ~BIT4;
    S2_FLAG = 1;
  }
}



#include "msp432p401r.h"
#include <stdint.h>

// MSP-EXP432 board
//
// P1.0 : LED1+
// P2.0 : LED2_RED+
// P2.1 : LED2_GREEN+
// P2.2 : LED2_BLUE+
//
// P1.1 : S1 : N-O, closed->GND
// P1.4 : S2 : N-O, closed->GND

volatile uint8_t S1_FLAG = 0;

void timer_init(void)
{
  // Up counting mode (to CCR0)
  // ACLK = auxillary clock, set to LFXT = 32768 KHz
  // SMCLK =  DCO freq (3MHz, too fast)
  TIMER_A0->CTL = TIMER_A_CTL_MC__UP | TIMER_A_CTL_SSEL__ACLK;

  // capture control interrupt enable (CCIFG set when TA0R counts to CCR0)
  TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE;

  TIMER_A0->CCR[0] = 32767;  // once per second

  // enable interrupt associated with CCR0 match
  __NVIC_EnableIRQ(TA0_0_IRQn);
}

void button_init(void)
{
  P1->DIR &= ~BIT1; // input
  P1->OUT |= BIT1; // pull up (vs pull down)
  P1->REN |= BIT1; // enable pull up
  P1->IES |= BIT1; // high-to-low edge select
  P1->IE |= BIT1;  // interrupt enabled

  __NVIC_EnableIRQ(PORT1_IRQn);
}

int main(void) {

  // clocks/watchdog configured via SystemInit() on reset (see: system_msp432p401r.c)

  P1->DIR |= BIT0; // set LED1 pin as output

  P2->DIR |= BIT0 | BIT1 | BIT2 ; // set LED2 pins as output
  P2->OUT &= ~(BIT0|BIT1|BIT2);   // turn off LED2

  typedef enum { COLOR_RED, COLOR_GREEN, COLOR_BLUE } color_t;
  color_t led2_color = COLOR_RED;

  timer_init();
  button_init();

  __enable_irq();

  while (1) {
    if (S1_FLAG) {
      switch (led2_color) {
      case COLOR_RED:
        led2_color = COLOR_GREEN;
        P2->OUT = BIT1;
        break;
      case COLOR_GREEN:
        led2_color = COLOR_BLUE;
        P2->OUT = BIT2;
        break;
      case COLOR_BLUE:
        led2_color = COLOR_RED;
        P2->OUT = BIT0;
        break;
      }
      // debounce here?
      S1_FLAG = 0;
    }
  }
}


// Interrupt hanlder for compare register A0.0 (TA0CCR0)
void TA0_0_IRQHandler(void)
{
  // reset timer interrupt flag
  TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
  // toggle LED1
  P1->OUT ^= BIT0;
}

// Interrupt hanlder for Port 1
void PORT1_IRQHandler(void)
{
  // check if it was S1
  if (P1->IFG & BIT1) {
    // clear interrupt flag
    P1->IFG &= ~BIT1;
    S1_FLAG = 1;
  }
}



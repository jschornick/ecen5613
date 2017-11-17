// File       : demo.c
// Author     : Jeff Schornick
//
// Lab 4 demo of MSP432 features.
//
// Includes reading buttons via GPIO interrupts, basic timer interrupts,
// GPIO-based LED control, PWM-based control of the RGB LED, and an FIFO-based
// UART driver using interrupts.
//
// Also includes a simple ADC/VREF demonstration. By externally connecting
// P5.4(A1) to P5.6(VREF), the ADC can be used to read the various voltages
// produced by the voltage reference.
//
// Compilation: GCC cross compiler for ARM, v4.9.3+
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Attribution: ADC initialization based on code from TI Rersource Explorer
// examples as indicated.

#include <stdint.h>
#include <stdio.h>  // sprintf
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
  //TIMER_A1->CCR[0] = 32767;  // once per second for blink
  TIMER_A1->CCR[0] = 3277;  // ~10 Hz

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
  P1->REN |= BIT1 | BIT4; // enable pulling (up)
  P1->IES |= BIT1 | BIT4; // high-to-low edge select

  P1->IFG &= ~(BIT1 | BIT4);
  P1->IE |= BIT1 | BIT4;  // interrupt enabled

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


#define ADC_MAX 0x3FFF  /* 14-bit mode */
#define ADC_REF 3.3     /* AVCC = VCC = 3.3V */

// Function: adc_initializes
//
// Initializes the ADC in 14-bit single shot mode, reading from external pin A1.
//
// NOTE: Initialization based on TI Resource explorer example mps432p401x_adc14_01
void adc_init(void)
{
  // CTL0_SHP : sample-and-hold: pulse source = sampling timer
  // CTL0_SHT0: sample-and-hold: SHT0_3 = 32 ADC clock cycles
  // CTL0_ON  : ADC will be powered during conversion
  ADC14->CTL0 = ADC14_CTL0_SHT0_3 | ADC14_CTL0_SHP | ADC14_CTL0_ON;

  ADC14->CTL1 = ADC14_CTL1_RES_3;        // 14-bit conversion results

  ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1;  // MEM[0] input = A1, AVCC/AVSS refs
  ADC14->IER0 |= ADC14_IER0_IE0;         // Interrupt on conversion complete

  __NVIC_EnableIRQ(ADC14_IRQn);
}


// REFVSEL: voltage reference select, REFCTL0 [5..4]
#define VREF_1_2   0x0  /* 1.2V  */
#define VREF_1_45  0x1  /* 1.45V */
#define VREF_2_5   0x3  /* 2.5V  */

uint8_t vref_mode;

// Function: set_vref
//
// Sets the voltage reference to a new voltage value
void set_vref(uint8_t mode)
{
  REF_A->CTL0 &= ~(REF_A_CTL0_VSEL_MASK);      // clear existing voltage setting
  REF_A->CTL0 |= (mode<<REF_A_CTL0_VSEL_OFS);  // set new voltage mode
  while (REF_A->CTL0 & REF_A_CTL0_GENBUSY);    // wait until reference is ready
  vref_mode = mode;
}

// Function: vref_init
//
// Initializes the voltage reference on P5.6
void vref_init(void)
{
  // P5.6 analog mode (voltage reference)
  P5->SEL0 |= BIT6;
  P5->SEL1 |= BIT6;

  REF_A->CTL0 |= REF_A_CTL0_ON;   // turn on reference module
  REF_A->CTL0 |= REF_A_CTL0_OUT;  // and output to external pin
  set_vref(VREF_1_2);
}


// Button flags that may be set during GPIO interrupt
volatile uint8_t S1_FLAG;
volatile uint8_t S2_FLAG;

volatile uint16_t heartbeat = 0; // pulsing heartbeat, updated by timer ISR

volatile uint8_t adc_flag = 0;   // adc complete flag, set in ADC ISR
volatile uint16_t adc_val = 0;   // adc reading, set in ADC ISR
char str[20];  // temporary string for float conversions


int main(void) {

  // clocks/watchdog configured via SystemInit() on reset (see: system_msp432p401r.c)

  char c;

  P1->DIR |= BIT0; // set LED1 pin as output
  P1->OUT |= BIT0; // turn on immediately

  timer_init();
  button_init();
  pwm_init();
  uart_init();
  adc_init();
  vref_init();

  __enable_irq();

  // Wake up on exit from ISR
  SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;

  uart_queue_str("\r\nWelcome to the last ECEN5613 Lab!\r\n");

  S1_FLAG = 0;
  S2_FLAG = 0;
  while(1) {
    if(S1_FLAG) {
      uart_queue_str("B1: request ADC conversion\r\n");
      // Enable and start ADC conversion
      ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
      S1_FLAG=0;
    }
    if(S2_FLAG) {
      uart_queue_str("B2: change VREF\r\n");
      switch(vref_mode) {
        case VREF_1_2:
          set_vref(VREF_1_45);
          uart_queue_str("VREF: 1.45V\r\n");
          break;
        case VREF_1_45:
          set_vref(VREF_2_5);
          uart_queue_str("VREF: 2.5V\r\n");
          break;
        case VREF_2_5:
          set_vref(VREF_1_2);
          uart_queue_str("VREF: 1.2V\r\n");
          break;
      }
      S2_FLAG=0;
    }

    if (adc_flag) {
      sprintf(str, "ADC: %u (%0.3fV)\r\n", adc_val, ADC_REF * adc_val / (ADC_MAX+1) );
      uart_queue_str(str);
      adc_flag = 0;
    }

    // Pop received characters off the FIFO and echo back
    while(rx_fifo.count) {
      fifo_pop(&rx_fifo, &c);
      uart_queue(c);
    }

    P1->OUT &= ~BIT0; // turn off
    __sleep();
    P1->OUT |= BIT0; // turn on

  };
}


// Interrupt handler for timer compare TA1CCR0 (blinker)
void TA1_0_IRQHandler(void)
{
  // reset timer interrupt flag
  TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;

  heartbeat += 0x1000;  // intensity change
  // Rescale the linear heartbeat value to rise and fall
  TIMER_A0->CCR[2] = (heartbeat < 1<<15) ? (heartbeat >> 11) : (0xffff-heartbeat) >> 11;
}

// Interrupt handler for Port 1 (buttons)
void PORT1_IRQHandler(void)
{
  // check if it was S1 or S2
  if (P1->IFG & BIT1) {
    P1->IFG &= ~BIT1; // clear interrupt flag
    S1_FLAG = 1;
  }
  if (P1->IFG & BIT4) {
    P1->IFG &= ~BIT4;
    S2_FLAG = 1;
  }
}


// ADC14 interrupt service routine
//
// Read the ADC value, set a flag for the main loop to print the result
void ADC14_IRQHandler(void)
{
  adc_val = ADC14->MEM[0];  // read and clear interrupt
  adc_flag = 1;
}

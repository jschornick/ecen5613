// File       : uart.c
// Author     : Jeff Schornick
//
// MSP432 UART driver using interrupts and a pair of RX/TX buffers.
// The EUSCIA0 device is the UART channeled over USB to the host PC.
//
// Compilation: GCC cross compiler for ARM, v4.9.3+
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include "msp432p401r.h"

// See MSP432P4xx TRM section 22.3.1
void uart_init(void)
{
  // Configure Port 1 pins to select UART module
  // RX : P1.2
  // TX : P1.3
  P1->SEL0 |= BIT2 | BIT3;
  P1->SEL1 &= ~(BIT2 | BIT3);

  // Reset device before configuration
  EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;

  // UART Clock = SMCLK (low-speed subsystem master clock) = 3MHz
  EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SSEL__SMCLK | EUSCI_A_CTLW0_SWRST;

  // Baud rate calculation
  //   See MSP432P4xx TRM section 22.3.10
  //   baud_clock/baud_rate = 3MHz/57600 = 52.0833  > 16 (so use oversampling)
  //   52.083 / 16  = 3.255 -> BRW = 3
  //   3.255-3 * 16 = 4     -> BRF = 4
  // Calculator: http://processors.wiki.ti.com/index.php/USCI_UART_Baud_Rate_Gen_Mode_Selection
  EUSCI_A0->BRW = 3;

  // MCTLW
  //   BRF = 4  (bits 7-4)
  //   BRS = 0  (bits 15-8)
  //   OS16 = 1 (bit0)
  EUSCI_A0->MCTLW = EUSCI_A_MCTLW_OS16 | (4<<EUSCI_A_MCTLW_BRF_OFS);

  // clear reset to enable UART
  EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

  // reset flags (RX=0, TX=1) and enable interrupts
  EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;
  EUSCI_A0->IFG |=  EUSCI_A_IFG_TXIFG;
  //EUSCI_A0->IE |= EUSCI_A_IE_RXIE | EUSCI_A_IE_TXIE;
  EUSCI_A0->IE |= EUSCI_A_IE_RXIE;

  __NVIC_EnableIRQ(EUSCIA0_IRQn);
}

void EUSCIA0_IRQHandler(void)
{
  // FXIFG automatically cleared on read from RXBUF
  // TXIFG automatically cleared on write to TXBUF
  if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG) {
    // Check if the TX buffer is empty first
    while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));

    // Echo the received character back
    EUSCI_A0->TXBUF = EUSCI_A0->RXBUF;
  }
}

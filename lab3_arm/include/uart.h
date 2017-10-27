// File       : uart.h
// Author     : Jeff Schornick
//
// MSP432 UART driver using interrupts and a pair of RX/TX buffers.
// The EUSCIA0 device is the UART channeled over USB to the host PC.
//
// Compilation: GCC cross compiler for ARM, v4.9.3+
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#ifndef __UART_H
#define __UART_H

void uart_init(void);

void EUSCIA0_IRQHandler(void);

#endif /* __UART_H */

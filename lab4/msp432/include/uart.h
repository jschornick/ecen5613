// File       : uart.h
// Author     : Jeff Schornick
//
// MSP432 UART driver using interrupts and a pair of RX/TX buffers.
// The EUSCIA0 device is the UART channeled over USB to the host PC.
//
// Compilation: GCC cross compiler for ARM, v4.9.3+
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include "fifo.h"

#ifndef __UART_H
#define __UART_H

#define UART_FIFO_SIZE 1000

extern fifo_t rx_fifo;
extern fifo_t tx_fifo;

// Function: uart_init
//
// Initializes the EUSCI A0 as a basic UART in 8n1 mode at 57.6K baud.
// Current configuration expectes a processor clock of 3MHz.
//
// Also initializes UART FIFOs for queued transmissions.
//
// See MSP432P4xx TRM section 22.3.1 for details on the initialization routine.
void uart_init(void);

// Function: uart_putc
//
// Send a character out the UART.
void uart_putc(char c);

// Function: uart_send
//
// Queues a character for UART transmission
void uart_queue(char c);

// Function: uart_send
//
// Queues a null-terminated string for UART transmission
void uart_queue_str(char *str);

void EUSCIA0_IRQHandler(void);

#endif /* __UART_H */

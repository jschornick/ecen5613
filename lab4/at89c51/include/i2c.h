// File       : i2c.h
// Author     : Jeff Schornick
//
// Generic I2C function declarations
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#ifndef __I2C_H
#define __I2C_H

#include <stdint.h>
#include "at89c51rc2.h"

// Use two GPIO lines for I2C clock and data
#define I2C_SCL P1_6
#define I2C_SDA P1_7

// I2C LSB determines read/write to address
#define I2C_READ   0x1
#define I2C_WRITE  0x0


// Function: i2c_start
//
// Generate I2C start condition
// High to low transition of SDA when SCL is high
void i2c_start(void);


// Function: i2c_stop
//
// Generate I2C stop condition
// Low to high transition of SDA when SCL is high
void i2c_stop(void);


// Function: i2c_send
//
// Send 8-bits over I2C, MSB first
//
// Returns the ACK/NACK value received as bit 9
uint8_t i2c_send(__data uint8_t data);


// Function: i2c_read
//
// Read 8-bits over I2C, MSB first
void i2c_read(uint8_t *data);


// send an ACK from the master
#define i2c_ack() I2C_SCL = 0; I2C_SDA = 0; I2C_SDA = 1; I2C_SCL = 1

#endif /* __I2C_H */

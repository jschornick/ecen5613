// File       : i2c.h
// Author     : Jeff Schornick
//
// Generic I2C function declarations
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#ifndef __I2C_H
#define __I2C_H

#include "at89c51rc2.h"

#define I2C_SCL P1_6
#define I2C_SDA P1_7

#define I2C_READ   0x1
#define I2C_WRITE  0x0

void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_send(uint8_t data);
void i2c_read(uint8_t *data);


#endif /* __I2C_H */

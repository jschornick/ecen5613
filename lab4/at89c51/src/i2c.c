// File       : i2c.c
// Author     : Jeff Schornick
//
// Generic I2C functions
//
// These are low level I2C functions which should be called by the drivers for
// specific I2C devices.
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdint.h>
#include "delay.h"
#include "i2c.h"


// Function: i2c_start
//
// Generate I2C start condition
// High to low transition of SDA when SCL is high
void i2c_start(void)
{
  I2C_SCL = 1;
  I2C_SDA = 1;
  nop();

  I2C_SDA = 0;  // START: high->low while clock high
  nop();
  I2C_SCL = 0;  // ready for data to change
}


// Function: i2c_stop
//
// Generate I2C stop condition
// Low to high transition of SDA when SCL is high
void i2c_stop(void)
{
  I2C_SCL = 0;
  I2C_SDA = 0;  // make sure SDA starts low
  nop();

  I2C_SCL = 1;
  nop();
  I2C_SDA = 1;  // STOP: low->high while clock high
  // bus now IDLE: both SCL/SDA high
}


// Function: i2c_send
//
// Send 8-bits over I2C, MSB first
//
// Returns the ACK/NACK value received as bit 9
uint8_t i2c_send(uint8_t data)
{
  uint8_t i;
  for(i = 0; i<8; i++) {
    I2C_SCL = 0; // data can now change
    I2C_SDA = (data & 0x80);  // get top bit
    data <<= 1; // shift bits left by one
    I2C_SCL = 1; // data stable
    nop();
  }
  I2C_SCL = 0;
  I2C_SDA = 1;    // release data line for ACK

  nop(); // make sure SCL stays low long enough
  nop(); //   ...slowest device is io_expander @4.7us
  nop();
  I2C_SCL = 1;    // clock for ACK
  nop();
  data = I2C_SDA; // read ACK signal
  I2C_SCL = 0;
  return data;    // return ACK signal
}


// Function: i2c_read
//
// Read 8-bits over I2C, MSB first
void i2c_read(uint8_t *data) {
  uint8_t i;
  for(i = 0; i<8; i++) {
    I2C_SCL = 1;
    *data <<= 1;
    *data |= I2C_SDA;
    I2C_SCL = 0;
    nop();
  }
  // send NACK
  I2C_SDA = 1;
}

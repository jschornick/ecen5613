// File       : io_expander.c
// Author     : Jeff Schornick
//
// Functions to control a PCF8574 I2C I/O Expander
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdint.h>
#include "i2c.h"
#include "io_expander.h"

#include <stdio.h>

uint8_t io_exp_input_pins = 0;

// low read write from I/O expander
uint8_t io_exp_read(void)
{
  uint8_t pins;
  uint8_t status;

  i2c_start();

  status = i2c_send(IO_EXP_READ);
  //printf("I2C_send(addr) = %u\r\n", status);
  i2c_read(&pins);
  i2c_ack();
  i2c_stop();
  return pins;
}

// low level write to I/O expander
void io_exp_write(uint8_t pins)
{
  uint8_t status;
  i2c_start();

  status = i2c_send(IO_EXP_WRITE);
  printf("I2C_send(addr) = %u\r\n", status);
  status = i2c_send(pins);
  printf("I2C_send(pins) = %u\r\n", status);
  i2c_stop();
}

uint8_t io_exp_read_pin(uint8_t pinnum)
{
  return (io_exp_read() & (1<<pinnum)) != 0;
}


void io_exp_write_pin(uint8_t pinnum, uint8_t val)
{
  uint8_t pins;
  val = val<<pinnum;
  pins = io_exp_read();
  pins &= val;  // clear original value
  io_exp_write(io_exp_input_pins | val | pins);
}

// Set read/write mode
void io_exp_set_inputs(uint8_t pins)
{
  io_exp_input_pins = pins;
  // Set any input pins high, but leave output pins at current value
  io_exp_write(io_exp_input_pins | io_exp_read());
}


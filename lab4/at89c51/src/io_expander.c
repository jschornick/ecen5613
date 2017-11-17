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

// The pin mode (input = 1, output = 0) of the I/O expander.
// When changing a single pin, we must read and write the entire I/O port.
// Since reading a 0 could be an low output or a low input, we must be careful not
// to overwrite inputs with a zero if they are reading low.
// Keep track of which values are inputs so we have enough information to avoid
// this corruption.
uint8_t io_exp_input_pins = 0;

// Function: io_exp_read
//
// A low-level read of the I/O expander pins. The input/output mode is not
// considered, so all inputs read as 1s.
//
// Returns: An 8-bit value representing the 8 I/O pin states
uint8_t io_exp_read(void)
{
  uint8_t pins;
  uint8_t status;

  i2c_start();

  status = i2c_send(IO_EXP_READ);
  i2c_read(&pins);
  i2c_ack();
  i2c_stop();
  return pins;
}

// Function: io_exp_write
//
// A low-level write to the I/O expander pins. The input/output mode is not
// considered, so a high (1) represents both a high output and setting the
// pin as an input.
//
// Params:
//   pins: An 8-bit value representing the 8 I/O pin values to set
void io_exp_write(uint8_t pins)
{
  uint8_t status;
  i2c_start();

  status = i2c_send(IO_EXP_WRITE);
  status = i2c_send(pins);
  i2c_stop();
}


// Function: io_exp_read_pin
//
// Return the value of individual pin of the I/O expander.
//
// Params:
//   pinnum: a 0..7 value corresponding to the pin to be read
uint8_t io_exp_read_pin(uint8_t pinnum)
{
  return (io_exp_read() & (1<<pinnum)) != 0;
}


// Function: io_exp_write_pin
//
// Sets a single pin without changing other pin inputs or outputs.
//
// Params:
//   pinnum: a 0..7 value corresponding to the pin to set
//   val   : the value (0,1) to set the pin to
void io_exp_write_pin(uint8_t pinnum, uint8_t val)
{
  uint8_t pins;
  val = val<<pinnum;
  pins = io_exp_read();
  pins &= val;  // clear original value
  // set the new value, but also keep inputs set high
  io_exp_write(io_exp_input_pins | val | pins);
}

// Function: io_exp_set_inputs
//
// Select which pins should be treated as inputs.
// The I/O expander only has a single bit of state per pin, where a 1 represents both
// a high output or an input. We keep track of this separately to avoid corrupting
// inputs during a single pin write.
void io_exp_set_inputs(uint8_t pins)
{
  io_exp_input_pins = pins;
  // Set any input pins high, but leave output pins at current value
  io_exp_write(io_exp_input_pins | io_exp_read());
}


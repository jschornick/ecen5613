// File       : io_expander.h
// Author     : Jeff Schornick
//
// Function declarations for controling a PCF8574 I2C I/O Expander
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#define IO_EXP_ID    (0x7)  /* 0111, TI PCF8574A datahseet p13 */
#define IO_EXP_ADDR  (0x0)

#define IO_EXP_READ  ( (IO_EXP_ID<<4) | (IO_EXP_ADDR<<1) | I2C_READ )
#define IO_EXP_WRITE ( (IO_EXP_ID<<4) | (IO_EXP_ADDR<<1) | I2C_WRITE )

// Function: io_exp_read
//
// A low-level read of the I/O expander pins. The input/output mode is not
// considered, so all inputs read as 1s.
//
// Returns: An 8-bit value representing the 8 I/O pin states
uint8_t io_exp_read(void);

// Function: io_exp_write
//
// A low-level write to the I/O expander pins. The input/output mode is not
// considered, so a high (1) represents both a high output and setting the
// pin as an input.
//
// Params:
//   pins: An 8-bit value representing the 8 I/O pin values to set
void io_exp_write(uint8_t pins);

// Function: io_exp_read_pin
//
// Return the value of individual pin of the I/O expander.
//
// Params:
//   pinnum: a 0..7 value corresponding to the pin to be read
uint8_t io_exp_read_pin(uint8_t pinnum);

// Function: io_exp_write_pin
//
// Sets a single pin without changing other pin inputs or outputs.
//
// Params:
//   pinnum: a 0..7 value corresponding to the pin to set
//   val   : the value (0,1) to set the pin to
void io_exp_write_pin(uint8_t pinnum, uint8_t val);

// Function: io_exp_set_inputs
//
// Select which pins should be treated as inputs.
// The I/O expander only has a single bit of state per pin, where a 1 represents both
// a high output or an input. We keep track of this separately to avoid corrupting
// inputs during a single pin write.
void io_exp_set_inputs(uint8_t pins);

// The pin mode (input = 1, output = 0) of the I/O expander.
extern uint8_t io_exp_input_pins;

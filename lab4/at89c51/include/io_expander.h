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

uint8_t io_exp_read(void);

void io_exp_write(uint8_t pins);

uint8_t io_exp_read_pin(uint8_t pinnum);

void io_exp_write_pin(uint8_t pinnum, uint8_t val);

void io_exp_set_inputs(uint8_t pins);

extern uint8_t io_exp_input_pins;

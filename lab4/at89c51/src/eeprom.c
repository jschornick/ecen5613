// File       : eeprom.c
// Author     : Jeff Schornick
//
// Functions to send and recieve data from an I2C EEPROM
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdint.h>
#include "i2c.h"
#include "eeprom.h"

// The top 3 bits of the 11-bit EEPROM address are actually the page number,
// sent as the top 3-bits of the 8-bit device address.
// I2C standard reads have the LSB = 1, writes have LSB = 0.
#define EEPROM_READ(page)  ( ((page)<<1) | EEPROM_DEVICE_ID | I2C_READ)
#define EEPROM_WRITE(page) ( ((page)<<1) | EEPROM_DEVICE_ID | I2C_WRITE)


// Function eeprom_write
//
// Writes an 8-bit value to the specified EEPROM address
//
// Params:
//   addr: 11-bit memory address (3-bit page, 8-bit address)
//   data: 8-bit value to write to address
void eeprom_write(uint16_t addr, uint8_t data)
{
  uint8_t status;
  // Wait for not busy
  while (eeprom_busy());
  i2c_start();

  status = i2c_send(EEPROM_WRITE(addr>>8));
  status = i2c_send(addr&0xff);
  status = i2c_send(data);

  i2c_stop();
}


// Function eeprom_read
//
// Reads an 8-bit value from the specified EEPROM address
//
// Params:
//   addr: 11-bit memory address (3-bit page, 8-bit address)
//   data: address to store the 8-bit value read
void eeprom_read(uint16_t addr, uint8_t *data)
{
  uint8_t status;
  // Wait for not busy
  while (eeprom_busy());
  // send register address to EEPROM
  i2c_start();
  status = i2c_send(EEPROM_WRITE(addr>>8));
  status = i2c_send(addr&0xff);

  // Ask EEPROM for a byte
  i2c_start();
  status = i2c_send(EEPROM_READ(addr>>8));
  i2c_read(data);
  i2c_stop();
}


// Function eeprom_busy
//
// Return true if the EEPROM is busy with an operation, based on whether or not an ACK is received.
// An ACK is a low puslse, so reading 0 is not busy.
uint8_t eeprom_busy(void)
{
  i2c_start();
  return i2c_send(EEPROM_WRITE(0));
}

// Function: eeprom_reset
//
// Performs a software reset of the I2C EEPROM using an algorithm that conforms
// to Microchip application note AN709.
void eeprom_reset(void)
{
  i2c_start();
  i2c_send(0xff);  // Send 9 bits of '1', 8 bits data (0xff) + 1 bit high waiting for ACK
  i2c_start();
  i2c_stop();
}

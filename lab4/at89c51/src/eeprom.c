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

#define EEPROM_DEVICE_ID  0xA0
#define EEPROM_READ(page)  ( ((page)<<1) | EEPROM_DEVICE_ID | I2C_READ)
#define EEPROM_WRITE(page) ( ((page)<<1) | EEPROM_DEVICE_ID | I2C_WRITE)

void eeprom_write_p(uint8_t page, uint8_t addr, uint8_t data)
{
  i2c_start();

  i2c_send(EEPROM_WRITE(page));
  // TODO: check ACK/NACK status after sends
  i2c_send(addr);
  i2c_send(data);

  i2c_stop();
}

void eeprom_write(uint16_t addr, uint8_t data)
{
  while (eeprom_busy());
  i2c_start();

  i2c_send(EEPROM_WRITE(addr>>8));
  // TODO: check ACK/NACK status after sends
  i2c_send(addr&0xff);
  i2c_send(data);

  i2c_stop();
}


void eeprom_read(uint16_t addr, uint8_t *data)
{
  while (eeprom_busy());
  // send register address to eerpom
  i2c_start();
  i2c_send(EEPROM_WRITE(addr>>8));
  i2c_send(addr&0xff);

  // ask eeprom for a byte
  i2c_start();
  i2c_send(EEPROM_READ(addr>>8));
  i2c_read(data);
  i2c_stop();
}
void eeprom_read_p(uint8_t page, uint8_t addr, uint8_t *data)
{
  // send register address to eerpom
  i2c_start();
  i2c_send(EEPROM_WRITE(page));
  i2c_send(addr);

  // ask eeprom for a byte
  i2c_start();
  i2c_send(EEPROM_READ(page));
  i2c_read(data);
  i2c_stop();
}

// ack is low pulse, returns 0 when not busy
uint8_t eeprom_busy(void)
{
  i2c_start();
  return i2c_send(EEPROM_WRITE(0));
}

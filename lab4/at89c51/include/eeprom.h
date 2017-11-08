// File       : eeprom.c
// Author     : Jeff Schornick
//
// Functions declarations for sending and recieving data via an I2C EEPROM
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details


void eeprom_write(uint16_t addr, uint8_t data);

void eeprom_read(uint16_t addr, uint8_t *data);

uint8_t eeprom_busy(void);

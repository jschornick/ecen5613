// File       : eeprom.c
// Author     : Jeff Schornick
//
// Functions declarations for sending and recieving data via an I2C EEPROM
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details


#define EEPROM_DEVICE_ID  0xA0  /* standard EEPROM device id */
#define EEPROM_ADDR_MAX  0x7ff  /* 2048 byte EEPROM */

// Function eeprom_write
//
// Writes an 8-bit value to the specified EEPROM address
//
// Params:
//   addr: 11-bit memory address (3-bit page, 8-bit address)
//   data: 8-bit value to write to address
void eeprom_write(uint16_t addr, uint8_t data);


// Function eeprom_read
//
// Reads an 8-bit value from the specified EEPROM address
//
// Params:
//   addr: 11-bit memory address (3-bit page, 8-bit address)
//   data: address to store the 8-bit value read
void eeprom_read(uint16_t addr, uint8_t *data);


// Function eeprom_busy
//
// Return true if the EEPROM is busy with an operation, based on whether or not an ACK is received.
// An ACK is a low puslse, so reading 0 is not busy.
uint8_t eeprom_busy(void);


// Function: eeprom_reset
//
// Performs a software reset of the I2C EEPROM using an algorithm that conforms
// to Microchip application note AN709.
void eeprom_reset(void);

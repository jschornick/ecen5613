// File       : startup.c
// Author     : Jeff Schornick
//
// External hardware initialization routines for the Atmel AT89C51RC2.
//
// Note that these routines are included selectively based on whether or not
// running in a Paulmon environment.
//
// Compilation: Supports SDCC v3.6+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdint.h>
#include "at89c51rc2.h"
#include "paulmon.h"

// Add a Paulmon program header and menu item.
#ifdef PAULMON
__code __at (PM_HEADER_ADDR) uint8_t paulmon_header[] = {
  PM_SIGNATURE,
  PM_TYPE_PROGRAM,255,0,0,
  PM_RESERVED,
  PM_NO_CHECKSUM };

__code __at (PM_NAME_ADDR) char paulmon_name[] = "Lab #4";
#endif /* PAULMON */


// Paulmon has been modified to configure AUXR for the AT89C51,
// so only add the startup hook if running alone
#ifndef PAULMON
void __sdcc_external_startup(void)
{
  // Enable 1024 bytes of internal XRAM
  AUXR |= AUXR_XSR_1024|AUXR_EXTRAM_INT;
}
#endif /* PAULMON */



// File       : paulmon.h
// Author     : Jeff Schornick
//
// Macros to help define Paulmon program headers
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// References : https://www.pjrc.com/tech/8051/pm2_docs/headers.html

#ifndef __PAULMON_H
#define __PAULMON_H

#define PM_SIGNATURE    0xA5,0xE5,0xE0,0xA5
#define PM_TYPE_PROGRAM 35
#define PM_TYPE_STARTUP 253
#define PM_RESERVED     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
#define PM_NO_CHECKSUM  255,255,255,255

#define PM_NAME_OFFSET  32
#define PM_NAME_ADDR    (PM_HEADER_ADDR + PM_NAME_OFFSET)

#endif /* __PAULMON_H */

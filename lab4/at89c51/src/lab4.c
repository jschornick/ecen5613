// File       : labr.c
// Author     : Jeff Schornick
//
// Implements the required functionality for ECEN5613 Lab 4.
//
// Specifically, ...
//
// Compilation: Supports SDCC v3.6+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details

#include <stdio.h>  // printf
#include <stdint.h>
#include "serial.h"

// Use a printf implementation with long support
#define printf printf_fast


// Function: main
//
// ...
void main()
{

  serial_init_brg();

}

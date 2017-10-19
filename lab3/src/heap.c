// File       : heap.c
// Author     : Jeff Schornick
//
// Reserve and define the heap as referenced by SDCC's malloc.
//
// Compilation: Supports SDCC v3.5+, see included makefile for invocation
// Version    : See GitHub repository jschornick/ecen5613 for revision details
//
// Attribution: Based on the _heap.c by Maarten Brock, provided with SDCC v3.5.


// Define a default heap size if not overridden at compile time (see makefile).
#ifndef HEAP_SIZE
#define HEAP_SIZE 1024
#endif

// Reserve heap space in XRAM, and globally define the heap start address
__xdata char __sdcc_heap[HEAP_SIZE];

// Global definition of heap size, referenced by malloc
const unsigned int __sdcc_heap_size = HEAP_SIZE;


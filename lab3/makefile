# File  : makefile
# Author: Jeff Schornick
#
# Primary makefile for ECEN5613 Lab 3
#

SRC_DIR = src
SDCC_DIR = $(HOME)/sdcc-3.6.0
UTIL_DIR = ../util

GIT_COMMIT = $(shell git log --pretty=format:'%h' -n 1; git diff-index --quiet HEAD || echo +)
BUILD_DATE = $(shell date)



# Project settings
##################

# Primary target name
NAME = lab3

# Select code and link options to work with Paulmon
PAULMON = yes
PM_HEADER_ADDR = 0x2000  # NB: must be on 256 byte boundary
PM_PROG_START  = 0x2040  # HEADER_ADDR + 0x40
PM_PROG_SIZE   = 0x5FC0  # (XRAM size) - PROG_START

# Variables default to __xdata (i.e. XRAM)
MEMMODEL = large

# Override default heap size, in bytes
HEAP_SIZE = 3000

# Debug port enabled when defined
DEBUG = yes


# C settings
############

CC = $(SDCC_DIR)/bin/sdcc

CPPFLAGS = -Iinclude

ifdef PAULMON
  CPPFLAGS += -DPAULMON
  CPPFLAGS += -DPM_HEADER_ADDR=$(PM_HEADER_ADDR)
endif

ifdef HEAP_SIZE
  CPPFLAGS += -DHEAP_SIZE=$(HEAP_SIZE)
endif

ifdef DEBUG
  CPPFLAGS += -DDEBUG
endif

CPPFLAGS += -DGIT_COMMIT=\"$(GIT_COMMIT)\"
CPPFLAGS += -DBUILD_DATE="\"$(BUILD_DATE)\""

# Target procoessor architecture (8051)
ARCH = mcs51

CFLAGS = -m$(ARCH) --model-$(MEMMODEL)
CFLAGS += --Werror --verbose

# Use C99 standard with SDCC extensions
CFLAGS += --std-sdcc99


# Linker settigns
#################

LFLAGS = --model-$(MEMMODEL)

# 32k external ram (internal XRAM + NVRAM)
# 256b of internal ram (128b direct 128b indirect)
LFLAGS += --xram-loc 0x0000 --xram-size 0x8000 --iram-size 0x0100

ifdef PAULMON
  # Paulmon at 0x0000 - 0x1FFF, program at 0x2000
  LFLAGS += --code-loc $(PM_PROG_START) --code-size $(PM_PROG_SIZE)
else
  # Program at 0x0000
  LFLAGS += --code-loc 0x0000 --code-size 0x8000
endif

# Simulator
###########

S51 = $(SDCC_DIR)/bin/s51


# ISP
###########

# The Atmel BatchISP utility is used for flashing the AT89C51
ISP = $(UTIL_DIR)/isp.sh
ISPCMD = $(ISP) -device AT89C51RC2 -hardware RS232 -port ${SERIAL} -baudrate ${BAUD_RATE} -operation LOADBUFFER $(CURDIR)/$< PROGRAM VERIFY
# BatchISP only accepts serial devices ttyS1-S3, so others (e.g. ttyUSB0) must be aliased
SERIAL = /dev/ttyS1
BAUD_RATE = 115200


# Files
###########

# File with main() must be first due to how linkage works
C_SRCS = lab3.c heap.c serial.c startup.c

ASM_GEN = $(C_SRCS:.c=.asm)
OBJS = $(C_SRCS:.c=.rel)


# Rules
###########

default: $(NAME).hex

%.HEX: %.asm
	@echo Compiling $< with ASM51 ...
	@$(ASM51)
	@if grep -q "\*\* ERROR \*\*" $(@:.HEX=.LST); then rm -f $@; false; else true; fi

# Convert 32-byte ihex to 16-byte for flashing
%.hex: %.ihx
	packihx $< >$@

%.hex: %.asm
	@echo Compiling $< with as31 ...
	@$(AS31) $(AS31_FLAGS) $<

# Precompile only
%.i: %.c
	$(CC) $(CPPFLAGS) -E $< -o $@

# Compile to assembly only
%.asm: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S $<

# Compile but do not link
%.rel: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Compile from asm, don't link
%.rel: $(SRC_DIR)/%.asm
	sdas8051 -losg $<

# Link and relocate into a single hex file
lab3.ihx: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

%.flash: %.hex
	@echo Setting up serial port...
	stty -F ${SERIAL} ${BAUD_RATE}
	@$(UTIL_DIR)/prime_bootloader.sh ${SERIAL}
	@echo
	@echo Flashing $< ...
	@$(ISPCMD)

.PHONY: flash
flash: $(NAME).flash

.PHONY: simulate
simulate: $(NAME).hex
	@echo Starting simulator, telnet to port 8080 to connect...
	$(S51) -k 8080 $<

.PHONY: clean
clean:
	rm -f *.HEX *.LST *.hex *.lst *.i $(ASM_GEN) *.rel *.map *.mem *.ihx *.lk *.sym *.rst

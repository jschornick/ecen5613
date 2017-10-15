# File  : makefile
# Author: Jeff Schornick
#
# Primary makefile for ECEN5613 Lab 3
#

UTIL_DIR = ../util

# The DOSBox configuration ensures that the sources files and ASM51/EMILY52 are
# mounted in a standard location
DOSBOX_FLAGS = -c exit -conf $(UTIL_DIR)/dosbox.conf >/dev/null
DOS_SRC_DIR = G:\LAB3

DOS_EMILY = E:\EMILY52.EXE
EMILY = dosbox -c "$(DOS_EMILY) $(DOS_SRC_DIR)\$<" $(DOSBOX_FLAGS)

DOS_AS = E:\ASM51.EXE
ASM51 = dosbox -c "$(DOS_AS) $(DOS_SRC_DIR)\$< $(ASM51_FLAGS)" $(DOSBOX_FLAGS)
# generate full listing with symbol table, no page breaks, Intel hex
ASM51_FLAGS = -I -F -S P=0

# Alternate, non-DOS assembler
AS31 = as31
AS31_FLAGS = -l


# ISP 
###########

# The Atmel BatchISP utility is used for flashing the AT89C51
ISP = $(UTIL_DIR)/isp.sh
ISPCMD = $(ISP) -device AT89C51RC2 -hardware RS232 -port ${SERIAL} -baudrate ${BAUD_RATE} -operation LOADBUFFER $(CURDIR)/$< PROGRAM VERIFY
# BatchISP only accepts serial devices ttyS1-S3, so others (e.g. ttyUSB0) must be aliased
SERIAL = /dev/ttyS1
BAUD_RATE = 115200


# C settings
###########

CC = sdcc
MEMMODEL=large

CFLAGS = -mmcs51 --model-$(MEMMODEL) --std-sdcc99

# No Paulmon
#LFLAGS = --model-$(MEMMODEL) --code-loc 0x3000 --code-size=5000

# Paulmon at 0x0000
# TODO: configure this via a macro
LFLAGS = --model-$(MEMMODEL) --code-loc 0x2000 --code-size 6000 --xram-loc 0x0000 --xram-size 0x8000


# Files
###########

C_SRCS = lab3.c
ASM_GEN = $(C_SRCS:.c=.asm)
OBJS = $(C_SRCS:.c=.rel)

IHEX=$(@:.hex=.ihx)


# Rules
###########

default: lab3.hex

%.HEX: %.asm
	@echo Compiling $< with ASM51 ...
	@$(ASM51)
	@if grep -q "\*\* ERROR \*\*" $(@:.HEX=.LST); then rm -f $@; false; else true; fi

%.hex: %.asm
	@echo Compiling $< with as31 ...
	@$(AS31) $(AS31_FLAGS) $<

%.asm: %.c
	$(CC) $(CFLAGS) -S $<

%.i: %.c
	$(CC) $(CFLAGS) -E $< -o $@

%.rel: %.c
	$(CC) $(CFLAGS) -c $<

lab3.hex: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $(IHEX)
	packihx $(IHEX) > $@

%.sim: %.hex
	@echo Simulating $< ...
	$(EMILY)

%.flash: %.hex
	@echo Setting up serial port...
	stty -F ${SERIAL} ${BAUD_RATE}
	@$(UTIL_DIR)/prime_bootloader.sh ${SERIAL}
	@echo
	@echo Flashing $< ...
	@$(ISPCMD)

.PHONY: clean
clean:
	rm -f *.HEX *.LST *.hex *.lst *.i $(ASM_GEN) *.rel *.map *.mem *.ihx *.lk *.sym *.rst

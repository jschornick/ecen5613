# Makefile for ECEN5613 Lab 3
#
# Compiles/simulates a 8051 assembly files using EMILY52

DOS_SRC_DIR = G:\LAB3
DOS_AS = E:\ASM51.EXE
DOS_EMILY = E:\EMILY52.EXE

# generate full listing with symbol table, no page breaks, Intel hex
ASM_FLAGS = -I -F -S P=0

# The DOSBox configuration ensures that the sources files and ASM51/EMILY52 are
# mounted in a standard location
DOSBOX_FLAGS = -c exit -conf .dosbox.conf >/dev/null
#DOSBOX_FLAGS = -conf .dosbox.conf >/dev/null

AS = dosbox -c "$(DOS_AS) $(DOS_SRC_DIR)\$< $(ASM_FLAGS)" $(DOSBOX_FLAGS)
EMILY = dosbox -c "$(DOS_EMILY) $(DOS_SRC_DIR)\$<" $(DOSBOX_FLAGS)

FLIP_DIR = /home/jeff/flip.3.2.1/bin
ISP = $(FLIP_DIR)/isp.sh
ISPCMD = $(ISP) -device AT89C51RC2 -hardware RS232 -port /dev/ttyS1 -baudrate 115200 -operation LOADBUFFER $(CURDIR)/$< PROGRAM VERIFY

default: XRAM.asm

%.HEX: %.asm
	@echo Compiling $< ...
	@$(AS)
	@if grep -q "\*\* ERROR \*\*" $(@:.HEX=.LST); then rm -f $@; false; else true; fi

%.sim: %.HEX
	@echo Simulating $< ...
	@$(EMILY)

%.flash: %.HEX
	@echo Flashing $< ...
	$(ISPCMD)

.PHONY: clean
clean:
	rm -f *.HEX *.LST

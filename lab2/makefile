# Makefile for ECEN5613 Lab 2
#
# Compiles/simulates a 8051 assembly files using EMILY52

DOS_SRC_DIR = G:\LAB2
DOS_AS = E:\ASM51.EXE
DOS_EMILY = E:\EMILY52.EXE

# generate full listing with symbol table, no page breaks
ASM_FLAGS = -F -S P=0

# The DOSBox configuration ensures that the sources files and ASM51/EMILY52 are
# mounted in a standard location
DOSBOX_FLAGS = -c exit -conf .dosbox.conf >/dev/null

AS = dosbox -c "$(DOS_AS) $(DOS_SRC_DIR)\$< $(ASM_FLAGS)" $(DOSBOX_FLAGS)
#EMILY = dosbox -c "$(DOS_EMILY) $(DOS_SRC_DIR)\$< /overlay" $(DOSBOX_FLAGS)
EMILY = dosbox -c "$(DOS_EMILY) $(DOS_SRC_DIR)\$<" $(DOSBOX_FLAGS)

.PHONY: default
default: eprom

%.HEX: %.asm
	@echo Compiling $< ...
	@$(AS)
	@if grep -q "\*\* ERROR \*\*" $(@:.HEX=.LST); then rm -f $@; false; else true; fi

.PHONY: eprom
eprom: EPROM.HEX
	@echo Simulating $< ...
	@$(EMILY)

.PHONY: led
led: LED.HEX
	@echo Simulating $< ...
	@$(EMILY)

.PHONY: debug
debug: DEBUG.HEX
	@echo Simulating $< ...
	@$(EMILY)

.PHONY: clean
clean:
	rm -f *.HEX *.LST

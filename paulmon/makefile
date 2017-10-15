# Makefile for Paulmon

# Assember flags, generate listing
ASM_FLAGS = -l

AS = as31

FLIP_DIR = /home/jeff/flip.3.2.1/bin
ISP = $(FLIP_DIR)/isp.sh
UTIL_DIR = ../util
SERIAL = /dev/ttyS1
BAUD_RATE = 115200

SRCS = paulmon21.asm extra.asm
HEXS = $(SRCS:.asm=.hex)

all: $(HEXS)

%.hex: %.asm
	@echo Compiling $< ...
	@$(AS) $(ASM_FLAGS) $<

flash: $(HEXS)
	@echo Setting up serial port...
	stty -F ${SERIAL} ${BAUD_RATE}
	@$(UTIL_DIR)/prime_bootloader.sh ${SERIAL}
	@echo

	@echo Flashing...
	$(ISP) -device AT89C51RC2 -hardware RS232 -port ${SERIAL} -baudrate ${BAUD_RATE} -operation LOADBUFFER $(CURDIR)/paulmon21.hex PROGRAM VERIFY LOADBUFFER $(CURDIR)/extra.hex PROGRAM VERIFY

.PHONY: clean
clean:
	rm -f *.hex *.lst

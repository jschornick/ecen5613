# makefile

DEVICE = MSP432P401R

SRC_DIR	= src
INC_DIR	= include
LD_DIR	= link
BUILD_DIR	= BUILD

TI_GDB_DIR = $(HOME)/ti/msp432_gcc/emulation/common/uscif
TI_GDB = $(TI_GDB_DIR)/gdb_agent_console

MSP_INC_DIR   = $(INC_DIR)/ti
CMSIS_INC_DIR = $(INC_DIR)/arm
DRIVERLIB_DIR = $(HOME)/ti/msp432_driverlib

GCC_BIN_DIR = /usr/bin
CC          = $(GCC_BIN_DIR)/arm-none-eabi-gcc
GDB         = $(GCC_BIN_DIR)/arm-none-eabi-gdb -q

INCLUDES    = -I$(INC_DIR) -I$(CMSIS_INC_DIR) -I$(MSP_INC_DIR) -I$(DRIVERLIB_DIR)/driverlib/MSP432P4xx -I$(DRIVERLIB_DIR)/inc
CPP_FLAGS   = -D__$(DEVICE)__ -Dgcc
C_FLAGS     = $(CPP_FLAGS) $(INCLUDES)
C_FLAGS    += -std=c99
C_FLAGS    += -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
C_FLAGS    += -O0
C_FLAGS    += -Wall -Werror
C_FLAGS    += -g -gstrict-dwarf
C_FLAGS    += -ffunction-sections -fdata-sections
#C_FLAGS    += -MD

LD_SCRIPT   = $(LD_DIR)/msp432p401r.lds
LD_FLAGS    = -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
LD_FLAGS   += -T$(LD_SCRIPT)
LD_FLAGS   += -lc -lgcc -lnosys
LD_FLAGS   += -ffunction-sections -fdata-sections
LD_FLAGS   += -Wl,-Map=$(NAME).map

# If using functions/macros from TI's driverlib, we need to link the library
#LD_FLAGS   += $(DRIVERLIB_DIR)/driverlib/MSP432P4xx/gcc/msp432p4xx_driverlib.a

C_SOURCES = $(NAME).c uart.c system_msp432p401r.c startup_msp432p401r_gcc.c
OBJECTS   = $(addprefix $(BUILD_DIR)/, $(C_SOURCES:.c=.o))
BINARY    = $(NAME).elf

# The main project to build
#NAME  = blink
NAME  = demo

all: $(BINARY)

$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.i: $(SRC_DIR)/%.c
	$(CC) $(C_FLAGS) -E $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(C_FLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	@echo Linking...
	$(CC) $^ $(LD_FLAGS) -o $@
	@echo
	arm-none-eabi-size $@

.PHONY: debug
debug: $(BINARY) gdb_agent
	@cp $(BINARY) debug.elf
	@echo
	@echo Starting GDB
	@-$(GDB) -x script/gdb_debug_msp432
	@rm debug.elf
	@echo
	@echo Killing GDB agent \(PID: $(AGENT_PID)\)
	@kill $(AGENT_PID)
	@echo

.PHONY: flash
flash: $(BINARY) gdb_agent
	@cp $(BINARY) flash.elf
	@echo
	@echo Flashing via GDB...
	@-$(GDB) -batch -nh -x script/gdb_flash_msp432
	@rm flash.elf
	@echo
	@echo Killing GDB agent \(PID: $(AGENT_PID)\)
	@kill $(AGENT_PID)
	@echo

.PHONY: gdb_agent
gdb_agent:
	@echo
	@echo -n Starting GDB agent...
	$(eval AGENT_PID= $(shell $(TI_GDB_DIR)/gdb_agent_console -f MSP432 $(TI_GDB_DIR)/xds110_msp432_swd.dat >gdb_agent.log & echo "$$!"))
	@echo  PID is $(AGENT_PID)

clean:
	@rm -rf $(BUILD_DIR) *.elf *.pid *.log *.map

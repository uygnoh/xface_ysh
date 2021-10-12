
.PHONY: clean
#*******************************************************************************
# binaries
#*******************************************************************************
PREFIX = msp430-elf-
DEVICE := MSP430F5529
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
GDB	= $(PREFIX)gdb
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S



#*******************************************************************************
# target
#*******************************************************************************
TARGET = msp430
# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DDEPRECATED \
-D__$(DEVICE)__ \



#*******************************************************************************
# building variables
#*******************************************************************************
# debug build?
DEBUG = 1
# optimization
#-Og
OPT = -Og



#*******************************************************************************
# paths
#*******************************************************************************
# Build path
BUILD_DIR = build
# AS includes
AS_INCLUDES = 

# C includes
#TI
C_INCLUDES =  \
-ITI/Include \
-IUSER \



#*******************************************************************************
# source
#*******************************************************************************
# ASM sources
ASM_SOURCES =  

# C sources
#CORE
C_SOURCES =  \
USER/MSP430F55xx_uscia0_uart_01.c \
USER/test.c \
#*******************************************************************************
# LDFLAGS
#*******************************************************************************
# link script
LDSCRIPT = msp430f5529.ld

# libraries
LIBS =	

LIBDIR = \



#*******************************************************************************
# CFLAGS
#*******************************************************************************

# mcu
MCU = -mmcu=$(DEVICE)

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


LDFLAGS = $(MCU) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin



#*******************************************************************************
# build the application
#*******************************************************************************
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	

	
$(BUILD_DIR):
	mkdir $@		



#*******************************************************************************
# clean up
#*******************************************************************************
clean:
	cd $(BUILD_DIR) && rm -f  *.*



#*******************************************************************************
# write to flash
#*******************************************************************************
debug: 
	$(GDB) $(BUILD_DIR)/$(TARGET).elf



#*******************************************************************************
# dependencies
#*******************************************************************************
-include $(wildcard $(BUILD_DIR)/*.d)

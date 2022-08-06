
.PHONY: clean

###_____________________________________________________________________________
###             => binaries
###_____________________________________________________________________________
PREFIX = msp430-elf-
DEVICE := MSP430F5529
# The gcc compiler bin path can be either defined in make 
# command via GCC_PATH variable (> make GCC_PATH=xxx)
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



###_____________________________________________________________________________
###             => target
###_____________________________________________________________________________
TARGET = msp430
# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DDEPRECATED \
-D__$(DEVICE)__ \



###_____________________________________________________________________________
###             => building variables
###_____________________________________________________________________________
# debug build?
DEBUG = 1
# optimization
#-Og
OPT = -Og



###_____________________________________________________________________________
###             => paths
###_____________________________________________________________________________
# Build path
BUILD_DIR = build
# AS includes
AS_INCLUDES = 

# C includes
#TI
C_INCLUDES =  \
-ITI/Include \
-IUSER \



###_____________________________________________________________________________
###             => source
###_____________________________________________________________________________
# ASM sources
ASM_SOURCES =  

# C sources
#CORE
C_SOURCES =  \
USER/MSP430F55xx_uscia0_uart_01.c \
USER/test.c \



###_____________________________________________________________________________
###             => LDFLAGS
###_____________________________________________________________________________
# link script
LDSCRIPT = msp430f5529.ld

# libraries
LIBS =	

LIBDIR = \



###_____________________________________________________________________________
###             => CFLAGS
###_____________________________________________________________________________

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



###_____________________________________________________________________________
###             => build the application
###_____________________________________________________________________________
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



###_____________________________________________________________________________
###             => clean up
###_____________________________________________________________________________
clean:
	cd $(BUILD_DIR) && rm -f  *.*



###_____________________________________________________________________________
###             => write to flash
###_____________________________________________________________________________
debug: 
	$(GDB) $(BUILD_DIR)/$(TARGET).elf



###_____________________________________________________________________________
###             => dependencies
###_____________________________________________________________________________
-include $(wildcard $(BUILD_DIR)/*.d)




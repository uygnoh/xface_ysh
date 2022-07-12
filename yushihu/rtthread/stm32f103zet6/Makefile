###_____________________________________________________________________________
###     => GCC 编译器
###_____________________________________________________________________________
PREFIX          = arm-none-eabi-
CC              = $(PREFIX)gcc
AS              = $(PREFIX)gcc -x assembler-with-cpp
CP              = $(PREFIX)objcopy
SZ              = $(PREFIX)size
HEX             = $(CP) -O ihex
BIN             = $(CP) -O binary -S
TARGET          = stm32f103zet6
DEBUG           = 1
OPT             = -Og
BUILD_DIR       = build
CPU             = -mcpu=cortex-m3
FPU             = 
FLOAT-ABI       = 



###_____________________________________________________________________________
###     => 文件位置
###_____________________________________________________________________________
# C sources
C_SOURCES =                     \
user/main.c                     \
user/board.c                    \
user/system_stm32f1xx.c         \
library/src/stm32f1xx_hal.c             \
library/src/stm32f1xx_hal_gpio.c        \
library/src/stm32f1xx_hal_rcc.c         \
rtthread/libcpu/cpuport.c          \
rtthread/src/clock.c               \
rtthread/src/components.c          \
rtthread/src/cpu.c                 \
rtthread/src/idle.c                \
rtthread/src/ipc.c                 \
rtthread/src/irq.c                 \
rtthread/src/kservice.c            \
rtthread/src/mem.c                 \
rtthread/src/memheap.c             \
rtthread/src/mempool.c             \
rtthread/src/object.c              \
rtthread/src/scheduler.c           \
rtthread/src/slab.c                \
rtthread/src/thread.c              \
rtthread/src/timer.c               \



# ASM sources
ASM_SOURCES =  \
startup_stm32f103xe.s
# ASMX sources
ASMX_SOURCES = \
rtthread/libcpu/context_gcc.S


# ASM includes
ASM_INCLUDES = 
# ASMX includes
ASMX_INCLUDES = 


# C includes
C_INCLUDES =                    \
-Iuser                          \
-Icmsis                         \
-Iconfig                        \
-Ilibrary/inc                   \
-Irtthread/include              \
-Irtthread/include/libc         \




###_____________________________________________________________________________
###     => ASFLAGS CFLAGS
###_____________________________________________________________________________

# 汇编语言宏定义
ASM_DEFS        =
ASMX_DEFS       =
# C语言宏定义
C_DEFS          =       \
-DUSE_HAL_DRIVER        \
-DSTM32F103xE
# MCU选项
MCU             = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
# compile gcc flags
ASFLAGS         = $(MCU) $(ASM_DEFS) $(ASMX_DEFS) \
                  $(ASM_INCLUDES) $(ASMX_INCLUDES) $(OPT) \
                  -Wall -fdata-sections -ffunction-sections
CFLAGS          = $(MCU) $(C_DEFS) $(C_INCLUDES) \
                  $(OPT) -Wall -fdata-sections -ffunction-sections
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"



###_____________________________________________________________________________
###     => LDFLAGS
###_____________________________________________________________________________
# link script
LDSCRIPT        = STM32F103ZETx_FLASH.ld
# libraries
LIBS            = -lc -lm -lnosys 
LIBDIR          = 
LDFLAGS         = $(MCU) -specs=nano.specs \
                  -T$(LDSCRIPT) $(LIBDIR) $(LIBS) \
                  -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections



###_____________________________________________________________________________
###     => 编译程序
###_____________________________________________________________________________
# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
# list of ASMX program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASMX_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASMX_SOURCES)))


$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
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


# clean up
clean:
	-rm -fR $(BUILD_DIR)
  

# dependencies
-include $(wildcard $(BUILD_DIR)/*.d)

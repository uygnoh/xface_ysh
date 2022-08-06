
######################################
# target
######################################
TARGET = stm32f4_make


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/main.c \
Core/Src/gpio.c \
Core/Src/stm32f4xx_it.c \
Core/Src/stm32f4xx_hal_msp.c \
Core/Src/stm32f4xx_hal_timebase_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Core/Src/system_stm32f4xx.c \
ThreadX/common/src/tx_block_allocate.c \
ThreadX/common/src/tx_block_pool_cleanup.c \
ThreadX/common/src/tx_block_pool_create.c \
ThreadX/common/src/tx_block_pool_delete.c \
ThreadX/common/src/tx_block_pool_info_get.c \
ThreadX/common/src/tx_block_pool_initialize.c \
ThreadX/common/src/tx_block_pool_performance_info_get.c \
ThreadX/common/src/tx_block_pool_performance_system_info_get.c \
ThreadX/common/src/tx_block_pool_prioritize.c \
ThreadX/common/src/tx_block_release.c \
ThreadX/common/src/tx_byte_allocate.c \
ThreadX/common/src/tx_byte_pool_cleanup.c \
ThreadX/common/src/tx_byte_pool_create.c \
ThreadX/common/src/tx_byte_pool_delete.c \
ThreadX/common/src/tx_byte_pool_info_get.c \
ThreadX/common/src/tx_byte_pool_initialize.c \
ThreadX/common/src/tx_byte_pool_performance_info_get.c \
ThreadX/common/src/tx_byte_pool_performance_system_info_get.c \
ThreadX/common/src/tx_byte_pool_prioritize.c \
ThreadX/common/src/tx_byte_pool_search.c \
ThreadX/common/src/tx_byte_release.c \
ThreadX/common/src/tx_event_flags_cleanup.c \
ThreadX/common/src/tx_event_flags_create.c \
ThreadX/common/src/tx_event_flags_delete.c \
ThreadX/common/src/tx_event_flags_get.c \
ThreadX/common/src/tx_event_flags_info_get.c \
ThreadX/common/src/tx_event_flags_initialize.c \
ThreadX/common/src/tx_event_flags_performance_info_get.c \
ThreadX/common/src/tx_event_flags_performance_system_info_get.c \
ThreadX/common/src/tx_event_flags_set.c \
ThreadX/common/src/tx_event_flags_set_notify.c \
ThreadX/common/src/tx_initialize_high_level.c \
ThreadX/common/src/tx_initialize_kernel_enter.c \
ThreadX/common/src/tx_initialize_kernel_setup.c \
ThreadX/common/src/tx_mutex_cleanup.c \
ThreadX/common/src/tx_mutex_create.c \
ThreadX/common/src/tx_mutex_delete.c \
ThreadX/common/src/tx_mutex_get.c \
ThreadX/common/src/tx_mutex_info_get.c \
ThreadX/common/src/tx_mutex_initialize.c \
ThreadX/common/src/tx_mutex_performance_info_get.c \
ThreadX/common/src/tx_mutex_performance_system_info_get.c \
ThreadX/common/src/tx_mutex_prioritize.c \
ThreadX/common/src/tx_mutex_priority_change.c \
ThreadX/common/src/tx_mutex_put.c \
ThreadX/common/src/tx_queue_cleanup.c \
ThreadX/common/src/tx_queue_create.c \
ThreadX/common/src/tx_queue_delete.c \
ThreadX/common/src/tx_queue_flush.c \
ThreadX/common/src/tx_queue_front_send.c \
ThreadX/common/src/tx_queue_info_get.c \
ThreadX/common/src/tx_queue_initialize.c \
ThreadX/common/src/tx_queue_performance_info_get.c \
ThreadX/common/src/tx_queue_performance_system_info_get.c \
ThreadX/common/src/tx_queue_prioritize.c \
ThreadX/common/src/tx_queue_receive.c \
ThreadX/common/src/tx_queue_send.c \
ThreadX/common/src/tx_queue_send_notify.c \
ThreadX/common/src/tx_semaphore_ceiling_put.c \
ThreadX/common/src/tx_semaphore_cleanup.c \
ThreadX/common/src/tx_semaphore_create.c \
ThreadX/common/src/tx_semaphore_delete.c \
ThreadX/common/src/tx_semaphore_get.c \
ThreadX/common/src/tx_semaphore_info_get.c \
ThreadX/common/src/tx_semaphore_initialize.c \
ThreadX/common/src/tx_semaphore_performance_info_get.c \
ThreadX/common/src/tx_semaphore_performance_system_info_get.c \
ThreadX/common/src/tx_semaphore_prioritize.c \
ThreadX/common/src/tx_semaphore_put.c \
ThreadX/common/src/tx_semaphore_put_notify.c \
ThreadX/common/src/tx_thread_create.c \
ThreadX/common/src/tx_thread_delete.c \
ThreadX/common/src/tx_thread_entry_exit_notify.c \
ThreadX/common/src/tx_thread_identify.c \
ThreadX/common/src/tx_thread_info_get.c \
ThreadX/common/src/tx_thread_initialize.c \
ThreadX/common/src/tx_thread_performance_info_get.c \
ThreadX/common/src/tx_thread_performance_system_info_get.c \
ThreadX/common/src/tx_thread_preemption_change.c \
ThreadX/common/src/tx_thread_priority_change.c \
ThreadX/common/src/tx_thread_relinquish.c \
ThreadX/common/src/tx_thread_reset.c \
ThreadX/common/src/tx_thread_resume.c \
ThreadX/common/src/tx_thread_shell_entry.c \
ThreadX/common/src/tx_thread_sleep.c \
ThreadX/common/src/tx_thread_stack_analyze.c \
ThreadX/common/src/tx_thread_stack_error_handler.c \
ThreadX/common/src/tx_thread_stack_error_notify.c \
ThreadX/common/src/tx_thread_suspend.c \
ThreadX/common/src/tx_thread_system_preempt_check.c \
ThreadX/common/src/tx_thread_system_resume.c \
ThreadX/common/src/tx_thread_system_suspend.c \
ThreadX/common/src/tx_thread_terminate.c \
ThreadX/common/src/tx_thread_time_slice.c \
ThreadX/common/src/tx_thread_time_slice_change.c \
ThreadX/common/src/tx_thread_timeout.c \
ThreadX/common/src/tx_thread_wait_abort.c \
ThreadX/common/src/tx_time_get.c \
ThreadX/common/src/tx_time_set.c \
ThreadX/common/src/tx_timer_activate.c \
ThreadX/common/src/tx_timer_change.c \
ThreadX/common/src/tx_timer_create.c \
ThreadX/common/src/tx_timer_deactivate.c \
ThreadX/common/src/tx_timer_delete.c \
ThreadX/common/src/tx_timer_expiration_process.c \
ThreadX/common/src/tx_timer_info_get.c \
ThreadX/common/src/tx_timer_initialize.c \
ThreadX/common/src/tx_timer_performance_info_get.c \
ThreadX/common/src/tx_timer_performance_system_info_get.c \
ThreadX/common/src/tx_timer_system_activate.c \
ThreadX/common/src/tx_timer_system_deactivate.c \
ThreadX/common/src/tx_timer_thread_entry.c \
ThreadX/common/src/tx_trace_buffer_full_notify.c \
ThreadX/common/src/tx_trace_enable.c \
ThreadX/common/src/tx_trace_event_filter.c \
ThreadX/common/src/tx_trace_event_unfilter.c \
ThreadX/common/src/tx_trace_disable.c \
ThreadX/common/src/tx_trace_initialize.c \
ThreadX/common/src/tx_trace_interrupt_control.c \
ThreadX/common/src/tx_trace_isr_enter_insert.c \
ThreadX/common/src/tx_trace_isr_exit_insert.c \
ThreadX/common/src/tx_trace_object_register.c \
ThreadX/common/src/tx_trace_object_unregister.c \
ThreadX/common/src/tx_trace_user_event_insert.c \
ThreadX/common/src/txe_block_allocate.c \
ThreadX/common/src/txe_block_pool_create.c \
ThreadX/common/src/txe_block_pool_delete.c \
ThreadX/common/src/txe_block_pool_info_get.c \
ThreadX/common/src/txe_block_pool_prioritize.c \
ThreadX/common/src/txe_block_release.c \
ThreadX/common/src/txe_byte_allocate.c \
ThreadX/common/src/txe_byte_pool_create.c \
ThreadX/common/src/txe_byte_pool_delete.c \
ThreadX/common/src/txe_byte_pool_info_get.c \
ThreadX/common/src/txe_byte_pool_prioritize.c \
ThreadX/common/src/txe_byte_release.c \
ThreadX/common/src/txe_event_flags_create.c \
ThreadX/common/src/txe_event_flags_delete.c \
ThreadX/common/src/txe_event_flags_get.c \
ThreadX/common/src/txe_event_flags_info_get.c \
ThreadX/common/src/txe_event_flags_set.c \
ThreadX/common/src/txe_event_flags_set_notify.c \
ThreadX/common/src/txe_mutex_create.c \
ThreadX/common/src/txe_mutex_delete.c \
ThreadX/common/src/txe_mutex_get.c \
ThreadX/common/src/txe_mutex_info_get.c \
ThreadX/common/src/txe_mutex_prioritize.c \
ThreadX/common/src/txe_mutex_put.c \
ThreadX/common/src/txe_queue_create.c \
ThreadX/common/src/txe_queue_delete.c \
ThreadX/common/src/txe_queue_flush.c \
ThreadX/common/src/txe_queue_front_send.c \
ThreadX/common/src/txe_queue_info_get.c \
ThreadX/common/src/txe_queue_prioritize.c \
ThreadX/common/src/txe_queue_receive.c \
ThreadX/common/src/txe_queue_send.c \
ThreadX/common/src/txe_queue_send_notify.c \
ThreadX/common/src/txe_semaphore_ceiling_put.c \
ThreadX/common/src/txe_semaphore_create.c \
ThreadX/common/src/txe_semaphore_delete.c \
ThreadX/common/src/txe_semaphore_get.c \
ThreadX/common/src/txe_semaphore_info_get.c \
ThreadX/common/src/txe_semaphore_prioritize.c \
ThreadX/common/src/txe_semaphore_put.c \
ThreadX/common/src/txe_semaphore_put_notify.c \
ThreadX/common/src/txe_thread_create.c \
ThreadX/common/src/txe_thread_delete.c \
ThreadX/common/src/txe_thread_entry_exit_notify.c \
ThreadX/common/src/txe_thread_info_get.c \
ThreadX/common/src/txe_thread_preemption_change.c \
ThreadX/common/src/txe_thread_priority_change.c \
ThreadX/common/src/txe_thread_relinquish.c \
ThreadX/common/src/txe_thread_reset.c \
ThreadX/common/src/txe_thread_resume.c \
ThreadX/common/src/txe_thread_suspend.c \
ThreadX/common/src/txe_thread_terminate.c \
ThreadX/common/src/txe_thread_time_slice_change.c \
ThreadX/common/src/txe_thread_wait_abort.c \
ThreadX/common/src/txe_timer_activate.c \
ThreadX/common/src/txe_timer_change.c \
ThreadX/common/src/txe_timer_create.c \
ThreadX/common/src/txe_timer_deactivate.c \
ThreadX/common/src/txe_timer_delete.c \
ThreadX/common/src/txe_timer_info_get.c


# ASM sources
ASM_SOURCES =  \
startup_stm32f411xe.s


# ASM SOURCES2
ASM_SOURCES2 =  \
ThreadX/ports/cortex_m4/gnu/src/tx_initialize_low_level.S \
ThreadX/ports/cortex_m4/gnu/src/tx_thread_stack_build.S \
ThreadX/ports/cortex_m4/gnu/src/tx_thread_schedule.S \
ThreadX/ports/cortex_m4/gnu/src/tx_thread_system_return.S \
ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_save.S \
ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_restore.S \
ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_control.S \
ThreadX/ports/cortex_m4/gnu/src/tx_timer_interrupt.S \
ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_control.S



#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
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
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F411xE


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include/ \
-IThreadX/common/inc/ \
-IThreadX/ports/cortex_m4/gnu/inc


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F411RETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES2:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES2)))

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

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)


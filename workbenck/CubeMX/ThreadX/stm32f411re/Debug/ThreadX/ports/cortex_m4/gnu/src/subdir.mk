################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../ThreadX/ports/cortex_m4/gnu/src/tx_initialize_low_level.S \
../ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_restore.S \
../ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_save.S \
../ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_control.S \
../ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_disable.S \
../ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_restore.S \
../ThreadX/ports/cortex_m4/gnu/src/tx_thread_schedule.S \
../ThreadX/ports/cortex_m4/gnu/src/tx_thread_stack_build.S \
../ThreadX/ports/cortex_m4/gnu/src/tx_thread_system_return.S \
../ThreadX/ports/cortex_m4/gnu/src/tx_timer_interrupt.S 

OBJS += \
./ThreadX/ports/cortex_m4/gnu/src/tx_initialize_low_level.o \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_restore.o \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_save.o \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_control.o \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_disable.o \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_restore.o \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_schedule.o \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_stack_build.o \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_system_return.o \
./ThreadX/ports/cortex_m4/gnu/src/tx_timer_interrupt.o 

S_UPPER_DEPS += \
./ThreadX/ports/cortex_m4/gnu/src/tx_initialize_low_level.d \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_restore.d \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_save.d \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_control.d \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_disable.d \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_restore.d \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_schedule.d \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_stack_build.d \
./ThreadX/ports/cortex_m4/gnu/src/tx_thread_system_return.d \
./ThreadX/ports/cortex_m4/gnu/src/tx_timer_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
ThreadX/ports/cortex_m4/gnu/src/tx_initialize_low_level.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_initialize_low_level.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_initialize_low_level.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_restore.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_restore.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_restore.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_save.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_save.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_thread_context_save.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_control.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_control.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_control.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_disable.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_disable.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_disable.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_restore.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_restore.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_thread_interrupt_restore.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
ThreadX/ports/cortex_m4/gnu/src/tx_thread_schedule.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_thread_schedule.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_thread_schedule.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
ThreadX/ports/cortex_m4/gnu/src/tx_thread_stack_build.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_thread_stack_build.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_thread_stack_build.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
ThreadX/ports/cortex_m4/gnu/src/tx_thread_system_return.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_thread_system_return.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_thread_system_return.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
ThreadX/ports/cortex_m4/gnu/src/tx_timer_interrupt.o: ../ThreadX/ports/cortex_m4/gnu/src/tx_timer_interrupt.S ThreadX/ports/cortex_m4/gnu/src/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/src/tx_timer_interrupt.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"


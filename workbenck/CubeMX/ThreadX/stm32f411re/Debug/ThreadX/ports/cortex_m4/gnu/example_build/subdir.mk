################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThreadX/ports/cortex_m4/gnu/example_build/sample_threadx.c 

S_UPPER_SRCS += \
../ThreadX/ports/cortex_m4/gnu/example_build/tx_initialize_low_level.S 

OBJS += \
./ThreadX/ports/cortex_m4/gnu/example_build/sample_threadx.o \
./ThreadX/ports/cortex_m4/gnu/example_build/tx_initialize_low_level.o 

S_UPPER_DEPS += \
./ThreadX/ports/cortex_m4/gnu/example_build/tx_initialize_low_level.d 

C_DEPS += \
./ThreadX/ports/cortex_m4/gnu/example_build/sample_threadx.d 


# Each subdirectory must supply rules for building sources it contributes
ThreadX/ports/cortex_m4/gnu/example_build/sample_threadx.o: ../ThreadX/ports/cortex_m4/gnu/example_build/sample_threadx.c ThreadX/ports/cortex_m4/gnu/example_build/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/stm32f411re/ThreadX/common/inc" -I"/home/ysh/Desktop/github/workbenck/CubeMX/ThreadX/stm32f411re/ThreadX/ports/cortex_m4/gnu/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/example_build/sample_threadx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThreadX/ports/cortex_m4/gnu/example_build/tx_initialize_low_level.o: ../ThreadX/ports/cortex_m4/gnu/example_build/tx_initialize_low_level.S ThreadX/ports/cortex_m4/gnu/example_build/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"ThreadX/ports/cortex_m4/gnu/example_build/tx_initialize_low_level.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"


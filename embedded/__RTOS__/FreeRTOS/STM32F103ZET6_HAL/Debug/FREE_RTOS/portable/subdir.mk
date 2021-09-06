################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FREE_RTOS/portable/port.c 

OBJS += \
./FREE_RTOS/portable/port.o 

C_DEPS += \
./FREE_RTOS/portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
FREE_RTOS/portable/port.o: ../FREE_RTOS/portable/port.c FREE_RTOS/portable/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/include" -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FREE_RTOS/portable/port.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


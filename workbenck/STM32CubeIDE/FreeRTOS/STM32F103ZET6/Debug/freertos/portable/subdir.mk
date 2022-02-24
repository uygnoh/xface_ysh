################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/portable/heap_4.c \
../freertos/portable/port.c 

OBJS += \
./freertos/portable/heap_4.o \
./freertos/portable/port.o 

C_DEPS += \
./freertos/portable/heap_4.d \
./freertos/portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/portable/heap_4.o: ../freertos/portable/heap_4.c freertos/portable/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/HAL/STM32F103ZET6/freertos/include" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/HAL/STM32F103ZET6/freertos/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"freertos/portable/heap_4.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
freertos/portable/port.o: ../freertos/portable/port.c freertos/portable/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/HAL/STM32F103ZET6/freertos/include" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/HAL/STM32F103ZET6/freertos/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"freertos/portable/port.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


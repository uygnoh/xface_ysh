################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F1_REG/source/systick.c \
../STM32F1_REG/source/usart.c 

OBJS += \
./STM32F1_REG/source/systick.o \
./STM32F1_REG/source/usart.o 

C_DEPS += \
./STM32F1_REG/source/systick.d \
./STM32F1_REG/source/usart.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F1_REG/source/systick.o: ../STM32F1_REG/source/systick.c STM32F1_REG/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/__ysh__/workbenck/STM32CubeMX/STM32F103ZET6/STM32F1_REG/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F1_REG/source/systick.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F1_REG/source/usart.o: ../STM32F1_REG/source/usart.c STM32F1_REG/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/__ysh__/workbenck/STM32CubeMX/STM32F103ZET6/STM32F1_REG/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F1_REG/source/usart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


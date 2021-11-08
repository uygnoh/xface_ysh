################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Regf103/source/reg_adc.c \
../Regf103/source/reg_systick.c \
../Regf103/source/reg_uart.c \
../Regf103/source/temperature.c 

OBJS += \
./Regf103/source/reg_adc.o \
./Regf103/source/reg_systick.o \
./Regf103/source/reg_uart.o \
./Regf103/source/temperature.o 

C_DEPS += \
./Regf103/source/reg_adc.d \
./Regf103/source/reg_systick.d \
./Regf103/source/reg_uart.d \
./Regf103/source/temperature.d 


# Each subdirectory must supply rules for building sources it contributes
Regf103/source/reg_adc.o: ../Regf103/source/reg_adc.c Regf103/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/__ysh__/workbenck/STM32CubeMX/STM32F103ZET6/Regf103/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Regf103/source/reg_adc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Regf103/source/reg_systick.o: ../Regf103/source/reg_systick.c Regf103/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/__ysh__/workbenck/STM32CubeMX/STM32F103ZET6/Regf103/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Regf103/source/reg_systick.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Regf103/source/reg_uart.o: ../Regf103/source/reg_uart.c Regf103/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/__ysh__/workbenck/STM32CubeMX/STM32F103ZET6/Regf103/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Regf103/source/reg_uart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Regf103/source/temperature.o: ../Regf103/source/temperature.c Regf103/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/__ysh__/workbenck/STM32CubeMX/STM32F103ZET6/Regf103/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Regf103/source/temperature.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


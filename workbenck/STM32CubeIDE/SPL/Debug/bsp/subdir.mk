################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/bsp.c 

OBJS += \
./bsp/bsp.o 

C_DEPS += \
./bsp/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/bsp.o: ../bsp/bsp.c bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DSTM32 -DSTM32F1 -DSTM32F103ZETx -c -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/cmsis" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/libraries/inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Src" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/include" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/portable" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/bsp/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"bsp/bsp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


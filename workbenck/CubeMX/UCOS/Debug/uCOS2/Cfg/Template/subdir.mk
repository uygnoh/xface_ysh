################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uCOS2/Cfg/Template/app_hooks.c 

OBJS += \
./uCOS2/Cfg/Template/app_hooks.o 

C_DEPS += \
./uCOS2/Cfg/Template/app_hooks.d 


# Each subdirectory must supply rules for building sources it contributes
uCOS2/Cfg/Template/app_hooks.o: ../uCOS2/Cfg/Template/app_hooks.c uCOS2/Cfg/Template/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Cfg/Template/app_hooks.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


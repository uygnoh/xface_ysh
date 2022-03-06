################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_dbg.c 

S_UPPER_SRCS += \
../uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.S 

OBJS += \
./uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.o \
./uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_dbg.o 

S_UPPER_DEPS += \
./uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.d 

C_DEPS += \
./uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_dbg.d 


# Each subdirectory must supply rules for building sources it contributes
uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.o: ../uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.S uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_dbg.o: ../uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_dbg.c uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_dbg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


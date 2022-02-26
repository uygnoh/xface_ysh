################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/stm32f10x_it.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/stm32f10x_it.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/stm32f10x_it.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/main.o: ../Src/main.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DSTM32 -DSTM32F1 -DSTM32F103ZETx -c -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/cmsis" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/libraries/inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Src" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/include" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/portable" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/bsp/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/stm32f10x_it.o: ../Src/stm32f10x_it.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DSTM32 -DSTM32F1 -DSTM32F103ZETx -c -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/cmsis" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/libraries/inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Src" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/include" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/portable" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/bsp/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/stm32f10x_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DSTM32 -DSTM32F1 -DSTM32F103ZETx -c -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/cmsis" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/libraries/inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Src" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/include" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/portable" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/bsp/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DSTM32 -DSTM32F1 -DSTM32F103ZETx -c -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/cmsis" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/libraries/inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Inc" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/Src" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/include" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/FreeRTOS/portable" -I"/home/ysh/Desktop/github/workbenck/STM32CubeIDE/SPL/bsp/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


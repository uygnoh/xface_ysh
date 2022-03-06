################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uCOS2/Source/os_core.c \
../uCOS2/Source/os_flag.c \
../uCOS2/Source/os_mbox.c \
../uCOS2/Source/os_mem.c \
../uCOS2/Source/os_mutex.c \
../uCOS2/Source/os_q.c \
../uCOS2/Source/os_sem.c \
../uCOS2/Source/os_task.c \
../uCOS2/Source/os_time.c \
../uCOS2/Source/os_tmr.c 

OBJS += \
./uCOS2/Source/os_core.o \
./uCOS2/Source/os_flag.o \
./uCOS2/Source/os_mbox.o \
./uCOS2/Source/os_mem.o \
./uCOS2/Source/os_mutex.o \
./uCOS2/Source/os_q.o \
./uCOS2/Source/os_sem.o \
./uCOS2/Source/os_task.o \
./uCOS2/Source/os_time.o \
./uCOS2/Source/os_tmr.o 

C_DEPS += \
./uCOS2/Source/os_core.d \
./uCOS2/Source/os_flag.d \
./uCOS2/Source/os_mbox.d \
./uCOS2/Source/os_mem.d \
./uCOS2/Source/os_mutex.d \
./uCOS2/Source/os_q.d \
./uCOS2/Source/os_sem.d \
./uCOS2/Source/os_task.d \
./uCOS2/Source/os_time.d \
./uCOS2/Source/os_tmr.d 


# Each subdirectory must supply rules for building sources it contributes
uCOS2/Source/os_core.o: ../uCOS2/Source/os_core.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
uCOS2/Source/os_flag.o: ../uCOS2/Source/os_flag.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_flag.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
uCOS2/Source/os_mbox.o: ../uCOS2/Source/os_mbox.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_mbox.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
uCOS2/Source/os_mem.o: ../uCOS2/Source/os_mem.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_mem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
uCOS2/Source/os_mutex.o: ../uCOS2/Source/os_mutex.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_mutex.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
uCOS2/Source/os_q.o: ../uCOS2/Source/os_q.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_q.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
uCOS2/Source/os_sem.o: ../uCOS2/Source/os_sem.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_sem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
uCOS2/Source/os_task.o: ../uCOS2/Source/os_task.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_task.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
uCOS2/Source/os_time.o: ../uCOS2/Source/os_time.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_time.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
uCOS2/Source/os_tmr.o: ../uCOS2/Source/os_tmr.c uCOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Cfg/Template" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Ports/ARM-Cortex-M/ARMv7-M/GNU" -I"/home/ysh/Desktop/github/workbenck/CubeMX/UCOS/uCOS2/Source" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"uCOS2/Source/os_tmr.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


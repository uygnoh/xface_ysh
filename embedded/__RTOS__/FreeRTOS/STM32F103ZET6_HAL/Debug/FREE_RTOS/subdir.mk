################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FREE_RTOS/croutine.c \
../FREE_RTOS/event_groups.c \
../FREE_RTOS/heap_4.c \
../FREE_RTOS/list.c \
../FREE_RTOS/queue.c \
../FREE_RTOS/tasks.c \
../FREE_RTOS/timers.c 

OBJS += \
./FREE_RTOS/croutine.o \
./FREE_RTOS/event_groups.o \
./FREE_RTOS/heap_4.o \
./FREE_RTOS/list.o \
./FREE_RTOS/queue.o \
./FREE_RTOS/tasks.o \
./FREE_RTOS/timers.o 

C_DEPS += \
./FREE_RTOS/croutine.d \
./FREE_RTOS/event_groups.d \
./FREE_RTOS/heap_4.d \
./FREE_RTOS/list.d \
./FREE_RTOS/queue.d \
./FREE_RTOS/tasks.d \
./FREE_RTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FREE_RTOS/croutine.o: ../FREE_RTOS/croutine.c FREE_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/include" -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FREE_RTOS/croutine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FREE_RTOS/event_groups.o: ../FREE_RTOS/event_groups.c FREE_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/include" -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FREE_RTOS/event_groups.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FREE_RTOS/heap_4.o: ../FREE_RTOS/heap_4.c FREE_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/include" -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FREE_RTOS/heap_4.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FREE_RTOS/list.o: ../FREE_RTOS/list.c FREE_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/include" -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FREE_RTOS/list.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FREE_RTOS/queue.o: ../FREE_RTOS/queue.c FREE_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/include" -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FREE_RTOS/queue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FREE_RTOS/tasks.o: ../FREE_RTOS/tasks.c FREE_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/include" -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FREE_RTOS/tasks.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FREE_RTOS/timers.o: ../FREE_RTOS/timers.c FREE_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/include" -I"/home/freeysh/Documents/GIT_HUB/FREE_RTOS/STM32F103ZET6_HAL/FREE_RTOS/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FREE_RTOS/timers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


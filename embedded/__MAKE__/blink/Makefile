vpath %.S stlib
vpath %.c stlib stlib/src
vpath %.h stlib stlib/cminc stlib/inc

DEFS += -DUSE_STDPERIPH_DRIVER

INCS += -Istlib -Istlib/cminc -Istlib/inc

OBJS += stlib/startup_stm32f30x.o stlib/system_stm32f30x.o
OBJS += stlib/src/stm32f30x_rcc.o stlib/src/stm32f30x_gpio.o 
OBJS += main.o

CFLAGS += -mcpu=cortex-m4 -mthumb -Wall 
LFLAGS += -mcpu=cortex-m4 -mthumb 

all:blink.bin
clean:
	@rm -f $(OBJS) blink.bin blink.elf
	
blink.bin:blink.elf
	@arm-none-eabi-objcopy -O binary -S $< $@
	
blink.elf:$(OBJS)
	@arm-none-eabi-gcc $(LFLAGS) $^ -Tstlib/flash.ld -o $@
	@arm-none-eabi-size $@
	
burn:blink.bin
	@st-flash write $< 0x08000000
	
%.o:%.S
	@arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
%.o:%.c
	@arm-none-eabi-gcc $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@

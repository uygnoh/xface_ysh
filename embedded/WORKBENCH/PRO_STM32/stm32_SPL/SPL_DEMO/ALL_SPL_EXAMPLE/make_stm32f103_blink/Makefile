# general Makefile
# ================

include Makefile.common

LDFLAGS=$(COMMONFLAGS) -fno-exceptions -ffunction-sections \
			-fdata-sections -L$(STM32DIR) -L$(BSPDIR) -L$(CMSISDIR) -L$(INTERRUPTDIR) \
			-Wl,--gc-sections,-Tldscripts/linker.ld

LDLIBS+=-lcmsis
LDLIBS+=-linterrupt
LDLIBS+=-lstm32
LDLIBS+=-lbsp



all: user bsp cmsis stm32 interrupt
	$(CC) -o output/$(PROGRAM).elf $(LDFLAGS) \
		-Wl,--whole-archive \
			user/app.a \
		-Wl,--no-whole-archive \
			$(LDLIBS)
	$(OBJCOPY) -O ihex output/$(PROGRAM).elf output/$(PROGRAM).hex
	$(OBJCOPY) -O binary output/$(PROGRAM).elf output/$(PROGRAM).bin
# Extract info contained in ELF to readable text-files:
# =====================================================
	arm-none-eabi-readelf -a output/$(PROGRAM).elf > output/$(PROGRAM).info_elf
	arm-none-eabi-size -d -B -t output/$(PROGRAM).elf > output/$(PROGRAM).info_size
	arm-none-eabi-objdump -S output/$(PROGRAM).elf > output/$(PROGRAM).info_code
	arm-none-eabi-nm -t x -S --numeric-sort -s output/$(PROGRAM).elf > output/$(PROGRAM).info_symbol
	@echo "################ Compile completed--->$? ################"



.PHONY: user cmsis stm32 bsp interrupt clean tshow
	
user:
	$(MAKE) -C user $@

cmsis:
	$(MAKE) -C cmsis $@
	
stm32:
	$(MAKE) -C stm32 $@
	
bsp:
	$(MAKE) -C bsp $@
	
interrupt:
	$(MAKE) -C interrupt $@

clean:
	$(MAKE) -C user $@
	$(MAKE) -C cmsis $@
	$(MAKE) -C stm32 $@
	$(MAKE) -C bsp $@
	$(MAKE) -C interrupt $@
	rm -f output/$(PROGRAM).elf output/$(PROGRAM).hex \
		output/$(PROGRAM).bin output/$(PROGRAM).info_elf \
			output/$(PROGRAM).info_size output/$(PROGRAM).info_code \
				output/$(PROGRAM).info_symbol

tshow:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"




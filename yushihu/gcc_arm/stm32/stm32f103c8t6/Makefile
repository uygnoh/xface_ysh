# general Makefile
# ================

include common.mk

LDFLAGS         := $(CFLAGS) -fno-exceptions -ffunction-sections\
                -fdata-sections -L$(YUSHIHU)/library            \
                -Wl,--gc-sections,-T$(YUSHIHU)/user/STM32F103C8T6.ld


LDLIBS          += -lstm32


all: user library
	$(CC) -o build/$(PROGRAM).elf $(LDFLAGS) \
		-Wl,--whole-archive               \
			user/app.a                \
		-Wl,--no-whole-archive            \
			$(LDLIBS)
	$(OBJCOPY) -O ihex build/$(PROGRAM).elf build/$(PROGRAM).hex
	$(OBJCOPY) -O binary build/$(PROGRAM).elf build/$(PROGRAM).bin
	# Extract info contained in ELF to readable text-files:
	# =====================================================
	arm-none-eabi-readelf -a build/$(PROGRAM).elf > build/$(PROGRAM).info_elf
	arm-none-eabi-size -d -B -t build/$(PROGRAM).elf > build/$(PROGRAM).info_size
	arm-none-eabi-objdump -S build/$(PROGRAM).elf > build/$(PROGRAM).info_code
	arm-none-eabi-nm -t x -S --numeric-sort -s build/$(PROGRAM).elf > build/$(PROGRAM).info_symbol
	@echo "################ Compile completed--->$? ################"


.PHONY:	user clean library tshow
user:
	$(MAKE) -C user	$@
library:
	$(MAKE) -C library	$@
clean:
	$(MAKE) -C user         $@
	$(MAKE) -C library      $@
	$(RM) build/$(PROGRAM).elf build/$(PROGRAM).hex
	$(RM) build/$(PROGRAM).bin build/$(PROGRAM).info_elf
	$(RM) build/$(PROGRAM).info_size build/$(PROGRAM).info_code
	$(RM) build/$(PROGRAM).info_symbol
tshow:
	@echo "################################################################"
	@echo "## optimize settings: $(INFO_TEXT_LIB), $(INFO_TEXT_USER) ###"
	@echo "################################################################"

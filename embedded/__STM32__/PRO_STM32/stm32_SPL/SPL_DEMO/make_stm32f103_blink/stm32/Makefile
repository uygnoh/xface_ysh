# STM32libs Makefile
# ==================

include ../Makefile.common
STM32_LIBS+=libstm32.a
CFLAGSlib+=-c



all: stm32
stm32: $(STM32_LIBS)
libstm32.a:
	@echo -n "Building $@ ..."
	@cd $(STM32LIB)/src && \
		$(CC) $(CFLAGSlib) \
			*.c
			
	@$(AR) cr $(STM32DIR)/$@ \
		$(STM32LIB)/src/*.o
	@echo "done."



.PHONY: stm32 clean tshow

clean:
	rm -f $(STM32LIB)/src/*.o
	rm -f $(STM32_LIBS)
	
tshow:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"




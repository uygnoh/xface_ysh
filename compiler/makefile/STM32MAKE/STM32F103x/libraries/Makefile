# libraries Makefile
# ==================

include ../Makefile.common
LIBS+=libstm32.a
CFLAGSlib+=-c



all: libraries
libraries: $(LIBS)
libstm32.a:
	@echo -n "Building $@ ..."
	@cd $(STMLIB)/clock/src && \
		$(CC) $(CFLAGSlib) \
			system_stm32f10x.c
	@cd $(STMLIB)/cm3/src && \
		$(CC) $(CFLAGSlib) \
			*.c
	@$(AR) cr $(LIBDIR)/$@ \
		$(STMLIB)/clock/src/system_stm32f10x.o \
		$(STMLIB)/cm3/src/*.o
	@echo "done."


.PHONY: libraries clean display

clean:
	rm -f $(STMLIB)/clock/src/system_stm32f10x.o
	rm -f $(STMLIB)/cm3/src/*.o
	rm -f $(LIBS)
	
display:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"




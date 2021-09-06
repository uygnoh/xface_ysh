# INTERRUPTlibs Makefile
# =====================

include ../Makefile.common
INTERRUPT_LIBS+=libinterrupt.a
CFLAGSlib+=-c


all: interrupt
interrupt: $(INTERRUPT_LIBS)
libinterrupt.a:
	@echo -n "Building $@ ..."
	
	@cd $(INTERRUPTLIB)/ && \
		$(CC) $(CFLAGSlib) \
			*.c
			
	@$(AR) cr $(INTERRUPTDIR)/$@ \
		$(INTERRUPTLIB)/*.o
	@echo "done."



.PHONY: interrupt clean tshow

clean:
	rm -f $(INTERRUPTLIB)/*.o
	rm -f $(INTERRUPT_LIBS)

tshow:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"




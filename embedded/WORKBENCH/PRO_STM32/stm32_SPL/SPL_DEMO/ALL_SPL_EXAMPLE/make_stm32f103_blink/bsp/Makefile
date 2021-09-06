# BSPlibs Makefile
# ================

include ../Makefile.common
BSP_LIBS+=libbsp.a
CFLAGSlib+=-c


all: bsp
bsp: $(BSP_LIBS)
libbsp.a:
	@echo -n "Building $@ ..."
	
	@cd $(BSPLIB)/ && \
		$(CC) $(CFLAGSlib) \
			*.c
			
	@$(AR) cr $(BSPDIR)/$@ \
		$(BSPLIB)/*.o
	@echo "done."



.PHONY: bsp clean tshow

clean:
	rm -f $(BSPLIB)/*.o
	rm -f $(BSP_LIBS)

tshow:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"




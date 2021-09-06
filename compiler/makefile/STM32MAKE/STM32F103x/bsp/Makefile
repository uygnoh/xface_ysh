# BSPlibs Makefile
# ================

include ../Makefile.common
BSP_LIBS+=libbsp.a
CFLAGSlib+=-c


all: bsp
bsp: $(BSP_LIBS)
libbsp.a:
	@echo -n "Building $@ ..."
	@cd $(BSPLIB)/src && \
		$(CC) $(CFLAGSlib) \
			-D"assert_param(expr)=((void)0)" \
			*.c
	@$(AR) cr $(BSPDIR)/$@ \
		$(BSPLIB)/src/*.o
	@echo "done."



.PHONY: bsp clean display

clean:
	rm -f $(BSPLIB)/src/*.o
	rm -f $(BSP_LIBS)

display:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"




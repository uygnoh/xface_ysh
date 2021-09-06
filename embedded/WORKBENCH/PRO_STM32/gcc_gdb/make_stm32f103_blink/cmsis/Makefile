# CMSISlibs Makefile
# ==================

include ../Makefile.common
CMSIS_LIBS+=libcmsis.a
CFLAGSlib+=-c


all: cmsis
cmsis: $(CMSIS_LIBS)
libcmsis.a:
	@echo -n "Building $@ ..."
	
	@cd $(CMSISLIB)/clock_init && \
		$(CC) $(CFLAGSlib) \
			*.c
	@cd $(CMSISLIB) && \
		$(CC) $(CFLAGSlib) \
			*.c
			
	@$(AR) cr $(CMSISDIR)/$@ \
		$(CMSISLIB)/clock_init/*.o \
		$(CMSISLIB)/*.o
		
	@echo "done."



.PHONY: cmsis clean tshow

clean:
	rm -f $(CMSISLIB)/clock_init/*.o
	rm -f $(CMSISLIB)/*.o
	rm -f $(CMSIS_LIBS)

tshow:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"




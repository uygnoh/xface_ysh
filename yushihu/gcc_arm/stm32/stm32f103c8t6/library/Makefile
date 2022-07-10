# STM32libs Makefile
# ==================

include ../common.mk
LIBS            += libstm32.a
CFLAGSLIB       += -c


all: library
library: $(LIBS)
libstm32.a:
	@echo -n "Building $@ ..."
	@cd $(YUSHIHU)/library/src && $(CC) $(CFLAGSLIB) \
		-D"assert_param(expr)=((void)0)" \
		-I$(INCLUDE) \
		*.c		
	@$(AR) cr $(YUSHIHU)/library/$@ $(YUSHIHU)/library/src/*.o
	@echo "done."


.PHONY: clean library tshow
clean:
	$(RM) $(YUSHIHU)/library/src/*.o
	$(RM) $(YUSHIHU)/library/$(LIBS)
tshow:
	@echo "################################################################"
	@echo "## optimize settings: $(INFO_TEXT_LIB), $(INFO_TEXT_USER) ###"
	@echo "################################################################"


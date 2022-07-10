# user Makefile

include ../common.mk

OBJS    := main.o
OBJS    += stm32f10x_it.o
OBJS    += system_stm32f10x.o
OBJS    += startup_stm32f10x_md.o
OBJS    += ../cmsis/core_cm3.o


all: user
user: app.a
app.a: $(OBJS)
	$(AR) cr app.a $(OBJS)

.PHONY: user clean cls tshow

clean:
	rm -f app.a $(OBJS)
	rm -f *.o

tshow:
	@echo "################################################################"
	@echo "## optimize settings: $(INFO_TEXT_LIB), $(INFO_TEXT_USER) ###"
	@echo "################################################################"	

# user Makefile

include ../Makefile.common
OBJS+=../boot/startup.o
OBJS+=main.o
OBJS+=stm32f10x_it.o



all: user
user: app.a
app.a: $(OBJS)
	$(AR) cr app.a $(OBJS)

.PHONY: user clean display

clean:
	rm -f app.a $(OBJS)

display:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"
	
	

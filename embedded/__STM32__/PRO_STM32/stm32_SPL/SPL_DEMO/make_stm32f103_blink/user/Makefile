# user Makefile

include ../Makefile.common
OBJS +=../startup/startup_stm32f10x_md.o
OBJS +=main.o


all: user
user: app.a
app.a: $(OBJS)
	$(AR) cr app.a $(OBJS)



.PHONY: user clean tshow

clean:
	rm -f app.a $(OBJS)

tshow:
	@echo "######################################################################################################"
	@echo "######## optimize settings: $(InfoTextLib), $(InfoTextSrc)"
	@echo "######################################################################################################"
	
	

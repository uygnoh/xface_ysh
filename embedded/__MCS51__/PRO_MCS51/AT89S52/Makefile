CC=sdcc

SOURCE = $(wildcard *.c)


all :
	$(CC) -mmcs51 $(SOURCE) 
hex:
	packihx '$(wildcard *.ihx)' > '$(patsubst %.ihx,%.hex,$(wildcard *.ihx))'

program : 
	sudo avrdude -p 8052 -c usbasp -e -U flash:w:'./$(wildcard *.ihx)'

.PHONY:	clean
clean:
	rm -f *.bak
	rm -f *.rel
	rm -f *.asm
	rm -f *.lst
	rm -f *.sym
	rm -f *.map
	rm -f *.lnk
	rm -f *.mem
	rm -f *.i
	rm -f *.d
	rm -f *.rst

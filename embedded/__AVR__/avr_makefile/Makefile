CC      = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS  = -Os -mmcu=atmega328p


TARGET  = main
SUBDIR  = $(shell ls -d */)
ROOTSRC = $(wildcard *.c)
ROOTOBJ = $(ROOTSRC:%.c=%.o)
SUBSRC  = $(shell find $(SUBDIR) -name '*.c')
SUBOBJ  = $(SUBSRC:%.c=%.o)


$(TARGET): $(ROOTOBJ) $(SUBOBJ)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(ROOTOBJ) $(SUBOBJ)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET).elf $(ROOTOBJ) $(SUBOBJ)

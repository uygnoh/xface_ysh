CC      = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS  = -Os -mmcu=atmega328p


TARGET  = main
ROOTSRC = $(wildcard *.c)
ROOTOBJ = $(patsubst %.c, %.o, $(ROOTSRC))
SUBDIR  = $(shell ls -d */)
SUBSRC  = $(shell find $(SUBDIR) -name '*.c')
SUBOBJ  = $(patsubst %.c, %.o, $(SUBSRC))


$(TARGET): $(ROOTOBJ) $(SUBOBJ)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(ROOTOBJ) $(SUBOBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET).elf $(ROOTOBJ) $(SUBOBJ)

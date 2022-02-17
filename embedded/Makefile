##******************************************************************************
###     => AVR-GCC atmega328p
##******************************************************************************
### AVR-GCC__编译器设定
###____________________________________________________________
CROSS_COMPILE   = avr-
AS              = $(CROSS_COMPILE)as
LD              = $(CROSS_COMPILE)ad
CC              = $(CROSS_COMPILE)gcc
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump


### AVR-GCC__编译器参数
###____________________________________________________________
CFLAGS          := -Wall -Os -g
CFLAGS          += -mmcu=atmega328p
CFLAGS          += -I $(shell pwd)/include


### Makefile（用于二级目录文件）
###____________________________________________________________
TARGET          = main
SUBDIR          = $(shell ls -d */)
ROOTSRC         = $(wildcard *.c)
ROOTOBJ         = $(patsubst %.c, %.o, $(ROOTOBJ))
SUBSRC          = $(shell find $(SUBDIR) -name '*.c')
SUBOBJ          = $(patsubst %.c, %.o, $(SUBOBJ))


$(TARGET): $(ROOTOBJ) $(SUBOBJ)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(ROOTOBJ) $(SUBOBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET).elf $(ROOTOBJ) $(SUBOBJ)

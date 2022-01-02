###____________________________________________________________
### AVR-GCC
###____________________________________________________________
### 读取当前目录的绝对路径，并保存在“TOP”中
TOP=$(shell readlink -f "$(dir $(lastword $(MAKEFILE_LIST)))")
CROSS_COMPILE   = avr-
AS              = $(CROSS_COMPILE)as
LD              = $(CROSS_COMPILE)ad
CC              = $(CROSS_COMPILE)gcc
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump



###____________________________________________________________
### 编译器参数
###____________________________________________________________
CFLAGS          := -Wall -Os -g
CFLAGS          += -mmcu=atmega328p
CFLAGS          += -I $(shell pwd)/include



###____________________________________________________________
### Makefile
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

###############################################################################
###     => GCC compiler toolchain
###############################################################################
PREFIX          ?= arm-none-eabi
#PREFIX         ?= arm-elf
CC              := $(PREFIX)-gcc
LD              := $(PREFIX)-gcc
AR              := $(PREFIX)-ar
AS              := $(PREFIX)-as
OBJCOPY         := $(PREFIX)-objcopy
OBJDUMP         := $(PREFIX)-objdump
GDB             := $(PREFIX)-gdb
SIZE            := $(PREFIX)-size



###############################################################################
###     => 头文件位置
###############################################################################
YUSHIHU         := $(shell readlink -f "$(dir $(lastword $(MAKEFILE_LIST)))")
INCLUDE	        := -I$(YUSHIHU)/include
INCLUDE	        += -I$(YUSHIHU)/user
INCLUDE	        += -I$(YUSHIHU)/cmsis
INCLUDE	        += -I$(YUSHIHU)/library
INCLUDE	        += -I$(YUSHIHU)/library/inc

PROGRAM         := main
#Adjust TYPE_OF_CPU in use, see CMSIS file "stm32f10x.h"
#STM32F103RBT (128KB FLASH, 20KB RAM) --> STM32F10X_MD
TYPE_OF_CPU     := STM32F10X_MD
#STM32F103RET (512KB FLASH, 64KB RAM) --> STM32F10X_HD
#TYPE_OF_CPU=STM32F10X_HD
COMMONFLAGS     := -g -mcpu=cortex-m3 -mthumb
COMMONFLAGSLIB  := $(COMMONFLAGS)



###############################################################################
###     => GCC 优化选项
###############################################################################
# 建议优化发布版本的设置： -O3
# 建议优化调试版本的设置： -O0
#       -O0     无需优化，减少编译时间，使调试产生预期效果
#       -O1     优化，减少代码大小和执行时间，而不增加编译时间
#       -O2     优化，与“O1”相比减少代码执行时间，增加编译时间
#       -O3     优化，打开所有优化，进一步增加编译时间
#       -Os     针对大小进行优化，启用通常不增加代码大小的所有“-O2”优化和其他代码大小优化
#       all     --> build all
#       library --> build library only
#       user    --> build user only
#       clean   --> clean project
#       tshow   --> show optimize settings
# Example:
#       make OptLIB=3 OptUSER=0 all tshow

#Commands for general Makefile and user Makefile 
ifeq ($(OptUSER),0)
	COMMONFLAGS+=-O0
	INFO_TEXT_USER=user (no optimize, -O0)
else ifeq ($(OptUSER),1)
	COMMONFLAGS+=-O1
	INFO_TEXT_USER=user (optimize time+ size+, -O1)
else ifeq ($(OptUSER),2)
 	COMMONFLAGS+=-O2
 	INFO_TEXT_USER=user (optimize time++ size+, -O2)
else ifeq ($(OptUSER),s)
 	COMMONFLAGS+=-Os
 	INFO_TEXT_USER=user (optimize size++, -Os)
else ifeq ($(OptUSER),3)
 	COMMONFLAGS+=-O3
 	INFO_TEXT_USER=user (full optimize, -O3) 	
else
 	COMMONFLAGS+=-O3
 	CFLAGS  += -D RELEASE_PUBLIC
 	INFO_TEXT_USER=user (full optimize and readout protected, -O4)
endif
CFLAGS          += $(COMMONFLAGS) -Wall -Werror $(INCLUDE)
CFLAGS          += -D $(TYPE_OF_CPU)
CFLAGS          += -D VECT_TAB_FLASH
CFLAGS          += -D USE_STDPERIPH_DRIVER

#Commands for library Makefile
ifeq ($(OptLIB),0)
	COMMONFLAGSLIB+=-O0
	INFO_TEXT_LIB=library (no optimize, -O0)
else ifeq ($(OptLIB),1)
	COMMONFLAGSLIB+=-O1
	INFO_TEXT_LIB=library (optimize time+ size+, -O1)
else ifeq ($(OptLIB),2)
 	COMMONFLAGSLIB+=-O2 
 	INFO_TEXT_LIB=library (optimize time++ size+, -O2)
else ifeq ($(OptLIB),s)
 	COMMONFLAGSLIB+=-Os 
 	INFO_TEXT_LIB=library (optimize size++, -Os)
else
 	COMMONFLAGSLIB+=-O3
 	INFO_TEXT_LIB=library (full optimize, -O3)
endif	
CFLAGSLIB       += $(COMMONFLAGSLIB) -Wall -Werror $(INCLUDE)
CFLAGSLIB       += -D $(TYPE_OF_CPU)
CFLAGSLIB       += -D VECT_TAB_FLASH
CFLAGSLIB       += -D USE_STDPERIPH_DRIVER

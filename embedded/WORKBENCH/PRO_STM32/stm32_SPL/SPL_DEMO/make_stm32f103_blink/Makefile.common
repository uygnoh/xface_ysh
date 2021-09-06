# public_makefile              
# ===============

#This file is included in the general Makefile, the libs Makefile and the src Makefile
#Different optimize settings for library and source files can be realized by using arguments
#Compiler optimize settings:
# -O0 no optimize, reduce compilation time and make debugging produce the expected results.
# -O1 optimize, reduce code size and execution time, without much increase of compilation time.
# -O2 optimize, reduce code execution time compared to ‘O1’, increase of compilation time.
# -O3 optimize, turns on all optimizations, further increase of compilation time. 
# -Os optimize for size, enables all ‘-O2’ optimizations that do not typically increase code size and other code size optimizations.
#Recommended optimize settings for release version: -O3
#Recommended optimize settings for debug version: -O0
#Valid parameters :
# OptLIB=0  --> optimize library files using the -O0 setting
# OptLIB=1  --> optimize library files using the -O1 setting
# OptLIB=2  --> optimize library files using the -O2 setting
# OptLIB=3  --> optimize library files using the -O3 setting(default)
# OptLIB=s  --> optimize library files using the -Os setting
# OptSRC=0  --> optimize user files using the -O0 setting
# OptSRC=1  --> optimize user files using the -O1 setting
# OptSRC=2  --> optimize user files using the -O2 setting
# OptSRC=3  --> optimize user files using the -O3 setting
# OptSRC=s  --> optimize user files using the -Os setting
# OptSRC=4  --> optimize source files using the -O3 setting,                 \
#           --> conditional compiling by use of define RELEASE_PUBLIC (default)
# all       --> build all
# libraries --> build libraries only
# user      --> build user only
# clean     --> clean project
# display   --> show optimize settings
#Example:
# % make OptLIB=3 OptSRC=0 all tshow

TOP=$(shell readlink -f "$(dir $(lastword $(MAKEFILE_LIST)))")
PROGRAM=main

#Adjust TypeOfMCU in use, see CMSIS file "stm32f10x.h"
#STM32F103RBT (128KB FLASH, 20KB RAM) --> STM32F10X_MD
TypeOfMCU=STM32F10X_MD
#STM32F103RET (512KB FLASH, 64KB RAM) --> STM32F10X_HD
#TypeOfMCU=STM32F10X_HD


TC              =arm-none-eabi
CC              =$(TC)-gcc
LD              =$(TC)-ld -v
OBJCOPY         =$(TC)-objcopy
AR              =$(TC)-ar
GDB             =$(TC)-gdb

INCLUDE	        =-I$(TOP)/include
INCLUDE	        =-I$(TOP)/startup
INCLUDE	        =-I$(TOP)/user

CMSISDIR        =$(TOP)/cmsis
CMSISLIB        =$(CMSISDIR)
INCLUDE	        +=-I$(CMSISLIB)/clock_init
INCLUDE	        +=-I$(CMSISLIB)

INTERRUPTDIR    =$(TOP)/interrupt
INTERRUPTLIB    =$(INTERRUPTDIR)
INCLUDE         +=-I$(INTERRUPTLIB)

STM32DIR        =$(TOP)/stm32
STM32LIB        =$(STM32DIR)
INCLUDE	        +=-I$(STM32LIB)/inc

BSPDIR          =$(TOP)/bsp
BSPLIB          =$(BSPDIR)
INCLUDE	        +=-I$(BSPLIB)



COMMONFLAGS     =-g -mcpu=cortex-m3 -mthumb
COMMONFLAGSlib  =$(COMMONFLAGS)



# Commands for general Makefile and user Makefile
# ===============================================
ifeq ($(OptSRC),0)
	COMMONFLAGS+=-O0
	InfoTextSrc=user (no optimize, -O0)
else ifeq ($(OptSRC),1)
	COMMONFLAGS+=-O1
	InfoTextSrc=user (optimize time+ size+, -O1)
else ifeq ($(OptSRC),2)
	COMMONFLAGS+=-O2
	InfoTextSrc=user (optimize time++ size+, -O2)
else ifeq ($(OptSRC),s)
	COMMONFLAGS+=-Os
	InfoTextSrc=user (optimize size++, -Os)
else ifeq ($(OptSRC),3)
	COMMONFLAGS+=-O3
	InfoTextSrc=user (full optimize, -O3)
else
	COMMONFLAGS+=-O3
	CFLAGS += -D RELEASE_PUBLIC
	InfoTextSrc=user (full optimize and readout protected, -O4)
endif
CFLAGS          +=$(COMMONFLAGS) -Wall -Werror $(INCLUDE)
CFLAGS          +=-D $(TypeOfMCU)
CFLAGS          +=-D VECT_TAB_FLASH
CFLAGS          +=-D USE_STDPERIPH_DRIVER


# Commands for Library Makefile
# ================================
ifeq ($(OptLIB),0)
	COMMONFLAGSlib+=-O0
	InfoTextLib=libraries (no optimize, -O0)
else ifeq ($(OptLIB),1)
	COMMONFLAGSlib+=-O1
	InfoTextLib=libraries (optimize time+ size+, -O1)
else ifeq ($(OptLIB),2)
	COMMONFLAGSlib+=-O2
	InfoTextLib=libraries (optimize time++ size+, -O2)
else ifeq ($(OptLIB),s)
	COMMONFLAGSlib+=-Os
	InfoTextLib=libraries (optimize size++, -Os)
else
	COMMONFLAGSlib+=-O3
	InfoTextLib=libraries (full optimize, -O3)
endif
CFLAGSlib       +=$(COMMONFLAGSlib) -Wall -Werror $(INCLUDE)
CFLAGSlib       +=-D $(TypeOfMCU)
CFLAGSlib       +=-D VECT_TAB_FLASH
CFLAGSlib       +=-D USE_STDPERIPH_DRIVER



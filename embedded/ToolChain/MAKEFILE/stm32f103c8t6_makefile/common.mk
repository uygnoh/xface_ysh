### 公用的Makefile文件
 
###_____________________________________________________________________________
### 建议优化发布版本的设置： -O3
### 建议优化调试版本的设置： -O0
# -O0 无需优化，减少编译时间，使调试产生预期效果
# -O1 优化，减少代码大小和执行时间，而不增加编译时间
# -O2 优化，与“O1”相比减少代码执行时间，增加编译时间
# -O3 优化，打开所有优化，进一步增加编译时间
# -Os 针对大小进行优化，启用通常不增加代码大小的所有“-O2”优化和其他代码大小优化
### 有效参数:
# OptLIB=0  --> 使用 -O0 设置优化库文件
# OptLIB=1  --> 使用 -O1 设置优化库文件
# OptLIB=2  --> 使用 -O2 设置优化库文件
# OptLIB=3  --> 使用 -O3 设置优化库文件（默认）
# OptLIB=s  --> 使用 -Os 设置优化库文件
# OptSRC=0  --> 使用 -O0 设置优化用户文件
# OptSRC=1  --> 使用 -O1 设置优化用户文件
# OptSRC=2  --> 使用 -O2 设置优化用户文件
# OptSRC=3  --> 使用 -O3 设置优化用户文件
# OptSRC=s  --> 使用 -Os 设置优化用户文件
# OptSRC=4  --> 使用 -O3 设置优化源文件, 使用define RELEASE_PUBLIC进行条件编译（默认）
### 例子：
# make OptLIB=0 OptSRC=0 all tshow
###_____________________________________________________________________________



### 读取当前目录的绝对路径，并保存在“TOP”中
TOP=$(shell readlink -f "$(dir $(lastword $(MAKEFILE_LIST)))")


### 编译所生成的文件名
PROGRAM=main


### 调整所使用的单片机类型
#STM32F103RBT (128KB FLASH, 20KB RAM) --> STM32F10X_MD
TypeOfMCU=STM32F10X_MD
#STM32F103RET (512KB FLASH, 64KB RAM) --> STM32F10X_HD
#TypeOfMCU=STM32F10X_HD


### arm-none-eabi编译器设置
TC              =arm-none-eabi
CC              =$(TC)-gcc
LD              =$(TC)-ld -v
OBJCOPY         =$(TC)-objcopy
AR              =$(TC)-ar
GDB             =$(TC)-gdb


### 头文件包括
INCLUDE	        +=-I$(TOP)/include
INCLUDE	        +=-I$(TOP)/startup
INCLUDE	        +=-I$(TOP)/user
### cmsis目录下的头文件包括
CMSISDIR        =$(TOP)/cmsis
CMSISLIB        =$(CMSISDIR)
INCLUDE	        +=-I$(CMSISLIB)/clock_setup
INCLUDE	        +=-I$(CMSISLIB)
### stm32目录下的头文件包括
STM32DIR        =$(TOP)/stm32
STM32LIB        =$(STM32DIR)
INCLUDE	        +=-I$(STM32LIB)/inc
### bsp目录下的头文件包括
BSPDIR          =$(TOP)/bsp
BSPLIB          =$(BSPDIR)
INCLUDE	        +=-I$(BSPLIB)


### STM32单片机编译选项
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

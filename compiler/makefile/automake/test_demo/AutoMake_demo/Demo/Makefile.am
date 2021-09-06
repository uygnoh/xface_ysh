### 指示 automake代码级别，默认级别为 GNU.
### GNU规定自由软件发布需要 NEW, README, AUTHORS, ChangLog说明文件，
### 这里降级为 foreign,从而避免准备这些文件。
AUTOMAKE_OPTIONS=foreign

### 打包 autogen.sh 文件
EXTRA_DIST=autogen.sh

### 指定需要处理的子目录，如果要处理多个子目录，以空格隔开，
### 这里只有：src, include 两个子目录文件
SUBDIRS=src include

### 利用PWD命令来获取当前目录路径
ROOTDIR=$(shell /bin/pwd)

###指定头文件所在路径，并导出供 子目录，Makefile.am 使用
INCLUDES=-I$(ROOTDIR)/include
export INCLUDES

### 指定要产生的执行文件名
bin_PROGRAMS=target

### 指定要产生的执行文件需要的源文件，如果有多个，以空格隔开，这里只有main.c
target_SOURCES=main.c

### 库文件名要和下一页的对应
### 利用 src 创建静态库文件
### 或者 LIBS+=... 增加链接库
### LIBS = -l xxx -l xxx    ###添加必要的库  
target_LDADD=$(ROOTDIR)/src/libmath.a

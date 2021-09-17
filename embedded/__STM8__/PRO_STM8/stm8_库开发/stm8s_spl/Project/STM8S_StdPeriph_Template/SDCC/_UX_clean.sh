#!/bin/bash 

# open terminal on double-click, skip else. See https://www.linuxquestions.org/questions/programming-9/executing-shell-script-in-terminal-directly-with-a-double-click-370091/
tty -s; if [ $? -ne 0 ]; then /etc/alternatives/x-terminal-emulator -e "$0"; exit; fi

# change to current working directory
cd `dirname $0`

# just for output
clear

# target device (for supported devices see stm8s.h)
DEVICE=STM8AF52Ax
#DEVICE=STM8S105

# set make tool (if not in PATH, set complete path)
MAKE=make

# use Makefiles to delete outputs
$MAKE -f Makefile DEVICE=$DEVICE clean 

#!/bin/bash
echo "*********************************";
echo "* jtagoocd for use with OpenOCD *";
echo "*      start/stop-utility       *";
echo "*********************************";

case "$1" in
	"1")	xterm -geometry 100x16+100+100 -bg blue -e "openocd -f openocd.cfg" &
		echo -e "INFO: OpenOCD started\n"
            ;;
	"0")	echo -e "INFO: OpenOCD stopped\n"
		pkill openocd
            ;;
        
	*)	echo "script usage:";
		echo  "    ./jtagoocd.sh [option]";
		echo  "where option includes:";
		echo  "    1        start OpenOCD";
		echo  "    0        stop OpenOCD";
		echo  "examples:";
		echo  "    ./jtagoocd.sh 1";
		echo -e "    ./jtagoocd.sh 0\n";
            ;;
esac

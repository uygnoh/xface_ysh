EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Memory_EEPROM:AT24CS02-MAHM U?
U 1 1 60EEF584
P 5600 3600
F 0 "U?" H 5600 4078 50  0000 C CNN
F 1 "AT24C02(2Kbit)" H 5600 3987 50  0000 C CNN
F 2 "Package_DFN_QFN:DFN-8-1EP_3x2mm_P0.5mm_EP1.3x1.5mm" H 5600 3600 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8815-SEEPROM-AT24CS01-02-Datasheet.pdf" H 5600 3600 50  0001 C CNN
	1    5600 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3500 5200 3600
Wire Wire Line
	5200 3600 5200 3700
Connection ~ 5200 3600
Wire Wire Line
	5200 3700 5200 3900
Wire Wire Line
	5200 3900 5600 3900
Connection ~ 5200 3700
$Comp
L power:GND #PWR?
U 1 1 60EEF70E
P 5600 3900
F 0 "#PWR?" H 5600 3650 50  0001 C CNN
F 1 "GND" H 5605 3727 50  0000 C CNN
F 2 "" H 5600 3900 50  0001 C CNN
F 3 "" H 5600 3900 50  0001 C CNN
	1    5600 3900
	1    0    0    -1  
$EndComp
Connection ~ 5600 3900
$Comp
L power:GND #PWR?
U 1 1 60EEF747
P 6000 3700
F 0 "#PWR?" H 6000 3450 50  0001 C CNN
F 1 "GND" H 6005 3527 50  0000 C CNN
F 2 "" H 6000 3700 50  0001 C CNN
F 3 "" H 6000 3700 50  0001 C CNN
	1    6000 3700
	1    0    0    -1  
$EndComp
$EndSCHEMATC

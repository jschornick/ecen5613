EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ecen5613_lab-cache
LIBS:switches
EELAYER 26 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 4 5
Title "ECEN5613 Lab"
Date "F2017"
Rev ""
Comp "Jeff Schornick"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DB9_MALE J5
U 1 1 59DD9815
P 5800 4000
F 0 "J5" H 5750 4550 50  0000 L CNN
F 1 "DB9_MALE" V 6000 3800 50  0000 L CNN
F 2 "" H 5800 4000 50  0001 C CNN
F 3 "" H 5800 4000 50  0001 C CNN
	1    5800 4000
	1    0    0    1   
$EndComp
$Comp
L CONN_01X09 J4
U 1 1 59DD981C
P 6400 2550
F 0 "J4" H 6350 2000 50  0000 L CNN
F 1 "CONN_01X09" H 6478 2500 50  0001 L CNN
F 2 "" H 6400 2550 50  0001 C CNN
F 3 "" H 6400 2550 50  0001 C CNN
	1    6400 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2150 6200 2150
Wire Wire Line
	6200 2250 5350 2250
Wire Wire Line
	5350 2450 6200 2450
Wire Wire Line
	6200 2550 5350 2550
Wire Wire Line
	5350 2650 6200 2650
Wire Wire Line
	5350 2750 6200 2750
Wire Wire Line
	6200 2950 5350 2950
Entry Wire Line
	5350 2150 5250 2250
Entry Wire Line
	5350 2250 5250 2350
Entry Wire Line
	5350 2350 5250 2450
Entry Wire Line
	5350 2450 5250 2550
Entry Wire Line
	5350 2550 5250 2650
Entry Wire Line
	5350 2650 5250 2750
Entry Wire Line
	5350 2750 5250 2850
Entry Wire Line
	5350 2850 5250 2950
Entry Wire Line
	5350 2950 5250 3050
Text Label 6200 2150 2    39   ~ 0
J5P1
Text Label 6200 2250 2    39   ~ 0
J5P2
Text Label 6200 2350 2    39   ~ 0
J5P3
Text Label 6200 2450 2    39   ~ 0
J5P4
Text Label 6200 2550 2    39   ~ 0
J5P5
Text Label 6200 2650 2    39   ~ 0
J5P6
Text Label 6200 2750 2    39   ~ 0
J5P7
Text Label 6200 2850 2    39   ~ 0
J5P8
Text Label 6200 2950 2    39   ~ 0
J5P9
Text Label 5500 3600 2    39   ~ 0
J5P1
Text Label 5500 3800 2    39   ~ 0
J5P2
Text Label 5500 4000 2    39   ~ 0
J5P3
Text Label 5500 4200 2    39   ~ 0
J5P4
Text Label 5500 4400 2    39   ~ 0
J5P5
Text Label 5500 3700 2    39   ~ 0
J5P6
Text Label 5500 3900 2    39   ~ 0
J5P7
Text Label 5500 4100 2    39   ~ 0
J5P8
Text Label 5500 4300 2    39   ~ 0
J5P9
Wire Wire Line
	5500 3600 5350 3600
Wire Wire Line
	5500 3700 5350 3700
Wire Wire Line
	5500 3800 5350 3800
Wire Wire Line
	5500 3900 5350 3900
Wire Wire Line
	5500 4000 5350 4000
Wire Wire Line
	5500 4100 5350 4100
Wire Wire Line
	5500 4200 5350 4200
Wire Wire Line
	5500 4300 5350 4300
Wire Wire Line
	5500 4400 5350 4400
Entry Wire Line
	5350 4400 5250 4300
Entry Wire Line
	5350 4300 5250 4200
Entry Wire Line
	5350 4200 5250 4100
Entry Wire Line
	5350 4100 5250 4000
Entry Wire Line
	5350 4000 5250 3900
Entry Wire Line
	5350 3900 5250 3800
Entry Wire Line
	5350 3800 5250 3700
Entry Wire Line
	5350 3700 5250 3600
Entry Wire Line
	5350 3600 5250 3500
Wire Bus Line
	5250 2250 5250 4300
Text Label 5250 3400 1    39   ~ 0
J5P[1..9]
$Comp
L C_Small C401
U 1 1 59DD9A05
P 1950 2800
F 0 "C401" H 2041 2846 50  0000 L CNN
F 1 "1uF" H 2041 2755 50  0000 L CNN
F 2 "" H 1950 2800 50  0001 C CNN
F 3 "" H 1950 2800 50  0001 C CNN
	1    1950 2800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2050 2650 1950 2650
Wire Wire Line
	1950 2650 1950 2700
Wire Wire Line
	1950 2900 1950 2950
Wire Wire Line
	1950 2950 2050 2950
$Comp
L C_Small C402
U 1 1 59DD9C2E
P 3750 2800
F 0 "C402" H 3842 2846 50  0000 L CNN
F 1 "1uF" H 3842 2755 50  0000 L CNN
F 2 "" H 3750 2800 50  0001 C CNN
F 3 "" H 3750 2800 50  0001 C CNN
	1    3750 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2650 3750 2650
Wire Wire Line
	3750 2650 3750 2700
Wire Wire Line
	3750 2900 3750 2950
Wire Wire Line
	3750 2950 3650 2950
$Comp
L C_Small C405
U 1 1 59DD9D40
P 2550 1900
F 0 "C405" V 2779 1900 50  0000 C CNN
F 1 "1uF" V 2688 1900 50  0000 C CNN
F 2 "" H 2550 1900 50  0001 C CNN
F 3 "" H 2550 1900 50  0001 C CNN
	1    2550 1900
	0    1    -1   0   
$EndComp
$Comp
L C_Small C403
U 1 1 59DD9EE9
P 3750 2200
F 0 "C403" H 3658 2154 50  0000 R CNN
F 1 "1uF" H 3658 2245 50  0000 R CNN
F 2 "" H 3750 2200 50  0001 C CNN
F 3 "" H 3750 2200 50  0001 C CNN
	1    3750 2200
	-1   0    0    1   
$EndComp
$Comp
L C_Small C404
U 1 1 59DD9FF1
P 3750 4350
F 0 "C404" H 3658 4304 50  0000 R CNN
F 1 "1uF" H 3658 4395 50  0000 R CNN
F 2 "" H 3750 4350 50  0001 C CNN
F 3 "" H 3750 4350 50  0001 C CNN
	1    3750 4350
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 59DDA04C
P 2850 4600
F 0 "#PWR?" H 2850 4350 50  0001 C CNN
F 1 "GND" H 2855 4427 50  0000 C CNN
F 2 "" H 2850 4600 50  0001 C CNN
F 3 "" H 2850 4600 50  0001 C CNN
	1    2850 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59DDA0BD
P 2350 2000
F 0 "#PWR?" H 2350 1750 50  0001 C CNN
F 1 "GND" H 2355 1827 50  0000 C CNN
F 2 "" H 2350 2000 50  0001 C CNN
F 3 "" H 2350 2000 50  0001 C CNN
	1    2350 2000
	1    0    0    -1  
$EndComp
$Comp
L MAX232_ALT U401
U 1 1 59DDBBDB
P 2850 3300
F 0 "U401" H 2850 3850 50  0000 C CNN
F 1 "MAX232" H 2850 3950 50  0000 C CNN
F 2 "" H 2900 2250 50  0001 L CNN
F 3 "" H 2925 3400 50  0001 C CNN
	1    2850 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2450 3750 2450
Wire Wire Line
	3750 2450 3750 2300
Wire Wire Line
	3750 1900 3750 2100
Wire Wire Line
	2650 1900 3750 1900
Wire Wire Line
	2850 1600 2850 2100
Connection ~ 2850 1900
Wire Wire Line
	2350 2000 2350 1900
Wire Wire Line
	2350 1900 2450 1900
Wire Wire Line
	2850 4500 2850 4600
Wire Wire Line
	2850 4550 4200 4550
Wire Wire Line
	3750 4550 3750 4450
Connection ~ 2850 4550
Wire Wire Line
	3650 4150 3750 4150
Wire Wire Line
	3750 4150 3750 4250
Wire Wire Line
	3650 3600 4200 3600
Wire Wire Line
	3650 3200 4200 3200
Wire Wire Line
	1500 3200 2050 3200
Wire Wire Line
	2050 3600 1500 3600
NoConn ~ 2050 3400
NoConn ~ 2050 3800
NoConn ~ 3650 3800
NoConn ~ 3650 3400
Text Notes 3700 3300 0    39   ~ 0
uC_Tx / PC_Rx
Text Notes 3700 3700 0    39   ~ 0
uC_Rx / PC_Tx
Text Label 3800 3600 0    39   ~ 0
TX_232
Text Label 3800 3200 0    39   ~ 0
RX_232
Wire Wire Line
	6200 2350 5350 2350
Text GLabel 4200 3600 2    39   Input ~ 0
J5P3
Text GLabel 4200 3200 2    39   Input ~ 0
J5P2
Text GLabel 4200 4550 2    39   Input ~ 0
J5P5
Connection ~ 3750 4550
Text HLabel 1500 3200 0    39   Input ~ 0
TX
Text HLabel 1500 3600 0    39   Input ~ 0
RX
Text Label 5600 2150 0    39   ~ 0
DCD_232
Text Label 5600 2450 0    39   ~ 0
DTR_232
Text Label 5650 2250 0    39   ~ 0
RX_232
Text Label 5650 2350 0    39   ~ 0
TX_232
Text Label 5650 2550 0    39   ~ 0
GND
Text Label 5600 2650 0    39   ~ 0
DSR_232
Text Label 5600 2750 0    39   ~ 0
RTS_232
Text Label 5600 2850 0    39   ~ 0
CTS_232
Text Label 5650 2950 0    39   ~ 0
RI_232
Wire Wire Line
	5350 2850 6200 2850
Connection ~ 5550 2850
Wire Wire Line
	5550 2150 5550 2650
Connection ~ 5550 2150
Connection ~ 5550 2450
Wire Wire Line
	5550 2750 5550 2850
Connection ~ 5550 2750
Connection ~ 5550 2650
Text GLabel 2850 1600 1    39   Input ~ 0
VCC
$EndSCHEMATC

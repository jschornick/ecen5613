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
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ecen5613_lab-cache
EELAYER 26 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 2 2
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
L Barrel_Jack J1
U 1 1 59CDDBBE
P 2700 1900
F 0 "J1" H 2700 2200 50  0000 C CNN
F 1 "2.1mm, Tip+" H 2600 2100 50  0000 C CNN
F 2 "" H 2750 1860 50  0001 C CNN
F 3 "" H 2750 1860 50  0001 C CNN
	1    2700 1900
	1    0    0    -1  
$EndComp
$Comp
L SW_SPDT_MSM SW1
U 1 1 59CDDBBF
P 3750 1300
F 0 "SW1" H 3750 1493 50  0000 C CNN
F 1 "SW_SPDT_MSM" H 3750 1494 50  0001 C CNN
F 2 "" H 3750 1300 50  0001 C CNN
F 3 "" H 3750 1300 50  0001 C CNN
	1    3750 1300
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D1
U 1 1 59CDDBC0
P 4000 2050
F 0 "D1" H 4000 1834 50  0000 C CNN
F 1 "1N4003" H 4000 1925 50  0000 C CNN
F 2 "" H 4000 2050 50  0001 C CNN
F 3 "" H 4000 2050 50  0001 C CNN
	1    4000 2050
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D2
U 1 1 59CDDBC1
P 4550 2050
F 0 "D2" H 4550 1834 50  0000 C CNN
F 1 "1N4003" H 4550 1925 50  0000 C CNN
F 2 "" H 4550 2050 50  0001 C CNN
F 3 "" H 4550 2050 50  0001 C CNN
	1    4550 2050
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D3
U 1 1 59CDDBC2
P 4000 2500
F 0 "D3" H 4000 2284 50  0000 C CNN
F 1 "1N4003" H 4000 2375 50  0000 C CNN
F 2 "" H 4000 2500 50  0001 C CNN
F 3 "" H 4000 2500 50  0001 C CNN
	1    4000 2500
	-1   0    0    1   
$EndComp
$Comp
L D_ALT D4
U 1 1 59CDDBC3
P 4550 2500
F 0 "D4" H 4550 2284 50  0000 C CNN
F 1 "1N4003" H 4550 2375 50  0000 C CNN
F 2 "" H 4550 2500 50  0001 C CNN
F 3 "" H 4550 2500 50  0001 C CNN
	1    4550 2500
	-1   0    0    1   
$EndComp
NoConn ~ 3950 1400
Wire Wire Line
	3000 1800 3250 1800
Wire Wire Line
	3250 1800 3250 1300
Wire Wire Line
	3000 2000 3250 2000
Wire Wire Line
	3250 2000 3250 2700
Wire Wire Line
	3250 1300 3550 1300
Wire Wire Line
	3950 1200 4300 1200
Wire Wire Line
	4300 1200 4300 2050
Wire Wire Line
	4150 2050 4400 2050
Connection ~ 4300 2050
Wire Wire Line
	3850 2050 3750 2050
Wire Wire Line
	3750 2050 3750 2500
Wire Wire Line
	3750 2500 3850 2500
Wire Wire Line
	4700 2050 4800 2050
Wire Wire Line
	4800 2050 4800 2500
Wire Wire Line
	4800 2500 4700 2500
Wire Wire Line
	3250 2700 4300 2700
Wire Wire Line
	4300 2700 4300 2500
Wire Wire Line
	4150 2500 4400 2500
Connection ~ 4300 2500
Wire Wire Line
	3550 2300 3550 2250
Wire Wire Line
	3550 2250 3750 2250
Connection ~ 3750 2250
Wire Wire Line
	4800 2250 5600 2250
Connection ~ 4800 2250
$Comp
L LM7805_TO220 U2
U 1 1 59CDDBC4
P 5900 2250
F 0 "U2" H 5900 2492 50  0000 C CNN
F 1 "GL7805" H 5900 2401 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220_Vertical" H 5900 2475 50  0001 C CIN
F 3 "" H 5900 2200 50  0001 C CNN
	1    5900 2250
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D5
U 1 1 59CDDBC5
P 5900 1750
F 0 "D5" H 5900 1966 50  0000 C CNN
F 1 "1N4003" H 5900 1875 50  0000 C CNN
F 2 "" H 5900 1750 50  0001 C CNN
F 3 "" H 5900 1750 50  0001 C CNN
	1    5900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1750 6350 2500
Wire Wire Line
	6350 1750 6050 1750
Wire Wire Line
	5750 1750 5400 1750
Wire Wire Line
	5400 1750 5400 2500
Connection ~ 5400 2250
$Comp
L CP1 C1
U 1 1 59CDDBC6
P 5400 2650
F 0 "C1" H 5515 2696 50  0000 L CNN
F 1 "0.1uF" H 5515 2605 50  0000 L CNN
F 2 "" H 5400 2650 50  0001 C CNN
F 3 "" H 5400 2650 50  0001 C CNN
	1    5400 2650
	1    0    0    -1  
$EndComp
$Comp
L CP1 C2
U 1 1 59CDDBC7
P 6350 2650
F 0 "C2" H 6465 2696 50  0000 L CNN
F 1 "47uF" H 6465 2605 50  0000 L CNN
F 2 "" H 6350 2650 50  0001 C CNN
F 3 "" H 6350 2650 50  0001 C CNN
	1    6350 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 59CDDBC8
P 3550 2300
F 0 "#PWR07" H 3550 2050 50  0001 C CNN
F 1 "GND" H 3555 2127 50  0000 C CNN
F 2 "" H 3550 2300 50  0001 C CNN
F 3 "" H 3550 2300 50  0001 C CNN
	1    3550 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 59CDDBC9
P 5900 3200
F 0 "#PWR08" H 5900 2950 50  0001 C CNN
F 1 "GND" H 5905 3027 50  0000 C CNN
F 2 "" H 5900 3200 50  0001 C CNN
F 3 "" H 5900 3200 50  0001 C CNN
	1    5900 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2550 5900 3200
Connection ~ 6350 2250
Wire Wire Line
	5400 2950 6350 2950
Connection ~ 5900 2950
Wire Wire Line
	5400 2800 5400 2950
Wire Wire Line
	6350 2950 6350 2800
$Comp
L CONN_02X01 J6
U 1 1 59CDDBCA
P 7050 2250
F 0 "J6" H 7050 2373 50  0000 C CNN
F 1 "CONN_02X01" H 7050 2374 50  0001 C CNN
F 2 "" H 7050 1050 50  0001 C CNN
F 3 "" H 7050 1050 50  0001 C CNN
	1    7050 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2250 6800 2250
$Comp
L LED_ALT D6
U 1 1 59CDDBCB
P 7600 2950
F 0 "D6" V 7638 2832 50  0000 R CNN
F 1 "RED_LED" V 7547 2832 50  0000 R CNN
F 2 "" H 7600 2950 50  0001 C CNN
F 3 "" H 7600 2950 50  0001 C CNN
	1    7600 2950
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 59CDDBCC
P 7600 2500
F 0 "R1" H 7670 2546 50  0000 L CNN
F 1 "330" H 7670 2455 50  0000 L CNN
F 2 "" V 7530 2500 50  0001 C CNN
F 3 "" H 7600 2500 50  0001 C CNN
	1    7600 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2250 8050 2250
Wire Wire Line
	7600 2250 7600 2350
Wire Wire Line
	7600 2650 7600 2800
$Comp
L GND #PWR09
U 1 1 59CDDBCD
P 7600 3200
F 0 "#PWR09" H 7600 2950 50  0001 C CNN
F 1 "GND" H 7605 3027 50  0000 C CNN
F 2 "" H 7600 3200 50  0001 C CNN
F 3 "" H 7600 3200 50  0001 C CNN
	1    7600 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3100 7600 3200
Connection ~ 7600 2250
Text Label 6450 2250 0    39   ~ 0
5V_OUT
Text Label 3100 1800 0    39   ~ 0
DC+
Text Label 3100 2000 0    39   ~ 0
DC-
Text Label 5000 2250 0    39   ~ 0
REG_IN
Wire Wire Line
	2500 4550 3450 4550
NoConn ~ 3000 1900
$Comp
L SW_Push SW2
U 1 1 59CDDBCE
P 2750 5000
F 0 "SW2" V 2796 4952 50  0000 R CNN
F 1 "RESET" V 2705 4952 50  0000 R CNN
F 2 "" H 2750 5200 50  0001 C CNN
F 3 "" H 2750 5200 50  0001 C CNN
	1    2750 5000
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 59CDDBCF
P 2750 5500
F 0 "R2" H 2820 5546 50  0000 L CNN
F 1 "330" H 2820 5455 50  0000 L CNN
F 2 "" V 2680 5500 50  0001 C CNN
F 3 "" H 2750 5500 50  0001 C CNN
	1    2750 5500
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D7
U 1 1 59CDDBD0
P 2750 6050
F 0 "D7" V 2704 6129 50  0000 L CNN
F 1 "1N4448" V 2795 6129 50  0000 L CNN
F 2 "" H 2750 6050 50  0001 C CNN
F 3 "" H 2750 6050 50  0001 C CNN
	1    2750 6050
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 4550 2750 4800
Wire Wire Line
	2750 5200 2750 5350
Wire Wire Line
	2750 5650 2750 5900
$Comp
L CP1 C3
U 1 1 59CDDBD1
P 3450 5250
F 0 "C3" H 3565 5296 50  0000 L CNN
F 1 "10uF" H 3565 5205 50  0000 L CNN
F 2 "" H 3450 5250 50  0001 C CNN
F 3 "" H 3450 5250 50  0001 C CNN
	1    3450 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4550 3450 5100
Connection ~ 2750 4550
Wire Wire Line
	3450 5400 3450 5900
Wire Wire Line
	2750 5800 3900 5800
Connection ~ 2750 5800
$Comp
L R R3
U 1 1 59CDDBD2
P 3450 6050
F 0 "R3" H 3520 6096 50  0000 L CNN
F 1 "10K" H 3520 6005 50  0000 L CNN
F 2 "" V 3380 6050 50  0001 C CNN
F 3 "" H 3450 6050 50  0001 C CNN
	1    3450 6050
	1    0    0    -1  
$EndComp
Connection ~ 3450 5800
Wire Wire Line
	2750 6200 2750 6350
Wire Wire Line
	3450 6350 3450 6200
$Comp
L GND #PWR010
U 1 1 59CDDBD3
P 3100 6450
F 0 "#PWR010" H 3100 6200 50  0001 C CNN
F 1 "GND" H 3105 6277 50  0000 C CNN
F 2 "" H 3100 6450 50  0001 C CNN
F 3 "" H 3100 6450 50  0001 C CNN
	1    3100 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 6350 3450 6350
Wire Wire Line
	3100 6350 3100 6450
Connection ~ 3100 6350
Wire Notes Line
	1900 4100 4500 4100
Wire Notes Line
	4500 4100 4500 7200
Wire Notes Line
	4500 7200 1900 7200
Wire Notes Line
	1900 7200 1900 4100
Wire Notes Line
	3000 3600 8550 3600
Wire Notes Line
	8550 3600 8550 850 
Wire Notes Line
	8550 850  1900 850 
Wire Notes Line
	1900 850  1900 3600
Wire Notes Line
	1900 3600 3050 3600
Text Notes 2000 3550 0    39   ~ 8
Power Regulation
Text Notes 2000 7150 0    39   ~ 8
Reset Circuit
Text Notes 3650 6950 0    30   ~ 0
Note: 40K-225K resistor between \nRST and GND internal to 8051
Text GLabel 2500 4550 0    60   Input ~ 0
VCC
Text HLabel 8050 2250 2    47   Input ~ 0
VCC
Text HLabel 3900 5800 2    47   Input ~ 0
RESET
$EndSCHEMATC
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
Sheet 1 5
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
L GND #PWR01
U 1 1 59CDD77F
P 2300 5400
F 0 "#PWR01" H 2300 5150 50  0001 C CNN
F 1 "GND" H 2305 5227 50  0000 C CNN
F 2 "" H 2300 5400 50  0001 C CNN
F 3 "" H 2300 5400 50  0001 C CNN
	1    2300 5400
	1    0    0    -1  
$EndComp
$Comp
L 74LS373_Latch U3
U 1 1 59CDD782
P 5600 2400
F 0 "U3" H 5900 2300 60  0000 C CNN
F 1 "74LS373" H 5900 2200 60  0000 C CNN
F 2 "" H 5600 2400 60  0001 C CNN
F 3 "" H 5600 2400 60  0001 C CNN
	1    5600 2400
	1    0    0    -1  
$EndComp
$Comp
L R_Network09 RN?
U 1 1 59CDD784
P 5150 1000
F 0 "RN?" H 5630 1046 50  0001 L CNN
F 1 "2.7K" H 5100 1200 50  0000 L CNN
F 2 "Resistors_THT:R_Array_SIP10" V 5725 1000 50  0001 C CNN
F 3 "" H 5150 1000 50  0001 C CNN
	1    5150 1000
	1    0    0    -1  
$EndComp
NoConn ~ 5550 1200
$Comp
L CONN_02X01 J?
U 1 1 59CDD785
P 7450 3450
F 0 "J?" H 7450 3665 50  0001 C CNN
F 1 "CONN_02X01" H 7450 3574 50  0001 C CNN
F 2 "" H 7450 2250 50  0001 C CNN
F 3 "" H 7450 2250 50  0001 C CNN
	1    7450 3450
	-1   0    0    1   
$EndComp
Text GLabel 7200 3450 0    39   UnSpc ~ 0
VCC
$Comp
L GND #PWR02
U 1 1 59CDD786
P 5900 3750
F 0 "#PWR02" H 5900 3500 50  0001 C CNN
F 1 "GND" H 5905 3577 50  0000 C CNN
F 2 "" H 5900 3750 50  0001 C CNN
F 3 "" H 5900 3750 50  0001 C CNN
	1    5900 3750
	1    0    0    -1  
$EndComp
$Comp
L ATF16V8C U6
U 1 1 59CDD787
P 5600 6350
F 0 "U6" H 5900 7350 60  0000 C CNN
F 1 "ATF16V8C" H 5900 7250 60  0000 C CNN
F 2 "" H 5000 6800 60  0001 C CNN
F 3 "" H 5000 6800 60  0001 C CNN
	1    5600 6350
	1    0    0    -1  
$EndComp
Text GLabel 4000 4500 2    39   Output ~ 0
ALE
Text GLabel 5350 2100 0    39   Input ~ 0
ALE
$Comp
L GND #PWR03
U 1 1 59CDD789
P 5750 6800
F 0 "#PWR03" H 5750 6550 50  0001 C CNN
F 1 "GND" H 5750 6650 50  0000 C CNN
F 2 "" H 5750 6800 50  0001 C CNN
F 3 "" H 5750 6800 50  0001 C CNN
	1    5750 6800
	1    0    0    -1  
$EndComp
Text GLabel 5750 4700 0    39   UnSpc ~ 0
V_MCU
$Sheet
S 800  1350 700  550 
U 59CDDA14
F0 "Power" 60
F1 "power.sch" 60
F2 "VCC" I R 1500 1550 39 
F3 "RESET" I R 1500 1700 39 
$EndSheet
$Comp
L Crystal Y1
U 1 1 59CDDF3A
P 1350 4750
F 0 "Y1" V 1350 4900 39  0000 L CNN
F 1 "11.0592MHz" V 1400 4900 39  0000 L CNN
F 2 "" H 1350 4750 50  0001 C CNN
F 3 "" H 1350 4750 50  0001 C CNN
	1    1350 4750
	0    1    1    0   
$EndComp
$Comp
L C C5
U 1 1 59CDDF41
P 1050 4500
F 0 "C5" V 1200 4500 39  0000 C CNN
F 1 "27pF" V 1250 4500 39  0000 C CNN
F 2 "" H 1088 4350 50  0001 C CNN
F 3 "" H 1050 4500 50  0001 C CNN
	1    1050 4500
	0    1    1    0   
$EndComp
$Comp
L C C6
U 1 1 59CDDF48
P 1050 5050
F 0 "C6" V 1200 5050 39  0000 C CNN
F 1 "27pF" V 1250 5050 39  0000 C CNN
F 2 "" H 1088 4900 50  0001 C CNN
F 3 "" H 1050 5050 50  0001 C CNN
	1    1050 5050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR04
U 1 1 59CDDF5A
P 800 5350
F 0 "#PWR04" H 800 5100 50  0001 C CNN
F 1 "GND" H 805 5177 50  0000 C CNN
F 2 "" H 800 5350 50  0001 C CNN
F 3 "" H 800 5350 50  0001 C CNN
	1    800  5350
	1    0    0    -1  
$EndComp
$Comp
L Q_PNP_EBC Q1
U 1 1 59CE0FA5
P 1250 3100
F 0 "Q1" H 1441 3054 50  0000 L CNN
F 1 "2N2907" H 1441 3145 50  0000 L CNN
F 2 "" H 1450 3200 50  0001 C CNN
F 3 "" H 1250 3100 50  0001 C CNN
	1    1250 3100
	-1   0    0    1   
$EndComp
$Comp
L R R5
U 1 1 59CE0FA6
P 1150 3450
F 0 "R5" H 1200 3450 50  0000 L CNN
F 1 "330" V 1150 3450 39  0000 C CNN
F 2 "" V 1080 3450 50  0001 C CNN
F 3 "" H 1150 3450 50  0001 C CNN
	1    1150 3450
	-1   0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 59CE0FA7
P 1650 3100
F 0 "R4" V 1550 3100 50  0000 C CNN
F 1 "1000" V 1650 3100 39  0000 C CNN
F 2 "" V 1580 3100 50  0001 C CNN
F 3 "" H 1650 3100 50  0001 C CNN
	1    1650 3100
	0    -1   1    0   
$EndComp
$Comp
L LED_ALT D8
U 1 1 59CE0FA8
P 1150 3750
F 0 "D8" V 1188 3632 50  0000 R CNN
F 1 "GREEN_LED" V 1097 3632 50  0000 R CNN
F 2 "" H 1150 3750 50  0001 C CNN
F 3 "" H 1150 3750 50  0001 C CNN
	1    1150 3750
	0    1    -1   0   
$EndComp
Text GLabel 1150 2800 1    39   Input ~ 0
VCC
$Comp
L GND #PWR06
U 1 1 59CE0FA9
P 1150 3950
F 0 "#PWR06" H 1150 3700 50  0001 C CNN
F 1 "GND" H 1155 3777 50  0000 C CNN
F 2 "" H 1150 3950 50  0001 C CNN
F 3 "" H 1150 3950 50  0001 C CNN
	1    1150 3950
	-1   0    0    -1  
$EndComp
Entry Wire Line
	5450 1400 5350 1500
Entry Wire Line
	5350 1400 5250 1500
Entry Wire Line
	5250 1400 5150 1500
Entry Wire Line
	5150 1400 5050 1500
Entry Wire Line
	5050 1400 4950 1500
Entry Wire Line
	4950 1400 4850 1500
Entry Wire Line
	4850 1400 4750 1500
Entry Wire Line
	4750 1400 4650 1500
Text Label 4050 2100 0    39   ~ 0
AD0
Text Label 4050 2250 0    39   ~ 0
AD1
Text Label 4050 2400 0    39   ~ 0
AD2
Text Label 4050 2550 0    39   ~ 0
AD3
Text Label 4050 2700 0    39   ~ 0
AD4
Text Label 4050 2850 0    39   ~ 0
AD5
Text Label 4050 3000 0    39   ~ 0
AD6
Text Label 4050 3150 0    39   ~ 0
AD7
Entry Wire Line
	5000 2150 5100 2250
Entry Wire Line
	5000 2150 5100 2250
Entry Wire Line
	5000 2300 5100 2400
Entry Wire Line
	5000 2450 5100 2550
Entry Wire Line
	5000 2600 5100 2700
Entry Wire Line
	5000 2750 5100 2850
Entry Wire Line
	5000 2900 5100 3000
Entry Wire Line
	5000 3050 5100 3150
Entry Wire Line
	5000 3200 5100 3300
Text Label 5200 2250 0    39   ~ 0
AD0
Text Label 5200 2400 0    39   ~ 0
AD1
Text Label 5200 2550 0    39   ~ 0
AD2
Text Label 5200 2700 0    39   ~ 0
AD3
Text Label 5200 2850 0    39   ~ 0
AD4
Text Label 5200 3000 0    39   ~ 0
AD5
Text Label 5200 3150 0    39   ~ 0
AD6
Text Label 5200 3300 0    39   ~ 0
AD7
$Comp
L CONN_02X01 J?
U 1 1 59CDD783
P 2650 1550
F 0 "J?" H 2650 1765 50  0001 C CNN
F 1 "CONN_02X01" H 2650 1674 50  0001 C CNN
F 2 "" H 2650 350 50  0001 C CNN
F 3 "" H 2650 350 50  0001 C CNN
	1    2650 1550
	1    0    0    -1  
$EndComp
Text Label 5450 1200 3    39   ~ 0
AD0
Text Label 5350 1200 3    39   ~ 0
AD1
Text Label 5250 1200 3    39   ~ 0
AD2
Text Label 5150 1200 3    39   ~ 0
AD3
Text Label 5050 1200 3    39   ~ 0
AD4
Text Label 4950 1200 3    39   ~ 0
AD5
Text Label 4850 1200 3    39   ~ 0
AD6
Text Label 4750 1200 3    39   ~ 0
AD7
$Comp
L bq4011YMA-100 U4
U 1 1 59CE7C64
P 7550 4800
F 0 "U4" H 7600 5600 39  0000 C CNN
F 1 "bq4011YMA-100" H 7600 5550 39  0000 C CNN
F 2 "" H 7800 4300 39  0001 C CNN
F 3 "" H 7800 4300 39  0001 C CNN
	1    7550 4800
	1    0    0    -1  
$EndComp
Text GLabel 3050 1100 2    39   UnSpc ~ 0
V_MCU
Entry Wire Line
	6600 2250 6700 2350
Entry Wire Line
	6600 2400 6700 2500
Entry Wire Line
	6600 2550 6700 2650
Entry Wire Line
	6600 2700 6700 2800
Entry Wire Line
	6600 2850 6700 2950
Entry Wire Line
	6600 3000 6700 3100
Entry Wire Line
	6600 3150 6700 3250
Entry Wire Line
	6600 3300 6700 3400
Text Label 6450 2250 0    39   ~ 0
A0
Text Label 6450 2400 0    39   ~ 0
A1
Text Label 6450 2550 0    39   ~ 0
A2
Text Label 6450 2700 0    39   ~ 0
A3
Text Label 6450 2850 0    39   ~ 0
A4
Text Label 6450 3000 0    39   ~ 0
A5
Text Label 6450 3150 0    39   ~ 0
A6
Text Label 6450 3300 0    39   ~ 0
A7
Text Label 6800 3750 0    39   ~ 0
A0
Text Label 6800 3900 0    39   ~ 0
A1
Text Label 6800 4050 0    39   ~ 0
A2
Text Label 6800 4200 0    39   ~ 0
A3
Text Label 6800 4350 0    39   ~ 0
A4
Text Label 6800 4500 0    39   ~ 0
A5
Text Label 6800 4650 0    39   ~ 0
A6
Text Label 6800 4800 0    39   ~ 0
A7
Text Label 6800 4950 0    39   ~ 0
A8
Text Label 6800 5100 0    39   ~ 0
A9
Text Label 6800 5250 0    39   ~ 0
A10
Text Label 6800 5400 0    39   ~ 0
A11
Text Label 6800 5550 0    39   ~ 0
A12
Text Label 6800 5700 0    39   ~ 0
A13
Text Label 6800 5850 0    39   ~ 0
A14
Entry Wire Line
	6700 3650 6800 3750
Entry Wire Line
	6700 3800 6800 3900
Entry Wire Line
	6700 3950 6800 4050
Entry Wire Line
	6700 4100 6800 4200
Entry Wire Line
	6700 4250 6800 4350
Entry Wire Line
	6700 4400 6800 4500
Entry Wire Line
	6700 4550 6800 4650
Entry Wire Line
	6700 4700 6800 4800
$Comp
L GND #PWR?
U 1 1 59CE9B17
P 7700 6500
F 0 "#PWR?" H 7700 6250 50  0001 C CNN
F 1 "GND" H 7705 6327 50  0000 C CNN
F 2 "" H 7700 6500 50  0001 C CNN
F 3 "" H 7700 6500 50  0001 C CNN
	1    7700 6500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59CEA6A2
P 6450 1850
F 0 "#PWR?" H 6450 1600 50  0001 C CNN
F 1 "GND" H 6455 1677 50  0000 C CNN
F 2 "" H 6450 1850 50  0001 C CNN
F 3 "" H 6450 1850 50  0001 C CNN
	1    6450 1850
	1    0    0    -1  
$EndComp
$Comp
L C_Small C21
U 1 1 59CEA6A8
P 6150 1850
F 0 "C21" V 6300 1800 39  0000 L CNN
F 1 "0.1uF" V 6250 1750 39  0000 L CNN
F 2 "" H 6150 1850 50  0001 C CNN
F 3 "" H 6150 1850 50  0001 C CNN
	1    6150 1850
	0    -1   -1   0   
$EndComp
$Comp
L CONN_02X01 J?
U 1 1 59CEA6E0
P 5650 1850
F 0 "J?" H 5650 2065 50  0001 C CNN
F 1 "CONN_02X01" H 5650 1974 50  0001 C CNN
F 2 "" H 5650 650 50  0001 C CNN
F 3 "" H 5650 650 50  0001 C CNN
	1    5650 1850
	1    0    0    -1  
$EndComp
Text GLabel 5350 1850 0    39   UnSpc ~ 0
VCC
$Comp
L GND #PWR?
U 1 1 59CEAE58
P 8300 3450
F 0 "#PWR?" H 8300 3200 50  0001 C CNN
F 1 "GND" H 8305 3277 50  0000 C CNN
F 2 "" H 8300 3450 50  0001 C CNN
F 3 "" H 8300 3450 50  0001 C CNN
	1    8300 3450
	1    0    0    -1  
$EndComp
$Comp
L C_Small C23
U 1 1 59CEAE5E
P 8000 3450
F 0 "C23" V 8150 3400 39  0000 L CNN
F 1 "0.1uF" V 8100 3350 39  0000 L CNN
F 2 "" H 8000 3450 50  0001 C CNN
F 3 "" H 8000 3450 50  0001 C CNN
	1    8000 3450
	0    -1   -1   0   
$EndComp
Entry Wire Line
	8400 5400 8500 5300
Entry Wire Line
	8400 5250 8500 5150
Entry Wire Line
	8400 5100 8500 5000
Entry Wire Line
	8400 4950 8500 4850
Entry Wire Line
	8400 4800 8500 4700
Entry Wire Line
	8400 4650 8500 4550
Entry Wire Line
	8400 4500 8500 4400
Entry Wire Line
	8400 4350 8500 4250
Text Label 8250 4350 0    39   ~ 0
AD0
Text Label 8250 4500 0    39   ~ 0
AD1
Text Label 8250 4650 0    39   ~ 0
AD2
Text Label 8250 4800 0    39   ~ 0
AD3
Text Label 8250 4950 0    39   ~ 0
AD4
Text Label 8250 5100 0    39   ~ 0
AD5
Text Label 8250 5250 0    39   ~ 0
AD6
Text Label 8250 5400 0    39   ~ 0
AD7
Text Label 6750 1500 0    39   ~ 0
AD[0..7]
Entry Wire Line
	4300 3300 4400 3400
Entry Wire Line
	4300 3450 4400 3550
Entry Wire Line
	4300 3600 4400 3700
Entry Wire Line
	4300 3750 4400 3850
Entry Wire Line
	4300 3900 4400 4000
Entry Wire Line
	4300 4050 4400 4150
Entry Wire Line
	4300 4200 4400 4300
Entry Wire Line
	4850 4400 4950 4500
Entry Wire Line
	4750 4400 4850 4500
Entry Wire Line
	4650 4400 4750 4500
NoConn ~ 5200 5100
NoConn ~ 5200 5850
Text Label 4950 4500 3    39   ~ 0
A12
Text Label 4850 4500 3    39   ~ 0
A13
Text Label 4750 4500 3    39   ~ 0
A14
Text Label 5200 4400 0    39   ~ 0
A[8..14]
Text Label 6700 3450 3    39   ~ 0
A[0..7]
Wire Wire Line
	2300 5100 2300 5400
Wire Wire Line
	5400 2100 5350 2100
Wire Wire Line
	1500 1550 2400 1550
Wire Wire Line
	5750 4700 5750 4900
Wire Wire Line
	5900 3650 5900 3750
Wire Wire Line
	5400 3450 5400 3700
Wire Wire Line
	5400 3700 5900 3700
Connection ~ 5900 3700
Wire Wire Line
	5750 6800 5750 6650
Wire Wire Line
	800  5050 900  5050
Wire Wire Line
	1200 5050 1950 5050
Wire Wire Line
	1350 4900 1350 5050
Wire Wire Line
	800  4500 800  5350
Wire Wire Line
	1350 4500 1350 4600
Wire Wire Line
	1200 4500 2000 4500
Wire Wire Line
	900  4500 800  4500
Connection ~ 800  5050
Connection ~ 1350 5050
Wire Wire Line
	1150 2900 1150 2800
Wire Wire Line
	1150 3900 1150 3950
Wire Wire Line
	3950 2100 4300 2100
Wire Wire Line
	3950 2250 4300 2250
Wire Wire Line
	3950 2400 4300 2400
Wire Wire Line
	3950 2550 4300 2550
Wire Wire Line
	3950 2700 4300 2700
Wire Wire Line
	3950 2850 4300 2850
Wire Wire Line
	3950 3000 4300 3000
Wire Wire Line
	3950 3150 4300 3150
Connection ~ 3000 1550
Wire Wire Line
	5450 1200 5450 1400
Wire Wire Line
	5350 1200 5350 1400
Wire Wire Line
	5250 1200 5250 1400
Wire Wire Line
	5150 1200 5150 1400
Wire Wire Line
	5050 1200 5050 1400
Wire Wire Line
	4950 1200 4950 1400
Wire Wire Line
	4850 1200 4850 1400
Wire Wire Line
	4750 1200 4750 1400
Connection ~ 1350 4500
Wire Wire Line
	5100 2250 5400 2250
Wire Wire Line
	5100 2400 5400 2400
Wire Wire Line
	5100 2550 5400 2550
Wire Wire Line
	5100 2700 5400 2700
Wire Wire Line
	5100 2850 5400 2850
Wire Wire Line
	5100 3000 5400 3000
Wire Wire Line
	5100 3150 5400 3150
Wire Wire Line
	5100 3300 5400 3300
Wire Wire Line
	2000 4650 1950 4650
Wire Wire Line
	1950 4650 1950 5050
Wire Bus Line
	5000 2150 5000 3200
Wire Wire Line
	3950 3300 4300 3300
Wire Wire Line
	3950 3450 4300 3450
Wire Wire Line
	3950 3600 4300 3600
Wire Wire Line
	3950 3750 4300 3750
Wire Wire Line
	3950 4500 4000 4500
Wire Wire Line
	3000 800  3000 1900
Wire Wire Line
	3000 1100 3050 1100
Wire Wire Line
	6400 2250 6600 2250
Wire Wire Line
	6400 2400 6600 2400
Wire Wire Line
	6400 2550 6600 2550
Wire Wire Line
	6400 2700 6600 2700
Wire Wire Line
	6400 2850 6600 2850
Wire Wire Line
	6400 3000 6600 3000
Wire Wire Line
	6400 3150 6600 3150
Wire Wire Line
	6400 3300 6600 3300
Wire Bus Line
	6700 2350 6700 4700
Wire Wire Line
	6950 3750 6800 3750
Wire Wire Line
	6950 3900 6800 3900
Wire Wire Line
	6950 4050 6800 4050
Wire Wire Line
	6950 4200 6800 4200
Wire Wire Line
	6950 4350 6800 4350
Wire Wire Line
	6950 4500 6800 4500
Wire Wire Line
	6950 4650 6800 4650
Wire Wire Line
	6950 4800 6800 4800
Wire Wire Line
	6950 4950 6800 4950
Wire Wire Line
	6950 5100 6800 5100
Wire Wire Line
	6950 5250 6800 5250
Wire Wire Line
	6950 5400 6800 5400
Wire Wire Line
	6950 5550 6800 5550
Wire Wire Line
	6950 5700 6800 5700
Wire Wire Line
	6950 5850 6800 5850
Wire Wire Line
	8200 4350 8400 4350
Wire Wire Line
	8200 4500 8400 4500
Wire Wire Line
	8200 4650 8400 4650
Wire Wire Line
	8200 4800 8400 4800
Wire Wire Line
	8200 4950 8400 4950
Wire Wire Line
	8200 5100 8400 5100
Wire Wire Line
	8200 5250 8400 5250
Wire Wire Line
	8200 5400 8400 5400
Wire Wire Line
	2900 1550 3250 1550
Wire Wire Line
	5350 1850 5400 1850
Wire Wire Line
	5900 1850 5900 1900
Wire Wire Line
	5900 1850 6050 1850
Wire Wire Line
	6250 1850 6450 1850
Wire Wire Line
	8100 3450 8300 3450
Wire Wire Line
	7700 3450 7900 3450
Wire Wire Line
	3950 3900 4300 3900
Wire Wire Line
	3950 4050 4300 4050
Wire Wire Line
	3950 4200 4300 4200
Text Label 4050 3300 0    39   ~ 0
A8
Text Label 4050 3450 0    39   ~ 0
A9
Text Label 4050 3600 0    39   ~ 0
A10
Text Label 4050 3750 0    39   ~ 0
A11
Text Label 4050 3900 0    39   ~ 0
A12
Text Label 4050 4050 0    39   ~ 0
A13
Text Label 4050 4200 0    39   ~ 0
A14
Wire Bus Line
	4400 3400 4400 4300
Wire Wire Line
	7700 3450 7700 3550
Connection ~ 7700 3450
Wire Bus Line
	4500 2050 4900 2050
Text Label 4600 2050 0    39   ~ 0
AD[0..7]
Wire Bus Line
	4400 4300 4500 4400
Wire Bus Line
	4500 4400 6550 4400
Entry Wire Line
	4300 2100 4400 2000
Entry Wire Line
	4300 2250 4400 2150
Entry Wire Line
	4300 2400 4400 2300
Entry Wire Line
	4300 2550 4400 2450
Entry Wire Line
	4300 2700 4400 2600
Entry Wire Line
	4300 2850 4400 2750
Entry Wire Line
	4300 3000 4400 2900
Entry Wire Line
	4300 3150 4400 3050
Wire Bus Line
	4400 1500 4400 3050
Entry Wire Line
	6700 5750 6800 5850
Entry Wire Line
	6700 5600 6800 5700
Entry Wire Line
	6700 5450 6800 5550
Entry Wire Line
	6700 5300 6800 5400
Entry Wire Line
	6700 5150 6800 5250
Entry Wire Line
	6700 5000 6800 5100
Entry Wire Line
	6700 4850 6800 4950
$Comp
L GND #PWR?
U 1 1 59CF2B6F
P 3650 1550
F 0 "#PWR?" H 3650 1300 50  0001 C CNN
F 1 "GND" H 3655 1377 50  0000 C CNN
F 2 "" H 3650 1550 50  0001 C CNN
F 3 "" H 3650 1550 50  0001 C CNN
	1    3650 1550
	1    0    0    -1  
$EndComp
$Comp
L C_Small C20
U 1 1 59CF2B75
P 3350 1550
F 0 "C20" V 3500 1500 39  0000 L CNN
F 1 "0.1uF" V 3450 1450 39  0000 L CNN
F 2 "" H 3350 1550 50  0001 C CNN
F 3 "" H 3350 1550 50  0001 C CNN
	1    3350 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3450 1550 3650 1550
Wire Bus Line
	4900 2050 5000 2150
Wire Bus Line
	6700 4850 6550 4700
Wire Wire Line
	3950 4350 4250 4350
Wire Wire Line
	4250 4350 4250 5700
Wire Wire Line
	4250 5700 5200 5700
Wire Wire Line
	4950 4500 4950 5250
Wire Wire Line
	4950 5250 5200 5250
Wire Wire Line
	4850 4500 4850 5400
Wire Wire Line
	4850 5400 5200 5400
Wire Wire Line
	4750 4500 4750 5550
Wire Wire Line
	4750 5550 5200 5550
Wire Wire Line
	3600 6150 5200 6150
Wire Wire Line
	6300 6000 6950 6000
Wire Bus Line
	8500 1500 8500 5300
Wire Bus Line
	4400 1500 9000 1500
Wire Bus Line
	6550 4700 6550 4400
Wire Bus Line
	6700 4850 6700 5750
Wire Wire Line
	3000 800  4750 800 
Wire Wire Line
	1500 1700 1750 1700
Wire Wire Line
	1750 1700 1750 2200
Wire Wire Line
	1750 2200 2000 2200
Connection ~ 3000 1100
Wire Bus Line
	4500 2050 4400 1950
Text GLabel 6400 6300 2    39   Output ~ 0
DEBUG
Wire Wire Line
	6300 6300 6400 6300
$Sheet
S 9000 1300 550  400 
U 59D6D316
F0 "Debug" 39
F1 "debug.sch" 39
F2 "AD[0..7]" I L 9000 1500 39 
$EndSheet
Text Notes 5550 5600 0    39   ~ 0
(SPLD code: lab.pld)
$Sheet
S 2000 5800 600  500 
U 59DD9602
F0 "Serial" 39
F1 "serial.sch" 39
F2 "TX" I R 2600 6150 39 
F3 "RX" I R 2600 6000 39 
$EndSheet
Wire Wire Line
	1500 3100 1450 3100
$Comp
L AT89C51RC2 U1
U 1 1 59DE17AD
P 3000 3500
F 0 "U1" H 3000 4400 60  0000 C CNN
F 1 "AT89C51RC2" H 3000 4300 60  0000 C CNN
F 2 "" H 2650 4100 60  0001 C CNN
F 3 "" H 2650 4100 60  0001 C CNN
	1    3000 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 5100 3600 6150
Wire Wire Line
	5200 6300 3450 6300
Wire Wire Line
	3450 5100 3450 6700
$Comp
L SW_Push SW3
U 1 1 59DE4249
P 3700 6700
F 0 "SW3" H 3700 6515 50  0000 C CNN
F 1 "Bootloader" H 3700 6606 50  0000 C CNN
F 2 "" H 3700 6900 50  0001 C CNN
F 3 "" H 3700 6900 50  0001 C CNN
	1    3700 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5100 2700 6000
Wire Wire Line
	2700 6000 2600 6000
Wire Wire Line
	2850 5100 2850 6150
Wire Wire Line
	2850 6150 2600 6150
Wire Wire Line
	3450 6700 3500 6700
Connection ~ 3450 6300
$Comp
L R R6
U 1 1 59DE66D4
P 4100 6700
F 0 "R6" V 4000 6700 50  0000 C CNN
F 1 "1000" V 4100 6700 39  0000 C CNN
F 2 "" V 4030 6700 50  0001 C CNN
F 3 "" H 4100 6700 50  0001 C CNN
	1    4100 6700
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 6700 3900 6700
Wire Wire Line
	4250 6700 4300 6700
Wire Wire Line
	4300 6700 4300 6800
$Comp
L GND #PWR?
U 1 1 59DE6904
P 4300 6800
F 0 "#PWR?" H 4300 6550 50  0001 C CNN
F 1 "GND" H 4305 6627 50  0000 C CNN
F 2 "" H 4300 6800 50  0001 C CNN
F 3 "" H 4300 6800 50  0001 C CNN
	1    4300 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 3100 2000 3100
Wire Wire Line
	2600 1900 2600 1800
Wire Wire Line
	2600 1800 3000 1800
Connection ~ 3000 1800
Wire Wire Line
	5200 6000 3750 6000
Wire Wire Line
	3750 6000 3750 5100
Wire Wire Line
	7450 6350 7450 6400
Wire Wire Line
	7450 6400 7700 6400
Wire Wire Line
	7700 6350 7700 6500
Connection ~ 7700 6400
Wire Wire Line
	6950 6150 6300 6150
Text GLabel 6400 6450 2    39   Output ~ 0
LCD_EN
Wire Wire Line
	6400 6450 6300 6450
$Sheet
S 9000 2050 550  350 
U 5A001753
F0 "peripherals" 39
F1 "peripherals.sch" 39
F2 "AD[0..7]" B L 9000 2200 39 
$EndSheet
Wire Bus Line
	8500 2200 9000 2200
Text GLabel 1900 3700 0    47   Output ~ 0
SCL
Text GLabel 1900 3850 0    47   BiDi ~ 0
SDA
Wire Wire Line
	1900 3700 2000 3700
Wire Wire Line
	1900 3850 2000 3850
NoConn ~ 2000 3550
NoConn ~ 2000 3400
NoConn ~ 2000 2950
NoConn ~ 2000 2800
$Comp
L CONN_02X01 JP1
U 1 1 5A092DF4
P 1750 3250
F 0 "JP1" H 1750 3150 50  0000 C CNN
F 1 "CONN_02X01" H 1750 3374 50  0001 C CNN
F 2 "" H 1750 2050 50  0001 C CNN
F 3 "" H 1750 2050 50  0001 C CNN
	1    1750 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5A093004
P 1500 3350
F 0 "#PWR?" H 1500 3100 50  0001 C CNN
F 1 "GND" H 1505 3177 50  0000 C CNN
F 2 "" H 1500 3350 50  0001 C CNN
F 3 "" H 1500 3350 50  0001 C CNN
	1    1500 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3250 1500 3350
$EndSCHEMATC

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
Sheet 1 2
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
P 2450 5400
F 0 "#PWR01" H 2450 5150 50  0001 C CNN
F 1 "GND" H 2455 5227 50  0000 C CNN
F 2 "" H 2450 5400 50  0001 C CNN
F 3 "" H 2450 5400 50  0001 C CNN
	1    2450 5400
	1    0    0    -1  
$EndComp
$Comp
L 74LS373_Latch U3
U 1 1 59CDD782
P 5750 2400
F 0 "U3" H 6050 2300 60  0000 C CNN
F 1 "74LS373" H 6050 2200 60  0000 C CNN
F 2 "" H 5750 2400 60  0001 C CNN
F 3 "" H 5750 2400 60  0001 C CNN
	1    5750 2400
	1    0    0    -1  
$EndComp
$Comp
L R_Network09 RN?
U 1 1 59CDD784
P 5300 1000
F 0 "RN?" H 5780 1046 50  0001 L CNN
F 1 "2.7K" H 5250 1200 50  0000 L CNN
F 2 "Resistors_THT:R_Array_SIP10" V 5875 1000 50  0001 C CNN
F 3 "" H 5300 1000 50  0001 C CNN
	1    5300 1000
	1    0    0    -1  
$EndComp
NoConn ~ 5700 1200
$Comp
L CONN_02X01 J?
U 1 1 59CDD785
P 7600 3200
F 0 "J?" H 7600 3415 50  0001 C CNN
F 1 "CONN_02X01" H 7600 3324 50  0001 C CNN
F 2 "" H 7600 2000 50  0001 C CNN
F 3 "" H 7600 2000 50  0001 C CNN
	1    7600 3200
	0    -1   -1   0   
$EndComp
Text GLabel 7600 2950 1    39   Input ~ 0
VCC
$Comp
L GND #PWR02
U 1 1 59CDD786
P 6050 3750
F 0 "#PWR02" H 6050 3500 50  0001 C CNN
F 1 "GND" H 6055 3577 50  0000 C CNN
F 2 "" H 6050 3750 50  0001 C CNN
F 3 "" H 6050 3750 50  0001 C CNN
	1    6050 3750
	1    0    0    -1  
$EndComp
$Comp
L ATF16V8C U6
U 1 1 59CDD787
P 5750 6350
F 0 "U6" H 6050 7350 60  0000 C CNN
F 1 "ATF16V8C" H 6050 7250 60  0000 C CNN
F 2 "" H 5150 6800 60  0001 C CNN
F 3 "" H 5150 6800 60  0001 C CNN
	1    5750 6350
	1    0    0    -1  
$EndComp
Text GLabel 4150 4500 2    39   Input ~ 0
ALE
Text GLabel 5500 2100 0    39   Input ~ 0
ALE
$Comp
L GND #PWR03
U 1 1 59CDD789
P 5900 6800
F 0 "#PWR03" H 5900 6550 50  0001 C CNN
F 1 "GND" H 5900 6650 50  0000 C CNN
F 2 "" H 5900 6800 50  0001 C CNN
F 3 "" H 5900 6800 50  0001 C CNN
	1    5900 6800
	1    0    0    -1  
$EndComp
Text GLabel 5900 4700 0    39   Input ~ 0
V_MCU
$Comp
L DB9_MALE J5
U 1 1 59CDD78A
P 10100 6400
F 0 "J5" H 10050 6950 50  0000 L CNN
F 1 "DB9_MALE" H 9900 5800 50  0000 L CNN
F 2 "" H 10100 6400 50  0001 C CNN
F 3 "" H 10100 6400 50  0001 C CNN
	1    10100 6400
	1    0    0    1   
$EndComp
$Comp
L CONN_01X09 J4
U 1 1 59CDD78B
P 8650 6400
F 0 "J4" H 8600 5850 50  0000 L CNN
F 1 "CONN_01X09" H 8728 6350 50  0001 L CNN
F 2 "" H 8650 6400 50  0001 C CNN
F 3 "" H 8650 6400 50  0001 C CNN
	1    8650 6400
	-1   0    0    -1  
$EndComp
$Sheet
S 700  1350 950  500 
U 59CDDA14
F0 "power" 60
F1 "power.sch" 60
F2 "VCC" I R 1650 1550 39 
F3 "RESET" I R 1650 1700 39 
$EndSheet
$Comp
L Crystal Y1
U 1 1 59CDDF3A
P 1500 4750
F 0 "Y1" V 1500 4900 39  0000 L CNN
F 1 "11.0592MHz" V 1550 4900 39  0000 L CNN
F 2 "" H 1500 4750 50  0001 C CNN
F 3 "" H 1500 4750 50  0001 C CNN
	1    1500 4750
	0    1    1    0   
$EndComp
$Comp
L C C5
U 1 1 59CDDF41
P 1200 4500
F 0 "C5" V 1350 4500 39  0000 C CNN
F 1 "27pF" V 1400 4500 39  0000 C CNN
F 2 "" H 1238 4350 50  0001 C CNN
F 3 "" H 1200 4500 50  0001 C CNN
	1    1200 4500
	0    1    1    0   
$EndComp
$Comp
L C C6
U 1 1 59CDDF48
P 1200 5050
F 0 "C6" V 1350 5050 39  0000 C CNN
F 1 "27pF" V 1400 5050 39  0000 C CNN
F 2 "" H 1238 4900 50  0001 C CNN
F 3 "" H 1200 5050 50  0001 C CNN
	1    1200 5050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR04
U 1 1 59CDDF5A
P 950 5350
F 0 "#PWR04" H 950 5100 50  0001 C CNN
F 1 "GND" H 955 5177 50  0000 C CNN
F 2 "" H 950 5350 50  0001 C CNN
F 3 "" H 950 5350 50  0001 C CNN
	1    950  5350
	1    0    0    -1  
$EndComp
$Comp
L Q_PNP_EBC Q1
U 1 1 59CE0FA5
P 3300 5900
F 0 "Q1" H 3491 5854 50  0000 L CNN
F 1 "2N2907" H 3491 5945 50  0000 L CNN
F 2 "" H 3500 6000 50  0001 C CNN
F 3 "" H 3300 5900 50  0001 C CNN
	1    3300 5900
	1    0    0    1   
$EndComp
$Comp
L R R5
U 1 1 59CE0FA6
P 3400 6350
F 0 "R5" H 3470 6396 50  0000 L CNN
F 1 "330" H 3470 6305 50  0000 L CNN
F 2 "" V 3330 6350 50  0001 C CNN
F 3 "" H 3400 6350 50  0001 C CNN
	1    3400 6350
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 59CE0FA7
P 2900 5450
F 0 "R4" V 2693 5450 50  0000 C CNN
F 1 "1000" V 2784 5450 50  0000 C CNN
F 2 "" V 2830 5450 50  0001 C CNN
F 3 "" H 2900 5450 50  0001 C CNN
	1    2900 5450
	-1   0    0    1   
$EndComp
$Comp
L LED_ALT D8
U 1 1 59CE0FA8
P 3400 6750
F 0 "D8" V 3438 6632 50  0000 R CNN
F 1 "GREEN_LED" V 3347 6632 50  0000 R CNN
F 2 "" H 3400 6750 50  0001 C CNN
F 3 "" H 3400 6750 50  0001 C CNN
	1    3400 6750
	0    -1   -1   0   
$EndComp
Text GLabel 3400 5600 1    39   Input ~ 0
VCC
$Comp
L GND #PWR06
U 1 1 59CE0FA9
P 3400 7000
F 0 "#PWR06" H 3400 6750 50  0001 C CNN
F 1 "GND" H 3405 6827 50  0000 C CNN
F 2 "" H 3400 7000 50  0001 C CNN
F 3 "" H 3400 7000 50  0001 C CNN
	1    3400 7000
	1    0    0    -1  
$EndComp
Entry Wire Line
	5600 1400 5500 1500
Entry Wire Line
	5500 1400 5400 1500
Entry Wire Line
	5400 1400 5300 1500
Entry Wire Line
	5300 1400 5200 1500
Entry Wire Line
	5200 1400 5100 1500
Entry Wire Line
	5100 1400 5000 1500
Entry Wire Line
	5000 1400 4900 1500
Entry Wire Line
	4900 1400 4800 1500
Text Label 4200 2100 0    39   ~ 0
AD0
Text Label 4200 2250 0    39   ~ 0
AD1
Text Label 4200 2400 0    39   ~ 0
AD2
Text Label 4200 2550 0    39   ~ 0
AD3
Text Label 4200 2700 0    39   ~ 0
AD4
Text Label 4200 2850 0    39   ~ 0
AD5
Text Label 4200 3000 0    39   ~ 0
AD6
Text Label 4200 3150 0    39   ~ 0
AD7
Entry Wire Line
	5150 2150 5250 2250
Entry Wire Line
	5150 2150 5250 2250
Entry Wire Line
	5150 2300 5250 2400
Entry Wire Line
	5150 2450 5250 2550
Entry Wire Line
	5150 2600 5250 2700
Entry Wire Line
	5150 2750 5250 2850
Entry Wire Line
	5150 2900 5250 3000
Entry Wire Line
	5150 3050 5250 3150
Entry Wire Line
	5150 3200 5250 3300
Text Label 5350 2250 0    39   ~ 0
AD0
Text Label 5350 2400 0    39   ~ 0
AD1
Text Label 5350 2550 0    39   ~ 0
AD2
Text Label 5350 2700 0    39   ~ 0
AD3
Text Label 5350 2850 0    39   ~ 0
AD4
Text Label 5350 3000 0    39   ~ 0
AD5
Text Label 5350 3150 0    39   ~ 0
AD6
Text Label 5350 3300 0    39   ~ 0
AD7
NoConn ~ 2600 5100
NoConn ~ 2750 5100
NoConn ~ 3050 5100
NoConn ~ 3200 5100
NoConn ~ 3350 5100
NoConn ~ 3500 5100
NoConn ~ 3650 5100
$Comp
L CONN_02X01 J?
U 1 1 59CDD783
P 2800 1550
F 0 "J?" H 2800 1765 50  0001 C CNN
F 1 "CONN_02X01" H 2800 1674 50  0001 C CNN
F 2 "" H 2800 350 50  0001 C CNN
F 3 "" H 2800 350 50  0001 C CNN
	1    2800 1550
	1    0    0    -1  
$EndComp
Text Label 5600 1200 3    39   ~ 0
AD0
Text Label 5500 1200 3    39   ~ 0
AD1
Text Label 5400 1200 3    39   ~ 0
AD2
Text Label 5300 1200 3    39   ~ 0
AD3
Text Label 5200 1200 3    39   ~ 0
AD4
Text Label 5100 1200 3    39   ~ 0
AD5
Text Label 5000 1200 3    39   ~ 0
AD6
Text Label 4900 1200 3    39   ~ 0
AD7
$Comp
L C501 U1
U 1 1 59CE642E
P 3150 3500
F 0 "U1" H 3150 4050 60  0000 C CNN
F 1 "C501" H 3150 3950 60  0000 C CNN
F 2 "" H 2800 4100 60  0001 C CNN
F 3 "" H 2800 4100 60  0001 C CNN
	1    3150 3500
	1    0    0    -1  
$EndComp
$Comp
L bq4011YMA-100 U4
U 1 1 59CE7C64
P 7700 4800
F 0 "U4" H 7750 5600 39  0000 C CNN
F 1 "bq4011YMA-100" H 7750 5550 39  0000 C CNN
F 2 "" H 7950 4300 39  0001 C CNN
F 3 "" H 7950 4300 39  0001 C CNN
	1    7700 4800
	1    0    0    -1  
$EndComp
Text GLabel 3200 1100 2    39   Input ~ 0
V_MCU
Entry Wire Line
	6750 2250 6850 2350
Entry Wire Line
	6750 2400 6850 2500
Entry Wire Line
	6750 2550 6850 2650
Entry Wire Line
	6750 2700 6850 2800
Entry Wire Line
	6750 2850 6850 2950
Entry Wire Line
	6750 3000 6850 3100
Entry Wire Line
	6750 3150 6850 3250
Entry Wire Line
	6750 3300 6850 3400
Text Label 6600 2250 0    39   ~ 0
A0
Text Label 6600 2400 0    39   ~ 0
A1
Text Label 6600 2550 0    39   ~ 0
A2
Text Label 6600 2700 0    39   ~ 0
A3
Text Label 6600 2850 0    39   ~ 0
A4
Text Label 6600 3000 0    39   ~ 0
A5
Text Label 6600 3150 0    39   ~ 0
A6
Text Label 6600 3300 0    39   ~ 0
A7
Text Label 6950 3750 0    39   ~ 0
A0
Text Label 6950 3900 0    39   ~ 0
A1
Text Label 6950 4050 0    39   ~ 0
A2
Text Label 6950 4200 0    39   ~ 0
A3
Text Label 6950 4350 0    39   ~ 0
A4
Text Label 6950 4500 0    39   ~ 0
A5
Text Label 6950 4650 0    39   ~ 0
A6
Text Label 6950 4800 0    39   ~ 0
A7
Text Label 6950 4950 0    39   ~ 0
A8
Text Label 6950 5100 0    39   ~ 0
A9
Text Label 6950 5250 0    39   ~ 0
A10
Text Label 6950 5400 0    39   ~ 0
A11
Text Label 6950 5550 0    39   ~ 0
A12
Text Label 6950 5700 0    39   ~ 0
A13
Text Label 6950 5850 0    39   ~ 0
A14
Entry Wire Line
	6850 3650 6950 3750
Entry Wire Line
	6850 3800 6950 3900
Entry Wire Line
	6850 3950 6950 4050
Entry Wire Line
	6850 4100 6950 4200
Entry Wire Line
	6850 4250 6950 4350
Entry Wire Line
	6850 4400 6950 4500
Entry Wire Line
	6850 4550 6950 4650
Entry Wire Line
	6850 4700 6950 4800
$Comp
L GND #PWR?
U 1 1 59CE9B17
P 7850 6300
F 0 "#PWR?" H 7850 6050 50  0001 C CNN
F 1 "GND" H 7855 6127 50  0000 C CNN
F 2 "" H 7850 6300 50  0001 C CNN
F 3 "" H 7850 6300 50  0001 C CNN
	1    7850 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59CEA6A2
P 6600 1850
F 0 "#PWR?" H 6600 1600 50  0001 C CNN
F 1 "GND" H 6605 1677 50  0000 C CNN
F 2 "" H 6600 1850 50  0001 C CNN
F 3 "" H 6600 1850 50  0001 C CNN
	1    6600 1850
	1    0    0    -1  
$EndComp
$Comp
L C_Small C21
U 1 1 59CEA6A8
P 6300 1850
F 0 "C21" V 6450 1800 39  0000 L CNN
F 1 "0.1uF" V 6400 1750 39  0000 L CNN
F 2 "" H 6300 1850 50  0001 C CNN
F 3 "" H 6300 1850 50  0001 C CNN
	1    6300 1850
	0    -1   -1   0   
$EndComp
$Comp
L CONN_02X01 J?
U 1 1 59CEA6E0
P 5800 1850
F 0 "J?" H 5800 2065 50  0001 C CNN
F 1 "CONN_02X01" H 5800 1974 50  0001 C CNN
F 2 "" H 5800 650 50  0001 C CNN
F 3 "" H 5800 650 50  0001 C CNN
	1    5800 1850
	1    0    0    -1  
$EndComp
Text GLabel 5500 1850 0    39   Input ~ 0
VCC
$Comp
L GND #PWR?
U 1 1 59CEAE58
P 8450 3450
F 0 "#PWR?" H 8450 3200 50  0001 C CNN
F 1 "GND" H 8455 3277 50  0000 C CNN
F 2 "" H 8450 3450 50  0001 C CNN
F 3 "" H 8450 3450 50  0001 C CNN
	1    8450 3450
	1    0    0    -1  
$EndComp
$Comp
L C_Small C22
U 1 1 59CEAE5E
P 8150 3450
F 0 "C22" V 8300 3400 39  0000 L CNN
F 1 "0.1uF" V 8250 3350 39  0000 L CNN
F 2 "" H 8150 3450 50  0001 C CNN
F 3 "" H 8150 3450 50  0001 C CNN
	1    8150 3450
	0    -1   -1   0   
$EndComp
Entry Wire Line
	8550 5400 8650 5300
Entry Wire Line
	8550 5250 8650 5150
Entry Wire Line
	8550 5100 8650 5000
Entry Wire Line
	8550 4950 8650 4850
Entry Wire Line
	8550 4800 8650 4700
Entry Wire Line
	8550 4650 8650 4550
Entry Wire Line
	8550 4500 8650 4400
Entry Wire Line
	8550 4350 8650 4250
Text Label 8400 4350 0    39   ~ 0
AD0
Text Label 8400 4500 0    39   ~ 0
AD1
Text Label 8400 4650 0    39   ~ 0
AD2
Text Label 8400 4800 0    39   ~ 0
AD3
Text Label 8400 4950 0    39   ~ 0
AD4
Text Label 8400 5100 0    39   ~ 0
AD5
Text Label 8400 5250 0    39   ~ 0
AD6
Text Label 8400 5400 0    39   ~ 0
AD7
Text Label 6900 1500 0    39   ~ 0
AD[0..7]
Entry Wire Line
	4450 3300 4550 3400
Entry Wire Line
	4450 3450 4550 3550
Entry Wire Line
	4450 3600 4550 3700
Entry Wire Line
	4450 3750 4550 3850
Entry Wire Line
	4450 3900 4550 4000
Entry Wire Line
	4450 4050 4550 4150
Entry Wire Line
	4450 4200 4550 4300
Entry Wire Line
	5000 4400 5100 4500
Entry Wire Line
	4900 4400 5000 4500
Entry Wire Line
	4800 4400 4900 4500
NoConn ~ 5350 5100
NoConn ~ 5350 5850
NoConn ~ 5350 6300
NoConn ~ 6450 6150
Text Label 5100 4500 3    39   ~ 0
A12
Text Label 5000 4500 3    39   ~ 0
A13
Text Label 4900 4500 3    39   ~ 0
A14
Text Label 5350 4400 0    39   ~ 0
A[8..14]
Text Label 6850 3450 3    39   ~ 0
A[0..7]
Wire Wire Line
	2450 5100 2450 5400
Wire Wire Line
	5550 2100 5500 2100
Wire Wire Line
	1650 1550 2550 1550
Wire Wire Line
	5900 4700 5900 4900
Wire Wire Line
	6050 3650 6050 3750
Wire Wire Line
	5550 3450 5550 3700
Wire Wire Line
	5550 3700 6050 3700
Connection ~ 6050 3700
Wire Wire Line
	5900 6800 5900 6650
Wire Wire Line
	950  5050 1050 5050
Wire Wire Line
	1350 5050 2100 5050
Wire Wire Line
	1500 4900 1500 5050
Wire Wire Line
	950  4200 950  5350
Wire Wire Line
	1500 4500 1500 4600
Wire Wire Line
	1350 4500 2150 4500
Wire Wire Line
	2150 4200 950  4200
Wire Wire Line
	1050 4500 950  4500
Connection ~ 950  4500
Connection ~ 950  5050
Connection ~ 1500 5050
Wire Wire Line
	3400 6100 3400 6200
Wire Wire Line
	3400 6500 3400 6600
Wire Wire Line
	3400 5700 3400 5600
Wire Wire Line
	3400 6900 3400 7000
Wire Wire Line
	2900 5900 3100 5900
Wire Wire Line
	4100 2100 4450 2100
Wire Wire Line
	4100 2250 4450 2250
Wire Wire Line
	4100 2400 4450 2400
Wire Wire Line
	4100 2550 4450 2550
Wire Wire Line
	4100 2700 4450 2700
Wire Wire Line
	4100 2850 4450 2850
Wire Wire Line
	4100 3000 4450 3000
Wire Wire Line
	4100 3150 4450 3150
Connection ~ 3150 1550
Wire Wire Line
	5600 1200 5600 1400
Wire Wire Line
	5500 1200 5500 1400
Wire Wire Line
	5400 1200 5400 1400
Wire Wire Line
	5300 1200 5300 1400
Wire Wire Line
	5200 1200 5200 1400
Wire Wire Line
	5100 1200 5100 1400
Wire Wire Line
	5000 1200 5000 1400
Wire Wire Line
	4900 1200 4900 1400
Connection ~ 1500 4500
Wire Wire Line
	5250 2250 5550 2250
Wire Wire Line
	5250 2400 5550 2400
Wire Wire Line
	5250 2550 5550 2550
Wire Wire Line
	5250 2700 5550 2700
Wire Wire Line
	5250 2850 5550 2850
Wire Wire Line
	5250 3000 5550 3000
Wire Wire Line
	5250 3150 5550 3150
Wire Wire Line
	5250 3300 5550 3300
Wire Wire Line
	2150 4650 2100 4650
Wire Wire Line
	2100 4650 2100 5050
Wire Bus Line
	5150 2150 5150 3200
Wire Wire Line
	2900 5100 2900 5300
Wire Wire Line
	2900 5600 2900 5900
Wire Wire Line
	4100 3300 4450 3300
Wire Wire Line
	4100 3450 4450 3450
Wire Wire Line
	4100 3600 4450 3600
Wire Wire Line
	4100 3750 4450 3750
Wire Wire Line
	4100 4500 4150 4500
Wire Wire Line
	3150 800  3150 1900
Wire Wire Line
	3150 1100 3200 1100
Wire Wire Line
	6550 2250 6750 2250
Wire Wire Line
	6550 2400 6750 2400
Wire Wire Line
	6550 2550 6750 2550
Wire Wire Line
	6550 2700 6750 2700
Wire Wire Line
	6550 2850 6750 2850
Wire Wire Line
	6550 3000 6750 3000
Wire Wire Line
	6550 3150 6750 3150
Wire Wire Line
	6550 3300 6750 3300
Wire Bus Line
	6850 2350 6850 4700
Wire Wire Line
	7100 3750 6950 3750
Wire Wire Line
	7100 3900 6950 3900
Wire Wire Line
	7100 4050 6950 4050
Wire Wire Line
	7100 4200 6950 4200
Wire Wire Line
	7100 4350 6950 4350
Wire Wire Line
	7100 4500 6950 4500
Wire Wire Line
	7100 4650 6950 4650
Wire Wire Line
	7100 4800 6950 4800
Wire Wire Line
	7100 4950 6950 4950
Wire Wire Line
	7100 5100 6950 5100
Wire Wire Line
	7100 5250 6950 5250
Wire Wire Line
	7100 5400 6950 5400
Wire Wire Line
	7100 5550 6950 5550
Wire Wire Line
	7100 5700 6950 5700
Wire Wire Line
	7100 5850 6950 5850
Wire Wire Line
	8350 4350 8550 4350
Wire Wire Line
	8350 4500 8550 4500
Wire Wire Line
	8350 4650 8550 4650
Wire Wire Line
	8350 4800 8550 4800
Wire Wire Line
	8350 4950 8550 4950
Wire Wire Line
	8350 5100 8550 5100
Wire Wire Line
	8350 5250 8550 5250
Wire Wire Line
	8350 5400 8550 5400
Wire Wire Line
	7600 3550 7600 3450
Wire Wire Line
	7600 6200 7600 6250
Wire Wire Line
	7600 6250 7850 6250
Wire Wire Line
	7850 6200 7850 6300
Connection ~ 7850 6250
Wire Wire Line
	3050 1550 3400 1550
Wire Wire Line
	5500 1850 5550 1850
Wire Wire Line
	6050 1850 6050 1900
Wire Wire Line
	6050 1850 6200 1850
Wire Wire Line
	6400 1850 6600 1850
Wire Wire Line
	8250 3450 8450 3450
Wire Wire Line
	7600 3450 8050 3450
Wire Wire Line
	4100 3900 4450 3900
Wire Wire Line
	4100 4050 4450 4050
Wire Wire Line
	4100 4200 4450 4200
Wire Wire Line
	8850 6000 9050 6000
Wire Wire Line
	8850 6100 9050 6100
Wire Wire Line
	8850 6200 9050 6200
Wire Wire Line
	8850 6300 9050 6300
Wire Wire Line
	8850 6400 9050 6400
Wire Wire Line
	8850 6500 9050 6500
Wire Wire Line
	8850 6600 9050 6600
Wire Wire Line
	8850 6700 9050 6700
Wire Wire Line
	8850 6800 9050 6800
Entry Wire Line
	9050 6000 9150 6100
Entry Wire Line
	9050 6100 9150 6200
Entry Wire Line
	9050 6200 9150 6300
Entry Wire Line
	9050 6300 9150 6400
Entry Wire Line
	9050 6400 9150 6500
Entry Wire Line
	9050 6500 9150 6600
Entry Wire Line
	9050 6600 9150 6700
Entry Wire Line
	9050 6700 9150 6800
Entry Wire Line
	9050 6800 9150 6900
Text Label 8850 6000 0    39   ~ 0
J5P1
Text Label 8850 6100 0    39   ~ 0
J5P2
Text Label 8850 6200 0    39   ~ 0
J5P3
Text Label 8850 6300 0    39   ~ 0
J5P4
Text Label 8850 6400 0    39   ~ 0
J5P5
Text Label 8850 6500 0    39   ~ 0
J5P6
Text Label 8850 6600 0    39   ~ 0
J5P7
Text Label 8850 6700 0    39   ~ 0
J5P8
Text Label 8850 6800 0    39   ~ 0
J5P9
Text Label 9800 6000 2    39   ~ 0
J5P1
Text Label 9800 6200 2    39   ~ 0
J5P2
Text Label 9800 6400 2    39   ~ 0
J5P3
Text Label 9800 6600 2    39   ~ 0
J5P4
Text Label 9800 6800 2    39   ~ 0
J5P5
Text Label 9800 6100 2    39   ~ 0
J5P6
Text Label 9800 6300 2    39   ~ 0
J5P7
Text Label 9800 6500 2    39   ~ 0
J5P8
Text Label 9800 6700 2    39   ~ 0
J5P9
Wire Wire Line
	9800 6000 9650 6000
Wire Wire Line
	9800 6100 9650 6100
Wire Wire Line
	9800 6200 9650 6200
Wire Wire Line
	9800 6300 9650 6300
Wire Wire Line
	9800 6400 9650 6400
Wire Wire Line
	9800 6500 9650 6500
Wire Wire Line
	9800 6600 9650 6600
Wire Wire Line
	9800 6700 9650 6700
Wire Wire Line
	9800 6800 9650 6800
Entry Wire Line
	9650 6000 9550 6100
Entry Wire Line
	9650 6100 9550 6200
Entry Wire Line
	9650 6200 9550 6300
Entry Wire Line
	9650 6300 9550 6400
Entry Wire Line
	9650 6400 9550 6500
Entry Wire Line
	9650 6500 9550 6600
Entry Wire Line
	9650 6600 9550 6700
Entry Wire Line
	9650 6700 9550 6800
Entry Wire Line
	9650 6800 9550 6900
Wire Bus Line
	9550 6100 9550 6900
Wire Bus Line
	9150 6100 9150 6900
Wire Bus Line
	9150 6100 9550 6100
Text Label 9200 6100 0    39   ~ 0
J5P[1..9]
Text Label 4200 3300 0    39   ~ 0
A8
Text Label 4200 3450 0    39   ~ 0
A9
Text Label 4200 3600 0    39   ~ 0
A10
Text Label 4200 3750 0    39   ~ 0
A11
Text Label 4200 3900 0    39   ~ 0
A12
Text Label 4200 4050 0    39   ~ 0
A13
Text Label 4200 4200 0    39   ~ 0
A14
Wire Bus Line
	4550 3400 4550 4300
Wire Wire Line
	7850 3450 7850 3550
Connection ~ 7850 3450
Connection ~ 7600 3450
Wire Bus Line
	4650 2050 5050 2050
Text Label 4750 2050 0    39   ~ 0
AD[0..7]
Wire Bus Line
	4550 4300 4650 4400
Wire Bus Line
	4650 4400 6700 4400
Entry Wire Line
	4450 2100 4550 2000
Entry Wire Line
	4450 2250 4550 2150
Entry Wire Line
	4450 2400 4550 2300
Entry Wire Line
	4450 2550 4550 2450
Entry Wire Line
	4450 2700 4550 2600
Entry Wire Line
	4450 2850 4550 2750
Entry Wire Line
	4450 3000 4550 2900
Entry Wire Line
	4450 3150 4550 3050
Wire Bus Line
	4550 1500 4550 3050
Entry Wire Line
	6850 5750 6950 5850
Entry Wire Line
	6850 5600 6950 5700
Entry Wire Line
	6850 5450 6950 5550
Entry Wire Line
	6850 5300 6950 5400
Entry Wire Line
	6850 5150 6950 5250
Entry Wire Line
	6850 5000 6950 5100
Entry Wire Line
	6850 4850 6950 4950
$Comp
L GND #PWR?
U 1 1 59CF2B6F
P 3800 1550
F 0 "#PWR?" H 3800 1300 50  0001 C CNN
F 1 "GND" H 3805 1377 50  0000 C CNN
F 2 "" H 3800 1550 50  0001 C CNN
F 3 "" H 3800 1550 50  0001 C CNN
	1    3800 1550
	1    0    0    -1  
$EndComp
$Comp
L C_Small C20
U 1 1 59CF2B75
P 3500 1550
F 0 "C20" V 3650 1500 39  0000 L CNN
F 1 "0.1uF" V 3600 1450 39  0000 L CNN
F 2 "" H 3500 1550 50  0001 C CNN
F 3 "" H 3500 1550 50  0001 C CNN
	1    3500 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3600 1550 3800 1550
Wire Bus Line
	5050 2050 5150 2150
Wire Bus Line
	6850 4850 6700 4700
Wire Wire Line
	4100 4350 4400 4350
Wire Wire Line
	4400 4350 4400 5700
Wire Wire Line
	4400 5700 5350 5700
Wire Wire Line
	5100 4500 5100 5250
Wire Wire Line
	5100 5250 5350 5250
Wire Wire Line
	5000 4500 5000 5400
Wire Wire Line
	5000 5400 5350 5400
Wire Wire Line
	4900 4500 4900 5550
Wire Wire Line
	4900 5550 5350 5550
Wire Wire Line
	4100 4650 4300 4650
Wire Wire Line
	4300 4650 4300 6000
Wire Wire Line
	4300 6000 5350 6000
Wire Wire Line
	4100 4800 4200 4800
Wire Wire Line
	4200 4800 4200 6150
Wire Wire Line
	4200 6150 5350 6150
Wire Wire Line
	6450 6000 7100 6000
Wire Bus Line
	8650 1500 8650 5300
Wire Bus Line
	4550 1500 8650 1500
Wire Bus Line
	6700 4700 6700 4400
Wire Bus Line
	6850 4850 6850 5750
Wire Wire Line
	3150 800  4900 800 
Wire Wire Line
	1650 1700 1900 1700
Wire Wire Line
	1900 1700 1900 2850
Wire Wire Line
	1900 2850 2150 2850
Connection ~ 3150 1100
Wire Bus Line
	4650 2050 4550 1950
$Comp
L 74LS374_Flipflop U7
U 1 1 59D1FBF3
P 9150 2350
F 0 "U7" H 9450 2350 60  0000 C CNN
F 1 "74LS374" H 9450 2250 60  0000 C CNN
F 2 "" H 9150 2350 60  0001 C CNN
F 3 "" H 9150 2350 60  0001 C CNN
	1    9150 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 3400 8900 3400
Wire Wire Line
	8900 3400 8900 3600
Wire Wire Line
	8900 3600 9450 3600
$Comp
L GND #PWR?
U 1 1 59D1FFDB
P 9450 3600
F 0 "#PWR?" H 9450 3350 50  0001 C CNN
F 1 "GND" H 9455 3427 50  0000 C CNN
F 2 "" H 9450 3600 50  0001 C CNN
F 3 "" H 9450 3600 50  0001 C CNN
	1    9450 3600
	1    0    0    -1  
$EndComp
Entry Wire Line
	8650 1950 8750 2050
Entry Wire Line
	8650 2100 8750 2200
Entry Wire Line
	8650 2250 8750 2350
Entry Wire Line
	8650 2400 8750 2500
Entry Wire Line
	8650 2550 8750 2650
Entry Wire Line
	8650 2700 8750 2800
Entry Wire Line
	8650 2850 8750 2950
Entry Wire Line
	8650 3000 8750 3100
Text Label 8800 2050 0    39   ~ 0
AD0
Text Label 8800 2200 0    39   ~ 0
AD1
Text Label 8800 2350 0    39   ~ 0
AD2
Text Label 8800 2500 0    39   ~ 0
AD3
Text Label 8800 2650 0    39   ~ 0
AD4
Text Label 8800 2800 0    39   ~ 0
AD5
Text Label 8800 2950 0    39   ~ 0
AD6
Text Label 8800 3100 0    39   ~ 0
AD7
Wire Wire Line
	8750 2050 8950 2050
Wire Wire Line
	8750 2200 8950 2200
Wire Wire Line
	8750 2350 8950 2350
Wire Wire Line
	8750 2500 8950 2500
Wire Wire Line
	8750 2650 8950 2650
Wire Wire Line
	8750 2800 8950 2800
Wire Wire Line
	8750 2950 8950 2950
Wire Wire Line
	8750 3100 8950 3100
Text GLabel 6550 6300 2    39   Input ~ 0
DEBUG
Wire Wire Line
	6450 6300 6550 6300
Text GLabel 8950 3250 0    39   Input ~ 0
DEBUG
Text GLabel 9450 1800 1    39   Input ~ 0
VCC
Wire Wire Line
	9450 1800 9450 1850
NoConn ~ 9950 2200
NoConn ~ 9950 2350
NoConn ~ 9950 2500
NoConn ~ 9950 2650
NoConn ~ 9950 2800
NoConn ~ 9950 2950
NoConn ~ 9950 3100
NoConn ~ 9950 3250
$EndSCHEMATC
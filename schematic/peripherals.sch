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
Sheet 5 5
Title "ECEN5613 Lab"
Date "F2017"
Rev ""
Comp "Jeff Schornick"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2600 2300 1    39   BiDi ~ 0
AD[0..7]
Entry Wire Line
	2600 2650 2700 2750
Entry Wire Line
	2600 2800 2700 2900
Entry Wire Line
	2600 2950 2700 3050
Entry Wire Line
	2600 3100 2700 3200
Entry Wire Line
	2600 3250 2700 3350
Entry Wire Line
	2600 3400 2700 3500
Entry Wire Line
	2600 3550 2700 3650
Entry Wire Line
	2600 3700 2700 3800
Text Label 2800 2750 0    39   ~ 0
AD0
Text Label 2800 2900 0    39   ~ 0
AD1
Text Label 2800 3050 0    39   ~ 0
AD2
Text Label 2800 3200 0    39   ~ 0
AD3
Text Label 2800 3350 0    39   ~ 0
AD4
Text Label 2800 3500 0    39   ~ 0
AD5
Text Label 2800 3650 0    39   ~ 0
AD6
Text Label 2800 3800 0    39   ~ 0
AD7
Wire Wire Line
	2700 2750 2950 2750
Wire Wire Line
	2700 2900 2950 2900
Wire Wire Line
	2700 3050 2950 3050
Wire Wire Line
	2700 3200 2950 3200
Wire Wire Line
	2700 3350 2950 3350
Wire Wire Line
	2700 3500 2950 3500
Wire Wire Line
	2700 3650 2950 3650
Wire Wire Line
	2700 3800 2950 3800
Wire Bus Line
	2600 2300 2600 2650
Wire Bus Line
	2600 2650 2600 2800
Wire Bus Line
	2600 2800 2600 2950
Wire Bus Line
	2600 2950 2600 3100
Wire Bus Line
	2600 3100 2600 3250
Wire Bus Line
	2600 3250 2600 3400
Wire Bus Line
	2600 3400 2600 3550
Wire Bus Line
	2600 3550 2600 3700
$Comp
L POT RV1
U 1 1 5A0024BC
P 3550 2050
F 0 "RV1" V 3343 2050 50  0000 C CNN
F 1 "10k" V 3434 2050 50  0000 C CNN
F 2 "" H 3550 2050 50  0001 C CNN
F 3 "" H 3550 2050 50  0001 C CNN
	1    3550 2050
	0    1    1    0   
$EndComp
$Comp
L optrex_lcd A1
U 1 1 5A002E32
P 3400 3500
F 0 "A1" H 3500 3550 39  0001 L CNN
F 1 "optrex_lcd" H 3350 3600 39  0000 L CNN
F 2 "" H 3150 4400 39  0001 C CNN
F 3 "" H 3150 4400 39  0001 C CNN
	1    3400 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1550 3400 2050
Wire Wire Line
	3400 2050 3400 2500
Wire Wire Line
	3550 2200 3550 2500
Wire Wire Line
	3700 2050 3900 2050
Wire Wire Line
	3900 2050 3900 2250
$Comp
L GND #PWR?
U 1 1 5A003004
P 3900 2250
F 0 "#PWR?" H 3900 2000 50  0001 C CNN
F 1 "GND" H 3905 2077 50  0000 C CNN
F 2 "" H 3900 2250 50  0001 C CNN
F 3 "" H 3900 2250 50  0001 C CNN
	1    3900 2250
	1    0    0    -1  
$EndComp
Text GLabel 3400 1550 1    39   UnSpc ~ 0
VCC
Connection ~ 3400 2050
Text GLabel 2650 4250 0    39   Input ~ 0
LCD_EN
Wire Wire Line
	2650 4250 2950 4250
Text GLabel 2650 3950 0    39   Input ~ 0
A1
Text GLabel 2650 4100 0    39   Input ~ 0
A0
Wire Wire Line
	2650 3950 2950 3950
Wire Wire Line
	2650 4100 2950 4100
$Comp
L GND #PWR?
U 1 1 5A00389E
P 3400 4550
F 0 "#PWR?" H 3400 4300 50  0001 C CNN
F 1 "GND" H 3405 4377 50  0000 C CNN
F 2 "" H 3400 4550 50  0001 C CNN
F 3 "" H 3400 4550 50  0001 C CNN
	1    3400 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 4500 3400 4550
Wire Notes Line
	2100 1250 4200 1250
Wire Notes Line
	4200 1250 4200 4950
Wire Notes Line
	4200 4950 2100 4950
Wire Notes Line
	2100 4950 2100 1250
Text Notes 2150 4900 0    47   ~ 9
LCD
$Comp
L 24LC16B U501
U 1 1 5A008977
P 6000 2500
F 0 "U501" H 6050 2950 47  0000 C CNN
F 1 "24LC16B" H 6050 2850 47  0000 C CNN
F 2 "" H 5550 2400 47  0001 C CNN
F 3 "" H 5550 2400 47  0001 C CNN
	1    6000 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2650 6350 2650
Wire Wire Line
	6350 2650 6350 2900
Wire Wire Line
	6350 2900 6350 2950
Wire Wire Line
	6350 2900 5800 2900
Wire Wire Line
	6250 2350 6950 2350
Wire Wire Line
	6950 2350 7300 2350
Wire Wire Line
	7300 2350 8600 2350
Wire Wire Line
	6250 2500 6800 2500
Wire Wire Line
	6800 2500 7150 2500
Wire Wire Line
	7150 2500 8600 2500
$Comp
L R R?
U 1 1 5A008B15
P 6950 2050
F 0 "R?" V 6950 2000 39  0001 L CNN
F 1 "5.1k" V 6950 2000 39  0000 L CNN
F 2 "" V 6880 2050 50  0001 C CNN
F 3 "" H 6950 2050 50  0001 C CNN
	1    6950 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2200 6950 2350
Wire Wire Line
	6800 2200 6800 2500
Connection ~ 6800 2500
Connection ~ 6950 2350
Text GLabel 8600 2350 2    47   BiDi ~ 0
SDA
Text GLabel 8600 2500 2    47   Input ~ 0
SCL
Wire Wire Line
	6950 1800 6950 1900
Wire Wire Line
	6800 1800 6800 1900
$Comp
L R R?
U 1 1 5A008D3D
P 6800 2050
F 0 "R?" V 6800 2000 39  0001 L CNN
F 1 "5.1k" V 6800 2000 39  0000 L CNN
F 2 "" V 6730 2050 50  0001 C CNN
F 3 "" H 6800 2050 50  0001 C CNN
	1    6800 2050
	1    0    0    -1  
$EndComp
Text GLabel 5800 1600 1    47   UnSpc ~ 0
VCC
Wire Wire Line
	5800 1600 5800 1800
Wire Wire Line
	5800 1800 5800 2150
Wire Wire Line
	5800 1800 6800 1800
Wire Wire Line
	6800 1800 6950 1800
Wire Wire Line
	6950 1800 7850 1800
Connection ~ 6350 2900
$Comp
L GND #PWR?
U 1 1 5A009168
P 6350 2950
F 0 "#PWR?" H 6350 2700 50  0001 C CNN
F 1 "GND" H 6355 2777 50  0000 C CNN
F 2 "" H 6350 2950 50  0001 C CNN
F 3 "" H 6350 2950 50  0001 C CNN
	1    6350 2950
	1    0    0    -1  
$EndComp
Connection ~ 5800 1800
Connection ~ 6800 1800
Wire Notes Line
	5100 1250 5100 4950
Wire Notes Line
	5100 4950 9450 4950
Wire Notes Line
	9450 1250 5100 1250
Text Notes 5150 4900 0    47   ~ 9
I2C EEPROM and I/O Expander
$Comp
L PCF8574A U502
U 1 1 5A0943A5
P 7850 3600
F 0 "U502" H 7850 3750 39  0000 C CNN
F 1 "PCF8574A" H 7900 3650 39  0000 C CNN
F 2 "" H 8300 4250 39  0001 C CNN
F 3 "" H 8300 4250 39  0001 C CNN
	1    7850 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 1800 7850 2700
Wire Wire Line
	7850 2700 7850 2800
Connection ~ 6950 1800
Wire Wire Line
	7350 3200 7300 3200
Wire Wire Line
	7300 3200 7300 2350
Connection ~ 7300 2350
Wire Wire Line
	7150 2500 7150 3350
Wire Wire Line
	7150 3350 7350 3350
Connection ~ 7150 2500
$Comp
L GND #PWR?
U 1 1 5A094697
P 7850 4500
F 0 "#PWR?" H 7850 4250 50  0001 C CNN
F 1 "GND" H 7855 4327 50  0000 C CNN
F 2 "" H 7850 4500 50  0001 C CNN
F 3 "" H 7850 4500 50  0001 C CNN
	1    7850 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 4450 7850 4500
Wire Wire Line
	7350 3800 7300 3800
Wire Wire Line
	7300 3800 7300 3950
Wire Wire Line
	7300 3950 7300 4100
Wire Wire Line
	7300 4100 7300 4500
Wire Wire Line
	7300 4500 7850 4500
Wire Wire Line
	7350 3950 7300 3950
Connection ~ 7300 3950
Wire Wire Line
	7350 4100 7300 4100
Connection ~ 7300 4100
Wire Notes Line
	9450 4950 9450 1250
Text GLabel 8500 4250 2    39   Output ~ 0
IO_INT
Wire Wire Line
	8350 4250 8500 4250
NoConn ~ 8350 3200
NoConn ~ 8350 3050
NoConn ~ 8350 3800
NoConn ~ 8350 3650
NoConn ~ 8350 3500
NoConn ~ 8350 3350
$Comp
L LED_ALT D501
U 1 1 5A0958FC
P 8200 2700
F 0 "D501" H 8200 2800 39  0000 C CNN
F 1 "LED_ALT" H 8192 2536 50  0001 C CNN
F 2 "" H 8200 2700 50  0001 C CNN
F 3 "" H 8200 2700 50  0001 C CNN
	1    8200 2700
	-1   0    0    1   
$EndComp
$Comp
L R R?
U 1 1 5A095AD5
P 8550 2900
F 0 "R?" V 8343 2900 50  0001 C CNN
F 1 "330" V 8550 2900 39  0000 C CNN
F 2 "" V 8480 2900 50  0001 C CNN
F 3 "" H 8550 2900 50  0001 C CNN
	1    8550 2900
	-1   0    0    1   
$EndComp
$Comp
L SW_Push SW501
U 1 1 5A095CC8
P 8850 4100
F 0 "SW501" H 8850 4285 39  0000 C CNN
F 1 "SW_Push" H 8850 4294 50  0001 C CNN
F 2 "" H 8850 4300 50  0001 C CNN
F 3 "" H 8850 4300 50  0001 C CNN
	1    8850 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 4100 9100 4100
Wire Wire Line
	9100 4100 9100 4200
$Comp
L GND #PWR?
U 1 1 5A096205
P 9100 4200
F 0 "#PWR?" H 9100 3950 50  0001 C CNN
F 1 "GND" H 9105 4027 50  0000 C CNN
F 2 "" H 9100 4200 50  0001 C CNN
F 3 "" H 9100 4200 50  0001 C CNN
	1    9100 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 2700 8050 2700
Connection ~ 7850 2700
Wire Wire Line
	8550 3950 8550 3050
Wire Wire Line
	8350 4100 8650 4100
Wire Wire Line
	8350 2700 8550 2700
Wire Wire Line
	8550 2700 8550 2750
Wire Wire Line
	8350 3950 8550 3950
Wire Wire Line
	8500 4250 8500 4250
$EndSCHEMATC

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
Text GLabel 3400 1550 1    39   BiDi ~ 0
VCC
Connection ~ 3400 2050
Text GLabel 2650 4250 0    39   BiDi ~ 0
LCD_EN
Wire Wire Line
	2650 4250 2950 4250
Text GLabel 2650 3950 0    39   BiDi ~ 0
A1
Text GLabel 2650 4100 0    39   BiDi ~ 0
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
P 6600 3550
F 0 "U501" H 6650 4000 47  0000 C CNN
F 1 "24LC16B" H 6650 3900 47  0000 C CNN
F 2 "" H 6150 3450 47  0001 C CNN
F 3 "" H 6150 3450 47  0001 C CNN
	1    6600 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3700 6950 3700
Wire Wire Line
	6950 3700 6950 3950
Wire Wire Line
	6950 3950 6950 4000
Wire Wire Line
	6950 3950 6400 3950
Wire Wire Line
	6850 3400 6950 3400
Wire Wire Line
	6950 3400 6950 2700
Wire Wire Line
	6850 3550 7100 3550
Wire Wire Line
	7100 3550 7100 2550
Wire Wire Line
	6950 2550 7100 2550
Wire Wire Line
	7100 2550 7500 2550
Wire Wire Line
	7500 2550 7500 2550
Wire Wire Line
	6750 2700 6950 2700
Wire Wire Line
	6950 2700 7500 2700
Wire Wire Line
	7500 2700 7500 2700
$Comp
L R R?
U 1 1 5A008B15
P 6950 2300
F 0 "R?" V 6950 2250 39  0001 L CNN
F 1 "5.1k" V 6950 2250 39  0000 L CNN
F 2 "" V 6880 2300 50  0001 C CNN
F 3 "" H 6950 2300 50  0001 C CNN
	1    6950 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2450 6950 2550
Wire Wire Line
	6750 2450 6750 2700
Connection ~ 6950 2700
Connection ~ 7100 2550
Text GLabel 7500 2550 2    47   BiDi ~ 0
SDA
Text GLabel 7500 2700 2    47   BiDi ~ 0
SCL
Wire Wire Line
	6950 2000 6950 2150
Wire Wire Line
	6750 2000 6750 2150
$Comp
L R R?
U 1 1 5A008D3D
P 6750 2300
F 0 "R?" V 6750 2250 39  0001 L CNN
F 1 "5.1k" V 6750 2250 39  0000 L CNN
F 2 "" V 6680 2300 50  0001 C CNN
F 3 "" H 6750 2300 50  0001 C CNN
	1    6750 2300
	1    0    0    -1  
$EndComp
Text GLabel 6200 2000 0    47   BiDi ~ 0
VCC
Wire Wire Line
	6200 2000 6400 2000
Wire Wire Line
	6400 2000 6750 2000
Wire Wire Line
	6750 2000 6950 2000
Connection ~ 6950 3950
$Comp
L GND #PWR?
U 1 1 5A009168
P 6950 4000
F 0 "#PWR?" H 6950 3750 50  0001 C CNN
F 1 "GND" H 6955 3827 50  0000 C CNN
F 2 "" H 6950 4000 50  0001 C CNN
F 3 "" H 6950 4000 50  0001 C CNN
	1    6950 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 3200 6400 2000
Connection ~ 6400 2000
Wire Wire Line
	7500 2550 7500 2550
Wire Wire Line
	7500 2700 7500 2700
Connection ~ 6750 2000
Wire Notes Line
	5200 1250 5200 4950
Wire Notes Line
	5200 4950 9050 4950
Wire Notes Line
	9050 1250 9050 4950
Wire Notes Line
	5200 1250 9050 1250
Text Notes 5250 4900 0    47   ~ 9
I2C EEPROM
$EndSCHEMATC

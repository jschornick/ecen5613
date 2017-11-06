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
$Descr A4 11693 8268
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
Text HLabel 4050 3100 1    39   BiDi ~ 0
AD[0..7]
Entry Wire Line
	4050 3450 4150 3550
Entry Wire Line
	4050 3600 4150 3700
Entry Wire Line
	4050 3750 4150 3850
Entry Wire Line
	4050 3900 4150 4000
Entry Wire Line
	4050 4050 4150 4150
Entry Wire Line
	4050 4200 4150 4300
Entry Wire Line
	4050 4350 4150 4450
Entry Wire Line
	4050 4500 4150 4600
Text Label 4250 3550 0    39   ~ 0
AD0
Text Label 4250 3700 0    39   ~ 0
AD1
Text Label 4250 3850 0    39   ~ 0
AD2
Text Label 4250 4000 0    39   ~ 0
AD3
Text Label 4250 4150 0    39   ~ 0
AD4
Text Label 4250 4300 0    39   ~ 0
AD5
Text Label 4250 4450 0    39   ~ 0
AD6
Text Label 4250 4600 0    39   ~ 0
AD7
Wire Wire Line
	4150 3550 4400 3550
Wire Wire Line
	4150 3700 4400 3700
Wire Wire Line
	4150 3850 4400 3850
Wire Wire Line
	4150 4000 4400 4000
Wire Wire Line
	4150 4150 4400 4150
Wire Wire Line
	4150 4300 4400 4300
Wire Wire Line
	4150 4450 4400 4450
Wire Wire Line
	4150 4600 4400 4600
Wire Bus Line
	4050 3100 4050 4500
$Comp
L POT RV1
U 1 1 5A0024BC
P 5000 2850
F 0 "RV1" V 4793 2850 50  0000 C CNN
F 1 "10k" V 4884 2850 50  0000 C CNN
F 2 "" H 5000 2850 50  0001 C CNN
F 3 "" H 5000 2850 50  0001 C CNN
	1    5000 2850
	0    1    1    0   
$EndComp
$Comp
L optrex_lcd A1
U 1 1 5A002E32
P 4850 4300
F 0 "A1" H 4950 4350 39  0001 L CNN
F 1 "optrex_lcd" H 4800 4400 39  0000 L CNN
F 2 "" H 4600 5200 39  0001 C CNN
F 3 "" H 4600 5200 39  0001 C CNN
	1    4850 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2350 4850 3300
Wire Wire Line
	5000 3000 5000 3300
Wire Wire Line
	5150 2850 5350 2850
Wire Wire Line
	5350 2850 5350 3050
$Comp
L GND #PWR?
U 1 1 5A003004
P 5350 3050
F 0 "#PWR?" H 5350 2800 50  0001 C CNN
F 1 "GND" H 5355 2877 50  0000 C CNN
F 2 "" H 5350 3050 50  0001 C CNN
F 3 "" H 5350 3050 50  0001 C CNN
	1    5350 3050
	1    0    0    -1  
$EndComp
Text GLabel 4850 2350 1    39   BiDi ~ 0
VCC
Connection ~ 4850 2850
Text GLabel 4100 5050 0    39   BiDi ~ 0
LCD_EN
Wire Wire Line
	4100 5050 4400 5050
Text GLabel 4100 4750 0    39   BiDi ~ 0
A1
Text GLabel 4100 4900 0    39   BiDi ~ 0
A0
Wire Wire Line
	4100 4750 4400 4750
Wire Wire Line
	4100 4900 4400 4900
$Comp
L GND #PWR?
U 1 1 5A00389E
P 4850 5350
F 0 "#PWR?" H 4850 5100 50  0001 C CNN
F 1 "GND" H 4855 5177 50  0000 C CNN
F 2 "" H 4850 5350 50  0001 C CNN
F 3 "" H 4850 5350 50  0001 C CNN
	1    4850 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5300 4850 5350
$EndSCHEMATC

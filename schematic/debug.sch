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
Sheet 3 4
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
L CONN_01X10 J302
U 1 1 59D6FB26
P 4350 4000
F 0 "J302" H 4300 4550 50  0000 L CNN
F 1 "DEBUG HEADER" V 4450 3700 50  0000 L CNN
F 2 "" H 4350 4000 50  0001 C CNN
F 3 "" H 4350 4000 50  0001 C CNN
	1    4350 4000
	-1   0    0    -1  
$EndComp
$Comp
L ATF16V8C_DEBUG U302
U 1 1 59D70528
P 5850 5700
F 0 "U302" H 6000 6500 60  0000 C CNN
F 1 "ATF16V8C_DEBUG" H 6450 5700 47  0000 C CNN
F 2 "" H 4600 6250 60  0001 C CNN
F 3 "" H 4600 6250 60  0001 C CNN
	1    5850 5700
	1    0    0    -1  
$EndComp
$Comp
L ATF16V8C_DEBUG U301
U 1 1 59D70646
P 5800 3650
F 0 "U301" H 5950 4450 60  0000 C CNN
F 1 "ATF16V8C_DEBUG" H 6400 3650 47  0000 C CNN
F 2 "" H 4550 4200 60  0001 C CNN
F 3 "" H 4550 4200 60  0001 C CNN
	1    5800 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3650 5000 3650
Wire Wire Line
	5000 3650 5000 2800
Wire Wire Line
	5000 2800 5400 2800
Wire Wire Line
	4550 3750 5100 3750
Wire Wire Line
	5100 3750 5100 2950
Wire Wire Line
	5100 2950 5400 2950
Wire Wire Line
	4550 3850 5200 3850
Wire Wire Line
	5200 3850 5200 3100
Wire Wire Line
	5200 3100 5400 3100
Wire Wire Line
	4550 3950 5300 3950
Wire Wire Line
	5300 3950 5300 3250
Wire Wire Line
	5300 3250 5400 3250
Wire Wire Line
	4550 4050 5300 4050
Wire Wire Line
	5300 4050 5300 4850
Wire Wire Line
	5300 4850 5450 4850
Wire Wire Line
	4550 4150 5200 4150
Wire Wire Line
	5200 4150 5200 5000
Wire Wire Line
	5200 5000 5450 5000
Wire Wire Line
	4550 4250 5100 4250
Wire Wire Line
	5100 4250 5100 5150
Wire Wire Line
	5100 5150 5450 5150
Wire Wire Line
	4550 4350 5000 4350
Wire Wire Line
	5000 4350 5000 5300
Wire Wire Line
	5000 5300 5450 5300
$Comp
L GND #PWR?
U 1 1 59D707FA
P 5950 3800
F 0 "#PWR?" H 5950 3550 50  0001 C CNN
F 1 "GND" H 5955 3627 50  0000 C CNN
F 2 "" H 5950 3800 50  0001 C CNN
F 3 "" H 5950 3800 50  0001 C CNN
	1    5950 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3700 5950 3800
$Comp
L GND #PWR?
U 1 1 59D7086F
P 6000 5800
F 0 "#PWR?" H 6000 5550 50  0001 C CNN
F 1 "GND" H 6005 5627 50  0000 C CNN
F 2 "" H 6000 5800 50  0001 C CNN
F 3 "" H 6000 5800 50  0001 C CNN
	1    6000 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 5750 6000 5800
$Comp
L GND #PWR?
U 1 1 59D70936
P 4700 3300
F 0 "#PWR?" H 4700 3050 50  0001 C CNN
F 1 "GND" H 4705 3127 50  0000 C CNN
F 2 "" H 4700 3300 50  0001 C CNN
F 3 "" H 4700 3300 50  0001 C CNN
	1    4700 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3550 4550 3250
Wire Wire Line
	4550 3250 4700 3250
Wire Wire Line
	4700 3250 4700 3300
Text GLabel 4600 4450 2    39   Input ~ 0
V_DBG
Wire Wire Line
	4600 4450 4550 4450
Text GLabel 6000 4400 1    39   Input ~ 0
V_DBG
Wire Wire Line
	6000 4400 6000 4450
Text GLabel 5950 2350 1    39   Input ~ 0
V_DBG
Wire Wire Line
	5950 2350 5950 2400
$Comp
L QDSP-G545 D301
U 1 1 59D71B95
P 9200 4950
F 0 "D301" H 9154 5438 50  0000 L CNN
F 1 "QDSP-G545" H 9100 4400 50  0000 L CNN
F 2 "" H 9200 4950 50  0001 C CNN
F 3 "" H 9200 4950 50  0001 C CNN
	1    9200 4950
	1    0    0    -1  
$EndComp
Text GLabel 8100 4250 0    39   Input ~ 0
V_DBG
Wire Wire Line
	8100 4250 8250 4250
Wire Wire Line
	8250 4250 10150 4250
Wire Wire Line
	8250 4250 8250 4550
Wire Wire Line
	10150 4250 10150 4550
Connection ~ 8250 4250
$Comp
L R R301
U 1 1 59D71D7E
P 8100 4650
F 0 "R301" V 8250 4700 50  0001 L CNN
F 1 "220" V 8100 4600 39  0000 L CNN
F 2 "" V 8030 4650 50  0001 C CNN
F 3 "" H 8100 4650 50  0001 C CNN
	1    8100 4650
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71D91
P 8100 4750
F 0 "R?" V 8250 4800 50  0001 L CNN
F 1 "220" V 8100 4700 39  0000 L CNN
F 2 "" V 8030 4750 50  0001 C CNN
F 3 "" H 8100 4750 50  0001 C CNN
	1    8100 4750
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71DA4
P 8100 4850
F 0 "R?" V 8250 4900 50  0001 L CNN
F 1 "220" V 8100 4800 39  0000 L CNN
F 2 "" V 8030 4850 50  0001 C CNN
F 3 "" H 8100 4850 50  0001 C CNN
	1    8100 4850
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71DB7
P 8100 4950
F 0 "R?" V 8250 5000 50  0001 L CNN
F 1 "220" V 8100 4900 39  0000 L CNN
F 2 "" V 8030 4950 50  0001 C CNN
F 3 "" H 8100 4950 50  0001 C CNN
	1    8100 4950
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71DCA
P 8100 5050
F 0 "R?" V 8250 5100 50  0001 L CNN
F 1 "220" V 8100 5000 39  0000 L CNN
F 2 "" V 8030 5050 50  0001 C CNN
F 3 "" H 8100 5050 50  0001 C CNN
	1    8100 5050
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71DDD
P 8100 5150
F 0 "R?" V 8250 5200 50  0001 L CNN
F 1 "220" V 8100 5100 39  0000 L CNN
F 2 "" V 8030 5150 50  0001 C CNN
F 3 "" H 8100 5150 50  0001 C CNN
	1    8100 5150
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71DF0
P 8100 5250
F 0 "R?" V 8250 5300 50  0001 L CNN
F 1 "220" V 8100 5200 39  0000 L CNN
F 2 "" V 8030 5250 50  0001 C CNN
F 3 "" H 8100 5250 50  0001 C CNN
	1    8100 5250
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71E2A
P 10300 4650
F 0 "R?" V 10450 4700 50  0001 L CNN
F 1 "220" V 10300 4600 39  0000 L CNN
F 2 "" V 10230 4650 50  0001 C CNN
F 3 "" H 10300 4650 50  0001 C CNN
	1    10300 4650
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71E30
P 10300 4750
F 0 "R?" V 10450 4800 50  0001 L CNN
F 1 "220" V 10300 4700 39  0000 L CNN
F 2 "" V 10230 4750 50  0001 C CNN
F 3 "" H 10300 4750 50  0001 C CNN
	1    10300 4750
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71E36
P 10300 4850
F 0 "R?" V 10450 4900 50  0001 L CNN
F 1 "220" V 10300 4800 39  0000 L CNN
F 2 "" V 10230 4850 50  0001 C CNN
F 3 "" H 10300 4850 50  0001 C CNN
	1    10300 4850
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71E3C
P 10300 4950
F 0 "R?" V 10450 5000 50  0001 L CNN
F 1 "220" V 10300 4900 39  0000 L CNN
F 2 "" V 10230 4950 50  0001 C CNN
F 3 "" H 10300 4950 50  0001 C CNN
	1    10300 4950
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71E42
P 10300 5050
F 0 "R?" V 10450 5100 50  0001 L CNN
F 1 "220" V 10300 5000 39  0000 L CNN
F 2 "" V 10230 5050 50  0001 C CNN
F 3 "" H 10300 5050 50  0001 C CNN
	1    10300 5050
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71E48
P 10300 5150
F 0 "R?" V 10450 5200 50  0001 L CNN
F 1 "220" V 10300 5100 39  0000 L CNN
F 2 "" V 10230 5150 50  0001 C CNN
F 3 "" H 10300 5150 50  0001 C CNN
	1    10300 5150
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D71E4E
P 10300 5250
F 0 "R?" V 10450 5300 50  0001 L CNN
F 1 "220" V 10300 5200 39  0000 L CNN
F 2 "" V 10230 5250 50  0001 C CNN
F 3 "" H 10300 5250 50  0001 C CNN
	1    10300 5250
	0    1    1    0   
$EndComp
Entry Wire Line
	6800 4650 6900 4750
Entry Wire Line
	6800 4800 6900 4900
Entry Wire Line
	6800 4950 6900 5050
Entry Wire Line
	6800 5100 6900 5200
Entry Wire Line
	6800 5250 6900 5350
Entry Wire Line
	6800 5400 6900 5500
Entry Wire Line
	6800 5550 6900 5650
Wire Wire Line
	6550 4650 6800 4650
Wire Wire Line
	6550 4800 6800 4800
Wire Wire Line
	6550 4950 6800 4950
Wire Wire Line
	6550 5100 6800 5100
Wire Wire Line
	6550 5250 6800 5250
Wire Wire Line
	6550 5400 6800 5400
Wire Wire Line
	6550 5550 6800 5550
Text Label 6600 4650 0    39   ~ 0
D1_A
Text Label 6600 4800 0    39   ~ 0
D1_B
Text Label 6600 4950 0    39   ~ 0
D1_C
Text Label 6600 5100 0    39   ~ 0
D1_D
Text Label 6600 5250 0    39   ~ 0
D1_E
Text Label 6600 5400 0    39   ~ 0
D1_F
Text Label 6600 5550 0    39   ~ 0
D1_G
Wire Bus Line
	6900 4750 6900 4900
Wire Bus Line
	6900 4900 6900 5050
Wire Bus Line
	6900 5050 6900 5200
Wire Bus Line
	6900 5200 6900 5350
Wire Bus Line
	6900 5350 6900 5500
Wire Bus Line
	6900 5500 6900 5650
Wire Bus Line
	6900 5650 6900 5800
Wire Bus Line
	7600 5800 6900 5800
Wire Bus Line
	7600 4750 7600 4850
Wire Bus Line
	7600 4850 7600 4950
Wire Bus Line
	7600 4950 7600 5050
Wire Bus Line
	7600 5050 7600 5150
Wire Bus Line
	7600 5150 7600 5250
Wire Bus Line
	7600 5250 7600 5350
Wire Bus Line
	7600 5350 7600 5800
Entry Wire Line
	7700 4650 7600 4750
Entry Wire Line
	7700 4750 7600 4850
Entry Wire Line
	7700 4850 7600 4950
Entry Wire Line
	7700 4950 7600 5050
Entry Wire Line
	7700 5050 7600 5150
Entry Wire Line
	7700 5150 7600 5250
Entry Wire Line
	7700 5250 7600 5350
Wire Wire Line
	7950 4650 7700 4650
Wire Wire Line
	7950 4750 7700 4750
Wire Wire Line
	7950 4850 7700 4850
Wire Wire Line
	7950 4950 7700 4950
Wire Wire Line
	7950 5050 7700 5050
Wire Wire Line
	7950 5150 7700 5150
Wire Wire Line
	7950 5250 7700 5250
Text Label 7900 4650 2    39   ~ 0
D1_A
Text Label 7900 4750 2    39   ~ 0
D1_B
Text Label 7900 4850 2    39   ~ 0
D1_C
Text Label 7900 4950 2    39   ~ 0
D1_D
Text Label 7900 5050 2    39   ~ 0
D1_E
Text Label 7900 5150 2    39   ~ 0
D1_F
Text Label 7900 5250 2    39   ~ 0
D1_G
Text Label 7100 5800 0    39   ~ 0
D1_[A..G]
Entry Wire Line
	6750 2600 6850 2700
Entry Wire Line
	6750 2750 6850 2850
Entry Wire Line
	6750 2900 6850 3000
Entry Wire Line
	6750 3050 6850 3150
Entry Wire Line
	6750 3200 6850 3300
Entry Wire Line
	6750 3350 6850 3450
Entry Wire Line
	6750 3500 6850 3600
Wire Wire Line
	6500 2600 6750 2600
Wire Wire Line
	6500 2750 6750 2750
Wire Wire Line
	6500 2900 6750 2900
Wire Wire Line
	6500 3050 6750 3050
Wire Wire Line
	6500 3200 6750 3200
Wire Wire Line
	6500 3350 6750 3350
Wire Wire Line
	6500 3500 6750 3500
Text Label 6550 2600 0    39   ~ 0
D0_A
Text Label 6550 2750 0    39   ~ 0
D0_B
Text Label 6550 2900 0    39   ~ 0
D0_C
Text Label 6550 3050 0    39   ~ 0
D0_D
Text Label 6550 3200 0    39   ~ 0
D0_E
Text Label 6550 3350 0    39   ~ 0
D0_F
Text Label 6550 3500 0    39   ~ 0
D0_G
Entry Wire Line
	10800 4550 10700 4650
Entry Wire Line
	10800 4650 10700 4750
Entry Wire Line
	10800 4750 10700 4850
Entry Wire Line
	10800 4850 10700 4950
Entry Wire Line
	10800 4950 10700 5050
Entry Wire Line
	10800 5050 10700 5150
Entry Wire Line
	10800 5150 10700 5250
Wire Wire Line
	10700 4650 10450 4650
Wire Wire Line
	10700 4750 10450 4750
Wire Wire Line
	10700 4850 10450 4850
Wire Wire Line
	10700 4950 10450 4950
Wire Wire Line
	10700 5050 10450 5050
Wire Wire Line
	10700 5150 10450 5150
Wire Wire Line
	10700 5250 10450 5250
Text Label 10650 4650 2    39   ~ 0
D0_A
Text Label 10650 4750 2    39   ~ 0
D0_B
Text Label 10650 4850 2    39   ~ 0
D0_C
Text Label 10650 4950 2    39   ~ 0
D0_D
Text Label 10650 5050 2    39   ~ 0
D0_E
Text Label 10650 5150 2    39   ~ 0
D0_F
Text Label 10650 5250 2    39   ~ 0
D0_G
Wire Bus Line
	6850 2700 6850 2850
Wire Bus Line
	6850 2850 6850 3000
Wire Bus Line
	6850 3000 6850 3150
Wire Bus Line
	6850 3150 6850 3300
Wire Bus Line
	6850 3300 6850 3450
Wire Bus Line
	6850 3450 6850 3600
Wire Bus Line
	6850 3600 6850 3650
Wire Bus Line
	6850 3650 10800 3650
Wire Bus Line
	10800 3650 10800 4550
Wire Bus Line
	10800 4550 10800 4650
Wire Bus Line
	10800 4650 10800 4750
Wire Bus Line
	10800 4750 10800 4850
Wire Bus Line
	10800 4850 10800 4950
Wire Bus Line
	10800 4950 10800 5050
Wire Bus Line
	10800 5050 10800 5150
Text Label 8350 3650 0    39   ~ 0
D0_[A..G]
Text Notes 6050 3750 0    39   ~ 0
(SPLD code: debug.pld)
Text Notes 6100 5800 0    39   ~ 0
(SPLD code: debug.pld)
Text Notes 4200 4600 0    28   ~ 0
+5V for V_DBG may be sourced \nfrom main board or separately
NoConn ~ 8250 5350
NoConn ~ 10150 5350
$Comp
L 74LS374_Flipflop U?
U 1 1 59DE9CCC
P 1750 3650
F 0 "U?" H 2050 3650 60  0000 C CNN
F 1 "74LS374" H 2050 3550 60  0000 C CNN
F 2 "" H 1750 3650 60  0001 C CNN
F 3 "" H 1750 3650 60  0001 C CNN
	1    1750 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 4700 1500 4700
Wire Wire Line
	1500 4700 1500 4900
Wire Wire Line
	1500 4900 2050 4900
$Comp
L GND #PWR?
U 1 1 59DE9CD6
P 2050 4900
F 0 "#PWR?" H 2050 4650 50  0001 C CNN
F 1 "GND" H 2055 4727 50  0000 C CNN
F 2 "" H 2050 4900 50  0001 C CNN
F 3 "" H 2050 4900 50  0001 C CNN
	1    2050 4900
	1    0    0    -1  
$EndComp
Entry Wire Line
	1200 3250 1300 3350
Entry Wire Line
	1200 3400 1300 3500
Entry Wire Line
	1200 3550 1300 3650
Entry Wire Line
	1200 3700 1300 3800
Entry Wire Line
	1200 3850 1300 3950
Entry Wire Line
	1200 4000 1300 4100
Entry Wire Line
	1200 4150 1300 4250
Entry Wire Line
	1200 4300 1300 4400
Text Label 1400 3350 0    39   ~ 0
AD0
Text Label 1400 3500 0    39   ~ 0
AD1
Text Label 1400 3650 0    39   ~ 0
AD2
Text Label 1400 3800 0    39   ~ 0
AD3
Text Label 1400 3950 0    39   ~ 0
AD4
Text Label 1400 4100 0    39   ~ 0
AD5
Text Label 1400 4250 0    39   ~ 0
AD6
Text Label 1400 4400 0    39   ~ 0
AD7
Wire Wire Line
	1300 3350 1550 3350
Wire Wire Line
	1300 3500 1550 3500
Wire Wire Line
	1300 3650 1550 3650
Wire Wire Line
	1300 3800 1550 3800
Wire Wire Line
	1300 3950 1550 3950
Wire Wire Line
	1300 4100 1550 4100
Wire Wire Line
	1300 4250 1550 4250
Wire Wire Line
	1300 4400 1550 4400
Text GLabel 1550 4550 0    39   Input ~ 0
DEBUG
Text GLabel 2050 3100 1    39   Input ~ 0
VCC
Wire Wire Line
	2050 3100 2050 3150
$Comp
L CONN_01X10 J301
U 1 1 59DE9CF7
P 2950 4000
F 0 "J301" H 2900 3450 50  0000 L CNN
F 1 "DEBUG HEADER" V 3050 3700 50  0000 L CNN
F 2 "" H 2950 4000 50  0001 C CNN
F 3 "" H 2950 4000 50  0001 C CNN
	1    2950 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3500 2750 3650
Wire Wire Line
	2550 3650 2750 3750
Wire Wire Line
	2550 3800 2750 3850
Wire Wire Line
	2550 3950 2750 3950
Wire Wire Line
	2550 4100 2750 4050
Wire Wire Line
	2550 4250 2750 4150
Wire Wire Line
	2550 4400 2750 4250
Wire Wire Line
	2550 4550 2750 4350
$Comp
L GND #PWR?
U 1 1 59DE9D06
P 2950 3200
F 0 "#PWR?" H 2950 2950 50  0001 C CNN
F 1 "GND" H 2955 3027 50  0000 C CNN
F 2 "" H 2950 3200 50  0001 C CNN
F 3 "" H 2950 3200 50  0001 C CNN
	1    2950 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 3550 2750 3150
Wire Wire Line
	2750 3150 2950 3150
Wire Wire Line
	2950 3150 2950 3200
Wire Wire Line
	2700 4700 2750 4700
Text GLabel 2700 4700 0    39   Input ~ 0
VCC
Wire Wire Line
	2750 4700 2750 4450
Wire Bus Line
	1200 2900 1200 3250
Wire Bus Line
	1200 3250 1200 3400
Wire Bus Line
	1200 3400 1200 3550
Wire Bus Line
	1200 3550 1200 3700
Wire Bus Line
	1200 3700 1200 3850
Wire Bus Line
	1200 3850 1200 4000
Wire Bus Line
	1200 4000 1200 4150
Wire Bus Line
	1200 4150 1200 4300
Text HLabel 1200 2900 1    39   Input ~ 0
AD[0..7]
Wire Notes Line
	3250 1950 3250 5400
Text Notes 1800 2200 0    47   ~ 9
Debug Interface
Text Notes 3950 2200 0    47   ~ 9
Debug Display
Wire Notes Line
	3250 1950 1000 1950
Wire Notes Line
	1000 1950 950  5400
Wire Notes Line
	950  5400 3250 5400
Wire Notes Line
	3700 1950 3700 6250
Wire Notes Line
	3700 6250 11050 6250
Wire Notes Line
	11050 6250 11050 1950
Wire Notes Line
	11050 1950 3700 1950
$EndSCHEMATC

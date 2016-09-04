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
LIBS:power_switch
LIBS:74xgxx
LIBS:ac-dc
LIBS:actel
LIBS:Altera
LIBS:analog_devices
LIBS:battery_management
LIBS:bbd
LIBS:brooktre
LIBS:cmos_ieee
LIBS:dc-dc
LIBS:diode
LIBS:elec-unifil
LIBS:ESD_Protection
LIBS:ftdi
LIBS:gennum
LIBS:graphic
LIBS:hc11
LIBS:ir
LIBS:Lattice
LIBS:logo
LIBS:maxim
LIBS:microchip_dspic33dsc
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic32mcu
LIBS:motor_drivers
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp_armmcu
LIBS:onsemi
LIBS:Oscillators
LIBS:Power_Management
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:relays
LIBS:rfcom
LIBS:sensors
LIBS:silabs
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:switches
LIBS:transf
LIBS:ttl_ieee
LIBS:video
LIBS:Worldsemi
LIBS:Xicor
LIBS:Zilog
LIBS:power_switch-cache
EELAYER 25 0
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
L WALLPLUG_NOEARTH_220V H1
U 1 1 57CBFFA8
P 2150 1300
F 0 "H1" H 1700 1725 60  0000 C CNN
F 1 "WALLPLUG_NOEARTH_220V" H 2000 1650 60  0001 C CNN
F 2 "" H 2150 1300 60  0001 C CNN
F 3 "" H 2150 1300 60  0001 C CNN
	1    2150 1300
	1    0    0    -1  
$EndComp
$Comp
L WALLSOCKET_NOEARTH_220V H2
U 1 1 57CC00E0
P 5600 1300
F 0 "H2" H 4900 1550 60  0000 C CNN
F 1 "WALLSOCKET_NOEARTH_220V" H 5250 1500 60  0001 C CNN
F 2 "" H 5600 1300 60  0001 C CNN
F 3 "" H 5600 1300 60  0001 C CNN
	1    5600 1300
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 57CC042E
P 8600 1400
F 0 "P2" H 8600 1550 50  0000 C CNN
F 1 "5V=" V 8700 1400 50  0000 C CNN
F 2 "" H 8600 1400 50  0000 C CNN
F 3 "" H 8600 1400 50  0000 C CNN
	1    8600 1400
	-1   0    0    1   
$EndComp
Text Notes 7650 1500 0    60   ~ 12
AC/DC\n220V~ -> 5V=
$Comp
L FARROW2 U2
U 1 1 57CC0667
P 8050 1050
F 0 "U2" H 8100 1100 50  0001 C CNN
F 1 "-" H 8050 950 50  0000 C CNN
F 2 "" H 8050 1050 60  0001 C CNN
F 3 "" H 8050 1050 60  0001 C CNN
	1    8050 1050
	0    -1   -1   0   
$EndComp
$Comp
L C C1
U 1 1 57CC0AE9
P 850 6100
F 0 "C1" H 875 6200 50  0000 L CNN
F 1 "100nF" H 875 6000 50  0000 L CNN
F 2 "" H 888 5950 50  0000 C CNN
F 3 "" H 850 6100 50  0000 C CNN
	1    850  6100
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR12
U 1 1 57CC0BB4
P 8950 1300
F 0 "#PWR12" H 8950 1150 50  0001 C CNN
F 1 "+5V" H 8950 1440 50  0000 C CNN
F 2 "" H 8950 1300 50  0000 C CNN
F 3 "" H 8950 1300 50  0000 C CNN
	1    8950 1300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR1
U 1 1 57CC0BD6
P 850 5450
F 0 "#PWR1" H 850 5300 50  0001 C CNN
F 1 "+5V" H 850 5590 50  0000 C CNN
F 2 "" H 850 5450 50  0000 C CNN
F 3 "" H 850 5450 50  0000 C CNN
	1    850  5450
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 57CC0BF8
P 850 6850
F 0 "#PWR2" H 850 6600 50  0001 C CNN
F 1 "GND" H 850 6700 50  0000 C CNN
F 2 "" H 850 6850 50  0000 C CNN
F 3 "" H 850 6850 50  0000 C CNN
	1    850  6850
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 57CC0C1A
P 8950 1500
F 0 "#PWR13" H 8950 1250 50  0001 C CNN
F 1 "GND" H 8950 1350 50  0000 C CNN
F 2 "" H 8950 1500 50  0000 C CNN
F 3 "" H 8950 1500 50  0000 C CNN
	1    8950 1500
	1    0    0    -1  
$EndComp
$Comp
L BC548 Q1
U 1 1 57CC0D88
P 3300 3350
F 0 "Q1" H 3500 3425 50  0000 L CNN
F 1 "BC548" H 3500 3350 50  0000 L CNN
F 2 "TO-92" H 3500 3275 50  0000 L CIN
F 3 "" H 3300 3350 50  0000 L CNN
	1    3300 3350
	1    0    0    -1  
$EndComp
$Comp
L MMBD4148TW D2
U 1 1 57CC0DD1
P 3650 2950
F 0 "D2" H 3650 3050 50  0000 C CNN
F 1 "MMBD4148TW" H 3650 2850 50  0000 C CNN
F 2 "" H 3550 2950 50  0000 C CNN
F 3 "" H 3650 3050 50  0000 C CNN
	1    3650 2950
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR8
U 1 1 57CC0E54
P 4150 2550
F 0 "#PWR8" H 4150 2400 50  0001 C CNN
F 1 "+5V" H 4150 2690 50  0000 C CNN
F 2 "" H 4150 2550 50  0000 C CNN
F 3 "" H 4150 2550 50  0000 C CNN
	1    4150 2550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR5
U 1 1 57CC0E7A
P 3400 3650
F 0 "#PWR5" H 3400 3400 50  0001 C CNN
F 1 "GND" H 3400 3500 50  0000 C CNN
F 2 "" H 3400 3650 50  0000 C CNN
F 3 "" H 3400 3650 50  0000 C CNN
	1    3400 3650
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 57CC0EA0
P 3100 3700
F 0 "R3" V 3180 3700 50  0000 C CNN
F 1 "10k" V 3100 3700 50  0000 C CNN
F 2 "" V 3030 3700 50  0000 C CNN
F 3 "" H 3100 3700 50  0000 C CNN
	1    3100 3700
	1    0    0    -1  
$EndComp
$Comp
L CNY17-2 U1
U 1 1 57CC11CE
P 2350 2550
F 0 "U1" H 2150 2750 50  0000 L CNN
F 1 "CNY17-2" H 2350 2750 50  0000 L CNN
F 2 "" H 2350 2550 50  0000 L CNN
F 3 "" H 2350 2550 50  0000 L CNN
	1    2350 2550
	0    1    1    0   
$EndComp
$Comp
L D D1
U 1 1 57CC122B
P 2300 2050
F 0 "D1" H 2300 2150 50  0000 C CNN
F 1 "D" H 2300 1950 50  0000 C CNN
F 2 "" H 2300 2050 50  0000 C CNN
F 3 "" H 2300 2050 50  0000 C CNN
	1    2300 2050
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 57CC12B6
P 2200 1700
F 0 "R1" V 2280 1700 50  0000 C CNN
F 1 "100k" V 2200 1700 50  0000 C CNN
F 2 "" V 2130 1700 50  0000 C CNN
F 3 "" H 2200 1700 50  0000 C CNN
	1    2200 1700
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 57CC2493
P 2550 3050
F 0 "R2" V 2630 3050 50  0000 C CNN
F 1 "1k" V 2550 3050 50  0000 C CNN
F 2 "" V 2480 3050 50  0000 C CNN
F 3 "" H 2550 3050 50  0000 C CNN
	1    2550 3050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR3
U 1 1 57CC2896
P 2100 2850
F 0 "#PWR3" H 2100 2600 50  0001 C CNN
F 1 "GND" H 2100 2700 50  0000 C CNN
F 2 "" H 2100 2850 50  0000 C CNN
F 3 "" H 2100 2850 50  0000 C CNN
	1    2100 2850
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR4
U 1 1 57CC28CE
P 2750 3050
F 0 "#PWR4" H 2750 2900 50  0001 C CNN
F 1 "+5V" H 2750 3190 50  0000 C CNN
F 2 "" H 2750 3050 50  0000 C CNN
F 3 "" H 2750 3050 50  0000 C CNN
	1    2750 3050
	0    1    1    0   
$EndComp
$Comp
L CONN_01X02 P1
U 1 1 57CC5032
P 6000 6500
F 0 "P1" H 6000 6650 50  0000 C CNN
F 1 "CONN_01X02" V 6100 6500 50  0000 C CNN
F 2 "" H 6000 6500 50  0000 C CNN
F 3 "" H 6000 6500 50  0000 C CNN
	1    6000 6500
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 57CC5244
P 4800 5750
F 0 "R4" V 4880 5750 50  0000 C CNN
F 1 "10k" V 4800 5750 50  0000 C CNN
F 2 "" V 4730 5750 50  0000 C CNN
F 3 "" H 4800 5750 50  0000 C CNN
	1    4800 5750
	0    1    1    0   
$EndComp
$Comp
L BC548 Q2
U 1 1 57CC52BA
P 5300 5900
F 0 "Q2" H 5500 5975 50  0000 L CNN
F 1 "BC548" H 5500 5900 50  0000 L CNN
F 2 "TO-92" H 5500 5825 50  0000 L CIN
F 3 "" H 5300 5900 50  0000 L CNN
	1    5300 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 57CC5329
P 5400 6150
F 0 "#PWR11" H 5400 5900 50  0001 C CNN
F 1 "GND" H 5400 6000 50  0000 C CNN
F 2 "" H 5400 6150 50  0000 C CNN
F 3 "" H 5400 6150 50  0000 C CNN
	1    5400 6150
	1    0    0    -1  
$EndComp
$Comp
L FINDER-40.31 RL2
U 1 1 57CC5421
P 5950 5250
F 0 "RL2" H 6400 5400 50  0000 L CNN
F 1 "FINDER-40.31" H 6400 5300 50  0000 L CNN
F 2 "" H 5950 5250 50  0000 C CNN
F 3 "" H 5950 5250 50  0000 C CNN
	1    5950 5250
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR10
U 1 1 57CC5543
P 5400 4850
F 0 "#PWR10" H 5400 4700 50  0001 C CNN
F 1 "+5V" H 5400 4990 50  0000 C CNN
F 2 "" H 5400 4850 50  0000 C CNN
F 3 "" H 5400 4850 50  0000 C CNN
	1    5400 4850
	-1   0    0    -1  
$EndComp
$Comp
L MMBD4148TW D2
U 2 1 57CC5590
P 5400 5250
F 0 "D2" H 5400 5350 50  0000 C CNN
F 1 "MMBD4148TW" H 5400 5150 50  0000 C CNN
F 2 "" H 5300 5250 50  0000 C CNN
F 3 "" H 5400 5350 50  0000 C CNN
	2    5400 5250
	0    -1   1    0   
$EndComp
$Comp
L SWITCH_INV SW1
U 1 1 57CC108C
P 4600 2150
F 0 "SW1" H 4400 2300 50  0000 C CNN
F 1 "SWITCH_INV" H 4450 2000 50  0000 C CNN
F 2 "" H 4600 2150 50  0000 C CNN
F 3 "" H 4600 2150 50  0000 C CNN
	1    4600 2150
	1    0    0    1   
$EndComp
$Comp
L 2PIN_POWERTERMINAL_220V H3
U 1 1 57CC5952
P 6900 5250
F 0 "H3" H 6925 5475 60  0000 C CNN
F 1 "2PIN_POWERTERMINAL_220V" H 6750 5600 60  0001 C CNN
F 2 "" H 6900 5250 60  0001 C CNN
F 3 "" H 6900 5250 60  0001 C CNN
	1    6900 5250
	-1   0    0    -1  
$EndComp
$Comp
L FINDER-40.52 RL1
U 1 1 57CC5D13
P 3700 2350
F 0 "RL1" H 4550 2500 50  0000 L CNN
F 1 "FINDER-40.52" H 4550 2400 50  0000 L CNN
F 2 "" H 3700 2350 50  0000 C CNN
F 3 "" H 3700 2350 50  0000 C CNN
	1    3700 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6150 4950 6700 4950
Wire Wire Line
	5400 6150 5400 6100
Wire Wire Line
	5400 5450 5400 5700
Wire Wire Line
	5750 5650 5400 5650
Wire Wire Line
	5750 5550 5750 5650
Connection ~ 5400 4950
Wire Wire Line
	5400 4850 5400 5050
Wire Wire Line
	2350 3050 2400 3050
Wire Wire Line
	2250 2850 2100 2850
Connection ~ 1900 2050
Wire Wire Line
	2150 2050 1900 2050
Wire Wire Line
	1900 2250 2250 2250
Connection ~ 2450 2050
Wire Wire Line
	2700 3050 2750 3050
Wire Wire Line
	3400 3550 3400 3650
Connection ~ 4050 2550
Wire Wire Line
	4000 2550 4150 2550
Wire Wire Line
	4050 2950 4050 2550
Wire Wire Line
	3850 2950 4050 2950
Connection ~ 3400 2950
Wire Wire Line
	3450 2950 3400 2950
Wire Wire Line
	3400 3150 3400 2550
Wire Wire Line
	3100 3550 3100 3350
Wire Wire Line
	8950 1450 8950 1500
Wire Wire Line
	8800 1450 8950 1450
Wire Wire Line
	8950 1350 8950 1300
Wire Wire Line
	8800 1350 8950 1350
Wire Notes Line
	7550 1550 7550 1250
Wire Notes Line
	8350 1550 7550 1550
Wire Notes Line
	8350 1250 8350 1550
Wire Notes Line
	7550 1250 8350 1250
Wire Wire Line
	2350 1200 5400 1200
Wire Wire Line
	2350 1400 3400 1400
Wire Wire Line
	3400 1400 3400 1650
Wire Wire Line
	4000 1750 4000 1400
Wire Wire Line
	4000 1400 5400 1400
Wire Wire Line
	4100 2150 4000 2150
Wire Wire Line
	5100 2050 5100 1400
Connection ~ 5100 1400
Wire Wire Line
	3400 2250 2700 2250
Wire Wire Line
	2700 2250 2700 1400
Connection ~ 2700 1400
Wire Wire Line
	1900 1700 1900 2250
Wire Wire Line
	3400 2050 2450 2050
Wire Wire Line
	2450 2050 2450 2250
Wire Wire Line
	2500 1700 2500 1200
Connection ~ 2500 1200
Wire Wire Line
	2500 1700 2350 1700
Wire Wire Line
	2050 1700 1900 1700
Wire Wire Line
	6250 5550 6700 5550
Connection ~ 5400 5650
Text Notes 6000 5950 0    60   ~ 12
power-switch relay for \nAMP power supply
Text Notes 7900 5350 0    60   ~ 12
OFF-state:\n  - RL1: off\n  - H2: no power\n\nOFF-state, SW1 pushed:\n  - RL1: off\n  - H2: powered, momentarily\n  - IC1: powered => switch on RL1\n  - U1: disconnected\n  - PB0: LOW (shutdwn NOT REQUESTED)\n\nOFF-state, after SW1 pushed = ON-state:\n  - RL1: on\n  - H2/IC1: powered permanently\n  - U1: connected via SW1\n  - PB0: LOW (shutdwn NOT REQUESTED)\n  - PB1 (IN): waiting for HIGH = RPi has booted\n    => when PB1=HIGH => switch on RL2\n\nON-state: SW1 not pushed:\n  - H2: powered permanently\n  - U1: off =>pin7=HIGH\n\nON-state: SW1 pushed:\n  - H2: powered permanently\n  - U1: on =>PA0=LOW => request shutdown (PB0=HIGH) \n    => wait for PB1=LOW (RPi shut down) => switch off RL1
$Comp
L LED D3
U 1 1 57CC90EB
P 4600 3000
F 0 "D3" H 4600 3100 50  0000 C CNN
F 1 "LED" H 4600 2900 50  0000 C CNN
F 2 "" H 4600 3000 50  0000 C CNN
F 3 "" H 4600 3000 50  0000 C CNN
	1    4600 3000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR9
U 1 1 57CC91BC
P 4900 3000
F 0 "#PWR9" H 4900 2850 50  0001 C CNN
F 1 "+5V" H 4900 3140 50  0000 C CNN
F 2 "" H 4900 3000 50  0000 C CNN
F 3 "" H 4900 3000 50  0000 C CNN
	1    4900 3000
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 57CC92B7
P 4400 3400
F 0 "R5" V 4480 3400 50  0000 C CNN
F 1 "220R" V 4400 3400 50  0000 C CNN
F 2 "" V 4330 3400 50  0000 C CNN
F 3 "" H 4400 3400 50  0000 C CNN
	1    4400 3400
	1    0    0    -1  
$EndComp
Wire Notes Line
	4600 3000 4600 2150
Wire Wire Line
	4900 3000 4800 3000
Wire Wire Line
	4400 3000 4400 3250
Text Notes 4700 3700 0    60   ~ 12
LED inside power button:\n  - off: power off\n  - on: power on, RPi booted\n  - blink slow: bootig\n  - blink faster: waiting for shutdown
$Comp
L ATTINY84-P IC1
U 1 1 57CCAB9D
P 1900 6150
F 0 "IC1" H 1050 6900 50  0000 C CNN
F 1 "ATTINY84-P" H 2600 5400 50  0000 C CNN
F 2 "DIP14" H 1900 5950 50  0000 C CIN
F 3 "" H 1900 6150 50  0000 C CNN
	1    1900 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  5450 850  5950
Wire Wire Line
	850  6250 850  6850
Connection ~ 850  6750
Connection ~ 850  5550
$Comp
L CONN_02X03 P3
U 1 1 57CCB357
P 3500 7250
F 0 "P3" H 3500 7450 50  0000 C CNN
F 1 "CONN_02X03" H 3500 7050 50  0000 C CNN
F 2 "" H 3500 6050 50  0000 C CNN
F 3 "" H 3500 6050 50  0000 C CNN
	1    3500 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2850 2350 5400
Wire Wire Line
	2950 6750 2950 7350
Wire Wire Line
	2950 7350 3250 7350
Wire Wire Line
	3250 7250 3050 7250
Wire Wire Line
	3050 7250 3050 5950
Wire Wire Line
	3050 5950 2950 5950
Wire Wire Line
	3250 7150 3150 7150
Wire Wire Line
	3150 7150 3150 6050
Wire Wire Line
	3150 6050 2950 6050
Wire Wire Line
	3750 7250 3850 7250
Wire Wire Line
	3850 7250 3850 6150
Wire Wire Line
	3850 6150 2950 6150
$Comp
L GND #PWR7
U 1 1 57CCBC19
P 3750 7550
F 0 "#PWR7" H 3750 7300 50  0001 C CNN
F 1 "GND" H 3750 7400 50  0000 C CNN
F 2 "" H 3750 7550 50  0000 C CNN
F 3 "" H 3750 7550 50  0000 C CNN
	1    3750 7550
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR6
U 1 1 57CCBC69
P 3750 7050
F 0 "#PWR6" H 3750 6900 50  0001 C CNN
F 1 "+5V" H 3750 7190 50  0000 C CNN
F 2 "" H 3750 7050 50  0000 C CNN
F 3 "" H 3750 7050 50  0000 C CNN
	1    3750 7050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3750 7050 3750 7150
Wire Wire Line
	3750 7350 3750 7550
Wire Wire Line
	5800 6450 2950 6450
Wire Wire Line
	2950 6550 5800 6550
Wire Wire Line
	4400 3550 4400 6250
Wire Wire Line
	4400 6250 2950 6250
Wire Wire Line
	2350 5400 3050 5400
Wire Wire Line
	3050 5400 3050 5550
Wire Wire Line
	3050 5550 2950 5550
Connection ~ 2350 3050
Wire Wire Line
	3100 3850 3100 5300
Wire Wire Line
	3100 5300 3200 5300
Wire Wire Line
	3200 5300 3200 5650
Wire Wire Line
	3200 5650 2950 5650
Wire Wire Line
	4950 5750 5100 5750
Wire Wire Line
	5100 5750 5100 5900
Wire Wire Line
	5400 4950 5750 4950
Wire Notes Line
	7850 2550 10850 2550
Wire Notes Line
	10850 2550 10850 5400
Wire Notes Line
	10850 5400 7850 5400
Wire Notes Line
	7850 5400 7850 2550
Wire Notes Line
	8150 1700 8150 1700
Wire Wire Line
	4650 5750 2950 5750
Wire Notes Line
	7800 2500 7800 5450
Wire Notes Line
	7800 5450 10900 5450
Wire Notes Line
	10900 5450 10900 2500
Wire Notes Line
	10900 2500 7800 2500
Wire Wire Line
	6700 4950 6700 5150
Wire Wire Line
	6700 5550 6700 5350
$EndSCHEMATC

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
LIBS:rpi_webradio_lib
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
LIBS:power_connectors
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
L CONN_01X02 P2
U 1 1 57CC042E
P 8600 1400
F 0 "P2" H 8600 1550 50  0000 C CNN
F 1 "5V=" V 8700 1400 50  0000 C CNN
F 2 "Connect:bornier2" H 8600 1400 50  0001 C CNN
F 3 "" H 8600 1400 50  0000 C CNN
	1    8600 1400
	-1   0    0    1   
$EndComp
Text Notes 7650 1500 0    60   ~ 12
AC/DC\n220V~ -> 5V=
$Comp
L C C1
U 1 1 57CC0AE9
P 850 6100
F 0 "C1" H 875 6200 50  0000 L CNN
F 1 "100nF" H 875 6000 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 888 5950 50  0001 C CNN
F 3 "" H 850 6100 50  0000 C CNN
	1    850  6100
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR01
U 1 1 57CC0BB4
P 8950 1300
F 0 "#PWR01" H 8950 1150 50  0001 C CNN
F 1 "+5V" H 8950 1440 50  0000 C CNN
F 2 "" H 8950 1300 50  0000 C CNN
F 3 "" H 8950 1300 50  0000 C CNN
	1    8950 1300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR02
U 1 1 57CC0BD6
P 850 5450
F 0 "#PWR02" H 850 5300 50  0001 C CNN
F 1 "+5V" H 850 5590 50  0000 C CNN
F 2 "" H 850 5450 50  0000 C CNN
F 3 "" H 850 5450 50  0000 C CNN
	1    850  5450
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 57CC0BF8
P 850 6850
F 0 "#PWR03" H 850 6600 50  0001 C CNN
F 1 "GND" H 850 6700 50  0000 C CNN
F 2 "" H 850 6850 50  0000 C CNN
F 3 "" H 850 6850 50  0000 C CNN
	1    850  6850
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 57CC0C1A
P 8950 1500
F 0 "#PWR04" H 8950 1250 50  0001 C CNN
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
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 3500 3275 50  0001 L CIN
F 3 "" H 3300 3350 50  0000 L CNN
	1    3300 3350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 57CC0E54
P 4150 2550
F 0 "#PWR05" H 4150 2400 50  0001 C CNN
F 1 "+5V" H 4150 2690 50  0000 C CNN
F 2 "" H 4150 2550 50  0000 C CNN
F 3 "" H 4150 2550 50  0000 C CNN
	1    4150 2550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR06
U 1 1 57CC0E7A
P 3400 3650
F 0 "#PWR06" H 3400 3400 50  0001 C CNN
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
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3030 3700 50  0001 C CNN
F 3 "" H 3100 3700 50  0000 C CNN
	1    3100 3700
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 57CC12B6
P 2200 1700
F 0 "R1" V 2280 1700 50  0000 C CNN
F 1 "47k" V 2200 1700 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2130 1700 50  0001 C CNN
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
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2480 3050 50  0001 C CNN
F 3 "" H 2550 3050 50  0000 C CNN
	1    2550 3050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR07
U 1 1 57CC2896
P 2650 2850
F 0 "#PWR07" H 2650 2600 50  0001 C CNN
F 1 "GND" H 2650 2700 50  0000 C CNN
F 2 "" H 2650 2850 50  0000 C CNN
F 3 "" H 2650 2850 50  0000 C CNN
	1    2650 2850
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR08
U 1 1 57CC28CE
P 2750 3050
F 0 "#PWR08" H 2750 2900 50  0001 C CNN
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
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 6000 6500 50  0001 C CNN
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
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4730 5750 50  0001 C CNN
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
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 5500 5825 50  0001 L CIN
F 3 "" H 5300 5900 50  0000 L CNN
	1    5300 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 57CC5329
P 5400 6150
F 0 "#PWR09" H 5400 5900 50  0001 C CNN
F 1 "GND" H 5400 6000 50  0000 C CNN
F 2 "" H 5400 6150 50  0000 C CNN
F 3 "" H 5400 6150 50  0000 C CNN
	1    5400 6150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR010
U 1 1 57CC5543
P 5400 4850
F 0 "#PWR010" H 5400 4700 50  0001 C CNN
F 1 "+5V" H 5400 4990 50  0000 C CNN
F 2 "" H 5400 4850 50  0000 C CNN
F 3 "" H 5400 4850 50  0000 C CNN
	1    5400 4850
	-1   0    0    -1  
$EndComp
$Comp
L FINDER-40.52 RL1
U 1 1 57CC5D13
P 3700 2350
F 0 "RL1" H 4550 2500 50  0000 L CNN
F 1 "FINDER-40.52" H 4550 2400 50  0000 L CNN
F 2 "Relays_ThroughHole:Relay_DPDT_Schrack-RT2_RM5mm" H 3700 2350 50  0001 C CNN
F 3 "" H 3700 2350 50  0000 C CNN
	1    3700 2350
	0    -1   -1   0   
$EndComp
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
	5400 4850 5400 5150
Wire Wire Line
	2150 3050 2400 3050
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
	3750 2950 4050 2950
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
	5100 1400 5100 2150
Connection ~ 5100 1400
Wire Wire Line
	3400 2250 2700 2250
Wire Wire Line
	2700 2250 2700 1400
Connection ~ 2700 1400
Wire Wire Line
	2500 1700 2500 1200
Connection ~ 2500 1200
Wire Wire Line
	2500 1700 2350 1700
Connection ~ 5400 5650
Text Notes 6700 5800 0    60   ~ 12
power-switch relay for \nAMP power supply
Text Notes 7900 5350 0    60   ~ 12
OFF-state:\n  - RL1: off\n  - H2: no power\n\nOFF-state, SW1 pushed:\n  - RL1: off\n  - H2: powered, momentarily\n  - IC1: powered => switch on RL1\n  - U1: disconnected\n  - PB0: LOW (shutdwn NOT REQUESTED)\n\nOFF-state, after SW1 pushed = ON-state:\n  - RL1: on\n  - H2/IC1: powered permanently\n  - U1: connected via SW1\n  - PB0: LOW (shutdwn NOT REQUESTED)\n  - PB1 (IN): waiting for HIGH = RPi has booted\n    => when PB1=HIGH => switch on RL2\n\nON-state: SW1 not pushed:\n  - H2: powered permanently\n  - U1: off =>pin7=HIGH\n\nON-state: SW1 pushed:\n  - H2: powered permanently\n  - U1: on =>PA0=LOW => request shutdown (PB0=HIGH) \n    => wait for PB1=LOW (RPi shut down) => switch off RL1
$Comp
L LED D3
U 1 1 57CC90EB
P 4600 3000
F 0 "D3" H 4600 3100 50  0000 C CNN
F 1 "LED" H 4600 2900 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 4600 3000 50  0001 C CNN
F 3 "" H 4600 3000 50  0000 C CNN
	1    4600 3000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR011
U 1 1 57CC91BC
P 4900 3000
F 0 "#PWR011" H 4900 2850 50  0001 C CNN
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
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4330 3400 50  0001 C CNN
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
F 2 "Housings_DIP:DIP-14_W7.62mm_LongPads" H 1900 5950 50  0001 C CIN
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
	3500 7250 3850 7250
Wire Wire Line
	3850 7250 3850 6150
Wire Wire Line
	3850 6150 2950 6150
$Comp
L GND #PWR012
U 1 1 57CCBC19
P 3750 7550
F 0 "#PWR012" H 3750 7300 50  0001 C CNN
F 1 "GND" H 3750 7400 50  0000 C CNN
F 2 "" H 3750 7550 50  0000 C CNN
F 3 "" H 3750 7550 50  0000 C CNN
	1    3750 7550
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR013
U 1 1 57CCBC69
P 3750 7050
F 0 "#PWR013" H 3750 6900 50  0001 C CNN
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
$Comp
L FINDER-40.52 RL2
U 1 1 57D56536
P 5950 5250
F 0 "RL2" H 6800 5400 50  0000 L CNN
F 1 "FINDER-40.52" H 6800 5300 50  0000 L CNN
F 2 "Relays_ThroughHole:Relay_DPDT_Schrack-RT2_RM5mm" H 5950 5250 50  0001 C CNN
F 3 "" H 5950 5250 50  0000 C CNN
	1    5950 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 5600 6150 5600
Wire Wire Line
	6150 5600 6150 5550
Wire Wire Line
	6450 5600 6550 5600
Wire Wire Line
	6550 5600 6550 5550
Wire Wire Line
	6250 4950 6250 4850
Wire Wire Line
	6250 4850 6350 4850
Wire Wire Line
	6650 4950 6650 4850
Wire Wire Line
	6650 4850 6550 4850
$Comp
L AVR-ISP-6 CON1
U 1 1 57D57B05
P 3400 7250
F 0 "CON1" H 3295 7490 50  0000 C CNN
F 1 "AVR-ISP-6" H 3135 7020 50  0000 L BNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" V 2880 7290 50  0001 C CNN
F 3 "" H 3375 7250 50  0000 C CNN
	1    3400 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 7150 3500 7150
Wire Wire Line
	3500 7350 3750 7350
Wire Wire Line
	5800 7000 4100 7000
Wire Wire Line
	4100 7000 4100 5850
Wire Wire Line
	4100 5850 2950 5850
Wire Wire Line
	2950 6650 4000 6650
Wire Wire Line
	4000 6650 4000 7100
Wire Wire Line
	4000 7100 5800 7100
$Comp
L D D1
U 1 1 57DECD80
P 3600 2950
F 0 "D1" H 3600 3050 50  0000 C CNN
F 1 "D" H 3600 2850 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-35_SOD27_Horizontal_RM10" H 3600 2950 50  0001 C CNN
F 3 "" H 3600 2950 50  0000 C CNN
	1    3600 2950
	-1   0    0    1   
$EndComp
$Comp
L D D2
U 1 1 57DED00A
P 5400 5300
F 0 "D2" H 5400 5400 50  0000 C CNN
F 1 "D" H 5400 5200 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-35_SOD27_Horizontal_RM10" H 5400 5300 50  0001 C CNN
F 3 "" H 5400 5300 50  0000 C CNN
	1    5400 5300
	0    1    1    0   
$EndComp
$Comp
L LTV-814 U1
U 1 1 57DED362
P 2250 2550
F 0 "U1" H 2050 2750 50  0000 L CNN
F 1 "LTV-814" H 2250 2750 50  0000 L CNN
F 2 "Housings_DIP:DIP-4_W7.62mm_LongPads" H 2050 2350 50  0001 L CIN
F 3 "" H 2275 2550 50  0000 L CNN
	1    2250 2550
	0    -1   1    0   
$EndComp
Wire Wire Line
	2350 2250 2350 2050
Wire Wire Line
	2050 1700 2050 2250
Wire Wire Line
	2050 2250 2150 2250
Wire Notes Line
	7650 1050 8150 1050
Wire Notes Line
	8150 1050 8000 1150
Wire Notes Line
	8150 1050 8000 950 
$Comp
L SPST SW1
U 1 1 57DEE3BF
P 4600 2150
F 0 "SW1" H 4600 2250 50  0000 C CNN
F 1 "SPST" H 4600 2050 50  0000 C CNN
F 2 "Connect:bornier2" H 4600 2150 50  0001 C CNN
F 3 "" H 4600 2150 50  0000 C CNN
	1    4600 2150
	1    0    0    -1  
$EndComp
$Comp
L WALLPLUG_NOEARTH_220V K1
U 1 1 57DEDE39
P 2150 1300
F 0 "K1" H 1700 1725 60  0000 C CNN
F 1 "WALLPLUG_NOEARTH_220V" H 2000 1650 60  0001 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 2150 1300 60  0001 C CNN
F 3 "" H 2150 1300 60  0001 C CNN
	1    2150 1300
	1    0    0    -1  
$EndComp
$Comp
L WALLSOCKET_NOEARTH_220V K2
U 1 1 57DEECFF
P 5400 1300
F 0 "K2" H 4900 1450 60  0000 L BNN
F 1 "WALLSOCKET_NOEARTH_220V" H 4900 1550 60  0001 L BNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 5400 1300 60  0001 C CNN
F 3 "" H 5400 1300 60  0001 C CNN
	1    5400 1300
	-1   0    0    1   
$EndComp
$Comp
L screw_terminal_2x01 H2
U 1 1 57DEF43E
P 6550 4850
F 0 "H2" H 6300 5000 50  0000 L TNN
F 1 "screw_terminal_2x01" H 6300 5100 50  0001 L TNN
F 2 "Connect:bornier2" H 6350 4750 60  0001 C CNN
F 3 "" H 6350 4750 60  0001 C CNN
	1    6550 4850
	0    1    1    0   
$EndComp
$Comp
L screw_terminal_2x01 H1
U 1 1 57DEF4F0
P 6250 5600
F 0 "H1" H 6000 5750 50  0000 L TNN
F 1 "screw_terminal_2x01" H 6000 5850 50  0001 L TNN
F 2 "Connect:bornier2" H 6050 5500 60  0001 C CNN
F 3 "" H 6050 5500 60  0001 C CNN
	1    6250 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2650 2850 2350 2850
Wire Wire Line
	2150 3050 2150 2850
Wire Wire Line
	2350 3050 2350 5400
$Comp
L CONN_01X01 P3
U 1 1 57DEFFB9
P 6000 7000
F 0 "P3" H 6000 7100 50  0000 C CNN
F 1 "CONN_01X01" V 6100 7000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 6000 7000 50  0001 C CNN
F 3 "" H 6000 7000 50  0000 C CNN
	1    6000 7000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P4
U 1 1 57DF003E
P 6000 7100
F 0 "P4" H 6000 7200 50  0000 C CNN
F 1 "CONN_01X01" V 6100 7100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 6000 7100 50  0001 C CNN
F 3 "" H 6000 7100 50  0000 C CNN
	1    6000 7100
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 57DF0773
P 2500 2050
F 0 "R6" V 2580 2050 50  0000 C CNN
F 1 "47k" V 2500 2050 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2430 2050 50  0001 C CNN
F 3 "" H 2500 2050 50  0000 C CNN
	1    2500 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3400 2050 2650 2050
$EndSCHEMATC

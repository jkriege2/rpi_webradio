EESchema Schematic File Version 2
LIBS:amplifier-rescue
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
LIBS:amplifier-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L Diode_Bridge D2
U 1 1 57E09893
P 3100 3050
F 0 "D2" H 2850 3350 50  0000 C CNN
F 1 "B40C5000" H 3450 2700 50  0000 C CNN
F 2 "special_symbols:Diode_Bridge_32x5.7" H 3100 3050 50  0001 C CNN
F 3 "" H 3100 3050 50  0000 C CNN
	1    3100 3050
	0    -1   -1   0   
$EndComp
$Comp
L screw_terminal_2x01 H1
U 1 1 57E098E4
P 2500 2850
F 0 "H1" H 2250 3000 50  0000 L TNN
F 1 "screw_terminal_2x01" H 2250 3100 50  0001 L TNN
F 2 "Connect:bornier2" H 2300 2750 60  0001 C CNN
F 3 "" H 2300 2750 60  0001 C CNN
	1    2500 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3050 2700 3050
Wire Wire Line
	2500 2850 2500 2550
Wire Wire Line
	2500 2550 3650 2550
Wire Wire Line
	3650 2550 3650 3050
Wire Wire Line
	3650 3050 3500 3050
$Comp
L screw_terminal_2x01 H2
U 1 1 57E099C7
P 5550 3150
F 0 "H2" H 5300 3300 50  0000 L TNN
F 1 "screw_terminal_2x01" H 5300 3400 50  0001 L TNN
F 2 "Connect:bornier2" H 5350 3050 60  0001 C CNN
F 3 "" H 5350 3050 60  0001 C CNN
	1    5550 3150
	-1   0    0    1   
$EndComp
Wire Wire Line
	5550 3150 5550 3650
Wire Wire Line
	5550 3650 3100 3650
Wire Wire Line
	3100 3650 3100 3450
Wire Wire Line
	3100 2650 3100 2350
Wire Wire Line
	5550 2350 5550 2950
$Comp
L R R17
U 1 1 57E09AC0
P 5250 2750
F 0 "R17" V 5330 2750 50  0000 C CNN
F 1 "1k5" V 5250 2750 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 5180 2750 50  0001 C CNN
F 3 "" H 5250 2750 50  0000 C CNN
	1    5250 2750
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 57E09B2F
P 5050 2350
F 0 "R16" V 5130 2350 50  0000 C CNN
F 1 "1R" V 5050 2350 50  0000 C CNN
F 2 "special_symbols:Resistor_Ceramic_Horizontal_L25mm-W6.4mm-H6.4mm-p30mm" V 4980 2350 50  0001 C CNN
F 3 "" H 5050 2350 50  0000 C CNN
	1    5050 2350
	0    1    1    0   
$EndComp
$Comp
L LED D3
U 1 1 57E09BF5
P 5250 3250
F 0 "D3" H 5250 3350 50  0000 C CNN
F 1 "LED" H 5250 3150 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 5250 3250 50  0001 C CNN
F 3 "" H 5250 3250 50  0000 C CNN
	1    5250 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5250 3450 5250 3650
Connection ~ 5250 3650
Wire Wire Line
	5250 3050 5250 2900
Wire Wire Line
	5200 2350 5550 2350
Wire Wire Line
	5250 2600 5250 2350
Connection ~ 5250 2350
Wire Wire Line
	3100 2350 4900 2350
$Comp
L C C36
U 1 1 57E09DAC
P 4850 2950
F 0 "C36" H 4875 3050 50  0000 L CNN
F 1 "100nF" H 4875 2850 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D6_P5" H 4888 2800 50  0001 C CNN
F 3 "" H 4850 2950 50  0000 C CNN
	1    4850 2950
	1    0    0    -1  
$EndComp
$Comp
L CP C33
U 1 1 57E09E7C
P 4150 2950
F 0 "C33" H 4175 3050 50  0000 L CNN
F 1 "2200µF" H 4175 2850 50  0000 L CNN
F 2 "special_symbols:C_Radial_D30_L51_P10_3pin" H 4188 2800 50  0001 C CNN
F 3 "" H 4150 2950 50  0000 C CNN
	1    4150 2950
	1    0    0    -1  
$EndComp
$Comp
L CP C34
U 1 1 57E09EAB
P 4400 2950
F 0 "C34" H 4425 3050 50  0000 L CNN
F 1 "2200µF" H 4425 2850 50  0000 L CNN
F 2 "special_symbols:C_Radial_D30_L51_P10_3pin" H 4438 2800 50  0001 C CNN
F 3 "" H 4400 2950 50  0000 C CNN
	1    4400 2950
	1    0    0    -1  
$EndComp
$Comp
L CP C35
U 1 1 57E09F07
P 4650 2950
F 0 "C35" H 4675 3050 50  0000 L CNN
F 1 "2200µF" H 4675 2850 50  0000 L CNN
F 2 "special_symbols:C_Radial_D30_L51_P10_3pin" H 4688 2800 50  0001 C CNN
F 3 "" H 4650 2950 50  0000 C CNN
	1    4650 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2800 4850 2350
Connection ~ 4850 2350
Wire Wire Line
	4650 2800 4650 2350
Connection ~ 4650 2350
Wire Wire Line
	4400 2800 4400 2350
Connection ~ 4400 2350
Wire Wire Line
	4150 2800 4150 2350
Connection ~ 4150 2350
Connection ~ 3850 2350
Connection ~ 3850 3650
Wire Wire Line
	4150 3100 4150 3650
Connection ~ 4150 3650
Wire Wire Line
	4400 3100 4400 3650
Connection ~ 4400 3650
Wire Wire Line
	4650 3100 4650 3650
Connection ~ 4650 3650
Wire Wire Line
	4850 3100 4850 3650
Connection ~ 4850 3650
$EndSCHEMATC

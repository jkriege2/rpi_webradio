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
LIBS:motors
LIBS:amplifier-cache
EELAYER 25 0
EELAYER END
$Descr A3 11693 16535 portrait
encoding utf-8
Sheet 1 2
Title "Webradio-Amplifier (with tube-preamp)"
Date "2016-09-03"
Rev ""
Comp "(c) 2016 Jan Krieger"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LM1875 U1
U 1 1 57CB30F1
P 8600 4250
F 0 "U1" H 8800 4500 50  0000 C CNN
F 1 "LM1875" H 8800 4450 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:Pentawatt_Neutral_Staggered_Verical_TO220-5-T05D" H 8450 4250 50  0001 C CIN
F 3 "" H 8600 4250 50  0000 C CNN
	1    8600 4250
	1    0    0    -1  
$EndComp
$Comp
L CP C7
U 1 1 57CB323C
P 9500 4250
F 0 "C7" H 9525 4350 50  0000 L CNN
F 1 "4700µF" H 9525 4150 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D18_L36_P7.5" H 9538 4100 50  0001 C CNN
F 3 "" H 9500 4250 50  0000 C CNN
	1    9500 4250
	0    -1   -1   0   
$EndComp
$Comp
L CP C3
U 1 1 57CB32C5
P 8050 5450
F 0 "C3" H 8075 5550 50  0000 L CNN
F 1 "10µF" H 8075 5350 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 8088 5300 50  0001 C CNN
F 3 "" H 8050 5450 50  0000 C CNN
	1    8050 5450
	1    0    0    -1  
$EndComp
$Comp
L CP C4
U 1 1 57CB33B3
P 8850 3450
F 0 "C4" H 8875 3550 50  0000 L CNN
F 1 "100µF" H 8875 3350 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D10_L13_P5" H 8888 3300 50  0001 C CNN
F 3 "" H 8850 3450 50  0000 C CNN
	1    8850 3450
	1    0    0    -1  
$EndComp
$Comp
L CP C2
U 1 1 57CB344C
P 7650 5450
F 0 "C2" H 7675 5550 50  0000 L CNN
F 1 "10µF" H 7675 5350 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 7688 5300 50  0001 C CNN
F 3 "" H 7650 5450 50  0000 C CNN
	1    7650 5450
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 57CB35CD
P 7050 4100
F 0 "C1" H 7075 4200 50  0000 L CNN
F 1 "100nF" H 7075 4000 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 7088 3950 50  0001 C CNN
F 3 "" H 7050 4100 50  0000 C CNN
	1    7050 4100
	0    1    1    0   
$EndComp
$Comp
L C C5
U 1 1 57CB36F6
P 9250 3450
F 0 "C5" H 9275 3550 50  0000 L CNN
F 1 "100nF" H 9275 3350 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 9288 3300 50  0001 C CNN
F 3 "" H 9250 3450 50  0000 C CNN
	1    9250 3450
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 57CB37AC
P 9250 5450
F 0 "C6" H 9275 5550 50  0000 L CNN
F 1 "100nF" H 9275 5350 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 9288 5300 50  0001 C CNN
F 3 "" H 9250 5450 50  0000 C CNN
	1    9250 5450
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 57CB38FD
P 9250 5050
F 0 "R6" V 9330 5050 50  0000 C CNN
F 1 "2k2" V 9250 5050 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 9180 5050 50  0001 C CNN
F 3 "" H 9250 5050 50  0000 C CNN
	1    9250 5050
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 57CB39A2
P 8850 4850
F 0 "R5" V 8930 4850 50  0000 C CNN
F 1 "220k" V 8850 4850 50  0000 C CNN
F 2 "special_symbols:Resistor_Vertical_RM2.5mm" V 8780 4850 50  0001 C CNN
F 3 "" H 8850 4850 50  0000 C CNN
	1    8850 4850
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 57CB39F1
P 8050 5050
F 0 "R4" V 8130 5050 50  0000 C CNN
F 1 "22k" V 8050 5050 50  0000 C CNN
F 2 "special_symbols:Resistor_Vertical_RM2.5mm" V 7980 5050 50  0001 C CNN
F 3 "" H 8050 5050 50  0000 C CNN
	1    8050 5050
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 57CB3A52
P 7400 5450
F 0 "R2" V 7480 5450 50  0000 C CNN
F 1 "2k2" V 7400 5450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7330 5450 50  0001 C CNN
F 3 "" H 7400 5450 50  0000 C CNN
	1    7400 5450
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 57CB3ADB
P 7400 3450
F 0 "R1" V 7480 3450 50  0000 C CNN
F 1 "2k2" V 7400 3450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7330 3450 50  0001 C CNN
F 3 "" H 7400 3450 50  0000 C CNN
	1    7400 3450
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 57CB3B2A
P 7650 4800
F 0 "R3" V 7730 4800 50  0000 C CNN
F 1 "330k" V 7650 4800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7580 4800 50  0001 C CNN
F 3 "" H 7650 4800 50  0000 C CNN
	1    7650 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 57CB45F1
P 8600 5750
F 0 "#PWR01" H 8600 5500 50  0001 C CNN
F 1 "GND" H 8600 5600 50  0000 C CNN
F 2 "" H 8600 5750 50  0000 C CNN
F 3 "" H 8600 5750 50  0000 C CNN
	1    8600 5750
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR02
U 1 1 57CB4621
P 8600 3150
F 0 "#PWR02" H 8600 3000 50  0001 C CNN
F 1 "+24V" H 8600 3290 50  0000 C CNN
F 2 "" H 8600 3150 50  0000 C CNN
F 3 "" H 8600 3150 50  0000 C CNN
	1    8600 3150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 57CB47CF
P 8850 3700
F 0 "#PWR03" H 8850 3450 50  0001 C CNN
F 1 "GND" H 8850 3550 50  0000 C CNN
F 2 "" H 8850 3700 50  0000 C CNN
F 3 "" H 8850 3700 50  0000 C CNN
	1    8850 3700
	1    0    0    -1  
$EndComp
$Comp
L SPEAKER SP1
U 1 1 57CB4E18
P 10900 4350
F 0 "SP1" H 10800 4600 50  0000 C CNN
F 1 "SPEAKER" H 10800 4100 50  0000 C CNN
F 2 "Connect:bornier2" H 10900 4350 50  0001 C CNN
F 3 "" H 10900 4350 50  0000 C CNN
	1    10900 4350
	1    0    0    -1  
$EndComp
Text Notes 6800 2750 0    118  ~ 24
main speaker amplifier\nA=1+220k/22k=11
$Comp
L C C10
U 1 1 57CB78B0
P 4050 2800
F 0 "C10" H 4075 2900 50  0000 L CNN
F 1 "68nF" H 4075 2700 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 4088 2650 50  0001 C CNN
F 3 "" H 4050 2800 50  0000 C CNN
	1    4050 2800
	0    1    1    0   
$EndComp
$Comp
L CP C12
U 1 1 57CB792F
P 4750 3450
F 0 "C12" H 4775 3550 50  0000 L CNN
F 1 "10µF" H 4775 3350 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L11_P2.5" H 4788 3300 50  0001 C CNN
F 3 "" H 4750 3450 50  0000 C CNN
	1    4750 3450
	1    0    0    -1  
$EndComp
$Comp
L CP C9
U 1 1 57CB7A9A
P 4000 2150
F 0 "C9" H 4025 2250 50  0000 L CNN
F 1 "10µF" H 4025 2050 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 4038 2000 50  0001 C CNN
F 3 "" H 4000 2150 50  0000 C CNN
	1    4000 2150
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 57CB7D03
P 4650 2100
F 0 "R11" V 4730 2100 50  0000 C CNN
F 1 "47k" V 4650 2100 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4580 2100 50  0001 C CNN
F 3 "" H 4650 2100 50  0000 C CNN
	1    4650 2100
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 57CB7D72
P 4650 1700
F 0 "R10" V 4730 1700 50  0000 C CNN
F 1 "8k2" V 4650 1700 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4580 1700 50  0001 C CNN
F 3 "" H 4650 1700 50  0000 C CNN
	1    4650 1700
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 57CB831F
P 4950 3200
F 0 "R12" V 5030 3200 50  0000 C CNN
F 1 "1k2" V 4950 3200 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4880 3200 50  0001 C CNN
F 3 "" H 4950 3200 50  0000 C CNN
	1    4950 3200
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 57CB83D2
P 5150 2100
F 0 "R14" V 5230 2100 50  0000 C CNN
F 1 "1k2" V 5150 2100 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5080 2100 50  0001 C CNN
F 3 "" H 5150 2100 50  0000 C CNN
	1    5150 2100
	1    0    0    -1  
$EndComp
$Comp
L CP C14
U 1 1 57CB8473
P 5150 3450
F 0 "C14" H 5175 3550 50  0000 L CNN
F 1 "10µF" H 5175 3350 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 5188 3300 50  0001 C CNN
F 3 "" H 5150 3450 50  0000 C CNN
	1    5150 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 57CB8EEB
P 4550 3700
F 0 "#PWR04" H 4550 3450 50  0001 C CNN
F 1 "GND" H 4550 3550 50  0000 C CNN
F 2 "" H 4550 3700 50  0000 C CNN
F 3 "" H 4550 3700 50  0000 C CNN
	1    4550 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 57CB9B33
P 1900 3950
F 0 "#PWR05" H 1900 3700 50  0001 C CNN
F 1 "GND" H 1900 3800 50  0000 C CNN
F 2 "" H 1900 3950 50  0000 C CNN
F 3 "" H 1900 3950 50  0000 C CNN
	1    1900 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 57CBA07F
P 4000 2350
F 0 "#PWR06" H 4000 2100 50  0001 C CNN
F 1 "GND" H 4000 2200 50  0000 C CNN
F 2 "" H 4000 2350 50  0000 C CNN
F 3 "" H 4000 2350 50  0000 C CNN
	1    4000 2350
	1    0    0    -1  
$EndComp
Text Notes 3650 1350 0    118  ~ 24
tube pre-amp\ngain: A=5
$Comp
L TL082 U2
U 1 1 57CBA6E8
P 4800 5800
F 0 "U2" H 4800 6000 50  0000 L CNN
F 1 "TL082" H 4800 5600 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm_LongPads" H 4800 5800 50  0001 C CNN
F 3 "" H 4800 5800 50  0000 C CNN
	1    4800 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 57CBAABA
P 4700 7000
F 0 "#PWR07" H 4700 6750 50  0001 C CNN
F 1 "GND" H 4700 6850 50  0000 C CNN
F 2 "" H 4700 7000 50  0000 C CNN
F 3 "" H 4700 7000 50  0000 C CNN
	1    4700 7000
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 57CBAE9B
P 4400 6450
F 0 "R9" V 4480 6450 50  0000 C CNN
F 1 "220R" V 4400 6450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4330 6450 50  0001 C CNN
F 3 "" H 4400 6450 50  0000 C CNN
	1    4400 6450
	-1   0    0    1   
$EndComp
$Comp
L R R13
U 1 1 57CBB160
P 4950 6300
F 0 "R13" V 5030 6300 50  0000 C CNN
F 1 "820R" V 4950 6300 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4880 6300 50  0001 C CNN
F 3 "" H 4950 6300 50  0000 C CNN
	1    4950 6300
	0    1    1    0   
$EndComp
$Comp
L CP C11
U 1 1 57CBB1E1
P 4400 6800
F 0 "C11" H 4425 6900 50  0000 L CNN
F 1 "220µF" H 4425 6700 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D10_L13_P5" H 4438 6650 50  0001 C CNN
F 3 "" H 4400 6800 50  0000 C CNN
	1    4400 6800
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 57CBB38E
P 4050 6800
F 0 "R8" V 4130 6800 50  0000 C CNN
F 1 "22k" V 4050 6800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3980 6800 50  0001 C CNN
F 3 "" H 4050 6800 50  0000 C CNN
	1    4050 6800
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 57CBB44F
P 4050 5350
F 0 "R7" V 4130 5350 50  0000 C CNN
F 1 "22k" V 4050 5350 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3980 5350 50  0001 C CNN
F 3 "" H 4050 5350 50  0000 C CNN
	1    4050 5350
	1    0    0    -1  
$EndComp
$Comp
L CP C8
U 1 1 57CBB940
P 3800 5700
F 0 "C8" H 3825 5800 50  0000 L CNN
F 1 "2.2µF" H 3825 5600 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L11_P2.5" H 3838 5550 50  0001 C CNN
F 3 "" H 3800 5700 50  0000 C CNN
	1    3800 5700
	0    1    1    0   
$EndComp
Text Notes 3600 4550 0    118  ~ 24
AOPAMP pre-amp\ngain: A=1+820/220=4.7
$Comp
L LM7815CT U3
U 1 1 57CBCB4B
P 8050 6650
F 0 "U3" H 7850 6850 50  0000 C CNN
F 1 "LM7815CT" H 8050 6850 50  0000 L CNN
F 2 "Power_Integrations:TO-220" H 8050 6750 50  0001 C CIN
F 3 "" H 8050 6650 50  0000 C CNN
	1    8050 6650
	-1   0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 57CBCD4B
P 8450 6900
F 0 "C16" H 8475 7000 50  0000 L CNN
F 1 "100nF" H 8475 6800 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 8488 6750 50  0001 C CNN
F 3 "" H 8450 6900 50  0000 C CNN
	1    8450 6900
	1    0    0    1   
$EndComp
$Comp
L GND #PWR08
U 1 1 57CBD07B
P 8050 7100
F 0 "#PWR08" H 8050 6850 50  0001 C CNN
F 1 "GND" H 8050 6950 50  0000 C CNN
F 2 "" H 8050 7100 50  0000 C CNN
F 3 "" H 8050 7100 50  0000 C CNN
	1    8050 7100
	-1   0    0    -1  
$EndComp
$Comp
L +15V #PWR09
U 1 1 57CBDD2A
P 4700 4900
F 0 "#PWR09" H 4700 4750 50  0001 C CNN
F 1 "+15V" H 4700 5040 50  0000 C CNN
F 2 "" H 4700 4900 50  0000 C CNN
F 3 "" H 4700 4900 50  0000 C CNN
	1    4700 4900
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR010
U 1 1 57CBE2AD
P 8450 6450
F 0 "#PWR010" H 8450 6300 50  0001 C CNN
F 1 "+24V" H 8450 6590 50  0000 C CNN
F 2 "" H 8450 6450 50  0000 C CNN
F 3 "" H 8450 6450 50  0000 C CNN
	1    8450 6450
	1    0    0    -1  
$EndComp
$Comp
L CP C15
U 1 1 57CC0DAC
P 7650 6900
F 0 "C15" H 7675 7000 50  0000 L CNN
F 1 "100µF" H 7675 6800 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D6.3_L11.2_P2.5" H 7688 6750 50  0001 C CNN
F 3 "" H 7650 6900 50  0000 C CNN
	1    7650 6900
	1    0    0    -1  
$EndComp
$Comp
L CK6418-RESCUE-amplifier U4
U 1 1 57CBEF3A
P 4650 2750
F 0 "U4" H 4900 3200 50  0000 C CNN
F 1 "CK6418" H 4970 3030 50  0000 C CNN
F 2 "special_symbols:VALVE-MINI_PENTODE_LINEAR" H 5170 2780 50  0001 C CNN
F 3 "" H 4650 2750 60  0001 C CNN
	1    4650 2750
	1    0    0    -1  
$EndComp
$Comp
L CK6418-RESCUE-amplifier U4
U 2 1 57CBF642
P 4650 2750
F 0 "U4" H 4900 3100 50  0000 C CNN
F 1 "CK6418" H 4970 3030 50  0000 C CNN
F 2 "special_symbols:VALVE-MINI_PENTODE_LINEAR" H 5170 2780 50  0001 C CNN
F 3 "" H 4650 2750 60  0001 C CNN
	2    4650 2750
	1    0    0    -1  
$EndComp
$Comp
L FRT5_separated K1
U 1 1 57D58008
P 1000 7450
F 0 "K1" H 1150 7575 50  0000 L CNN
F 1 "FRT5_separated" H 1150 7475 50  0000 L CNN
F 2 "special_symbols:Relay_DPDT_FRT5" H 1000 7450 50  0001 C CNN
F 3 "" H 1000 7450 50  0000 C CNN
	1    1000 7450
	1    0    0    -1  
$EndComp
$Comp
L FRT5_separated K1
U 2 1 57D58285
P 2950 4100
F 0 "K1" H 3100 4225 50  0000 L CNN
F 1 "FRT5_separated" H 3100 4125 50  0000 L CNN
F 2 "special_symbols:Relay_DPDT_FRT5" H 2950 4100 50  0001 C CNN
F 3 "" H 2950 4100 50  0000 C CNN
	2    2950 4100
	0    1    -1   0   
$EndComp
$Comp
L FRT5_separated K1
U 3 1 57D5832C
P 6400 4100
F 0 "K1" H 6550 4225 50  0000 L CNN
F 1 "FRT5_separated" H 6550 4125 50  0000 L CNN
F 2 "special_symbols:Relay_DPDT_FRT5" H 6400 4100 50  0001 C CNN
F 3 "" H 6400 4100 50  0000 C CNN
	3    6400 4100
	0    -1   -1   0   
$EndComp
$Comp
L BC548 Q1
U 1 1 57D5964C
P 1200 8150
F 0 "Q1" H 1400 8225 50  0000 L CNN
F 1 "BC548" H 1400 8150 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 1400 8075 50  0001 L CIN
F 3 "" H 1200 8150 50  0000 L CNN
	1    1200 8150
	0    -1   -1   0   
$EndComp
$Comp
L R R15
U 1 1 57D59DF5
P 1200 8600
F 0 "R15" V 1280 8600 50  0000 C CNN
F 1 "10k" V 1200 8600 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1130 8600 50  0001 C CNN
F 3 "" H 1200 8600 50  0000 C CNN
	1    1200 8600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 57D5A747
P 1450 8050
F 0 "#PWR011" H 1450 7800 50  0001 C CNN
F 1 "GND" H 1450 7900 50  0000 C CNN
F 2 "" H 1450 8050 50  0000 C CNN
F 3 "" H 1450 8050 50  0000 C CNN
	1    1450 8050
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR012
U 1 1 57D5A7B5
P 1000 7100
F 0 "#PWR012" H 1000 6950 50  0001 C CNN
F 1 "+5V" H 1000 7240 50  0000 C CNN
F 2 "" H 1000 7100 50  0000 C CNN
F 3 "" H 1000 7100 50  0000 C CNN
	1    1000 7100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR013
U 1 1 57D5BA04
P 7350 7500
F 0 "#PWR013" H 7350 7350 50  0001 C CNN
F 1 "+5V" H 7350 7640 50  0000 C CNN
F 2 "" H 7350 7500 50  0000 C CNN
F 3 "" H 7350 7500 50  0000 C CNN
	1    7350 7500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 57D5BA9C
P 7550 7950
F 0 "#PWR014" H 7550 7700 50  0001 C CNN
F 1 "GND" H 7550 7800 50  0000 C CNN
F 2 "" H 7550 7950 50  0000 C CNN
F 3 "" H 7550 7950 50  0000 C CNN
	1    7550 7950
	1    0    0    -1  
$EndComp
$Comp
L +15V #PWR015
U 1 1 57D64510
P 7150 6600
F 0 "#PWR015" H 7150 6450 50  0001 C CNN
F 1 "+15V" H 7150 6740 50  0000 C CNN
F 2 "" H 7150 6600 50  0000 C CNN
F 3 "" H 7150 6600 50  0000 C CNN
	1    7150 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4900 8050 4400
Wire Wire Line
	8050 4400 8150 4400
Wire Wire Line
	8700 4850 8050 4850
Connection ~ 8050 4850
Wire Wire Line
	9000 4850 9250 4850
Wire Wire Line
	9250 4250 9250 4900
Connection ~ 9250 4850
Connection ~ 9250 4250
Connection ~ 8850 3300
Connection ~ 8600 3300
Connection ~ 7650 5600
Connection ~ 8050 5600
Wire Wire Line
	9250 5300 9250 5200
Wire Wire Line
	7650 4650 7650 4100
Wire Wire Line
	7200 4100 8150 4100
Wire Wire Line
	7650 5300 7650 4950
Wire Wire Line
	8050 5200 8050 5300
Wire Wire Line
	7650 5150 7400 5150
Connection ~ 7400 5150
Connection ~ 7650 5150
Connection ~ 7650 4100
Wire Wire Line
	8600 4600 8600 5750
Connection ~ 8600 5600
Wire Wire Line
	8850 3700 8850 3600
Wire Wire Line
	8850 3650 9250 3650
Wire Wire Line
	9250 3650 9250 3600
Connection ~ 8850 3650
Wire Wire Line
	7400 3300 9250 3300
Connection ~ 9250 5600
Wire Wire Line
	7400 5600 9800 5600
Wire Wire Line
	9650 4250 10600 4250
Wire Wire Line
	9800 5600 9800 4450
Wire Notes Line
	6750 2350 6750 6000
Wire Notes Line
	6750 6000 10450 6000
Wire Notes Line
	10450 6000 10450 2350
Wire Notes Line
	10450 2350 6750 2350
Wire Wire Line
	9800 4450 10600 4450
Wire Wire Line
	9150 4250 9350 4250
Wire Wire Line
	8600 3150 8600 3900
Wire Wire Line
	7400 3600 7400 5300
Wire Wire Line
	4750 3300 4750 3150
Wire Wire Line
	4800 3200 4750 3200
Connection ~ 4750 3200
Wire Wire Line
	5100 3200 5150 3200
Connection ~ 5150 3200
Wire Wire Line
	5150 2250 5150 3300
Wire Wire Line
	4650 1950 4000 1950
Wire Wire Line
	4000 1950 4000 2000
Wire Wire Line
	4650 1950 4650 1850
Wire Wire Line
	5150 1950 5150 1550
Wire Wire Line
	5150 1550 4650 1550
Wire Wire Line
	4200 2800 4350 2800
Wire Wire Line
	4550 3150 4550 3700
Connection ~ 4750 3600
Wire Wire Line
	4650 1550 4650 1450
Connection ~ 4550 3600
Wire Wire Line
	4000 2350 4000 2300
Wire Wire Line
	4550 3600 5150 3600
Wire Notes Line
	3550 950  3550 4050
Wire Notes Line
	3550 4050 6000 4050
Wire Notes Line
	6000 4050 6000 950 
Wire Notes Line
	6000 950  3550 950 
Wire Wire Line
	4700 4900 4700 5500
Wire Wire Line
	4050 5200 4050 5000
Connection ~ 4700 5200
Wire Wire Line
	4050 5500 4050 6650
Wire Wire Line
	4050 6950 4700 6950
Wire Wire Line
	4700 6100 4700 7000
Connection ~ 4400 6950
Connection ~ 4700 6950
Wire Wire Line
	4800 6300 4400 6300
Wire Wire Line
	4500 5900 4400 5900
Wire Wire Line
	4400 5900 4400 6300
Wire Wire Line
	3950 5700 4500 5700
Connection ~ 4050 5700
Wire Wire Line
	4400 6600 4400 6650
Wire Wire Line
	5100 6300 5100 5800
Wire Wire Line
	8450 6450 8450 6750
Wire Wire Line
	7650 7050 8850 7050
Wire Wire Line
	8050 6900 8050 7100
Connection ~ 8050 7050
Wire Wire Line
	7650 6600 7650 6750
Connection ~ 4700 5000
Connection ~ 8450 6600
Wire Notes Line
	3550 4150 3550 7250
Wire Wire Line
	2400 4100 2650 4100
Wire Wire Line
	4650 2300 4650 2250
Wire Wire Line
	1000 8050 1000 7750
Wire Wire Line
	700  7450 700  7750
Wire Wire Line
	700  7750 1000 7750
Wire Wire Line
	700  7250 700  7150
Wire Wire Line
	700  7150 1000 7150
Wire Wire Line
	1200 8750 1200 9000
Wire Wire Line
	1000 7150 1000 7100
Wire Wire Line
	4950 2700 6100 2700
Wire Wire Line
	6700 4100 6900 4100
Connection ~ 7400 6600
Wire Wire Line
	4050 5000 4700 5000
Wire Wire Line
	7150 6600 7650 6600
Connection ~ 5600 5800
Wire Notes Line
	3550 4150 6000 4150
Wire Notes Line
	6000 4150 6000 7250
Wire Notes Line
	6000 7250 3550 7250
Wire Wire Line
	5100 5800 6100 5800
Wire Wire Line
	6100 5800 6100 4200
Wire Wire Line
	6100 2700 6100 4000
Connection ~ 5900 2700
Connection ~ 6850 4100
Wire Wire Line
	3250 4000 3250 2800
Wire Wire Line
	3250 2800 3900 2800
Connection ~ 3750 2800
Wire Wire Line
	3250 5700 3650 5700
Wire Wire Line
	3250 4200 3250 5700
Connection ~ 3600 5700
$Comp
L screw_terminal_2x01 K4
U 1 1 57D5EADB
P 8850 6700
F 0 "K4" H 8675 6825 60  0001 C CNN
F 1 "screw_terminal_2x01" H 9075 6900 60  0001 C CNN
F 2 "Connect:bornier2" H 8650 6600 60  0001 C CNN
F 3 "" H 8650 6600 60  0001 C CNN
	1    8850 6700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8850 7050 8850 6900
Connection ~ 8450 7050
Wire Wire Line
	8450 6600 8850 6600
Wire Wire Line
	8850 6600 8850 6700
Wire Notes Line
	7000 6250 10450 6250
Wire Notes Line
	10450 6250 10450 8850
Wire Notes Line
	7000 6250 7000 8850
Text Notes 7100 8650 0    118  ~ 24
power supply
Wire Wire Line
	7350 7550 7350 7500
$Comp
L BC548 Q4
U 1 1 57D64036
P 4000 15450
F 0 "Q4" H 4200 15525 50  0000 L CNN
F 1 "BC548" H 4200 15450 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 4200 15375 50  0001 L CIN
F 3 "" H 4000 15450 50  0000 L CNN
	1    4000 15450
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 57D64042
P 3550 15450
F 0 "R18" V 3630 15450 50  0000 C CNN
F 1 "10k" V 3550 15450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3480 15450 50  0001 C CNN
F 3 "" H 3550 15450 50  0000 C CNN
	1    3550 15450
	0    1    1    0   
$EndComp
$Comp
L GND #PWR016
U 1 1 57D64048
P 4100 15700
F 0 "#PWR016" H 4100 15450 50  0001 C CNN
F 1 "GND" H 4100 15550 50  0000 C CNN
F 2 "" H 4100 15700 50  0000 C CNN
F 3 "" H 4100 15700 50  0000 C CNN
	1    4100 15700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR017
U 1 1 57D6404E
P 5050 15250
F 0 "#PWR017" H 5050 15100 50  0001 C CNN
F 1 "+5V" H 5050 15390 50  0000 C CNN
F 2 "" H 5050 15250 50  0000 C CNN
F 3 "" H 5050 15250 50  0000 C CNN
	1    5050 15250
	0    1    1    0   
$EndComp
Wire Wire Line
	4100 15250 4400 15250
Wire Wire Line
	4400 14950 4700 14950
Wire Wire Line
	4400 15250 4400 14950
Wire Wire Line
	4900 14950 5000 14950
Wire Wire Line
	5000 14950 5000 15250
Wire Wire Line
	5000 15250 5050 15250
Wire Wire Line
	1200 8450 1200 8350
Wire Wire Line
	3700 15450 3800 15450
$Comp
L LM1875 U7
U 1 1 57D686ED
P 8600 10950
F 0 "U7" H 8800 11200 50  0000 C CNN
F 1 "LM1875" H 8800 11150 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:Pentawatt_Neutral_Staggered_Verical_TO220-5-T05D" H 8450 10950 50  0001 C CIN
F 3 "" H 8600 10950 50  0000 C CNN
	1    8600 10950
	1    0    0    -1  
$EndComp
$Comp
L CP C30
U 1 1 57D686F3
P 9500 10950
F 0 "C30" H 9525 11050 50  0000 L CNN
F 1 "4700µF" H 9525 10850 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D18_L36_P7.5" H 9538 10800 50  0001 C CNN
F 3 "" H 9500 10950 50  0000 C CNN
	1    9500 10950
	0    -1   -1   0   
$EndComp
$Comp
L CP C26
U 1 1 57D686F9
P 8050 12150
F 0 "C26" H 8075 12250 50  0000 L CNN
F 1 "10µF" H 8075 12050 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 8088 12000 50  0001 C CNN
F 3 "" H 8050 12150 50  0000 C CNN
	1    8050 12150
	1    0    0    -1  
$EndComp
$Comp
L CP C27
U 1 1 57D686FF
P 8850 10150
F 0 "C27" H 8875 10250 50  0000 L CNN
F 1 "100µF" H 8875 10050 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D10_L13_P5" H 8888 10000 50  0001 C CNN
F 3 "" H 8850 10150 50  0000 C CNN
	1    8850 10150
	1    0    0    -1  
$EndComp
$Comp
L CP C25
U 1 1 57D68705
P 7650 12150
F 0 "C25" H 7675 12250 50  0000 L CNN
F 1 "10µF" H 7675 12050 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 7688 12000 50  0001 C CNN
F 3 "" H 7650 12150 50  0000 C CNN
	1    7650 12150
	1    0    0    -1  
$EndComp
$Comp
L C C24
U 1 1 57D6870B
P 7050 10800
F 0 "C24" H 7075 10900 50  0000 L CNN
F 1 "100nF" H 7075 10700 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 7088 10650 50  0001 C CNN
F 3 "" H 7050 10800 50  0000 C CNN
	1    7050 10800
	0    1    1    0   
$EndComp
$Comp
L C C28
U 1 1 57D68711
P 9250 10150
F 0 "C28" H 9275 10250 50  0000 L CNN
F 1 "100nF" H 9275 10050 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 9288 10000 50  0001 C CNN
F 3 "" H 9250 10150 50  0000 C CNN
	1    9250 10150
	1    0    0    -1  
$EndComp
$Comp
L C C29
U 1 1 57D68717
P 9250 12150
F 0 "C29" H 9275 12250 50  0000 L CNN
F 1 "100nF" H 9275 12050 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 9288 12000 50  0001 C CNN
F 3 "" H 9250 12150 50  0000 C CNN
	1    9250 12150
	1    0    0    -1  
$EndComp
$Comp
L R R34
U 1 1 57D6871D
P 9250 11750
F 0 "R34" V 9330 11750 50  0000 C CNN
F 1 "2k2" V 9250 11750 50  0000 C CNN
F 2 "special_symbols:Resistor_Vertical_RM2.5mm" V 9180 11750 50  0001 C CNN
F 3 "" H 9250 11750 50  0000 C CNN
	1    9250 11750
	1    0    0    -1  
$EndComp
$Comp
L R R33
U 1 1 57D68723
P 8850 11550
F 0 "R33" V 8930 11550 50  0000 C CNN
F 1 "220k" V 8850 11550 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 8780 11550 50  0001 C CNN
F 3 "" H 8850 11550 50  0000 C CNN
	1    8850 11550
	0    1    1    0   
$EndComp
$Comp
L R R32
U 1 1 57D68729
P 8050 11750
F 0 "R32" V 8130 11750 50  0000 C CNN
F 1 "22k" V 8050 11750 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7980 11750 50  0001 C CNN
F 3 "" H 8050 11750 50  0000 C CNN
	1    8050 11750
	1    0    0    -1  
$EndComp
$Comp
L R R30
U 1 1 57D6872F
P 7400 12150
F 0 "R30" V 7480 12150 50  0000 C CNN
F 1 "2k2" V 7400 12150 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7330 12150 50  0001 C CNN
F 3 "" H 7400 12150 50  0000 C CNN
	1    7400 12150
	1    0    0    -1  
$EndComp
$Comp
L R R29
U 1 1 57D68735
P 7400 10150
F 0 "R29" V 7480 10150 50  0000 C CNN
F 1 "2k2" V 7400 10150 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7330 10150 50  0001 C CNN
F 3 "" H 7400 10150 50  0000 C CNN
	1    7400 10150
	1    0    0    -1  
$EndComp
$Comp
L R R31
U 1 1 57D6873B
P 7650 11500
F 0 "R31" V 7730 11500 50  0000 C CNN
F 1 "330k" V 7650 11500 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7580 11500 50  0001 C CNN
F 3 "" H 7650 11500 50  0000 C CNN
	1    7650 11500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 57D68741
P 8600 12450
F 0 "#PWR018" H 8600 12200 50  0001 C CNN
F 1 "GND" H 8600 12300 50  0000 C CNN
F 2 "" H 8600 12450 50  0000 C CNN
F 3 "" H 8600 12450 50  0000 C CNN
	1    8600 12450
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR019
U 1 1 57D68747
P 8600 9850
F 0 "#PWR019" H 8600 9700 50  0001 C CNN
F 1 "+24V" H 8600 9990 50  0000 C CNN
F 2 "" H 8600 9850 50  0000 C CNN
F 3 "" H 8600 9850 50  0000 C CNN
	1    8600 9850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 57D6874D
P 8850 10400
F 0 "#PWR020" H 8850 10150 50  0001 C CNN
F 1 "GND" H 8850 10250 50  0000 C CNN
F 2 "" H 8850 10400 50  0000 C CNN
F 3 "" H 8850 10400 50  0000 C CNN
	1    8850 10400
	1    0    0    -1  
$EndComp
$Comp
L SPEAKER SP2
U 1 1 57D68753
P 10900 11050
F 0 "SP2" H 10800 11300 50  0000 C CNN
F 1 "SPEAKER" H 10800 10800 50  0000 C CNN
F 2 "Connect:bornier2" H 10900 11050 50  0001 C CNN
F 3 "" H 10900 11050 50  0000 C CNN
	1    10900 11050
	1    0    0    -1  
$EndComp
Text Notes 6800 9450 0    118  ~ 24
main speaker amplifier\nA=1+220k/22k=11
$Comp
L C C19
U 1 1 57D6875A
P 4050 9500
F 0 "C19" H 4075 9600 50  0000 L CNN
F 1 "68nF" H 4075 9400 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 4088 9350 50  0001 C CNN
F 3 "" H 4050 9500 50  0000 C CNN
	1    4050 9500
	0    1    1    0   
$EndComp
$Comp
L CP C21
U 1 1 57D68760
P 4750 10150
F 0 "C21" H 4775 10250 50  0000 L CNN
F 1 "10µF" H 4775 10050 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 4788 10000 50  0001 C CNN
F 3 "" H 4750 10150 50  0000 C CNN
	1    4750 10150
	1    0    0    -1  
$EndComp
$Comp
L CP C18
U 1 1 57D68766
P 4000 8850
F 0 "C18" H 4025 8950 50  0000 L CNN
F 1 "10µF" H 4025 8750 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 4038 8700 50  0001 C CNN
F 3 "" H 4000 8850 50  0000 C CNN
	1    4000 8850
	1    0    0    -1  
$EndComp
$Comp
L R R25
U 1 1 57D6876C
P 4650 8800
F 0 "R25" V 4730 8800 50  0000 C CNN
F 1 "47k" V 4650 8800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4580 8800 50  0001 C CNN
F 3 "" H 4650 8800 50  0000 C CNN
	1    4650 8800
	1    0    0    -1  
$EndComp
$Comp
L R R24
U 1 1 57D68772
P 4650 8400
F 0 "R24" V 4730 8400 50  0000 C CNN
F 1 "8k2" V 4650 8400 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4580 8400 50  0001 C CNN
F 3 "" H 4650 8400 50  0000 C CNN
	1    4650 8400
	1    0    0    -1  
$EndComp
$Comp
L R R26
U 1 1 57D68778
P 4950 9900
F 0 "R26" V 5030 9900 50  0000 C CNN
F 1 "1k2" V 4950 9900 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4880 9900 50  0001 C CNN
F 3 "" H 4950 9900 50  0000 C CNN
	1    4950 9900
	0    1    1    0   
$EndComp
$Comp
L R R28
U 1 1 57D6877E
P 5150 8800
F 0 "R28" V 5230 8800 50  0000 C CNN
F 1 "1k2" V 5150 8800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5080 8800 50  0001 C CNN
F 3 "" H 5150 8800 50  0000 C CNN
	1    5150 8800
	1    0    0    -1  
$EndComp
$Comp
L CP C23
U 1 1 57D68784
P 5150 10150
F 0 "C23" H 5175 10250 50  0000 L CNN
F 1 "10µF" H 5175 10050 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 5188 10000 50  0001 C CNN
F 3 "" H 5150 10150 50  0000 C CNN
	1    5150 10150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 57D6878A
P 4550 10400
F 0 "#PWR021" H 4550 10150 50  0001 C CNN
F 1 "GND" H 4550 10250 50  0000 C CNN
F 2 "" H 4550 10400 50  0000 C CNN
F 3 "" H 4550 10400 50  0000 C CNN
	1    4550 10400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 57D68796
P 4000 9050
F 0 "#PWR022" H 4000 8800 50  0001 C CNN
F 1 "GND" H 4000 8900 50  0000 C CNN
F 2 "" H 4000 9050 50  0000 C CNN
F 3 "" H 4000 9050 50  0000 C CNN
	1    4000 9050
	1    0    0    -1  
$EndComp
Text Notes 3650 8050 0    118  ~ 24
tube pre-amp\ngain: A=5
$Comp
L TL082 U2
U 2 1 57D6879D
P 4800 12500
F 0 "U2" H 4800 12700 50  0000 L CNN
F 1 "TL082" H 4800 12300 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm_LongPads" H 4800 12500 50  0001 C CNN
F 3 "" H 4800 12500 50  0000 C CNN
	2    4800 12500
	1    0    0    -1  
$EndComp
$Comp
L C C22
U 1 1 57D687A3
P 4950 11900
F 0 "C22" H 4975 12000 50  0000 L CNN
F 1 "100nF" H 4975 11800 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 4988 11750 50  0001 C CNN
F 3 "" H 4950 11900 50  0000 C CNN
	1    4950 11900
	0    1    1    0   
$EndComp
$Comp
L GND #PWR023
U 1 1 57D687A9
P 4700 13700
F 0 "#PWR023" H 4700 13450 50  0001 C CNN
F 1 "GND" H 4700 13550 50  0000 C CNN
F 2 "" H 4700 13700 50  0000 C CNN
F 3 "" H 4700 13700 50  0000 C CNN
	1    4700 13700
	1    0    0    -1  
$EndComp
$Comp
L R R23
U 1 1 57D687AF
P 4400 13150
F 0 "R23" V 4480 13150 50  0000 C CNN
F 1 "220R" V 4400 13150 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4330 13150 50  0001 C CNN
F 3 "" H 4400 13150 50  0000 C CNN
	1    4400 13150
	-1   0    0    1   
$EndComp
$Comp
L R R27
U 1 1 57D687B5
P 4950 13000
F 0 "R27" V 5030 13000 50  0000 C CNN
F 1 "820R" V 4950 13000 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4880 13000 50  0001 C CNN
F 3 "" H 4950 13000 50  0000 C CNN
	1    4950 13000
	0    1    1    0   
$EndComp
$Comp
L CP C20
U 1 1 57D687BB
P 4400 13500
F 0 "C20" H 4425 13600 50  0000 L CNN
F 1 "220µF" H 4425 13400 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D10_L13_P5" H 4438 13350 50  0001 C CNN
F 3 "" H 4400 13500 50  0000 C CNN
	1    4400 13500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 57D687C1
P 5200 11900
F 0 "#PWR024" H 5200 11650 50  0001 C CNN
F 1 "GND" H 5200 11750 50  0000 C CNN
F 2 "" H 5200 11900 50  0000 C CNN
F 3 "" H 5200 11900 50  0000 C CNN
	1    5200 11900
	0    -1   -1   0   
$EndComp
$Comp
L R R22
U 1 1 57D687C7
P 4050 13500
F 0 "R22" V 4130 13500 50  0000 C CNN
F 1 "22k" V 4050 13500 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3980 13500 50  0001 C CNN
F 3 "" H 4050 13500 50  0000 C CNN
	1    4050 13500
	1    0    0    -1  
$EndComp
$Comp
L R R21
U 1 1 57D687CD
P 4050 12050
F 0 "R21" V 4130 12050 50  0000 C CNN
F 1 "22k" V 4050 12050 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3980 12050 50  0001 C CNN
F 3 "" H 4050 12050 50  0000 C CNN
	1    4050 12050
	1    0    0    -1  
$EndComp
$Comp
L CP C17
U 1 1 57D687D3
P 3800 12400
F 0 "C17" H 3825 12500 50  0000 L CNN
F 1 "2.2µF" H 3825 12300 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L11_P2.5" H 3838 12250 50  0001 C CNN
F 3 "" H 3800 12400 50  0000 C CNN
	1    3800 12400
	0    1    1    0   
$EndComp
Text Notes 3600 11250 0    118  ~ 24
AOPAMP pre-amp\ngain: A=1+820/220=4.7
$Comp
L +15V #PWR025
U 1 1 57D687EC
P 4700 11600
F 0 "#PWR025" H 4700 11450 50  0001 C CNN
F 1 "+15V" H 4700 11740 50  0000 C CNN
F 2 "" H 4700 11600 50  0000 C CNN
F 3 "" H 4700 11600 50  0000 C CNN
	1    4700 11600
	1    0    0    -1  
$EndComp
$Comp
L CK6418-RESCUE-amplifier U6
U 1 1 57D687FE
P 4650 9450
F 0 "U6" H 4900 9900 50  0000 C CNN
F 1 "CK6418" H 4970 9730 50  0000 C CNN
F 2 "special_symbols:VALVE-MINI_PENTODE_LINEAR" H 5170 9480 50  0001 C CNN
F 3 "" H 4650 9450 60  0001 C CNN
	1    4650 9450
	1    0    0    -1  
$EndComp
$Comp
L CK6418-RESCUE-amplifier U6
U 2 1 57D68804
P 4650 9450
F 0 "U6" H 4900 9800 50  0000 C CNN
F 1 "CK6418" H 4970 9730 50  0000 C CNN
F 2 "special_symbols:VALVE-MINI_PENTODE_LINEAR" H 5170 9480 50  0001 C CNN
F 3 "" H 4650 9450 60  0001 C CNN
	2    4650 9450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 11600 8050 11100
Wire Wire Line
	8050 11100 8150 11100
Wire Wire Line
	8700 11550 8050 11550
Connection ~ 8050 11550
Wire Wire Line
	9000 11550 9250 11550
Wire Wire Line
	9250 10950 9250 11600
Connection ~ 9250 11550
Connection ~ 9250 10950
Connection ~ 8850 10000
Connection ~ 8600 10000
Connection ~ 7650 12300
Connection ~ 8050 12300
Wire Wire Line
	9250 12000 9250 11900
Wire Wire Line
	7650 11350 7650 10800
Wire Wire Line
	7200 10800 8150 10800
Wire Wire Line
	7650 12000 7650 11650
Wire Wire Line
	8050 11900 8050 12000
Wire Wire Line
	7650 11850 7400 11850
Connection ~ 7400 11850
Connection ~ 7650 11850
Connection ~ 7650 10800
Wire Wire Line
	8600 11300 8600 12450
Connection ~ 8600 12300
Wire Wire Line
	8850 10400 8850 10300
Wire Wire Line
	8850 10350 9250 10350
Wire Wire Line
	9250 10350 9250 10300
Connection ~ 8850 10350
Wire Wire Line
	7400 10000 9250 10000
Connection ~ 9250 12300
Wire Wire Line
	7400 12300 9800 12300
Wire Wire Line
	9650 10950 10600 10950
Wire Wire Line
	9800 12300 9800 11150
Wire Notes Line
	6750 9050 6750 12700
Wire Notes Line
	6750 12700 10450 12700
Wire Notes Line
	10450 12700 10450 9050
Wire Notes Line
	10450 9050 6750 9050
Wire Wire Line
	9800 11150 10600 11150
Wire Wire Line
	9150 10950 9350 10950
Wire Wire Line
	8600 9850 8600 10600
Wire Wire Line
	7400 10300 7400 12000
Wire Wire Line
	4750 10000 4750 9850
Wire Wire Line
	4800 9900 4750 9900
Connection ~ 4750 9900
Wire Wire Line
	5100 9900 5150 9900
Connection ~ 5150 9900
Wire Wire Line
	5150 8950 5150 10000
Wire Wire Line
	4650 8650 4000 8650
Wire Wire Line
	4000 8650 4000 8700
Wire Wire Line
	4650 8650 4650 8550
Wire Wire Line
	5150 8650 5150 8250
Wire Wire Line
	5150 8250 4650 8250
Wire Wire Line
	4200 9500 4350 9500
Wire Wire Line
	4550 9850 4550 10400
Connection ~ 4750 10300
Wire Wire Line
	4650 8250 4650 8150
Connection ~ 4550 10300
Wire Wire Line
	4000 9050 4000 9000
Wire Wire Line
	4550 10300 5150 10300
Wire Notes Line
	3550 7650 3550 10750
Wire Notes Line
	3550 10750 6000 10750
Wire Notes Line
	6000 10750 6000 7650
Wire Notes Line
	6000 7650 3550 7650
Wire Wire Line
	4700 11600 4700 12200
Wire Wire Line
	4700 11900 4800 11900
Wire Wire Line
	5100 11900 5200 11900
Wire Wire Line
	4050 11900 4050 11700
Connection ~ 4700 11900
Wire Wire Line
	4050 12200 4050 13350
Wire Wire Line
	4050 13650 4700 13650
Wire Wire Line
	4700 12800 4700 13700
Connection ~ 4400 13650
Connection ~ 4700 13650
Wire Wire Line
	4800 13000 4400 13000
Wire Wire Line
	4500 12600 4400 12600
Wire Wire Line
	4400 12600 4400 13000
Wire Wire Line
	3950 12400 4500 12400
Connection ~ 4050 12400
Wire Wire Line
	4400 13300 4400 13350
Wire Wire Line
	5100 13000 5100 12500
Connection ~ 4700 11700
Wire Notes Line
	3550 10850 3550 13950
Wire Wire Line
	4650 9000 4650 8950
Wire Wire Line
	4950 9400 6100 9400
Wire Wire Line
	6700 10800 6900 10800
Wire Wire Line
	4050 11700 4700 11700
Connection ~ 5600 12500
Wire Notes Line
	3550 10850 6000 10850
Wire Notes Line
	6000 10850 6000 13950
Wire Notes Line
	6000 13950 3550 13950
Wire Wire Line
	5100 12500 6100 12500
Wire Wire Line
	6100 12500 6100 10900
Wire Wire Line
	6100 9400 6100 10700
Connection ~ 5900 9400
Connection ~ 6850 10800
Wire Wire Line
	3250 10700 3250 9500
Wire Wire Line
	3250 9500 3900 9500
Connection ~ 3750 9500
Wire Wire Line
	3250 12400 3650 12400
Wire Wire Line
	3250 10900 3250 12400
Connection ~ 3600 12400
$Comp
L FRT5_separated K2
U 2 1 57D6BA68
P 2950 10800
F 0 "K2" H 3100 10925 50  0000 L CNN
F 1 "FRT5_separated" H 3100 10825 50  0000 L CNN
F 2 "special_symbols:Relay_DPDT_FRT5" H 2950 10800 50  0001 C CNN
F 3 "" H 2950 10800 50  0000 C CNN
	2    2950 10800
	0    1    -1   0   
$EndComp
$Comp
L FRT5_separated K2
U 1 1 57D6C8BF
P 4700 15250
F 0 "K2" H 4850 15375 50  0000 L CNN
F 1 "FRT5_separated" H 4850 15275 50  0000 L CNN
F 2 "special_symbols:Relay_DPDT_FRT5" H 4700 15250 50  0001 C CNN
F 3 "" H 4700 15250 50  0000 C CNN
	1    4700 15250
	0    1    1    0   
$EndComp
$Comp
L FRT5_separated K2
U 3 1 57D6CEC1
P 6400 10800
F 0 "K2" H 6550 10925 50  0000 L CNN
F 1 "FRT5_separated" H 6550 10825 50  0000 L CNN
F 2 "special_symbols:Relay_DPDT_FRT5" H 6400 10800 50  0001 C CNN
F 3 "" H 6400 10800 50  0000 C CNN
	3    6400 10800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1750 10800 2650 10800
Wire Notes Line
	4700 15100 4700 14100
Wire Notes Line
	2950 14100 6400 14100
Wire Notes Line
	2950 14100 2950 10850
Wire Notes Line
	6400 14100 6400 10850
Wire Notes Line
	1100 7450 6400 7450
Wire Notes Line
	6400 7450 6400 4150
Wire Notes Line
	2950 4150 2950 7450
$Comp
L VCC #PWR026
U 1 1 57D7F896
P 7550 7500
F 0 "#PWR026" H 7550 7350 50  0001 C CNN
F 1 "VCC" H 7550 7650 50  0000 C CNN
F 2 "" H 7550 7500 50  0000 C CNN
F 3 "" H 7550 7500 50  0000 C CNN
	1    7550 7500
	1    0    0    -1  
$EndComp
$Comp
L VPP #PWR027
U 1 1 57D84AD5
P 4650 8150
F 0 "#PWR027" H 4650 8000 50  0001 C CNN
F 1 "VPP" H 4650 8300 50  0000 C CNN
F 2 "" H 4650 8150 50  0000 C CNN
F 3 "" H 4650 8150 50  0000 C CNN
	1    4650 8150
	1    0    0    -1  
$EndComp
$Comp
L VPP #PWR028
U 1 1 57D85BD0
P 4650 1450
F 0 "#PWR028" H 4650 1300 50  0001 C CNN
F 1 "VPP" H 4650 1600 50  0000 C CNN
F 2 "" H 4650 1450 50  0000 C CNN
F 3 "" H 4650 1450 50  0000 C CNN
	1    4650 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 15650 4100 15700
Wire Wire Line
	1400 8050 1450 8050
$Comp
L BC548 Q5
U 1 1 57D8B0A4
P 8950 8300
F 0 "Q5" H 9150 8375 50  0000 L CNN
F 1 "BC548" H 9150 8300 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 9150 8225 50  0001 L CIN
F 3 "" H 8950 8300 50  0000 L CNN
	1    8950 8300
	1    0    0    -1  
$EndComp
$Comp
L R R35
U 1 1 57D8B0B0
P 8500 8300
F 0 "R35" V 8580 8300 50  0000 C CNN
F 1 "10k" V 8500 8300 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 8430 8300 50  0001 C CNN
F 3 "" H 8500 8300 50  0000 C CNN
	1    8500 8300
	0    1    1    0   
$EndComp
$Comp
L GND #PWR029
U 1 1 57D8B0B6
P 9050 8550
F 0 "#PWR029" H 9050 8300 50  0001 C CNN
F 1 "GND" H 9050 8400 50  0000 C CNN
F 2 "" H 9050 8550 50  0000 C CNN
F 3 "" H 9050 8550 50  0000 C CNN
	1    9050 8550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR030
U 1 1 57D8B0BC
P 10000 8100
F 0 "#PWR030" H 10000 7950 50  0001 C CNN
F 1 "+5V" H 10000 8240 50  0000 C CNN
F 2 "" H 10000 8100 50  0000 C CNN
F 3 "" H 10000 8100 50  0000 C CNN
	1    10000 8100
	0    1    1    0   
$EndComp
Wire Wire Line
	9050 8100 9350 8100
Wire Wire Line
	9350 7800 9650 7800
Wire Wire Line
	9350 8100 9350 7800
Wire Wire Line
	9850 7800 9950 7800
Wire Wire Line
	9950 7800 9950 8100
Wire Wire Line
	6950 8300 8350 8300
Wire Wire Line
	9950 8100 10000 8100
Wire Wire Line
	8650 8300 8750 8300
Wire Wire Line
	9050 8500 9050 8550
$Comp
L TIANBO-HJR-4102-L RL1
U 1 1 57D8B2A5
P 9650 8300
F 0 "RL1" H 10100 8450 50  0000 L CNN
F 1 "TIANBO-HJR-4102-L" H 10100 8350 50  0000 L CNN
F 2 "special_symbols:Relay_SPDT_HJR-4102" H 9650 8300 50  0001 C CNN
F 3 "" H 9650 8300 50  0000 C CNN
	1    9650 8300
	0    1    1    0   
$EndComp
$Comp
L +24V #PWR031
U 1 1 57D8F59B
P 9300 8650
F 0 "#PWR031" H 9300 8500 50  0001 C CNN
F 1 "+24V" H 9300 8790 50  0000 C CNN
F 2 "" H 9300 8650 50  0000 C CNN
F 3 "" H 9300 8650 50  0000 C CNN
	1    9300 8650
	-1   0    0    1   
$EndComp
Wire Wire Line
	9300 8650 9300 8500
Wire Wire Line
	9300 8500 9350 8500
$Comp
L VPP #PWR032
U 1 1 57D8FD9B
P 10200 8600
F 0 "#PWR032" H 10200 8450 50  0001 C CNN
F 1 "VPP" H 10200 8750 50  0000 C CNN
F 2 "" H 10200 8600 50  0000 C CNN
F 3 "" H 10200 8600 50  0000 C CNN
	1    10200 8600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 8600 9950 8600
Wire Notes Line
	7000 8850 10450 8850
$Comp
L CONN_02X01 P1
U 1 1 57D9301E
P 6700 8300
F 0 "P1" H 6700 8400 50  0000 C CNN
F 1 "CONN_02X01" H 6700 8200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x01" H 6700 7100 50  0001 C CNN
F 3 "" H 6700 7100 50  0000 C CNN
	1    6700 8300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 3750 2400 3750
Wire Wire Line
	2400 3750 2400 4100
Wire Wire Line
	1750 4150 1750 10800
$Comp
L D_Small D1
U 1 1 57DB8D80
P 700 7350
F 0 "D1" H 650 7430 50  0000 L CNN
F 1 "1N4148" H 550 7270 50  0000 L CNN
F 2 "Diodes_ThroughHole:Diode_DO-35_SOD27_Horizontal_RM10" V 700 7350 50  0001 C CNN
F 3 "" V 700 7350 50  0000 C CNN
	1    700  7350
	0    1    1    0   
$EndComp
$Comp
L D_Small D4
U 1 1 57DBCB14
P 4800 14950
F 0 "D4" H 4750 15030 50  0000 L CNN
F 1 "1N4148" H 4650 14870 50  0000 L CNN
F 2 "Diodes_ThroughHole:Diode_DO-35_SOD27_Horizontal_RM10" V 4800 14950 50  0001 C CNN
F 3 "" V 4800 14950 50  0000 C CNN
	1    4800 14950
	-1   0    0    1   
$EndComp
$Comp
L D_Small D5
U 1 1 57DBE29E
P 9750 7800
F 0 "D5" H 9700 7880 50  0000 L CNN
F 1 "1N4148" H 9600 7720 50  0000 L CNN
F 2 "Diodes_ThroughHole:Diode_DO-35_SOD27_Horizontal_RM10" V 9750 7800 50  0001 C CNN
F 3 "" V 9750 7800 50  0000 C CNN
	1    9750 7800
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 4150 1750 4150
Wire Wire Line
	1400 3950 1900 3950
$Comp
L CONN_01X03 P5
U 1 1 57DE8D79
P 1200 3950
F 0 "P5" H 1200 4150 50  0000 C CNN
F 1 "CONN_01X03" V 1300 3950 50  0000 C CNN
F 2 "Connect:bornier3" H 1200 3950 50  0001 C CNN
F 3 "" H 1200 3950 50  0000 C CNN
	1    1200 3950
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 3750 1400 3850
Wire Wire Line
	1400 4050 1400 4150
NoConn ~ 9950 8400
Connection ~ 4650 1550
Connection ~ 4650 1950
Connection ~ 4650 8250
Connection ~ 4650 8650
Text GLabel 6450 8150 1    60   Input ~ 0
RELAIS
Wire Wire Line
	6450 8150 6450 8300
$Comp
L CONN_02X01 P2
U 1 1 57E00D36
P 1200 9250
F 0 "P2" H 1200 9350 50  0000 C CNN
F 1 "CONN_02X01" H 1200 9150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x01" H 1200 8050 50  0001 C CNN
F 3 "" H 1200 8050 50  0000 C CNN
	1    1200 9250
	0    1    1    0   
$EndComp
Text GLabel 1200 9650 3    60   Input ~ 0
RELAIS
Wire Wire Line
	1200 9650 1200 9500
$Comp
L CONN_02X01 P4
U 1 1 57E0250E
P 3050 15450
F 0 "P4" H 3050 15550 50  0000 C CNN
F 1 "CONN_02X01" H 3050 15350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x01" H 3050 14250 50  0001 C CNN
F 3 "" H 3050 14250 50  0000 C CNN
	1    3050 15450
	-1   0    0    1   
$EndComp
Text GLabel 2700 15450 0    60   Input ~ 0
RELAIS
Wire Wire Line
	2700 15450 2800 15450
Wire Wire Line
	3300 15450 3400 15450
Text GLabel 1150 14750 0    60   Input ~ 0
RELAIS
$Comp
L CONN_02X01 P3
U 1 1 57E03A18
P 1550 14950
F 0 "P3" H 1550 15050 50  0000 C CNN
F 1 "CONN_02X01" H 1550 14850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x01" H 1550 13750 50  0001 C CNN
F 3 "" H 1550 13750 50  0000 C CNN
	1    1550 14950
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 14750 1800 14750
Wire Wire Line
	1800 14750 1800 14950
Wire Wire Line
	1300 14950 1300 14750
Connection ~ 1300 14750
$Comp
L LM7805CT U5
U 1 1 57E0621E
P 8050 7600
F 0 "U5" H 7850 7800 50  0000 C CNN
F 1 "LM7805CT" H 8050 7800 50  0000 L CNN
F 2 "Power_Integrations:TO-220" H 8050 7700 50  0000 C CIN
F 3 "" H 8050 7600 50  0000 C CNN
	1    8050 7600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7650 7550 7350 7550
Wire Wire Line
	7550 7500 7550 7600
Connection ~ 7550 7550
$Comp
L C C31
U 1 1 57E06EED
P 8450 7800
F 0 "C31" H 8475 7900 50  0000 L CNN
F 1 "100nF" H 8475 7700 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 8488 7650 50  0001 C CNN
F 3 "" H 8450 7800 50  0000 C CNN
	1    8450 7800
	1    0    0    1   
$EndComp
Wire Wire Line
	8450 7950 7550 7950
Wire Wire Line
	7550 7950 7550 7900
Wire Wire Line
	8050 7850 8050 7950
Connection ~ 8050 7950
Wire Wire Line
	8450 7550 8450 7650
Wire Wire Line
	8450 7550 8700 7550
Wire Wire Line
	8700 7550 8700 6600
Connection ~ 8700 6600
Connection ~ 8450 7550
Connection ~ 7550 7950
$Comp
L CP C13
U 1 1 57E07903
P 7550 7750
F 0 "C13" H 7575 7850 50  0000 L CNN
F 1 "100µF" H 7575 7650 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D6.3_L11.2_P2.5" H 7588 7600 50  0001 C CNN
F 3 "" H 7550 7750 50  0000 C CNN
	1    7550 7750
	1    0    0    -1  
$EndComp
$Sheet
S 8950 1600 1350 500 
U 57E0958C
F0 "power_supply_24V" 60
F1 "power_supply_24V.sch" 60
$EndSheet
$EndSCHEMATC

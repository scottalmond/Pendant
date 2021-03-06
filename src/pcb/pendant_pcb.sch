EESchema Schematic File Version 2
LIBS:pendant_pcb-rescue
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
LIBS:JS102011SAQN
LIBS:S2B-PH-SM4-TB_LF__SN_
LIBS:2019-03-28_23-53-15
LIBS:2019-03-28_23-58-03
LIBS:SamacSys_Parts
LIBS:M20-7810445
LIBS:10118193-0001LF
LIBS:sk6812
LIBS:2019-03-30_02-10-41
LIBS:pendant_pcb-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "P3 Pendant"
Date "2019-03-28"
Rev "v1.1"
Comp ""
Comment1 ""
Comment2 "www.creativecommons.org/licenses/by/4.0/"
Comment3 "License: CC BY 4.0"
Comment4 "Author: Scott Almond"
$EndDescr
$Comp
L ATTINY85-S IC1
U 1 1 5C9D293B
P 6300 5400
F 0 "IC1" H 5150 5800 50  0000 C CNN
F 1 "ATTINY85-S" H 7300 5000 50  0000 C CNN
F 2 "attiny:ATTINY85-20SU" H 7250 5400 50  0000 C CIN
F 3 "" H 6300 5400 50  0000 C CNN
	1    6300 5400
	1    0    0    -1  
$EndComp
$Comp
L JS102011SAQN S2
U 1 1 5C9D5075
P 8700 2200
F 0 "S2" H 8400 2400 50  0000 L BNN
F 1 "JS102011SAQN" H 8400 2000 50  0000 L BNN
F 2 "JS102011SAQN:SW_JS102011SAQN" H 8700 2200 50  0001 L BNN
F 3 "C&K" H 8700 2200 50  0001 L BNN
F 4 "JS10 Series SPDT On-On 6 V 0.3 A Gull Wing SMT Slide Switch" H 8700 2200 50  0001 L BNN "Field4"
F 5 "https://www.digikey.com/product-detail/en/c-k/JS102011SAQN/401-1999-1-ND/1640114?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 8700 2200 50  0001 L BNN "Field5"
F 6 "JS102011SAQN" H 8700 2200 50  0001 L BNN "Field6"
F 7 "None" H 8700 2200 50  0001 L BNN "Field7"
F 8 "401-1999-1-ND" H 8700 2200 50  0001 L BNN "Field8"
	1    8700 2200
	1    0    0    -1  
$EndComp
$Comp
L S2B-PH-SM4-TB(LF)(SN) J2
U 1 1 5C9D510D
P 1550 3700
F 0 "J2" H 1350 3920 50  0000 L BNN
F 1 "S2B-PH-SM4-TB(LF)(SN)" H 1350 3329 50  0000 L BNN
F 2 "S2B-PH-SM4-TB_LF__SN_:JST_S2B-PH-SM4-TB(LF)(SN)" H 1550 3700 50  0001 L BNN
F 3 "JST Sales" H 1550 3700 50  0001 L BNN
F 4 "455-1749-1-ND" H 1550 3700 50  0001 L BNN "Field4"
F 5 "PH Series 2 Position 2 mm Pitch Surface Mount Side Entry Shrouded Header" H 1550 3700 50  0001 L BNN "Field5"
F 6 "None" H 1550 3700 50  0001 L BNN "Field6"
F 7 "S2B-PH-SM4-TB_LF__SN_" H 1550 3700 50  0001 L BNN "Field7"
F 8 "https://www.digikey.com/product-detail/en/jst-sales-america-inc/S2B-PH-SM4-TB_LF__SN_/455-1749-1-ND/926846?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 1550 3700 50  0001 L BNN "Field8"
	1    1550 3700
	-1   0    0    -1  
$EndComp
$Comp
L S2B-PH-SM4-TB(LF)(SN) J4
U 1 1 5C9D5196
P 8800 1100
F 0 "J4" H 8600 1320 50  0000 L BNN
F 1 "S2B-PH-SM4-TB(LF)(SN)" H 8600 729 50  0000 L BNN
F 2 "S2B-PH-SM4-TB_LF__SN_:JST_S2B-PH-SM4-TB(LF)(SN)" H 8800 1100 50  0001 L BNN
F 3 "JST Sales" H 8800 1100 50  0001 L BNN
F 4 "455-1749-1-ND" H 8800 1100 50  0001 L BNN "Field4"
F 5 "PH Series 2 Position 2 mm Pitch Surface Mount Side Entry Shrouded Header" H 8800 1100 50  0001 L BNN "Field5"
F 6 "None" H 8800 1100 50  0001 L BNN "Field6"
F 7 "S2B-PH-SM4-TB_LF__SN_" H 8800 1100 50  0001 L BNN "Field7"
F 8 "https://www.digikey.com/product-detail/en/jst-sales-america-inc/S2B-PH-SM4-TB_LF__SN_/455-1749-1-ND/926846?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 8800 1100 50  0001 L BNN "Field8"
	1    8800 1100
	1    0    0    -1  
$EndComp
$Comp
L TPA6211A1DGNR U4
U 1 1 5C9D5F6E
P 6200 4000
F 0 "U4" H 7600 4400 60  0000 C CNN
F 1 "TPA6211A1DGNR" H 7600 4300 60  0000 C CNN
F 2 "tpa:TPA6211A1DGNR" H 7600 4240 60  0001 C CNN
F 3 "" H 6200 4000 60  0000 C CNN
	1    6200 4000
	-1   0    0    1   
$EndComp
$Comp
L MCP73831T-2ACI/OT U3
U 1 1 5C9D6099
P 3600 1600
F 0 "U3" H 4800 2000 60  0000 C CNN
F 1 "MCP73832T-2ACI/OT" H 4800 1900 60  0000 C CNN
F 2 "mcp:MCP73831T-2ACI&slash_OT" H 4800 1840 60  0001 C CNN
F 3 "" H 3600 1600 60  0000 C CNN
	1    3600 1600
	1    0    0    -1  
$EndComp
Text Notes 9050 1050 0    60   ~ 0
Pin 1 VCC\nPin 2 GND
$Comp
L M20-7810445 J3
U 1 1 5C9D846A
P 3200 6800
F 0 "J3" H 3850 7100 50  0000 L CNN
F 1 "M20-7810445" H 3850 7000 50  0000 L CNN
F 2 "M20-7810445:M207810445" H 3850 6900 50  0001 L CNN
F 3 "https://componentsearchengine.com/Datasheets/1/M20-7810445.pdf" H 3850 6800 50  0001 L CNN
F 4 "Headers & Wire Housings 4+4 DIL 2.54MM L/P SMT SKT" H 3850 6700 50  0001 L CNN "Description"
F 5 "3.7" H 3850 6600 50  0001 L CNN "Height"
F 6 "855-M20-7810445" H 3850 6500 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.com/Search/Refine.aspx?Keyword=855-M20-7810445" H 3850 6400 50  0001 L CNN "Mouser Price/Stock"
F 8 "HARWIN" H 3850 6300 50  0001 L CNN "Manufacturer_Name"
F 9 "M20-7810445" H 3850 6200 50  0001 L CNN "Manufacturer_Part_Number"
	1    3200 6800
	1    0    0    -1  
$EndComp
Text Notes 3150 6400 0    60   ~ 0
Programming Header
Text Notes 8600 750  0    60   ~ 0
LiPo Header
Text Notes 8400 1900 0    60   ~ 0
Power Switch
Text Notes 4350 1100 0    60   ~ 0
USB to LiPo Charger
Text Notes 4500 3350 0    60   ~ 0
Audio Amplifier
Text Notes 700  1150 0    60   ~ 0
Micro USB Charging Header
$Comp
L 10118193-0001LF J1
U 1 1 5C9D99D4
P 1250 1650
F 0 "J1" H 1050 2080 50  0000 L BNN
F 1 "10118193-0001LF" H 850 1250 50  0000 L BNN
F 2 "Misc:FCI_10118193-0001LF" H 1250 1650 50  0001 L BNN
F 3 "Conn Micro USB Type B RCP 5 POS 0.65mm Solder RA SMD 5 Terminal 1 Port T/R" H 1250 1650 50  0001 L BNN
F 4 "https://www.digikey.com/product-detail/en/amphenol-icc-fci/10118193-0001LF/609-4616-1-ND/2785380?utm_source=snapeda&utm_medium=aggregator&utm_campaign=symbol" H 1250 1650 50  0001 L BNN "Field4"
F 5 "None" H 1250 1650 50  0001 L BNN "Field5"
F 6 "Amphenol ICC" H 1250 1650 50  0001 L BNN "Field6"
F 7 "10118193-0001LF" H 1250 1650 50  0001 L BNN "Field7"
F 8 "609-4616-1-ND" H 1250 1650 50  0001 L BNN "Field8"
	1    1250 1650
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR01
U 1 1 5C9DA9F4
P 1900 1650
F 0 "#PWR01" H 1900 1400 50  0001 C CNN
F 1 "GND" H 1900 1500 50  0000 C CNN
F 2 "" H 1900 1650 50  0000 C CNN
F 3 "" H 1900 1650 50  0000 C CNN
	1    1900 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5C9DAB5E
P 3600 1850
F 0 "#PWR02" H 3600 1600 50  0001 C CNN
F 1 "GND" H 3600 1700 50  0000 C CNN
F 2 "" H 3600 1850 50  0000 C CNN
F 3 "" H 3600 1850 50  0000 C CNN
	1    3600 1850
	1    0    0    -1  
$EndComp
NoConn ~ 1650 1650
NoConn ~ 1650 1750
NoConn ~ 1650 1850
$Comp
L C C3
U 1 1 5C9DAEBB
P 6300 1900
F 0 "C3" H 6325 2000 50  0000 L CNN
F 1 "4.7uF" H 6325 1800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6338 1750 50  0001 C CNN
F 3 "" H 6300 1900 50  0000 C CNN
	1    6300 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5C9DB58A
P 6300 2050
F 0 "#PWR03" H 6300 1800 50  0001 C CNN
F 1 "GND" H 6300 1900 50  0000 C CNN
F 2 "" H 6300 2050 50  0000 C CNN
F 3 "" H 6300 2050 50  0000 C CNN
	1    6300 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5C9DB7B8
P 8450 1400
F 0 "#PWR04" H 8450 1150 50  0001 C CNN
F 1 "GND" H 8450 1250 50  0000 C CNN
F 2 "" H 8450 1400 50  0000 C CNN
F 3 "" H 8450 1400 50  0000 C CNN
	1    8450 1400
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5C9DC4B0
P 6000 2550
F 0 "C2" H 6025 2650 50  0000 L CNN
F 1 "4.7uF" H 6025 2450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6038 2400 50  0001 C CNN
F 3 "" H 6000 2550 50  0000 C CNN
	1    6000 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5C9DC4FF
P 6000 2700
F 0 "#PWR05" H 6000 2450 50  0001 C CNN
F 1 "GND" H 6000 2550 50  0000 C CNN
F 2 "" H 6000 2700 50  0000 C CNN
F 3 "" H 6000 2700 50  0000 C CNN
	1    6000 2700
	1    0    0    -1  
$EndComp
Text GLabel 2400 2200 2    60   Input ~ 0
VUSB
Text GLabel 6550 1700 2    60   Input ~ 0
VUSB
Text GLabel 9300 2200 2    60   Input ~ 0
VBAT
Text GLabel 8000 5150 2    60   Input ~ 0
VBAT
$Comp
L GND #PWR06
U 1 1 5C9DDE79
P 7900 5700
F 0 "#PWR06" H 7900 5450 50  0001 C CNN
F 1 "GND" H 7900 5550 50  0000 C CNN
F 2 "" H 7900 5700 50  0000 C CNN
F 3 "" H 7900 5700 50  0000 C CNN
	1    7900 5700
	1    0    0    -1  
$EndComp
Text GLabel 2750 3700 0    60   Input ~ 0
VBAT
$Comp
L C C1
U 1 1 5C9DEE2B
P 2850 3900
F 0 "C1" H 2875 4000 50  0000 L CNN
F 1 "1uF" H 2875 3800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2888 3750 50  0001 C CNN
F 3 "" H 2850 3900 50  0000 C CNN
	1    2850 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5C9DEEDB
P 2850 4150
F 0 "#PWR07" H 2850 3900 50  0001 C CNN
F 1 "GND" H 2850 4000 50  0000 C CNN
F 2 "" H 2850 4150 50  0000 C CNN
F 3 "" H 2850 4150 50  0000 C CNN
	1    2850 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 5C9DF181
P 3400 4100
F 0 "#PWR08" H 3400 3850 50  0001 C CNN
F 1 "GND" H 3400 3950 50  0000 C CNN
F 2 "" H 3400 4100 50  0000 C CNN
F 3 "" H 3400 4100 50  0000 C CNN
	1    3400 4100
	1    0    0    -1  
$EndComp
Text Notes 1200 3350 0    60   ~ 0
Speaker Header
$Comp
L GND #PWR09
U 1 1 5C9E0D73
P 1200 5800
F 0 "#PWR09" H 1200 5550 50  0001 C CNN
F 1 "GND" H 1200 5650 50  0000 C CNN
F 2 "" H 1200 5800 50  0000 C CNN
F 3 "" H 1200 5800 50  0000 C CNN
	1    1200 5800
	1    0    0    -1  
$EndComp
NoConn ~ 8400 2100
Text GLabel 3450 1600 0    60   Input ~ 0
CHARGING_STAT
Text GLabel 2750 5400 2    60   Input ~ 0
BUTTON_STAT
Text GLabel 4950 5650 0    60   Input ~ 0
RESET
Text GLabel 3200 6800 0    60   Input ~ 0
RESET
Text GLabel 4000 6800 2    60   Input ~ 0
VBAT
$Comp
L GND #PWR010
U 1 1 5C9E87AC
P 3200 7100
F 0 "#PWR010" H 3200 6850 50  0001 C CNN
F 1 "GND" H 3200 6950 50  0000 C CNN
F 2 "" H 3200 7100 50  0000 C CNN
F 3 "" H 3200 7100 50  0000 C CNN
	1    3200 7100
	1    0    0    -1  
$EndComp
Text GLabel 4000 6900 2    60   Input ~ 0
CHARGING_STAT
Text GLabel 6200 4000 2    60   Input ~ 0
AMP_STAT
Text GLabel 4950 5150 0    60   Input ~ 0
AMP_STAT
Text GLabel 4950 5450 0    60   Input ~ 0
BUTTON_STAT
Text GLabel 4950 5350 0    60   Input ~ 0
CHARGING_STAT
Text GLabel 8500 3700 2    60   Input ~ 0
AUDIO_DRIVE
Text GLabel 4950 5550 0    60   Input ~ 0
AUDIO_DRIVE
Text GLabel 4950 5250 0    60   Input ~ 0
LED_DRIVE
Text GLabel 11050 1100 1    60   Input ~ 0
LED_DRIVE
Text GLabel 4000 7000 2    60   Input ~ 0
LED_DRIVE
Text GLabel 3200 7000 0    60   Input ~ 0
AUDIO_DRIVE
Text GLabel 3200 6900 0    60   Input ~ 0
BUTTON_STAT
Text GLabel 4000 7100 2    60   Input ~ 0
AMP_STAT
$Comp
L SK6812 D2
U 1 1 5C9EC8CF
P 10500 1700
F 0 "D2" H 10500 1900 60  0000 C CNN
F 1 "SK6812" H 10500 1500 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 1950 60  0001 C CNN
F 3 "" H 10400 1950 60  0000 C CNN
	1    10500 1700
	1    0    0    -1  
$EndComp
$Comp
L SK6812 D1
U 1 1 5C9ECCEB
P 10500 1200
F 0 "D1" H 10500 1400 60  0000 C CNN
F 1 "SK6812" H 10500 1000 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 1450 60  0001 C CNN
F 3 "" H 10400 1450 60  0000 C CNN
	1    10500 1200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 5C9ED89A
P 10900 1250
F 0 "#PWR011" H 10900 1000 50  0001 C CNN
F 1 "GND" H 10900 1100 50  0000 C CNN
F 2 "" H 10900 1250 50  0000 C CNN
F 3 "" H 10900 1250 50  0000 C CNN
	1    10900 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5C9EDA56
P 10900 1750
F 0 "#PWR012" H 10900 1500 50  0001 C CNN
F 1 "GND" H 10900 1600 50  0000 C CNN
F 2 "" H 10900 1750 50  0000 C CNN
F 3 "" H 10900 1750 50  0000 C CNN
	1    10900 1750
	1    0    0    -1  
$EndComp
Text GLabel 10050 1150 0    60   Input ~ 0
VBAT
Text GLabel 10050 1650 0    60   Input ~ 0
VBAT
$Comp
L SK6812 D3
U 1 1 5C9EF96D
P 10500 2200
F 0 "D3" H 10500 2400 60  0000 C CNN
F 1 "SK6812" H 10500 2000 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 2450 60  0001 C CNN
F 3 "" H 10400 2450 60  0000 C CNN
	1    10500 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5C9EF974
P 10900 2250
F 0 "#PWR013" H 10900 2000 50  0001 C CNN
F 1 "GND" H 10900 2100 50  0000 C CNN
F 2 "" H 10900 2250 50  0000 C CNN
F 3 "" H 10900 2250 50  0000 C CNN
	1    10900 2250
	1    0    0    -1  
$EndComp
Text GLabel 10050 2150 0    60   Input ~ 0
VBAT
$Comp
L SK6812 D4
U 1 1 5C9EF9D3
P 10500 2700
F 0 "D4" H 10500 2900 60  0000 C CNN
F 1 "SK6812" H 10500 2500 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 2950 60  0001 C CNN
F 3 "" H 10400 2950 60  0000 C CNN
	1    10500 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5C9EF9DA
P 10900 2750
F 0 "#PWR014" H 10900 2500 50  0001 C CNN
F 1 "GND" H 10900 2600 50  0000 C CNN
F 2 "" H 10900 2750 50  0000 C CNN
F 3 "" H 10900 2750 50  0000 C CNN
	1    10900 2750
	1    0    0    -1  
$EndComp
Text GLabel 10050 2650 0    60   Input ~ 0
VBAT
$Comp
L SK6812 D5
U 1 1 5C9EFA56
P 10500 3200
F 0 "D5" H 10500 3400 60  0000 C CNN
F 1 "SK6812" H 10500 3000 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 3450 60  0001 C CNN
F 3 "" H 10400 3450 60  0000 C CNN
	1    10500 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 5C9EFA5D
P 10900 3250
F 0 "#PWR015" H 10900 3000 50  0001 C CNN
F 1 "GND" H 10900 3100 50  0000 C CNN
F 2 "" H 10900 3250 50  0000 C CNN
F 3 "" H 10900 3250 50  0000 C CNN
	1    10900 3250
	1    0    0    -1  
$EndComp
Text GLabel 10050 3150 0    60   Input ~ 0
VBAT
$Comp
L SK6812 D6
U 1 1 5C9EFACC
P 10500 3700
F 0 "D6" H 10500 3900 60  0000 C CNN
F 1 "SK6812" H 10500 3500 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 3950 60  0001 C CNN
F 3 "" H 10400 3950 60  0000 C CNN
	1    10500 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5C9EFAD3
P 10900 3750
F 0 "#PWR016" H 10900 3500 50  0001 C CNN
F 1 "GND" H 10900 3600 50  0000 C CNN
F 2 "" H 10900 3750 50  0000 C CNN
F 3 "" H 10900 3750 50  0000 C CNN
	1    10900 3750
	1    0    0    -1  
$EndComp
Text GLabel 10050 3650 0    60   Input ~ 0
VBAT
$Comp
L SK6812 D7
U 1 1 5C9EFB83
P 10500 4200
F 0 "D7" H 10500 4400 60  0000 C CNN
F 1 "SK6812" H 10500 4000 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 4450 60  0001 C CNN
F 3 "" H 10400 4450 60  0000 C CNN
	1    10500 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5C9EFB8A
P 10900 4250
F 0 "#PWR017" H 10900 4000 50  0001 C CNN
F 1 "GND" H 10900 4100 50  0000 C CNN
F 2 "" H 10900 4250 50  0000 C CNN
F 3 "" H 10900 4250 50  0000 C CNN
	1    10900 4250
	1    0    0    -1  
$EndComp
Text GLabel 10050 4150 0    60   Input ~ 0
VBAT
$Comp
L SK6812 D8
U 1 1 5C9EFBE1
P 10500 4700
F 0 "D8" H 10500 4900 60  0000 C CNN
F 1 "SK6812" H 10500 4500 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 4950 60  0001 C CNN
F 3 "" H 10400 4950 60  0000 C CNN
	1    10500 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5C9EFBE8
P 10900 4750
F 0 "#PWR018" H 10900 4500 50  0001 C CNN
F 1 "GND" H 10900 4600 50  0000 C CNN
F 2 "" H 10900 4750 50  0000 C CNN
F 3 "" H 10900 4750 50  0000 C CNN
	1    10900 4750
	1    0    0    -1  
$EndComp
Text GLabel 10050 4650 0    60   Input ~ 0
VBAT
$Comp
L SK6812 D9
U 1 1 5C9EFC52
P 10500 5200
F 0 "D9" H 10500 5400 60  0000 C CNN
F 1 "SK6812" H 10500 5000 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 5450 60  0001 C CNN
F 3 "" H 10400 5450 60  0000 C CNN
	1    10500 5200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 5C9EFC59
P 10900 5250
F 0 "#PWR019" H 10900 5000 50  0001 C CNN
F 1 "GND" H 10900 5100 50  0000 C CNN
F 2 "" H 10900 5250 50  0000 C CNN
F 3 "" H 10900 5250 50  0000 C CNN
	1    10900 5250
	1    0    0    -1  
$EndComp
Text GLabel 10050 5150 0    60   Input ~ 0
VBAT
$Comp
L SK6812 D10
U 1 1 5C9EFCCA
P 10500 5700
F 0 "D10" H 10500 5900 60  0000 C CNN
F 1 "SK6812" H 10500 5500 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 5950 60  0001 C CNN
F 3 "" H 10400 5950 60  0000 C CNN
	1    10500 5700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 5C9EFCD1
P 10900 5750
F 0 "#PWR020" H 10900 5500 50  0001 C CNN
F 1 "GND" H 10900 5600 50  0000 C CNN
F 2 "" H 10900 5750 50  0000 C CNN
F 3 "" H 10900 5750 50  0000 C CNN
	1    10900 5750
	1    0    0    -1  
$EndComp
Text GLabel 10050 5650 0    60   Input ~ 0
VBAT
$Comp
L SK6812 D11
U 1 1 5C9EFD4B
P 10500 6200
F 0 "D11" H 10500 6400 60  0000 C CNN
F 1 "SK6812" H 10500 6000 60  0000 C CNN
F 2 "Misc:LED_SK6812_PLCC4_5.0x5.0mm_P3.2mm" H 10400 6450 60  0001 C CNN
F 3 "" H 10400 6450 60  0000 C CNN
	1    10500 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 5C9EFD52
P 10900 6250
F 0 "#PWR021" H 10900 6000 50  0001 C CNN
F 1 "GND" H 10900 6100 50  0000 C CNN
F 2 "" H 10900 6250 50  0000 C CNN
F 3 "" H 10900 6250 50  0000 C CNN
	1    10900 6250
	1    0    0    -1  
$EndComp
Text GLabel 10050 6150 0    60   Input ~ 0
VBAT
Text Notes 10250 750  0    60   ~ 0
LED Screen
NoConn ~ 10050 6250
$Comp
L R R1
U 1 1 5C9F36F6
P 6250 1600
F 0 "R1" V 6330 1600 50  0000 C CNN
F 1 "3.9k" V 6250 1600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 6180 1600 50  0001 C CNN
F 3 "" H 6250 1600 50  0000 C CNN
	1    6250 1600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR022
U 1 1 5C9F3891
P 6950 1750
F 0 "#PWR022" H 6950 1500 50  0001 C CNN
F 1 "GND" H 6950 1600 50  0000 C CNN
F 2 "" H 6950 1750 50  0000 C CNN
F 3 "" H 6950 1750 50  0000 C CNN
	1    6950 1750
	1    0    0    -1  
$EndComp
$Comp
L Debug U5
U 1 1 5C9FF499
P 7900 1450
F 0 "U5" H 7900 1550 60  0000 C CNN
F 1 "Debug" H 7900 1350 60  0000 C CNN
F 2 "Misc:Debug_2p" H 7900 1450 60  0001 C CNN
F 3 "" H 7900 1450 60  0000 C CNN
	1    7900 1450
	0    -1   -1   0   
$EndComp
$Comp
L Debug U1
U 1 1 5CA0062A
P 2300 1700
F 0 "U1" H 2300 1800 60  0000 C CNN
F 1 "Debug" H 2300 1600 60  0000 C CNN
F 2 "Misc:Debug_2p" H 2300 1700 60  0001 C CNN
F 3 "" H 2300 1700 60  0000 C CNN
	1    2300 1700
	0    -1   -1   0   
$EndComp
$Comp
L Debug U2
U 1 1 5CA00B71
P 2350 4000
F 0 "U2" H 2350 4100 60  0000 C CNN
F 1 "Debug" H 2350 3900 60  0000 C CNN
F 2 "Misc:Debug_2p" H 2350 4000 60  0001 C CNN
F 3 "" H 2350 4000 60  0000 C CNN
	1    2350 4000
	0    1    1    0   
$EndComp
$Comp
L C C5
U 1 1 5CA0795A
P 7250 3200
F 0 "C5" H 7275 3300 50  0000 L CNN
F 1 "4.7nF" H 7275 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7288 3050 50  0001 C CNN
F 3 "" H 7250 3200 50  0000 C CNN
	1    7250 3200
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 5CA082CC
P 7650 3700
F 0 "R2" V 7730 3700 50  0000 C CNN
F 1 "27k" V 7650 3700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 7580 3700 50  0001 C CNN
F 3 "" H 7650 3700 50  0000 C CNN
	1    7650 3700
	0    -1   -1   0   
$EndComp
$Comp
L C C8
U 1 1 5CA08749
P 7950 4050
F 0 "C8" H 7975 4150 50  0000 L CNN
F 1 "100nF" H 7975 3950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7988 3900 50  0001 C CNN
F 3 "" H 7950 4050 50  0000 C CNN
	1    7950 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5CA0896A
P 7950 4300
F 0 "#PWR023" H 7950 4050 50  0001 C CNN
F 1 "GND" H 7950 4150 50  0000 C CNN
F 2 "" H 7950 4300 50  0000 C CNN
F 3 "" H 7950 4300 50  0000 C CNN
	1    7950 4300
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5CA08AE5
P 8200 3700
F 0 "C9" H 8225 3800 50  0000 L CNN
F 1 "100nF" H 8225 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8238 3550 50  0001 C CNN
F 3 "" H 8200 3700 50  0000 C CNN
	1    8200 3700
	0    -1   -1   0   
$EndComp
Text Notes 8400 2600 0    60   ~ 0
ON=2+3 (UP)\nOFF=1+2 (DOWN)
Text Notes 1850 5050 0    60   ~ 0
Button
Text Notes 6050 4950 0    60   ~ 0
Microcontroller
Text Notes 5850 1400 0    60   ~ 0
>3.3k for 1C charge of 400mAh\n2k for 500mA/h charge of 1.2Ah
Text Notes 8350 4200 0    60   ~ 0
9.5 dB Power Gain (B5 to B1)\n850 Hz LPF\n60 Hz HPF
$Comp
L C C7
U 1 1 5CA14FAC
P 7900 5400
F 0 "C7" H 7925 5500 50  0000 L CNN
F 1 "47uF" H 7925 5300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7938 5250 50  0001 C CNN
F 3 "" H 7900 5400 50  0000 C CNN
	1    7900 5400
	1    0    0    -1  
$EndComp
Text Notes 8000 5750 0    60   ~ 0
Cap reduces LED flicker\nReduces railing of loud sounds
$Comp
L R R3
U 1 1 5CA1A8CF
P 7650 3800
F 0 "R3" V 7730 3800 50  0000 C CNN
F 1 "27k" V 7650 3800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 7580 3800 50  0001 C CNN
F 3 "" H 7650 3800 50  0000 C CNN
	1    7650 3800
	0    1    1    0   
$EndComp
$Comp
L C C6
U 1 1 5CA1BFEF
P 7250 4450
F 0 "C6" H 7275 4550 50  0000 L CNN
F 1 "4.7nF" H 7275 4350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7288 4300 50  0001 C CNN
F 3 "" H 7250 4450 50  0000 C CNN
	1    7250 4450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR024
U 1 1 5CA50C6F
P 750 2050
F 0 "#PWR024" H 750 1800 50  0001 C CNN
F 1 "GND" H 750 1900 50  0000 C CNN
F 2 "" H 750 2050 50  0000 C CNN
F 3 "" H 750 2050 50  0000 C CNN
	1    750  2050
	1    0    0    -1  
$EndComp
NoConn ~ 750  1550
NoConn ~ 750  1450
$Comp
L C C4
U 1 1 5CA546C4
P 6850 4050
F 0 "C4" H 6875 4150 50  0000 L CNN
F 1 "1uF" H 6875 3950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6888 3900 50  0001 C CNN
F 3 "" H 6850 4050 50  0000 C CNN
	1    6850 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 5CA548D5
P 6850 4200
F 0 "#PWR025" H 6850 3950 50  0001 C CNN
F 1 "GND" H 6850 4050 50  0000 C CNN
F 2 "" H 6850 4200 50  0000 C CNN
F 3 "" H 6850 4200 50  0000 C CNN
	1    6850 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 5CA5B8D1
P 1900 4000
F 0 "#PWR026" H 1900 3750 50  0001 C CNN
F 1 "GND" H 1900 3850 50  0000 C CNN
F 2 "" H 1900 4000 50  0000 C CNN
F 3 "" H 1900 4000 50  0000 C CNN
	1    1900 4000
	1    0    0    -1  
$EndComp
Connection ~ 7900 5650
Wire Wire Line
	7900 5550 7900 5700
Connection ~ 7900 5150
Wire Wire Line
	7900 5250 7900 5150
Wire Wire Line
	3250 3200 7100 3200
Wire Wire Line
	6950 1600 6950 1750
Wire Wire Line
	6100 1600 6000 1600
Wire Wire Line
	6400 1600 6950 1600
Wire Wire Line
	6000 1700 6550 1700
Connection ~ 6300 1700
Wire Wire Line
	6300 1750 6300 1700
Wire Wire Line
	7800 3700 8050 3700
Wire Wire Line
	7950 3800 7800 3800
Wire Wire Line
	7950 3900 7950 3800
Wire Wire Line
	7950 4300 7950 4200
Connection ~ 3250 4450
Connection ~ 2350 4450
Wire Wire Line
	2050 4450 7100 4450
Connection ~ 3250 3600
Wire Wire Line
	3250 3200 3250 3600
Wire Wire Line
	11050 1150 11050 1100
Wire Wire Line
	2350 4350 2350 4450
Connection ~ 2350 3600
Wire Wire Line
	2350 3650 2350 3600
Connection ~ 2300 2200
Wire Wire Line
	2300 2050 2300 2200
Wire Wire Line
	2100 2200 2400 2200
Wire Wire Line
	2100 1950 2100 2200
Connection ~ 7650 1800
Wire Wire Line
	7900 1800 7650 1800
Wire Wire Line
	7900 1100 8500 1100
Connection ~ 7650 2300
Wire Wire Line
	7650 1000 7650 2300
Wire Wire Line
	6000 2300 8400 2300
Wire Wire Line
	1650 1950 2100 1950
Wire Wire Line
	10050 5950 10050 5750
Wire Wire Line
	10900 5950 10050 5950
Wire Wire Line
	10900 6150 10900 5950
Wire Wire Line
	10050 5450 10050 5250
Wire Wire Line
	10900 5450 10050 5450
Wire Wire Line
	10900 5650 10900 5450
Wire Wire Line
	10050 4950 10050 4750
Wire Wire Line
	10900 4950 10050 4950
Wire Wire Line
	10900 5150 10900 4950
Wire Wire Line
	10050 4450 10050 4250
Wire Wire Line
	10900 4450 10050 4450
Wire Wire Line
	10900 4650 10900 4450
Wire Wire Line
	10050 3950 10050 3750
Wire Wire Line
	10900 3950 10050 3950
Wire Wire Line
	10900 4150 10900 3950
Wire Wire Line
	10050 3450 10050 3250
Wire Wire Line
	10900 3450 10050 3450
Wire Wire Line
	10900 3650 10900 3450
Wire Wire Line
	10050 2950 10050 2750
Wire Wire Line
	10900 2950 10050 2950
Wire Wire Line
	10900 3150 10900 2950
Wire Wire Line
	10050 2450 10050 2250
Wire Wire Line
	10900 2450 10050 2450
Wire Wire Line
	10900 2650 10900 2450
Wire Wire Line
	10050 1950 10050 1750
Wire Wire Line
	10900 1950 10050 1950
Wire Wire Line
	10900 2150 10900 1950
Wire Wire Line
	10050 1450 10050 1250
Wire Wire Line
	10900 1450 10050 1450
Wire Wire Line
	10900 1650 10900 1450
Wire Wire Line
	11050 1150 10900 1150
Wire Wire Line
	2550 5400 2750 5400
Wire Wire Line
	3600 1600 3450 1600
Connection ~ 6000 2300
Wire Wire Line
	6000 1800 6000 2400
Wire Wire Line
	9000 2200 9300 2200
Wire Wire Line
	3250 3900 3250 4450
Wire Wire Line
	3400 3900 3250 3900
Wire Wire Line
	3400 4100 3400 4000
Connection ~ 2850 4100
Wire Wire Line
	3150 4100 2850 4100
Wire Wire Line
	2850 4150 2850 4050
Wire Wire Line
	3150 3800 3150 4100
Wire Wire Line
	3150 3800 3400 3800
Connection ~ 2850 3700
Wire Wire Line
	2750 3700 3400 3700
Wire Wire Line
	7650 5150 8000 5150
Wire Wire Line
	7650 1000 8500 1000
Connection ~ 1900 1550
Wire Wire Line
	1900 1550 1650 1550
Wire Wire Line
	1900 1350 1900 1650
Wire Wire Line
	3600 1850 3600 1700
Wire Wire Line
	2850 3750 2850 3700
Wire Wire Line
	7650 5650 7900 5650
Wire Wire Line
	1900 1350 2300 1350
Connection ~ 750  1950
Connection ~ 750  1850
Connection ~ 750  1750
Wire Wire Line
	750  1650 750  2050
Wire Wire Line
	6200 3900 6850 3900
Wire Wire Line
	6200 3800 7500 3800
Wire Wire Line
	7500 3700 6200 3700
Wire Wire Line
	7400 3200 7450 3200
Wire Wire Line
	7450 3200 7450 3700
Connection ~ 7450 3700
Wire Wire Line
	7450 3800 7450 4450
Wire Wire Line
	7450 4450 7400 4450
Connection ~ 7450 3800
Wire Wire Line
	8350 3700 8500 3700
Wire Wire Line
	8450 1400 8450 1100
Connection ~ 8450 1100
Wire Wire Line
	8500 1200 8450 1200
Connection ~ 8450 1200
Wire Wire Line
	8500 1300 8450 1300
Connection ~ 8450 1300
Wire Wire Line
	2050 4450 2050 3700
Wire Wire Line
	2050 3700 1850 3700
Wire Wire Line
	1850 3600 3400 3600
Wire Wire Line
	1900 4000 1900 3800
Wire Wire Line
	1900 3800 1850 3800
Wire Wire Line
	1850 3900 1900 3900
Connection ~ 1900 3900
$Comp
L EVQ-P7C01P S1
U 1 1 5C9D6B5E
P 1350 5400
F 0 "S1" H 2400 5700 50  0000 L CNN
F 1 "EVQ-P7C01P" H 2400 5600 50  0000 L CNN
F 2 "SamacSys_Parts:EVQP7C01P" H 2400 5500 50  0001 L CNN
F 3 "https://www.arrow.com/en/products/evqp7c01p/panasonic" H 2400 5400 50  0001 L CNN
F 4 "Black Side Tactile Switch, SPST 50 mA@ 12 V dc 1.7mm" H 2400 5300 50  0001 L CNN "Description"
F 5 "1" H 2400 5200 50  0001 L CNN "Height"
F 6 "Panasonic" H 2400 5100 50  0001 L CNN "Manufacturer_Name"
F 7 "EVQ-P7C01P" H 2400 5000 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "667-EVQP7C01P" H 2400 4900 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=667-EVQP7C01P" H 2400 4800 50  0001 L CNN "Mouser Price/Stock"
F 10 "8113353" H 2400 4700 50  0001 L CNN "RS Part Number"
F 11 "http://uk.rs-online.com/web/p/products/8113353" H 2400 4600 50  0001 L CNN "RS Price/Stock"
	1    1350 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 5400 1200 5400
Wire Wire Line
	1200 5400 1200 5800
Wire Wire Line
	2550 5500 2550 5750
Wire Wire Line
	2550 5750 1200 5750
Connection ~ 1200 5750
Wire Wire Line
	1350 5500 1350 5650
Wire Wire Line
	1350 5650 2700 5650
Wire Wire Line
	2700 5650 2700 5400
Connection ~ 2700 5400
$EndSCHEMATC

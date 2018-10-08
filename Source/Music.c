// ******** Music.c **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 10/1/18
// Description: File to hold music operations
// Lab Number: Lab05
// TA: Zee Lv
// Date of last revision: 10/1/18
// Hardware Configuration: N/A

#include <stdint.h>
#include "Music.h"

const uint32_t defaultInstrument[64] = {
	1024,1124,1224,1321,1416,1507,1593,1674,
	1748,1816,1875,1927,1970,2004,2028,2043,
	2048,2043,2028,2004,1970,1927,1875,1816,
	1748,1674,1593,1507,1416,1321,1224,1124,
	1024,924,824,727,632,541,455,374,
	300,232,173,121,78,44,20,5,
	0,5,20,44,78,121,173,232,
	300,374,455,541,632,727,824,924,
};

const uint32_t fluteInstrument[64] = {
	1007, 1252, 1374, 1548, 1698,
	1797, 1825, 1797, 1675, 1562, 1383, 1219, 1092, 1007, 913, 890, 833, 
	847, 810, 777, 744, 674, 598, 551, 509, 476, 495, 533, 589, 659, 
	758, 876, 1007, 1252, 1374 ,1548 ,1698 ,1797 ,1825 ,1797 ,1675 ,1562,
	1383 ,1219 ,1092 ,1007 ,913 ,890 ,833 ,847 ,810 ,777 ,744 ,674 ,598 ,551 ,
	509 ,476 ,495 ,533 ,589 ,659 ,758 ,876
};


	

const uint32_t hornInstrument[64] = {
	1063,1082,1119,1275,1678,1748,1275,755,
	661,661,703,731,769,845,1039,1134,
	1209,1332,1465,1545,1427,1588,1370,1086,
	708,519,448,490,566,684,802,992,
	1063,1082,1119,1275,1678,1748,1275,755,
	661,661,703,731,769,845,1039,1134,
	1209,1332,1465,1545,1427,1588,1370,1086,
	708,519,448,490,566,684,802,992
};	
const uint32_t bassoonInstrument[64] = {
	1068, 1169, 1175, 1161, 1130, 1113, 1102, 1076, 1032, 985, 963, 987, 1082, 1343, 1737, 1863, 
	1575, 1031, 538, 309, 330, 472, 626, 807, 1038, 1270, 1420, 1461, 1375, 1201, 1005, 819, 658, 
	532, 496, 594, 804, 1055, 1248, 1323, 1233, 1049, 895, 826, 826, 850, 862, 861, 899, 961, 1006, 
	1023, 1046, 1092, 1177, 1224, 1186, 1133, 1098, 1102, 1109, 1076, 1027, 1003
};
const uint32_t oboeInstrument[64] = {
	1024, 1024, 1014, 1008, 1022, 1065, 1093, 1006, 858, 711, 612, 596, 672, 806, 952, 1074, 1154, 1191, 
	1202, 1216, 1236, 1255, 1272, 1302, 1318, 1299, 1238, 1140, 1022, 910, 827, 779, 758, 757, 782, 856, 
	972, 1088, 1177, 1226, 1232, 1203, 1157, 1110, 1067, 1028, 993, 958, 929, 905, 892, 900, 940, 1022, 
	1125, 1157, 1087, 965, 836, 783, 816, 895, 971, 1017
};
const uint32_t trumpetInstrument[64] = {
	987, 1049, 1090, 1110, 1134, 1160, 1139, 1092, 1070, 1042, 1035, 1029, 1008, 1066, 1150, 1170, 1087, 915, 679, 372, 151, 
	558, 1014, 1245, 1260, 1145, 1063, 984, 934, 960, 1027, 1077, 1081, 1074, 1064, 1042, 1010, 974, 968, 974, 994, 1039, 
	1094, 1129, 1125, 1092, 1056, 1056, 1082, 1059, 1046, 1058, 1061, 1045, 1034, 1050, 1094, 1112, 1092, 1063, 1053, 1065, 1052, 992
};

//Freq for the various notes based on 80000000/(64*notefreq)
#define REST 0//0x00FFFFFF
#define C2 	19110
#define CS2 18038
#define D2 	17025
#define DS2 16071
#define E2 	15168
#define F2 	14317
#define FS2 13514
#define G2 	12755
#define GS2 12039
#define A2 	11364
#define AS2 10726
#define B2	10124
#define C3 	9556
#define CS3 9019
#define D3 	8513
#define DS3 8035
#define E3 	7584
#define F3 	7159
#define FS3 6757
#define G3 	6378
#define GS3 6020
#define A3 	5682
#define AS3 5603
#define B3	5062
#define C4 	4778
#define CS4 4510
#define D4 	4257
#define DS4 4018
#define E4 	3792
#define F4 	3579
#define FS4 3378
#define G4 	3189
#define GS4 3010
#define A4 	2841
#define AS4 2681
#define B4	2531
#define C5 	2389
#define CS5 2255
#define D5 	2128
#define DS5 2009
#define E5 	1896
#define F5 	1790
#define FS5 1689
#define G5 	1594
#define GS5 1505
#define A5 	1420
#define AS5 1341
#define B5	1265
#define C6 	1194
#define CS6 1127
#define D6 	1064
#define DS6 1004
#define E6 	948
#define F6 	895
#define FS6 845
#define G6 	797
#define GS6 752
#define A6 	710
#define AS6 670
#define B6	633

//Define note speeds
#define NOTE_SPEED 		(80000000 / 1) 	//set to 1Hz = 60 BPM
#define SIXTEENTH_NOTE	(uint32_t)(NOTE_SPEED / 4)
#define EIGHTH_NOTE 	(uint32_t)(NOTE_SPEED / 2)
#define QUARTER_NOTE 	(uint32_t)(NOTE_SPEED)
#define HALF_NOTE 		(uint32_t)(NOTE_SPEED * 2)
#define WHOLE_NOTE 		(uint32_t)(NOTE_SPEED * 4)

uint32_t CurrentSongIndex;
uint32_t CurrentWaveIndex;
Instrument CurrentInstrument = DefaultInstrument;
Tempo CurrentTempo = NormalSpeed;

Note BombOmbBattlefieldData[] = {
	{E4, SIXTEENTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, QUARTER_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{GS3, SIXTEENTH_NOTE, DefaultInstrument},
	{A3, SIXTEENTH_NOTE, DefaultInstrument},
	{GS3, SIXTEENTH_NOTE, DefaultInstrument},
	{A3, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{D4, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, EIGHTH_NOTE, DefaultInstrument},
	{A3, QUARTER_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{GS3, EIGHTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{FS3, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{FS3, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, EIGHTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{FS3, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{G4, EIGHTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, EIGHTH_NOTE, DefaultInstrument},
	{D4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{D4, SIXTEENTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, SIXTEENTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, QUARTER_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{GS4, EIGHTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{GS4, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{D5, SIXTEENTH_NOTE, DefaultInstrument},
	{C5, EIGHTH_NOTE, DefaultInstrument},
	{A4, QUARTER_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{GS4, EIGHTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{FS4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{FS4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, EIGHTH_NOTE + SIXTEENTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{C4, QUARTER_NOTE, DefaultInstrument},
	{REST, HALF_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{D4, SIXTEENTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, SIXTEENTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, EIGHTH_NOTE, DefaultInstrument},
	{C4, QUARTER_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{GS4, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{GS4, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{D4, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, EIGHTH_NOTE, DefaultInstrument},
	{A4, QUARTER_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{GS4, EIGHTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{FS3, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{FS3, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, EIGHTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{FS3, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{G4, EIGHTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, EIGHTH_NOTE, DefaultInstrument},
	{D4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{D4, SIXTEENTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, SIXTEENTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, QUARTER_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{GS4, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{GS4, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{D5, SIXTEENTH_NOTE, DefaultInstrument},
	{C5,EIGHTH_NOTE, DefaultInstrument},
	{A4, QUARTER_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{GS4, EIGHTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{FS4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{FS4, SIXTEENTH_NOTE, DefaultInstrument},
	{G4, SIXTEENTH_NOTE, DefaultInstrument},
	{G3, SIXTEENTH_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{C4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, HALF_NOTE, DefaultInstrument},
	{E5, SIXTEENTH_NOTE, DefaultInstrument},
	{F5, SIXTEENTH_NOTE, DefaultInstrument},
	{G5, SIXTEENTH_NOTE, DefaultInstrument},
	{GS5, SIXTEENTH_NOTE, DefaultInstrument},
	{A5, QUARTER_NOTE, DefaultInstrument},
	{GS5, QUARTER_NOTE, DefaultInstrument},
	{G5, QUARTER_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{FS5, EIGHTH_NOTE, DefaultInstrument},
	{G5, SIXTEENTH_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{GS5, SIXTEENTH_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{DS5, QUARTER_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{E5, SIXTEENTH_NOTE, DefaultInstrument},
	{F5, SIXTEENTH_NOTE, DefaultInstrument},
	{G5, SIXTEENTH_NOTE, DefaultInstrument},
	{GS5, SIXTEENTH_NOTE, DefaultInstrument},
	{A5, QUARTER_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{GS5, EIGHTH_NOTE, DefaultInstrument},
	{G5, QUARTER_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{FS5, EIGHTH_NOTE, DefaultInstrument},
	{F5, EIGHTH_NOTE + SIXTEENTH_NOTE, DefaultInstrument},
	{E5, EIGHTH_NOTE + SIXTEENTH_NOTE, DefaultInstrument},
	{C5, HALF_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{A5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{GS5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{GS5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{G5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{G5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{FS5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{FS5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{F5, EIGHTH_NOTE + SIXTEENTH_NOTE, DefaultInstrument},
	{G5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{E5, HALF_NOTE + EIGHTH_NOTE, DefaultInstrument},
	{A5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{GS5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{GS5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{G5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{G5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{FS5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{FS5, SIXTEENTH_NOTE, DefaultInstrument},
	{F5, EIGHTH_NOTE + SIXTEENTH_NOTE, DefaultInstrument},
	{E5, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, EIGHTH_NOTE, DefaultInstrument},
	{C5, EIGHTH_NOTE + QUARTER_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, EIGHTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, EIGHTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{GS4, QUARTER_NOTE, DefaultInstrument},
	{G4, QUARTER_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, EIGHTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, EIGHTH_NOTE, DefaultInstrument},
	{DS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{C5, SIXTEENTH_NOTE, DefaultInstrument},
	{E4, EIGHTH_NOTE, DefaultInstrument},
	{AS4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, QUARTER_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{A4, SIXTEENTH_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{C4, EIGHTH_NOTE, DefaultInstrument},
	{DS5, EIGHTH_NOTE + QUARTER_NOTE, DefaultInstrument},
	{REST, SIXTEENTH_NOTE, DefaultInstrument},
	{E5, QUARTER_NOTE, DefaultInstrument}
};

Song Songs[] = {
	
	{BombOmbBattlefieldData, sizeof(BombOmbBattlefieldData) / sizeof(Note)}
};

const uint8_t NumberOfSongs = sizeof(Songs) / sizeof(Song);

const uint32_t* InstrumentTable[NumInstruments] = {&defaultInstrument[0], &fluteInstrument[0],
	&(hornInstrument[0]), &bassoonInstrument[0], &oboeInstrument[0], trumpetInstrument[0]};

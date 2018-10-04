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

//Freq for the various notes based on 80000000/(64*notefreq)
#define REST 0x00FFFFFF
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


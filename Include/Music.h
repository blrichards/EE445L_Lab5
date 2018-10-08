// ******** Music.h **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 10/1/18
// Description: Header file for Music.c
// Lab Number: Lab05
// TA: Zee Lv
// Date of last revision: 10/1/18
// Hardware Configuration: N/A

#ifndef MUSIC_H_
#define MUSIC_H_

#include <stdint.h>

typedef enum {
	NormalSpeed,
	DoubleSpeed,
	HalfSpeed,
	NumTempos,
} Tempo;

typedef enum {
	DefaultInstrument, // basic sine tab
	Flute,			   // on the 445L site
	Horn,			   // on the 445L site
	Bassoon,		   // on the 445L site
	Oboe,			   // on the 445L site
	Trumpet,		   // on the 445L site
	NumInstruments     // number of instruments
} Instrument;

extern const uint32_t* InstrumentTable[NumInstruments];

typedef struct{
	uint32_t Frequency;
	uint32_t Duration;
} Note;

typedef struct {
	const Note* notes;
	const uint32_t length;
} Song;

extern Song Songs[];
extern const uint8_t NumberOfSongs;
extern uint32_t CurrentSongIndex;
extern uint32_t CurrentWaveIndex;
extern Instrument CurrentInstrument;
extern Tempo CurrentTempo;

#endif // MUSIC_H_

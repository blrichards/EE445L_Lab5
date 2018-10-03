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

#define NUM_INSTRUMENTS 6

//For tempo manipulation
#define NORMAL_SPEED 1
#define DOUBLE_SPEED 2
#define HALF_SPEED 	 3


typedef enum{
	Default,		//basic sine tab
	Flute,			//on the 445L site
	Horn,			//on the 445L site
	Basson,			//on the 445L site
	Oboe,			//on the 445L site
	Trumpet			//on the 445L site
} Instrument;

typedef struct{
	uint32_t Frequency;
	uint32_t Duration;
	Instrument Instrument;
} Note_t;

extern uint32_t CurrentSongIndex;
extern uint32_t CurrentWaveIndex;
extern Instrument CurrentInstrumet;
extern uint8_t CurrentTempo;

#endif // MUSIC_H_

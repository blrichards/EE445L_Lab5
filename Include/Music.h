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

extern uint32_t CurrentNoteValue;


typedef enum{
	Default,
	Flute,
	Horn,
	Basson,
	Oboe,
	Trumpet
} Instrument;

typedef struct{
	uint32_t Frequency;
	uint16_t Duration;
	Instrument Instrument;
} Note_t;


#endif // MUSIC_H_

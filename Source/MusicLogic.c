// ******** MusicLogic.c **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 10/1/18
// Description: Main Driver for Music Operations
// Lab Number: Lab05
// TA: Zee Lv
// Date of last revision: 10/1/18
// Hardware Configuration: N/A

#include <stdint.h>
#include <stdbool.h>
#include "Buttons.h"
#include "Music.h"
#include "MusicLogic.h"
#include "tm4c123gh6pm.h"

#define CYCLE_ENUM(type, limit, current) ((type)(((uint8_t)(current) + 1) % (limit)))

static bool musicPlaying = false;

typedef void(*ButtonAction)(void);

static void PlayButtonHandler(void);
static void RewindButtonHandler(void);
static void InstrumentButtonHandler(void);
static void TempoButtonHandler(void);

static const ButtonAction ButtonHandler[NumMusicPlayerButtons] = {
	PlayButtonHandler,
	RewindButtonHandler,
	InstrumentButtonHandler,
	TempoButtonHandler
};

void PlayButtonHandler(void){
	if(musicPlaying) {
		musicPlaying = false;
		TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // Disable Note timer
		NVIC_ST_CTRL_R &= ~0x00000001;	 // Disable SineTab timer
	} else {
		musicPlaying = true;
		TIMER0_CTL_R |= TIMER_CTL_TAEN;	 // Disable Note timer
		NVIC_ST_CTRL_R |= 0x00000001;	 // Disable SineTab timer
	}
}

void RewindButtonHandler(void){
	if (musicPlaying) 
		musicPlaying = false;
	TIMER0_CTL_R &= ~TIMER_CTL_TAEN;	//Disable Note timer
	NVIC_ST_CTRL_R &= ~0x00000001;		//Disable SineTab timer
	CurrentSongIndex = 0;
	CurrentWaveIndex = 0;
}

void InstrumentButtonHandler(void)
{
	CurrentInstrument = CYCLE_ENUM(Instrument, NumInstruments, CurrentInstrument);
}

void TempoButtonHandler(void)
{
	CurrentTempo = CYCLE_ENUM(Tempo, NumTempos, CurrentTempo);
}

void MusicPlayerShouldUpdate(MusicPlayerButton button){
	if(button >= NumMusicPlayerButtons) 
		return;
	ButtonHandler[button]();
}

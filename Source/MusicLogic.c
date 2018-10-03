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

static bool musicPlaying = false;

typedef void(*ButtonAction)(void);

static void PlayButtonHandler(void);
static void RewindButtonHandler(void);
static void InstrumentButtonHandler(void);
static void TempoButtonHandler(void);

static const ButtonAction ButtonHandler[NUM_BUTTONS] = {
	PlayButtonHandler,
	RewindButtonHandler,
	InstrumentButtonHandler,
	TempoButtonHandler,
};

void PlayButtonHandler(void){
	if(musicPlaying){
		musicPlaying = false;
		TIMER0_CTL_R &= ~TIMER_CTL_TAEN;	//Disable Note timer
		NVIC_ST_CTRL_R &= ~0x00000001;		//Disable SineTab timer
	} 
	else {
		musicPlaying = true;
		TIMER0_CTL_R |= TIMER_CTL_TAEN;	//Disable Note timer
		NVIC_ST_CTRL_R |= 0x00000001;		//Disable SineTab timer
	}
}
void RewindButtonHandler(void){
	if(musicPlaying) musicPlaying = false;
	TIMER0_CTL_R &= ~TIMER_CTL_TAEN;	//Disable Note timer
	NVIC_ST_CTRL_R &= ~0x00000001;		//Disable SineTab timer
	CurrentSongIndex = 0;
	CurrentWaveIndex = 0;
}

void InstrumentButtonHandler(void){
	/*
	 * TODO: for this handler we basically need a global of the instruments
	 * and cycle through them using CurrentInstrumet global, but might not be needed
	 * with the note struct, just an idea of a cool feature that would be easy to implament
	 */
}

void TempoButtonHandler(void){
	if(CurrentTempo == NORMAL_SPEED){
		CurrentTempo = DOUBLE_SPEED;
		return;
	}
	else if(CurrentTempo == DOUBLE_SPEED){
		CurrentTempo = HALF_SPEED;
		return;
	}
	else if(CurrentTempo == HALF_SPEED){
		CurrentTempo = NORMAL_SPEED;
		return;
	}
}

void MusicPlayerShouldUpdate(Buttons button){
	if(button > NUM_BUTTONS - 1) return;
	ButtonHandler[button]();
}

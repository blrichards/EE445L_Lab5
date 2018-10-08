// ******** Timer.c **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 9/18/18
// Description: File for timer functionality
// Lab Number: Lab05
// TA: Zee Lv
// Date of last revision: 9/19/2018
// Hardware Configuration: N/A

#include "Music.h"
#include "Timer.h"
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "SPI.h"
#include <stdint.h>

uint32_t CurrentNoteFrequency;
uint8_t NoteIndex = 0;
uint32_t SongIndex = 0;

#define PB7 (*((volatile uint32_t*)0x40005200))
#define PF2 (*((volatile uint32_t*)0x40025010))

void SysTick_Init(void)
{
	NVIC_ST_CTRL_R = 0;           		// disable SysTick during setup
	NVIC_ST_RELOAD_R = 0x00FFFFFF;       	// Set max reload value
	NVIC_ST_CURRENT_R = 0;        		// any write to current clears it
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x00000000; // priority 1
	NVIC_ST_CTRL_R = 0x00000006;  		// enable interrupts, not clock
}

void SysTick_Handler(void){
    NVIC_ST_RELOAD_R = CurrentNoteFrequency;     // reload value for high phase
	
	SPI_Output(InstrumentTable[CurrentInstrument][instrumentIndex]); //TODO: add current sine table value based on instrument
	instrumentIndex = (instrumentIndex == 63) ? 0 : instrumentIndex + 1;
	PF2 ^= 0x04;
}

void Timer0A_Init(uint32_t reloadValue)
{
    volatile uint32_t delay;
    SYSCTL_RCGCTIMER_R |= 0x01;			 	// activate timer0
    delay = SYSCTL_RCGCTIMER_R; 			// allow time to finish activating
    TIMER0_CTL_R &= ~TIMER_CTL_TAEN;		// disable timer0A during setup
    TIMER0_CFG_R = 0; 						// configure for 32-bit timer mode
	
    // configure for periodic mode
    TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
    TIMER0_TAILR_R = reloadValue; 			// start value for 1 Hz interrupts
    TIMER0_IMR_R |= TIMER_IMR_TATOIM; 		// enable timeout (rollover) interrupt
    TIMER0_ICR_R = TIMER_ICR_TATOCINT; 		// clear timer0A timeout flag
    TIMER0_CTL_R |= TIMER_CTL_TAEN; 		// enable timer0A 32-b, periodic, interrupts
    
    // Timer0A=priority 2
    NVIC_PRI4_R = (NVIC_PRI4_R & 0x00FFFFFF) | 0x40000000; 	// top 3 bits
    NVIC_EN0_R = 1 << 19; 									// enable interrupt 19 in NVIC
}

//used for quarter notes, eight notes, etc
void Timer0A_Handler(void)
{
	NoteIndex = (NoteIndex + 1) % Songs[CurrentSongIndex].length;
	// If we reach the end of a song, go to the next.
	if (NoteIndex == 0)
		CurrentSongIndex = (CurrentSongIndex + 1) % NumberOfSongs;
	const Note* note = &Songs[CurrentSongIndex].notes[NoteIndex];
	CurrentNoteFrequency = note->Frequency;
	uint32_t duration = note->Duration;
	if (CurrentTempo == HalfSpeed)
		duration *= 2;
	else if (CurrentTempo == DoubleSpeed)
		duration /= 2;
	TIMER0_TAILR_R = duration;
	TIMER0_ICR_R = TIMER_ICR_TATOCINT; // acknowledge timer0A timeout
}

//Not being used right now
void Timer1_Init(uint32_t reloadValue)
{
    volatile uint32_t delay;
    SYSCTL_RCGCTIMER_R |= 0x02; 	// 0) activate TIMER1
    delay = SYSCTL_RCGCTIMER_R; 	// allow time to finish activating
    TIMER1_CTL_R = 0x00000000; 		// 1) disable TIMER1A during setup
    TIMER1_CFG_R = 0x00000000; 		// 2) configure for 32-bit mode
    TIMER1_TAMR_R = 0x00000002; 	// 3) configure for periodic mode, down-count
    TIMER1_TAILR_R = reloadValue; 	// 4) reload value
    TIMER1_TAPR_R = 0; 				// 5) bus clock resolution
    TIMER1_CTL_R = 0x00000001; 		// 10) enable TIMER1A
}

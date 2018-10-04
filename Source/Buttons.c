// ******** Buttons.c **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 9/18/18
// Description: File for button functionality 
// Lab Number: Lab05
// TA: Zee Lv
// Date of last revision: 9/19/2018
// Hardware Configuration: N/A

#include "Buttons.h"
#include "MusicLogic.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

#define PLAY_PAUSE_SWITCH 	0x8
#define REWIND_SWITCH		0x4
#define INSTRUMENTS_SWITCH 	0x2
#define TEMPO_SWITCH	 	0x1
#define PF2 				(*((volatile uint32_t*)0x40025010))
#define NVIC_PRIORITY_5 	(NVIC_PRI1_R & 0xFFFFFF00) | 0x000000E0

void Buttons_Init(void)
{                      
	GPIO_PORTB_DIR_R &= ~0x0F;        // Set dir to input 0-3
	GPIO_PORTB_AFSEL_R &= ~0x0F;      // disable alt funct
	GPIO_PORTB_DEN_R |= 0x0F;         // enable digital I/O
	GPIO_PORTB_PCTL_R &= ~0x000F0000; // configure PF4 as GPIO
	GPIO_PORTB_AMSEL_R = 0;           // disable analog functionality on PF
	GPIO_PORTB_IS_R &= ~0x0F;         // is edge-sensitive
	GPIO_PORTB_IBE_R &= ~0x0F;        // PF4 is not both edges
	GPIO_PORTB_IEV_R |= ~0x0F;        // PF4 rising edge event
	GPIO_PORTB_ICR_R = 0x0F;          // clear flag
	GPIO_PORTB_IM_R |= 0x0F;          // arm interrupt on PF4 *** No IME bit as mentioned in Book ***
	NVIC_PRI1_R = NVIC_PRIORITY_5;    // (g) priority 5
	NVIC_EN0_R = 0x00000002;          // (h) enable interrupt 30 in NVIC
}

void GPIOPortB_Handler(void){
	uint8_t flags = (GPIO_PORTB_MIS_R & 0x0F);
	GPIO_PORTB_ICR_R = 0x0F;      // acknowledge flag

	switch(flags){
		case PLAY_PAUSE_SWITCH:
			MusicPlayerShouldUpdate(PlayPause);
			break;
		case REWIND_SWITCH:
			MusicPlayerShouldUpdate(Rewind);
			break;
		case INSTRUMENTS_SWITCH:
			MusicPlayerShouldUpdate(ChangeInstrument);
			break;
		case TEMPO_SWITCH:	
			MusicPlayerShouldUpdate(ChangeTempo);
			break;
		default:	
			break; //multiple buttons pressed, dont do anything
	}
	
	PF2 ^= 0x04;
}

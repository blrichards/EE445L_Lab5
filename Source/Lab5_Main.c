// ******** Lab3_Main.c **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 9/18/18
// Description: Main file for Lab 3
// Lab Number: Lab05
// TA: Zee Lv
// Date of last revision: 9/19/2018
// Hardware Configuration: N/A

#include "Buttons.h"
#include "Debug.h"
#include "PLL.h"
#include "SPI.h"
#include "ST7735.h"
#include "Timer.h"
#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define PF2 (*((volatile uint32_t*)0x40025010))
#define PF1 (*((volatile uint32_t*)0x40025008))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void); // Enable interrupts
long StartCritical(void); // previous I bit, disable interrupts
void EndCritical(long sr); // restore I bit to previous value
void WaitForInterrupt(void); // low power mode

int main(void)
{
	PLL_Init(Bus80MHz); // 80 MHz
    SYSCTL_RCGCGPIO_R |= 0x23;//0x22; 		// activate port F, B
	while((SYSCTL_PRGPIO_R & 0x23) == 0){};
		
    // configure PF2 as GPIO
    Debug_Init();
	Buttons_Init();
	SysTick_Init();					//for note frequency
	Timer0A_Init(79999999); 		//set to 1 sec initially for notes
	SPI_Init();
    EnableInterrupts();
	
	// NVIC_ST_CTRL_R |= 0x00000001;
	
    while (true) {
		PF1 ^= 0x02; // toggles when running in main
    }
}

// ******** Timer.h **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 9/18/18
// Description: Header file for Timer.c
// Lab Number: Lab05
// TA: Zee Lv
// Date of last revision: 9/19/2018
// Hardware Configuration: N/A

#include <stdint.h>

#ifndef TIMER_H_
#define TIMER_H_
	
void SysTick_Init(void);
void Timer0A_Init(uint32_t reloadValue);
void Timer1_Init(uint32_t reloadValue);

#endif // TIMER_H_

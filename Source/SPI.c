// ******** SPI.c **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 10/1/18
// Description: SPI Control for 
// Lab Number: Lab05
// TA: Zee Lv
// Date of last revision: 10/1/18
// Hardware Configuration: N/A

#include <stdint.h>
#include "SPI.h"
#include "tm4c123gh6pm.h"

#define PF2 (*((volatile uint32_t*)0x40025010))

/*
void SPI_Init(void) {
	SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R2;		//set SSI clock2
	//GPIO_PORTB_DIR_R |= 0xB0;
	GPIO_PORTB_AFSEL_R |= 0xB0;
	GPIO_PORTB_DEN_R |= 0xB0;					//Set PB7,5,4 to out
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0x0F00FFFF) + 0x20220000;
	GPIO_PORTB_AMSEL_R &= ~0xB0;						//Disbale analog mode
    SSI2_CR1_R &= ~SSI_CR1_SSE; 				// disable SSI
    SSI2_CR1_R &= ~SSI_CR1_MS; 					// master mode
	SSI2_CC_R = (SSI2_CC_R & ~SSI_CC_CS_M) + SSI_CC_CS_SYSPLL;
	SSI2_CPSR_R = 0;//0x02;						//SSI prescale clock divisor
	SSI2_CR0_R &= ~(0x0000FFF0);				//Clears functionality of and divisor of SSI
	SSI2_CR0_R |= 0x0F;							//sends 16 bits
	SSI2_DR_R = 0;								//Read/write to read/transmit over SSI
	SSI2_CR1_R |= SSI_CR1_SSE;							//Enables SSI
}


void SPI_Output(uint16_t value) {
	while((SSI2_SR_R & 0x02) == 0){};			//check to see if transmit FIFO is full
	SSI2_DR_R = value;							//Transmit SSI value
}
*/

void SPI_Init(void) {
	SYSCTL_RCGCSSI_R |= 0x01;
	SYSCTL_RCGCGPIO_R |= 0x01;
	while((SYSCTL_PRGPIO_R & 0x01) == 0){};
	GPIO_PORTA_AFSEL_R |= 0x2C;
	GPIO_PORTA_DEN_R |= 0x2C;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFF0F00FF) + 0x00202200;
	GPIO_PORTA_AMSEL_R = 0;
	SSI0_CR1_R = 0x0;
	SSI0_CPSR_R = 0x05;
	SSI0_CR0_R &= ~(0x0000FFF0);
	SSI0_CR0_R |= 0x0F;
	SSI0_DR_R = 0x0;
	SSI0_CR1_R |= 0x02;
}

void SPI_Output(uint16_t value) {
	while((SSI0_SR_R & 0x02) == 0){};
	SSI0_DR_R = (value & 0x0FFF) | 0xC000;
	PF2 ^= 0x04;
}

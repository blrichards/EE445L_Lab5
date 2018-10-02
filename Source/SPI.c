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

void SPI_Init(void) {
	SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R2;		//set SSI clock2
	GPIO_PORTB_AFSEL_R |= 0xF0;
	GPIO_PORTB_DEN_R |= 0xB0;					//Set PB7,5,4 to out
	GPIO_PORTB_DEN_R &= ~0x40;					
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFF0F0000) + 0x22020000;
	GPIO_PORTB_AMSEL_R = 0;						//Disbale analog mode
	SSI2_CR1_R = 0x0;							//Diables SSI/set to master
	SSI2_CPSR_R = 0x02;							//SSI prescale clock divisor
	SSI2_CR0_R &= ~(0x0000FFF0);				//Clears functionality of and divisor of SSI
	SSI2_CR0_R |= 0x0F;							//sends 16 bits
	SSI2_DR_R = 0;								//Read/write to read/transmit over SSI
	SSI2_CR1_R |= 0x02;							//Enables SSI
}


void SPI_Output(uint16_t value) {
	while((SSI0_SR_R & 0x02) == 0){};			//check to see if transmit FIFO is full
	SSI2_DR_R = value;							//Transmit SSI value
}

// ******** SPI.h **************
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 10/1/18
// Description: Header file for SPI.c
// Lab Number: Lab03
// TA: Zee Lv
// Date of last revision: 10/1/18
// Hardware Configuration: N/A

#include <stdint.h>

#ifndef SPI_H_
#define SPI_H_

void SPI_Init(void);
void SPI_Output(uint16_t value);

#endif // SPI_H_

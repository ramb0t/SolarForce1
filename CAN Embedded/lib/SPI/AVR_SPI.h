/*
 * AVR_SPI.h
 *
 *  Created on: 21 Feb 2015
 *      Author: RobThePyro
 */

#ifndef AVR_SPI_H_
#define AVR_SPI_H_

// Includes:
/*********************************************/
#include <avr/io.h>

// Defines:
/*********************************************/

// MOSI Port and Pins
#define SPI_MOSI_DDR 	DDRB
#define SPI_MOSI 		3

// MISO Port and Pins
#define SPI_MISO_PORT 	PORTB
#define SPI_MISO_DDR  	DDRB
#define SPI_MISO 		4

// SCK Port and Pins
#define SPI_SCK_DDR 	DDRB
#define SPI_SCK 		5

// SS Port and Pins
#define SPI_SS_DDR 		DDRB
#define SPI_SS_PORT 	PORTB
#define SPI_SS 			2

// Functions:
/*********************************************/

void SPI_Init(void);
uint8_t spi_putc(uint8_t);

uint8_t SPI_WriteRead(uint8_t);
uint8_t SPI_Read();
void SPI_Write(uint8_t);


#endif /* AVR_SPI_H_ */

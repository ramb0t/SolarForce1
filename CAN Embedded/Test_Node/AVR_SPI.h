/*
 * AVR_SPI.h
 *
 *  Created on: 21 Feb 2015
 *      Author: RobThePyro
 */

#ifndef AVR_SPI_H_
#define AVR_SPI_H_

// Includes:

#include <avr/io.h>

// Defines:

#define SPI_SS_DDR DDRB
#define SPI_SS_PORT PORTB
#define SPI_SS 2

#define SPI_MOSI_DDR DDRB
#define SPI_MOSI 3
#define SPI_MISO_PORT PORTB
#define SPI_MISO 4
#define SPI_SCK_DDR DDRB
#define SPI_SCK 5

// Functions:

void SPI_Init(void);
uint8_t spi_putc(uint8_t);


#endif /* AVR_SPI_H_ */

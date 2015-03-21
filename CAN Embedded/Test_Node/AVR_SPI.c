/*
 * AVR_SPI.c
 *
 *  Created on: 21 Feb 2015
 *      Author: RobThePyro
 */

#include "AVR_SPI.h"

void SPI_Init(void){

	SPI_SS_DDR |= (1 << SPI_SS); /* set SS output */
	SPI_SS_PORT |= (1 << SPI_SS); /* start off not selected (high) */
	SPI_MOSI_DDR |= (1 << SPI_MOSI); /* output on MOSI */
	SPI_MISO_PORT |= (1 << SPI_MISO); /* pullup on MISO */
	SPI_SCK_DDR |= (1 << SPI_SCK); /* output on SCK */

	SPCR |= (1 << MSTR); /* clockmaster */
	SPCR |= (1 << SPE); /* enable */
	SPSR = ( 1 <<SPI2X ) ; /* fosc = fclk / 2 */

}

uint8_t spi_putc ( uint8_t data )
{
	// The byte to send
	SPDR = data;

	// Wait until the byte is sent!
	while ( ! ( SPSR & ( 1 <<SPIF ) ) );

	// Return the register with rx loop data back
	return SPDR;
}


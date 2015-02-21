/*
 * main.c
 *
 *  Created on: 21 Feb 2015
 *      Author: RobThePyro
 */
#include "main.h"

// -------- Global Variables --------- //


// -------- Functions --------- //


int main(void) {
	// -------- Inits --------- //
	SPI_Init(); // setup SPI

	DDRB  |= 1<<PB1; // led output
	mcp2515_init();



	// Create a new message struct
	CANMessage message;

	// Fill struct with data
	message. id = 0x0000;
	message. rtr = 0 ;
	message. length = 2 ;
	message. data [ 0 ] = 0x04;
	message. data [ 1 ] = 0xf3;


	// clock_prescale_set(clock_div_1); /* CPU Clock: 8 MHz */
	//initUSART();
	//printString("OK");

	// ------ Event loop ------ //
		while (1) {
			_delay_ms(100);
			// Send message every 100mS
			can_send_message ( &message ) ;

		} /* End event loop */
	return (0); /* This line is never reached */
}

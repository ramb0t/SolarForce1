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
	CANMessage messageOn;
	CANMessage messageOff;

	// Fill struct with data
	messageOn. id = 0x0000;
	messageOn. rtr = 0 ;
	messageOn. length = 2 ;
	messageOn. data [ 0 ] = 0x04;
	messageOn. data [ 1 ] = 0x01;

	// Fill struct with data
	messageOff. id = 0x0000;
	messageOff. rtr = 0 ;
	messageOff. length = 2 ;
	messageOff. data [ 0 ] = 0x04;
	messageOff. data [ 1 ] = 0x02;


	// clock_prescale_set(clock_div_1); /* CPU Clock: 8 MHz */
	//initUSART();
	//printString("OK");

	// ------ Event loop ------ //
		while (1) {
			_delay_ms(500);
			can_send_message ( &messageOn ) ; // turn led on
			_delay_ms(500);
			can_send_message ( &messageOff ) ; // turn led off

		} /* End event loop */
	return (0); /* This line is never reached */
}

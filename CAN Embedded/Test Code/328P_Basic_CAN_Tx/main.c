/*
 * main.c
 *
 *  Created on: 21 Feb 2015
 *      Author: RobThePyro
 */
#include "main.h"
// Project Specific
#include "CAN.h"
#include "AVR_SPI.h"

// -------- Global Variables --------- //


// -------- Functions --------- //


int main(void) {
	// -------- Inits --------- //
	SPI_Init(); // setup SPI

	DDRB  |= 1<<PB1; // led output
	CAN_Init(CAN_125KBPS_16MHZ);



	// Create a new message struct
	CANMessage messageOn;
	CANMessage messageOff;

	// Fill struct with data
	messageOn. id = 0x0007;
	messageOn. rtr = 0 ;
	messageOn. length = 2 ;
	messageOn. data [ 0 ] = 0x04;
	messageOn. data [ 1 ] = 0x01;

	// Fill struct with data
	messageOff. id = 0x0101;
	messageOff. rtr = 0 ;
	messageOff. length = 3 ;
	messageOff. data [ 0 ] = 0x64;
	messageOff. data [ 1 ] = 0xAB;


	// clock_prescale_set(clock_div_1); /* CPU Clock: 8 MHz */
	//initUSART();
	//printString("OK");

	// ------ Event loop ------ //
		while (1) {
			//_delay_ms(750);
			//can_send_message ( &messageOn ) ; // turn led on
			//_delay_ms(750);
			//can_send_message ( &messageOff ) ; // turn led off
			CANMessage message;
			message.id = rand();
			message.length = (rand() / 0xfff);
			for (int i = 0; i < message.length; i++){
				message.data[i] = (rand() >> 7);
			}

			CAN_sendMessage ( &message ) ;
			_delay_ms(750);


		} /* End event loop */
	return (0); /* This line is never reached */
}

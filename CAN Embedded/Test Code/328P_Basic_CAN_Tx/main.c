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

	// Setup USART
	uart_init((UART_BAUD_SELECT((UART_BAUD_RATE),F_CPU)));
	sei();
	uart_puts("Hello! CAN Tx node has booted!! :D\n");
	// For working with strings
	char buffer[10];


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
	messageOff. data [ 1 ] = 0xABclock_prescale_set


	// (clock_div_1); /* CPU Clock: 8 MHz */
	//initUSART();
	//printString("OK");
	uint16_t i = 0;
	// ------ Event loop ------ //
		while (1) {

			//_delay_ms(750);
			//can_send_message ( &messageOn ) ; // turn led on
			//_delay_ms(750);
			//can_send_message ( &messageOff ) ; // turn led off
			CANMessage message;
			message.id = i;
			i++;
			if(i > 2047){
				i = 0;
			}
			message.length = (rand() / 0xfff);

			uart_puts("CAN Message: ID= ");
			itoa( message.id, buffer, 10);   // convert integer into string (decimal format)
			uart_puts(buffer);        // and transmit string to UART
			uart_puts(" | Len= ");
			itoa( message.length, buffer, 10);   // convert integer into string (decimal format)
			uart_puts(buffer);        // and transmit string to UART


			for (int i = 0; i < message.length; i++){
				message.data[i] = (rand() >> 7);

				char string[15] ="| D";
				itoa(i, buffer, 10);
				strcat(string, buffer);
				strcat(string, "= ");

				itoa(message.data[i], buffer, 10);
				strcat(string, buffer);
				uart_puts(string);        // and transmit string to UART
			}
			uart_puts("\n");

			CAN_sendMessage ( &message ) ;


			_delay_ms(750);


		} /* End event loop */
	return (0); /* This line is never reached */
}

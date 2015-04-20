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

	CAN_Init(CAN_125KBPS_16MHZ);

	// Setup USART
	uart_init((UART_BAUD_SELECT((UART_BAUD_RATE),F_CPU)));
	sei();
	uart_puts("Hello! CAN Tx node has booted!! :D\n");
	// For working with strings
	char buffer[10];




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

/*
 * uart_CANFunc.c
 *
 *  Created on: 01 Apr 2015
 *      Author: rambo
 */
// some fucntions to help with sending CANstuff to the uart.


#include "uart_CANFunc.h"


/*************************************************************************
Function: uart_SendCANMsg()
Purpose:  Take a CAN message, string format and pass to the uart port.
Input:    CANMessage
Returns:  None
**************************************************************************/
void uart_SendCANMsg(CANMessage* message){
	char buffer[5]; // used to hold conversions

	uart_puts("CAN Message: ID= ");

	itoa( message->id, buffer, 10);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART
	uart_puts(" | Len= ");
	itoa( message->length, buffer, 10);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART

	uart_puts(" | RTR= ");
	itoa( message->rtr, buffer, 10);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART

	for (int i = 0; i < message->length; i++){

		char string[15] ="| D";
		itoa(i, buffer, 10);
		strcat(string, buffer);
		strcat(string, "= ");

		itoa(message->data[i], buffer, 10);
		strcat(string, buffer);
		uart_puts(string);        // and transmit string to UART
	}
	uart_puts("\n");

}


/*************************************************************************
Function: uart_SendCANMsgRAW()
Purpose:  Take a CAN message, Output it 'RAW'.
Input:    CANMessage
Returns:  None
**************************************************************************/
void uart_SendCANMsgRAW(CANMessage* message){
	char buffer[5]; // used to hold conversions

	itoa( message->id, buffer, 10);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART

	uart_puts(",");
	itoa( message->rtr, buffer, 10);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART


	uart_puts(",");
	itoa( message->length, buffer, 10);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART



	for (int i = 0; i < message->length; i++){

		char string[15] =",";
		itoa(i, buffer, 10);
		strcat(string, buffer);
		itoa(message->data[i], buffer, 10);
		strcat(string, buffer);
		uart_puts(string);        // and transmit string to UART
	}
	uart_puts("\n");

}

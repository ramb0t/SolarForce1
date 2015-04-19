/*
 * uart_CANFunc.c
 *
 *  Created on: 01 Apr 2015
 *      Author: rambo
 */
// some fucntions to help with sending CANstuff to the uart.


#include "uart_CANFunc.h"

extern volatile uint32_t ms_Counter;

// HACK TEMP
uint32_t oldtime;


/*************************************************************************
Function: uart_SendCANMsg()
Purpose:  Take a CAN message, string format and pass to the uart port.
Input:    CANMessage
Returns:  None
**************************************************************************/
void uart_SendCANMsg(CANMessage* message){
	char buffer[5]; // used to hold conversions

	uart_puts("CAN Msg: ID= ");

	itoa( message->id, buffer, 10);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART
	uart_puts(" |L= ");
	itoa( message->length, buffer, 10);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART

	//uart_puts(" | RTR= ");
	//itoa( message->rtr, buffer, 10);   // convert integer into string (decimal format)
	//uart_puts(buffer);        // and transmit string to UART

	for (int i = 0; i < message->length; i++){

		char string[15] ="|D";
		itoa(i, buffer, 10);
		strcat(string, buffer);
		strcat(string, "= ");

		itoa(message->data[i], buffer, 10);
		strcat(string, buffer);
		uart_puts(string);        // and transmit string to UART
	}
	uart_puts(" |t= ");
	ultoa(ms_Counter, buffer, 10); // get the ms time'
	uart_puts(buffer);

	uart_puts(" |delT= ");
	ultoa(ms_Counter-oldtime, buffer, 10); // get the delta time
	oldtime = ms_Counter;
	uart_puts(buffer);

	uart_puts("\n");

}


/*************************************************************************
Function: uart_SendCANMsgRAW()
Purpose:  Take a CAN message, Output it 'RAW'.
Input:    CANMessage
Returns:  None
**************************************************************************/
void uart_SendCANMsgRAW(CANMessage* message){
	char buffer[50]; // used to hold conversions

	utoa( message->id, buffer, 2);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART

	//uart_puts(",");
	//itoa( message->rtr, buffer, 2);   // convert integer into string (decimal format)
	//uart_puts(buffer);        // and transmit string to UART


	uart_puts(",");
	utoa( message->length, buffer, 10);   // convert integer into string (decimal format)
	uart_puts(buffer);        // and transmit string to UART



	for (int i = 0; i < message->length; i++){

		char string[15] =",";
		// add padding zeros
		if(message->data[i] < 0x80){
			strcat(string,"0");
			if(message->data[i] < 0x40){
				strcat(string,"0");
				if(message->data[i] < 0x20){
					strcat(string,"0");
					if(message->data[i] < 0x10){
						strcat(string,"0");
						if(message->data[i] < 0x08){
							strcat(string,"0");
							if(message->data[i] < 0x04){
								strcat(string,"0");
								if(message->data[i] < 0x02){
									strcat(string,"0");
									if(message->data[i] < 0x01){
										strcat(string,"0");
										        // So Prettttyyyyyyyyyyyyyyyyy
									}

								}
							}
						}
					}
				}
			}
		}
		utoa(message->data[i], buffer, 2);
		strcat(string, buffer);
		uart_puts(string);        // and transmit string to UART
	}
	uart_puts("\n");

}

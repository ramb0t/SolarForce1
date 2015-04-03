/*
 * Display_Node.c
 *
 *  Created on: 01 Apr 2015
 *      Author: RobThePyro
 */

#include "Display_Node.h"

int main(void)
{

	SPI_Init();  //Setup SPI
	CAN_Init(CAN_125KBPS_16MHZ); // Init CAN application layer and hardware
	// Create a new message
	CANMessage message;
	// setup var to hold message status
	uint8_t rx_status = CAN_NOMSG;

	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	// enable interrupts. needed for uart.
    sei();

    uart_puts("Hello! CAN display node has booted!! :D\n");
    // For working with strings
    char buffer[10];

    // init LCD
    u8g_setup();

    while(1) {
    	rx_status = CAN_checkReceiveAvailable()();

    	if(rx_status == CAN_MSGAVAIL){
    		CAN_readMessage(&message); //gets msg from bus (pointer to the object of CanMessage type)

    		GFX_LCD_Draw(&message);

    	}
    }
}

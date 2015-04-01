/*
 * Test_Node.c
 *
 *  Created on: 21 Mar 2015
 *      Author: RobThePyro
 */


#include "Test_Node.h"

int main(void)
{

	SPI_Init();
	CAN_Init(CAN_125KBPS_16MHZ);
	// Create a new message
	CANMessage message;
	uint8_t rx_status = 0xff;


	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

    sei();

    uart_puts("Hello! CAN Test node has booted!! :D\n");
    // For working with strings
    char buffer[10];

    DDRC |= (1<<2);
    // init LCD
    u8g_setup();
    int g = 0;
    while(1) {

    	//FX_Cnt(g++);

    	rx_status = CAN_checkReceiveAvailable();

    	if(rx_status == CAN_MSGAVAIL){
    		CAN_readMessage(&message); //gets msg from bus (pointer to the object of CanMessage type)

    		GFX_LCD_Draw(&message);
    		// sends the message on the CAN interface.
    		uart_SendCANMsg(&message);

    	}
    }
}

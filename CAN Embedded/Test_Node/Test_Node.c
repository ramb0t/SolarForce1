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
	mcp2515_init();
	// Create a new message
	CANMessage message;
	uint8_t rx_status = 0xff;


	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

    sei();

    // init LCD
    u8g_setup();

    while(1) {

    	rx_status = can_get_message (&message); //gets msg from bus (pointer to the object of CanMessage type) [returns value based on result of Rx




    	if(rx_status!=0xff){
    		PORTC &= ~(1<<2);
    		GFX_LCD_Draw(message);
    		PORTC |= (1<<2);
    	}
    }
}

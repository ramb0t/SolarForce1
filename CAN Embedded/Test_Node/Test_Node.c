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


	// Init UART
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

    sei();

    uart_puts("Hello! CAN Test node has booted!! :D\n");

    // Init LCD
    u8g_setup();

    // Create Terminal State
    uint8_t Terminal_state = TERMINAL_INIT;
    // Init the Terminal
    Terminal_init();

    // Loop for all the time!
    while(1) {

    	if(uart_available()){ // UART RX data waiting
    		// Let the Terminal deal with it.
    		Terminal_read(&Terminal_state);
    	}


    	rx_status = CAN_checkReceiveAvailable();

    	if(rx_status == CAN_MSGAVAIL){
    		CAN_readMessage(&message); //gets msg from bus (pointer to the object of CanMessage type)

    		GFX_LCD_Draw(&message);
    		// sends the message on the CAN interface.
    		//uart_SendCANMsg(&message);

    	}
    }
}

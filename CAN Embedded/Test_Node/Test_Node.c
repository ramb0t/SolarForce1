/*
 * Test_Node.c
 *
 *  Created on: 21 Mar 2015
 *      Author: RobThePyro
 */


#include "Test_Node.h"

int main(void)
{

	// Init UART
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	// Enable Interrupts
	sei();

	uart_puts("USART Initialised\n");

	// Init SPI
	SPI_Init();
	uart_puts("SPI Initialised\n");

	// Init CAN
	CAN_Init(CAN_125KBPS_16MHZ);
	uart_puts("CAN Initialised\n");

    // Init LCD
    u8g_setup();
	uart_puts("LCD Initialised\n");


    uart_puts("\nHello! CAN Test node has booted!! :D\n");
    uart_puts("-------------------------------------\n");

    // Create Terminal State
    uint8_t Terminal_state = TERMINAL_INIT;
    // Init the Terminal
    Terminal_init();


	// Create a new message
	CANMessage message;
	uint8_t rx_status = 0xff;


    // Loop for all the time!
    while(1) {

    	if(uart_available()){ // UART RX data waiting
    		// Let the Terminal deal with it.
    		Terminal_read(&Terminal_state);
    	}

    	// Run the Terminal Operation
    	//Terminal_run(&Terminal_state);

    	switch (Terminal_state){
    		case (TERMINAL_INIT):

    				break;
    		case (TERMINAL_RUN):

    			break;
    		case (TERMINAL_LISTEN):
    	    	rx_status = CAN_checkReceiveAvailable();

    	    	if(rx_status == CAN_MSGAVAIL){
    	    		CAN_readMessage(&message); //gets msg from bus (pointer to the object of CanMessage type)

    	    		GFX_LCD_Draw(&message);
    	    		// sends the message on the CAN interface.
    	    		uart_SendCANMsg(&message);
    	    	}

    			break;
    		case (TERMINAL_LISTENRAW):


    	    	while(CAN_checkReceiveAvailable() == CAN_MSGAVAIL){
    	    		CAN_readMessage(&message); //gets msg from bus (pointer to the object of CanMessage type)

    	    		//GFX_LCD_Draw(&message);
    	    		// sends the message on the CAN interface.
    	    		uart_SendCANMsgRAW(&message);
    	    	}

    			break;
    		case (TERMINAL_SEND1):
    	    	message.id = 0b11100010001;
    			message.rtr = 1;
    			message.length = 0;

    			// Send the request
    			CAN_sendMessage(&message);

    			// Listen for the response
    			Terminal_state = TERMINAL_LISTENRAW;

    			break;
    		default:

    			break;
    		}

    }
}

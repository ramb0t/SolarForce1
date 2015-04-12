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
	uart_init( UART_BAUD_SELECT_DOUBLE_SPEED(UART_BAUD_RATE,F_CPU) );

	// Enable Interrupts
	sei();

	uart_puts("USART Initialised\n");

	// Init SPI
	SPI_Init();
	uart_puts("SPI Initialised\n");

	// Init CAN
	CAN_Init(CAN_125KBPS_16MHZ);
	uart_puts("CAN Initialised\n");

	// setup pin int
	CAN_setupInt0();

    // Init LCD
    //u8g_setup();
	//uart_puts("LCD Initialised\n");

	// Init LCD Backlight
	//Timer1_init();
	//OCR1A = 14;

	// Init Timer0
	Timer0_init();

	// HACK
	// LCD SCKCTL Output
	//LCD_SCKCTL_DDR |= (1<<LCD_SCKCTL);


	// /HACK


    uart_puts("\nHello! CAN Test node has booted!! :D\n");
    uart_puts("-------------------------------------\n");

    // Create Terminal State
    Terminal_state = TERMINAL_RUN;
    // Init the Terminal
    Terminal_init();


	// Create a new message
	CANMessage message;
	uint8_t rx_status = 0xff;

	uint16_t i = 0;
	// For working with strings
		char buffer[10];

	// for timing!
	extern volatile uint16_t ms_Counter;
	uint16_t oldtime = ms_Counter;
	uint16_t waittime = 1000; // delay time in ms

	BMS_init();

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
    				Terminal_init();
    				Terminal_state = TERMINAL_RUN;

    				break;
    		case (TERMINAL_RUN):

    			break;
    		case (TERMINAL_LISTEN):
//    	    	rx_status = CAN_checkReceiveAvailable();
//
//    	    	if(rx_status == CAN_MSGAVAIL){
//    	    		CAN_readMessage(&message); //gets msg from bus (pointer to the object of CanMessage type)
//
//    	    		//LCD_SELECT();
//    	    		//GFX_LCD_Draw(&message);
//    	    		//LCD_UNSELECT();
//    	    		// sends the message on the CAN interface.
//    	    		uart_SendCANMsg(&message);
//    	    	}
				if(flag == CAN_MSGAVAIL){
					// reset the flag
					flag = CAN_NOMSG;
					uart_SendCANMsg(&gMessage);
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
    			Terminal_state = TERMINAL_RUN;

    			Terminal_init();

    			// Listen for the response
    			//Terminal_state = TERMINAL_LISTENRAW;

    			break;

    		case (TERMINAL_SENDRANDOM):
				if((ms_Counter - oldtime) > waittime){
					oldtime = ms_Counter;

					message.id = i;
					i++;
					if(i > 2047){
						i = 0;
					}
					message.length = (rand() / 0xfff)+1;

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
				}
    			break;

    		case(TERMINAL_SENDBMS):
				BMS_send_fake_data();
    			Terminal_state = TERMINAL_INIT;
				break;

    		case (TERMINAL_LOOPBMS):
				if((ms_Counter - oldtime) > waittime){
					oldtime = ms_Counter;

					BMS_send_fake_data();
				}
				break;

    		default:

    			break;
    		}

    }
}

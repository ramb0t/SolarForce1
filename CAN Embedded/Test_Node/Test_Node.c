/*
 * Test_Node.c
 *
 *  Created on: 21 Mar 2015
 *      Author: RobThePyro
 */


#include "Test_Node.h"

// fixes problem?
#include "../lib/CAN/CAN_defs.h"

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
	//uint8_t rx_status = 0xff;

	uint16_t i = 0;
	// For working with strings
		char buffer[10];

	// for timing!
	extern volatile uint16_t ms_Counter;
		uint16_t oldBMSTime = ms_Counter;
		uint16_t oldSpeedTime = ms_Counter-50; // add a small offset
		uint16_t oldGyroTime = ms_Counter-75; // add a small offset
#define	waitBMSTime 1000 // delay time in ms
#define waitSpeedTime 200
#define waitGyroTime GyroPeriod

	uint8_t spd = 0;
	uint16_t Gyro_Angle = 0;

	BMS_init();
	SpeedEmu_init();

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
					if(CAN_getMessage_Buffer(&message) == CAN_OK){
						uart_SendCANMsg(&message);
					}
				}else if(flag == CAN_FAIL){
					uart_puts("that");
					CAN_getMessage_Buffer(&message);
					uart_SendCANMsg(&message);
				}

    			break;
    		case (TERMINAL_LISTENRAW):
				if(flag == CAN_MSGAVAIL){
					if(CAN_getMessage_Buffer(&message) == CAN_OK){
						// sends the message on the CAN interface.
						uart_SendCANMsgRAW(&message);
					}
				}else if(flag == CAN_FAIL){
					uart_puts("that");
					CAN_getMessage_Buffer(&message);
					uart_SendCANMsg(&message);
				}
    			break;

    		case (TERMINAL_LISTENMPPT):
				if(flag == CAN_MSGAVAIL){ // stuff in the buffer
					if(CAN_getMessage_Buffer(&message) == CAN_OK){
						if(message.rtr == 1){ // we have request to reply...
						// decode and see if it matches what we need?
						switch(message.id){  // switch to the correct reply and send it
							case (CANID_MPPTRQ1):
								MPPTEmu_SendReply(1);
							break;
							case (CANID_MPPTRQ2):
								MPPTEmu_SendReply(2);
							break;
							case (CANID_MPPTRQ3):
								MPPTEmu_SendReply(3);
							break;
							case (CANID_MPPTRQ4):
								MPPTEmu_SendReply(4);
							break;
							default:
								break;
							}

						// sends the message on the CAN interface.
						uart_SendCANMsg(&message); // this shows the MPPT request
						}
					}
				}else if(flag == CAN_FAIL){
					uart_puts("that bad thing happened");
					CAN_getMessage_Buffer(&message);
					uart_SendCANMsg(&message);
				}
    			break; //MPPT response

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
				if((ms_Counter - oldBMSTime) > waitBMSTime){
					oldBMSTime = ms_Counter;

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
    			// send 1 message
				BMS_send_fake_data();
    			// goback to submenu!
    			Terminal_state = TERMINAL_SENDSUB;
				break;



    		default:

    			break;
    		}// State Switch

    	if ((Terminal_state & TERMINAL_LOOPBMS)&0x0f){
			if((ms_Counter - oldBMSTime) > waitBMSTime){
				oldBMSTime = ms_Counter;
				BMS_send_fake_data();
			}
    	}

    	if ((Terminal_state & TERMINAL_LOOPSPEED)&0x0f){
			if((ms_Counter - oldSpeedTime) > waitSpeedTime){
				oldSpeedTime = ms_Counter;
				SpeedEmu_set_speed(spd);
				SpeedEmu_set_HESSpd(spd+1);
				SpeedEmu_set_HESRPM((int16_t)spd +100);
				SpeedEmu_set_MTSpd(spd+2);
				SpeedEmu_set_MTRPM((uint16_t)spd +200);
				spd = spd+1;
				if(spd > 250){
					spd = 0;
				}
				SpeedEmu_send_fake_data();

				// send gyro same time because that's how it works!
				Gyro_Angle = Gyro_Angle + 100;
				GyroEmu_set_AngleX(Gyro_Angle);
				GyroEmu_set_AngleY(Gyro_Angle+100);
				GyroEmu_set_AngleZ(Gyro_Angle+200);
				GyroEmu_send_fake_data();

			}
    	}



    } // while
} // main


// Int0 ISR for CAN buffer...
ISR(INT0_vect){
	CAN_fillBuffer();

}

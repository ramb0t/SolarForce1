/*
 * Display_Node.c
 *
 *  Created on: 01 Apr 2015
 *      Author: RobThePyro
 */

#include "Display_Node.h"

int main(void)
{
	// Init SPI
	SPI_Init();

	// Init CAN
	CAN_Init(CAN_125KBPS_16MHZ);
	CAN_setupPCINT0();

	// HACK
	// LCD SCKCTL Output
	LCD_SCKCTL_DDR |= (1<<LCD_SCKCTL);
	LCD_SELECT();

	// Init LCD
	u8g_setup();
	LCD_UNSELECT();

	// Init LCD Backlight
	Timer1_init();
	OCR1A = 0;
	Timer1_PWM_Off();
	OCR1A = 128;
	Timer1_PWM_On();

	// Create a new message
	CANMessage message;
	//uint8_t rx_status = 0xff;

	// Enable Interrupts
	sei();

    while(1) {
    	cli();
    	if(~(PINB & (1<<PB0))){
    		//PCIFR |= (1<<PCIF0); // fire ISR!
    		//while(CAN_checkReceiveAvailable()==CAN_MSGAVAIL){
    			CAN_fillBuffer();
    		//}

    	}
    	sei();
    	if(flag == CAN_MSGAVAIL){
    		//cli();
			if(CAN_getMessage_Buffer(&message) == CAN_OK){

				if(CAN_Decode(&message) == CAN_MSG_DECODED){
					//GFX_LCD_Draw(&message);
					// call the update routine
					GFX_LCD_DrawMain();
				}

			}
			//sei();
		}else if(flag == CAN_FAIL){
			flag = CAN_NOMSG;
		}
//    	rx_status = CAN_checkReceiveAvailable();
//
//    	if(rx_status == CAN_MSGAVAIL){
//    		CAN_readMessage(&message); //gets msg from bus (pointer to the object of CanMessage type)
//    		LCD_SELECT();
//    		GFX_LCD_Draw(&message);
//    		LCD_UNSELECT();
//
//    	}
    }
}

//CAN Message selective decoding
uint8_t CAN_Decode(CANMessage *message){
	uint8_t	decode_result;

	// Decode the message into global external vars
	switch(message->id){

	case CANID_SPEED:
		// We found a speed message!
		// get the speed value;
		gSpeed = (message->data[0]<<8)|(message->data[1]);

		// let the caller know we found something!
		decode_result = CAN_MSG_DECODED;

	break; //CANID_SPEED


	case CANID_BMS6:
		//We found BMS Msg 7
		gBMS_soc = message->data[0]; // State of charge

		// let the caller know we found something!
		decode_result = CAN_MSG_DECODED;

	break; //CANID_BMS6

	case CANID_BMS3:
		gBMS_PackVoltage = (message->data[0]<<8)|(message->data[1]);

		// let the caller know we found something!
		decode_result = CAN_MSG_DECODED;
	break;

	default:
		// We didn't find any message we are looking for...
		decode_result = CAN_NODECODE;
	break;
	}

	// Let the caller know if we found something useful
	return decode_result;

}

ISR(PCINT0_vect){
	//LCD_UNSELECT();
	CAN_fillBuffer();
	//LCD_SELECT();

}

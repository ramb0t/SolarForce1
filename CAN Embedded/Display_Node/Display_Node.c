/*
 * Display_Node.c
 *
 *  Created on: 01 Apr 2015
 *      Author: RobThePyro
 */

#include "Display_Node.h"

int main(void)
{
	// HACK
	// LCD SCKCTL Output
	LCD_SCKCTL_DDR |= (1<<LCD_SCKCTL);
	LCD_UNSELECT();				// Disable the sck line of LCD to bypass ST7920 bug

	// Init SPI
	SPI_Init();

	// Init CAN
	CAN_Init(CAN_125KBPS_16MHZ); // Setup CAN Bus with our desired speed
	CAN_setupPCINT0();			 // Setup CAN Message buffer using PCINT ISR

	// Init LCD
	LCD_SELECT();				// Enable the sck line of LCD to bypass ST7920 bug
	u8g_setup();				// Call u8glib setup for the LCD
	LCD_UNSELECT();				// Disable sck of LCD to prevent crap being displayed when
								// Talking to other things on SPI
	// Init LCD Backlight
	Timer1_init();				// Setup the timer for PWM
	LCD_BackLight = 64;		// Set the default backlight value
	Timer1_PWM_On();			// Turn backlight on

	// Create a new message
	CANMessage message;

	// Enable Interrupts
	sei();

	// Loop for all the time ever!!! (Hopefully...)
    while(1) {
    	// If the int pin is held low then we wont have an ISR!
    	// Disable the interrupts and process all outstanding buffer calls
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

	case CANID_BMS3:
		gBMS_PackVoltage = (message->data[0]<<8)|(message->data[1]);

		// let the caller know we found something!
		decode_result = CAN_MSG_DECODED;
	break; //CANID_BMS3

	case CANID_BMS4:
		gBMS_PackCurrent = (message->data[0]<<8)|(message->data[1]);

		// let the caller know we found something!
		decode_result = CAN_MSG_DECODED;
	break; //CANID_BMS4

	case CANID_BMS6:
		gBMS_soc = message->data[0]; // State of charge

		// let the caller know we found something!
		decode_result = CAN_MSG_DECODED;

	break; //CANID_BMS6

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



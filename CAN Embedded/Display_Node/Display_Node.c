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
	flagUpdateLCD = TRUE; 		// Signal that an update is needed;

	// Init LCD Backlight
	Timer1_init();				// Setup the timer for PWM
	LCD_BackLight = 64;		// Set the default backlight value
	Timer1_PWM_On();			// Turn backlight on

	// Init Timer0 for mS Counter
	Timer0_init();

	// Init Hardware
	IOInit();

	// Create a new message
	CANMessage message;

	// Enable Interrupts
	sei();

	// Loop for all the time ever!!! (Hopefully...)
    while(1) {
    	// If the int pin is held low then we wont have an ISR!
    	// Disable the interrupts and process all outstanding buffer calls
    	//cli();
    	//while(~CHECKBIT(PINB,PB0))
    	//{
    	//	CAN_fillBuffer();
    	//}
    	//sei();

    	// Check if there are any messages in the buffer, loop on more messages
    	while(flag == CAN_MSGAVAIL){
    		// Fetch a message and if valid, decode it
			if(CAN_getMessage_Buffer(&message) == CAN_OK){
				// Decode a message and if a field of importance is found, signal LCD update
				if(CAN_Decode(&message) == CAN_MSG_DECODED){
					// Set the LCD update flag
					flagUpdateLCD = TRUE;
				}
			// no valid message, reset the CAN Buffer flag ?
			//TODO: There might be a logic fail here that leads to an overflow... must check..
			}else if(flag == CAN_FAIL){
				flag = CAN_NOMSG;
			}
			// Improve buffer performance?
			//cli();
			//if(~CHECKBIT(PINB,PB0))
			//{
			//	CAN_fillBuffer();
			//}
			//sei();
    	}

    	// lockout for at least 10 mS after last interrupt
    	if(gMilliSecTick - int_mS > 9){
			// If an LCD update is needed, then do it!
			if(flagTimerUpdateLCD == TRUE && flagUpdateLCD == TRUE){
				// Call the update function
				LED_ON(LED_1);
				GFX_LCD_DrawMain();
				LED_OFF(LED_1);
				// reset the flag
				flagUpdateLCD = FALSE;
				flagTimerUpdateLCD = FALSE;
			}
    	}



    } // FOREVER LOOP :0
} // Life...


// Sets up the IO...
void 	IOInit(void){
	// LEDs Outputs
	LED_DDR |= (1<<LED_1)|(1<<LED_2);
	LED_ON(LED_1);
	LED_OFF(LED_2);

	// Btn inputs
	BTN_DDR &= ~((1<<BTN_1)|(1<<BTN_2)|(1<<BTN_3)|(1<<BTN_4));
	// Btn Pullups
	BTN_PORT |= (1<<BTN_1)|(1<<BTN_2)|(1<<BTN_3)|(1<<BTN_4);


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

	case CANID_BMS2:
		gBMS_Flags = message->data[3];

		// let the caller know we found something!
		decode_result = CAN_MSG_DECODED;
	break; //CANID_BMS2

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

	case CANID_BMS7:
		gBMS_Temp = message->data[0]; // Average Temp

		// let the caller know we found something!
		decode_result = CAN_MSG_DECODED;

	break; //CANID_BMS7


	default:
		// We didn't find any message we are looking for...
		decode_result = CAN_NODECODE;
	break;
	}

	// Let the caller know if we found something useful
	return decode_result;

}

// CAN Interrupt ISR!
ISR(PCINT0_vect){

	LED_ON(LED_2);
	CAN_fillBuffer();
	int_mS = gMilliSecTick;
	LED_OFF(LED_2);

}



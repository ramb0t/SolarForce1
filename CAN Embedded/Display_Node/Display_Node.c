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


				GFX_LCD_Draw(&message);

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

ISR(PCINT0_vect){
	//LCD_UNSELECT();
	CAN_fillBuffer();
	//LCD_SELECT();

}

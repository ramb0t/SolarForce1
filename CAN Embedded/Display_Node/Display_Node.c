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

	// HACK
	// LCD SCKCTL Output
	LCD_SCKCTL_DDR |= (1<<LCD_SCKCTL);
	LCD_SELECT();

	// Init LCD
	u8g_setup();
	LCD_UNSELECT();

	// Init LCD Backlight
	Timer1_init();
	OCR1A = 128;

	// Create a new message
	CANMessage message;
	uint8_t rx_status = 0xff;

	// Enable Interrupts
	sei();

    while(1) {
    	rx_status = CAN_checkReceiveAvailable();

    	if(rx_status == CAN_MSGAVAIL){
    		CAN_readMessage(&message); //gets msg from bus (pointer to the object of CanMessage type)
    		LCD_SELECT();
    		GFX_LCD_Draw(&message);
    		LCD_UNSELECT();

    	}
    }
}

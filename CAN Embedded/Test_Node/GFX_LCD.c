
#include "GFX_LCD.h"
#include <stdio.h>
#include <stdlib.h>

u8g_t u8g;

void u8g_setup(void)
{
  /*
    Test Envionment 1, ATMEGA and DOGM132
    CS: PORTB, Bit 2
    A0: PORTB, Bit 1
    SCK: PORTB, Bit 5
    MOSI: PORTB, Bit 3
  */
  //u8g_InitSPI(&u8g, &u8g_dev_st7565_dogm132_sw_spi, PN(1, 5), PN(1, 3), PN(1, 2), PN(1, 1), U8G_PIN_NONE);

  /*
    Test Envionment 2, ATMEGA and Seeedstudio 96x96 OLED via I2C
    SCL: Port C, Bit 5
    SDA: Port C, Bit 4
  */

  /* activate pull-up, set ports to output, init U8glib */
  //u8g_SetPinInput(PN(2,5)); u8g_SetPinLevel(PN(2,5), 1); u8g_SetPinOutput(PN(2,5));
  //u8g_SetPinInput(PN(2,4)); u8g_SetPinLevel(PN(2,4), 1); u8g_SetPinOutput(PN(2,4));
  //u8g_InitI2C(&u8g, &u8g_dev_ssd1327_96x96_gr_i2c, U8G_I2C_OPT_NONE);
  //u8g_InitI2C(&u8g, &u8g_dev_ssd1306_128x64_i2c, U8G_I2C_OPT_NONE);


  /*
    Test Envionment 3, ATMEGA and NHD 192x32 ST7920 special SPI
    R/W, MOSI, Red: 	Port C, Bit 5
    RS, CS, Yellow: 	Port C, Bit 4
    EN, SCK, Green:	Port C, Bit 3
    Arguments for u8g_InitSPI are: SCK, MOSI, CS, A0, Reset
      A0 and Reset are not used.
  */
   //u8g_InitSPI(&u8g, &u8g_dev_st7920_128x64_sw_spi, PN(2, 0), PN(2, 1), PN(2, 2), U8G_PIN_NONE, U8G_PIN_NONE);
   u8g_InitHWSPI(&u8g, &u8g_dev_st7920_128x64_hw_spi, PN(2, 2), U8G_PIN_NONE, U8G_PIN_NONE);

   u8g_DrawStr(&u8g, 5, 15, "Hello! ");

}

void GFX_LCD_Draw(CANMessage message){
	u8g_FirstPage(&u8g);
	do
	{
		draw(message);
	} while ( u8g_NextPage(&u8g) );
}

void draw(CANMessage message){
	char buf[10]; // used for forming strings to pass to the display ??

	// ID
	itoa(message.id, buf, 10);
	u8g_DrawStr(&u8g, 5, 15, "ID= ");
	u8g_DrawStr(&u8g, 25, 15, buf);

	// L
	itoa(message.length, buf, 10);
	u8g_DrawStr(&u8g, 5, 25, "Length= ");
	u8g_DrawStr(&u8g, 25, 25, buf);

	// D0
	if(message.length > 0){
		itoa(message.data[0], buf, 10);
		u8g_DrawStr(&u8g, 5, 35, "D0= ");
		u8g_DrawStr(&u8g, 25, 35, buf);
	}
	// D1
	if(message.length > 1){
		itoa(message.data[1], buf, 10);
		u8g_DrawStr(&u8g, 5, 15, "ID= ");
		u8g_DrawStr(&u8g, 5, 15, buf);
	}
	// D2
	if(message.length > 2){
		itoa(message.data[2], buf, 10);
		u8g_DrawStr(&u8g, 5, 15, "ID= ");
		u8g_DrawStr(&u8g, 5, 15, buf);
	}
	// D3
	if(message.length > 3){
		itoa(message.data[3], buf, 10);
		u8g_DrawStr(&u8g, 5, 15, "ID= ");
		u8g_DrawStr(&u8g, 5, 15, buf);
	}
	// D4
	if(message.length > 4){
		itoa(message.data[4], buf, 10);
		u8g_DrawStr(&u8g, 5, 15, "ID= ");
		u8g_DrawStr(&u8g, 5, 15, buf);
	}
	// D5
	if(message.length > 5){
		itoa(message.data[5], buf, 10);
		u8g_DrawStr(&u8g, 5, 15, "ID= ");
		u8g_DrawStr(&u8g, 5, 15, buf);
	}
	// D6
	if(message.length > 6){
		itoa(message.data[6], buf, 10);
		u8g_DrawStr(&u8g, 5, 15, "ID= ");
		u8g_DrawStr(&u8g, 5, 15, buf);
	}
	// D7
	if(message.length > 7){
		itoa(message.data[7], buf, 10);
		u8g_DrawStr(&u8g, 5, 15, "ID= ");
		u8g_DrawStr(&u8g, 5, 15, buf);
	}
}

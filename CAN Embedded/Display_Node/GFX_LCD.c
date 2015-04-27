
#include "GFX_LCD.h"
//#include "../lib/CAN/CAN_defs.h"

#define DEBUG

u8g_t u8g;

extern volatile uint8_t CAN_Rx_Head;
extern volatile uint8_t CAN_Rx_Tail;

void u8g_setup(void)
{
	// Init CS pin
	GFX_CS_DDR |= (1<<GFX_CS_BIT);
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
	//GFX_SELECT();
	u8g_InitHWSPI(&u8g, &u8g_dev_st7920_128x64_hw_spi, PN(3, 7), U8G_PIN_NONE, PN(3,4));
   //u8g_Init8Bit(&u8g, &u8g_dev_ks0108_128x64, PN(1, 2), PN(1, 1), PN(1, 0), PN(3, 7), PN(3, 6), PN(3, 5), PN(3, 4), PN(3, 3), PN(2, 5), PN(2, 1), PN(2, 0), PN(2,2), PN(2, 3), U8G_PIN_NONE);

   //U8GLIB_KS0108_128(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw [, reset])u8g_dev_ks0108_128x64
	u8g_Begin(&u8g);
   u8g_FirstPage(&u8g);
   u8g_prepare();
   	do
   	{

   	    u8g_DrawStr(&u8g, 5, 15, "Hello! Welcome to ");
   	    u8g_DrawStr(&u8g, 5, 25, "the CAN Display Node ");
   	} while ( u8g_NextPage(&u8g) );



}

void u8g_prepare(void) {
  u8g_SetFont(&u8g, u8g_font_6x10);
  u8g_SetFontRefHeightExtendedText(&u8g);
  u8g_SetDefaultForegroundColor(&u8g);
  u8g_SetFontPosTop(&u8g);
  u8g_SetRot180(&u8g);
}


void GFX_LCD_Draw(CANMessage* message){

	cli();
	LCD_SELECT();
	u8g_FirstPage(&u8g);
	//u8g_prepare();
	do
	{
		draw(message);

	} while ( u8g_NextPage(&u8g) );
	LCD_UNSELECT();
	sei();
}

void GFX_LCD_DrawMain(void){

	// Generate strings for each field?
	cli();
	LCD_SELECT();
	u8g_FirstPage(&u8g);
	do
	{
		switch(Screen){ // select the code for the current active screen
		case SCREEN_MAIN:
			drawMain();
		break;
		case SCREEN_SPD:
			drawSpd();
		break;
		case SCREEN_MPPT:
			drawMPPT();
		break;
		default:
			drawMain();
		break;
		} // Switch

	} while ( u8g_NextPage(&u8g) );
	LCD_UNSELECT();
	sei();
}


void drawSpd(){
	char buf[10]; // used for forming strings to pass to the display ??
	char string[15];

	// Set The Font
	u8g_SetFont(&u8g, u8g_font_freedoomr25n);
	u8g_SetFontRefHeightExtendedText(&u8g);
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_SetFontPosTop(&u8g);

	// Draw a Frame
	u8g_DrawHLine(&u8g, 0,30,65);
	u8g_DrawHLine(&u8g, 0,31,65);
	u8g_DrawVLine(&u8g, 65,0,64);
	//u8g_DrawFrame(&u8g,0,0,64,32);

	// Draw the Speed
	utoa(gSpeed_MTSpd, buf, 10);
	u8g_DrawStr(&u8g, 3, 4, buf);

	// Change the font
	u8g_SetFont(&u8g, u8g_font_5x8);
	u8g_SetFontPosTop(&u8g);

	// Title:
	u8g_DrawStr(&u8g, 67, 1, "Speed Node:");

	// Draw AVGSpd
	utoa(gSpeed, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"AVGSPD:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 67, 10, string);

	// Draw HESSPD
	utoa(gSpeed_HESSpd, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"HESSPD:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 67, 19, string);

	// Draw HESRPM
	utoa(gSpeed_HESRPM, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"HESRPM:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 67, 28, string);

	// Draw MTSPD
	utoa(gSpeed_MTSpd, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"MTSPD:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 67, 37, string);

	// Draw MTRPM
	utoa(gSpeed_MTRPM, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"MTRPM:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 67, 46, string);

	// Draw MTSPD
	utoa(gSpeed_status, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"status:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 67, 55, string);

	u8g_DrawStr(&u8g, 0, 35, "Gyro:");

	// Draw AngleTHE  ROLL
	ltoa(gGyro_AngleTHE, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"Roll:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 0, 44, string);

	// Draw AngleSI
	ltoa(gGyro_AngleSI, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"Pitch:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 0, 53, string);

	// Draw AnglePHI
	//ltoa(gGyro_AnglePHI, buf, 10);
	//memset(string, 0, sizeof string);
	//strcat(string,"P:");
	//strcat(string,buf);
	//u8g_DrawStr(&u8g, 0, 53, string);

}


void drawMain(){
	char buf[10]; // used for forming strings to pass to the display ??
	char string[15];

	// Set The Font
	u8g_SetFont(&u8g, u8g_font_freedoomr25n);
	u8g_SetFontRefHeightExtendedText(&u8g);
	u8g_SetDefaultForegroundColor(&u8g);
	u8g_SetFontPosTop(&u8g);

	// Draw a Frame
	u8g_DrawHLine(&u8g, 0,30,65);
	u8g_DrawHLine(&u8g, 0,31,65);
	u8g_DrawVLine(&u8g, 65,0,64);
	//u8g_DrawFrame(&u8g,0,0,64,32);

	// Draw the Speed
	utoa(gSpeed_MTSpd, buf, 10);
	u8g_DrawStr(&u8g, 3, 4, buf);

	// Change the font
	u8g_SetFont(&u8g, u8g_font_6x10);
	u8g_SetFontPosTop(&u8g);

	// Draw Power In / Power Out
	memset(string, 0, sizeof string);
	strcat(string,"P:");

	// First Calculate the power: P = V.I
	int32_t packPower = gBMS_PackVoltage ;
	packPower = packPower * gBMS_PackCurrent;

	if(packPower > 0){
		strcat(string,"+");
	}
	if(packPower >=1000 || packPower <=-1000){ // We need to go to kW
		int16_t  iPackPower = packPower / 1000; // Get kW ints
		uint16_t rPackPower = packPower % 1000; // Get kW dec
		if(packPower < 0){ // need to flip the sign of the remainder... twos comp?
			rPackPower = ~rPackPower + 1;
		}
		itoa(iPackPower, buf, 10);
		strcat(string,buf);
		strcat(string,".");
		// Sort out Zeros etc
		if(rPackPower < 100){
			strcat(string,"0");
			if(rPackPower < 10){
				strcat(string,"0");
			}
		}
		utoa(rPackPower, buf, 10);
		strcat(string,buf);
		strcat(string,"kW");
	}else{
		itoa(packPower, buf, 10);
		strcat(string,buf);
		strcat(string,"W");
	}
	// Finally draw the power
	u8g_DrawStr(&u8g, 0, 32, string);

	// Lets show the temp?
	// Draw Temp
//	itoa(AVR_Temp, buf, 10);
//	memset(string, 0, sizeof string);
//	strcat(string,"CPUTmp:");
//	strcat(string,buf);
//	strcat(string,"'C");
//	u8g_DrawStr(&u8g, 0, 42, string);

	// Change the font
	u8g_SetFont(&u8g, u8g_font_5x8);
	u8g_SetFontPosTop(&u8g);

	// Draw Pack Voltage
	utoa(gBMS_PackVoltage, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"Volt:");
	strcat(string,buf);
	strcat(string,"V");
	u8g_DrawStr(&u8g, 67, 1, string);

	// Draw Pack Current
	itoa(gBMS_PackCurrent, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"Curr:");
	strcat(string,buf);
	strcat(string,"A");
	u8g_DrawStr(&u8g, 67, 10, string);

	// Draw Temp
	itoa(gBMS_Temp, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"Temp:");
	strcat(string,buf);
	strcat(string,"'C");
	u8g_DrawStr(&u8g, 67, 19, string);

	// Draw HLIM
	if(gBMS_Flags & BMSFLAG_HLIM){
		u8g_DrawStr(&u8g, 67, 27, "HLIM!");
	}
	if(gBMS_Flags & BMSFLAG_LLIM){
		u8g_DrawStr(&u8g, 67, 27, "LLIM!");
	}

	// Fault Condition! Power cycle needed?
	if((gBMS_State & BMSSTATE_FAULT) || (gBMS_State & BMSSTATE_RFAULT)){
		u8g_DrawStr(&u8g, 67, 35, "FAULT!");
		// Prob wise to draw the stored fault code byte?
		utoa(gBMS_Faults,buf,2);
		u8g_DrawStr(&u8g, 67, 43, buf);
	}

	// Warnings!
	if(gBMS_Warnings){
		u8g_DrawStr(&u8g, 67, 50, "Warning!");
		// Prob wise to draw the stored warning code byte?
		utoa(gBMS_Warnings,buf,2);
		u8g_DrawStr(&u8g, 67, 57, buf);
	}

	// Draw SOC Bar
	u8g_DrawVLine(&u8g, 120,0,50);
	u8g_DrawHLine(&u8g, 114,0,6);
	u8g_DrawHLine(&u8g, 114,49,6);
	// Draw the bar graph
	u8g_DrawBox(&u8g, 122,50-(gBMS_soc/2)-1,6,(gBMS_soc/2)+1);

	// write BMS SOC Label
	u8g_SetFont(&u8g, u8g_font_5x7);
	u8g_SetFontPosTop(&u8g);
	utoa(gBMS_soc, buf, 10);
	strcat(buf,"%");
	u8g_DrawStr(&u8g, 114, 50, buf);
	u8g_SetFontPosBottom(&u8g);
	u8g_DrawStr(&u8g, 114, 65, "SOC");


	// write BMS volt Label
	//u8g_DrawStr(&u8g, 66, 21, "BMS Volts:");
	//utoa(gBMS_PackVoltage, buf, 10);
	//strcat(buf,"V");
	//u8g_DrawStr(&u8g, 66, 31, buf);

}

void drawMPPT(){
	char buf[10]; // used for forming strings to pass to the display ??
	char string[15];

	// Set The Font
//	u8g_SetFont(&u8g, u8g_font_freedoomr25n);
//	u8g_SetFontRefHeightExtendedText(&u8g);
//	u8g_SetDefaultForegroundColor(&u8g);
//	u8g_SetFontPosTop(&u8g);

	// Draw a Frame
	//u8g_DrawHLine(&u8g, 0,30,65);
	//u8g_DrawHLine(&u8g, 0,31,65);
	u8g_DrawVLine(&u8g, 65,0,64);
	//u8g_DrawFrame(&u8g,0,0,64,32);

	// Draw the Speed
//	utoa(gSpeed, buf, 10);
//	u8g_DrawStr(&u8g, 3, 4, buf);

	// Change the font
	u8g_SetFont(&u8g, u8g_font_5x8);
	u8g_SetFontPosTop(&u8g);

	u8g_DrawStr(&u8g, 0, 1, "MPPT1 Data:");

	// Draw MPPT1 Status
	utoa(gCANVars.MPPT1_Status, buf, 2);
	memset(string, 0, sizeof string);
	strcat(string,"1S:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 0, 10, string);

	// Draw MPPT1 Vin
	utoa(gCANVars.MPPT1_Vin, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"1Vin:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 0, 19, string);

	// Draw MPPT1 Iin
	utoa(gCANVars.MPPT1_Iin, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"1Iin:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 0, 28, string);

	// Draw MPPT1 Vout
	utoa(gCANVars.MPPT1_Vout, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"1Vout:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 0, 36, string);

	// Draw MPPT1 Tamb
	utoa(gCANVars.MPPT1_Tamb, buf, 10);
	memset(string, 0, sizeof string);
	strcat(string,"1Tamb:");
	strcat(string,buf);
	u8g_DrawStr(&u8g, 0, 47, string);

} // end drawMPPt



void draw(CANMessage* msg){
	char buf[10]; // used for forming strings to pass to the display ??

	if(msg->id == 0x0420){ //speed!
		CANMessage message = *msg;

		u8g_SetFont(&u8g, u8g_font_freedoomr25n);
		u8g_SetFontRefHeightExtendedText(&u8g);
		u8g_SetDefaultForegroundColor(&u8g);
		u8g_SetFontPosTop(&u8g);
		u8g_DrawFrame(&u8g,0,0,64,32);
		itoa(message.data[0], buf, 10);
		u8g_DrawStr(&u8g, 3, 4, buf);

	}else{
		CANMessage message = *msg;

		u8g_SetFont(&u8g, u8g_font_6x10);
		u8g_SetFontRefHeightExtendedText(&u8g);
		u8g_SetDefaultForegroundColor(&u8g);
		u8g_SetFontPosTop(&u8g);
		// ID
		itoa(message.id, buf, 10);
		u8g_DrawStr(&u8g, 5, 0, "ID= ");
		u8g_DrawStr(&u8g, 24, 0, buf);

		itoa(CAN_Rx_Head, buf, 10);
		u8g_DrawStr(&u8g, 64, 0, "H= ");
		u8g_DrawStr(&u8g, 88, 0, buf);
		itoa(CAN_Rx_Tail, buf, 10);
		u8g_DrawStr(&u8g, 64, 15, "T= ");
		u8g_DrawStr(&u8g, 88, 15, buf);


		// L
		itoa(message.length, buf, 10);
		u8g_DrawStr(&u8g, 5, 15, "Length= ");
		u8g_DrawStr(&u8g, 48, 15, buf);

		u8g_SetFont(&u8g, u8g_font_5x8);
		  u8g_SetFontRefHeightExtendedText(&u8g);
		  u8g_SetDefaultForegroundColor(&u8g);
		  u8g_SetFontPosTop(&u8g);

		for(int i = 0 ; i < message.length; i++){
			char string[15] ="D";
			itoa(i, buf, 10);
			strcat(string, buf);
			strcat(string, "= ");

			itoa(message.data[i], buf, 10);
			strcat(string, buf);

			if(i%2){ // odd number
				u8g_DrawStr(&u8g, 64, 30 + (i/2)*9, string);
			}else{ // even number
				u8g_DrawStr(&u8g, 0, 30 + (i/2)*9, string);
			}

		}
	}
}

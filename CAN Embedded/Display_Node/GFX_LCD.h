/*
 * GFX_LCD.h
 *
 *  Created on: 21 Mar 2015
 *      Author: RobThePyro
 */

#ifndef GFX_LCD_H_
#define GFX_LCD_H_

#include "../lib/u8glib/src/u8g.h"
#include "../lib/CAN/CAN.h" // CANMessage Struct?
#include "../lib/CAN/CAN_defs.h"
#include <string.h>			// strcat etc
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>         // itoa etc

// Hardware:
#define GFX_CS_PORT PORTD
#define GFX_CS_DDR  DDRD
#define GFX_CS_BIT  PD7


// Pin Defines
#include "pinDefines.h"
#define LCD_SELECT() 	( LCD_SCKCTL_PORT |=  (1<<LCD_SCKCTL) )
#define LCD_UNSELECT()  ( LCD_SCKCTL_PORT &= ~(1<<LCD_SCKCTL) )

// Structure Definitions
/*********************************************/

// Definitions
/*********************************************/
#define		SCREEN_MAIN		0x01
#define		SCREEN_SPD		0x02
#define		SCREEN_MPPT		0x04

// Variable Definitions
/*********************************************/
volatile uint8_t	Screen;
// Used for the display...
uint8_t		gSpeed;
uint8_t		gSpeed_HESSpd;
uint16_t	gSpeed_HESRPM;
uint8_t		gSpeed_MTSpd;
uint16_t	gSpeed_MTRPM;
uint8_t		gSpeed_status;
uint8_t		gBMS_State;
uint8_t		gBMS_Flags;
uint8_t		gBMS_Faults;
uint8_t		gBMS_LevelFaults;
uint8_t		gBMS_Warnings;
uint8_t 	gBMS_soc;
uint16_t 	gBMS_PackVoltage;
uint8_t		gBMS_MaxVTG;
int16_t 	gBMS_PackCurrent;
int8_t		gBMS_Temp;
int32_t		gGyro_AngleTHE;
int32_t		gGyro_AngleSI;
int32_t		gGyro_AnglePHI;

typedef struct{

	// MPPT Vars
	uint8_t 	MPPT1_Status;
	uint16_t 	MPPT1_Vin;
	uint16_t	MPPT1_Iin;
	uint16_t	MPPT1_Vout;
	uint8_t		MPPT1_Tamb;
	uint8_t 	MPPT2_Status;
	uint16_t 	MPPT2_Vin;
	uint16_t	MPPT2_Iin;
	uint16_t	MPPT2_Vout;
	uint8_t		MPPT2_Tamb;
	uint8_t 	MPPT3_Status;
	uint16_t 	MPPT3_Vin;
	uint16_t	MPPT3_Iin;
	uint16_t	MPPT3_Vout;
	uint8_t		MPPT3_Tamb;
	uint8_t 	MPPT4_Status;
	uint16_t 	MPPT4_Vin;
	uint16_t	MPPT4_Iin;
	uint16_t	MPPT4_Vout;
	uint8_t		MPPT4_Tamb;

} gCANVars_struct;

// create an instance of the global stuct!
gCANVars_struct gCANVars;

int16_t     AVR_Temp;



// used for the timing / interrupts
extern	volatile uint16_t	gMilliSecTick;
extern	volatile uint16_t	int_mS;

// Function Prototypes
/*********************************************/
void GFX_LCD_u8g_setup();
void u8g_prepare();
void GFX_LCD_Draw(CANMessage*);
void GFX_LCD_DrawMain(void);
void drawMain(void);
void drawSpd(void);
void drawMPPT(void);
void draw(CANMessage*);

#endif /* GFX_LCD_H_ */

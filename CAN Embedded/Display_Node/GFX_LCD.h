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
// Flag byte Masks
#define 	BMSFLAG_FAN		0x80
#define 	BMSFLAG_LLIM	0x40
#define 	BMSFLAG_HLIM	0x20
#define 	BMSFLAG_CANC	0x10
#define 	BMSFLAG_HWC		0x08
#define 	BMSFLAG_INTT	0x04
#define 	BMSFLAG_PL		0x02
#define 	BMSFLAG_PS		0x01

// Variable Definitions
/*********************************************/
// Used for the display...
uint16_t	gSpeed;
uint8_t 	gBMS_soc;
uint16_t 	gBMS_PackVoltage;
int16_t 	gBMS_PackCurrent;
int8_t		gBMS_Temp;
uint8_t		gBMS_Flags;

// used for the timing / interrupts
extern	volatile uint16_t	gMilliSecTick;
extern	volatile uint16_t	int_mS;

// Function Prototypes
/*********************************************/
void u8g_setup();
void u8g_prepare();
void GFX_LCD_Draw(CANMessage*);
void GFX_LCD_DrawMain(void);
void drawMain(void);
void draw(CANMessage*);

#endif /* GFX_LCD_H_ */

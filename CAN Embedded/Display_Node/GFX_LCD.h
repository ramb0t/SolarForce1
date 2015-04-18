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
#include <string.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

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

// Variable Definitions
/*********************************************/
// Used for the display...
uint16_t	gSpeed;
uint8_t 	gBMS_soc;
uint16_t 	gBMS_PackVoltage;
int16_t 	gBMS_PackCurrent;
int8_t		gBMS_Temp;


// Function Prototypes
/*********************************************/
void u8g_setup();
void u8g_prepare();
void GFX_Cnt(int);
void GFX_LCD_Draw(CANMessage*);
void GFX_LCD_DrawMain(void);
void drawMain(void);
void draw(CANMessage*);

#endif /* GFX_LCD_H_ */

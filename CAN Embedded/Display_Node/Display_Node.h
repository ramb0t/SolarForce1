/*
 * Display_Node.h
 *
 *  Created on: 01 Apr 2015
 *      Author: RobThePyro
 */

#ifndef DISPLAY_NODE_H_
#define DISPLAY_NODE_H_

// Based on https://github.com/hexagon5un/AVR-Programming

// Standard AVR includes
/*********************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>

//#include <stdio.h> // http://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html
#include <stdlib.h>  // Random, ITOA etc http://www.nongnu.org/avr-libc/user-manual/group__avr__stdlib.html
#include <stdint.h> // C99 Integer typedefs http://www.nongnu.org/avr-libc/user-manual/group__avr__stdint.html



// Project Specific
/*********************************************/
// CAN Application Layer
#include "../lib/CAN/CAN.h"
// MCP2515 Library
#include "../lib/mcp2515/mcp2515.h"
// for the GFX lcd used
#include "GFX_LCD.h"
// SPI Library used with CAN Controller
#include "../lib/SPI/AVR_SPI.h"
// Timer0
#include "Timer0.h"
// Timer1
#include "Timer1.h"
// ADC Functions
#include "ADC.h"

// Pin Defines
#include "pinDefines.h"
#define LCD_SELECT() 	( LCD_SCKCTL_PORT |=  (1<<LCD_SCKCTL) )
#define LCD_UNSELECT()  ( LCD_SCKCTL_PORT &= ~(1<<LCD_SCKCTL) )


#include <string.h>

// These are optional, but nice to have around.
// Feel free to comment them out if you don't use them.

#include "../lib/macros.h" // latest version maintained at https://github.com/robthepyro/AVR_Lib
// Return Defines
/*********************************************/
#define CAN_NODECODE	0
#define CAN_MSG_DECODED	1


// Structure Definitions
/*********************************************/

// Variable Definitions
/*********************************************/
// local vars
//				uint8_t		LCD_BackLight_Val;  // Better to use a macro?
#define			LCD_BackLight	OCR1A

				 uint8_t	flagUpdateLCD;		// sets if an update is needed.
extern  volatile uint8_t    flagTimerUpdateLCD; // allow the timer to determine update rate
extern 	volatile uint16_t	gMilliSecTick;      // Keeps track how many mS Have passed
		volatile uint16_t	int_mS;				// Keep track of when the last interupt was
				 uint16_t	heartbeat_mS;		// Keep track of when to send the next heartbeat
#define 	HEATBEAT_MS		1111                // arb to keep things interesting
				 CANMessage heartbeat_Msg;

extern	volatile uint8_t 	flag;
// External vars for the display values we are interested in
extern 			uint8_t 	gSpeed;
extern			uint8_t		gBMS_State;
extern			uint8_t		gBMS_Flags;
extern			uint8_t		gBMS_Faults;
extern			uint8_t		gBMS_LevelFaults;
extern			uint8_t		gBMS_Warnings;
extern 			uint8_t		gBMS_soc;
extern			uint16_t	gBMS_PackVoltage;
extern			int16_t		gBMS_PackCurrent;
extern			int8_t		gBMS_Temp;
extern 			int16_t		AVR_Temp;


// Function Prototypes
/*********************************************/
void 	IOInit(void);
uint8_t CAN_Decode(CANMessage *message);


#endif /* DISPLAY_NODE_H_ */

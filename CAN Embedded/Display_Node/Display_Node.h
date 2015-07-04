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
// Timer2
#include "Timer2.h"
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

// Constant Defines for Calcs
/*********************************************/
#define MPPT_VIN_MUL	150.49
#define MPPT_VOUT_MUL	208.79
#define MPPT_IIN_MUL	8.72
uint32_t tempVar;


// Structure Definitions
/*********************************************/

// Variable Definitions
/*********************************************/
// local vars
//				uint8_t		LCD_BackLight_Val;  // Better to use a macro?
#define			LCD_BackLight	OCR1A

		volatile uint8_t	flagUpdateLCD;		// sets if an update is needed.
extern  volatile uint8_t    flagTimerUpdateLCD; // allow the timer to determine update rate
extern 	volatile uint8_t	flagTimerRegMPPT;	// Time to req new data from MPPT's
extern 	volatile uint16_t	gMilliSecTick;      // Keeps track how many mS Have passed
		volatile uint16_t	int_mS;				// Keep track of when the last interupt was
		volatile uint16_t	btn_int_mS;			// used for btn debounce isr stuff
		volatile uint8_t	btn_press_flag;
				 uint16_t	heartbeat_mS;		// Keep track of when to send the next heartbeat
#define 	HEATBEAT_MS		1111                // arb to keep things interesting
				 CANMessage heartbeat_Msg;
				 CANMessage reqMPPT1_Msg, reqMPPT2_Msg, reqMPPT3_Msg, reqMPPT4_Msg;

extern	volatile uint8_t 	flag;

extern  volatile uint8_t	Screen; // Keeps track of which screen we are on...
// External vars for the display values we are interested in
extern 			uint8_t 	gSpeed;
extern			uint8_t		gSpeed_HESSpd;
extern			uint16_t	gSpeed_HESRPM;
extern			uint8_t		gSpeed_MTSpd;
extern			uint16_t	gSpeed_MTRPM;
extern			uint8_t		gSpeed_status;
extern			uint8_t		gBMS_State;
extern			uint8_t		gBMS_Flags;
extern			uint8_t		gBMS_Faults;
extern			uint8_t		gBMS_LevelFaults;
extern			uint8_t		gBMS_Warnings;
extern 			uint8_t		gBMS_soc;
extern			uint16_t	gBMS_PackVoltage;
extern			int16_t		gBMS_PackCurrent;
extern			int8_t		gBMS_Temp;
extern			int32_t		gGyro_AngleTHE;
extern			int32_t		gGyro_AngleSI;
extern			int32_t		gGyro_AnglePHI;

extern 			int16_t		AVR_Temp;

extern			gCANVars_struct gCANVars;


// Function Prototypes
/*********************************************/
void 	IOInit(void);
uint8_t CAN_Decode(CANMessage *message);
void 	setupPCINT2(void);


#endif /* DISPLAY_NODE_H_ */

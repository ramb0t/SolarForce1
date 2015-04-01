/*
 * Test_Node.h
 *
 *  Created on: 21 Mar 2015
 *      Author: RobThePyro
 */

#ifndef TEST_NODE_H_
#define TEST_NODE_H_

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



#define UART_BAUD_RATE 9600
#include "../lib/uart/uart.h"
// Handy uart functions
#include "../lib/uart/uart_CANFunc.h"
#include <string.h>

// These are optional, but nice to have around.
// Feel free to comment them out if you don't use them.

#include "../lib/macros.h" // latest version maintained at https://github.com/robthepyro/AVR_Lib


// Structure Definitions
/*********************************************/

// Function Prototypes
/*********************************************/




#endif /* TEST_NODE_H_ */

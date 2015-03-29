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

#include <stdio.h>
#include <stdlib.h>



// Project Specific
/*********************************************/
// for the GFX lcd used
#include "GFX_LCD.h"
// SPI Library used with CAN Controller
#include <SPI/AVR_SPI.h>
// MCP2515 Library
#include "mcp2515_cmds.h"

#define UART_BAUD_RATE 9600
#include <uart/uart.h>

// These are optional, but nice to have around.
// Feel free to comment them out if you don't use them.
#include <stdint.h>
#include "macros.h" // latest version maintained at https://github.com/robthepyro/AVR_Lib
//#include "USART.h"


// Structure Definitions
/*********************************************/




#endif /* TEST_NODE_H_ */

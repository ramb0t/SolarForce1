/*
 * main.h
 *
 *  Created on: 21 Feb 2015
 *      Author: RobThePyro
 */

#ifndef MAIN_H_
#define MAIN_H_

// Based on https://github.com/hexagon5un/AVR-Programming

// Standard AVR includes
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>

#include <stdlib.h>

// Project Specific
#include "CAN.h"
#include "mcp2515.h"
#include "AVR_SPI.h"
#include "uart.h"
#include <string.h>

// These are optional, but nice to have around.
// Feel free to comment them out if you don't use them.
#include <stdint.h>
#include "macros.h" // latest version maintained at https://github.com/robthepyro/AVR_Lib
//#include "USART.h"

/* 9600 baud */
#define UART_BAUD_RATE 9600



#endif /* MAIN_H_ */

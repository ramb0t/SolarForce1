/*
 * Terminal.h
 *
 *  Created on: 01 Apr 2015
 *      Author: RobThePyro
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

// Includes:
/*****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <util/delay.h>

// Project Specific
#include "../lib/uart/uart.h"


// Defines:
/*****************************************************************************/
//#define DEBUG

#define TERMINAL_INIT					0
#define TERMINAL_RUN					0x10

#define TERMINAL_LISTENSUB				0x20
#define TERMINAL_LISTEN					0x21
#define TERMINAL_LISTENRAW				0x22
#define TERMINAL_LISTENFILTER			0x24
#define TERMINAL_LISTENMPPT				0x25

#define TERMINAL_SENDSUB				0x40
#define TERMINAL_SEND1					0x41

#define TERMINAL_SENDRANDOM				0x42
#define TERMINAL_SENDBMS				0x43
#define TERMINAL_LOOPBMS				0x44
#define TERMINAL_LOOPSPEED				0x48
#define TERMINAL_LOOPGYRO				0x49

#define TERMINAL_MAX_INPUT_LENGTH		10

#define TERMINAL_sCANCEL				"c"
#define TERMINAL_sHELP					"help"

#define TERMINAL_cBACK					0

#define TERMINAL_cLISTENSUB				1
#define TERMINAL_cLISTEN				1
#define TERMINAL_cLISTENRAW				2
#define TERMINAL_cLISTENFILTER			3
#define TERMINAL_cLISTENMPPT			4

#define TERMINAL_cSENDSUB				2
//#define TERMINAL_cLISTEN				1
//#define TERMINAL_cLISTENRAW				2
#define TERMINAL_cSENDRANDOM			3
#define TERMINAL_cSENDBMS				4
#define TERMINAL_cLOOPBMS				5
#define TERMINAL_cLOOPSPEED				6
#define TERMINAL_cLOOPGYRO				7

#define TERMINAL_s1						"1"
#define TERMINAL_s2						"2"
#define TERMINAL_s3						"3"
#define TERMINAL_s4						"4"
#define TERMINAL_s5						"5"
#define TERMINAL_s6						"6"
#define TERMINAL_s7						"7"
#define TERMINAL_s8						"8"
#define TERMINAL_s9						"9"

// Variables:
/*****************************************************************************/


// Function Prototypes:
/*****************************************************************************/
void Terminal_init(void);
void Terminal_read(volatile uint8_t* state);
void Terminal_run(volatile uint8_t* state);

static void Terminal_showMenu(void);
static void Terminal_showListenMenu(void);
static void Terminal_showSendMenu(void);


#endif /* TERMINAL_H_ */

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


// Project Specific
#include "../lib/uart/uart.h"

// Defines:
/*****************************************************************************/
#define DEBUG

#define TERMINAL_INIT					0
#define TERMINAL_RUN					TERMINAL_INIT+1
#define TERMINAL_LISTEN					TERMINAL_INIT+2
#define TERMINAL_LISTENFILTER			TERMINAL_INIT+3
#define TERMINAL_SEND1					TERMINAL_INIT+4

#define TERMINAL_MAX_INPUT_LENGTH		10

#define TERMINAL_sCANCEL				"c"
#define TERMINAL_sHELP					"help"
#define TERMINAL_sLISTEN				"1"


// Variables:
/*****************************************************************************/

// Function Prototypes:
/*****************************************************************************/
void Terminal_init(void);
void Terminal_read(uint8_t* state);
void Terminal_run(uint8_t* state);

static void Terminal_showMenu(void);


#endif /* TERMINAL_H_ */

/*
 * Timer0.h
 *
 *  Created on: 02 Apr 2015
 *      Author: RobThePyro
 */

// For Atmega328p !!
#ifndef TIMER0_H_
#define TIMER0_H_

// Includes:
/*****************************************************************************/
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../lib/macros.h"

// Defines:
/*****************************************************************************/
// timebase on timer0 serves a 1ms tick
// for 16MHz System and Prescaler 64
#define TIMEBASE_PRESCALE (64) // prescaler value
#define TIMEBASE_HITS_PER_1MS ( F_CPU/TIMEBASE_PRESCALE/1000 ) //number of timer counts per 1mS
#define TIMEBASE_RELOAD ((uint8_t)(0xff-TIMEBASE_HITS_PER_1MS+1)) // value to reload timer with

#define LCD_REFRESH_RATE	240			// refresh rate in mS
// Variables:
/*****************************************************************************/
		volatile uint16_t 	gMilliSecTick;
		volatile uint16_t	old_mS;
		volatile uint8_t	flagTimerUpdateLCD;

// Function Prototypes:
/*****************************************************************************/
void Timer0_init(void);


#endif /* TIMER0_H_ */

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
#include "../lib/uart/uart.h"

// Project Specific

// Defines:
/*****************************************************************************/
// timebase on timer0 serves a 1ms tick
// for 16MHz System and Prescaler 64
#define TIMEBASE_PRESCALE (64) // prescaler value
#define TIMEBASE_HITS_PER_1MS ( F_CPU/TIMEBASE_PRESCALE/1000 ) //number of timer ovf per 1mS
#define TIMEBASE_RELOAD ((uint8_t)(0xff-TIMEBASE_HITS_PER_1MS+1)) // value to reload timer with

#define LEDT_DDR	DDRD
#define LEDT_PORT	PORTD
#define LEDT1		PD0
#define LEDT2		PD1

// Variables:
/*****************************************************************************/
volatile uint8_t gMilliSecTick;
volatile uint16_t ms_Counter;
extern volatile uint8_t Terminal_state;


// Function Prototypes:
/*****************************************************************************/
void Timer0_init(void);


#endif /* TIMER0_H_ */

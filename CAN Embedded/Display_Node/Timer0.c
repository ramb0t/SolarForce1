/*
 * Timer0.c
 *
 *  Created on: 02 Apr 2015
 *      Author: RobThePyro
 */

// For ATmega328p !!

#include "Timer0.h"


// Timer 0 OVF ISR
ISR(TIMER0_OVF_vect)
{
	TCNT0 = TIMEBASE_RELOAD; // Reload Timer

	gMilliSecTick++;

	if((gMilliSecTick - old_mS) > LCD_REFRESH_RATE){ // Time for an LCD refresh
		old_mS = gMilliSecTick;
		flagTimerUpdateLCD = TRUE;
	}

}

// Init the Timer0
void Timer0_init(void)
{
	// set the timer to ovf ever 1mS
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00); // prescaler: 64
	TCNT0 = TIMEBASE_RELOAD; // set initial reload-value
	TIFR0  |= (1<<TOV0);  // clear overflow int.
	TIMSK0 |= (1<<TOIE0); // enable overflow-interrupt

	gMilliSecTick = 0;
	old_mS = 0;
}



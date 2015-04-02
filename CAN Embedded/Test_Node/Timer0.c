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
	gMilliSecTick++;   // Inc Counter
	TCNT0 = TIMEBASE_RELOAD; // Reload Timer


	if(gMilliSecTick > TIMEBASE_HITS_PER_1MS){// 1mS has passed!
		gMilliSecTick = 0;
	}
}

// Init the Timer0
void Timer0_init(void)
{
	TCCR0B = (1<<CS01) | (1<<CS00); // prescaler: 64
	TCNT0 = TIMEBASE_RELOAD; // set initial reload-value
	TIFR0  |= (1<<TOV0);  // clear overflow int.
	TIMSK0 |= (1<<TOIE0); // enable overflow-interrupt
}



/*
 * timer0.c
 *
 * Created: 19/04/2015 12:19:01 AM
 *  Author: Terayza
 */ 

// For aTmega328p

#include "timer0.h"

//timer0 overflow
ISR(TIMER0_OVF_vect)
{
	count0++;
	TCNT0 = TIMEBASE_RELOAD0; //reload timer
	//timer will be reloaded to the highest value(overflow value) - 1ms
	
	if (count0 > 500)
	{
		send();
		count0 = 0;
	}
}

//timer0 setup
void timer0_init(void)
{
	// set the timer to overflow ever 1mS
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00); // prescaler: 64
	TCNT0 = TIMEBASE_RELOAD0; // set initial reload-value
	TIFR0  |= (1<<TOV0);  // clear overflow int.
	TIMSK0 |= (1<<TOIE0); // enable overflow-interrup
}



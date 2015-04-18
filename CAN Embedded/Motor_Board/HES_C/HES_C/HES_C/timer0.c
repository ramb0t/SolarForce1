/*
 * timer0.c
 *
 * Created: 17/04/2015 11:49:02 AM
 *  Author: Terayza
 */ 

// For aTmega328p

#include "timer0.h"

//timer0 overflow
ISR(TIMER0_OVF_vect)
{
	TCNT0 = TIMEBASE_RELOAD; //reload timer
	//timer will be reloaded to the highest value(overflow value) - 1ms
	
	speedCalcs(); //call calculations function
}

//timer0 setup
void timer0_init(void)
{
	// set the timer to overflow ever 1mS
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00); // prescaler: 64
	TCNT0 = TIMEBASE_RELOAD; // set initial reload-value
	TIFR0  |= (1<<TOV0);  // clear overflow int.
	TIMSK0 |= (1<<TOIE0); // enable overflow-interrupt
	
	sei(); 	// set (global) interrupt enable bit
}



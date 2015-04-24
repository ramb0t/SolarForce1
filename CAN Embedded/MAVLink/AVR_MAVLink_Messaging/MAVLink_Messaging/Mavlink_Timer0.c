/*
 * Mavlink_Timer0.c
 *
 * Created: 2015/04/24 08:26:13 PM
 *  Author: Matt
 */ 

#include "Mavlink_Timer0.h"

ISR(TIMER0_OVF_vect)
{
	TCNT0 = TIMEBASE_RELOAD;		//Reroll timer value!
	
	gMilliSecTick++;
	
	if ((gMilliSecTick - old_mS) > MAVLINK_HB_UPDATERATE )
	{
		old_mS = gMilliSecTick;		//set the previous value back to let counter run
		updateMAV_flag = TRUE;
	}
	
}

// Init the Timer0
void Timer0_init(void)
{
	// set the timer to ovf every 1mS
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00); // prescaler: 64
	TCNT0 = TIMEBASE_RELOAD; // set initial reload-value
	TIFR0  |= (1<<TOV0);  // clear overflow int.
	TIMSK0 |= (1<<TOIE0); // enable overflow-interrupt

	gMilliSecTick = 0;
	old_mS = 0;
}
/*
 * Mavlink_Timer0.c
 *
 * Created: 2015/04/24 08:26:13 PM
 *  Author: Matt
 */ 

#include "Mavlink_Timer0.h"

ISR(TIMER0_OVF_vect)
{
	gMilliSecTick++;
	TCNT0 = TIMEBASE_RELOAD;		//Reroll timer value!
	
	ms_Counter++;								//another 1ms passed!
	
	if ((ms_Counter - old_mS) > MAVLINK_HB_UPDATERATE )
	{
		old_mS = ms_Counter;		//set the previous value back to let counter run
		updateMAV_flag = TRUE;
		
	}
	
		if ((ms_Counter - old_mS_MPPT) > MPPT_REQUEST_TIME ) //need to send request to mppt's every 1s
		{
			old_mS_MPPT = ms_Counter;		//set the previous value back to let counter run
			reqMPPTs_flag = TRUE;
			updateGPS_flag = TRUE;
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
	old_mS_MPPT = 0;
	ms_Counter = 0;
}
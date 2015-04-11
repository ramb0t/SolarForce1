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


	//if(gMilliSecTick > TIMEBASE_HITS_PER_1MS){// 1mS has passed!
		//gMilliSecTick = 0;
		ms_Counter++;

		// Count 1 sec
		if(ms_Counter == 1000){ // 1 sec has passed?
			ms_Counter = 0;
		}

		// Flash some LEDs ?
		if(ms_Counter == 350){
			LEDT_PORT ^= (1<<LEDT1)|(1<<LEDT2);
		}

		//Should we check for stuff?
		//if(uart_available()){
			// We have something available!! Process?
		//	Terminal_read(&Terminal_state);
		//}
	//}
}

// Init the Timer0
void Timer0_init(void)
{
	// set the timer to ovf ever 1mS
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00); // prescaler: 64
	TCNT0 = TIMEBASE_RELOAD; // set initial reload-value
	TIFR0  |= (1<<TOV0);  // clear overflow int.
	TIMSK0 |= (1<<TOIE0); // enable overflow-interrupt

	// Setup LEDs
	LEDT_DDR |= (1<<LEDT1)|(1<<LEDT2);
	// Turn one on to start?
	LEDT_PORT |= (1<<LEDT2);

	LEDT_PORT ^= (1<<LEDT1)|(1<<LEDT2);

	ms_Counter = 0;
	gMilliSecTick = 0;
}



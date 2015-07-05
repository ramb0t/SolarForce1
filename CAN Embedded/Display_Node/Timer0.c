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

	// Check for LCD refresh time?
	if((gMilliSecTick - old_mS_LCD) > LCD_REFRESH_RATE){ // Time for an LCD refresh
		old_mS_LCD = gMilliSecTick;
		flagTimerUpdateLCD = TRUE;
	}

	// Check for MPPT req time?
	if((gMilliSecTick - old_mS_MPPT) > MPPT_REFRESH_RATE){ // Time for a MPPT req
		old_mS_MPPT = gMilliSecTick;
		flagTimerReqMPPT = TRUE;
	}

	// Check for ADC refresh time?
	if((gMilliSecTick - old_mS_ADC) > ADC_THR_REFRESH_RATE){ // Time for an ADC refresh
		old_mS_ADC = gMilliSecTick;
		// create temp var.
		//uint8_t tempADC = 0;
		// get a result
		//tempADC = ADC_start(CRUISE_ADC_THR_MUX);
		ADC_start(CRUISE_ADC_THR_MUX);
		// write it as a pwm output?
		Timer2_Set_PWM_Cruise(ADC_start(CRUISE_ADC_THR_MUX)>>2);

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

	// Init variables
	gMilliSecTick = 0;
	old_mS_LCD = 0;
	old_mS_MPPT = 0;
	old_mS_ADC = 0;
}



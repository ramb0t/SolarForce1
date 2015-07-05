/*
 * Timer2.c
 *
 *  Created on: 05 Jul 2015
 *      Author: RobThePyro
 */

#include "Timer2.h"


void Timer2_init(void) {
	// Timer 2 B only (A used in SPI ? )
	// make sure min value set on boot
	OCR2B = 0;
	OCR2A = 0;
	TCCR2A |= (1 << WGM21)|(1 << WGM20); /* Fast PWM mode, 8-bit */
	TCCR2B |= (1 << CS20); /* PWM Freq = F_CPU/1/256 ~78kHz */
	//TCCR2A |= (1 << COM2A1); /* PWM output on OC2A */
	TCCR2A |= (1 << COM2B1); /* PWM output on OC1B */

	// Pin Setup
	CRUISE_PWM_DDR |= (1 << CRUISE_PWM);
}

void Timer2_PWM_Off(void){
	// Disconnect Clock!
	TCCR2B &= ~((1<<CS22)|(1<<CS21)|(1<<CS20));
}

void Timer2_PWM_On(void){
	// Connect Clock!
	TCCR2B |= (0<<CS22)|(0<<CS21)|(1<<CS20);
}

void Timer2_Set_PWM_Cruise(uint8_t PWM_Val){
	OCR2B = PWM_Val;
}

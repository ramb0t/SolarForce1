/*
 * Timer1.c
 *
 *  Created on: 04 Apr 2015
 *      Author: RobThePyro
 */

#include "Timer1.h"


void Timer1_init(void) {
	// Timer 1 A,B
	TCCR1A |= (1 << WGM10); /* Fast PWM mode, 8-bit */
	TCCR1B |= (1 << WGM12); /* Fast PWM mode, pt.2 */
	TCCR1B |= (1 << CS11); /* PWM Freq = F_CPU/8/256 */
	TCCR1A |= (1 << COM1A1); /* PWM output on OCR1A */
	//TCCR1A |= (1 << COM1B1); /* PWM output on OCR1B */

	// Pin Setup
	LCD_PWM_DDR |= (1 << LCD_PWM);
}

void Timer1_PWM_Off(void){
	// Disconnect Clock!
	TCCR1B &= ~((1<<CS12)|(1<<CS11)|(1<<CS10));
}

void Timer1_PWM_On(void){
	// Connect Clock!
	TCCR1B |= (0<<CS12)|(1<<CS11)|(0<<CS10);
}

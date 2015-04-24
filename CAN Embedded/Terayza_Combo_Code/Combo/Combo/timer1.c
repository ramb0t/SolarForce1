/*
 * timer1.c
 *
 * Created: 25/04/2015 12:27:19 AM
 *  Author: Terayza
 */ 

#include "timer1.h"

//timer0 overflow
ISR(TIMER1_OVF_vect)
{
	if(totalCount < 50000)
	{
		motorSpeed = 0x00;
		TCNT1 = 0;
	}
}

//timer1 setup
void timer1_init()
{
	TCNT1 = 0;
	TCCR1B &=~ (1<<ICES1); //falling edge select
	TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler: 64
	TIMSK1 |= (1<<ICIE1) | (1<<TOIE0); //enable overflow-interrupts
	totalCount = 0;
	numCount1 = 0;
}
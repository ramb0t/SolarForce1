/*
 * timer1.h
 *
 * Created: 25/04/2015 12:27:48 AM
 *  Author: Terayza
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

// For atmega328p
#define F_CPU 16000000UL
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../lib/uart/uart.h"

extern volatile uint8_t motorSpeed;
extern volatile uint16_t totalCount;
extern volatile uint8_t numCount1;

void timer1_init(void);

#endif /* TIMER1_H_ */
/*
 * timer2.h
 *
 * Created: 19/04/2015 02:51:56 AM
 *  Author: Terayza
 */ 


#ifndef TIMER2_H_
#define TIMER2_H_

// For atmega328p
#define F_CPU 16000000UL
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../lib/uart/uart.h"

extern volatile uint16_t count2;

// timebase on timer2 serves a 0.5ms tick
// for 16MHz System and Prescaler 64
#define TIMEBASE_PRESCALE2 (64) // prescaler value
#define TIMEBASE_HITS_PER_05MS ( F_CPU/TIMEBASE_PRESCALE2/2000 ) //number of timer ovf per 0.5mS
#define TIMEBASE_RELOAD2 ((uint8_t)(0xff-TIMEBASE_HITS_PER_05MS+1)) // value to reload timer with

void timer2_init(void);



#endif /* TIMER2_H_ */
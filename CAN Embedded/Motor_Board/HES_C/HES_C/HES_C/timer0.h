/*
 * timer0.h
 *
 * Created: 17/04/2015 11:49:16 AM
 *  Author: Terayza
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

// For atmega328p
#define F_CPU 16000000UL
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../lib/uart/uart.h"

// timebase on timer0 serves a 1ms tick
// for 16MHz System and Prescaler 64
#define TIMEBASE_PRESCALE (64) // prescaler value
#define TIMEBASE_HITS_PER_1MS ( F_CPU/TIMEBASE_PRESCALE/1000 ) //number of timer ovf per 1mS
#define TIMEBASE_RELOAD ((uint8_t)(0xff-TIMEBASE_HITS_PER_1MS+1)) // value to reload timer with

void timer0_init(void);


#endif /* TIMER0_H_ */
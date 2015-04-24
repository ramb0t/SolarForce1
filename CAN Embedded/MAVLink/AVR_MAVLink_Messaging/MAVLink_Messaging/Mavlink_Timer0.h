/*
 * Mavlink_Timer0.h
 *
 * Created: 2015/04/24 08:26:53 PM
 *  Author: Matt
 */ 


#ifndef MAVLINK_TIMER0_H_
#define MAVLINK_TIMER0_H_

//---------------Includes & defines-------//
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// timebase on timer0 serves a 1ms tick
// for 16MHz System and Prescaler 64
#define TIMEBASE_PRESCALE (64) // prescaler value
#define TIMEBASE_HITS_PER_1MS ( F_CPU/TIMEBASE_PRESCALE/1000 ) //number of timer counts per 1mS
#define TIMEBASE_RELOAD ((uint8_t)(0xff-TIMEBASE_HITS_PER_1MS+1)) // value to reload timer with
#define MAVLINK_HB_UPDATERATE 500
#define TRUE 1

//---------------Variables---------------//
volatile uint8_t	updateMAV_flag = 0;		//flag to know whether MAVLink packet to be sent
volatile uint16_t 	gMilliSecTick;
volatile uint16_t	old_mS;


//---------------Prototypes---------------//
void Timer0_init(void);

#endif /* MAVLINK_TIMER0_H_ */
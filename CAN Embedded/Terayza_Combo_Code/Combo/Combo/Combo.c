/*
 * Combo.c
 *
 * Created: 17/04/2015 04:43:14 PM
 *  Author: Terayza
 */ 

#define F_CPU 16000000UL
#define HES1 1
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/CAN/CAN.h"
#include "../lib/mcp2515/mcp2515.h"
#include "../lib/SPI/AVR_SPI.h"
#include "timer0.h"
#include "timer2.h"

volatile uint16_t count2 = 0;
volatile uint8_t hSpeed = 0;
volatile uint16_t count0 = 0;
volatile uint8_t motorSpeed = 0;
volatile uint8_t numCount1;
volatile uint16_t totalCount;
volatile uint16_t avgCount;

void send()
{
	volatile uint8_t avgSpeed;
	avgSpeed = (hSpeed + motorSpeed)/2;
	
	CANMessage speed;
	
	speed. id = 0x0420;
	speed. rtr = 0 ;
	speed. length = 3 ;
	speed. data [ 0 ] = avgSpeed;
	speed. data [ 1 ] = hSpeed;
	//speed. data [ 2 ] = hRPM>>8;
	//speed. data [ 3 ] = hRPM;
	speed. data [ 2 ] = motorSpeed;
	//speed. data [ 5 ] = motorRPM>>8;
	//speed. data [ 6 ] = motorRPM;
	//speed. data [ 7 ] = status;
	
	CAN_sendMessage (&speed);
	
	/*CANMessage angle;
	
	angle. id = 0x0820;
	angle. rtr = 0 ;
	angle. length = 3 ;
	angle. data [ 0 ] = yaw;
	angle. data [ 1 ] = pitch;
	angle. data [ 2 ] = roll;
	
	CAN_sendMessage (&angle);
	
	CANMessage gyroscope;
	
	gyroscope. id = 0x0821;
	gyroscope. rtr = 0 ;
	gyroscope. length = 3 ;
	gyroscope. data [ 0 ] = gyrox;
	gyroscope. data [ 1 ] = gyroy;
	gyroscope. data [ 2 ] = gyroz;
	
	CAN_sendMessage (&gyroscope);
	
	CANMessage accelerometer;
	
	accelerometer. id = 0x0822;
	accelerometer. rtr = 0 ;
	accelerometer. length = 3 ;
	accelerometer. data [ 0 ] = accelx;
	accelerometer. data [ 1 ] = accely;
	accelerometer. data [ 2 ] = accelz;
	
	CAN_sendMessage (&accelerometer);*/

}

void motorCalcs()
{
	if(numCount1 > 0)
	{
		avgCount = totalCount/numCount1;
	}
	else
	{
		avgCount = 0;
	}
	
	totalCount = 0;
	numCount1 = 0;
	
	motorSpeed = 40250/avgCount;
}

ISR(INT0_vect)
{
	volatile uint16_t Capt2 = 0;
	
	//need debouncing here!!!!
	//if magnet passes by slowly, picks up more than one interrupt
	
	//number of overflows * counts per overflows
	Capt2 = (count2*125 + (TCNT2 - TIMEBASE_RELOAD2)); //125 is the number of counts that it counts
	
	count2 = 0;
	TCNT2 = TIMEBASE_RELOAD2; //reload timer
	
	//place in circum depending on where its mounted on wheel
	//24.5cm diameter on my bike, therefore circum = 0.76969m
	//90000* circum = 69272.11801
	hSpeed = (69272)/Capt2;
}

ISR (TIMER1_CAPT_vect)
{
	volatile uint16_t Capt1;
	
	Capt1 = ICR1;
	TCNT1 = 0;
	totalCount = totalCount + Capt1;
	numCount1++;
	
	if(totalCount > 50000) //could this be the issue for being stuck at 1 instead of going to 0???
	{
		motorCalcs();
	}
}

void initInterrupt0(void)
{
	EIMSK |= (1 << INT0); //enable INT0
	EICRA |= (1 << ISC00); // trigger when button changes
}

int main(void)
{
	//initializations
	initInterrupt0();
	timer0_init();
	timer1_init();
	timer2_init();
	
	SPI_Init(); // setup SPI
	CAN_Init(CAN_125KBPS_16MHZ);
	
	DDRD = 0x00; //set port D as input pins
	PORTD = 0xff; // set pull ups
	
	DDRB &= ~(1 << PORTB0); //set PB0 as input
	PORTB |= (1<< PORTB0);  //pull up
	
	sei(); 	// set (global) interrupt enable bit
	
	while(1)
	{
		//do something
	}
}


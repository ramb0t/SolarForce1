/*
 * MotorRead.c
 *
 * Created: 12/04/2015 02:27:14 PM
 *  Author: Terayza
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "../lib/CAN/CAN.h"
#include "../lib/mcp2515/mcp2515.h"
#include "../lib/SPI/AVR_SPI.h"
#include "../lib/uart/uart.h"

#include "timer0.h"
#include "timer2.h"


volatile uint16_t inputCaptureVals[] = {0,0,0,0,0,0};
volatile uint16_t count = 0;

volatile uint32_t sum = 0;
volatile uint32_t avgPeriod = 0;
volatile uint32_t freq = 0;
volatile uint32_t rpm = 0;
volatile uint32_t step = 0;
volatile uint16_t motorSpeed = 0;

volatile uint8_t numCount;
volatile uint16_t Capt1;
volatile uint16_t totalCount;
volatile uint16_t avgCount;

volatile uint16_t count0 = 0;
volatile uint16_t count2 = 0;
volatile uint16_t Capt2 = 0;
volatile uint16_t numCount2 = 0;
volatile uint16_t step2 = 0;
volatile uint16_t hallRev = 0;
volatile uint16_t avgCountH = 0;
volatile uint16_t totalCountH = 0;


volatile uint8_t hSpeed = 0;

volatile uint8_t avgSpeed = 0;

void speedCalcs()
{
	avgSpeed = (motorSpeed + hSpeed)/2;
	
	CANMessage speed;
	
	speed. id = 0x0420;
	speed. rtr = 0 ;
	speed. length = 8 ;
	speed. data [ 0 ] = avgSpeed;			//average speed
	speed. data [ 1 ] = hSpeed;				//hall speed
	speed. data [ 2 ] =	motorSpeed;			//hall rpm [0]
	speed. data [ 3 ] = 0x00;				//hall rpm [1]
	speed. data [ 4 ] = 0x00;				//motor speed
	speed. data [ 5 ] = 0x00;				//motor rpm [0]
	speed. data [ 6 ] = 0x00;				//motor rpm [1]
	speed. data [ 7 ] = 0x00;				//status flag
	
	CAN_sendMessage (&speed);
}

void motorCalcs()
{
	if(numCount > 0)
	{
		avgCount = totalCount/numCount;
	}
		else
	{
		avgCount = 0;
	}
	
	totalCount = 0;
	numCount = 0;
	
	motorSpeed = 40000/avgCount;
	
	
	speedCalcs();
}

void timer1SetUp()
{
	TCNT1 = 0;
	TCCR1B &=~ (1<<ICES1);
	TCCR1B |= (1<<CS11) | (1<<CS10);
	TIMSK1 |= (1<<ICIE1) | (1<<TOIE0);
	totalCount = 0;
	numCount = 0;
}

ISR (TIMER1_CAPT_vect)
{
	Capt1 = ICR1;
	TCNT1 = 0;
	totalCount = totalCount + Capt1;
	numCount++;
	
	if(totalCount > 50000)
	{
		motorCalcs();
	}
}

ISR(INT0_vect)
{
	//number of overflows * counts per overflows
	Capt2 = (count2*125 + (TCNT2 - TIMEBASE_RELOAD2)); //125 is the number of counts that it counts
	numCount2 = Capt2*4; //number of balls in microseconds
	
	count2 = 0;
	TCNT2 = TIMEBASE_RELOAD2; //reload timer
	
	//rps = 1/numCount
	//numCount in us, multiply by 1000 give ms
	//1.61*3.4*10000 gives 57960
	step2 = (numCount2)*5896;
	hSpeed = step2/100; //converted to km/h
	
	CANMessage speedTest1;
	
	speedTest1. id = 0x0002;
	speedTest1. rtr = 0 ;
	speedTest1. length = 4 ;
	speedTest1. data [ 0 ] = 0x01;
	speedTest1. data [ 1 ] = step2>>8;
	speedTest1. data [ 2 ] = step2;
	speedTest1. data [ 3 ] = hSpeed;
	
	CAN_sendMessage (&speedTest1);
}

void initInterrupt0(void)
{
	EIMSK |= (1 << INT0); //enable INT0
	EICRA |= (1 << ISC00); // trigger when button changes
}

ISR(TIMER1_OVF_vect)
{
	speedCalcs();
}

int main(void)
{
	//initializations
	timer0_init();
	timer2_init();
	timer1SetUp();
	
	
	SPI_Init(); // setup SPI
	CAN_Init(CAN_125KBPS_16MHZ);
	
	DDRB &= ~(1 << PORTB0); //set PB0 as input
	PORTB |= (1<< PORTB0);  //pull up
	
	DDRD = 0x00; //set port D as input pins
	PORTD = 0xff; // set pull ups
	
	sei();
    
	while(1)
    {	
		//do something
    }
}





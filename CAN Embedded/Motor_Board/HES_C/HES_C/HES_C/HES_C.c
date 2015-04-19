/*
 * HES_C.c
 *
 * Created: 16/03/2015 02:48:28 PM
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

volatile uint16_t count0 = 0;
volatile uint16_t count2 = 0;
volatile uint16_t Capt2 = 0;
volatile uint16_t numCount = 0;
volatile uint16_t step2 = 0;
volatile uint16_t hallRev = 0;
volatile uint16_t avgCountH = 0;
volatile uint16_t totalCountH = 0;
volatile uint16_t rpm = 0;
volatile uint16_t step = 0;
volatile uint8_t hSpeed = 0;


/*void send()
{
	//in combo, this 0x420 will have all data
	//not individual ones like how it is now
	//work on this!
	CANMessage hallSpeed;
	
	hallSpeed. id = 0x0420;
	hallSpeed. rtr = 0 ;
	hallSpeed. length = 1 ;
	hallSpeed. data [ 0 ] = hSpeed;
	
	CAN_sendMessage (&hallSpeed);
	//_delay_ms(200);
}*/


void speedCalcs ()
{	
	//fix this calculation to keep accuracy
	//the way Ben showed for the motor one
	
	/*if (hallRev > 0)
	{
		avgCountH = totalCountH/hallRev; 
	}
		else
	{
		avgCountH = 0;
	}
	
	CANMessage tryit1;
	
	tryit1. id = 0x0009;
	tryit1. rtr = 0 ;
	tryit1. length = 7 ;
	tryit1. data [ 0 ] = 0x09;
	tryit1. data [ 1 ] = totalCountH>>8;
	tryit1. data [ 2 ] = totalCountH;
	tryit1. data [ 3 ] = Capt2>>8;
	tryit1. data [ 4 ] = Capt2;
	tryit1. data [ 5 ] = avgCountH>>8;
	tryit1. data [ 6 ] = avgCountH;
	
	CAN_sendMessage (&tryit1);
	
	totalCountH = 0;
	Capt2 = 0;
	
	hSpeed = 40000/avgCountH;
	
	CANMessage tryit;
	
	tryit. id = 0x0006;
	tryit. rtr = 0 ;
	tryit. length = 2 ;
	tryit. data [ 0 ] = 0x04;
	tryit. data [ 1 ] = hSpeed;
	
	CAN_sendMessage (&tryit);*/
	
	CANMessage speedTest;
	
	speedTest. id = 0x0420;
	speedTest. rtr = 0 ;
	speedTest. length = 2 ;
	speedTest. data [ 0 ] = 0x04;
	speedTest. data [ 1 ] = hSpeed;
	
	CAN_sendMessage (&speedTest);
}

ISR(INT0_vect)
{
	//to run when there is an interrupt from HES
	//increment the value of the count by one each time
	//the magnet is detected
	//use this value to calculate the rpm's
	//half_rev = half_rev + 1;
	
	//need debouncing here!!!!
	//if magnet passes by slowly, picks up more than one interrupt
	
	//step2 = count2*5; //number of overflows*0.5ms
	//Capt2 = Capt2/10; //5 divided by 10 = 0.5
	
	//number of overflows * counts per overflows
	Capt2 = (count2*125 + (TCNT2 - TIMEBASE_RELOAD2)); //125 is the number of counts that it counts
	numCount = Capt2*4; //number of balls in microseconds
	
	count2 = 0;
	TCNT2 = TIMEBASE_RELOAD2; //reload timer
	
	//rps = 1/numCount 
	//numCount in us, multiply by 1000 give ms
	//1.61*3.4*10000 gives 57960
	step2 = (numCount)*5896; 
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
	
	//totalCountH = totalCountH + numCount;
		
	/*CANMessage tryit2;
	
	tryit2. id = 0x0007;
	tryit2. rtr = 0 ;
	tryit2. length = 2 ;
	tryit2. data [ 0 ] = 0x07;
	tryit2. data [ 1 ] = totalCountH;
	
	CAN_sendMessage (&tryit2);*/
	
	/*hallRev++;
	
	if (totalCountH > 50000)
	{
		speedCalcs();
	}*/
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
	timer2_init();
		
	SPI_Init(); // setup SPI	
	CAN_Init(CAN_125KBPS_16MHZ);
	
	DDRD = 0x00; //set port D as input pins
	PORTD = 0xff; // set pull ups
	
	sei(); 	// set (global) interrupt enable bit
	
    while(1)
    {
	
	}
}
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

void send()
{	
	CANMessage speedTest;
	
	speedTest. id = 0x0420;
	speedTest. rtr = 0 ;
	speedTest. length = 2 ;
	speedTest. data [ 0 ] = 0x00;
	speedTest. data [ 1 ] = hSpeed;
	
	CAN_sendMessage (&speedTest);
}

ISR(INT0_vect)
{	
	//need debouncing here!!!!
	//if magnet passes by slowly, picks up more than one interrupt
	//step2 = count2*5; //number of overflows*0.5ms
	//Capt2 = Capt2/10; //5 divided by 10 = 0.5
	
	//number of overflows * counts per overflows
	Capt2 = (count2*125 + (TCNT2 - TIMEBASE_RELOAD2)); //125 is the number of counts that it counts
	//numCount = Capt2*4; //number of balls in microseconds
	
	count2 = 0;
	TCNT2 = TIMEBASE_RELOAD2; //reload timer
	
	//place i circum depending on where its mounted on wheel
	//24.5cm diameter on my bike, therefore circum = 0.76969m
	//90000* circum = 69272.11801
	hSpeed = (69272)/Capt2;
	
	//rps = 1/numCount 
	//numCount in us, multiply by 1000 give m/s
	//1.61*3.14*10000 gives 50554
	
	//19 April test, mounted at 10cm from center nut
	//therefore 10cm radius is 20cm diameter
	//20cm diameter multiplied y pi is 0.6283m
	//this multiplied by 1000 gives m/s
	//0.6283*3.14*10000 gives 19739.2088
	
	//rpus = 1/numCount; //revolutions per microseconds
	//rps = rpus* 1e-6 or rps = //convert microseconds to seconds
	//rpm = rps*60;
	//speed = rpm*1.61*3.6
	
	//step2 = 60000000/numCount;
	//hSpeed = step2*
	//step2 = (numCount)*5896; 
	//hSpeed = step2/100; //converted to km/h
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
		//do something	
	}
}
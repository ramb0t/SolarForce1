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

void send()
{
	CANMessage speed;
	
	speed. id = 0x0420;
	speed. rtr = 0 ;
	speed. length = 8 ;
	speed. data [ 0 ] = motorSpeed;			//average speed
	speed. data [ 1 ] = motorSpeed;			//hall speed
	speed. data [ 2 ] =	Capt1;				//hall rpm [0]
	speed. data [ 3 ] = avgCount;			//hall rpm [1]
	speed. data [ 4 ] = motorSpeed;			//motor speed
	speed. data [ 5 ] = 0x01;				//motor rpm [0]
	speed. data [ 6 ] = 0x02;				//motor rpm [1]
	speed. data [ 7 ] = 0x03;				//status flag
	
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
	
	
	send();
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

ISR(TIMER1_OVF_vect)
{
	send();
}

int main(void)
{
	//initializations
	timer1SetUp();
	
	SPI_Init(); // setup SPI
	CAN_Init(CAN_125KBPS_16MHZ);
	
	DDRB &= ~(1 << PORTB0); //set PB0 as input
	PORTB |= (1<< PORTB0);  //pull up
	
	sei();
    
	while(1)
    {	
		//do something
    }
}
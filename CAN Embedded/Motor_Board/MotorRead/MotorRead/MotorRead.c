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

volatile uint32_t rpm = 0;
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
	speed. data [ 0 ] = 0x00;			//average speed
	speed. data [ 1 ] = motorSpeed;				//hall speed
	speed. data [ 2 ] =	0x00;				//hall rpm [0]
	speed. data [ 3 ] = 0x00;				//hall rpm [1]
	speed. data [ 4 ] = 0x00;				//motor speed
	speed. data [ 5 ] = 0x00;				//motor rpm [0]
	speed. data [ 6 ] = 0x00;				//motor rpm [1]
	speed. data [ 7 ] = 0x00;			//status flag
	
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
	
	motorSpeed = 40250/avgCount;
	
	send();
}

ISR (TIMER1_CAPT_vect)
{
	Capt1 = ICR1;
	TCNT1 = 0;
	totalCount = totalCount + Capt1;
	numCount++;
	
	if(totalCount > 50000) //could this be the issue for being stuck at 1 instead of going to 0???
	{
		motorCalcs();
	}
}

ISR(TIMER1_OVF_vect)
{
	send();
	//if(totalCount < 50000); //finish this
}

void timer1_init()
{
	TCNT1 = 0;
	TCCR1B &=~ (1<<ICES1); //falling edge select
	TCCR1B |= (1<<CS11) | (1<<CS10); //prescaler: 64
	TIMSK1 |= (1<<ICIE1) | (1<<TOIE0); //enable overflow-interrupts
	totalCount = 0;
	numCount = 0;
}

int main(void)
{
	//initializations
	timer1_init();
	
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
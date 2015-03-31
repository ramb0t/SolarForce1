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
#include "main.h"
#include "AVR_SPI.h"


void magnet()
{
	if (PINB & (1 << PB1)) //((PinB & (1 << HES1)) == (1 << HES1))
	{
		//increase half_rev when magnet is detected
		half_rev++;
		UDR0 = 0x01; //print to serial as sign of detection
		
		CANMessage speed;
		
		speed. id = 0x0101;
		speed. rtr = 0 ;
		speed. length = 2 ;
		speed. data [ 0 ] = 0x06;
		speed. data [ 1 ] = 0x09;
		
		CAN_sendMessage (&speed);
	}
	
	//else 
	//UDR0 = 0x02;
	//_delay_ms(300);
}

ISR(INT0_vect)
{
	//to run when there is an interrupt from HES
	half_rev++;
}

void initInterrupt0(void)
{
	EIMSK |= (1 << INT0); //enable INT0
	EICRA |= (1 << ISC00); // trigger when button changes
	sei(); // set (global) interrupt enable bit
}

void initComms(unsigned int baudRate)
{
	//set baud rate to 4800
	UBRR0H = (unsigned char)(baudRate>>8);
	UBRR0L = (unsigned char) baudRate;
	UCSR0B = (1<<TXEN0);	
}

int main(void)
{
	//initializations
	initInterrupt0();
	initComms(12);
	
	SPI_Init(); // setup SPI	
	CAN_Init(CAN_125KBPS_16MHZ);
	
	DDRD = 0x00; //set port D as input pins
	PORTD = 0xff; // set pull ups
	
	volatile int half_rev;
	unsigned int rpm = 0;
	unsigned int speed = 0;
	
	UDR0 = 0x04;
	
	//while(1==1){
	//	magnet();
	//}

    while(1)
    {
        TCCR0A |= (1 << CS01) | (1 << CS00);
		//set prescaler to 64 and start the timer
		
		
		CANMessage speed;
		
		speed.id = 1053;
		speed.rtr = 0 ;
		speed.length = 2 ;
		speed.data [ 0 ] = 0x06;
		speed.data [ 1 ] = 0x09;
		
		CAN_sendMessage (&speed);
		
		while((TIFR0 & (1 << TOV0) ) == 0) //wait for first overflow event
		{
			magnet();
		}
		TIFR0 &= ~(1 << TOV0);
		//reset the overflow flag
		
		if(half_rev >= 20){
			rpm = 30*1000/1000*half_rev;
			UDR0 = half_rev;
			half_rev = 0;
			speed = (rpm*(18*3.14)/60)*2;
			UDR0 = speed;
			}
	}
}
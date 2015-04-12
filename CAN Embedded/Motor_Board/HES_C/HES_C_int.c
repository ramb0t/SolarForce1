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
#include "../lib/CAN/CAN.h" //sort this shit out bitch
#include "main.h"
#include "AVR_SPI.h"

/*void magnet()
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
}*/

ISR(INT0_vect)
{
	//to run when there is an interrupt from HES
	half_rev++;
	UDR0 = 0x01; //for debugging purposes
	
	//LED to indicate interrupt has occurred
	PORTC |= (1<<PORTC2);   
	_delay_ms(100);        
	PORTC &= ~(1<<PORTC2);
	_delay_ms(100);
	
}

int speedCalc(volatile int revNum)
{
	//calculations function
	/*takes in number of half_rev and performs calculations
	  outputs the speed value
	  half_rev will be incremented each time detection is made
	  in 1ms time period, therefore half_rev value will be different
	  each time, but will always be 1ms = "1000 ticks" */
		
	rpm = 30*1000/1000*revNum;
	UDR0 = revNum;
	speed = (rpm*(18*3.14)/60)*2;
	UDR0 = speed;
	
	return speed;
}

void ISR(TIMER0_OVF_vect)
{
	TCNT0 +
};

void initInterrupt0(void)
{
	//setting up interrupts
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
	
    while(1)
    {
		TIMSK0 |= (1 << TOIE0);
        TCCR0A |= (1 << CS01) | (1 << CS00); //set prescaler to 64 and start the timer
		
		while(1)
		{
			//magnet();
		}
		
		speedCalc(half_rev);
		
		half_rev = 0; //reset to 0
		
		//output to CAN
		CANMessage speed;
	
		speed. id = 0x0011;
		speed. rtr = 0 ;
		speed. length = 2 ;
		speed. data [ 0 ] = speedCalc(0);
		speed. data [ 1 ] = speedCalc(1);
	
		CAN_sendMessage (&speed);
	}
}
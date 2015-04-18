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

volatile int half_rev;
volatile int rpm = 0;
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
	//rpm = 30*1000/1000*half_rev;
	//hSpeed = (rpm*(18*3.14)/60)*2;
	rpm = 30*half_rev;
	step = rpm*126; //126 is diameter*314 for pi
	hSpeed = step/300; //this value has the decimal point in the value, must divide by 10 on other side
	
	/*CANMessage test;
	
	test. id = 0x0006;
	test. rtr = 0 ;
	test. length = 4 ;
	test. data [ 0 ] = half_rev;
	test. data [ 1 ] = rpm;
	test. data [ 2 ] = step;
	test. data [ 3 ] = hSpeed;
	
	CAN_sendMessage (&test);*/
	
	//half_rev = 0; //reset to 0	
	//send();
}

ISR(INT0_vect)
{
	//to run when there is an interrupt from HES
	//increment the value of the count by one each time
	//the magnet is detected
	//use this value to calculate the rpms
	half_rev++;
	
	/*CANMessage test1;
	
	test1. id = 0x0001;
	test1. rtr = 0 ;
	test1. length = 1 ;
	test1. data [ 0 ] = half_rev;
	
	CAN_sendMessage (&test1);*/
}

void initInterrupt0(void)
{
	EIMSK |= (1 << INT0); //enable INT0
	EICRA |= (1 << ISC00); // trigger when button changes
}

/*void initComms(unsigned int baudRate)
{
	//set baud rate to 4800
	UBRR0H = (unsigned char)(baudRate>>8);
	UBRR0L = (unsigned char) baudRate;
	UCSR0B = (1<<TXEN0);	
}*/

int main(void)
{
	//initializations
	//initComms(12); //for own testing
	initInterrupt0();
	timer0_init();
		
	SPI_Init(); // setup SPI	
	CAN_Init(CAN_125KBPS_16MHZ);
	
	DDRD = 0x00; //set port D as input pins
	PORTD = 0xff; // set pull ups
	
    while(1)
    {
        //do something
	}
}
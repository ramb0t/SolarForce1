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
	//rpm = 30*1000/1000*half_rev;
	//hSpeed = (rpm*(18*3.14)/60)*2;
	//rpm = 30*half_rev;
	//rpm/60 = rps, rps*161 = m/s, m/s*3.6 = km/h
	//step = rpm*161; //161 is circumference in cm
	//hSpeed = step/300; //this value has the decimal point in the value, must divide by 10 on other side
	//half_rev = 0; //reset to 0	
	//send();
	
	
	if (hallRev > 0)
	{
		avgCountH = totalCountH/step2; 
	}
		else
	{
		avgCountH = 0;
	}
	
	totalCountH = 0;
	Capt2 = 0;
	
	hSpeed = 40000/avgCountH;
	
	
	CANMessage tryit;
	
	tryit. id = 0x0006;
	tryit. rtr = 0 ;
	tryit. length = 7 ;
	tryit. data [ 0 ] = 0x04;
	tryit. data [ 1 ] = hSpeed;
	/*test. data [ 0 ] = half_rev>>8;
	test. data [ 1 ] = half_rev;
	test. data [ 2 ] = rpm>>8;
	test. data [ 3 ] = rpm;
	test. data [ 4 ] = step>>8;
	test. data [ 5 ] = step;
	test. data [ 6 ] = hSpeed;*/
	
	CAN_sendMessage (&tryit);
}

ISR(INT0_vect)
{
	//to run when there is an interrupt from HES
	//increment the value of the count by one each time
	//the magnet is detected
	//use this value to calculate the rpms
	//half_rev = half_rev + 1;
	
	//need debouncing here!!!!
	//if magnet passes by slowly, picks up more than one interrupt
	
	step2 = count2*5; //number of overflows*0.5ms
	Capt2 = Capt2/10; //5 divided by 10 = 0.5
	
	totalCountH = totalCountH + Capt2;
	
	hallRev++;
	
	if (totalCountH > 50000)
	{
		speedCalcs();
	}
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
	timer2_init();
		
	SPI_Init(); // setup SPI	
	CAN_Init(CAN_125KBPS_16MHZ);
	
	DDRD = 0x00; //set port D as input pins
	PORTD = 0xff; // set pull ups
	
    while(1)
    {
	
	}
}
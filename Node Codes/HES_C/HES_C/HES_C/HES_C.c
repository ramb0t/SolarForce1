/*
 * HES_C.c
 *
 * Created: 16/03/2015 02:48:28 PM
 *  Author: Terayza
 */ 

#define F_CPU 16000000L
#define HES1 1
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int half_rev;

void magnet()
{
	if (PINB & (1 << PB1)) //((PORTB & (1 << HES1)) == (1 << HES1))
	{
		//increase half_rev when magnet is detected
		half_rev++;
		UDR0 = 0x01; //print to serial as sign of detection
	}
	//else 
	//UDR0 = 0x02;
	//_delay_ms(300);
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
	//timerSetup();
	initComms(12);
	
	DDRB = 0x00; //set port B as input pins
	PORTB = 0xff; // set pullups
		
	int rpm = 0; //unsigned
	int speed = 0; //unsigned
	
	UDR0 = 0x04;
	
	//while(1==1){
	//	magnet();
	//}


    while(1)
    {
        TCCR0A |= (1 << CS01) | (1 << CS00);
		//set prescaler to 64 and start the timer
		
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

//need substitute for millis fcn in arduino
//millis uses timer 0
//start_time = timer
//function()
//exec_time = timer - start_time

//void timerSetup()
//{
	//start the timer
	//TIMSK0 |= (1 << TOIE0);
	//sei();
	//enable interrupts
	//TCCR0A |= (1 << CS01) | (1 << CS00); //set prescaler to 64 and start the timer
//}

//ISR (TIMER0_OVF_vect) //timer0 overflow interrupt
//{
	//TCNT0 += 6; //add 6 to the register
//}
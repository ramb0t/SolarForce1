/*
 * PrototypeFirmware.c
 *
 * Created: 2015/02/20 01:06:37 AM
 *  Author: Sulaiman
 */ 

#define F_CPU 1e6
#define ACK 0x55

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int count = 0;
int vals[] = {3, 58, 240, 9};
volatile int prev_capture = 0;
volatile int current_capture = 0;
int a = 0;

typedef union
{
	uint8_t all;
	struct 
	{
		uint8_t connected: 1,
				undef1: 1,
				undef2: 1,
				undef3: 1,
				undef4: 1,
				undef5: 1,
				undef6: 1,
				undef7: 1;
	};
} FLAGS;

typedef union
{
	uint8_t packet[7];
	struct
	{
		uint8_t ID: 7,
				Type: 1;
		uint8_t length;
		uint8_t payload[4];
		uint8_t end_of_transfer;
	};
}PACKET;

static FLAGS myFlags;

void timer1Start()
{
	TCCR1B |=  (1<<CS12) | (1<<CS10);
}

void InitComms(unsigned int baudRate)
{
	//set baud rate 
	UBRRH = (unsigned char)(baudRate>>8);
	UBRRL = (unsigned char) baudRate;
	UCSRB = (1<<TXEN) | (1<<RXEN) | (1<<RXCIE);
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0) | (1<<UPM1) | (1<<UPM0) | (1<<USBS);
}

int main(void)
{
	
	//configure the uC to transmit serial data
	InitComms(12);
	myFlags.all = 0; //clear all user-defined flags
	DDRA = 0xff;
	
	//setup timer 1 for input capture.
	//TIMSK |= 1<<TICIE1;
	//TCCR1B = (1<<ICES1);
	//timer1Start();
	//enable global interrupts
	sei();
	

	
	while(1)
    {
		PACKET test;
		test.ID = 0b1000001;
		test.Type = 1;
		int P = test.Type | (test.ID<<1);
		//
		if (myFlags.connected != 1) 
		{
			UDR = 0x3f;
		}
		else
		{
			_delay_ms(100);
			PORTA = P;
			_delay_ms(100);	
			PORTA = 0x00;
		}
    }
}

void transmit_packet(PACKET p)
{
	do
	{
		UDR = p.Type | (p.ID<<1);
	}while (waitingForAck());
	do 
	{
		UDR = p.length;
	} while (waitingForAck()==1);
}

int waitingForAck()
{
	int retVal = (UDR != ACK) ? 1 : 0;
	return retVal;
}

ISR (TIMER1_CAPT_vect)
{
	prev_capture = current_capture;
	current_capture = ICR1;
}

ISR(USART_RXC_vect)
{
	if (UDR == ACK)
	{
		myFlags.connected = 1;
		UCSRB &= ~(1<<TXEN);
	}
}

/*
ISR(USART_UDRE_vect)
{
	if (count<3)
		UDR = vals[count++];
	else
	{
		UDR = vals[count];
		count = 0;
	}
}*/
/*
 * PrototypeFirmware.c
 *
 * Created: 2015/02/20 01:06:37 AM
 *  Author: Sulaiman
 */ 

#define F_CPU 1e6
#define ACK 0x06
#define PING 0x05

enum uint8_t {BMS, MPPT1, MPPT2, MPPT3, MPPT4,
			  HE_left, HE_right, MotorDriver,
			  GPS,
			  Incline, Accel,//for encoding purposes --> match the enum to Matt's MAVlink ID for these
			  WindSpeed = 1, Irrad = 2}; //local sensors

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
				ID_sent: 1,
				length_sent: 1,
				payload_sent: 1,
				ID_received_ack: 1,
				length_received_ack: 1,
				payload_received_ack: 1,
				undef7: 1;
	};
} FLAGS;

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
	UCSRB = (1<<TXEN) | (1<<RXEN) ;//| (1<<RXCIE);
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0) | (1<<UPM1) | (1<<UPM0) | (1<<USBS);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

void DoSim(uint8_t x)
{
	USART_Transmit('>');
	USART_Transmit('>');
	USART_Transmit(0xa4);
	USART_Transmit(',');
	USART_Transmit(x);
	USART_Transmit('<');
	USART_Transmit('<');
	USART_Transmit(',');
	_delay_us(500);
}

void transmit_packet(PACKET p)
{
	myFlags.ID_received_ack = 0;
	myFlags.ID_sent = 0;
	myFlags.length_received_ack = 0;
	myFlags.length_sent = 0;
	myFlags.payload_received_ack = 0;
	myFlags.payload_sent = 0;
	
	//transmit ID and Type
	UDR = (p.ID << 1) | p.Type;
	myFlags.ID_sent = 1;
	while (myFlags.ID_received_ack == 0); //wait for ack
	
	//transmit length of payload
	UDR = p.length;
	myFlags.length_sent = 1;
	while(myFlags.length_received_ack == 0); //wait for ack
	
	//transmit payload
	for (int i = 0; i<p.length; i++)
	{
		UDR = p.payload[i];
		while (TXC==0);
	}
	myFlags.payload_sent = 1;
	while (myFlags.payload_received_ack == 0); //wait for ack
}

int main(void)
{
	
	//configure the uC to transmit serial data
	InitComms(12);
}
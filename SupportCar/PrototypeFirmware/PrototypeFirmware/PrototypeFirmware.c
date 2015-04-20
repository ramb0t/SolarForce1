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
	UCSRB = (1<<TXEN) | (1<<RXEN) ;//| (1<<RXCIE);
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0) | (1<<UPM1) | (1<<UPM0) | (1<<USBS);
}

PACKET makePacket(int identifier)
{
	PACKET pkt;
	switch(identifier)
	{
		case BMS:
			pkt.ID = 1;
			break;
		case HE_right:
			pkt.ID = 2;
			break;
		case HE_left:
			pkt.ID = 3;
			break;
		case WindSpeed:
			pkt.ID = 4;
			break;
		case Irrad:
			pkt.ID = 5;
			break;
		//add other sensors
	}
	return pkt;
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
		DoSim(60);
		DoSim(113);
		DoSim(8);
		DoSim(90);
		DoSim(85);
		
		/*PACKET test;
		test.ID = 0b1000001;
		test.Type = 1;
		int P = test.Type | (test.ID<<1);
		transmit_packet(test);
		//
		if (myFlags.connected != 1) 
		{
			UDR = PING;
		}
		else
		{
			_delay_ms(100);
			PORTA = P;
			_delay_ms(100);	
			PORTA = 0x00;
		}*/
    }
}

ISR (TIMER1_CAPT_vect)
{
	prev_capture = current_capture;
	current_capture = ICR1;
	
}

ISR(USART_RXC_vect)
{
	if (UDR == ACK)//check if ack is received
	{
		if (myFlags.connected != 1)//if the ack is for checking initial connection
		{
			myFlags.connected = 1;//connected flag is set
		}
		else if (myFlags.ID_received_ack != 1 && myFlags.ID_sent == 1)//if the ack is for receiving the ID
		{
			myFlags.ID_received_ack = 1;
		}
		else if (myFlags.length_received_ack != 1 && myFlags.length_sent == 1)//if the ack is for receiving the payload length
		{
			myFlags.length_sent = 1;
		}
		else if(myFlags.payload_received_ack != 1 && myFlags.payload_sent == 1)//if the ack is for receiving the payload
		{
			myFlags.payload_sent = 1;
		}
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
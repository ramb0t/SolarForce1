/*
 * MotorRead.c
 *
 * Created: 12/04/2015 02:27:14 PM
 *  Author: Terayza
 */ 

#define F_CPU 16000000UL
/*#define UART_BAUD_RATE		76800
#define UART_DDR			DDRD
#define UART_REG			UCSR0A*/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "../lib/CAN/CAN.h"
#include "../lib/mcp2515/mcp2515.h"
#include "../lib/SPI/AVR_SPI.h"
#include "../lib/uart/uart.h"

volatile uint16_t inputCaptureVals[] = {0,0,0,0,0,0};
volatile uint16_t count = 0;

volatile uint32_t sum = 0;
volatile uint32_t avgCount = 0;
volatile uint32_t avgPeriod = 0;
volatile uint32_t freq = 0;
volatile uint32_t rpm = 0;
volatile uint32_t step = 0;
volatile uint32_t motorSpeed = 0;

/*void initComms(unsigned int baudRate)
{
	//set baud rate to 4800
	UBRR0H = (unsigned char)(baudRate>>8);
	UBRR0L = (unsigned char) baudRate;
	UCSR0B = (1<<TXEN0);
}*/

void timerSetUp()
{
	TIMSK1 |= 1<<ICIE1;
	//TCCR1B = (1<<ICES1);
	//TCCR1B |=  (1<<CS11) | (1<<CS10);
	TCCR1B |=  (1<<CS12);
}

/*ISR (ANALOG_COMP_vect)
{
	using this interrupt to tell when 6 input captures
	  have arrived
	uint32_t sum = 0;
	
	for (int i = 1; i < 6; i++)
	{
		if(inputCaptureVals[i] < inputCaptureVals[i - 1])
		{
			sum += 0xFFFF;
		}
		
		sum += (inputCaptureVals[i] - inputCaptureVals[i - 1]);
		UDR0 = 0x06; //test purposes
	} 
	
	//Motor Speed calculations FIND CALCS
	avgPeriod = 5/sum;
	motorSpeed = (20*(pi^2))/sum)*r_wheel;
}*/

void send()
{
	CANMessage speed;
	
	speed. id = 0x0420;
	speed. rtr = 0 ;
	speed. length = 8 ;
	speed. data [ 0 ] = motorSpeed>>24;			//average speed
	speed. data [ 1 ] = motorSpeed>>16;				//hall speed
	speed. data [ 2 ] = ICR1>>8;				//hall rpm [0]
	speed. data [ 3 ] = ICR1;				//hall rpm [1]
	speed. data [ 4 ] = inputCaptureVals[0];				//motor speed
	speed. data [ 5 ] = inputCaptureVals[0]>>8;				//motor rpm [0]
	speed. data [ 6 ] = ICR1L;				//motor rpm [1]
	speed. data [ 7 ] = ICR1H;				//status flag
	
	CAN_sendMessage (&speed);
	_delay_ms(250);
}

void calcs()
{
	//Motor Speed calculations FIND CALCS
	//NB: *4 and /6 has been swapped to keep accuracy #benlifehack
	avgCount = sum*4;  //average count is the sum of 5 differences divided by 5
	avgPeriod = avgCount/6; //average period in micro second (us)
	step = 1600000/avgPeriod;
	//motorSpeed = step*10; //motorSpeed value now contains last bit as decimal, when received, must multiplied by 10
	
	/*
	freq = 1/avgPeriod; //frequency is = 1/T
	freq = 5000/sum; //should be 5, multiplying by 1000
	rpm = 6000000/avgPeriod; ///avgPeriod; //freq to rpm is 1:60

	wheel diameter (including tire) is 20inches
	step1 = rpm*508*314; //508 is 50.8cm diameter, 314 is pi
	step2 = step1/60000;
	step3 = step2*36;
	motorSpeed = step3/100; //motorSpeed value now contains last bit as decimal, when received, must divide by 10*/
	motorSpeed = sum;
	send();
}

ISR (TIMER1_CAPT_vect)
{
	//TCNT1H = 0;
	//TCNT1L = 0;
	
	inputCaptureVals[0] = ICR1L;
	inputCaptureVals[0] |= ICR1H<<8;
	TCNT1H = 0;
	TCNT1L = 0;
	
	send();
	//inputCaptureVals[count] = 0x00000000;
	//inputCaptureVals[count] = ICR1L;
	//inputCaptureVals[count] |= ICR1H<<8;
	//
	//count++;
	//
	//if (count == 6)
	//{
		//count = 0;
		//sum = 0;
		//
		//for (int i = 0; i < 6; i++)
		//{
			//sum += inputCaptureVals[i];
		//}
			//
		//calcs();
		//
		////ACSR |= (1 << ACI);
	//}
}

int main(void)
{
	//initializations
//	initComms(12);
	timerSetUp();
	
	//UART TEST STUFF ONLY

	/*UART_DDR |= _BV(DDD1);	//output

	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );*/
	
	
	
	SPI_Init(); // setup SPI
	CAN_Init(CAN_125KBPS_16MHZ);
	
	DDRB &= ~(1 << PORTB0); //set PB0 as input
	PORTB |= (1<< PORTB0);  //pull up
	
	UDR0 = 0x04; //test purposes
	sei();
    while(1)
    {	
        	/*uart_puts("Hello World!");
        	//---------------------------*/
			

    }
}
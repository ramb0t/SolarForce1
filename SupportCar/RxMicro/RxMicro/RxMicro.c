/*
 * RxMicro.c
 *
 * Created: 2015/03/30 04:27:38 AM
 *  Author: Sulaiman
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16e6
#define MAX_CAPTURE 15


#pragma region ADC Functions

//initialise the adc
void init_adc(uint8_t channel)
{
	//adc reference is AVcc
	//Single Ended Mode
	ADMUX |= (1<<REFS0);
	
	ADMUX |= channel;
	//MUX5 is in ADCSRB!
	if (channel>=8 && channel <=13)
	ADCSRB |= (1<<MUX5);
	else
	ADCSRB &= ~(1<<MUX5);
	
	//Enable ADC with conversion completed interrupt
	//assume single conversion mode
	ADCSRA = (1<<ADEN) | (1<<ADIE);
}

typedef enum uint8_t {Prescalar2 = 1,
	Prescalar4 = 2,
	Prescalar8 = 3,
	Prescalar16 = 4,
	Prescalar32 = 5,
	Prescalar64 = 6,
Prescalar128 = 7} PRESCALAR;

void setPrescalar(PRESCALAR p)
{
	ADCSRA |= p;
}

//allows the disabling of a digital input to reduce power consumption
void disable_digital_input(uint8_t channel)
{
	if (channel<=7)
	{
		DIDR0 |= 1<<channel;
	}
	else if(channel<=13)
	{
		DIDR1 |= 1<<(channel-8);
	}
}

uint16_t adc_read()
{
	ADCSRA |= 1<<ADSC;
}

#pragma endregion
#pragma region Timer Setups

//setup timer 3 for input capture
void init_timer3_ICP()
{
	//enable input capture noise canceller and trigger on a rising edge
	//choose prescaler of /256... gives 62500 clocks for max freq and 16us resolution
	TCCR3B = (1<<ICES3)|(1<<CS32)|(1<<ICNC3);
	
	//setup input capture interrupt and overflow interrupt
	TIMSK3 = (1<<TOIE3)|(1<<ICIE3);
}

uint32_t sum_capture = 0;
uint8_t count_capture = 0;

#pragma endregion
#pragma region Flag Setup

typedef union
{
	uint8_t all;
	struct
	{
		uint8_t ADC_read_complete: 1,
				ICP_ready: 1;
	};
} FLAGS;

static volatile FLAGS myFlags;

#pragma endregion

int main(void)
{
	DDRC = 0xff;
	myFlags.all = 0;
	
	init_adc(13);
	disable_digital_input(13);
	setPrescalar(Prescalar128);
	
    while(1)
    {
		uint8_t counter = 0; //counts the number of messages received from the solar car to determine when to send a support car packet
		
        //insert MAVLink decoding here
		
		counter++;//increment counter
		
		if (counter == 75) //condition to read from the irradiance sensor
		{
			 adc_read();
		}
		
		//if an ADC reading is ready for transmission
		if (myFlags.ADC_read_complete == 1)
		{
			//debug thingy
			PORTC = 0xff;
			_delay_ms(500);
			PORTC = 0;
			_delay_ms(500);
			
			
			//proper code will send the string ">>13,ADC<<"
			myFlags.ADC_read_complete = 0;//clear the flag	
		}
		
		//if a wind speed reading is ready for transmission
		if (myFlags.ICP_ready == 1)
		{
			//calculate wind speed
			//w_Speed = 4.02336kmph/Hz * (sum_capture_times/count_captures (in counts) * 16us/count)^-1
			//			this will give 4.02336km/hour @ 1 Hz which is min resolution
			//			multiply by a thousand (m/hour) and then let the PC take care of things :D
			
			//for debugging, check freq against scope
			uint32_t freq = 1e6*count_capture/sum_capture/16;
			
			//for actual system, use this
			uint32_t wind_speed = 1e9*4.02336/16*count_capture/sum_capture;
			
			//sends the string ">>8,wind_speed<<
			myFlags.ICP_ready = 0;
		}
		
    }
}

#pragma region ISRs

ISR(ADC_vect)
{
	myFlags.ADC_read_complete = 1;
}

ISR(TIMER3_CAPT_vect)
{
	sum_capture += ICR3;//add ICR value to sum of captures
	TCNT3 = 0;//clear timer so ICR value always starts at 0
	count_capture++;//increment count of captures
	if (count_capture == MAX_CAPTURE)//if Max Captures were reached (max captures = 15)
	{
		myFlags.ICP_ready = 1;//set flag indicating ready to average values
	}
}

ISR(TIMER3_OVF_vect)
{
	myFlags.ICP_ready = 1;
	count_capture++;
	sum_capture = 0xFFFF;
}

#pragma endregion
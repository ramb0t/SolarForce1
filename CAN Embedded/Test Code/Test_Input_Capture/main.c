/*
 * main.c
 *
 *  Created on: 17 Apr 2015
 *      Author: rambo
 */


//#include <avr/iom328p.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// CAN Application Layer
#include "../../lib/CAN/CAN.h"
// MCP2515 Library
#include "../../lib/mcp2515/mcp2515.h"
// SPI Library used with CAN Controller
#include "../../lib/SPI/AVR_SPI.h"

#define UART_BAUD_RATE 115200
#include "../../lib/uart/uart.h"
// Handy uart functions
//#include "../../lib/uart/uart_CANFunc.h"
#include <string.h>



//Counts overflovs
volatile uint16_t T1Ovs1, T1Ovs2;
//Variables holding three timestamps
volatile uint16_t Capt1, TotalCount, Capt3;
//capture Flag
volatile uint8_t NumCount;
//Initialize timer
void InitTimer1(void)
{
//Set Initial Timer value
TCNT1=0;
//change capture on falling edge
        TCCR1B&=~(1<<ICES1);
//64 prescaler
TCCR1B |= (1<<CS11)|(1<<CS10);
//Enable input capture and overflow interrupts
//TIMSK |= (1<<ICIE1)|(1<<TOIE1);
TIMSK1|= (1<<ICIE1)|(1<<TOIE1);
TotalCount = 0;
NumCount = 0;
}
void StartTimer1(void)
{
//Start timer without prescaller
//TCCR1B|=(1<<CS10);
//Enable global interrutps
sei();
}

void sendSpeed(){
	uint16_t avgCount ;
	if(NumCount > 0){
		avgCount = TotalCount/NumCount;
	}else{
		avgCount = 0;
	}
	TotalCount = 0;
	NumCount = 0;
	char buffer[10];
	utoa(avgCount,buffer,10);
	uart_puts(buffer);
	uart_puts("\n");

	uint16_t speed = 40000 / avgCount;  // This is fucking clever!
	utoa(speed,buffer,10);
	uart_puts(buffer);
	uart_puts("\n");



}

//capture ISR
ISR(TIMER1_CAPT_vect)
{
	Capt1=ICR1;
	TCNT1=0;
	TotalCount = TotalCount + Capt1;
	NumCount++;
	//char buffer[10];
	//utoa(Capt1,buffer,10);
	//uart_puts(buffer);
	//uart_puts("icp\n");
	if(TotalCount > 50000){ // it has been ~200mS since the timer started
		sendSpeed();
	}

//if (Flag==0)
//    {
//        //save captured timestamp
//        Capt1=ICR1;
//        //change capture on falling edge
//        TCCR1B&=~(1<<ICES1);
//        //reset overflows
//        T1Ovs2=0;
//    }
//if (Flag==1)
//    {
//        Capt2=ICR1;
//        //change capture on rising edge
//        TCCR1B|=(1<<ICES1);
//        //save first overflow counter
//        T1Ovs1=T1Ovs2;
//    }
//if (Flag==2)
//    {
//        Capt3=ICR1;
//        //stop input capture and overflow interrupts
//        TIMSK1&=~((1<<ICIE1)|(1<<TOIE1));
//    }
////increment Flag
//Flag++;
}
//Overflow ISR
ISR(TIMER1_OVF_vect)
{
	sendSpeed();
}





int main(void)
{
//dutycycle result holder
volatile uint8_t DutyCycle;
InitTimer1();
// Init UART
	uart_init( UART_BAUD_SELECT_DOUBLE_SPEED(UART_BAUD_RATE,F_CPU) );

StartTimer1();

    while(1)
    {
//        //calculate duty cycle if all timestamps captured
//        if (Flag==3)
//        {
//                DutyCycle=(uint8_t)((((uint32_t)(Capt2-Capt1)+((uint32_t)T1Ovs1*0x10000L))*100L)
//                    /((uint32_t)(Capt3-Capt1)+((uint32_t)T1Ovs2*0x10000L)));
//                //send Duty Cycle value to LCD or USART
//                //clear flag
//                Flag=0;
//                //clear overflow counters;
//                T1Ovs1=0;
//                T1Ovs2=0;
//                //clear interrupt flags to avoid any pending interrupts
//                TIFR1=(1<<ICF1)|(1<<TOV1);
//                //enable input capture and overflow interrupts
//                TIMSK1|=(1<<ICIE1)|(1<<TOIE1);
//        }

    	_delay_ms(1000);
    	uart_puts("hello!");
    	uart_puts("\n");
    }
}

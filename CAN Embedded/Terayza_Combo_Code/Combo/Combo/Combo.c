/*
 * Combo.c
 *
 * Created: 17/04/2015 04:43:14 PM
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
#include "timer1.h"
#include "timer2.h"
#include "I2C.h"

volatile uint16_t count2 = 0;
volatile uint8_t hSpeed = 0;
volatile uint16_t hRPM = 0;
volatile uint16_t count0 = 0;
volatile uint8_t motorSpeed = 0;
volatile uint16_t motorRPM = 0;
volatile uint8_t numCount1;
volatile uint16_t totalCount;
volatile uint16_t avgCount;
volatile uint8_t status;

void send()
{
	//*****************************************
	//Speed sending
	//*****************************************
	volatile uint8_t avgSpeed;
	avgSpeed = (hSpeed + motorSpeed)/2;
	status = 0; //decide status things 
	
	CANMessage speed;
	
	speed. id = 0x0420;
	speed. rtr = 0 ;
	speed. length = 8 ;
	speed. data [ 0 ] = avgSpeed;
	speed. data [ 1 ] = hSpeed;
	speed. data [ 2 ] = hRPM>>8;
	speed. data [ 3 ] = hRPM;
	speed. data [ 2 ] = motorSpeed;
	speed. data [ 5 ] = motorRPM>>8;
	speed. data [ 6 ] = motorRPM;
	speed. data [ 7 ] = status;
	
	CAN_sendMessage (&speed);
	
	//*****************************************
	//MPU6050 sending
	//*****************************************
	/*CANMessage angle;
	
	angle. id = 0x0820;
	angle. rtr = 0 ;
	angle. length = 3 ;
	angle. data [ 0 ] = theta>>8;
	angle. data [ 0 ] = theta;
	angle. data [ 1 ] = phi>>8;
	angle. data [ 1 ] = phi;
	angle. data [ 2 ] = psi>>8;
	angle. data [ 2 ] = psi;
	
	CAN_sendMessage (&angle);
	
	CANMessage gyroscope;
	
	gyroscope. id = 0x0821;
	gyroscope. rtr = 0 ;
	gyroscope. length = 3 ;
	gyroscope. data [ 0 ] = MPU6050_ReadGyro(0)>>8; //therefore x values
	gyroscope. data [ 1 ] = MPU6050_ReadGyro(0);
	gyroscope. data [ 2 ] = MPU6050_ReadGyro(1)>>8;
	gyroscope. data [ 3 ] = MPU6050_ReadGyro(1);
	gyroscope. data [ 3 ] = MPU6050_ReadGyro(2)>>8;
	gyroscope. data [ 3 ] = MPU6050_ReadGyro(2);
	
	CAN_sendMessage (&gyroscope);
	
	CANMessage accelerometer;
	
	accelerometer. id = 0x0822;
	accelerometer. rtr = 0 ;
	accelerometer. length = 3 ;
	accelerometer. data [ 0 ] = MPU6050_ReadAccel(0)>>8;
	accelerometer. data [ 1 ] = MPU6050_ReadAccel(0);
	accelerometer. data [ 2 ] = MPU6050_ReadAccel(1)>>8;
	accelerometer. data [ 3 ] = MPU6050_ReadAccel(1);
	accelerometer. data [ 4 ] = MPU6050_ReadAccel(2)>>8;
	accelerometer. data [ 5 ] = MPU6050_ReadAccel(2);
	
	CAN_sendMessage (&accelerometer);*/
}

//*****************************************
//Calculation for motor speed
//*****************************************
void motorCalcs()
{
	if(numCount1 > 0)
	{
		avgCount = totalCount/numCount1;
	}
	else
	{
		avgCount = 0;
	}
	
	totalCount = 0;
	numCount1 = 0;
	
	motorSpeed = 40250/avgCount;
	
	motorRPM = 416666/avgCount; //value should be 41666.6667
}

//*****************************************
//Interrupt 0 ISR
//Used for Hall Effect Sensor
//*****************************************
ISR(INT0_vect)
{
	volatile uint16_t Capt2 = 0;
	
	//need debouncing here!!!!
	//if magnet passes by slowly, picks up more than one interrupt
	
	//number of overflows * counts per overflows
	Capt2 = (count2*125 + (TCNT2 - TIMEBASE_RELOAD2)); //125 is the number of counts that it counts
	
	count2 = 0;
	TCNT2 = TIMEBASE_RELOAD2; //reload timer
	
	//place in circum depending on where its mounted on wheel
	//24.5cm diameter on my bike, therefore circum = 0.76969m
	//90000* circum = 69272.11801
	hSpeed = (69272)/Capt2;
	
	hRPM = 15000000/Capt2;
}

//*****************************************
//Input Capture ISR
//Used for the motor controller
//*****************************************
ISR (TIMER1_CAPT_vect)
{
	volatile uint16_t Capt1;
	
	Capt1 = ICR1;
	TCNT1 = 0;
	totalCount = totalCount + Capt1;
	numCount1++;
	
	if(totalCount > 50000) //could this be the issue for being stuck at 1 instead of going to 0???
	{
		motorCalcs();
	}
}

//*****************************************
//Initilising Interrupts
//*****************************************
void initInterrupt0(void)
{
	EIMSK |= (1 << INT0); //enable INT0
	EICRA |= (1 << ISC00); // trigger when button changes
}

int main(void)
{
	//*****************************************
	//Initializations
	//*****************************************
	initInterrupt0();
	timer0_init();
	timer1_init();
	timer2_init();
	
	//*****************************************
	//CAN Send things
	//*****************************************
	SPI_Init(); // setup SPI
	CAN_Init(CAN_125KBPS_16MHZ);
	
	//*****************************************
	//MPU6050 Init
	//*****************************************
	TWIM_Init(12);
	TWIM_WriteRegister(107,0); //disable sleep mode
	
	//*****************************************
	//HES Setup
	//*****************************************
	DDRD = 0x00; //set port D as input pins
	PORTD = 0xff; // set pull ups
	
	//*****************************************
	//Motor Controller Setup
	//*****************************************
	DDRB &= ~(1 << PORTB0); //set PB0 as input
	PORTB |= (1<< PORTB0);  //pull up
	
	sei(); 	// set (global) interrupt enable bit
	
	while(1)
	{
		//do something
	}
}


/*
 * Combo.c
 *
 * Created: 17/04/2015 04:43:14 PM
 *  Author: Terayza
 */ 

#define F_CPU 16000000UL
#define HES1 1
#define addr 0x68

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
volatile uint8_t avgSpeed;
volatile uint8_t status;

void send()
{
	//*****************************************
	//Speed sending
	//*****************************************
	
	//avgSpeed = (hSpeed + motorSpeed)/2;
	//status = 0; //decide status things 
	check();
		
	CANMessage speed;
	
	speed. id = 0x0420;
	speed. rtr = 0 ;
	speed. length = 8 ;
	speed. data [ 0 ] = avgSpeed;
	speed. data [ 1 ] = hSpeed;
	speed. data [ 2 ] = hRPM>>8;
	speed. data [ 3 ] = hRPM;
	speed. data [ 4 ] = motorSpeed;
	speed. data [ 5 ] = motorRPM>>8;
	speed. data [ 6 ] = motorRPM;
	speed. data [ 7 ] = status;
	
	CAN_sendMessage (&speed);
	
	//*****************************************
	//MPU6050 sending
	//*****************************************
	/*
	//*****************************************
	//Send angle
	//*****************************************
	float angletheta;
	float anglepsi;
	float anglephi;
	
	angletheta = (atan(MPU6050_CalcAngle(0)/(sqrt((pow(MPU6050_CalcAngle(1),2)) + (pow(MPU6050_CalcAngle(2),2))))))*180/M_PI;
	anglepsi = (atan(MPU6050_CalcAngle(1)/(sqrt((pow(MPU6050_CalcAngle(0),2)) + (pow(MPU6050_CalcAngle(2),2))))))*180/M_PI;
	anglephi = (atan((sqrt((pow(MPU6050_CalcAngle(0),2)) + (pow(MPU6050_CalcAngle(1),2))))/MPU6050_CalcAngle(2)))*180/M_PI;
		
	CANMessage angle;
	
	angle. id = 0x0820;
	angle. rtr = 0 ;
	angle. length = 3 ;
	angle. data [ 0 ] = theta>>8;
	angle. data [ 0 ] = theta;
	angle. data [ 1 ] = phi>>8;
	angle. data [ 1 ] = phi;
	angle. data [ 2 ] = psi>>8;
	angle. data [ 2 ] = psi;
	
	CAN_sendMessage (&angle);*/
	
	//*****************************************
	//Send gyroscope
	//*****************************************
	int16_t tempGX = MPU6050_ReadGyro(0);
	int16_t tempGY = MPU6050_ReadGyro(1);
	int16_t tempGZ = MPU6050_ReadGyro(2);
			
	CANMessage Gyro;
		
	Gyro. id = 0x7A2;
	Gyro. rtr = 0 ;
	Gyro. length = 6 ;
	Gyro. data [ 0 ] = tempGX>>8;
	Gyro. data [ 1 ] = tempGX;
	Gyro. data [ 2 ] = tempGY>>8;
	Gyro. data [ 3 ] = tempGY;
	Gyro. data [ 4 ] = tempGZ>>8;
	Gyro. data [ 5 ] = tempGZ;
			
	CAN_sendMessage (&Gyro);
		
	//*****************************************
	//Send accelerometer
	//*****************************************		
	int16_t tempAX = MPU6050_ReadAccel(0);
	int16_t tempAY = MPU6050_ReadAccel(1);
	int16_t tempAZ = MPU6050_ReadAccel(2);
		
	CANMessage Accel;
	
	Accel. id = 0x07A3;
	Accel. rtr = 0 ;
	Accel. length = 6 ;
	Accel. data [ 0 ] = tempAX>>8;
	Accel. data [ 1 ] = tempAX;
	Accel. data [ 2 ] = tempAY>>8;
	Accel. data [ 3 ] = tempAY;
	Accel. data [ 4 ] = tempAZ>>8;
	Accel. data [ 5 ] = tempAZ;
		
	CAN_sendMessage (&Accel);
}

//*****************************************
//Start of MPU functions
//*****************************************
void TWIM_WriteRegister(char reg, char value)
{
	TWIM_Start(addr, TWIM_WRITE); // set device address and write mode
	TWIM_Write(reg);
	TWIM_Write(value);
	TWIM_Stop();
}

char TWIM_ReadRegister(char reg)
{
	TWIM_Start(addr, TWIM_WRITE);
	TWIM_Write(reg);
	TWIM_Stop();

	TWIM_Start(addr, TWIM_READ); // set device address and read mode
	char ret = TWIM_ReadNack();
	TWIM_Stop();
	return ret;
}

int16_t MPU6050_ReadAccel(int axis)//x = 0; y = 1; z = 2
{
	char reg = axis * 2 + 59;
	char AFS_SEL = TWIM_ReadRegister(28);
	float factor = 1<<AFS_SEL;
	factor = 16384/factor;
	int16_t val = 0;
	float float_val = 0;
	char ret = 0;

	ret = TWIM_ReadRegister(reg);
	val = ret << 8;

	ret = TWIM_ReadRegister(reg+1);
	val += ret;

	if (val & 1<<15)
	val -= 1<<16;
	
	//float_val = val;

	//float_val = float_val / factor;

	//return float_val;
	return val;
}

int16_t MPU6050_ReadGyro(int axis)//x = 0; y = 1; z = 2
{
	PORTC &= ~ (1<< PORTC2);
	
	char reg = axis * 2 + 67;
	char FS_SEL = TWIM_ReadRegister(27);
	float factor = 1<<FS_SEL;
	factor = 131/factor;
	int16_t val = 0;
	float float_val = 0;
	char ret = 0;

	ret = TWIM_ReadRegister(reg);
	val = ret << 8;

	ret = TWIM_ReadRegister(reg+1);
	val += ret;

	if (val & 1<<15)
	val -= 1<<16;
	
	//float_val = val;
	
	//float_val = float_val / factor;

	//return float_val;
	PORTC |= (1<< PORTC2);
	return val;
}

int16_t MPU6050_CalcAngle(int axis)//x = 0; y = 1; z = 2
{
	char reg = axis * 2 + 59;
	char AFS_SEL = TWIM_ReadRegister(28);
	float factor = 1<<AFS_SEL;
	factor = 16384/factor;
	int16_t val = 0;
	float float_val = 0;
	char ret = 0;

	ret = TWIM_ReadRegister(reg);
	val = ret << 8;

	ret = TWIM_ReadRegister(reg+1);
	val += ret;

	if (val & 1<<15)
	val -= 1<<16;
	
	float_val = val;

	float_val = float_val / factor;

	return float_val;
}
//*****************************************
//End of MPU functions
//*****************************************

//*****************************************
//Error checking
//*****************************************
void check()
{
	//go back to send() and sort shit out
	
	//*****************************************
	//Status: Check if all is okay with speed data
	//Length: 1 byte; 8 bits
	//Bit 0: 
	//Bit 1: 
	//Bit 2: 
	//Bit 3: 
	//Bit 4: 
	//Bit 5: 
	//Bit 6: 
	//Bit 7: HES & Motor Controller speeds do not correlate
	//*****************************************
	
	avgSpeed = (hSpeed + motorSpeed)/2;
	
	if (((avgSpeed-motorSpeed) <= 2) & ((avgSpeed-hSpeed) <= 2))
	{
		status = 0x00;
	}
	
	else
	{
		status = 0x01;
	}
	
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


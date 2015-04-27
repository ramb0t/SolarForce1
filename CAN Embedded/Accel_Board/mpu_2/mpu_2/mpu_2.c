/*
 * mpu_2.c
 *
 * Created: 26/04/2015 12:36:31 AM
 *  Author: Terayza
 */ 

#define F_CPU 16000000UL
#define UART_BAUD_RATE 57600
#define addr 0x68
//#define Dev24C02 0xA2 //new

#define LED1_ON	PORTC &= ~(1<<PORTC2);
#define LED2_ON	PORTC &= ~(1<<PORTC3);
#define LED1_OFF	PORTC |= (1<<PORTC2);
#define LED2_OFF	PORTC |= (1<<PORTC3);

// Standard AVR includes
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "I2C.h" //old one
//#include "i2cmaster.h" //new one
#include "../lib/CAN/CAN.h"
#include "../lib/CAN/CAN_defs.h"
#include "../lib/mcp2515/mcp2515.h"
#include "../lib/mcp2515/mcp2515_bittime.h"
#include "../lib/mcp2515/mcp2515_defs.h"
#include "../lib/SPI/AVR_SPI.h"
#include "../lib/uart/uart.h"
#include "../lib/uart/uart_CANFunc.h"

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

float MPU6050_CalcAngle(int axis)//x = 0; y = 1; z = 2
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

int main(void)
{
	unsigned char ret;
	
	DDRC |= (1 << PORTC2); //output
	DDRC |= (1 << PORTC3); //output
	
	SPI_Init(); // setup SPI
	CAN_Init(CAN_125KBPS_16MHZ);
	
	//i2c_init(); 
	
	//TWIM_Init(12);
	//TWIM_WriteRegister(107,0); //disable sleep mode

	sei();
	
	
	ret = TWIM_Start(addr, TWIM_WRITE);

	
		while(1)
    {
        //TODO:: Please write your application code 
		
		
		
		//*****************************************
		//Send angle
		//*****************************************
		float angletheta;
		float anglepsi;
		float anglephi;
		
		angletheta = ((atan(MPU6050_CalcAngle(0)/(sqrt((pow(MPU6050_CalcAngle(1),2)) + (pow(MPU6050_CalcAngle(2),2))))))*180/M_PI)*1000;
		anglepsi = ((atan(MPU6050_CalcAngle(1)/(sqrt((pow(MPU6050_CalcAngle(0),2)) + (pow(MPU6050_CalcAngle(2),2))))))*180/M_PI)*1000;
		anglephi = ((atan((sqrt((pow(MPU6050_CalcAngle(0),2)) + (pow(MPU6050_CalcAngle(1),2))))/MPU6050_CalcAngle(2)))*180/M_PI)*1000;
		
		int32_t anglethetaTEMP = angletheta;
		int32_t anglepsiTEMP = anglepsi;
		int16_t anglephiTEMP = anglephi;
		
		//*****************************************
		//Send gyroscope
		//*****************************************
		int16_t tempGX = MPU6050_ReadGyro(0);
		int16_t tempGY = MPU6050_ReadGyro(1);
		int16_t tempGZ = MPU6050_ReadGyro(2);
			
		CANMessage Gyro;
			
		Gyro. id = 0x07A2;
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
		
		CANMessage anglexy;
		
		anglexy. id = 0x07A0;
		anglexy. rtr = 0 ;
		anglexy. length = 8 ;
		anglexy. data [ 0 ] = anglethetaTEMP>>24;
		anglexy. data [ 1 ] = anglethetaTEMP>>16;
		anglexy. data [ 2 ] = anglethetaTEMP>>8;
		anglexy. data [ 3 ] = anglethetaTEMP;
		anglexy. data [ 4 ] = anglepsiTEMP>>32;
		anglexy. data [ 5 ] = anglepsiTEMP>>16;
		anglexy. data [ 6 ] = anglepsiTEMP>>8;
		anglexy. data [ 7 ] = anglepsiTEMP;
		
		CAN_sendMessage (&anglexy);
		
		CANMessage anglez;
		
		anglez. id = 0x07A1;
		anglez. rtr = 0 ;
		anglez. length = 4 ;
		anglez. data [ 0 ] = anglephiTEMP>>24;
		anglez. data [ 1 ] = anglephiTEMP>>16;
		anglez. data [ 2 ] = anglephiTEMP>>8;
		anglez. data [ 3 ] = anglephiTEMP;
		
		CAN_sendMessage (&anglez);
		
		CANMessage test1;
	
		test1. id = 0x0004;
		test1. rtr = 0 ;
		test1. length = 2 ;
		test1. data [ 0 ] = 0x02;//MPU6050_ReadGyro(0)>>8;
		test1. data [ 1 ] = 0x04;//MPU6050_ReadGyro(0);
		//PORTC &= ~ (1<< PORTC3);
		CAN_sendMessage (&test1);
		//PORTC |= (1<< PORTC3);
		_delay_ms(200);
		
		int16_t tempx = MPU6050_ReadGyro(0);
	
		CANMessage test;
	
		test. id = 0x0002;
		test. rtr = 0 ;
		test. length = 2 ;
		test. data [ 0 ] = tempx>>8;
		test. data [ 1 ] = tempx;
		//PORTC &= ~ (1<< PORTC3);
		CAN_sendMessage (&test);
		//PORTC |= (1<< PORTC3);
		
		_delay_ms(500);
	
		int16_t temp;
		temp = (int16_t) MPU6050_ReadGyro(0);
	

    }
	}
		
    
}
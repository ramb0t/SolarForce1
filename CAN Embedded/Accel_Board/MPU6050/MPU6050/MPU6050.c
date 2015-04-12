/*
 * MPU6050.c
 *
 * Created: 31/03/2015 10:36:22 PM
 *  Author: Terayza
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include <avr/interrupt.h>
//#include "../../lib/CAN/CAN.h"
#include "../../CAN Embedded/lib/CAN/CAN.h"
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

// Project Specific
//#include "../../lib/mcp2515/mcp2515.h"
#include "../../CAN Embedded/lib/mcp2515/mcp2515.h"
//#include "../../lib/SPI/AVR_SPI.h"
#include "../../CAN Embedded/lib/SPI/AVR_SPI.h"
//#include "../../lib/uart/uart.h"
#include "../../CAN Embedded/lib/uart/uart.h"
#include <string.h>

// These are optional, but nice to have around.
// Feel free to comment them out if you don't use them.
#include <stdint.h>

#define addr 0x68

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

double MPU6050_ReadAccel(int axis)//x = 0; y = 1; z = 2
{
	char reg = axis * 2 + 59;
	char AFS_SEL = TWIM_ReadRegister(28);
	double factor = 1<<AFS_SEL;
	factor = 16384/factor;
	int val = 0;
	double double_val = 0;
	char ret = 0;

	ret = TWIM_ReadRegister(reg);
	val = ret << 8;

	ret = TWIM_ReadRegister(reg+1);
	val += ret;

	if (val & 1<<15)
	val -= 1<<16;
	
	double_val = val;

	double_val = double_val / factor;

	return double_val;
}

double MPU6050_ReadGyro(int axis)//x = 0; y = 1; z = 2
{
	char reg = axis * 2 + 67;
	char FS_SEL = TWIM_ReadRegister(27);
	double factor = 1<<FS_SEL;
	factor = 131/factor;
	int val = 0;
	double double_val = 0;
	char ret = 0;

	ret = TWIM_ReadRegister(reg);
	val = ret << 8;

	ret = TWIM_ReadRegister(reg+1);
	val += ret;

	if (val & 1<<15)
	val -= 1<<16;


	double_val = val;
	
	double_val = double_val / factor;

	return double_val;
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
	initComms(12);
	SPI_Init(); // setup SPI
	CAN_Init(CAN_125KBPS_16MHZ);
	
	UDR0 = 'A';
	
	TWIM_Init(12);
	TWIM_WriteRegister(107,0); //disable sleep mode
	
	UDR0 = 0x02;
	
    while(1)
    {
		CANMessage gyro;
		
		gyro. id = 0x0011;
		gyro. rtr = 0 ;
		gyro. length = 2 ;
		gyro. data [ 0 ] = MPU6050_ReadGyro(0);
		gyro. data [ 1 ] = MPU6050_ReadGyro(1);
		
		CAN_sendMessage (&gyro);
		
        UDR0 = MPU6050_ReadGyro(0);
		_delay_ms(100);
		
		CANMessage acc;
		
		gyro. id = 0x0012;
		gyro. rtr = 0 ;
		gyro. length = 2 ;
		gyro. data [ 0 ] = MPU6050_ReadAccel(0);
		gyro. data [ 1 ] = MPU6050_ReadAccel(1);
		
		CAN_sendMessage (&acc);
		
		UDR0 = MPU6050_ReadAccel(0);
		_delay_ms(100);
    }
}
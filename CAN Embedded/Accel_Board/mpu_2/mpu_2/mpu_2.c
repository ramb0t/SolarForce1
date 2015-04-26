/*
 * mpu_2.c
 *
 * Created: 26/04/2015 12:36:31 AM
 *  Author: Terayza
 */ 

#define F_CPU 16000000UL
#define UART_BAUD_RATE 57600
#define addr 0x68

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
#include "I2C.h"
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
	return val;
}


int main(void)
{
	DDRC |= (1 << PORTC2); //output
	DDRC |= (1 << PORTC3); //output
	
	SPI_Init(); // setup SPI
	CAN_Init(CAN_125KBPS_16MHZ);
	
	PORTC |= (1<< PORTC2);
	PORTC |= (1<< PORTC3);
	_delay_ms(500);
	PORTC &= ~ (1<< PORTC2);
	PORTC &= ~ (1<< PORTC3);
	
	
	TWIM_Init(12);
	TWIM_WriteRegister(107,0); //disable sleep mode
	
	sei();
	
    while(1)
    {
        //TODO:: Please write your application code 
	_delay_ms(500);
	PORTC ^=  (1<< PORTC2);	
	
	//int16_t temp;
	//temp = (int16_t) MPU6050_ReadGyro(0);
	
	CANMessage test;
	
	test. id = 0x0002;
	test. rtr = 0 ;
	test. length = 2 ;
	test. data [ 0 ] = MPU6050_ReadGyro(0)>>8;
	test. data [ 1 ] = MPU6050_ReadGyro(0);
	CAN_sendMessage (&test);
    }
}
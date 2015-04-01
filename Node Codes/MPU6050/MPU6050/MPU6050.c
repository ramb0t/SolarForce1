/*
 * MPU6050.c
 *
 * Created: 31/03/2015 10:36:22 PM
 *  Author: Terayza
 */ 


#include <avr/io.h>
#include "I2C.h"
#include <avr/delay.h>;


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
	
	UDR0 = 'A';
	
	TWIM_Init(12);
	TWIM_WriteRegister(107,0); //disable sleep mode
	
	UDR0 = 0x04;
	
    while(1)
    {
        UDR0 = MPU6050_ReadGyro(0);
		_delay_ms(100);
    }
}
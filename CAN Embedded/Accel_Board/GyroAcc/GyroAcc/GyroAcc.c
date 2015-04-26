/*
 * GyroAcc.c
 *
 * Created: 11/04/2015 10:50:49 PM
 *  Author: Terayza
 */ 

#define F_CPU 16000000UL
#define UART_BAUD_RATE 57600

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

#include "I2C.h"
#include "../lib/CAN/CAN.h"
#include "../lib/CAN/CAN_defs.h"
#include "../lib/mcp2515/mcp2515.h"
#include "../lib/mcp2515/mcp2515_bittime.h"
#include "../lib/mcp2515/mcp2515_defs.h"
#include "../lib/uart/uart.h"
#include "../lib/uart/uart_CANFunc.h"
#include "../lib/SPI/AVR_SPI.h"

#include <stdlib.h>

// Project Specific
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

int main(void)
{

	
	
	
	// Init UART
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	
	
	
	TWIM_Init(12);
	//AS SOON AS DISABLE SLEEP MODE, CAN WONT SEND
	
	TWIM_WriteRegister(107,0); //disable sleep mode
	


	SPI_Init(); // setup SPI
	CAN_Init(CAN_125KBPS_16MHZ);
	sei();
	
	while(1)
	{
		double tempD;
		char buffer[10];
		char buffer2[30]; 
		
		//*********************************************
		//GYROSCOPE OUTPUTS
		//*********************************************
		
		//Gyro X
		memset(buffer2, 0, sizeof buffer2);
		strcat(buffer2, "Gyro x: ");
		
		tempD = MPU6050_ReadGyro(0);
		dtostrf(tempD,1,4,buffer);
		strcat(buffer2,buffer);
		strcat(buffer2,"\n");
		
		uart_puts(buffer2);
		_delay_ms(500);
		
		//Gyro Y
		memset(buffer2, 0, sizeof buffer2);
		strcat(buffer2, "Gyro y: ");
		
		tempD = MPU6050_ReadGyro(2);
		dtostrf(tempD,1,4,buffer);
		strcat(buffer2,buffer);
		strcat(buffer2,"\n");
		
		uart_puts(buffer2);
		_delay_ms(500);
		
		//Gyro Z
		memset(buffer2, 0, sizeof buffer2);
		strcat(buffer2, "Gyro z: ");
		
		tempD = MPU6050_ReadGyro(3);
		dtostrf(tempD,1,4,buffer);
		strcat(buffer2,buffer);
		strcat(buffer2,"\n");
		
		uart_puts(buffer2);
		_delay_ms(500);
		
		//*********************************************
		//ACCELEROMETER OUTPUTS
		//*********************************************
		
		//Acc X
		memset(buffer2, 0, sizeof buffer2);
		strcat(buffer2, "Acc x: ");
		
		tempD = MPU6050_ReadAccel(0);
		dtostrf(tempD,1,4,buffer);
		strcat(buffer2,buffer);
		strcat(buffer2,"\n");
		
		uart_puts(buffer2);
		_delay_ms(500);
		
		//Acc Y
		memset(buffer2, 0, sizeof buffer2);
		strcat(buffer2, "Acc y: ");
		
		tempD = MPU6050_ReadAccel(1);
		dtostrf(tempD,1,4,buffer);
		strcat(buffer2,buffer);
		strcat(buffer2,"\n");
		
		uart_puts(buffer2);
		_delay_ms(500);
		
		//Acc Z
		memset(buffer2, 0, sizeof buffer2);
		strcat(buffer2, "Acc z: ");
		
		tempD = MPU6050_ReadAccel(3);
		dtostrf(tempD,1,4,buffer);
		strcat(buffer2,buffer);
		strcat(buffer2,"\n");
		
		uart_puts(buffer2);
		_delay_ms(500);
		
		//trying to work out angle		
		double angletheta;
		
		//angletry = atan((MPU6050_ReadAccel(0))/(sqrt(pow((MPU6050_ReadAccel(1)),2)+pow((MPU6050_ReadAccel(2)),2))));
		//angletheta = ((atan((MPU6050_ReadAccel(0))/(MPU6050_ReadAccel(1))))*180/M_PI);
		angletheta = (atan(MPU6050_ReadAccel(0)/(sqrt((pow(MPU6050_ReadAccel(1),2)) + (pow(MPU6050_ReadAccel(2),2))))))*180/M_PI;

		memset(buffer2, 0, sizeof buffer2);
		strcat(buffer2, "Angle theta: ");
		
		tempD = angletheta;
		dtostrf(tempD,1,4,buffer);
		strcat(buffer2,buffer);
		strcat(buffer2,"\n");
		
		uart_puts(buffer2);
		_delay_ms(500);
		
		double anglepsi;
		
		//angletry = atan((MPU6050_ReadAccel(0))/(sqrt(pow((MPU6050_ReadAccel(1)),2)+pow((MPU6050_ReadAccel(2)),2))));
		//anglephi = ((atan((MPU6050_ReadAccel(3))/(sqrt((pow(MPU6050_ReadAccel(0),2)) + (pow(MPU6050_ReadAccel(1),2)) + (pow(MPU6050_ReadAccel(2),2))))))*180/M_PI);
		anglepsi = (atan(MPU6050_ReadAccel(1)/(sqrt((pow(MPU6050_ReadAccel(0),2)) + (pow(MPU6050_ReadAccel(2),2))))))*180/M_PI;

		memset(buffer2, 0, sizeof buffer2);
		strcat(buffer2, "Angle psi: ");
		
		tempD = anglepsi;
		dtostrf(tempD,1,4,buffer);
		strcat(buffer2,buffer);
		strcat(buffer2,"\n");
		
		uart_puts(buffer2);
		_delay_ms(500);
		
		double anglephi;
		
		//angletry = atan((MPU6050_ReadAccel(0))/(sqrt(pow((MPU6050_ReadAccel(1)),2)+pow((MPU6050_ReadAccel(2)),2))));
		//anglephi = ((atan((MPU6050_ReadAccel(3))/(sqrt((pow(MPU6050_ReadAccel(0),2)) + (pow(MPU6050_ReadAccel(1),2)) + (pow(MPU6050_ReadAccel(2),2))))))*180/M_PI);
		anglephi = (atan((sqrt((pow(MPU6050_ReadAccel(0),2)) + (pow(MPU6050_ReadAccel(1),2))))/MPU6050_ReadAccel(2)))*180/M_PI;
		
		memset(buffer2, 0, sizeof buffer2);
		strcat(buffer2, "Angle pi: ");
		
		tempD = anglephi;
		dtostrf(tempD,1,4,buffer);
		strcat(buffer2,buffer);
		strcat(buffer2,"\n");
		
		uart_puts(buffer2);
		_delay_ms(500);
		
		CANMessage test;
		
		test. id = 0x0002;
		test. rtr = 0 ;
		test. length = 1 ;
		test. data [ 0 ] = 0x03;
		
		CAN_sendMessage (&test);

	}
}
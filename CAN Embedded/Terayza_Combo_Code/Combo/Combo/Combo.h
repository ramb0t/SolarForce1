/*
 * Combo.h
 *
 * Created: 26/04/2015 09:43:00 PM
 *  Author: Terayza
 */ 


#ifndef COMBO_H_
#define COMBO_H_

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

//void send()
//void TWIM_WriteRegister(char, char);
//char TWIM_ReadRegister(char);
int16_t MPU6050_ReadAccel(int);
int16_t MPU6050_ReadGyro(int);
float MPU6050_CalcAngle(int);
void check();
//void motorCalcs();
//void initInterrupt0(void)


#endif /* COMBO_H_ */
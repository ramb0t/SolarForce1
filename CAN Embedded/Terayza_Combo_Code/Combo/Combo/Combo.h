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

//void send()
//void TWIM_WriteRegister(char, char);
//char TWIM_ReadRegister(char);
int16_t MPU6050_ReadAccel(int);
int16_t MPU6050_ReadGyro(int);
float MPU6050_CalcAngle(int);
//void check();
//void motorCalcs();
//void initInterrupt0(void)


#endif /* COMBO_H_ */
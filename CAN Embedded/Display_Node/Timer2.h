/*
 * Timer2.h
 *
 *  Created on: 05 Jul 2015
 *      Author: RobThePyro
 */

#ifndef TIMER2_H_
#define TIMER2_H_

// Includes:
/*****************************************************************************/
#include <avr/io.h> /* Defines pins, ports, etc */
#include <util/delay.h> /* Functions to waste time */
#include "pinDefines.h" /* Defines the pins used on the board */

// Defines:
/*****************************************************************************/

// Variables:
/*****************************************************************************/


// Function Prototypes:
/*****************************************************************************/
void Timer2_init(void);
void Timer2_PWM_Off(void);
void Timer2_PWM_On(void);
void Timer2_Set_PWM_Cruise(uint8_t PWM_Val);

#endif /* TIMER2_H_ */

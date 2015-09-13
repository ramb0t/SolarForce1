/*
 * pinDefines.h
 *
 *  Created on: 04 Apr 2015
 *      Author: RobThePyro
 */

#ifndef PINDEFINES_H_
#define PINDEFINES_H_

#define LCD_PWM_DDR		DDRB
#define LCD_PWM_PORT	PORTB
#define LCD_PWM_PIN		PINB
#define LCD_PWM 		PB1

#define LCD_SCKCTL_DDR	DDRD
#define LCD_SCKCTL_PORT	PORTD
#define LCD_SCKCTL_PIN	PIND
#define LCD_SCKCTL 		PD6

#define LED_DDR			DDRD
#define LED_PORT		PORTD
#define LED_RF			PD0
#define LED_B			PD1
#define LED_ON(led)		LED_PORT |= (1<<led)
#define LED_OFF(led)	LED_PORT &= ~(1<<led)
#define LED_FLIP(led)	LED_PORT ^= (1<<led)

#define BTN_DDR			DDRD
#define BTN_PORT		PORTD
#define BTN_PIN			PIND
#define BTN_1			PD2
#define BTN_2			PD3
#define BTN_3			PD4
#define BTN_4			PD5

#define CRUISE_PWM_DDR	DDRD
#define CRUISE_PWM 		PD3  //Use Timer2 -> OSC2B Pin for PWM for motor control?

#define CRUISE_ADC_DDR	DDRC
#define CRUISE_ADC_PORT	PORTC
#define CRUISE_ADC_PIN	PINC
#define CRUISE_ADC_THR 	PC0	 //Throttle on PC0 / ADC0 ?
#define CRUISE_ADC_THR_MUX	0





#endif /* PINDEFINES_H_ */

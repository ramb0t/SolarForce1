/*
 * main.c
 *
 *  Created on: 08 Apr 2015
 *      Author: RobThePyro
 */


#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR		DDRD
#define LED_PORT	PORTD
#define LED1		PD3
#define LED2		PD2

int main(void){
	// setup leds
	LED_DDR |= (1<<LED1)|(1<<LED2);

	while(1){
		// toggle
		LED_PORT |= (1<<LED1);
		LED_PORT &= ~(1<<LED2);
		_delay_ms(500);

		LED_PORT |= (1<<LED2);
		LED_PORT &= ~(1<<LED1);
		_delay_ms(500);
	}


}

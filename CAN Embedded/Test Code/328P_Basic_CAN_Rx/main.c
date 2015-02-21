/*
 * main.c
 *
 *  Created on: 21 Feb 2015
 *      Author: RobThePyro
 */

#include "main.h"

int main(void)
{
	DDRB |=(1<<PORTB1);
	SPI_Init();
	mcp2515_init();
	// Create a new message
	CANMessage message;
	uint8_t rx_status = 0x00;

	// Flashes on boot for test
	for(int a = 0; a<10; a++)
	{
		PORTB |= (1<<PORTB1);
		_delay_ms(50);
		PORTB &=~(1<<PORTB1);
		_delay_ms(50);
	}

while(1)
	{


	// quick flash while waiting for a message
	while( rx_status == 0xff )
		//_delay_ms(1000);

		PORTB |= (1<<PORTB1);
		_delay_ms(200);
		PORTB &=~(1<<PORTB1);

		rx_status = can_get_message (&message); //gets msg from bus (pointer to the object of CanMessage type) [returns value based on result of Rx

	}

	rx_status = 0xff; // reset

    // we have a message now!!
	// check if valid?
	if (message.data[0] == 0x04 && message.data[1]==0xf3)
		{
			// turn on for a time
			PORTB |= (1<<PORTB1);
			_delay_ms(1000);
		}

}


//// Enable the Rx buffer interrupts
//mcp2515_write_reg(CANINTE, (1 << RX1IE) | (1 << RX0IE));
//
//// Use RX0BF as digital output
//mcp2515_bit_modify (BFPCTRL, (1 << B0BFE) | (1 << B0BFM), (1 << B0BFE));
//
//// Set pin
//mcp2515_bit_modify (BFPCTRL, (1 << B0BFE), (1 << B0BFE));
//
//// Use RX0BF and RX1BF as interrupt outputs
//mcp2515_write_reg (BFPCTRL, (1 << B1BFE) | (1 << B0BFE) | (1 << B1BFM) | (1 << B0BFM));

// Prescaler of the CLKOUT pin set to zero,
// => Output clock frequency of the MCP2515 on the CLKOUT pin

//mcp2515_bit_modify (CANCTRL, 0x07, (1 << CLKEN));



/*
 * MAVLink_Messaging.c
 *
 * Created: 2015/03/29 11:47:11 PM
 *  Author: Matt
 */ 

#define F_CPU 20000000UL
#define UART_BAUD_RATE 9600  
#define MAVLINK_USE_CONVENIENCE_FUNCTIONS   

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "mavlink.h"

mavlink_system_t mavlink_system;


enum {
	BLINK_DELAY_MS = 1000,
};

int main (void)
{
	/* port configuration
	GPS Serial In Dig I/P 2 = PORTD2
	Telemetry Serial O/P 3 = PORTD3
	Telemetry Serial I/P 4 = PORTD4
	*/
	DDRD |= _BV(DDD3);	//output
	DDRD &=~_BV(DDD2);	//input
	DDRD &=~_BV(DDD4);	//input
	
	DDRB |= _BV(DDB5);
	
	//---------Serial Init --------------------//
	    unsigned int c;
	    char buffer[7];
	    int  num=134;
		uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
		
		 sei();	//interrupts ON
	
	//------------MAVLink Setup-----------------//

	/*MAVLINK asks to set all systm statuses as integers. For human readibility ENUMS are used in the appropriate headers
  these enums convert text for states to integers sent & interpreted. 3 phases to a message:
  --define the enum types you'll need and use friendly names e.g. value_name = MAV_ENUM_VALUE_NAME
  --use a send / encode function from the relevant header to send HEARTBEAT to get QGC/APM working
  --then have a function (see solarCar.h and the entire message_definitions folder for types to send
  --pass the values or enum friendly names to the functions
  --this ensures the message goes to MAVLink frame
  --connect to QGC and observe output! */
    
	// Define the system type (see solarCar.h for list of possible types) 
	int system_type = MAV_TYPE_GROUND_ROVER;
	int autopilot_type = MAV_AUTOPILOT_GENERIC;
    int base_mode = MAV_MODE_FLAG_AUTO_ENABLED;
	int custom_mode = MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
    int system_status = MAV_STATE_ACTIVE;

	// Initialize the required buffers
	mavlink_message_t msg; 
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
 
	
	while(1) {
		/* set pin 5 high to turn led on */
		PORTB |= _BV(PORTB5);
		_delay_ms(BLINK_DELAY_MS);
		uart_puts("LED Turned ON\n");
		
		// Pack the message
		// mavlink_message_heartbeat_pack(system id, component id, message container, system type, MAV_AUTOPILOT_GENERIC)
		mavlink_msg_heartbeat_pack(100, 200, &msg, system_type, autopilot_type,base_mode,custom_mode,system_status);
		uart_puts_p(buf);
		uart_puts_p(len);
		_delay_ms(1000);
		
		/* set pin 5 low to turn led off */
		PORTB &= ~_BV(PORTB5);
		_delay_ms(BLINK_DELAY_MS);
		uart_puts("LED Turned OFF\n");
	}
	
	return 0;
}
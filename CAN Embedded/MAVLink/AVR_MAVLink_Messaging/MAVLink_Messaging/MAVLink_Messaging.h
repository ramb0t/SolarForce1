/*
 * MAVLink_Messaging.h
 *
 * Created: 2015/03/31 10:51:38 PM
 *  Author: Matt
 */ 


#ifndef MAVLINK_MESSAGING_H_
#define MAVLINK_MESSAGING_H_

//------------Port Naming/ System Defines-----------------//

#define F_CPU 16000000UL
#define UART_BAUD_RATE 9600
#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

#define TELEMETRY_UART_OUT	DDD3
#define GPS_UART_DATA_IN	DDD2
#define TELEMETRY_UART_IN	DDD4

#define UART_DDR			DDRD

//------------Library and AVR Includes--------------------//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "uart.h"					//UART library
#include "mavlink.h"				//MAVLink framework

#include "../lib/CAN/CAN.h"			//CAN Framework
#include "../lib/mcp2515/mcp2515.h"	//bit timings for MCP2515

//------------Library Objects----------------------------//

CANMessage CANBusInput;				//CAN library object
mavlink_system_t mavlink_system;	//MAVLink system object

volatile int counter=0;
volatile int ctr2=0;

//------------Enum for MAVLink Heartbeat delay-----------//
enum {
	HEARTBEAT_DELAY = 1000
};

#endif /* MAVLINK_MESSAGING_H_ */
/*
 * MAVLink_Messaging.h
 *
 * Created: 2015/03/31 10:51:38 PM
 *  Author: Matt
 */ 


#ifndef MAVLINK_MESSAGING_RX_H_
#define MAVLINK_MESSAGING_RX_H_

//#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

//------------Port Naming/ System Defines-----------------//

#define F_CPU 16000000UL
#define UART_BAUD_RATE 9600


#define TELEMETRY_UART_OUT	DDD1
#define GPS_UART_DATA_IN	DDD0
#define TELEMETRY_UART_IN	DDD0

#define UART_DDR			DDRD

#define UART_REG			UCSR0A
#define TX_ENABLE			(1<<TXEN0)
#define TX_DISABLE			(0<<TXEN0)

//------------Library and AVR Includes--------------------//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "./lib/uart/uart.h"					//UART library

#include "mavlink_bridge_header.h"  //UART & convenience headers

#include "GlobalDefs.h"

mavlink_status_t* mavlink_get_channel_status(uint8_t chan);
mavlink_message_t* mavlink_get_channel_buffer(uint8_t chan);

//---------------CAN ID defines-----//

#define MOTOR_DRIVER_CANID	0x420
#define HALL_EFFECT_CANID	0x420

#define HESPD_TXID			420

#define BMS_TXID			1
#define AC_TXID				2
#define MPPT1_TXID			3
#define MPPT2_TXID			4
#define MPPT3_TXID			5
#define MPPT4_TXID			6
#define GPS_TXID			7

//------------Library Objects----------------------------//

volatile uint8_t counter=0;				//counts data on UART bus for connection check
volatile uint8_t ctr2=0;				//counts bytes passing thru MAVLink frame for length check
volatile uint16_t hb_lost = 0;			//counts cycles since last heartbeat
volatile GlobalVars	rxData;

char MAV_Rx_buff[16];

//------------Function Prototypes------------------------//

		int system_type = MAV_TYPE_GROUND_ROVER;
		int autopilot_type = MAV_AUTOPILOT_GENERIC;
		int base_mode = MAV_MODE_FLAG_AUTO_ENABLED;
		int custom_mode = MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
		int system_status = MAV_STATE_ACTIVE;

void CAN_readData(void);
void MAV_msg_Unpack();
void MAV_uart_send(uint8_t [],uint8_t);
void GPS_readData(void);


#endif /* MAVLINK_MESSAGING_H_ */
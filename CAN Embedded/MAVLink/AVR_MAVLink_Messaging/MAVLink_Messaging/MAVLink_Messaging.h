/*
 * MAVLink_Messaging.h
 *
 * Created: 2015/03/31 10:51:38 PM
 *  Author: Matt
 */ 


#ifndef MAVLINK_MESSAGING_H_
#define MAVLINK_MESSAGING_H_

//#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

//------------Port Naming/ System Defines-----------------//

#define F_CPU 16000000UL
#define UART_BAUD_RATE 9600

#define TELEMETRY_UART_OUT	DDD1
#define GPS_UART_DATA_IN	DDD0
#define TELEMETRY_UART_IN	DDD0

#define CANINT_DDR			DDRB
#define CANINT_PORT			PORTB
#define CANINT_LED			PORTB1

#define LED_DIAG_ORG		PORTC2

#define LED_DIAG_DDR		DDRD
#define LED_DIAG_PORT		PORTD
#define LED_DIAG_GRN		PORTD3	

#define UART_DDR			DDRD

#define UART_REG			UCSR0A
#define TX_ENABLE			(1<<TXEN0)
#define TX_DISABLE			(0<<TXEN0)

//------------GLobal -----------------//


//-------------CAN Defines----------------------------------//

#define MOTOR_DRIVER_CANID	0x0420
#define HALL_EFFECT_CANID	0x0420
// #420 BLAZING TIME :P!!


#define BMS_1_CANID			0x0621
#define BMS_2_CANID			0x0622
#define BMS_3_CANID			0x0623
#define BMS_4_CANID			0x0624
#define BMS_5_CANID			0x0625
#define BMS_6_CANID			0x0626
#define BMS_7_CANID			0x0627
#define BMS_8_CANID			0x0628

#define ACCELO_CANID		0x0011
#define GYRO_CANID			0x0012
#define MPPT1_CANID			0x0771
#define MPPT2_CANID			0x0772
#define MPPT3_CANID			0x0773
#define MPPT4_CANID			0x0774

//------------Library and AVR Includes--------------------//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <stdbool.h>
#include "../lib/uart/uart.h"					//UART library

#include "../lib/CAN/CAN.h"			//CAN Framework
#include "../lib/mcp2515/mcp2515.h"	//bit timings for MCP2515



//---------------Interrupt-based fuctions----------------//
#include "CAN_Int0.h"
#include "Mavlink_Timer0.h"
#include "GPS_Rx_ISR.h"
//#include "selecticeMAVSend.h"

//------------MAVlink convenience functions--------------//

#include "mavlink_bridge_header.h"  //UART & convenience headers
mavlink_status_t* mavlink_get_channel_status(uint8_t chan);
mavlink_message_t* mavlink_get_channel_buffer(uint8_t chan);


//------------Variables----------------------------//

volatile int counter=0;
volatile int ctr2=0;
volatile int canmsgctr = 0;
//volatile uint16_t 	flag =0;

char MAV_Rx_buff[10];

//GPS vars to store data for MAV framing later
char gpsdata;
char gps_string[62];
char parts[15][20];
char *p_start, *p_end;
uint8_t ctr=0;
uint8_t gpslen;

//------------Library Objects----------------------------//
//CAN library objects per device

volatile CANMessage Speed_Message;			//Aggregated Speed Board msg
volatile CANMessage BMS_Message;				//BMS data message
volatile CANMessage MPPT1_Message;			//MPPT messages
volatile CANMessage MPPT2_Message;			//MPPT messages
volatile CANMessage MPPT3_Message;			//MPPT messages
volatile CANMessage MPPT4_Message;			//MPPT messages
volatile CANMessage Gyro_Message;			//gyro messages
volatile CANMessage Accelo_message;			//Accelerometer messages


//------------MAVLink Function Prototypes------------------------//

		uint8_t system_type = MAV_TYPE_GROUND_ROVER;
		uint8_t autopilot_type = MAV_AUTOPILOT_UDB;
		uint8_t base_mode = MAV_MODE_FLAG_AUTO_ENABLED;
		uint8_t custom_mode = MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
		uint8_t system_status = MAV_STATE_ACTIVE;
		
//------------Function Prototypes------------------------//

void CAN_readData(void);
void MAV_msg_pack();
void MAV_uart_send(uint8_t [],uint8_t);

void GPS_readData(void);
void GPSParse();

void MAV_HB_send();


volatile uint8_t	updateMAV_flag;		//flag to know whether MAVLink packet to be sent
volatile uint16_t 	gMilliSecTick;
volatile uint16_t	ms_Counter;
volatile uint16_t	old_mS;



 

#endif /* MAVLINK_MESSAGING_H_ */
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

#define LED_DIAG_DDR		DDRD
#define LED_DIAG_PORT		PORTD
#define LED_DIAG_ORG		PORTD2
#define LED_DIAG_GRN		PORTD3	

#define UART_DDR			DDRD

#define UART_REG			UCSR0A
#define TX_ENABLE			(1<<TXEN0)
#define TX_DISABLE			(0<<TXEN0)

//------------Library and AVR Includes--------------------//

//-------------CAN Defines----------------------------------//

#define MOTOR_DRIVER_CANID	0x0420
#define HALL_EFFECT_CANID	0x0420

#define BMS_1_CANID			0x0621
#define BMS_2_CANID			0x0622
#define BMS_3_CANID			0x0623
#define BMS_4_CANID			0x0624
#define BMS_5_CANID			0x0625
#define BMS_6_CANID			0x0626
#define BMS_7_CANID			0x0627
#define BMS_8_CANID			0x0628

#define ACCELO_GYRO_CANID   0x00C8
#define MPPT1_CANID			0x0771
#define MPPT2_CANID			0x0772
#define MPPT3_CANID			0x0773
#define MPPT4_CANID			0x0774

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <stdbool.h>
#include "../lib/uart/uart.h"					//UART library

#include "../lib/CAN/CAN.h"			//CAN Framework
#include "../lib/mcp2515/mcp2515.h"	//bit timings for MCP2515

#include "mavlink_bridge_header.h"  //UART & convenience headers

mavlink_status_t* mavlink_get_channel_status(uint8_t chan);
mavlink_message_t* mavlink_get_channel_buffer(uint8_t chan);


//------------Library Objects----------------------------//

//CAN library objects per device


CANMessage Speed_Message;			//Aggregated Speed Board msg
CANMessage BMS_Message;				//BMS data message
CANMessage MPPT1_Message;			//MPPT messages
CANMessage MPPT2_Message;			//MPPT messages
CANMessage MPPT3_Message;			//MPPT messages
CANMessage MPPT4_Message;			//MPPT messages
CANMessage Gyro_Accel_Message;		//gyro messages
CANMessage GPS_message;



volatile int counter=0;
volatile int ctr2=0;
volatile int canmsgctr = 0;
extern	volatile uint8_t 	flag;

char MAV_Rx_buff[10];

//GPS vars to store data for MAV framing later
		

		//// GPS variables
		//volatile unsigned int Time, Msecs, Knots, Course, Date;
		//volatile long Lat, Long;
		//volatile bool Fix;
		//volatile char gpschar;
		//
		//char fmt[]="$GPRMC,dddtdd.ddm,A,eeae.eeee,l,eeeae.eeee,o,djdk,ddd.dc,dddy??,,,?*??";
//
		//int state = 0;
		//unsigned int temp;
		//long ltmp;
		
#include <stdint.h>


#define true 	1
#define false 	0

#define CR		0x0d
#define LF		0x0a

#define PI 3.14159265358979323846

//states for the GPS parser
#define GPS_TOP				0
#define GPS_GOT_START		1
#define GPS_GET_CHECKSUM	2

//pixels per distance unit
#define SCALE 1.0

struct gps{
	char time[13];
	char lat[17];
	char lon[18];
	char latdec[16];
	char londec[17];
	char sats[8];
	char fix[8];
	char altm[13];
	char altf[13];
	char mcog[15];
	char tcog[15];
	char sogkph[20];
	char sogknot[20];
	char sogmph[20];
	char mode[8];
};

struct gpsdisp
{
	char showtime;
	char showpos;
	char showalt;
	char showspeed;
	char showcourse;
	char showsats;
	char showfix;
	char showmode;
	char showtrack;
	char timex;
	char timey;
	char latx;
	char laty;
	char lonx;
	char lony;
	char altx;
	char alty;
	char speedx;
	char speedy;
	char coursex;
	char coursey;
	char satsx;
	char satsy;
	char fixx;
	char fixy;
	char modex;
	char modey;
	char posformat;
	char speedunits;
	char altunits;
	char coursetype;
	char refresh;
};

void gps_init(void);
void gps_parse(char inchar);
void gps_process_sentence(void);
void GPGGA(void);
void GPRMC(void);
void GPVTG(void);
void gps_show_data(void);

double deg2rad(double deg);
double rad2deg(double rad);
double find_distance(double lat1, double lon1, double lat2, double lon2);
double find_bearing(double lat1, double lon1, double lat2, double lon2);
void find_relxy(double distance,double bearing,double scale);


//------------Function Prototypes------------------------//

		uint8_t system_type = MAV_TYPE_GROUND_ROVER;
		uint8_t autopilot_type = MAV_AUTOPILOT_UDB;
		uint8_t base_mode = MAV_MODE_FLAG_AUTO_ENABLED;
		uint8_t custom_mode = MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
		uint8_t system_status = MAV_STATE_ACTIVE;

void CAN_readData(void);
void MAV_msg_pack();
void MAV_uart_send(uint8_t [],uint8_t);
void GPS_readData(void);
void GPSParse(char c);

static inline void mavlink_msg_motor_driver_decode(const mavlink_message_t* msg, mavlink_motor_driver_t* motor_driver);


 

#endif /* MAVLINK_MESSAGING_H_ */
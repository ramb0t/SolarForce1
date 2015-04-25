/*
 * CAN_Int0.h
 *
 * Created: 2015/04/24 08:56:02 PM
 *  Author: Matt
 */ 


#ifndef CAN_INT0_H_
#define CAN_INT0_H_

//---------------Includes & defines-------//
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>  // Random, ITOA etc http://www.nongnu.org/avr-libc/user-manual/group__avr__stdlib.html
#include <stdint.h> // C99 Integer typedefs http://www.nongnu.org/avr-libc/user-manual/group__avr__stdint.html

// CAN Application Layer
#include "../lib/CAN/CAN.h"
// MCP2515 Library
#include "../lib/mcp2515/mcp2515.h"
// SPI Library used with CAN Controller
#include "../lib/SPI/AVR_SPI.h"
// Timer0
#include "Mavlink_Timer0.h"

//define returned CAN data
#define CAN_MSG_DECODED 1
#define CAN_NOT_DECODED 0

//---------------CAN IDs-----------------//


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

#define ACCELO_CANID		0x0011
#define GYRO_CANID			0x0012

#define MPPT1_CANID			0x0771
#define MPPT2_CANID			0x0772
#define MPPT3_CANID			0x0773
#define MPPT4_CANID			0x0774

//---------------Variables---------------//
CANMessage Input_data;
extern volatile uint8_t		message_decoded;
extern volatile	uint8_t		flag;
char						buff[10];

extern volatile CANMessage Speed_Message;			//Aggregated Speed Board msg
extern volatile CANMessage BMS_Message;				//BMS data message
extern volatile CANMessage MPPT1_Message;			//MPPT messages
extern volatile CANMessage MPPT2_Message;			//MPPT messages
extern volatile CANMessage MPPT3_Message;			//MPPT messages
extern volatile CANMessage MPPT4_Message;			//MPPT messages
extern volatile CANMessage Gyro_Message;			//gyro messages
extern volatile CANMessage Accelo_message;			//Accelerometer messages

//flags for if any variables have updated
volatile	uint8_t		speedUpdated;
volatile	uint8_t		acceloUpdated;
volatile	uint8_t		gyroUpdated;

volatile	uint8_t		bms1Updated;	
volatile	uint8_t		bms2Updated;
volatile	uint8_t		bms3Updated;
volatile	uint8_t		bms4Updated;
volatile	uint8_t		bms5Updated;
volatile	uint8_t		bms6Updated;
volatile	uint8_t		bms7Updated;
volatile	uint8_t		bms8Updated;

volatile	uint8_t		mppt1Updated;
volatile	uint8_t		mppt2Updated;
volatile	uint8_t		mppt3Updated;
volatile	uint8_t		mppt4Updated;



//---------------Prototypes---------------//
uint8_t CAN_Decode(CANMessage *message);


#endif /* CAN_INT0_H_ */
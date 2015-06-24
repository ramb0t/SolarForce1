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

#include "../lib/CAN/CAN_defs.h"
// Timer0 stuffs
#include "Mavlink_Timer0.h"
//Global struct with definitions for CAN component variables
#include "GlobalDefs.h"
//main H file for MAVLink data sending
#include "MAVLink_Messaging.h"

//define returned CAN data
#define CAN_MSG_DECODED 1
#define CAN_NOT_DECODED 0

//---------------CAN IDs-----------------//
//MOVED TO SEPARATE CAN DEFINITIONS FILE

//#define SPEED_HE_CANID		0x0420

//#define CANID_BMSDEFAULT	0x0620
//#define BMS_0_CANID			CANID_BMSDEFAULT + 0
//#define BMS_1_CANID			CANID_BMSDEFAULT + 1
//#define BMS_2_CANID			CANID_BMSDEFAULT + 2
//#define BMS_3_CANID			CANID_BMSDEFAULT + 3
//#define BMS_4_CANID			CANID_BMSDEFAULT + 4
//#define BMS_5_CANID			CANID_BMSDEFAULT + 5
//#define BMS_6_CANID			CANID_BMSDEFAULT + 6
//#define BMS_7_CANID			CANID_BMSDEFAULT + 7
//#define BMS_8_CANID			CANID_BMSDEFAULT + 8
//
//#define ACGY1				0x0820
//#define ACGY2				0x0821
//#define	ACGY3				0x0822
//
//#define MPPT1_CANID			0x0771
//#define MPPT2_CANID			0x0772
//#define MPPT3_CANID			0x0773
//#define MPPT4_CANID			0x0774

//---------------Variables---------------//
volatile CANMessage Input_data;					//struct to hold CAN input data
extern volatile uint8_t		message_decoded;	//status flags
extern volatile	uint8_t		flag;
volatile char				buff[10];			//input buffer
volatile GlobalVars	CANData;					//struct holding all CAN component vars

//flags for if any variables have updated
volatile	uint8_t		speedHEUpdated;
volatile	uint8_t		speedMDUpdated;
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
uint8_t CAN_Decode(CANMessage *message);				//decode prototype


#endif /* CAN_INT0_H_ */
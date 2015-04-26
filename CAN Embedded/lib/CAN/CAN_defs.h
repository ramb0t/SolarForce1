/*
 * CAN_defs.h
 *
 *  Created on: 17 Apr 2015
 *      Author: rambo
 */

#ifndef CAN_CAN_DEFS_H_
#define CAN_CAN_DEFS_H_


//Definitions of the Message IDs on the Network

#define CANID_SPEED			0x0420
// #420 BLAZING TIME :P!!

#define CANID_BMSDEFAULT	0x0620
#define CANID_BMS0			CANID_BMSDEFAULT + 0
#define CANID_BMS1			CANID_BMSDEFAULT + 1
#define CANID_BMS2			CANID_BMSDEFAULT + 2
#define CANID_BMS3			CANID_BMSDEFAULT + 3
#define CANID_BMS4			CANID_BMSDEFAULT + 4
#define CANID_BMS5			CANID_BMSDEFAULT + 5
#define CANID_BMS6			CANID_BMSDEFAULT + 6
#define CANID_BMS7			CANID_BMSDEFAULT + 7
#define CANID_BMS8			CANID_BMSDEFAULT + 8

#define CANID_MPPTRQ1		0x0711
#define CANID_MPPTRQ2		0x0712
#define CANID_MPPTRQ3		0x0713
#define CANID_MPPTRQ4		0x0713

#define CANID_MPPT1			0x0771
#define CANID_MPPT2			0x0772
#define CANID_MPPT3			0x0773
#define CANID_MPPT4			0x0774

#define CANID_GYRO_ANGLESI	0x07A0
#define CANID_GYRO_ANGLEPHI	0x07A1
#define CANID_GYRO_GYRO		0x07A2
#define CANID_GYRO_ACCEL	0x07A3



// Masking definitions
// State Byte Masks
#define 	BMSSTATE_FAULT 	0x01
#define 	BMSSTATE_RFAULT	0x10

// Flag byte Masks
#define 	BMSFLAG_FAN		0x80
#define 	BMSFLAG_LLIM	0x40
#define 	BMSFLAG_HLIM	0x20
#define 	BMSFLAG_CANC	0x10
#define 	BMSFLAG_HWC		0x08
#define 	BMSFLAG_INTT	0x04
#define 	BMSFLAG_PL		0x02
#define 	BMSFLAG_PS		0x01

#endif /* CAN_CAN_DEFS_H_ */

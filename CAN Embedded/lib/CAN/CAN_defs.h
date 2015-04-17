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

#define CANID_MPPT1			0x0771
#define CANID_MPPT2			0x0772
#define CANID_MPPT3			0x0773
#define CANID_MPPT4			0x0774

#endif /* CAN_CAN_DEFS_H_ */

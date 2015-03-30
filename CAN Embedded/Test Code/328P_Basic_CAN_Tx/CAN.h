/*
 * CAN.h
 *
 *  Created on: 30 Mar 2015
 *      Author: RobThePyro
 */

#ifndef CAN_H_
#define CAN_H_

// Includes
/*****************************************************************************/
#include <inttypes.h>



// Defines
/*****************************************************************************/
#define CAN_OK         (0)
#define CAN_FAILINIT   (1)
#define CAN_FAILTX     (2)

#define CAN_MAX_CHAR_IN_MESSAGE (8)

// Structures
/*****************************************************************************/
typedef struct {
	// identifier CAN_xxxID
	uint8_t  extended_id;
	// either extended (the 29 LSB) or standard (the 11 LSB)
	uint32_t id;
	// data length:
	uint8_t  length;
	uint8_t  data[CAN_MAX_CHAR_IN_MESSAGE];

	// used for receive only:
	// Received Remote Transfer Bit
	//  (0=no... 1=remote transfer request received)
	uint8_t  rtr;
	// Acceptance Filter that enabled the reception
	uint8_t  filhit;
} CANMessage;

// Functions
/*****************************************************************************/
uint8_t CAN_Init(uint8_t speedset);
uint8_t CAN_sendMessage(const CANMessage* msg);

#endif /* CAN_H_ */

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
#include <avr/io.h>
#include <avr/interrupt.h>

// CAN Bus ID Definitions
#include "CAN_defs.h"


// Defines
/*****************************************************************************/

// For function returns
#define CAN_OK         (0)
#define CAN_FAILINIT   (1)
#define CAN_FAILTX     (2)
#define CAN_MSGAVAIL   (3)
#define CAN_NOMSG      (4)
#define CAN_CTRLERROR  (5)
#define CAN_FAIL       (0xff)

// What is the max length of the message
#define CAN_MAX_CHAR_IN_MESSAGE (8)

/** Size of the circular receive buffer, must be power of 2 */
#ifndef CAN_RX_BUFFER_SIZE
#define CAN_RX_BUFFER_SIZE 32
#endif

#define CAN_BUFFER_OVERFLOW  0x0200              /* receive ringbuffer overflow */

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
void 	CAN_setupInt0(void);
void 	CAN_setupPCINT0(void);
uint8_t CAN_fillBuffer(void);
uint8_t CAN_getMessage_Buffer(CANMessage* msg);
uint8_t CAN_sendMessage(const CANMessage* msg);
uint8_t CAN_readMessage(CANMessage* msg);
uint8_t CAN_checkReceiveAvailable(void);
uint8_t CAN_checkError(void);

#endif /* CAN_H_ */

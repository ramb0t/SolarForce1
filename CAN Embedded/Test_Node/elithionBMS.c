/*
 * elithionBMS.c
 *
 *  Created on: 29 Mar 2015
 *      Author: RobThePyro
 */

#include "elithionBMS.h"

// How to generate fake BMS data?
// We need to send the messages in the correct format.


void BMS_send_fake_data(){
	// We need to send a sequence of messages
	// setup a struct to hold the data

	CANMessage message;
	message.id = CAN_ID + CAN_ID_OFFSET;
	message.rtr = 0;
	message.length = 8;
	uint8_t datastring[8];

	message.data = &datastring;


	CAN_sendMessage(&message);

}

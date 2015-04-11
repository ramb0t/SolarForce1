/*
 * elithionBMS.h
 *
 *  Created on: 29 Mar 2015
 *      Author: RobThePyro
 */

#ifndef ELITHIONBMS_H_
#define ELITHIONBMS_H_

#include "../lib/CAN/CAN.h"
// Defines for CAN messages

#define Period			1000	// mS bettween messages
#define CAN_ID_OFFSET	0x7FF
#define CAN_ID			0x1     // ID of the controller


void BMS_send_fake_data(void);



#endif /* ELITHIONBMS_H_ */

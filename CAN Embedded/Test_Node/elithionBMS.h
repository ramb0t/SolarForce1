/*
 * elithionBMS.h
 *
 *  Created on: 29 Mar 2015
 *      Author: RobThePyro
 */

#ifndef ELITHIONBMS_H_
#define ELITHIONBMS_H_

#include "../lib/CAN/CAN.h"
#include <string.h>
#include <util/delay.h>
// Defines for CAN messages

#define Period			1000	// mS bettween messages
#define CAN_ID			0x620   // CAN ID of the BMS

CANMessage BMS[9];



void BMS_init(void);
void BMS_send_fake_data(void);



#endif /* ELITHIONBMS_H_ */

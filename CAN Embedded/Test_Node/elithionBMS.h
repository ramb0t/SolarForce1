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
// Defines for CAN messages

#define Period			1000	// mS bettween messages
#define CAN_ID			0x620   // CAN ID of the BMS

CANMessage MSG0;
CANMessage MSG1;
CANMessage MSG2;
CANMessage MSG3;
CANMessage MSG4;
CANMessage MSG5;
CANMessage MSG6;
CANMessage MSG7;
CANMessage MSG8;



void BMS_init(void);
void BMS_send_fake_data(void);



#endif /* ELITHIONBMS_H_ */

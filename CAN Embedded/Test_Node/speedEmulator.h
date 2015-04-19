/*
 * speedEmulator.h
 *
 *  Created on: 13 Apr 2015
 *      Author: RobThePyro
 */

#ifndef SPEEDEMULATOR_H_
#define SPEEDEMULATOR_H_

#include "../lib/CAN/CAN.h"
#include <string.h>
#include <util/delay.h>
// Defines for CAN messages

#define Period			500	// mS bettween messages
#define CAN_ID			0x100   // CAN ID of the Speed Message

CANMessage SpeedMsg;



void SpeedEmu_init(void);
void SpeedEmu_send_fake_data(void);
void SpeedEmu_set_speed(uint8_t speed);


#endif /* SPEEDEMULATOR_H_ */

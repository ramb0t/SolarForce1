/*
 * speedEmulator.h
 *
 *  Created on: 13 Apr 2015
 *      Author: RobThePyro
 */

#ifndef SPEEDEMULATOR_H_
#define SPEEDEMULATOR_H_

#include "../lib/CAN/CAN.h"
#include "../lib/CAN/CAN_defs.h"
#include <string.h>
#include <util/delay.h>
// Defines for CAN messages

#define SPDPeriod			250	// mS bettween messages
//#define CAN_ID			0x0420   // CAN ID of the Speed Message

CANMessage SpeedMsg;



void SpeedEmu_init(void);
void SpeedEmu_send_fake_data(void);
void SpeedEmu_set_speed(uint8_t speed);
void SpeedEmu_set_HESSpd(uint8_t HESSpd);
void SpeedEmu_set_HESRPM(uint16_t HESRPM);
void SpeedEmu_set_MTSpd(uint8_t MTSpd);
void SpeedEmu_set_MTRPM(uint16_t MTRPM);
void SpeedEmu_set_status(uint8_t status);




#endif /* SPEEDEMULATOR_H_ */

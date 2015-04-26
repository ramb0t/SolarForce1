/*
 * MPPTEmulator.h
 *
 *  Created on: 26 Apr 2015
 *      Author: rambo
 */

#ifndef MPPTEMULATOR_H_
#define MPPTEMULATOR_H_

#include "../lib/CAN/CAN.h"
#include "../lib/CAN/CAN_defs.h"
#include <string.h>
// Defines for CAN messages
CANMessage MPPT1;
CANMessage MPPT2;
CANMessage MPPT3;
CANMessage MPPT4;



void MPPTEmu_init(void);
void MPPTEmu_SendReply(uint8_t MPPT_id);

#endif /* MPPTEMULATOR_H_ */

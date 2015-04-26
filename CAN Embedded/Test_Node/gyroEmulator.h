/*
 * gyroEmulator.h
 *
 *  Created on: 26 Apr 2015
 *      Author: rambo
 */

#ifndef GYROEMULATOR_H_
#define GYROEMULATOR_H_

#include "../lib/CAN/CAN.h"
#include "../lib/CAN/CAN_defs.h"
#include <string.h>
// Defines for CAN messages

#define GyroPeriod			1000	// mS bettween messages

CANMessage GyroMsg_Angle;
CANMessage GyroMsg_Gyro;
CANMessage GyroMsg_Accel;



void GyroEmu_init(void);
void GyroEmu_send_fake_data(void);
void GyroEmu_set_AngleX(uint16_t angleX);
void GyroEmu_set_AngleY(uint16_t angleY);
void GyroEmu_set_AngleZ(uint16_t angleZ);

#endif /* GYROEMULATOR_H_ */

/*
 * gyroEmulator.c
 *
 *  Created on: 26 Apr 2015
 *      Author: rambo
 */

#include "gyroEmulator.h"

void GyroEmu_init(void){
	// Init the message
	GyroMsg_Angle = (CANMessage){.id=CANID_IMU_GYRO,.rtr=0,.length=8,.data={
				0,0,0,0,0,0,0,0
		}};
	GyroMsg_Gyro = (CANMessage){.id=CANID_IMU_EULER,.rtr=0,.length=8,.data={
				0,0,0,0,0,0,0,0
		}};
	GyroMsg_Accel = (CANMessage){.id=CANID_GYRO_ACCEL,.rtr=0,.length=8,.data={
				0,0,0,0,0,0,0,0
		}};
}

void GyroEmu_send_fake_data(void){
	CAN_sendMessage(&GyroMsg_Angle);
	CAN_sendMessage(&GyroMsg_Gyro);
	CAN_sendMessage(&GyroMsg_Accel);
}

void GyroEmu_set_AngleX(uint16_t angleX){
	GyroMsg_Angle.data[0] = angleX <<8;
	GyroMsg_Angle.data[1] = angleX;
}
void GyroEmu_set_AngleY(uint16_t angleY){
	GyroMsg_Angle.data[2] = angleY <<8;
	GyroMsg_Angle.data[3] = angleY;
}
void GyroEmu_set_AngleZ(uint16_t angleZ){
	GyroMsg_Angle.data[4] = angleZ <<8;
	GyroMsg_Angle.data[5] = angleZ;
}

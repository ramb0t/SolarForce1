/*
 * speedEmulator.c
 *
 *  Created on: 13 Apr 2015
 *      Author: RobThePyro
 */

#include "speedEmulator.h"

void SpeedEmu_init(void){
	SpeedMsg = (CANMessage){.id=CAN_ID,.rtr=0,.length=2,.data={
			0,0
	}};
}

void SpeedEmu_send_fake_data(void){
	CAN_sendMessage(&SpeedMsg);
}

void SpeedEmu_set_speed(uint8_t speed){
	SpeedMsg.data[0] = speed;

}

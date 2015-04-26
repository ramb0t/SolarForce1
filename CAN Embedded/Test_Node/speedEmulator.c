/*
 * speedEmulator.c
 *
 *  Created on: 13 Apr 2015
 *      Author: RobThePyro
 */

#include "speedEmulator.h"

void SpeedEmu_init(void){
	SpeedMsg = (CANMessage){.id=CAN_ID,.rtr=0,.length=8,.data={
			0,0,0,0,0,0,0,0
	}};
}

void SpeedEmu_send_fake_data(void){
	CAN_sendMessage(&SpeedMsg);
}

void SpeedEmu_set_speed(uint8_t speed){
	SpeedMsg.data[0] = speed;  // Load the Byte

}
void SpeedEmu_set_HESSpd(uint8_t HESSpd){
	SpeedMsg.data[1] = HESSpd;
}
void SpeedEmu_set_HESRPM(uint16_t HESRPM){
	SpeedMsg.data[2] = HESRPM<<8;
	SpeedMsg.data[3] = HESRPM;
}
void SpeedEmu_set_MTSpd(uint8_t MTSpd){
	SpeedMsg.data[4] = MTSpd;
}
void SpeedEmu_set_MTRPM(uint16_t MTRPM){
	SpeedMsg.data[5] = MTRPM<<8;
	SpeedMsg.data[6] = MTRPM;
}
void SpeedEmu_set_status(uint8_t status){
	SpeedMsg.data[7] = status;
}

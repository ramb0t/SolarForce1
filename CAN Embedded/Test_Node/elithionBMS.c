/*
 * elithionBMS.c
 *
 *  Created on: 29 Mar 2015
 *      Author: RobThePyro
 */

#include "elithionBMS.h"


void BMS_init(void){
	BMS[0] = (CANMessage) {.id=CAN_ID+0,.rtr=0,.length=8,.data={
				'E','L','I','T','H','I','O','N'
		}};

	BMS[1] = (CANMessage) {.id=CAN_ID+1,.rtr=0,.length=8,.data={
				'2','C','N','F','2','.','2','6'
		}};

	BMS[2] = (CANMessage) {.id=CAN_ID+2,.rtr=0,.length=7,.data={
			0b00000001,  //State
			0b00000000, 0b00000000, // Timer
			0b00100000,  //Flags
			0b00010100,  //Fault Code
			0b00000000,  //Level Fault
			0b01000000   //Warnings
		}};

	BMS[3] = (CANMessage) {.id=CAN_ID+3,.rtr=0,.length=6,.data={
			0b00000000, 0b00000000, //Pack Voltage
			0b00000000,  //MinVTG
			0b00000000,  //MinVTG #
			0b00000000,  //MaxVTG
			0b00000000,  //MAXVTG #
		}};

	BMS[4] = (CANMessage) {.id=CAN_ID+4,.rtr=0,.length=6,.data={
			0b00000000, 0b00000000, //Current
			0b00000000, 0b00000000, //Charge Limit
			0b00000000, 0b00000000, //Discharge Limit
		}};

	BMS[5] = (CANMessage) {.id=CAN_ID+5,.rtr=0,.length=8,.data={
			0b00000000, 0b00000000, 0b00000000, 0b00000000, //Batt. Energy In
			0b00000000, 0b00000000, 0b00000000, 0b00000000  //Batt. Energy Out
		}};

	BMS[6] = (CANMessage) {.id=CAN_ID+6,.rtr=0,.length=7,.data={
			0b00000000,  //SOC
			0b00000000, 0b00000000,  //DOD
			0b00000000, 0b00000000,  //Capacity
			0b00000000,  //00h
			0b00000000   //SOH
		}};

	BMS[7] = (CANMessage) {.id=CAN_ID+7,.rtr=0,.length=6,.data={
			0b00000000,  //Temperature
			0b00000000,  // -
			0b00000000,  //Min Temp
			0b00000000,  //Min Temp #
			0b00000000,  //Max Temp
			0b00000000   //Max Temp#
		}};


	BMS[8] = (CANMessage) {.id=CAN_ID+8,.rtr=0,.length=6,.data={
			0b00000000, 0b00000000,  //Pack Resistance
			0b00000000,  //Min res
			0b00000000,  //Min res #
			0b00000000,  //Max res
			0b00000000   //Max res#
		}};
}

// How to generate fake BMS data?
// We need to send the messages in the correct format.


void BMS_send_fake_data(){
	// We need to send a sequence of messages

	for(uint8_t i = 0; i < 9; i++){
		CAN_sendMessage(&BMS[i]);
		_delay_us(1000);
	}

	BMS[6].data[0]++; // SOC
	if(BMS[6].data[0] >100){
		BMS[6].data[0] = 0;
	}

	BMS[3].data[1]++; // Voltage
	BMS[4].data[1]++; // Current
	BMS[7].data[0]++; // Temperature

}

/*
 * elithionBMS.c
 *
 *  Created on: 29 Mar 2015
 *      Author: RobThePyro
 */

#include "elithionBMS.h"


void BMS_init(void){
	MSG0 = (CANMessage) {.id=CAN_ID+0,.rtr=0,.length=8,.data={
				'E','L','I','T','H','I','O','n'
		}};

	MSG1 = (CANMessage) {.id=CAN_ID+1,.rtr=0,.length=8,.data={
				'2','C','N','F','2','.','2','6'
		}};

	MSG2 = (CANMessage) {.id=CAN_ID+2,.rtr=0,.length=7,.data={
			0b00000000,  //State
			0b00000000, 0b00000000, // Timer
			0b00000000,  //Flags
			0b00000000,  //Fault Code
			0b00000000,  //Level Fault
			0b00000000   //Warnings
		}};

	MSG3 = (CANMessage) {.id=CAN_ID+3,.rtr=0,.length=6,.data={
			0b00000000, 0b00000000, //Pack Voltage
			0b00000000,  //MinVTG
			0b00000000,  //MinVTG #
			0b00000000,  //MaxVTG
			0b00000000,  //MAXVTG #
		}};

	MSG4 = (CANMessage) {.id=CAN_ID+4,.rtr=0,.length=6,.data={
			0b00000000, 0b00000000, //Current
			0b00000000, 0b00000000, //Charge Limit
			0b00000000, 0b00000000, //Discharge Limit
		}};

	MSG5 = (CANMessage) {.id=CAN_ID+5,.rtr=0,.length=8,.data={
			0b00000000, 0b00000000, 0b00000000, 0b00000000, //Batt. Energy In
			0b00000000, 0b00000000, 0b00000000, 0b00000000  //Batt. Energy Out
		}};

	MSG6 = (CANMessage) {.id=CAN_ID+6,.rtr=0,.length=7,.data={
			0b00000000,  //SOC
			0b00000000, 0b00000000,  //DOD
			0b00000000, 0b00000000,  //Capacity
			0b00000000,  //00h
			0b00000000   //SOH
		}};

	MSG7 = (CANMessage) {.id=CAN_ID+7,.rtr=0,.length=6,.data={
			0b00000000,  //Temperature
			0b00000000,  // -
			0b00000000,  //Min Temp
			0b00000000,  //Min Temp #
			0b00000000,  //Max Temp
			0b00000000   //Max Temp#
		}};


	MSG8 = (CANMessage) {.id=CAN_ID+8,.rtr=0,.length=6,.data={
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
#define mstime	50
	CAN_sendMessage(&MSG0);
	_delay_ms(mstime);
	CAN_sendMessage(&MSG1);
	_delay_ms(mstime);
	CAN_sendMessage(&MSG2);
	_delay_ms(mstime);
	CAN_sendMessage(&MSG3);
	_delay_ms(mstime);
	CAN_sendMessage(&MSG4);
	_delay_ms(mstime);
	CAN_sendMessage(&MSG5);
	_delay_ms(mstime);
	CAN_sendMessage(&MSG6);
	_delay_ms(mstime);
	CAN_sendMessage(&MSG7);
	_delay_ms(mstime);
	CAN_sendMessage(&MSG8);
	_delay_ms(mstime);

}

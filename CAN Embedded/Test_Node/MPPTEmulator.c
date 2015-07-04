/*
 * MPPTEmulator.c
 *
 *  Created on: 26 Apr 2015
 *      Author: rambo
 */

#include "MPPTEmulator.h"

void MPPTEmu_init(void){
	vin = 1234;
	vout = 256;
	iin = 1532;
	temp = 65;
	// Init the message
	// Message Struckture!
	// B1 : BLVR | OVT | NOC | UNDV | x | x | MSB Vin | MSB Vin
	// B2 : LSB Vin
	// B3 : xxxxxx MSB Iin
	// B4 : LSB Iin
	// B5 : xxxxxx MSB Vout
	// B6 : LSB Vout
	// B7 : Tamb 'C
	MPPT1 = (CANMessage){.id=CANID_MPPT1,.rtr=0,.length=7,.data={
				0x80,vin,iin>>8,iin,vout>>8,vout,temp
		}};
	MPPT2 = (CANMessage){.id=CANID_MPPT2,.rtr=0,.length=7,.data={
				0x41,10,0,20,0,30,10
		}};
	MPPT3 = (CANMessage){.id=CANID_MPPT3,.rtr=0,.length=7,.data={
				0x22,40,0,50,0,60,15
		}};
	MPPT4 = (CANMessage){.id=CANID_MPPT4,.rtr=0,.length=7,.data={
				0x13,70,0,80,0,90,20
		}};
}
void MPPTEmu_SendReply(uint8_t MPPT_id){
	vin = vin + 32;
	vout = vout + 64;
	iin = iin + 12;
	temp = temp + 1;
	switch(MPPT_id){
	case 1:
		MPPT1 = (CANMessage){.id=CANID_MPPT1,.rtr=0,.length=7,.data={
						0x80,vin,iin>>8,iin,vout>>8,vout,temp
				}};
		CAN_sendMessage(&MPPT1);
		break;
	case 2:
		CAN_sendMessage(&MPPT2);
		break;
	case 3:
		CAN_sendMessage(&MPPT3);
		break;
	case 4:
		CAN_sendMessage(&MPPT4);
		break;
	default:
		break;
	} // end switch

}

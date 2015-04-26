/*
 * CAN_Int0.c
 *
 * Created: 2015/04/24 08:56:22 PM
 *  Author: Matt
 */ 
#include "MAVLink_Messaging.h"
#include "CAN_Int0.h"
#include "GlobalDefs.h"


//CAN_Init(CAN_125KBPS_16MHZ); // Setup CAN Bus with our desired speed

ISR(INT0_vect)
{
	CAN_fillBuffer();

		//if (CAN_getMessage_Buffer(&Input_data)==CAN_OK)
		//{
			//if (CAN_Decode(&Input_data)==CAN_MSG_DECODED)	//if a new message has been decoded
			//{	
				//updateMAV_flag = TRUE;						//...set a flag to send this data & store data
			//}else
			//{
				//return;										//else leave it alone
			//}
		//}
		

}



uint8_t CAN_Decode(CANMessage *message)
{
	
	speedHEUpdated=0;
	speedMDUpdated=0;
	acceloUpdated=0;
	gyroUpdated=0;

	bms1Updated=0;
	bms2Updated=0;
	bms3Updated=0;
	bms4Updated=0;
	bms5Updated=0;
	bms6Updated=0;
	bms7Updated=0;
	bms8Updated=0;

	mppt1Updated=0;
	mppt2Updated=0;
	mppt3Updated=0;
	mppt4Updated=0;
	
	
	switch (message->id)
				{
					/*Speed	Data is aggregated across the Hall Effect and Motor Driver nodes
					Data as follows 
					Base ID 0x420
					<<Sent as "Hall Effect in MAVID">>
					SpeedData[0] = Averaged HE and Motor RPM Speed;
					SpeedData[1] = HallEffect speed
					SpeedData[2] = Hall RPM L
					SpeedData[3] = Hall RPM H
					
					<<Sent as MotorDriver in MAVID">>
					SpeedData[4] = MotorDriver Speed
					SpeedData[5] = MotorDriver RPM L
					SpeedData[6] = MotorDriver RPM H
					SpeedData[7] = Status flag
					
					*/
				case 	CANID_SPEED:
				{
							//LED_DIAG_PORT |= (1<<LED_DIAG_GRN);		
							CANData.avgSpeed = message->data[0];
							CANData.hesSPeed = message->data[1];
							CANData.hesRPM = (message->data[3]<<8)|(message->data[2]);
							CANData.motorSpeed = message->data[4];
							CANData.motorRPM = (message->data[5]<<8)|(message->data[6]);
							CANData.statusFlags = message->data[7];
						//
						
						speedMDUpdated=1;	
						speedHEUpdated=1;
						return CAN_MSG_DECODED;
				}
					
				/*NOTE: BMS Data across different messages, we want:
				Base CANID =	BMS[0] = 0x0620
								BMS[1] = 0x0621
								BMS[2] = 0x0622
								BMS[3] = 0x0623
								BMS[4] = 0x0624
								BMS[5] = 0x0625
								BMS[6] = 0x0626
								BMS[7] = 0x0627
								BMS[8] = 0x0628
						.........................................................................
						Parameters	 Value	Detail							CANID byte			CAN Object Number	Range/Type
						...........................................................................
						2 = uint8_t fault condition?						BMS[2].data[3]		BMSdata[0]					0=no 1=yes
						3 = uint16_t source current							BMS[5].data[0]		BMSdata[1]					0-65535mA
						4 = uint16_t net_current (load)						BMS[4].data[0]		BMSdata[2]					0-65535mA
						5 = char bat_fan_status																				t=OK f=FAULT
						6 = uint8_t LLIM_state																				1=flag active 0=flag not active
						7 = uint8_t HLIM_state																				1=flag active 0=flag not active
						8 = uint8_t state_of_chg (percentage)				BMS[6].data[0]		BMSdata[3]					0-100%
						9 = uint16_t pack_voltage							BMS[3].data[0]		BMSdata[4]					0-65535V
						10 = const uint16_t *cell_voltages [low,avg,high]	BMS[3].data[1,3]	BMSdata[5,6,7]					0-65535V per element
						11 = const uint16_t *cell_temps [low,avg,high]		BMS[7].data[2,4]	BMSdata[8,9,10]					0-65535C per element
						12 = uint8_t system_status												MAVLINK_ENUM
				
				*/
					
				case	CANID_BMS2:
				{
					utoa(message->data[3],buff,10);		//fault flags
					//BMS_Message.data[0] = message->data[3];
					
					//uart_puts(buff);
					
					//for (int i=0;i<16;i++)						//16 data fields
					//{
						//itoa(message->data[i],buff,10);
						//BMS_Message.data[i] = message->data[i]; //store into CAN object for BMS
						//uart_puts(buff);
					//}
					CANData.BMSData_warnings[0] = message->data[0];
					CANData.BMSData_warnings[1] = message->data[3];
					CANData.BMSData_warnings[2] = message->data[4];
					CANData.BMSData_warnings[3] = message->data[5];
					CANData.BMSData_warnings[4] = message->data[6];
					
					bms2Updated=1;
					return CAN_MSG_DECODED;
				}
					
				case	CANID_BMS3:
				{
					CANData.packVoltage = (message->data[0]<<8)|(message->data[1]);
					CANData.minVoltage = message->data[2];
					CANData.minVoltageID = message->data[3];
					CANData.maxVoltage = message->data[4];
					CANData.maxVoltageID = message->data[5];
					
					//uart_puts("\n");
					//uart_puts("CAN from BMS3:");					//Human readable data on UART
					//uart_puts(message->id);
					//
					//utoa(message->data[0],buff,10);		//low pack voltage
					////BMS_Message.data[5] = (message->data[2]<<8)|(message->data[3]);
					////uart_puts(buff);
					//
					//utoa(message->data[0],buff,10);		// avg pack voltages
					////BMS_Message.data[6] = (message->data[0]<<8)|(message->data[1]);
					////uart_puts(buff);
					//
					//utoa(message->data[0],buff,10);		//high pack voltages
					////BMS_Message.data[7] = (message->data[4]<<8)|(message->data[5]);
					////uart_puts(buff);
					//
					bms3Updated=1;
					return CAN_MSG_DECODED;
				}
				
				case	CANID_BMS4:
				{
					CANData.current = (message->data[0]<<8)|(message->data[1]);
					CANData.chargeLimit = (message->data[2]<<8)|(message->data[3]);
					CANData.dischargeLimit = (message->data[4]<<8)|(message->data[5]);
					//uart_puts("\n");
					//uart_puts("CAN from BMS4:");					//Human readable data on UART
					//uart_puts(message->id);
					
					//utoa(message->data[0],buff,10);		//pack current
					//utoa(message->data[1],buff,10);
					//BMS_Message.data[2] = (message->data[0]<<8)|(message->data[1]);
					//uart_puts(buff);
					
					bms4Updated=1;
					return CAN_MSG_DECODED;
				}
				
				case	CANID_BMS5:
				{
					CANData.batteryEnergyIn = (message->data[0]<<24)|(message->data[1]<<16)|(message->data[2]<<8)|(message->data[3]);
					CANData.batteryEnergyIn = (message->data[4]<<24)|(message->data[5]<<16)|(message->data[6]<<8)|(message->data[7]);
					
					bms5Updated=1;
					return CAN_MSG_DECODED;
				}
				

				case	CANID_BMS6:
				{
					CANData.SOC = message->data[0];
					CANData.DOD = (message->data[1]<<8)|(message->data[2]);
					CANData.capacity = (message->data[3]<<8)|(message->data[4]);
					CANData.SOH = message->data[6];
					
					//uart_puts("\n");
					//uart_puts("CAN from BMS6:");					//Human readable data on UART
					//uart_puts(message->id);
				
					//utoa(message->data[0],buff,10);		//SOC
					//BMS_Message.data[3] = message->data[0];
					//uart_puts(buff);
					
					bms6Updated=1;
					return CAN_MSG_DECODED;
				}
				
				case	CANID_BMS7:
				{
					//uart_puts("\n");
					//uart_puts("CAN from BMS7:");					//Human readable data on UART
					//uart_puts(message->id);
				//
					//utoa(message->data[2],buff,10);			//Min temps
					////uart_puts(buff);
					//utoa(message->data[3],buff,10);			//Min temps
					////uart_puts(buff);
					////BMS_Message.data[8] = (message->data[2]<<8)|(message->data[3]);
					//
				//
					//utoa(message->data[0],buff,10);			//Avg temps
					////BMS_Message.data[9] = message->data[0];
					////uart_puts(buff);
				//
					//utoa(message->data[4],buff,10);			//Max temps
					////BMS_Message.data[10] = (message->data[4]<<8)|(message->data[5]);
					////uart_puts(buff);
					//
					
					CANData.minTempID = message->data[0];
					CANData.minTemperature = message->data[2];
					CANData.temperature = message->data[3];
					CANData.maxTemperature = message->data[4];
					CANData.maxTempID = message->data[5];
					
					bms7Updated=1;
					return CAN_MSG_DECODED;
				}
				
				case CANID_BMS8:
				{
					CANData.packResistance = (message->data[0]<<8)|(message->data[1]);
					CANData.minRes = message->data[2];
					CANData.minResID = message->data[3];
					CANData.maxRes = message->data[4];
				}
				
				case	CANID_GYRO_GYRO:
				{	
					CANData.gyro_x = (message->data[0]<<8)|(message->data[1]);
					CANData.gyro_y = (message->data[2]<<8)|(message->data[3]);
					CANData.gyro_z = (message->data[4]<<8)|(message->data[5]);
					gyroUpdated=1;
					return CAN_MSG_DECODED;
				}
				
				case	CANID_GYRO_ACCEL:
				{
					CANData.accel_x = (message->data[0]<<8)|(message->data[1]);
					CANData.accel_y = (message->data[2]<<8)|(message->data[3]);
					CANData.accel_z = (message->data[4]<<8)|(message->data[5]);
					
					acceloUpdated=1;
					return CAN_MSG_DECODED;
				}
				
				case	CANID_MPPT1:
				{	
					//----METHOD TO BITSHIFT--------//
					/*uint16_t val = (byte4&0x03)<<8;
					val &= 0xff00;
					val |= (byte5&0x00ff);*/
					
					//uart_puts("\n");
					//uart_puts("CAN from MPPT1:");
					//uart_puts(message->id);
					//for (int i=0;i<4;i++)						//4 data fields
					//{
						//utoa(message->data[i],buff,10);
						////MPPT1_Message.data[i] = message->data[i];
						////uart_puts(buff);
					//}
					
					uint16_t temp = ((message->data[0] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[1] & (0x00FF));
					CANData.Vin1 = temp;
					
					uint16_t temp2 = ((message->data[2] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[3] & (0x00FF));
					CANData.Iin1 = temp2;
					
					uint16_t temp3 = ((message->data[4] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[5] & (0x00FF));
					CANData.Vin1 = temp3;
					
					CANData.Tamb1 = message->data[6];
					
					mppt1Updated=1;
					return CAN_MSG_DECODED;
				}
				
				case	CANID_MPPT2:
				{
					uint16_t temp = ((message->data[0] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[1] & (0x00FF));
					CANData.Vin2 = temp;
					
					uint16_t temp2 = ((message->data[2] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[3] & (0x00FF));
					CANData.Iin2 = temp2;
					
					uint16_t temp3 = ((message->data[4] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[5] & (0x00FF));
					CANData.Vin2 = temp3;
					
					CANData.Tamb2 = message->data[6];
				
				mppt2Updated=1;
				return CAN_MSG_DECODED;
				}
				
				case	CANID_MPPT3:
				{
					uint16_t temp = ((message->data[0] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[1] & (0x00FF));
					CANData.Vin3 = temp;
					
					uint16_t temp2 = ((message->data[2] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[3] & (0x00FF));
					CANData.Iin3 = temp2;
					
					uint16_t temp3 = ((message->data[4] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[5] & (0x00FF));
					CANData.Vin3 = temp3;
					
					CANData.Tamb3 = message->data[6];
				
				mppt3Updated=1;
				return CAN_MSG_DECODED;
				}
				
				case	CANID_MPPT4:
				{
					uint16_t temp = ((message->data[0] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[1] & (0x00FF));
					CANData.Vin4 = temp;
									
					uint16_t temp2 = ((message->data[2] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[3] & (0x00FF));
					CANData.Iin4 = temp2;
									
					uint16_t temp3 = ((message->data[4] & (0x03))<<8);
					temp &= 0xFF00;
					temp |= (message->data[5] & (0x00FF));
					CANData.Vin4 = temp3;
									
					CANData.Tamb4 = message->data[6];
				
				mppt4Updated=1;
				return CAN_MSG_DECODED;
				}
			}
				return CAN_NOT_DECODED;					//else if data not decoded return error
}
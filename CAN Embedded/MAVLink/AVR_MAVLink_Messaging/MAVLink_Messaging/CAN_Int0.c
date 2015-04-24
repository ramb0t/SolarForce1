/*
 * CAN_Int0.c
 *
 * Created: 2015/04/24 08:56:22 PM
 *  Author: Matt
 */ 

CAN_Init(CAN_125KBPS_16MHZ); // Setup CAN Bus with our desired speed
Timer0_init();

ISR(INT0_vect)
{
	while (flag)
	{
		if (CAN_getMessage_Buffer(&Input_data)==CAN_OK)
		{
			if (CAN_Decode(&Input_data)==CAN_MSG_DECODED)
			{
				updateMAV_flag = TRUE;
			}
		}
		
	}
}

uint8_t CAN_Decode(CANMessage *message)
{
	switch (Input_data.id)
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
				case 	MOTOR_DRIVER_CANID:
				{
						uart_puts("\n");
						uart_puts("CAN from MD:");
						uart_puts(Input_data.id);				//Human readable data on UART
						uart_puts(":");
						for (int i=0;i<4;i++)
						{
							uart_puts(":");
							itoa(Input_data.data[i],buff,10);	//convert to ascii form
							Speed_Message.data[i] = Input_data.data[i]; //store into CAN object for speed
							uart_puts(buff);
						}
					
					
						uart_puts("\n");
						uart_puts("CAN from HE:");
						uart_puts(Input_data.id);
						for (int i=4;i<8;i++)
						{
						itoa(Input_data.data[i],buff,10);
						Speed_Message.data[i] = Input_data.data[i];
						uart_puts(buff);
						}
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
					
				case	BMS_2_CANID:
				{
					uart_puts("\n");
					uart_puts("CAN from BMS2:");					//Human readable data on UART
					uart_puts(Input_data.id);
					
					itoa(Input_data.data[3],buff,10);		//fault flags
					BMS_Message.data[0] = Input_data.data[3];
					uart_puts(buff);
					
					//for (int i=0;i<16;i++)						//16 data fields
					//{
						//itoa(Input_data.data[i],buff,10);
						//BMS_Message.data[i] = Input_data.data[i]; //store into CAN object for BMS
						//uart_puts(buff);
					//}
					return CAN_MSG_DECODED;
				}
					
				case	BMS_3_CANID:
				{
					uart_puts("\n");
					uart_puts("CAN from BMS3:");					//Human readable data on UART
					uart_puts(Input_data.id);
					
					itoa(Input_data.data[0],buff,10);		//low pack voltage
					BMS_Message.data[5] = (Input_data.data[2]<<8)|(Input_data.data[3]);
					uart_puts(buff);
					
					itoa(Input_data.data[0],buff,10);		// avg pack voltages
					BMS_Message.data[6] = (Input_data.data[0]<<8)|(Input_data.data[1]);
					uart_puts(buff);
					
					itoa(Input_data.data[0],buff,10);		//high pack voltages
					BMS_Message.data[7] = (Input_data.data[4]<<8)|(Input_data.data[5]);
					uart_puts(buff);
					return CAN_MSG_DECODED;
				}
				
				case	BMS_4_CANID:
				{
					uart_puts("\n");
					uart_puts("CAN from BMS4:");					//Human readable data on UART
					uart_puts(Input_data.id);
					
					itoa(Input_data.data[0],buff,10);		//pack current
					itoa(Input_data.data[1],buff,10);
					BMS_Message.data[2] = (Input_data.data[0]<<8)|(Input_data.data[1]);
					uart_puts(buff);
					return CAN_MSG_DECODED;
				}
				

				case	BMS_6_CANID:
				{
					uart_puts("\n");
					uart_puts("CAN from BMS6:");					//Human readable data on UART
					uart_puts(Input_data.id);
				
					itoa(Input_data.data[0],buff,10);		//SOC
					BMS_Message.data[3] = Input_data.data[0];
					uart_puts(buff);
					return CAN_MSG_DECODED;
				}
				
				case	BMS_7_CANID:
				{
					uart_puts("\n");
					uart_puts("CAN from BMS7:");					//Human readable data on UART
					uart_puts(Input_data.id);
				
					itoa(Input_data.data[2],buff,10);			//Min temps
					uart_puts(buff);
					itoa(Input_data.data[3],buff,10);			//Min temps
					uart_puts(buff);
					BMS_Message.data[8] = (Input_data.data[2]<<8)|(Input_data.data[3]);
					
				
					itoa(Input_data.data[0],buff,10);			//Avg temps
					BMS_Message.data[9] = Input_data.data[0];
					uart_puts(buff);
				
					itoa(Input_data.data[4],buff,10);			//Max temps
					BMS_Message.data[10] = (Input_data.data[4]<<8)|(Input_data.data[5]);
					uart_puts(buff);
					return CAN_MSG_DECODED;
				}
				
				case	GYRO_CANID:
				{	
					uart_puts("\n");
					uart_puts("CAN from GY:");
					uart_puts(Input_data.id);
					Gyro_Message.data[0] = Input_data.data[0];
					uart_puts(buff);
					return CAN_MSG_DECODED;
				}
				
				case	ACCELO_CANID:
				{
					uart_puts("\n");
					uart_puts("CAN from GY:");
					uart_puts(Input_data.id);
					Accelo_message.data[1] = Input_data.data[1];
					uart_puts(buff);
					return CAN_MSG_DECODED;
				}
				
				case	MPPT1_CANID:
				{	
					uart_puts("\n");
					uart_puts("CAN from MPPT1:");
					uart_puts(Input_data.id);
					for (int i=0;i<4;i++)						//4 data fields
					{
						itoa(Input_data.data[i],buff,10);
						MPPT1_Message.data[i] = Input_data.data[i];
						uart_puts(buff);
					}
					return CAN_MSG_DECODED;
				}
				
				case	MPPT2_CANID:
				{
				uart_puts("\n");
				uart_puts("CAN from MPPT1:");
				uart_puts(Input_data.id);
				for (int i=0;i<4;i++)						//4 data fields
				{
					itoa(Input_data.data[i],buff,10);
					MPPT2_Message.data[i] = Input_data.data[i];
					uart_puts(buff);
				}
				return CAN_MSG_DECODED;
				}
				
				case	MPPT3_CANID:
				{
				uart_puts("\n");
				uart_puts("CAN from MPPT1:");
				uart_puts(Input_data.id);
				for (int i=0;i<4;i++)						//4 data fields
				{
					itoa(Input_data.data[i],buff,10);
					MPPT3_Message.data[i] = Input_data.data[i];
					uart_puts(buff);
				}
				return CAN_MSG_DECODED;
				}
				
				case	MPPT4_CANID:
				{
				uart_puts("\n");
				uart_puts("CAN from MPPT1:");
				uart_puts(Input_data.id);
				for (int i=0;i<4;i++)						//4 data fields
				{
					itoa(Input_data.data[i],buff,10);
					MPPT4_Message.data[i] = Input_data.data[i];
					uart_puts(buff);
				}
				return CAN_MSG_DECODED;
				}
				return CAN_NOT_DECODED;					//else if data not decoded return error
}
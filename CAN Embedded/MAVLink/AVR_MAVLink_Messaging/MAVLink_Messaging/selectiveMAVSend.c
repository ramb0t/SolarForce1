/*
 * selectiveMAVSend.c
 *
 * Created: 2015/04/25 03:02:56 AM
 *  Author: Matt
 */ 


uart_puts(" ");
			//---------------MAVLink Data---------------------------//
			// Initialize the required buffers
			// Set correct buffer lengths

			mavlink_message_t msg;
			uint8_t buf[MAVLINK_MAX_PACKET_LEN];
			uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
			char buff[10];
			
			/*FOR TEST WITH QGC SOFTWARE ONLY--------------------------------------------
			This message sends "UAV" style messages for the QGC software. For testing only!
			*/
			if (DEBUG)
			{
				//mavlink_msg_sys_status_send(0,base_mode,custom_mode,system_status,15,4201,2,0);
			}
			//-----------------------------------------------------------------------
			/*For all packaging, parameters 1 = MAVLink Channel */
			
			/*-----------------------------------------------------------------------
			NAME: Motor Driver Data
			DESCRIPTION: Speed from the motor driver RPM and error flags
				.........................................................................
				Parameters		 Value/Byte		Details							Range/Type
				...........................................................................
				
				uint8_t speed	SpeedData[4]	MotorDriver	Speed				0-255kmh
				//DEPRECATED uint8_t speed	SpeedData[5]	MotorDriver	RPM	L				0-255RPM L
				//DEPRECATED uint8_t rpm		SpeedData[6]	MotorDriver	RPM	H				0-255RPM H
				uint8_t rpm		SpeedData[7]	Status bits						xxxxxxxx */
//TESTING WAS SpeedMessage.data[1] BEFORE
			mavlink_msg_motor_driver_send(0,Speed_Message.data[4],Speed_Message.data[7]);

			
			/*-----------------------------------------------------------------------
			NAME: Hall Effect Sensor Data
			DESCRIPTION: Speed from the Hall Effect Sensors and error flags	
			.........................................................................
			Parameters		 Value/Byte		Details							Range/Type
			...........................................................................
							
			uint8_t speed	SpeedData[0]	Averaged HE and Motor RPM Speed	0-255kmh
			//DEPRECATED\\	uint8_t speed	SpeedData[1]	HallEffect speed				0=255kmh
			uint8_t rpm		SpeedData[2]	Hall RPM L						0-255RPM
			uint8_t rpm		SpeedData[3]	Hall RPM H						0-255RPM
																					*/
			
			//uart_flush();
			mavlink_msg_hall_effect_send(MAVLINK_COMM_0,Speed_Message.data[0],Speed_Message.data[2],Speed_Message.data[3]);
			
			//uart_puts("RX");
			//uart_puts(MAV_Rx_buff);
			/*-----------------------------------------------------------------------
			NAME: BMS Data
			DESCRIPTION: All data originating from the BMS, including error flags
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
			//					voltages min			voltage avg			voltage max
			uint16_t volt[] = {BMS_Message.data[5],BMS_Message.data[6],BMS_Message.data[7]};
				//				temp min				temp avg				temp max
			uint16_t temp[] = {BMS_Message.data[8],BMS_Message.data[9],BMS_Message.data[10]};
			uint16_t *cell_voltage = volt;	
			uint16_t *cell_temp = temp;

			//uart_flush();
			mavlink_msg_bms_data_send(MAVLINK_COMM_0,BMS_Message.data[0],BMS_Message.data[1],BMS_Message.data[2],'t',0,0,BMS_Message.data[3],BMS_Message.data[4],cell_voltage,cell_temp,MAV_STATE_ACTIVE);

			/*-----------------------------------------------------------------------
			NAME: Accelerometer/Gyroscope Data
			DESCRIPTION: Yaw, Pitch, Roll and Acceleration data from MPU6050
			.........................................................................
			Parameters		Value	Detail									Range/Type
			...........................................................................
								4 = int8_t acceleration (m.s^-2)			-127 to 127 m.s^-2		
								5 = int8_t incline (degrees)				-127 to 127 (0-100 @ 10 counts per degree)
			//TESTING																	*/
			
			//mavlink_msg_accelo_gyro_send(MAVLINK_COMM_0, /*CANBusInput.data[0]*/2,11);
			
//TESTING	mavlink_msg_accelo_gyro_pack(100,200,&msg,CANBusInput.data[3],CANBusInput.data[4]);
			//MAV_uart_send(buf,len);
			
			/*-----------------------------------------------------------------------
			NAME: GPS Data
			DESCRIPTION: Location, speed and other GPS data 
			.........................................................................
			Parameters		Value	Detail									Range/Type
			...........................................................................
								4 = const char *latitude					12 characters max
								5 = const char *longitude					12 characters max
								6 = const char *time						12 characters max
								7 = const char *date						12 characters max
								8 = const char *lock_error					12 characters max "OK" or "INVALID"
																					*/
			char *latitude = parts[3];
			char *longitude = parts[4];
			char *time = parts[1];
			char *date = parts[9];
			char lock_flag = parts[2];
			char *lock_error = lock_error[7];
			
			if (lock_flag == 'A')
			{
				lock_error = "OK";
			}else lock_error = "INVALID";
			
			mavlink_msg_gps_send(MAVLINK_COMM_0,latitude,longitude,time,date,lock_error);

			
			/*-----------------------------------------------------------------------
			NAME: MPPT Data
			DESCRIPTION: Telemetry data from the MPPT's. There a 4 definitions, one for each MPPT. All variable ranges and types are the same.
			.........................................................................
			Parameters(x4)		Value	Detail								Range/Type
			...........................................................................
								4 = 	uint16_t voltage_in					0-65535mV
								5 =		uint16_t current_in					0-65535mA
								6 =		uint8_t overtemp?					0=no 1=yes
								7 =		uint8_t undervolt?					0=no 1=yes
			//TESTING																		*/
			
//TESTING	mavlink_msg_mppt1_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			//MAV_uart_send(buf,len);
			mavlink_msg_mppt1_data_send(MAVLINK_COMM_0,MPPT1_Message.data[0],MPPT1_Message.data[1],MPPT1_Message.data[2],MPPT1_Message.data[3]);
			//MPPT1_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}};	//reset MPPT message container
			
//TESTING	mavlink_msg_mppt2_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			//MAV_uart_send(buf,len);
			mavlink_msg_mppt2_data_send(MAVLINK_COMM_0,MPPT2_Message.data[0],MPPT2_Message.data[1],MPPT2_Message.data[2],MPPT2_Message.data[3]);
			//MPPT2_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}};	//reset MPPT message container
			
//TESTING	mavlink_msg_mppt3_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			//MAV_uart_send(buf,len);
			mavlink_msg_mppt3_data_send(MAVLINK_COMM_0,MPPT3_Message.data[0],MPPT3_Message.data[1],MPPT3_Message.data[2],MPPT3_Message.data[3]);
			//MPPT3_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}};	//reset MPPT message container
			
//TESTING	mavlink_msg_mppt4_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			//MAV_uart_send(buf,len);
			mavlink_msg_mppt4_data_send(MAVLINK_COMM_0,MPPT4_Message.data[0],MPPT4_Message.data[1],MPPT4_Message.data[2],MPPT4_Message.data[3]);
			//MPPT4_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}};	//reset MPPT message container

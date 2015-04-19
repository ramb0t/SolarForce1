/*
 * MAVLink_Messaging.c
 *
 * Created: 2015/03/29 11:47:11 PM
 *  Author: Matt
 */ 

#include "MAVLink_Messaging.h"

#define DEBUG	0

//------------ISR for the Timer0-------------------------//
ISR(INT0_vect){
	CAN_fillBuffer();

}

int main (void)
{
	/* -------port configuration----------------
	GPS Serial In Dig I/P 2 = PORTD2
	Telemetry Serial O/P 3 = PORTD3
	Telemetry Serial I/P 4 = PORTD4				*/
	
	UART_DDR |= _BV(TELEMETRY_UART_OUT);	//output
	UART_DDR &=~_BV(GPS_UART_DATA_IN);	//input
	UART_DDR &=~_BV(TELEMETRY_UART_IN);	//input
	
	//DDRB |= _BV(DDB5);
	
	LED_DIAG_DDR |= (1<<LED_DIAG_GRN)|(1<<LED_DIAG_ORG); //setup diagnostic LEDs
	
	CANINT_DDR |= (1<<CANINT_LED);		//CAN interrupt LED
			
	/*----------CAN PORT INPUTS-----------------
		Initialise SPI and CAN libraries
		Name	CANPin	ArduinoPin		Port
		------------------------------------
		CS/SS	PIN8	DigPin10		PB2
		MISO	PIN7	DigPin12		PB4
		MOSI	PIN6	DigPin11		PB3
		SCK		PIN5	DigPin13		PB5
		INT		PIN4	N/A					*/
		
		SPI_Init();
		
		if(CAN_Init(CAN_125KBPS_16MHZ) !=CAN_OK)
		{
			CAN_Init(CAN_125KBPS_16MHZ);
		};
		
	/*---------Timer Setup---------------------
		*Overflow based
		*1024 Prescalar						*/
	
	TCNT0 = 0x00;
	TCCR0A = 0x00;
	//TCCR0B = (1<<CS02)|(1<<CS00);
	//TIMSK0 = (1<<TOIE0);		//--enable later!
	
	
	/*---------UART Serial Init --------------------
		*uses UART.h library
		*interrupt-based					*/
		CAN_setupInt0();
		uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
				
		sei();	//interrupts ON
	
	//TODO: Get interrupt-based heartbeats and GPS data integrated with CAN
	
				mavlink_system.sysid = 100; // System ID, 1-255
				mavlink_system.compid = 200; // Component/Subsystem ID, 1-255
	
//---------------Operational Loop---------------------//
	_delay_ms(100);
	while(1) {
		//uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); --CAUSES BREAKAGE
		

	if (DEBUG)
	{
		//_delay_ms(500);
		LED_DIAG_PORT |= (1<<LED_DIAG_ORG);
		LED_DIAG_PORT &= ~(1<<LED_DIAG_GRN);
		//_delay_ms(500);
		LED_DIAG_PORT &= ~(1<<LED_DIAG_ORG);
		LED_DIAG_PORT |= (1<<LED_DIAG_GRN);
	}	
		
		//uart_putc('a');
		
		CAN_readData();
		MAV_msg_pack();
		GPS_readData();
		//uart_puts("Hi!");
		

		

	}
	return 0;

}
 
void GPS_readData()
{
		//---------------GPS Parse--------------------------------//
	/*eg4. for NMEA 0183 version 3.00 active the Mode indicator field is added
	$GPRMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,ddmmyy,x.x,a,m*hh
	Field #
	1    = UTC time of fix
	2    = Data status (A=Valid position, V=navigation receiver warning)
	3    = Latitude of fix
	4    = N or S of longitude
	5    = Longitude of fix
	6    = E or W of longitude
	7    = Speed over ground in knots
	8    = Track made good in degrees True
	9    = UTC date of fix
	10   = Magnetic variation degrees (Easterly var. subtracts from true course)
	11   = E or W of magnetic variation
	12   = Mode indicator, (A=Autonomous, D=Differential, E=Estimated, N=Data not valid)
	13   = Checksum
	*/		
		char buffer[10];
		//unsigned int z=0;
		//unsigned int lgth=0;
		uint8_t ctr = 0;
		uint8_t ctr2 = 0;
		uint8_t errctr = 0;
		char gpsdata;
		
		if(uart_available())
		{
			while(!(UCSR0A & (1<<RXC0)))
			{
							//uart_putc(uart_getc());
							gpsdata = uart_getc();
							//uart_putc(gpsdata);
							if(gpsdata =='$')
							{
								gpsdata = uart_getc();
									while (gpsdata!=',')
									{
										_delay_ms(20);
										gpsdata = uart_getc();
										GPRMC[ctr] = gpsdata;
										ctr++;
									}
									if (gpsdata==',')
									{
										//uart_puts(GPRMC);
										for (int i=0;i<ctr;i++)
										{
											//uart_putc(GPRMC[i]);
											
										}
											ctr=1;	
										//----------get the time part--------//
										gpsdata = uart_getc();
										time[0] = gpsdata;
										//for the time
										while (gpsdata!=',')
										{
											_delay_ms(20);
											gpsdata = uart_getc();
											time[ctr] = gpsdata;
											ctr++;
										}
										if (gpsdata==',')
										{
											//uart_puts(GPRMC);
											for (int i=0;i<ctr;i++)
											{
												//uart_putc(time[i]);
											}
											ctr=1;
										//----------get data status--------//
											gpsdata = uart_getc();
											GPRMC[0]= gpsdata;
											fix = GPRMC[0];
											while (gpsdata!=',')
											{
												_delay_ms(20);
												gpsdata = uart_getc();
												//fix = gpsdata;
											}
											if (gpsdata==',')
											{
													//uart_putc(fix);
											}
												ctr=1;
											//----------get the latitude--------//
											gpsdata = uart_getc();
											lat[0] = gpsdata;
											//for the time
											while (gpsdata!=',')
											{
												_delay_ms(20);
												gpsdata = uart_getc();
												lat[ctr] = gpsdata;
												ctr++;
											}
											if (gpsdata==',')
											{
												//uart_puts(GPRMC);
												for (int i=0;i<ctr;i++)
												{
													//uart_putc(lat[i]);
												}
												ctr=1;	
											}
										}
										
									}
									break;
							}
			}

										

								
							


	
	}//if UART available
}//GPS get
			
			
void GPSParse(char* GPRMC,char gpsdata)
{
	int ctr =1;
	gpsdata = uart_getc();
	GPRMC[0] = gpsdata;
	while (gpsdata!=',')
	{
		_delay_ms(20);
		gpsdata = uart_getc();
		GPRMC[ctr] = gpsdata;
		ctr++;
	}
	if (gpsdata==',')
	{
		//uart_puts(GPRMC);
		for (int i=0;i<ctr;i++)
		{
			uart_putc(GPRMC[i]);
		}
		ctr=1;
	}
}




void CAN_readData()
{
		//itoa(CAN_checkReceiveAvailable(), buff,10);
		//uart_puts("RXAvail:");
		//uart_puts(buff);
		//
		//itoa(CAN_checkError(),buff,10);
		//uart_puts("CheckErr:");
		//uart_puts(buff);
//		_delay_ms(100);
		

	//if (CAN_checkError()==CAN_CTRLERROR)
	//{
	//uart_puts("CAN Controller Error!");
	////TODO: Set flag for controller error in GUI
	//}else if (CAN_checkError()==CAN_OK)
	
	uart_flush();		//<-------may be important
	
		//	_delay_ms(20);
		
		char buff[10] ;
	
	if(CAN_checkReceiveAvailable()==CAN_MSGAVAIL)
		{
	//-------------------DEBUG CODE!-------------------------//
	if(DEBUG)
	{
			uart_puts("<<<<START OF MESSAGE>>>>\n");
			uart_puts("\nCAN DATA\n");
			
			itoa(CAN_checkReceiveAvailable(), buff,10);
/*TEST DISPLAY*/		uart_puts("RX:");
						uart_puts(buff);
						uart_puts(",");
			itoa(CAN_checkError(),buff,10);
/*TEST DISPLAY*/		uart_puts("Err:");
						uart_puts(buff);
						uart_puts(",");
			uart_puts(",");
			
}//-------------------END DEBUG CODE!-------------------------//
	
				//-----------------Pull MPPT data----------------//
				//CANBusInput.id = 0x711;
				//CANBusInput.rtr = 1;
				//CANBusInput.length = 0;

				// Send the request
				//CAN_sendMessage(&message);
				
				//-------------------Receive Data----------------//
			
			int rx_Result;
			rx_Result = CAN_readMessage(&Input_Message);			//read a byte of CAN data
			
			if (rx_Result == CAN_OK)							//if read correctly...
			{
				////buff[0] = "\0";
				//itoa(Input_Message.id,buff,10);					//read ASCII-converted byte into buffer
///*TEST DISPLAY*/uart_puts("\nCAN ID:");
				//uart_puts(buff);								//output bytestring to UART
				
				//-----------------------Switches for detecting CAN ID--------------------------//
				if (Input_Message.id ==MOTOR_DRIVER_CANID)		//Motor driver ID detected
				{
					uart_puts("\n");
					uart_puts("CAN from MD:");
					uart_puts(Input_Message.id);
					for (int i=0;i<4;i++)
					{
						itoa(Input_Message.data[i],buff,10);
						uart_puts(buff);
					}

				}
				
				if (Input_Message.id ==HALL_EFFECT_CANID)		//Hall effect data detected
				{
					uart_puts("\n");
					uart_puts("CAN from HE:");
					uart_puts(Input_Message.id);
					for (int i=0;i<4;i++)
					{
						itoa(Input_Message.data[i],buff,10);
						uart_puts(buff);
					}

				}
				
				if (Input_Message.id ==BMS_CANID)				//BMS data detected
				{
					uart_puts("\n");
					uart_puts("CAN from BMS:");
					uart_puts(Input_Message.id);
					for (int i=0;i<16;i++)						//16 data fields
					{
						itoa(Input_Message.data[i],buff,10);
						uart_puts(buff);
					}

				}
				
				if (Input_Message.id ==ACCELO_GYRO_CANID)				//Gyro/MPU6050 data detected
				{
					uart_puts("\n");
					uart_puts("CAN from ACGY:");
					uart_puts(Input_Message.id);
					for (int i=0;i<2;i++)						//2 data fields
					{
						itoa(Input_Message.data[i],buff,10);
						uart_puts(buff);
					}

				}
				
				if (Input_Message.id ==MPPT1_CANID)				//BMS data detected
				{
					uart_puts("\n");
					uart_puts("CAN from MPPT1:");
					uart_puts(Input_Message.id);
					for (int i=0;i<4;i++)						//4 data fields
					{
						itoa(Input_Message.data[i],buff,10);
						uart_puts(buff);
					}

				}//endif MPPT1
				
				if (Input_Message.id ==MPPT2_CANID)				//BMS data detected
				{
					uart_puts("\n");
					uart_puts("CAN from MPPT2:");
					uart_puts(Input_Message.id);
					for (int i=0;i<4;i++)						//4 data fields
					{
						itoa(Input_Message.data[i],buff,10);
						uart_puts(buff);
					}

				}//endif MPPT1
				
				if (Input_Message.id ==MPPT3_CANID)				//BMS data detected
				{
					uart_puts("\n");
					uart_puts("CAN from MPPT3:");
					uart_puts(Input_Message.id);
					for (int i=0;i<4;i++)						//4 data fields
					{
						itoa(Input_Message.data[i],buff,10);
						uart_puts(buff);
					}

				}//endif MPPT1
								
				if (Input_Message.id ==MPPT4_CANID)				//BMS data detected
				{
					uart_puts("\n");
					uart_puts("CAN from MPPT4:");
					uart_puts(Input_Message.id);
					for (int i=0;i<4;i++)						//4 data fields
					{
						itoa(Input_Message.data[i],buff,10);
						uart_puts(buff);
					}

				}//endif MPPT1
				
			
				
			
	if (DEBUG)
	{
				uart_puts(",");
				itoa(Input_Message.length,buff,10);
				/*TEST DISPLAY*/uart_puts("\nCAN Data Length:");
				uart_puts(",");
				if(Input_Message.length==0)						//checks length
				{
					/*TEST DISPLAY*/uart_puts("No CAN Data bits\n");			//Prints if no data bits present
					}else{
								
					uart_puts(buff);
					for(int j = 0; j< Input_Message.length; j++)	//print byte for each data element
					{
						/*TEST DISPLAY*/		uart_puts("\nCAN Data ");
						itoa(j,buff,10);
						uart_puts(buff);
						/*TEST DISPLAY*/			uart_puts(": ");
									
						itoa(Input_Message.data[j],buff,10);
									
						uart_puts(buff);
						uart_puts(",");
					}
				}//endif input length==0
							
				itoa(Input_Message.rtr,buff,2);
				/*TEST DISPLAY*/	uart_puts("\nIs this an RTR?: ");
				if(Input_Message.rtr==1)
				{
					uart_puts("Y,");
				}else uart_puts("N\n");
							
	}
					



				
					
					
			}//endif CAN_OK
/*TEST DISPLAY*/ uart_puts("\n-------\n CAN Done.\n");
		}//endif CAN_MSGAVAIL
		
}//end CAN_readData



void MAV_msg_pack()
{
				////---------------MAVLink Setup---------------------------//
	///*MAVLINK asks to set all system statuses as integers. For human readibility ENUMS are used in the appropriate headers
	//these enums convert text for states to integers sent & interpreted. 3 phases to a message:
  //--define the enum types you'll need and use friendly names e.g. value_name = MAV_ENUM_VALUE_NAME
  //--use a send / encode function from the relevant header to send HEARTBEAT to get QGC/APM working
  //--then have a function (see solarCar.h and the entire message_definitions folder for types to send
  //--pass the values or enum friendly names to the functions
  //--this ensures the message goes to MAVLink frame
  //--connect to QGC and observe output! */


			uart_puts(" ");
			//---------------MAVLink Data---------------------------//
			// Initialize the required buffers
			// Set correct buffer lengths

			mavlink_message_t msg;
			uint8_t buf[MAVLINK_MAX_PACKET_LEN];
			uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
			
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
			..........................................................................
				Parameters	 Value	Detail									Range/Type
			...........................................................................				
								2 = temperature of motor controller			1,2,3,4
																			1 = below 85; 
																			2 = 85-95; 
																			3 = 95-105; 
																			4 = over 105
								3 = speed from motor driver (RPM)			0-255km/h
			Assume CAN data 2 = motor controller temp
							3 =   data 1 = speed								*/
			
			//mavlink_msg_motor_driver_pack(100,200,&msg,CANBusInput.data[0],CANBusInput.data[1]);
			//MAV_uart_send(buf,len);
			
			mavlink_msg_motor_driver_send(MAVLINK_COMM_0, Input_Message.data[0],Input_Message.data[1]);
			
			/*-----------------------------------------------------------------------
			NAME: Hall Effect Sensor Data
			DESCRIPTION: Speed from the Hall Effect Sensors and error flags	
			.........................................................................
			Parameters		 Value	Detail									Range/Type
			...........................................................................
				Parameters		2 = speed from hall effect					0-255km/h
								3 = uint8_t magnet_back missing?			0=no 1=yes
								4 = uint8_t magnet_front missing?			0=no 1=yes
			//TESTING		CAN 2 = speed to send							*/
			
			//uart_flush();
			mavlink_msg_hall_effect_send(MAVLINK_COMM_0, Input_Message.data[2],0,0);
			
			//uart_puts("RX");
			//uart_puts(MAV_Rx_buff);
			/*-----------------------------------------------------------------------
			NAME: BMS Data
			DESCRIPTION: All data originating from the BMS, including error flags
			.........................................................................
				Parameters	 Value	Detail									Range/Type
			...........................................................................
								2 = uint8_t fault condition?				0=no 1=yes
								3 = uint16_t source current					0-65535mA
								4 = uint16_t load_current					0-65535mA
								5 = char bat_fan_status						t=OK f=FAULT
								6 = uint8_t LLIM_state						1=flag active 0=flag not active
								7 = uint8_t HLIM_state						1=flag active 0=flag not active
								8 = uint8_t state_of_chg (percentage)		0-100%
								9= uint16_t pack_voltage					0-65535V
								10 = const uint16_t *cell_voltages [low,avg,high]	0-65535V per element
								11 = const uint16_t *cell_temps [low,avg,high]		0-65535C per element
								12 = uint8_t system_status							MAVLINK_ENUM
								
			*/
			//FOR TESTING ONLY. REPLACE VALUES WITH CAN ID POINTERS AS NEEDED!
			uint16_t volt[] = {4,5,8};
			uint16_t temp[] = {25,55,70};
			uint16_t *cell_voltage = volt;	
			uint16_t *cell_temp = temp;
			
			//uart_flush();
			mavlink_msg_bms_data_send(MAVLINK_COMM_0,0,1420,1550,'t',0,0,75,128,cell_voltage,cell_temp,MAV_STATE_ACTIVE);

			/*-----------------------------------------------------------------------
			NAME: Accelerometer/Gyroscope Data
			DESCRIPTION: Yaw, Pitch, Roll and Acceleration data from MPU6050
			.........................................................................
			Parameters		Value	Detail									Range/Type
			...........................................................................
								4 = int8_t acceleration (m.s^-2)			-127 to 127 m.s^-2		
								5 = int8_t incline (degrees)				-127 to 127 (0-100 @ 10 counts per degree)
			//TESTING																	*/
			
			mavlink_msg_accelo_gyro_send(MAVLINK_COMM_0, /*CANBusInput.data[0]*/2,11);
			
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
			//TESTING
																					*/
//TESTING	mavlink_msg_gps_pack(100,200,&msg,latitude,longitude,time,date,lock_error);
			//MAV_uart_send(buf,len);
			char * lockerr = "";
			if (fix == "V")
			{
				lockerr = "OK";
			}else {lockerr = "INVALID";}
			mavlink_msg_gps_send(MAVLINK_COMM_0,lat,longitude,time,date,lockerr);
			
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
			mavlink_msg_mppt1_data_send(MAVLINK_COMM_0,2542,1011,0,0);
			
//TESTING	mavlink_msg_mppt2_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			//MAV_uart_send(buf,len);
			mavlink_msg_mppt2_data_send(MAVLINK_COMM_0,2500,1000,0,0);
			
//TESTING	mavlink_msg_mppt3_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			//MAV_uart_send(buf,len);
			mavlink_msg_mppt3_data_send(MAVLINK_COMM_0,2591,968,0,1);
			
//TESTING	mavlink_msg_mppt4_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			//MAV_uart_send(buf,len);
			mavlink_msg_mppt4_data_send(MAVLINK_COMM_0,2411,1211,1,0);
			
			/*-----------------------------------------------------------------------
			NAME: Heartbeat
			DESCRIPTION: MAVLink heartbeat required to confirm a connection is active
			.........................................................................
			Parameters(x4)		Value	Detail								Range/Type
			...........................................................................
			Flags are fixed each time, standard to the MAVLink library. Not edited / written to.
			//TESTING																		*/			
			
			//uart_flush();
			//uart_puts("\n---------MAVLink Heartbeat---------\n");
			
			mavlink_msg_heartbeat_send(MAVLINK_COMM_0,system_type,autopilot_type,base_mode,custom_mode,system_status);

			//uart_puts("\n<<<<END OF MESSAGE>>>>\n");
			
			//-----FOR TESTING ONLY, LOOPBACK RECEIVE FUNCTION
			//uart_puts("\n<<<<RX MESSAGE>>>>\n");
			 
			//mavlink_message_t msg2 PROGMEM;
			//int chan = 0;
			//mavlink_status_t* mav_status;
			//
			 //while(uart_available()>0)
			 //{
				//uint8_t byte = uart_getc();
				//while( !(UCSR0A & (1<<UDRE0)) )
				//{
					//
						//byte = uart_getc() ;
						//if (mavlink_parse_char(chan, byte, &msg2,mav_status))
						//{
							//uart_puts("ID: ");
							//uart_putc(msg2.msgid);
							//uart_puts("\nSeq:");
							//uart_putc(msg2.seq);
							//uart_puts("\nCompo: " );
							//uart_putc(msg2.compid);
							//uart_puts("\nsys: ");
							//uart_putc(msg.sysid);
						//}
					//
				//}
			//}
				
			
			//mavlink_motor_driver_t* MotorDriver;
			//mavlink_message_type_t* msgRx;
			//
			//msgRx = MAV_Rx_buff;
			//mavlink_msg_motor_driver_decode(&msgRx, MotorDriver);
			//
			//itoa(MotorDriver->controller_temp,buf,10);					//read ASCII-converted byte into buffer
			//uart_puts("\nTemperature:");
			//uart_puts(buf);
			//
			//itoa(MotorDriver->speed,buf,10);
			//uart_puts("\nSpeed:");
			//uart_puts(buf);
	
}




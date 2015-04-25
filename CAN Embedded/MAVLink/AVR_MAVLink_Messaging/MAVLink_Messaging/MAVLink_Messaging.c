/*
 * MAVLink_Messaging.c
 *
 * Created: 2015/03/29 11:47:11 PM
 *  Author: Matt
 */ 

#include "MAVLink_Messaging.h"
#include "GlobalDefs.h"

#define DEBUG	0


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
	
		Timer0_init();
	
		CAN_setupInt0();
		
	
	/*---------UART Serial Init --------------------
		*uses UART.h library
		*interrupt-based					*/
	
		uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
		
		sei();	//interrupts ON
	
	//TODO: Get interrupt-based heartbeats and GPS data integrated with CAN
	
				mavlink_system.sysid = 100; // System ID, 1-255
				mavlink_system.compid = 200; // Component/Subsystem ID, 1-255
	
	/*---------GPS Pointer Init --------------------
		Sets the Parsing pointer to the start of the GPS string					*/
	
	p_start = gps_string;
	volatile GlobalVars CANData;
//---------------Operational Loop---------------------//
	
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
	
	//----------------new code---------------//

	//this goes true every 500ms
	

	if (updateMAV_flag == TRUE)
	{
		MAV_HB_send();					//send MAVLink heartbeat	
		MAV_msg_pack();					//selectively send MAVLink packets
		updateMAV_flag = FALSE;
	}
	
	
	
	if (updateGPS_flag == TRUE)
	{
		GPS_readData();					//store GPS data to global fields
		updateGPS_flag = FALSE;			//GPS has been 
	}


	
	//----------------/new code-------------//
	
		
		
	}
	return 0;

}


void GPS_readData()
{
	
	uart_flush();
	for (int i=0;i<62;i++)
	{
		gps_string[i]='0';
	}
			LED_DIAG_PORT &= ~(1<<LED_DIAG_ORG);
			LED_DIAG_PORT |= (1<<LED_DIAG_GRN);
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
	do	{
		gpsdata = uart_getc();
		flag++;
		if (flag > 10000)
		{
			flag=0;
			break;
		}
	}							//get a GPS char
	while (gpsdata !='$');

		//uart_putc(uart_getc());
		if (gpsdata == '$')									//if it's $ = start line
		{
			gps_string[0]=gpsdata;							//store this into GPS string
			//uart_putc(gpsdata);
			do
			{	
				if (uart_available())
				{
					gps_string[gpsctr+1] = uart_getc();		//as long as EOL symbol * not reached
					//uart_putc(gps_string[ctr+1]);
					gpsctr++;									//populate GPRMC NMEA sentence
				}
		
			}while (gps_string[gpsctr] !='*');
			gpslen = gpsctr;									
			gpsctr=0;
			
			if (gps_string[5]=='C')							//Only GPRMC sentence has a 'C' so isolate this
			{
				ParseGPS();
				uart_puts(gps_string);						//output it!
			}
	
	
			//for (int i=0;i<gpslen;i++)
			//{
			//uart_putc(gps_string[i]);
			//}
	
	
		}

	gps_needs_sending = TRUE;
}//GPS get



void ParseGPS () 
{	
			int i=0;
			p_end = strchr(p_start, ',');
			if (p_end) {
				strncpy(parts[i], p_start, p_end-p_start);
				parts[i][p_end-p_start] = 0;
				i++;
				p_start = p_end + 1;
			}
			else {
				// sopy the last bit - might as well copy 20
				strncpy(parts[i], p_start, 20);
				//break;
			}
			if(DEBUG){
			uart_puts("\n");
				for (int i=0;i<13;i++)
				{
					uart_puts("\nPART ");
					uart_putc(i);
					uart_puts(": ");
					uart_puts(parts[i]);
					uart_puts("\n");
				}
			}

}


void MAV_msg_pack()
{
	uart_flush();
	LED_DIAG_PORT &= ~(1<<LED_DIAG_ORG);
	////---------------MAVLink Setup---------------------------//
	///*MAVLINK asks to set all system statuses as integers. For human readibility ENUMS are used in the appropriate headers
	//these enums convert text for states to integers sent & interpreted. 3 phases to a message:
  //--define the enum types you'll need and use friendly names e.g. value_name = MAV_ENUM_VALUE_NAME
  //--use a send / encode function from the relevant header to send HEARTBEAT to get QGC/APM working
  //--then have a function (see solarCar.h and the entire message_definitions folder for types to send
  //--pass the values or enum friendly names to the functions
  //--this ensures the message goes to MAVLink frame
  //--connect to QGC and observe output! */


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
			/**/
			
			if (speedMDUpdated==1 || speedHEUpdated==1)
			{
				
				mavlink_msg_speed_halleffect_send(MAVLINK_COMM_0,CANData.avgSpeed,CANData.hesSPeed,
				CANData.hesRPM,CANData.motorSpeed,CANData.motorRPM,CANData.statusFlags);
				speedMDUpdated = 0; speedHEUpdated = 0;
			}
			
			
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
			//uart_flush();
			if (bms1Updated==1)
			{
			mavlink_msg_bms_data_send(MAVLINK_COMM_0,CANData.BMSData_warnings,CANData.maxVoltage,CANData.maxVoltageID,
			CANData.minVoltage,CANData.minVoltageID,CANData.packVoltage,CANData.current,CANData.chargeLimit,
			CANData.dischargeLimit,CANData.batteryEnergyIn,CANData.batteryEnergyOut,CANData.SOC,CANData.DOD,
			CANData.capacity,CANData.SOH,CANData.minTempID,CANData.minTemperature,CANData.temperature,
			CANData.maxTemperature,CANData.maxTempID,CANData.packResistance,CANData.minRes,CANData.minResID,
			CANData.maxRes,CANData.maxResID,MAV_STATE_ACTIVE);
			
			bms1Updated=0;
			}
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
			//char *latitude = parts[3];
			//char *longitude = parts[4];
			//char *time = parts[1];
			//char *date = parts[9];
			//char lock_flag = parts[2];
			//char *lock_error = lock_error[7];
			//
			//if (lock_flag == 'A')
			//{
				//lock_error = "OK";
			//}else lock_error = "INVALID";
			//
			//if (gps_needs_sending==TRUE)
			//{
				//mavlink_msg_gps_send(MAVLINK_COMM_0,latitude,longitude,time,date,lock_error);
				//gps_needs_sending=FALSE;
			//}
			//
			
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
			//if (mppt1Updated==1)
			//{
				//mavlink_msg_mppt1_data_send(MAVLINK_COMM_0,MPPT1_Message.data[0],MPPT1_Message.data[1],MPPT1_Message.data[2],MPPT1_Message.data[3]);
				////MPPT1_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}};	//reset MPPT message container
				//mppt1Updated=0;
			//}
//
			//
////TESTING	mavlink_msg_mppt2_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			////MAV_uart_send(buf,len);
			//if (mppt2Updated==1)
			//{
			//mavlink_msg_mppt2_data_send(MAVLINK_COMM_0,MPPT2_Message.data[0],MPPT2_Message.data[1],MPPT2_Message.data[2],MPPT2_Message.data[3]);
			////MPPT2_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}};	//reset MPPT message container
			//mppt2Updated=0;
			//}
////TESTING	mavlink_msg_mppt3_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			////MAV_uart_send(buf,len);
			//if (mppt3Updated==1)
			//{
			//mavlink_msg_mppt3_data_send(MAVLINK_COMM_0,MPPT3_Message.data[0],MPPT3_Message.data[1],MPPT3_Message.data[2],MPPT3_Message.data[3]);
			////MPPT3_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}};	//reset MPPT message container
			//mppt3Updated=0;
			//}
////TESTING	mavlink_msg_mppt4_data_pack(100,200,&msg,voltage_in,current_in,overtemp,undervolt);
			////MAV_uart_send(buf,len);
			//if (mppt4Updated==1)
			//{
			//mavlink_msg_mppt4_data_send(MAVLINK_COMM_0,MPPT4_Message.data[0],MPPT4_Message.data[1],MPPT4_Message.data[2],MPPT4_Message.data[3]);
			////MPPT4_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}};	//reset MPPT message container
			//mppt4Updated=0;
			//}
			//
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
			
			//mavlink_msg_heartbeat_send(MAVLINK_COMM_0,system_type,autopilot_type,base_mode,custom_mode,system_status);

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
			
					LED_DIAG_PORT &= ~(1<<LED_DIAG_ORG);
		LED_DIAG_PORT &= ~(1<<LED_DIAG_GRN);
	
			}
			
void MAV_HB_send()
{
		//------------MAVLink Function Prototypes------------------------//

		uint8_t system_type = MAV_TYPE_GROUND_ROVER;
		uint8_t autopilot_type = MAV_AUTOPILOT_UDB;
		uint8_t base_mode = MAV_MODE_FLAG_AUTO_ENABLED;
		uint8_t custom_mode = MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
		uint8_t system_status = MAV_STATE_ACTIVE;
	mavlink_msg_heartbeat_send(MAVLINK_COMM_0,system_type,autopilot_type,base_mode,custom_mode,system_status);
}

					



/*
 * MAVLink_Messaging.c
 *
 * Created: 2015/03/29 11:47:11 PM
 *  Author: Matt
 */ 

#include "MAVLink_Messaging.h"

#define DEBUG	0

//------------ISR for the INT0-------------------------//
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
	
		CAN_setupInt0();
	
	/*---------UART Serial Init --------------------
		*uses UART.h library
		*interrupt-based					*/
	
		uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
				
		sei();	//interrupts ON
	
	//TODO: Get interrupt-based heartbeats and GPS data integrated with CAN
	
				mavlink_system.sysid = 100; // System ID, 1-255
				mavlink_system.compid = 200; // Component/Subsystem ID, 1-255
	
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

		
		//CAN_readData();

		//MAV_msg_pack();
		
		
		
		
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
	
	
	
	//for (int i=0;i<strlen(fmt);i++)
	//{
		//uart_putc(fmt[i]);
	//}

}//GPS get



//void ParseGPS (char c) {
	//if (c == '$') { state = 0; temp = 0; }
	//char mode = fmt[state++];
	//// If received character matches format string, or format is '?' - return
	//if ((mode == c) || (mode == '?')) return;
	//// d=decimal digit
	//char d = c - '0';
	//if (mode == 'd') temp = temp*10 + d;
	//// e=long decimal digit
	//else if (mode == 'e') ltmp = ltmp*10 + d;
	//// a=angular measure
	//else if (mode == 'a') ltmp = ltmp*6 + d;
	//// t=Time - hhmm
	//else if (mode == 't') { Time = temp*10 + d; temp = 0; }
	//// m=Millisecs
	//else if (mode == 'm') { Msecs = temp*10 + d; ltmp=0; }
	//// l=Latitude - in minutes*1000
	//else if (mode == 'l') { if (c == 'N') Lat = ltmp; else Lat = -ltmp; ltmp = 0; }
	//// o=Longitude - in minutes*1000
	//else if (mode == 'o') { if (c == 'E') Long = ltmp; else Long = -ltmp; temp = 0; }
	//// j/k=Speed - in knots*100
	//else if (mode == 'j') { if (c != '.') { temp = temp*10 + d; state--; } }
	//else if (mode == 'k') { Knots = temp*10 + d; temp = 0; }
	//// c=Course (Track) - in degrees*100
	//else if (mode == 'c') { Course = temp*10 + d; temp = 0; }
	//// y=Date - ddmm
	//else if (mode == 'y') { Date = temp*10 + d ; Fix = 1; }
	//else state = 0;
//}

void CAN_readData()
{
	CANMessage Input_Message;			//Generic/temp CAN input msg
	//CANMessage Input_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}}; ;
	//zCANMessage Speed_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}}; ;	

	//	uart_flush();
		
		//	_delay_ms(20);
		
		char buff[10] ;
		
	cli();				//Interrupts off
	
	if (~(PINB & (1<<PINB0)))	//if interrupt not triggered fill msg buffer
	{
		CAN_fillBuffer();
	}
	
	sei();				//Interrupts on again
	
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
				//Input_Message.id = 0x771;
				//Input_Message.rtr = 1;
				//Input_Message.length = 0;
//
				 ////Send the request
				//CAN_sendMessage(&Input_Message);
				
				//-------------------Receive Data----------------//
			
			int rx_Result;
			rx_Result = CAN_getMessage_Buffer(&Input_Message);			//read a byte of CAN data
			
			if (rx_Result == CAN_OK)							//if read correctly...
			{
				////buff[0] = "\0";
				//itoa(Input_Message.id,buff,10);					//read ASCII-converted byte into buffer
///*TEST DISPLAY*/uart_puts("\nCAN ID:");
				//uart_puts(buff);								//output bytestring to UART
				
			while(CAN_checkReceiveAvailable()==CAN_MSGAVAIL)
			{	
				if (canmsgctr > 15)
				{
					canmsgctr = 0;
					break;
				}
				canmsgctr++;
				if (CAN_getMessage_Buffer(&Input_Message) == CAN_OK)
				{
					//-----------------------Switches for detecting CAN ID--------------------------//
				
				switch (Input_Message.id)
				{
					/*Speed	byte 1*/
				case 	MOTOR_DRIVER_CANID:
						uart_puts("\n");
						uart_puts("CAN from MD:");
						uart_puts(Input_Message.id);				//Human readable data on UART
						uart_puts(":");
						for (int i=0;i<4;i++)
						{
							uart_puts(":");
							itoa(Input_Message.data[i],buff,10);	//convert to ascii form
							Speed_Message.data[i] = Input_Message.data[i]; //store into CAN object for speed
							uart_puts(buff);
						}
					
					
						uart_puts("\n");
						uart_puts("CAN from HE:");
						uart_puts(Input_Message.id);
						for (int i=4;i<8;i++)
						{
						itoa(Input_Message.data[i],buff,10);
						Speed_Message.data[i] = Input_Message.data[i];
						uart_puts(buff);
						}
					break;
					
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
					uart_puts("\n");
					uart_puts("CAN from BMS2:");					//Human readable data on UART
					uart_puts(Input_Message.id);
					
					itoa(Input_Message.data[3],buff,10);		//fault flags
					BMS_Message.data[0] = Input_Message.data[3];
					uart_puts(buff);
					
					//for (int i=0;i<16;i++)						//16 data fields
					//{
						//itoa(Input_Message.data[i],buff,10);
						//BMS_Message.data[i] = Input_Message.data[i]; //store into CAN object for BMS
						//uart_puts(buff);
					//}
					break;
					
				case	BMS_3_CANID:
					uart_puts("\n");
					uart_puts("CAN from BMS3:");					//Human readable data on UART
					uart_puts(Input_Message.id);
					
					itoa(Input_Message.data[0],buff,10);		//low pack voltage
					BMS_Message.data[5] = (Input_Message.data[2]<<8)|(Input_Message.data[3]);
					uart_puts(buff);
					
					itoa(Input_Message.data[0],buff,10);		// avg pack voltages
					BMS_Message.data[6] = (Input_Message.data[0]<<8)|(Input_Message.data[1]);
					uart_puts(buff);
					
					itoa(Input_Message.data[0],buff,10);		//high pack voltages
					BMS_Message.data[7] = (Input_Message.data[4]<<8)|(Input_Message.data[5]);
					
					uart_puts(buff);
					break;
				
				case	BMS_4_CANID:
					uart_puts("\n");
					uart_puts("CAN from BMS4:");					//Human readable data on UART
					uart_puts(Input_Message.id);
					
					itoa(Input_Message.data[0],buff,10);		//pack current
					itoa(Input_Message.data[1],buff,10);
					BMS_Message.data[2] = (Input_Message.data[0]<<8)|(Input_Message.data[1]);
					uart_puts(buff);
					break;
				

				case	BMS_6_CANID:
					uart_puts("\n");
					uart_puts("CAN from BMS6:");					//Human readable data on UART
					uart_puts(Input_Message.id);
				
					itoa(Input_Message.data[0],buff,10);		//SOC
					BMS_Message.data[3] = Input_Message.data[0];
					uart_puts(buff);
				break;
				
				case	BMS_7_CANID:
					uart_puts("\n");
					uart_puts("CAN from BMS7:");					//Human readable data on UART
					uart_puts(Input_Message.id);
				
					itoa(Input_Message.data[2],buff,10);			//Min temps
					uart_puts(buff);
					itoa(Input_Message.data[3],buff,10);			//Min temps
					uart_puts(buff);
					BMS_Message.data[8] = (Input_Message.data[2]<<8)|(Input_Message.data[3]);
					
				
					itoa(Input_Message.data[0],buff,10);			//Avg temps
					BMS_Message.data[9] = Input_Message.data[0];
					uart_puts(buff);
				
					itoa(Input_Message.data[4],buff,10);			//Max temps
					BMS_Message.data[10] = (Input_Message.data[4]<<8)|(Input_Message.data[5]);
					uart_puts(buff);
				break;
				
				case	ACCELO_GYRO_CANID:
					uart_puts("\n");
					uart_puts("CAN from ACGY:");
					uart_puts(Input_Message.id);
					for (int i=0;i<2;i++)						//2 data fields
					{
						Gyro_Accel_Message.data[i] = Input_Message.data[i];
						uart_puts(buff);
					}

				break;
				
				case	MPPT1_CANID:
					uart_puts("\n");
					uart_puts("CAN from MPPT1:");
					uart_puts(Input_Message.id);
					for (int i=0;i<4;i++)						//4 data fields
					{
						itoa(Input_Message.data[i],buff,10);
						MPPT1_Message.data[i] = Input_Message.data[i];
						uart_puts(buff);
					}
				break;
				
				case	MPPT2_CANID:
				uart_puts("\n");
				uart_puts("CAN from MPPT1:");
				uart_puts(Input_Message.id);
				for (int i=0;i<4;i++)						//4 data fields
				{
					itoa(Input_Message.data[i],buff,10);
					MPPT2_Message.data[i] = Input_Message.data[i];
					uart_puts(buff);
				}
				break;
				
				case	MPPT3_CANID:
				uart_puts("\n");
				uart_puts("CAN from MPPT1:");
				uart_puts(Input_Message.id);
				for (int i=0;i<4;i++)						//4 data fields
				{
					itoa(Input_Message.data[i],buff,10);
					MPPT3_Message.data[i] = Input_Message.data[i];
					uart_puts(buff);
				}
				break;
				
				case	MPPT4_CANID:
				uart_puts("\n");
				uart_puts("CAN from MPPT1:");
				uart_puts(Input_Message.id);
				for (int i=0;i<4;i++)						//4 data fields
				{
					itoa(Input_Message.data[i],buff,10);
					MPPT4_Message.data[i] = Input_Message.data[i];
					uart_puts(buff);
				}
				break;
				
				
				}

				//------------OLD METHOD---------------//
				
//void CAN_readData()
//{
	////CANMessage Input_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}}; ;
	////zCANMessage Speed_Message = (CANMessage){.id=0, .rtr=0, .length=0, .data={}}; ;	
		////itoa(CAN_checkReceiveAvailable(), buff,10);
		////uart_puts("RXAvail:");
		////uart_puts(buff);
		////
		////itoa(CAN_checkError(),buff,10);
		////uart_puts("CheckErr:");
		////uart_puts(buff);
////		_delay_ms(100);
		//
//
	////if (CAN_checkError()==CAN_CTRLERROR)
	////{
	////uart_puts("CAN Controller Error!");
	//////TODO: Set flag for controller error in GUI
	////}else if (CAN_checkError()==CAN_OK)
	//
		//uart_flush();
		////	_delay_ms(20);
		//
		//char buff[10] ;
	//
	//if(CAN_checkReceiveAvailable()==CAN_MSGAVAIL)
		//{
	////-------------------DEBUG CODE!-------------------------//
	//if(DEBUG)
	//{
			//uart_puts("<<<<START OF MESSAGE>>>>\n");
			//uart_puts("\nCAN DATA\n");
			//
			//itoa(CAN_checkReceiveAvailable(), buff,10);
///*TEST DISPLAY*/		uart_puts("RX:");
						//uart_puts(buff);
						//uart_puts(",");
			//itoa(CAN_checkError(),buff,10);
///*TEST DISPLAY*/		uart_puts("Err:");
						//uart_puts(buff);
						//uart_puts(",");
			//uart_puts(",");
			//
//}//-------------------END DEBUG CODE!-------------------------//
	//
				////-----------------Pull MPPT data----------------//
				////Input_Message.id = 0x771;
				////Input_Message.rtr = 1;
				////Input_Message.length = 0;
////
				 //////Send the request
				////CAN_sendMessage(&Input_Message);
				//
				////-------------------Receive Data----------------//
			//
			//int rx_Result;
			//rx_Result = CAN_readMessage(&Input_Message);			//read a byte of CAN data
			//
			//if (rx_Result == CAN_OK)							//if read correctly...
			//{
				//////buff[0] = "\0";
				////itoa(Input_Message.id,buff,10);					//read ASCII-converted byte into buffer
/////*TEST DISPLAY*/uart_puts("\nCAN ID:");
				////uart_puts(buff);								//output bytestring to UART
				//
				////-----------------------Switches for detecting CAN ID--------------------------//
				//if (Input_Message.id ==MOTOR_DRIVER_CANID)		//Motor driver ID detected
				//{
					//uart_puts("\n");
					//uart_puts("CAN from MD:");
					//uart_puts(Input_Message.id);				//Human readable data on UART
					//uart_puts(":");
					//for (int i=0;i<8;i++)
					//{
						//uart_puts(":");
						//itoa(Input_Message.data[i],buff,10);	//convert to ascii form
						//Speed_Message.data[i] = Input_Message.data[i]; //store into CAN object for speed
						//uart_puts(buff);
					//}
//
				//}
				//
				////if (Input_Message.id ==HALL_EFFECT_CANID)		//Hall effect data detected
				////{
					////uart_puts("\n");
					////uart_puts("CAN from HE:");
					////uart_puts(Input_Message.id);
					////for (int i=4;i<8;i++)
					////{
						////itoa(Input_Message.data[i],buff,10);
						////uart_puts(buff);
					////}
////
				////}
				//
				///*NOTE: BMS Data across different messages, we want:
				//Base CANID =	BMS[0] = 0x0620
								//BMS[1] = 0x0621
								//BMS[2] = 0x0622
								//BMS[3] = 0x0623
								//BMS[4] = 0x0624
								//BMS[5] = 0x0625
								//BMS[6] = 0x0626
								//BMS[7] = 0x0627
								//BMS[8] = 0x0628
						//.........................................................................
						//Parameters	 Value	Detail							CANID byte			Range/Type
						//...........................................................................
						//2 = uint8_t fault condition?						BMS[2].data[3]		0=no 1=yes
						//3 = uint16_t source current							BMS[5].data[0]		0-65535mA
						//4 = uint16_t net_current (load)						BMS[4].data[0]		0-65535mA
						//5 = char bat_fan_status													t=OK f=FAULT
						//6 = uint8_t LLIM_state													1=flag active 0=flag not active
						//7 = uint8_t HLIM_state													1=flag active 0=flag not active
						//8 = uint8_t state_of_chg (percentage)				BMS[6].data[0]		0-100%
						//9 = uint16_t pack_voltage							BMS[3].data[0]		0-65535V
						//10 = const uint16_t *cell_voltages [low,avg,high]	BMS[3].data[1,3]	0-65535V per element
						//11 = const uint16_t *cell_temps [low,avg,high]		BMS[7].data[2,4]	0-65535C per element
						//12 = uint8_t system_status												MAVLINK_ENUM
				//
				//*/
				//if (Input_Message.id ==BMS_1_CANID)				//BMS data detected
				//{
					//uart_puts("\n");
					//uart_puts("CAN from BMS:");					//Human readable data on UART
					//uart_puts(Input_Message.id);
					//for (int i=0;i<16;i++)						//16 data fields
					//{
						//itoa(Input_Message.data[i],buff,10);
						//BMS_Message.data[i] = Input_Message.data[i]; //store into CAN object for BMS
						//uart_puts(buff);
					//}
//
				//}
				//
				//if (Input_Message.id ==ACCELO_GYRO_CANID)				//Gyro/MPU6050 data detected
				//{
					//uart_puts("\n");
					//uart_puts("CAN from ACGY:");
					//uart_puts(Input_Message.id);
					//for (int i=0;i<2;i++)						//2 data fields
					//{
						//Gyro_Accel_Message.data[i] = Input_Message.data[i];
						//uart_puts(buff);
					//}
//
				//}
				//
				//if (Input_Message.id ==MPPT1_CANID)				//MPPT1 data detected
				//{
					//uart_puts("\n");
					//uart_puts("CAN from MPPT1:");
					//uart_puts(Input_Message.id);
					//for (int i=0;i<4;i++)						//4 data fields
					//{
						//itoa(Input_Message.data[i],buff,10);
						//MPPT_Message.data[i] = Input_Message.data[i];
						//uart_puts(buff);
					//}
//
				//}//endif MPPT1
				//
				//if (Input_Message.id ==MPPT2_CANID)				//MPPT2 data detected
				//{
					//uart_puts("\n");
					//uart_puts("CAN from MPPT2:");
					//uart_puts(Input_Message.id);
					//for (int i=0;i<4;i++)						//4 data fields
					//{
						//itoa(Input_Message.data[i],buff,10);
						//MPPT_Message.data[i] = Input_Message.data[i];
						//uart_puts(buff);
					//}
//
				//}//endif MPPT1
				//
				//if (Input_Message.id ==MPPT3_CANID)				//MPPT3 data detected
				//{
					//uart_puts("\n");
					//uart_puts("CAN from MPPT3:");
					//uart_puts(Input_Message.id);
					//for (int i=0;i<4;i++)						//4 data fields
					//{
						//itoa(Input_Message.data[i],buff,10);
						//MPPT_Message.data[i] = Input_Message.data[i];
						//uart_puts(buff);
					//}
//
				//}//endif MPPT1
								//
				//if (Input_Message.id ==MPPT4_CANID)				//MPPT4 data detected
				//{
					//uart_puts("\n");
					//uart_puts("CAN from MPPT4:");
					//uart_puts(Input_Message.id);
					//for (int i=0;i<4;i++)						//4 data fields
					//{
						//itoa(Input_Message.data[i],buff,10);
						//MPPT_Message.data[i] = Input_Message.data[i];
						//uart_puts(buff);
					//}
//
				//}//endif MPPT1
				//
			//
				//
			//
	//if (DEBUG)
	//{
				//uart_puts(",");
				//itoa(Input_Message.length,buff,10);
				///*TEST DISPLAY*/uart_puts("\nCAN Data Length:");
				//uart_puts(",");
				//if(Input_Message.length==0)						//checks length
				//{
					///*TEST DISPLAY*/uart_puts("No CAN Data bits\n");			//Prints if no data bits present
					//}else{
								//
					//uart_puts(buff);
					//for(int j = 0; j< Input_Message.length; j++)	//print byte for each data element
					//{
						///*TEST DISPLAY*/		uart_puts("\nCAN Data ");
						//itoa(j,buff,10);
						//uart_puts(buff);
						///*TEST DISPLAY*/			uart_puts(": ");
									//
						//itoa(Input_Message.data[j],buff,10);
									//
						//uart_puts(buff);
						//uart_puts(",");
					//}
				//}//endif input length==0
							//
				//itoa(Input_Message.rtr,buff,2);
				///*TEST DISPLAY*/	uart_puts("\nIs this an RTR?: ");
				//if(Input_Message.rtr==1)
				//{
					//uart_puts("Y,");
				//}else uart_puts("N\n");
							//
	//}
					//
//
//
//
				//
					//
					//
			//}//endif CAN_OK
///*TEST DISPLAY*/ uart_puts("\n-------\n CAN Done.\n");
		//}//endif CAN_MSGAVAIL
		//
//}//end CAN_readData
	//
				
			
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
							
	}//endif DEBUG
				}
				
			}//end inner while CAN_checkreceiveavaialable == MSGAVAIL
		
			}//endif rx_result == CAN_OK
/*TEST DISPLAY*/ uart_puts("\n-------\n CAN Done.\n");
		}//endif checkreceive == CAN_MSGAVAIL
		
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
			mavlink_msg_motor_driver_send(0,/*0,66*/Speed_Message.data[1],Speed_Message.data[1]);

			
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
			//mavlink_msg_hall_effect_send(MAVLINK_COMM_0, Input_Message.data[2],Input_Message.data[7],0);
			
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
			//TESTING
																					*/
//TESTING	mavlink_msg_gps_pack(100,200,&msg,latitude,longitude,time,date,lock_error);
			//MAV_uart_send(buf,len);

			
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

void MAV_uart_send(uint8_t buf[],uint8_t len)
{

	if( !(UCSR0A & (1<<UDRE0)) )
	{
		uart_flush();
	for (int i = 0; i < len ; i++){
		uart_putc(buf[i]);
		MAV_Rx_buff[i] = buf[i];
		}
	}
						
}


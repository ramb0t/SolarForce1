/*
 * MAVLink_Messaging.c
 *
 * Created: 2015/03/29 11:47:11 PM
 *  Author: Matt
 */ 

#include "MAVLink_Messaging.h"

#define DEBUG	1


//------------ISR for the Timer0-------------------------//

ISR(TIMER0_OVF_vect)
{

};

int main (void)
{
	/* -------port configuration----------------
	GPS Serial In Dig I/P 2 = PORTD2
	Telemetry Serial O/P 3 = PORTD3
	Telemetry Serial I/P 4 = PORTD4				*/
	
	UART_DDR |= _BV(TELEMETRY_UART_OUT);	//output
	UART_DDR &=~_BV(GPS_UART_DATA_IN);	//input
	UART_DDR &=~_BV(TELEMETRY_UART_IN);	//input
	
	DDRB |= _BV(DDB5);
	
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
		
		//while(CAN_Init(CAN_125KBPS_16MHZ) !=CAN_OK)
		//{
			CAN_Init(CAN_125KBPS_16MHZ);
		//};
		
	/*---------Timer Setup---------------------
		*Overflow based
		*1024 Prescalar						*/
	
	TCNT0 = 0x00;
	TCCR0A = 0x00;
	TCCR0B = (1<<CS02)|(1<<CS00);
	TIMSK0 = (1<<TOIE0);		//--enable later!
	
	
	/*---------UART Serial Init --------------------
		*uses UART.h library
		*interrupt-based					*/
	
		uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
				
		sei();	//interrupts ON
	
	//HACK: Sending GPS data and heartbeat
	//TODO: Get interrupt-based heartbeats and GPS data integrated with CAN
	
//---------------Operational Loop---------------------//
	
	while(1) {
		//uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); --CAUSES BREAKAGE
		
		if(TIFR0 &(1<<TOV0))
		{
			if (ctr2 == 15)
			{
			ctr2=0;
			uart_puts("\n------------GPS start----------\n");
			//GPS_readData();
			uart_puts("\n------------GPS done----------\n");
			TIFR0 = (0<<TOV0);
			}else ctr2++;

		}
		
_delay_ms(500);
		LED_DIAG_PORT |= (1<<LED_DIAG_ORG);
		LED_DIAG_PORT &= ~(1<<LED_DIAG_GRN);
					
		CAN_readData();
		
		MAV_msg_pack();
		

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
		uint8_t parseDone = 0;		
		char NMEA[70];
		unsigned int z=0;
		unsigned int lgth=0;
		unsigned int ctr = 0;
		char gpsdata;


		//uart_puts("\n---------GPS DATA---------\n");
			
				
		//uart_puts("GPS Ready");
		
				if(DEBUG)
				{
						gpsdata = uart_getc();
						while (gpsdata != '$')
						{
							gpsdata = uart_getc();							
							uart_putc(gpsdata);
						}
						
							while (gpsdata != '\n')
							{
								gpsdata = uart_getc();	//store char in NMEA buffer
								strcat(NMEA[ctr],gpsdata);
							}
							uart_puts(NMEA);				//print raw NMEA data

							//PARSE TIME: hhmmss.ss
							uart_puts("Time: ");
							//hour
							for(int i=0;i<2;i++)
							{
								uart_putc(NMEA[i]);
							}
							//minute
							uart_puts("h:");
							for(int i=2;i<4;i++)
							{
								uart_putc(NMEA[i]);
							}
							uart_puts(": ");
							for(int i=4;i<6;i++)
							{
								uart_putc(NMEA[i]);
							}
							parseDone==1;
						
					

						
				}
					

				
				//gpsdata = uart_getc();
				//if(gpsdata != '\0')				//getting GPRMC data only
				//{
				//NMEA[z] = gpsdata;				//add to char array if not EOL
				//z++;
				//}else lgth=z; break;				//store string length
			
															////check each char for $GPRMC
		//for(int i = 0;i<62;i++)
		//{
			//uart_putc(NMEA[i]);
		//}


		//z=0;
		//
		//while(NMEA[z]!='$' && z<10)			//search the string for '$'
		//{
				//z++;
			//if(DEBUG)
			//{
				//if(NMEA[z]=='$')
				//{
					//uart_puts("Got$");
					//if (NMEA[z+1]=="G")
					//{
						//uart_puts("GotG");
					//}
					//break;
				//}
				//break;
			//}
					//
		//}
		
		////print GPS data to UART	
		//uart_flush();
		//for(ctr=z+1;ctr<lgth;ctr++)
		//{
			//uart_putc(NMEA[ctr]);
		//}
	
}


void CAN_readData()
{
	uart_flush();
	_delay_ms(20);
	uart_puts("<<<<START OF MESSAGE>>>>\n");
	uart_puts("\n---------CAN DATA---------\n");
	char buff[16] ;
	if(DEBUG){
		itoa(CAN_checkReceiveAvailable(), buff,10);
		uart_puts("RXAvail:");
		uart_puts(buff);
		
		itoa(CAN_checkError(),buff,10);
		uart_puts("CheckErr:");
		uart_puts(buff);
		_delay_ms(100);
		
		if(CAN_checkReceiveAvailable()==CAN_NOMSG)
		{
			uart_puts("\nNo CAN message / CAN Bus disconnected!\n");
		}
	
	//if (CAN_checkError()==CAN_CTRLERROR)
	//{
	//uart_puts("CAN Controller Error!");
	////TODO: Set flag for controller error in GUI
	//}else if (CAN_checkError()==CAN_OK)
	
		if(CAN_checkReceiveAvailable()==CAN_MSGAVAIL)
		{
			int rx_Result;
			rx_Result = CAN_readMessage(&CANBusInput);			//read a byte of CAN data
			
			if (rx_Result == CAN_OK)							//if read correctly...
			{
				//char buff[32] ;
				buff[0] = "\0";
				itoa(CANBusInput.id,buff,16);					//read ASCII-converted byte into buffer
				uart_puts("\nCAN ID:");
				uart_puts(buff);								//output bytestring to UART
				
				itoa(CANBusInput.length,buff,10);
				uart_puts("\nCAN Data Length:");
				
				if(CANBusInput.length==0)						//checks length
				{
					uart_puts("No CAN Data bits\n");			//Prints if no data bits present
					}else{
						
					uart_puts(buff);
					for(int j = 0; j< CANBusInput.length; j++)	//print byte for each data element
					{
						uart_puts("\nCAN Data ");
						itoa(j,buff,10);
						uart_puts(buff);
						uart_puts(": ");
						
						itoa(CANBusInput.data[j],buff,10);
						
						uart_puts(buff);
						uart_puts(" ");
					}
				}//endif input length==0
				
				itoa(CANBusInput.rtr,buff,2);
				uart_puts("\nIs this an RTR?: ");
				if(CANBusInput.rtr==1)
				{
					uart_puts("Yes\n");
				}else uart_puts("No\n");
				
				
			}//endif CAN_OK
			uart_puts("\n-------\n CAN Done.\n");
		}//endif CAN_MSGAVAIL
	}//endif DEBUG
		
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


			uart_puts("\n---------MAVLink Data---------\n");
			//---------------MAVLink Data---------------------------//
			//// Initialize the required buffers
			mavlink_message_t msg;
			uint8_t buf[MAVLINK_MAX_PACKET_LEN];
			uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
			
			/*For all packaging, parameters 1,2,3 are the same */
			
			/*-----------------------------------------------------------------------
			NAME: Motor Driver Data
			DESCRIPTION: Speed from the motor driver RPM and error flags
				Parameters		4 = speed from motor driver (RPM)
			/*					5 = uint8_t magnet_back missing? (0/n 1/y)
								6 = uint8_t magnet_front missing? (0/n 1/y)
			Assume CAN data 0 = motor controller temp
							   data 1 = speed								*/
			mavlink_msg_motor_driver_pack(100,200,&msg,CANBusInput.data[0],CANBusInput.data[1]);
			MAV_uart_send(buf,len);
			/*-----------------------------------------------------------------------
				Parameters		4 = speed from hall effect
								5 = uint8_t magnet_back missing? (0/n 1/y)
								6 = uint8_t magnet_front missing? (0/n 1/y)
			//TESTING		CAN 2 = speed to send							*/
			mavlink_msg_hall_effect_pack(100,200,&msg,CANBusInput.data[2],0,0);
			MAV_uart_send(buf,len);
			//-----------------------------------------------------------------------
			////Parameters		4 = uint8_t fault condition
			/*					5 = uint8_t source current
								6 = uint8_t load_current
								7 = char bat_fan_status
								8 = uint8_t LLIM_state
								9 = uint8_t HLIM_state
								10 = uint8_t state_of_chg (percentage)
								11 = uint16_t pack_voltage
								12 = const uint16_t *cell_voltages [low,avg,high]
								13 = const uint16_t *cell_temps [low,avg,high]
								14 = uint8_t system_status
								
			*/
			// mavlink_msg_bms_data_pack(100,200, &msg,uint8_t fault_condition, float source_current, float load_current, char bat_fan_status, uint8_t LLIM_state, uint8_t HLIM_state, uint8_t state_of_chg, uint16_t pack_voltage, const uint16_t *cell_voltages, const uint16_t *cell_temps, uint8_t system_status)

			uart_flush();
			uart_puts("\n---------MAVLink Heartbeat---------\n");
			// Pack the message
			// mavlink_message_heartbeat_pack(system id, component id, message container, system type, MAV_AUTOPILOT_GENERIC)
			mavlink_msg_heartbeat_pack(100, 200, &msg, system_type, autopilot_type,base_mode,custom_mode,system_status);
			MAV_uart_send(buf,len);
			//
			uart_puts("\n<<<<END OF MESSAGE>>>>\n");
			////_delay_ms(HEARTBEAT_DELAY);
	
}

void MAV_uart_send(uint8_t buf[],uint8_t len)
{

	if( !(UCSR0A & (1<<UDRE0)) )
	{
		uart_flush();
	for (int i = 0; i < len ; i++){
		uart_putc(buf[i]);
		}
	}
						
}



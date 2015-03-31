/*
 * MAVLink_Messaging.c
 *
 * Created: 2015/03/29 11:47:11 PM
 *  Author: Matt
 */ 

#define F_CPU 16000000UL
#define UART_BAUD_RATE 9600  
#define MAVLINK_USE_CONVENIENCE_FUNCTIONS   

#define TELEMETRY_UART_OUT DDD3
#define GPS_UART_DATA_IN DDD2
#define TELEMETRY_UART_IN DDD4

#define UART_DDR DDRD

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "uart.h"					//UART library
#include "mavlink.h"				//MAVLink framework

#include "../lib/CAN/CAN.h"			//CAN Framework
#include "../lib/mcp2515/mcp2515.h"	//bit timings for MCP2515

mavlink_system_t mavlink_system;
volatile int counter=0;
volatile int ctr2=0;

//------------Enum for MAVLink Heartbeat delay-----------//
enum {
	HEARTBEAT_DELAY = 1000
};

//------------CAN Received Message Struct----------------//

CANMessage CANBusInput;			//object of type CANMessage

//------------ISR for the Timer0-------------------------//

ISR(TIMER0_OVF_vect)
{
	if (counter ==16)
	{
		if (ctr2 ==16)
		{
		uart_puts("ISR!");
		ctr2=0;
		}
		else ctr2++;
		counter=0;
	}
	else counter++;
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
	
	/*----------CAN PORT INPUTS-----------------
		<<Master SPI>>
		Name	CANPin	ArduinoPin		Port
		------------------------------------
		CS/SS	PIN8	DigPin10		PB2
		MISO	PIN7	DigPin12		PB4
		MOSI	PIN6	DigPin11		PB3
		SCK		PIN5	DigPin13		PB5
		INT		PIN4	N/A					*/
		
		SPI_Init();
		CAN_Init(CAN_125KBPS_16MHZ);
		
	/*---------Timer Setup---------------------
		*Overflow based
		*1024 Prescalar						*/
	
	TCNT0 = 0x00;
	TCCR0A = 0x00;
	TCCR0B = (1<<CS02)|(1<<CS00);
	//TIMSK0 = (1<<TOIE0);		--enable later!
	
	
	/*---------UART Serial Init --------------------
		*uses UART.h library
		*interrupt-based					*/
	
	    unsigned int c;
	    char buffer[7];
	    unsigned int  num=134;
		uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
				
		sei();	//interrupts ON
	
	
	//HACK: Sending GPS data and heartbeat
	//TODO: Get interrupt-based heartbeats and GPS data integrated with CAN
	
	while(1) {
		
		//---------------Get CAN data via SPI---------------------//
	int rx_Result = CAN_OK;
	CAN_readMessage(&CANBusInput);
		if (rx_Result == CAN_OK)
		{
			char buff[10];
			itoa(CANBusInput.id,buff,10);
			uart_puts("\nCAN ID:");
			uart_puts(buff);
			
			itoa(CANBusInput.length,buff,10);
			uart_puts("\nCAN Data Length:");
			uart_puts(buff);
			
				for(int j = 0; j< CANBusInput.length; j++)
				{
				uart_puts("\nCAN Data");
				itoa(j,buff,10);
				uart_puts(buff);
				uart_puts(":");
				
				itoa(CANBusInput.data[j],buff,10);
				
				uart_puts(buff);
				uart_puts(" ");
				}
				
				uart_puts("\n-------\n CAN Done.\n");
		}
		
		
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
				
				char NMEA[300];
				unsigned int z=0;
				unsigned int ctr = 0;
				unsigned int hdr = 0;
				char gpsdata;

		//do								//try find start in first 6 chars
		//{
			//gpsdata = uart_getc();						//check first char of input buffer for $GPRMC
		//
		//}while(gpsdata != '$');		
		//
		
			while( !(UCSR0A & (1<<RXC0)) )
			{			
				gpsdata = uart_getc();				//get one char from GPS at a time

				if(gpsdata != '\0')				//getting GPRMC data only
				{
					NMEA[z] = gpsdata;				//add to char array if not EOL
					z++;
				}
				else 
				{
					(1<<RXC0); break;				//else set flag to stop parsing data
				}		
			}

				uart_puts("\nGPS MSG:");
				_delay_ms(100);

				for (ctr=0;ctr<z;ctr++)				//display parsed string
				{
					uart_putc(NMEA[ctr]);
				}
				uart_puts("\n<<end");
				uart_puts("\nGPS received.\n");
				_delay_ms(100);
				

		//---------------MAVLink Setup---------------------------//
	/*MAVLINK asks to set all systm statuses as integers. For human readibility ENUMS are used in the appropriate headers
	these enums convert text for states to integers sent & interpreted. 3 phases to a message:
  --define the enum types you'll need and use friendly names e.g. value_name = MAV_ENUM_VALUE_NAME
  --use a send / encode function from the relevant header to send HEARTBEAT to get QGC/APM working
  --then have a function (see solarCar.h and the entire message_definitions folder for types to send
  --pass the values or enum friendly names to the functions
  --this ensures the message goes to MAVLink frame
  --connect to QGC and observe output! */
    
	// Define the system type (see solarCar.h for list of possible types) 
	int system_type = MAV_TYPE_GROUND_ROVER;
	int autopilot_type = MAV_AUTOPILOT_GENERIC;
    int base_mode = MAV_MODE_FLAG_AUTO_ENABLED;
	int custom_mode = MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
    int system_status = MAV_STATE_ACTIVE;

		// Initialize the required buffers
		mavlink_message_t msg;
		uint8_t buf[MAVLINK_MAX_PACKET_LEN];
		uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
		
		// Pack the message
		// mavlink_message_heartbeat_pack(system id, component id, message container, system type, MAV_AUTOPILOT_GENERIC)
		mavlink_msg_heartbeat_pack(100, 200, &msg, system_type, autopilot_type,base_mode,custom_mode,system_status);
		
		//only load as many bytes as needed into the send buffer
		
		for (int i = 0; i < len ; i++)
		{
			uart_putc(buf[i]);
		}
	
		_delay_ms(HEARTBEAT_DELAY);
		
	uart_puts("\nTest Message from Solar Car\n");
	
	}
	
	
	
	return 0;
}


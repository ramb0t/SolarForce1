/*
 * MAVLink_Messaging.c
 *
 * Created: 2015/03/29 11:47:11 PM
 *  Author: Matt
 */ 

#include "MAVLink_Messaging_RX.h"

#define DEBUG	1

//------------ISR for the Timer0-------------------------//

int main (void)
{
	/* -------port configuration----------------
	GPS Serial In Dig I/P 2 = PORTD2
	Telemetry Serial O/P 3 = PORTD3
	Telemetry Serial I/P 4 = PORTD4				*/
	
	UART_DDR |= _BV(TELEMETRY_UART_OUT);	//output
	UART_DDR &=~_BV(TELEMETRY_UART_IN);	//input
	
	//DDRB |= _BV(DDB5);
			
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
	
		uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
				
		sei();	//interrupts ON
	
	//HACK: Sending GPS data and heartbeat
	//TODO: Get interrupt-based heartbeats and GPS data integrated with CAN
	
				mavlink_system.sysid = 100; // System ID, 1-255
				mavlink_system.compid = 200; // Component/Subsystem ID, 1-255
	
//---------------Operational Loop---------------------//
	
	while(1) {
		//uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); --CAUSES BREAKAGE

		MAV_msg_Unpack();
				

	}
	return 0;

}


void MAV_msg_Unpack()
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


			//uart_puts("\n-MAVLink Data---------\n");
			//---------------MAVLink Data---------------------------//
			// Initialize the required buffers
			// Set correct buffer lengths

			
			mavlink_message_t msg;
			mavlink_status_t status;
			uint8_t buf[MAVLINK_MAX_PACKET_LEN];
			uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
			
			uart_puts(" ");
			 
			mavlink_message_t msg2;
			int chan = 0;
			int ctr = 0;
			int hb_lost = 0;
			uint8_t c ;
			mavlink_status_t* mav_status;

			
			// COMMUNICATION THROUGH EXTERNAL UART PORT
			
			while(!(UCSR0A & (1<<UDRE0)))									//poll data from the UART bus only while there is data on it
			{
				while (ctr < MAVLINK_MAX_PACKET_LEN)						//while packet size < MAVLink packet
				{
					
					c=uart_getc();								//get another char
					uart_putc(c);	
					ctr++;										//TEST put out
					// Try to get a new message
					if(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) //if packet matches defined MAVLink packet
					{
						// Start Handler for message
						
						switch(msg.msgid)
						{
							case MAVLINK_MSG_ID_HEARTBEAT:					//Is it heartbeat ID?
							{
								uart_puts("HB");
								// E.g. read GCS heartbeat and go into
								// comm lost mode if timer times out
								
							}
							break;										//now check for next ID
							case MAVLINK_MSG_ID_MOTOR_DRIVER:				//is it Motor Driver data?
							{
								//uart_puts("MD");
							}
							break;										//now check for next ID
							case MAVLINK_MSG_ID_HALL_EFFECT:				//is it Hall Effect data?
							{
								uart_puts("HE");
							}
							break;										//now check for next ID
							case MAVLINK_MSG_ID_BMS_DATA:					//is it BMS data?
							{
								uart_puts("BMS");
							}
							case MAVLINK_MSG_ID_MPPT1_DATA:				//is it MPPT1 data?
							{
								//uart_puts("MPPT1");
							}
							default:
							hb_lost++;
							if (hb_lost > 100)
							{
								hb_lost = 0;
								uart_puts("\nConnLost\n");
							}
							break;
						}
					}
					
					// And get the next one
				
				}
				
			}
			
			

				//uint8_t byte = uart_getc();
			
				//{
					//if (uart_available())
					//{
							//for (int i=0;i<MAVLINK_MAX_PACKET_LEN;i++)
							//{
								//uart_putc(uart_getc());
							//}
												//
					//}
//
						//byte = uart_getc() ;
						////uart_putc(mavlink_parse_char(chan, byte, &msg2,mav_status));
						//if (mavlink_parse_char(chan, byte, &msg2,mav_status))
						//{
							//uart_puts("ID: ");
							//uart_putc(msg2.msgid);
							//
							////uart_puts("\nSeq:");
							////uart_putc(msg2.seq);
							////uart_puts("\nCompo: " );
							////uart_putc(msg2.compid);
							////uart_puts("\nsys: ");
							////uart_putc(msg.sysid);
						//}
					//
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



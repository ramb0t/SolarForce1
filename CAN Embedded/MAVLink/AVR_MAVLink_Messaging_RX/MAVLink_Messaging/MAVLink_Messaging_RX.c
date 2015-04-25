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
	//uart_puts("hi");
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

			//uart_puts_p("\n-MAVLink Data---------\n");
			//---------------MAVLink Data---------------------------//
			// Initialize the required buffers
			// Set correct buffer lengths

			
			mavlink_message_t msg;
			mavlink_status_t status;
			uint8_t buf[MAVLINK_MAX_PACKET_LEN];
			uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
						
			//uart_puts_p(PSTR(""));
			 
			mavlink_message_t msg2;
			int chan = 0;
			uint8_t c;
			mavlink_status_t* mav_status;

			//uart_puts("here");
			if(uart_available())
			{
			if(!(UCSR0A & (1<<RXC0)))									//poll data from the UART bus only while there is data on it
			{
				//uart_puts("also");
				//uart_putc('a');
				//if (ctr2 < MAVLINK_MAX_PACKET_LEN)						//while packet size < MAVLink packet
				
					c=uart_getc();								//get another char
					
					/*Each byte output of Unpack (takes 2ms)
					Count increased every 2ms
					hence if 5000ms pass with no data, errors are thrown!
					*/
					
					if (c == NULL)	
					{
						hb_lost++;										
						if (hb_lost > 7500)
						{
							hb_lost = 0;
							uart_puts_p(PSTR("ERROR>><<"));
							_delay_ms(20);
						}
					}
					
					// Try to get a new message
					
					uart_putc(c);								//TESTING OUTPUT	
					ctr2++;				
					if(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) //if packet matches defined MAVLink packet
					{
						// Start Handler for message
						switch(msg.msgid)
						{
							case MAVLINK_MSG_ID_HEARTBEAT:					//Is it heartbeat ID?
							{
								uart_puts_p(PSTR("HB"));
								// E.g. read GCS heartbeat and go into
								// comm lost mode if timer times out
								hb_lost = 0; //reset heartbeat counter
							}break;										//now check for next ID
							
							/*--------Data general message structure-------------
							>>XX,[comma separated fields]<<
							^ ^ ^         ^				 ^
							msg start
							 ID
								commadelim
										data
														end msg
																				*/
							case MAVLINK_MSG_ID_GPS:							//is it GPS data?
							{
								hb_lost=0;
								mavlink_gps_t gps;							//instantiate GPS object
								mavlink_msg_gps_decode(&msg,&gps);			//decode message
								uart_puts_p("GPS>>");					//delim and ID
								uart_putc(GPS_TXID);
								uart_putc(gps.latitude);
								uart_puts_p(PSTR(","));
								uart_putc(gps.longitude);
								uart_puts_p(PSTR(","));
								uart_putc(gps.time);
								uart_puts_p(PSTR(","));
								uart_putc(gps.date);
								uart_puts_p(PSTR(","));
								uart_putc(gps.lock_error);
								uart_puts_p(PSTR("<<"));
							break;	
							}break;
							
							case MAVLINK_MSG_ID_SPEED_HALLEFFECT:				//is it Motor Driver data?
							{
								hb_lost=0;
							//uart_flush();
							mavlink_speed_halleffect_t spdhe;					//instantiate object MD
							mavlink_msg_speed_halleffect_decode(&msg,&spdhe);	//encode message
							uart_puts_p(PSTR("MD>>"));					//delimiter & ID
							uart_putc(HESPD_TXID);
							uart_puts_p(PSTR(","));
							uart_putc(spdhe.avg_speed);						//avg. speed
							uart_puts_p(PSTR(","));						//delim
							uart_putc(spdhe.hes_speed);				//used as status flags
							uart_puts_p(PSTR(","));	
							uart_putc(spdhe.hes_RPM);	
							uart_puts_p(PSTR(","));	
							uart_putc(spdhe.motor_speed);
							uart_puts_p(PSTR(","));	
							uart_putc(spdhe.motor_RPM);
							uart_puts_p(PSTR(","));	
							uart_putc(spdhe.flags);
							uart_puts_p(PSTR("<<"));
														
							break;//now check for next ID
							}break;
							
						//////now check for next ID
							//case MAVLINK_MSG_ID_BMS_DATA:					//is it BMS data?
							//{
								//hb_lost=0;
								//uart_flush();
								//mavlink_bms_data_t bms;
								//mavlink_msg_bms_data_decode(&msg,&bms);	//decode BMS data packet
								//uart_puts_p(PSTR("BMS>>"));					//delim and ID
								//uart_putc(BMS_TXID);	
								//uart_puts_p(PSTR(","));
								////--------------BMS data  begin-----------//
								//uart_putc(bms.fault_condition);
								//uart_puts_p(PSTR(","));
								//uart_putc(bms.source_current);
								//uart_puts_p(PSTR(","));
								//uart_putc(bms.load_current);
								//uart_puts_p(PSTR(","));
								//uart_putc(bms.bat_fan_status);
								//uart_puts_p(PSTR(","));
								//uart_putc(bms.LLIM_state);
								//uart_puts_p(PSTR(","));
								//uart_putc(bms.HLIM_state);
								//uart_puts_p(PSTR(","));
								//uart_putc(bms.state_of_chg);
								//uart_puts_p(PSTR(","));
								//uart_putc(bms.pack_voltage);
								//uart_puts_p(PSTR(","));
								//for (int i=0;i<3;i++)
								//{
									//uart_putc(bms.cell_voltages[i]);	
									//uart_puts_p(PSTR(","));	
								//}
								//for (int i=0;i<3;i++)
								//{
									//uart_putc(bms.cell_temps[i]);
									//uart_puts_p(PSTR(","));
								//}
								//uart_putc(bms.system_status);
								//uart_puts_p(PSTR("<<"));	
								//break;				
							//}break;
							//
							//case MAVLINK_MSG_ID_ACCELO_GYRO:				//is it accelorometer data?
							//{
								//hb_lost=0;
								//uart_flush();
								//mavlink_accelo_gyro_t ac;
								//mavlink_msg_accelo_gyro_decode(&msg,&ac);
								//uart_puts_p(PSTR("AC>>"));
								//uart_putc(AC_TXID);		
								//uart_putc(ac.acceleration);
								//uart_puts_p(PSTR(","));
								//uart_putc(ac.incline);
								//uart_puts_p(PSTR("<<"));
								//break;
							//}break;
							//
							//case MAVLINK_MSG_ID_MPPT1_DATA:				//is it MPPT1 data?
							//{
								//hb_lost=0;
								//uart_flush();
								//mavlink_mppt1_data_t m1;
								//mavlink_msg_mppt1_data_decode(&msg,&m1);
								//uart_puts_p(PSTR("M1>>"));
								//uart_putc(MPPT1_TXID);
								//uart_puts_p(PSTR(","));		
								//uart_putc(m1.voltage_in);
								//uart_puts_p(PSTR(","));
								//uart_putc(m1.current_in);
								//uart_puts_p(PSTR(","));
								//uart_putc(m1.overtemp);
								//uart_puts_p(PSTR(","));
								//uart_putc(m1.undervolt);
								//uart_puts_p(PSTR("<<"));
								//break;
							//}break;
							//
							//case MAVLINK_MSG_ID_MPPT2_DATA:				//is it MPPT1 data?
							//{
								//hb_lost=0;
								//uart_flush();
								//mavlink_mppt2_data_t m2;
								//mavlink_msg_mppt1_data_decode(&msg,&m2);
								//uart_puts_p(PSTR("M2>>"));
								//uart_putc(MPPT2_TXID);
								//uart_puts_p(PSTR(","));
								//uart_putc(m2.voltage_in);
								//uart_puts_p(PSTR(","));
								//uart_putc(m2.current_in);
								//uart_puts_p(PSTR(","));
								//uart_putc(m2.overtemp);
								//uart_puts_p(PSTR(","));
								//uart_putc(m2.undervolt);
								//uart_puts_p(PSTR("<<"));
								//break;
							//}break;
							//
							//case MAVLINK_MSG_ID_MPPT3_DATA:				//is it MPPT1 data?
							//{
								//hb_lost=0;
								//uart_flush();
								//mavlink_mppt3_data_t m3;
								//mavlink_msg_mppt1_data_decode(&msg,&m3);
								//uart_puts_p(PSTR("M3>>"));
								//uart_putc(MPPT3_TXID);
								//uart_puts_p(PSTR(","));
								//uart_putc(m3.voltage_in);
								//uart_puts_p(PSTR(","));
								//uart_putc(m3.current_in);
								//uart_puts_p(PSTR(","));
								//uart_putc(m3.overtemp);
								//uart_puts_p(PSTR(","));
								//uart_putc(m3.undervolt);
								//uart_puts_p(PSTR("<<"));
								//break;
							//}break;
							//
							//case MAVLINK_MSG_ID_MPPT4_DATA:				//is it MPPT1 data?
							//{
								//hb_lost=0;
								//uart_flush();
								//mavlink_mppt4_data_t m4;
								//mavlink_msg_mppt1_data_decode(&msg,&m4);
								//uart_puts_p(PSTR("M4>>"));
								//uart_putc(MPPT4_TXID);
								//uart_puts_p(PSTR(","));
								//uart_putc(m4.voltage_in);
								//uart_puts_p(PSTR(","));
								//uart_putc(m4.current_in);
								//uart_puts_p(PSTR(","));
								//uart_putc(m4.overtemp);
								//uart_puts_p(PSTR(","));
								//uart_putc(m4.undervolt);
								//uart_puts_p(PSTR("<<"));
								//break;
							//}break;					
			
							default:
							{
	
							}
						}
					}//end mavlink_parse_char
					
					
					// And get the next one
							
				}//end while counter
				
			}//endif RXC0
			
			
							
}//end upacks




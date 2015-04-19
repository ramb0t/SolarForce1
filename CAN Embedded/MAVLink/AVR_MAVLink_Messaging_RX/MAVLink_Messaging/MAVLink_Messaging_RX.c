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


			//uart_puts_p("\n-MAVLink Data---------\n");
			//---------------MAVLink Data---------------------------//
			// Initialize the required buffers
			// Set correct buffer lengths

			
			mavlink_message_t msg;
			mavlink_status_t status;
			uint8_t buf[MAVLINK_MAX_PACKET_LEN];
			uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
			
			uart_puts_p(PSTR(" "));
			 
			mavlink_message_t msg2;
			int chan = 0;
			int ctr = 0;

			uint8_t c ;
			mavlink_status_t* mav_status;

			
			// COMMUNICATION THROUGH EXTERNAL UART PORT
			
			while(!(UCSR0A & (1<<UDRE0)))									//poll data from the UART bus only while there is data on it
			{
				while (ctr < MAVLINK_MAX_PACKET_LEN)						//while packet size < MAVLink packet
				{
					
					c=uart_getc();								//get another char
					uart_putc("");								//TESTING OUTPUT
					ctr++;										//TEST put out
					// Try to get a new message
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
								
							}
							break;										//now check for next ID
							
							/*--------Data general message structure-------------
							>>XX,[comma separated fields]<<
							^ ^ ^         ^				 ^
							msg start
							 ID
								commadelim
										data
														end msg
																				*/
							
							case MAVLINK_MSG_ID_MOTOR_DRIVER:				//is it Motor Driver data?
							{
								mavlink_motor_driver_t md;					//instantiate object MD
								mavlink_msg_motor_driver_decode(&msg,&md);	//encode message
								uart_puts_p(PSTR("MD>>"));					//delimiter & ID
								uart_putc(MD_TXID);							
								uart_puts_p(PSTR(","));
								uart_putc(md.speed);						//avg. speed
								uart_puts_p(PSTR(","));						//delim
								uart_putc(md.controller_temp);				
								uart_puts_p(PSTR("<<"));
								break;									//now check for next ID
							}break;
																		
							case MAVLINK_MSG_ID_HALL_EFFECT:				//is it Hall Effect data?
							{
								mavlink_hall_effect_t he;					//generate a struct object
								mavlink_msg_hall_effect_decode(&msg,&he);	//decode MAVLink into data
								uart_puts("HE>>");							//delimiter & ID
								uart_putc(HE_TXID);
								uart_puts_p(PSTR(","));
								uart_putc(he.speed);						//speed data
								uart_puts_p(PSTR(","));
								uart_putc(he.left_magnet);					//magnet flags
								uart_puts_p(PSTR(","));	
								uart_putc(he.right_magnet);
								uart_puts_p(PSTR("<<"));
								break;
							}break;
																	//now check for next ID
							case MAVLINK_MSG_ID_BMS_DATA:					//is it BMS data?
							{
								mavlink_bms_data_t bms;
								mavlink_msg_bms_data_decode(&msg,&bms);	//decode BMS data packet
								uart_puts_p(PSTR("BMS>>"));					//delim and ID
								uart_putc(BMS_TXID);	
								uart_puts_p(PSTR(","));
								//--------------BMS data  begin-----------//
								uart_putc(bms.fault_condition);
								uart_puts_p(PSTR(","));
								uart_putc(bms.source_current);
								uart_puts_p(PSTR(","));
								uart_putc(bms.load_current);
								uart_puts_p(PSTR(","));
								uart_putc(bms.bat_fan_status);
								uart_puts_p(PSTR(","));
								uart_putc(bms.LLIM_state);
								uart_puts_p(PSTR(","));
								uart_putc(bms.HLIM_state);
								uart_puts_p(PSTR(","));
								uart_putc(bms.state_of_chg);
								uart_puts_p(PSTR(","));
								uart_putc(bms.pack_voltage);
								uart_puts_p(PSTR(","));
								for (int i=0;i<3;i++)
								{
									uart_putc(bms.cell_voltages[i]);	
									uart_puts_p(PSTR(","));	
								}
								for (int i=0;i<3;i++)
								{
									uart_putc(bms.cell_temps[i]);
									uart_puts_p(PSTR(","));
								}
								uart_putc(bms.system_status);
								uart_puts_p(PSTR("<<"));					
								break;
							}break;
							
							case MAVLINK_MSG_ID_ACCELO_GYRO:				//is it accelorometer data?
							{
								mavlink_accelo_gyro_t ac;
								mavlink_msg_accelo_gyro_decode(&msg,&ac);
								uart_puts_p(PSTR("AC>>"));
								uart_putc(AC_TXID);		
								uart_putc(ac.acceleration);
								uart_puts_p(PSTR(","));
								uart_putc(ac.incline);
								uart_puts_p(PSTR("<<"));
								break;
							}break;
							
							case MAVLINK_MSG_ID_MPPT1_DATA:				//is it MPPT1 data?
							{
								mavlink_mppt1_data_t m1;
								mavlink_msg_mppt1_data_decode(&msg,&m1);
								uart_puts_p(PSTR("M1>>"));
								uart_putc(MPPT1_TXID);
								uart_puts_p(PSTR(","));		
								uart_putc(m1.voltage_in);
								uart_puts_p(PSTR(","));
								uart_putc(m1.current_in);
								uart_puts_p(PSTR(","));
								uart_putc(m1.overtemp);
								uart_puts_p(PSTR(","));
								uart_putc(m1.undervolt);
								break;
							}break;
							
							case MAVLINK_MSG_ID_MPPT2_DATA:				//is it MPPT1 data?
							{
								mavlink_mppt1_data_t m2;
								mavlink_msg_mppt1_data_decode(&msg,&m2);
								uart_puts_p(PSTR("M2>>"));
								uart_putc(MPPT2_TXID);
								uart_puts_p(PSTR(","));
								uart_putc(m2.voltage_in);
								uart_puts_p(PSTR(","));
								uart_putc(m2.current_in);
								uart_puts_p(PSTR(","));
								uart_putc(m2.overtemp);
								uart_puts_p(PSTR(","));
								uart_putc(m2.undervolt);
								break;
							}break;
							
							case MAVLINK_MSG_ID_MPPT3_DATA:				//is it MPPT1 data?
							{
								mavlink_mppt1_data_t m3;
								mavlink_msg_mppt1_data_decode(&msg,&m3);
								uart_puts_p(PSTR("M3>>"));
								uart_putc(MPPT3_TXID);
								uart_puts_p(PSTR(","));
								uart_putc(m3.voltage_in);
								uart_puts_p(PSTR(","));
								uart_putc(m3.current_in);
								uart_puts_p(PSTR(","));
								uart_putc(m3.overtemp);
								uart_puts_p(PSTR(","));
								uart_putc(m3.undervolt);
								break;
							}break;
							
							case MAVLINK_MSG_ID_MPPT4_DATA:				//is it MPPT1 data?
							{
								mavlink_mppt1_data_t m4;
								mavlink_msg_mppt1_data_decode(&msg,&m4);
								uart_puts_p(PSTR("M4>>"));
								uart_putc(MPPT4_TXID);
								uart_puts_p(PSTR(","));
								uart_putc(m4.voltage_in);
								uart_puts_p(PSTR(","));
								uart_putc(m4.current_in);
								uart_puts_p(PSTR(","));
								uart_putc(m4.overtemp);
								uart_puts_p(PSTR(","));
								uart_putc(m4.undervolt);
								break;
							}break;
							default:
							{
								
							}
							
						}
					}
					
					// And get the next one
				
				}
				
			}
			
			

										//byte = uart_getc() ;
						////uart_putc(mavlink_parse_char(chan, byte, &msg2,mav_status));
						//if (mavlink_parse_char(chan, byte, &msg2,mav_status))
						//{
							//uart_puts_p("ID: ");
							//uart_putc(msg2.msgid);
							//
							////uart_puts_p("\nSeq:");
							////uart_putc(msg2.seq);
							////uart_puts_p("\nCompo: " );
							////uart_putc(msg2.compid);
							////uart_puts_p("\nsys: ");
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
			//uart_puts_p("\nTemperature:");
			//uart_puts_p(buf);
			//
			//itoa(MotorDriver->speed,buf,10);
			//uart_puts_p("\nSpeed:");
			//uart_puts_p(buf);
	
}




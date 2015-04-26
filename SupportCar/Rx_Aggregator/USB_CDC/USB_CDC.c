/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the VirtualSerial demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "VirtualSerial.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef __AVR_ATmega32U4__
#define __AVR_ATmega32U4__
#endif

#include "MAVLink_Messaging_RX.h"
#include "../lib/uart/uart.h"

#define F_CPU 16e6
#define MAX_CAPTURE 15
#define Irrad_Channel 13
#define DEBUG	1

#define quick_blink 200
#define slow_blink 500
#define super_slow_blink 1500

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber   = INTERFACE_ID_CDC_CCI,
				.DataINEndpoint           =
					{
						.Address          = CDC_TX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.DataOUTEndpoint =
					{
						.Address          = CDC_RX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.NotificationEndpoint =
					{
						.Address          = CDC_NOTIFICATION_EPADDR,
						.Size             = CDC_NOTIFICATION_EPSIZE,
						.Banks            = 1,
					},
			},
	};

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs.
 */
static FILE USBSerialStream;

#pragma region ADC_Config

	//initialise the adc
	void init_adc()
	{
		//clear all
		ADMUX = 0;
		
		//adc reference is AVcc
		//Single Ended Mode
		ADMUX |= (1<<REFS0);
		
		//Enable ADC with conversion completed interrupt
		//assume single conversion mode
		ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	}

	//allows the disabling of a digital input to reduce power consumption
	void disable_digital_input(uint8_t channel)
	{
		DIDR2 |= 1<<ADC13D;
	}

	void adc_read()
	{
		//set channel to 13
		ADMUX |= (1<<MUX0)|(1<<MUX2);
		//MUX5 is in ADCSRB!
		ADCSRB |= (1<<MUX5);
		//start read
		ADCSRA |= 1<<ADSC;
	}
	
	volatile uint16_t voltage;

#pragma endregion

#pragma region TimerSetups

	//setup timer 3 for input capture
	void init_timer3_ICP()
	{
		//enable input capture noise canceller and trigger on a rising edge
		//choose prescaler of /256... gives 62500 clocks for max freq and 16us resolution
		TCCR3B = (1<<ICES3)|(1<<CS32)|(1<<ICNC3);
	
		//setup input capture interrupt and overflow interrupt
		TIMSK3 = (1<<TOIE3)|(1<<ICIE3);
	}

	volatile uint32_t sum_capture = 0;
	volatile uint8_t count_capture = 0;

#pragma endregion

#pragma region Flags_and_Useful_Things

	typedef union
	{
		uint8_t all;
		struct
		{
			uint8_t ADC_read_complete: 1,
			ICP_ready: 1;
		};
	} FLAGS;
	
	void diagnostic1_blink()
	{
		
	}

	static volatile FLAGS myFlags;

#pragma endregion

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	/* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	
	//MAVLink things
	
	//uart setup
	UART_DDR &=~_BV(TELEMETRY_UART_IN);	//input
	UART_DDR |= _BV(TELEMETRY_UART_OUT);//output
	
	//timer0 setup
	TCNT0 = 0x00;
	TCCR0A = 0x00;
	#define uart1_BAUD_RATE 9600
	uart1_init( UART_BAUD_SELECT(uart1_BAUD_RATE,F_CPU) );
	
	uint8_t msg_counter = 0;
	
	GlobalInterruptEnable();

	while (1)
	{
		fputs("new loop", &USBSerialStream);
		
		//send local sensors should be sent roughly once every 15 MAVLink Packets
		if(++msg_counter > 15)
		{
			adc_read();
			msg_counter = 0;
		}
		char buffer[50];
		
		if (myFlags.ADC_read_complete == 1)//if an Irradiance sensor data packet is ready to be sent
		{
			_delay_ms(123);    //debug or necessary?
			//testBlink(quick_blink);
			//debug!			fputs("Voltage Reading in counts = ", &USBSerialStream);
			
			itoa(voltage,buffer,10); //USB is really fast, so sending in ASCII is a minimal overhead.
									 //not constrained to fixed-length frames
			fputs(">>13,", &USBSerialStream);
			fputs(buffer, &USBSerialStream);
			fputs("<<", &USBSerialStream);
			
			//proper code will send the string ">>13,ADC<<"
			myFlags.ADC_read_complete = 0;//clear the flag
		}
		//fputs("Voltage Reading in mV = ",&USBSerialStream);
		//fputs(buffer1,&USBSerialStream);
		
		
		//MAV_msg_Unpack();
		
		/* Must throw away unused bytes from the host, or it will lock up while waiting for the device */
		CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
}

void ADC_ok_LED()
{
	ADC_ok_LED();
	PORTF &= ~(1<</*PORTF4*/PORTF0);
}

void testBlink(int time)
{
	PORTF &= ~((1<<PORTF1) | (1<<PORTF0) | (1<<PORTF4));
	
	PORTC &= ~(1<<PORTC6);
	
	PORTD &= ~((1<<PORTD0)|(1<<PORTD1));
	
	_delay_ms(250);
				
	PORTF |= (1<<PORTF1) | (1<<PORTF0) | (1<<PORTF4);
			
	PORTC |= 1<<PORTC6;
			
	PORTD |= (1<<PORTD0)|(1<<PORTD1);
	
	_delay_ms(250);
}

#pragma region LUFA_Functions

	/** Configures the board hardware and chip peripherals for the demo's functionality. */
	void SetupHardware(void)
	{
		#if (ARCH == ARCH_AVR8)
		/* Disable watchdog if enabled by bootloader/fuses */
		MCUSR &= ~(1 << WDRF);
		wdt_disable();

		/* Disable clock division */
		clock_prescale_set(clock_div_1);
		#elif (ARCH == ARCH_XMEGA)
		/* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
		XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
		XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

		/* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
		XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
		XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

		PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
		#endif

		/* Hardware Initialization */
		USB_Init();
		
		//init for ADC
		DDRB &= ~(1<<PORTB6);
		init_adc();
		//disable_digital_input();
		
		//init for diagnostic LEDs
		DDRF |= (1<<PORTF1) | (1<<PORTF0) | (1<<PORTF4);
		PORTF |= (1<<PORTF1) | (1<<PORTF0) | (1<<PORTF4);
		DDRC |= 1<<PORTC6;
		PORTC |= 1<<PORTC6;
		DDRD |= (1<<PORTD0)|(1<<PORTD1);
		PORTD |= (1<<PORTD0)|(1<<PORTD1);
	}

	/** Event handler for the library USB Connection event. */
	void EVENT_USB_Device_Connect(void)
	{
		//LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
	}

	/** Event handler for the library USB Disconnection event. */
	void EVENT_USB_Device_Disconnect(void)
	{
		//LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	}

	/** Event handler for the library USB Configuration Changed event. */
	void EVENT_USB_Device_ConfigurationChanged(void)
	{
		bool ConfigSuccess = true;

		ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);

		//LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
	}

	/** Event handler for the library USB Control Request reception event. */
	void EVENT_USB_Device_ControlRequest(void)
	{
		CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
	}

#pragma endregion

#pragma region MAVLink functions

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

			//uart1_puts_p("\n-MAVLink Data---------\n");
			//---------------MAVLink Data---------------------------//
			// Initialize the required buffers
			// Set correct buffer lengths
			
			//fputs("in unpack", &USBSerialStream);//debug
			
			mavlink_message_t msg;
			mavlink_status_t status;
			uint8_t buf[MAVLINK_MAX_PACKET_LEN];
			uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
						
			//uart1_puts_p(PSTR(""));
			 
			mavlink_message_t msg2;
			int chan = 0;
			uint8_t c;
			mavlink_status_t* mav_status;

			//uart1_puts("here");
			
			if(uart1_available())
			{
			if(!(UCSR1A & (1<<RXC1)))									//poll data from the UART bus only while there is data on it
			{
				//uart1_puts("also");
				//uart1_putc('a');
				//if (ctr2 < MAVLINK_MAX_PACKET_LEN)						//while packet size < MAVLink packet
				
					c=uart1_getc();								//get another char
					
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
							uart1_puts_p(PSTR("ERROR>><<"));
							_delay_ms(20);
						}
					}
					
					// Try to get a new message
					
					uart1_putc(c);								//TESTING OUTPUT	
					fputc(c,&USBSerialStream);
					ctr2++;				
					if(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) //if packet matches defined MAVLink packet
					{
						// Start Handler for message
						switch(msg.msgid)
						{
							case MAVLINK_MSG_ID_HEARTBEAT:					//Is it heartbeat ID?
							{
								uart1_puts_p(PSTR("HB"));
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
								uart1_puts_p("GPS>>");					//delim and ID
								uart1_putc(GPS_TXID);
								uart1_putc(gps.latitude);
								uart1_puts_p(PSTR(","));
								uart1_putc(gps.longitude);
								uart1_puts_p(PSTR(","));
								uart1_putc(gps.time);
								uart1_puts_p(PSTR(","));
								uart1_putc(gps.date);
								uart1_puts_p(PSTR(","));
								uart1_putc(gps.lock_error);
								uart1_puts_p(PSTR("<<"));
							break;	
							}break;
							
							case MAVLINK_MSG_ID_SPEED_HALLEFFECT:				//is it Motor Driver data?
							{
								hb_lost=0;
							//uart1_flush();
							mavlink_speed_halleffect_t spdhe;					//instantiate object MD
							mavlink_msg_speed_halleffect_decode(&msg,&spdhe);	//encode message
							uart1_puts_p(PSTR("MD>>"));					//delimiter & ID
							
							uart1_putc(HESPD_TXID);
							uart1_puts_p(PSTR(","));
							utoa(spdhe.avg_speed,MAV_Rx_buff,10);
							uart1_puts(MAV_Rx_buff);						//avg. speed
							uart1_puts_p(PSTR(","));						//delim
							utoa(spdhe.hes_speed,MAV_Rx_buff,10);
							uart1_puts(MAV_Rx_buff);			//used as status flags
							uart1_puts_p(PSTR(","));	
							utoa(spdhe.hes_RPM,MAV_Rx_buff,10);
							uart1_puts(MAV_Rx_buff);	
							uart1_puts_p(PSTR(","));	
							utoa(spdhe.motor_speed,MAV_Rx_buff,10);
							uart1_puts(MAV_Rx_buff);
							uart1_puts_p(PSTR(","));	
							utoa(spdhe.motor_RPM,MAV_Rx_buff,10);
							uart1_puts(MAV_Rx_buff);
							uart1_puts_p(PSTR(","));	
							utoa(spdhe.flags,MAV_Rx_buff,10);
							uart1_puts(MAV_Rx_buff);
							uart1_puts_p(PSTR("<<"));
														
							break;//now check for next ID
							}break;
							
						////now check for next ID
							//case MAVLINK_MSG_ID_BMS_DATA:					//is it BMS data?
							//{
								//hb_lost=0;
								//uart1_flush();
								//mavlink_bms_data_t bms;
								//mavlink_msg_bms_data_decode(&msg,&bms);	//decode BMS data packet
								//uart1_puts_p(PSTR("BMS>>"));					//delim and ID
								//uart1_putc(BMS_TXID);	
								//uart1_puts_p(PSTR(","));
								////--------------BMS data  begin-----------//
								//uart1_putc(bms.fault_condition);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(bms.source_current);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(bms.load_current);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(bms.bat_fan_status);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(bms.LLIM_state);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(bms.HLIM_state);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(bms.state_of_chg);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(bms.pack_voltage);
								//uart1_puts_p(PSTR(","));
								//for (int i=0;i<3;i++)
								//{
									//uart1_putc(bms.cell_voltages[i]);	
									//uart1_puts_p(PSTR(","));	
								//}
								//for (int i=0;i<3;i++)
								//{
									//uart1_putc(bms.cell_temps[i]);
									//uart1_puts_p(PSTR(","));
								//}
								//uart1_putc(bms.system_status);
								//uart1_puts_p(PSTR("<<"));	
								//break;				
							//}break;
							//
							//case MAVLINK_MSG_ID_ACCELO_GYRO:				//is it accelorometer data?
							//{
								//hb_lost=0;
								//uart1_flush();
								//mavlink_accelo_gyro_t ac;
								//mavlink_msg_accelo_gyro_decode(&msg,&ac);
								//uart1_puts_p(PSTR("AC>>"));
								//uart1_putc(AC_TXID);		
								//uart1_putc(ac.acceleration);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(ac.incline);
								//uart1_puts_p(PSTR("<<"));
								//break;
							//}break;
							//
							//case MAVLINK_MSG_ID_MPPT1_DATA:				//is it MPPT1 data?
							//{
								//hb_lost=0;
								//uart1_flush();
								//mavlink_mppt1_data_t m1;
								//mavlink_msg_mppt1_data_decode(&msg,&m1);
								//uart1_puts_p(PSTR("M1>>"));
								//uart1_putc(MPPT1_TXID);
								//uart1_puts_p(PSTR(","));		
								//uart1_putc(m1.voltage_in);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m1.current_in);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m1.overtemp);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m1.undervolt);
								//uart1_puts_p(PSTR("<<"));
								//break;
							//}break;
							//
							//case MAVLINK_MSG_ID_MPPT2_DATA:				//is it MPPT1 data?
							//{
								//hb_lost=0;
								//uart1_flush();
								//mavlink_mppt2_data_t m2;
								//mavlink_msg_mppt1_data_decode(&msg,&m2);
								//uart1_puts_p(PSTR("M2>>"));
								//uart1_putc(MPPT2_TXID);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m2.voltage_in);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m2.current_in);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m2.overtemp);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m2.undervolt);
								//uart1_puts_p(PSTR("<<"));
								//break;
							//}break;
							//
							//case MAVLINK_MSG_ID_MPPT3_DATA:				//is it MPPT1 data?
							//{
								//hb_lost=0;
								//uart1_flush();
								//mavlink_mppt3_data_t m3;
								//mavlink_msg_mppt1_data_decode(&msg,&m3);
								//uart1_puts_p(PSTR("M3>>"));
								//uart1_putc(MPPT3_TXID);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m3.voltage_in);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m3.current_in);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m3.overtemp);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m3.undervolt);
								//uart1_puts_p(PSTR("<<"));
								//break;
							//}break;
							//
							//case MAVLINK_MSG_ID_MPPT4_DATA:				//is it MPPT1 data?
							//{
								//hb_lost=0;
								//uart1_flush();
								//mavlink_mppt4_data_t m4;
								//mavlink_msg_mppt1_data_decode(&msg,&m4);
								//uart1_puts_p(PSTR("M4>>"));
								//uart1_putc(MPPT4_TXID);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m4.voltage_in);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m4.current_in);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m4.overtemp);
								//uart1_puts_p(PSTR(","));
								//uart1_putc(m4.undervolt);
								//uart1_puts_p(PSTR("<<"));
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

#pragma endregion

#pragma region ISRs

	ISR(ADC_vect)
	{
		myFlags.ADC_read_complete = 1;
		voltage = ADC;
		//testBlink(slow_blink);
		//ADCSRA &= ~(1<<ADIE);
	}

	ISR(TIMER3_CAPT_vect)
	{
		sum_capture += ICR3;//add ICR value to sum of captures
		TCNT3 = 0;//clear timer so ICR value always starts at 0
		count_capture++;//increment count of captures
		if (count_capture == MAX_CAPTURE)//if Max Captures were reached (max captures = 15)
		{
			myFlags.ICP_ready = 1;//set flag indicating ready to average values
		}
	}

	ISR(TIMER3_OVF_vect)
	{
		myFlags.ICP_ready = 1;
		count_capture++;
		sum_capture = 0xFFFF;
	}

#pragma endregion
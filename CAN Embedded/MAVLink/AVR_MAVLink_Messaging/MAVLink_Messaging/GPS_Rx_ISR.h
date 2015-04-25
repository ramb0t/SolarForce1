/*
 * GPS_Rx_ISR.h
 *
 * Created: 2015/04/25 12:25:18 AM
 *  Author: Matt
 */ 


#ifndef GPS_RX_ISR_H_
#define GPS_RX_ISR_H_

//---------------Includes & Defines---------//
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//---------------Variables---------------//
volatile uint8_t		updateGPS_flag;		//flag to know whether MAVLink packet to be sent
volatile uint8_t		gps_needs_sending;
extern volatile uint16_t 	gMilliSecTick;
extern volatile uint16_t	ms_Counter;
extern volatile uint16_t	old_mS;


//---------------Prototypes---------------//
void Timer0_init(void);
void GPS_readData(void);
void GPSParse();



#endif /* GPS_RX_ISR_H_ */
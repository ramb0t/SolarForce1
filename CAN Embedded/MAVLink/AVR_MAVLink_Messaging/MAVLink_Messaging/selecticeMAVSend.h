/*
 * selecticeMAVSend.h
 *
 * Created: 2015/04/25 03:02:39 AM
 *  Author: Matt
 */ 


#ifndef SELECTICEMAVSEND_H_
#define SELECTICEMAVSEND_H_
//---------------Includes and defines---------------//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <stdbool.h>
#include "../lib/uart/uart.h"					//UART library

#include "mavlink_bridge_header.h"  //UART & convenience headers

//---------------Variables---------------//
extern volatile	uint8_t		speedUpdated;
extern volatile	uint8_t		acceloUpdated;
extern volatile	uint8_t		gyroUpdated;

extern volatile	uint8_t		bms1Updated;
extern volatile	uint8_t		bms2Updated;
extern volatile	uint8_t		bms3Updated;
extern volatile	uint8_t		bms4Updated;
extern volatile	uint8_t		bms5Updated;
extern volatile	uint8_t		bms6Updated;
extern volatile	uint8_t		bms7Updated;
extern volatile	uint8_t		bms8Updated;

extern volatile	uint8_t		mppt1Updated;
extern volatile	uint8_t		mppt2Updated;
extern volatile	uint8_t		mppt3Updated;
extern volatile	uint8_t		mppt4Updated;

//------------Function Prototypes------------------------//

void selectiveSend();

//------------MAVlink convenience functions--------------//

mavlink_status_t* mavlink_get_channel_status(uint8_t chan);
mavlink_message_t* mavlink_get_channel_buffer(uint8_t chan);


#endif /* SELECTICEMAVSEND_H_ */
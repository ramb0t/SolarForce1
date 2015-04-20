/*
 * mcp2515_cmds.h
 *
 *  Created on: 21 Feb 2015
 *      Author: RobThePyro
 */

#ifndef MCP2515_CMDS_H_
#define MCP2515_CMDS_H_

/* Includes: */
#include <avr/io.h>
#include <util/delay.h>
#include "mcp2515_defs.h"
#include "AVR_SPI.h"

/* Defines: */

#define DDR_CS DDRB
#define PORT_CS PORTB
#define P_CS 2

#define DDR_SPI DDRB
#define PORT_SPI PORTB
#define P_MISO 4
#define P_MOSI 3
#define P_SCK 5


typedef struct
{
uint16_t id;
uint8_t rtr;
uint8_t length;
uint8_t data [ 8 ] ;
} CANMessage;

// CAN Bitrate 125 kbps
#define R_CNF1 (1<<BRP2)|(1<<BRP1)|(1<<BRP0)
#define R_CNF2 (1<<BTLMODE)|(1<<PHSEG11)
#define R_CNF3 (1<<PHSEG21)

/* Functions: */
void mcp2515_init ( void );
void mcp2515_write_register ( uint8_t , uint8_t );
uint8_t mcp2515_read_register ( uint8_t );
void mcp2515_bit_modify ( uint8_t , uint8_t , uint8_t );
void can_send_message ( CANMessage *);


#endif /* MCP2515_CMDS_H_ */

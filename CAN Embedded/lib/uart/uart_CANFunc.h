/*
 * uart_CANFunc.h
 *
 *  Created on: 01 Apr 2015
 *      Author: rambo
 */

#ifndef UART_CANFUNC_H
#define UART_CANFUNC_H


// Includes:
/*****************************************************************************/
#include <avr/io.h>


// Project Specific
#include "../CAN/CAN.h"
#include "../mcp2515/mcp2515.h"


// Function Prototypes:
/*****************************************************************************/
void uart_SendCANMsg(CANMessage * msg);

#endif // UART_CANFUNC_H

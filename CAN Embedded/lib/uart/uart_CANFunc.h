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
#include <stdlib.h>
#include <string.h>


// Project Specific
#include "uart.h"
#include "../CAN/CAN.h"
#include "../mcp2515/mcp2515.h"


// Function Prototypes:
/*****************************************************************************/
void uart_SendCANMsg(CANMessage* message);

#endif // UART_CANFUNC_H

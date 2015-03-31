/*
 * GFX_LCD.h
 *
 *  Created on: 21 Mar 2015
 *      Author: RobThePyro
 */

#ifndef GFX_LCD_H_
#define GFX_LCD_H_

#include "u8glib/src/u8g.h"
#include "../lib/CAN/CAN.h" // CANMessage Struct?
#include <string.h>
#include <avr/io.h>

void u8g_setup();
void u8g_prepare();
void GFX_LCD_Draw(CANMessage);
void draw(CANMessage);

#endif /* GFX_LCD_H_ */

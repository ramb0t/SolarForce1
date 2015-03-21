/*
 * GFX_LCD.h
 *
 *  Created on: 21 Mar 2015
 *      Author: RobThePyro
 */

#ifndef GFX_LCD_H_
#define GFX_LCD_H_

#include "u8glib/src/u8g.h"
#include "mcp2515_cmds.h"
#include "string.h"

void u8g_setup();
void u8g_prepare();
void GFX_LCD_Draw(CANMessage);
void draw(CANMessage);

#endif /* GFX_LCD_H_ */

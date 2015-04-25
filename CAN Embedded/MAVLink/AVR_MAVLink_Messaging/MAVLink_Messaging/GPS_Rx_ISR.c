/*
 * GPS_Rx_ISR.c
 *
 * Created: 2015/04/25 12:24:57 AM
 *  Author: Matt
 */ 

#include "GPS_Rx_ISR.h"

ISR(USART_RX_vect)
{
	if (uart_available())		//make sure UART is actually from GPS
	{
		updateGPS_flag = TRUE;
	}
}
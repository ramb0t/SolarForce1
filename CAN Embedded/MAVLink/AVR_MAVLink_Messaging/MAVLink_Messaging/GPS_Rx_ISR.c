/*
 * GPS_Rx_ISR.c
 *
 * Created: 2015/04/25 12:24:57 AM
 *  Author: Matt
 */ 

/* GPS Receive ISR
	Purpose: Currently, none.
	Reason: an Rx ISR cannot be used because of the multiplexing
			of the UART library receive routine making use of the Rx ISR
	Resolution: if the UART library is modified or the UART line muxed
				this routine may be used to receive characters from the GPS.

 */
#include "GPS_Rx_ISR.h"

//ISR(USART_RX_vect)
//{
//
		//updateGPS_flag = 1;
//}
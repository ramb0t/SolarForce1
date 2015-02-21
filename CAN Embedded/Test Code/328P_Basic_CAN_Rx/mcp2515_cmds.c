/*
 * mcp2515_cmds.c
 *
 *  Created on: 21 Feb 2015
 *      Author: RobThePyro
 */
#include "mcp2515_cmds.h"

void mcp2515_write_register ( uint8_t adress, uint8_t data )
{
// /CS des MCP2515 auf Low ziehen
PORT_CS &= ~ ( 1 <<P_CS ) ;

spi_putc ( SPI_WRITE ) ;
spi_putc ( adress ) ;
spi_putc ( data ) ;

// /CS Leitung wieder freigeben
PORT_CS |= ( 1 <<P_CS ) ;
}

uint8_t mcp2515_read_register ( uint8_t adress )
{
uint8_t data;

// /CS des MCP2515 auf Low ziehen
PORT_CS &= ~ ( 1 <<P_CS ) ;

spi_putc ( SPI_READ ) ;
spi_putc ( adress ) ;

data = spi_putc ( 0xff ) ;

// /CS Leitung wieder freigeben
PORT_CS |= ( 1 <<P_CS ) ;

return data;
}

void mcp2515_bit_modify ( uint8_t adress, uint8_t mask, uint8_t data )
{
// /CS des MCP2515 auf Low ziehen
PORT_CS &= ~ ( 1 <<P_CS ) ;

spi_putc ( SPI_BIT_MODIFY ) ;
spi_putc ( adress ) ;
spi_putc ( mask ) ;
spi_putc ( data ) ;

// /CS Leitung wieder freigeben
PORT_CS |= ( 1 <<P_CS ) ;
}

void mcp2515_init ( void )
{

	// MCP2515 per Software Reset zuruecksetzten,
	// danach ist der MCP2515 im Configuration Mode
	PORT_CS &= ~ ( 1 <<P_CS ) ;
	spi_putc ( SPI_RESET ) ;
	_delay_ms ( 1 ) ;
	PORT_CS |= ( 1 <<P_CS ) ;

	// etwas warten bis sich der MCP2515 zurueckgesetzt hat
	_delay_ms ( 10 ) ;

	/*
	* Einstellen des Bit Timings
	*
	* Fosc = 16MHz
	* BRP = 7 (teilen durch 8)
	* TQ = 2 * (BRP + 1) / Fosc (=> 1 uS)
	*
	* Sync Seg = 1TQ
	* Prop Seg = (PRSEG + 1) * TQ = 1 TQ
	* Phase Seg1 = (PHSEG1 + 1) * TQ = 3 TQ
	* Phase Seg2 = (PHSEG2 + 1) * TQ = 3 TQ
	*
	* Bus speed = 1 / (Total # of TQ) * TQ
	* = 1 / 8 * TQ = 125 kHz
	*/

	// BRP = 7
	mcp2515_write_register ( CNF1, ( 1 <<BRP0 ) | ( 1 <<BRP1 ) | ( 1 <<BRP2 ) ) ;

	// Prop Seg und Phase Seg1 einstellen
	mcp2515_write_register ( CNF2, ( 1 <<BTLMODE ) | ( 1 <<PHSEG11 ) ) ;

	// Wake-up Filter deaktivieren, Phase Seg2 einstellen
	mcp2515_write_register ( CNF3, ( 1 <<PHSEG21 ) ) ;

	// Aktivieren der Rx Buffer Interrupts
	mcp2515_write_register ( CANINTE, ( 1 <<RX1IE ) | ( 1 <<RX0IE ) ) ;

	/*
	* Einstellen der Filter
	*/

	// Buffer 0 : Empfangen aller Nachrichten
	mcp2515_write_register ( RXB0CTRL, ( 1 <<RXM1 ) | ( 1 <<RXM0 ) ) ;

	// Buffer 1 : Empfangen aller Nachrichten
	mcp2515_write_register ( RXB1CTRL, ( 1 <<RXM1 ) | ( 1 <<RXM0 ) ) ;

	// Alle Bits der Empfangsmaske loeschen,
	// damit werden alle Nachrichten empfangen
	mcp2515_write_register ( RXM0SIDH, 0 ) ;
	mcp2515_write_register ( RXM0SIDL, 0 ) ;
	mcp2515_write_register ( RXM0EID8, 0 ) ;
	mcp2515_write_register ( RXM0EID0, 0 ) ;

	mcp2515_write_register ( RXM1SIDH, 0 ) ;
	mcp2515_write_register ( RXM1SIDL, 0 ) ;
	mcp2515_write_register ( RXM1EID8, 0 ) ;
	mcp2515_write_register ( RXM1EID0, 0 ) ;

	/*
	* Einstellen der Pin Funktionen
	*/

	// Deaktivieren der Pins RXnBF Pins (High Impedance State)
	mcp2515_write_register ( BFPCTRL, 0 ) ;

	// TXnRTS Bits als Inputs schalten
	mcp2515_write_register ( TXRTSCTRL, 0 ) ;

	// Device zurueck in den normalen Modus versetzten
	mcp2515_bit_modify ( CANCTRL, 0xE0, 0 ) ;
}

void can_send_message ( CANMessage *p_message )
{
uint8_t length = p_message->length;

// ID einstellen
mcp2515_write_register ( TXB0SIDH, ( uint8_t ) ( p_message->id>> 3 ) ) ;
mcp2515_write_register ( TXB0SIDL, ( uint8_t ) ( p_message->id<< 5 ) ) ;

// Ist die Nachricht ein "Remote Transmit Request"
if ( p_message->rtr )
{
/* Eine RTR Nachricht hat zwar eine Laenge,
aber keine Daten */

// Nachrichten Laenge + RTR einstellen
mcp2515_write_register ( TXB0DLC, ( 1 <<RTR ) | length ) ;
}
else
{
// Nachrichten Laenge einstellen
mcp2515_write_register ( TXB0DLC, length ) ;

// Daten
for ( uint8_t i= 0 ;i<length;i++ ) {
mcp2515_write_register ( TXB0D0 + i, p_message->data [ i ] ) ;
}
}

// CAN Nachricht verschicken
PORT_CS &= ~ ( 1 <<P_CS ) ;
spi_putc ( SPI_RTS | 0x01 ) ;
PORT_CS |= ( 1 <<P_CS ) ;
}

uint8_t mcp2515_read_rx_status (void)
{
	uint8_t data;

	// Draw / CS of the MCP2515 to Low
	PORT_CS &=~ (1 << P_CS);

	spi_putc (SPI_RX_STATUS);
	data = spi_putc (0xff);

	// The data is sent again repeated,
	// You needed only one of the two bytes evaluate.
	spi_putc (0xff);

	//Unlock / CS line
	PORT_CS |= (1 << P_CS);

	return data;
}

uint8_t can_get_message (CANMessage *p_message)
{
	// Read status
	uint8_t status = mcp2515_read_rx_status ();
	PORTB &=~(1<<PORTB1);

	if (bit_is_set (status, 6))
	{
		// Message in buffer 0

		PORT_CS &=~ (1 << P_CS); // CS Low
		spi_putc (SPI_READ_RX);
	}
	else if (bit_is_set (status,7))
	{
		// Message in buffer 1

		PORT_CS &=~ (1 << P_CS); // CS Low
		spi_putc (SPI_READ_RX | 0x04);
	}
	else {
		/* Error: No new message is present */
		return 0xff;
	}

	// Read the standard ID
	p_message-> id = (uint16_t) spi_putc (0xff) << 3;
	p_message-> id |= (uint16_t) spi_putc (0xff) >> 5;

	spi_putc (0xff);
	spi_putc (0xff);

	// Read length
	uint8_t length = spi_putc (0xff) & 0x0f;
	p_message-> length = length;

	// Read the data
	for (uint8_t i = 0; i <length; i ++) {
		p_message-> data [i] = spi_putc (0xff);
	}

	PORT_CS |= (1 << P_CS);

	if (bit_is_set (status, 3)) {
		p_message-> rtr = 1;
		} else {
		p_message-> rtr = 0;
	}

	//delete Interrupt Flag
	if (bit_is_set (status, 6)) {
		mcp2515_bit_modify (CANINTF, (1 << RX0IF), 0);
		} else {
		mcp2515_bit_modify (CANINTF, (1 << RX1IF), 0);
	}

	return (status & 0x07);
}


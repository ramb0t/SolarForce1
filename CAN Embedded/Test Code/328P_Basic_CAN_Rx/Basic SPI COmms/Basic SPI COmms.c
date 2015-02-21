
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "mcp2515_defs.h"


#define PORT_CS		PORTB
#define DDR_CS		DDRB
#define P_CS		2

#define DDR_SPI		DDRB
#define PORT_SPI	PORTB
#define P_MISO		4
#define P_MOSI		3
#define P_SCK		5

// CAN bit rate 125 kbps
#define R_CNF1 (1 << BRP2) | (1 << BRP1) | (1 << BRP0)
#define R_CNF2 (1 << BTLMODE) | (1 << PHSEG11)
#define R_CNF3 (1 << PHSEG21)

	typedef struct
	{
		uint16_t id;
		uint8_t rtr;
		uint8_t length;
		uint8_t data [8];
	} CanMessage;

void spi_init (void) //init SPI interface
{
	DDR_SPI |= (1<<P_SCK)|(1<<P_MOSI);
	PORT_SPI&=~((1<<P_SCK)|(1<<P_MOSI)|(1<<P_MISO));
	DDR_CS|=(1<<P_CS);
	PORT_CS|=(1<<P_CS);  //SPI Master, fosc = fclk/2
	SPCR=(1<<SPE)|(1<<MSTR);
	SPSR=(1<<SPI2X);
}

uint8_t spi_putc(uint8_t data)
{
	SPDR = data; 
	while (!(SPSR & (1<<SPIF)));
	return SPDR;
}

void mcp2515_write_reg(uint8_t address, uint8_t data )
{
	//CS of the MP2515 to pull low
	PORT_CS &= ~(1<<P_CS);
	
	spi_putc(SPI_WRITE);
	spi_putc(address);
	spi_putc(data);
	
	//Unlock CS Line
	PORT_CS |= (1<<P_CS);
}

uint8_t mcp2515_read_reg(uint8_t address)
{
	uint8_t data;
	// Draw / CS of the MCP2515 to Low
	PORT_CS &=~ (1 << P_CS);

	spi_putc (SPI_READ);
	spi_putc (address);

	data = spi_putc (0xff);

	//Unlock  CS line
	PORT_CS |= (1 << P_CS);

	return data;
}

void mcp2515_bit_modify (uint8_t adress, uint8_t mask, uint8_t data)
{
	// Draw / CS of the MCP2515 to Low
	PORT_CS &= ~ (1 << P_CS);

	spi_putc (SPI_BIT_MODIFY);
	spi_putc (adress);
	spi_putc (mask);
	spi_putc (data);

	//Unlock / CS line
	PORT_CS |= (1 << P_CS);
}



void can_send_message (CanMessage *p_message)
{
	uint8_t length = p_message->length;

	// Set ID
	mcp2515_write_reg (TXB0SIDH, (uint8_t) (p_message-> id >> 3));
	mcp2515_write_reg (TXB0SIDL, (uint8_t) (p_message-> id << 5));

	// If the message is a "Remote Transmit Request"
	if (p_message-> rtr)
	{
		//Although / * A RTR message has a length,
		//but no data * /

		// Set message length + RTR
		mcp2515_write_reg (TXB0DLC, (1 << RTR) | length);
	}
	else
	{
		// Set message length
		mcp2515_write_reg (TXB0DLC, length);

		// Data
		for (uint8_t i = 0; i <length; i ++) {
			mcp2515_write_reg (TXB0D0 + i, p_message-> data [i]);
		}
	}

	// Send CAN message
	PORT_CS &=~ (1 << P_CS);
	spi_putc (SPI_RTS | 0x01);
	PORT_CS |= (1 << P_CS);
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


uint8_t can_get_message (CanMessage *p_message)
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

void mcp2515_init ( void )
{
	// SPI Interface initialisieren
	spi_init ( ) ;

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
	mcp2515_write_reg ( CNF1, ( 1 <<BRP0 ) | ( 1 <<BRP1 ) | ( 1 <<BRP2 ) ) ;

	// Prop Seg und Phase Seg1 einstellen
	mcp2515_write_reg ( CNF2, ( 1 <<BTLMODE ) | ( 1 <<PHSEG11 ) ) ;

	// Wake-up Filter deaktivieren, Phase Seg2 einstellen
	mcp2515_write_reg ( CNF3, ( 1 <<PHSEG21 ) ) ;

	// Aktivieren der Rx Buffer Interrupts
	mcp2515_write_reg ( CANINTE, ( 1 <<RX1IE ) | ( 1 <<RX0IE ) ) ;

	/*
	* Einstellen der Filter
	*/

	// Buffer 0 : Empfangen aller Nachrichten
	mcp2515_write_reg ( RXB0CTRL, ( 1 <<RXM1 ) | ( 1 <<RXM0 ) ) ;

	// Buffer 1 : Empfangen aller Nachrichten
	mcp2515_write_reg ( RXB1CTRL, ( 1 <<RXM1 ) | ( 1 <<RXM0 ) ) ;

	// Alle Bits der Empfangsmaske loeschen,
	// damit werden alle Nachrichten empfangen
	mcp2515_write_reg ( RXM0SIDH, 0 ) ;
	mcp2515_write_reg ( RXM0SIDL, 0 ) ;
	mcp2515_write_reg ( RXM0EID8, 0 ) ;
	mcp2515_write_reg ( RXM0EID0, 0 ) ;

	mcp2515_write_reg ( RXM1SIDH, 0 ) ;
	mcp2515_write_reg ( RXM1SIDL, 0 ) ;
	mcp2515_write_reg ( RXM1EID8, 0 ) ;
	mcp2515_write_reg ( RXM1EID0, 0 ) ;

	/*
	* Einstellen der Pin Funktionen
	*/

	// Deaktivieren der Pins RXnBF Pins (High Impedance State)
	mcp2515_write_reg ( BFPCTRL, 0 ) ;

	// TXnRTS Bits als Inputs schalten
	mcp2515_write_reg ( TXRTSCTRL, 0 ) ;

	// Device zurueck in den normalen Modus versetzten
	mcp2515_bit_modify ( CANCTRL, 0xE0, 0 ) ;
}


int main(void)
{
	DDRB |=(1<<PORTB1);
	spi_init();
	mcp2515_init();
	// Create a new message
	CanMessage message;
	uint8_t rx_status = 0x00;
	
while(1)
	{	
		for(int a = 0; a<1; a++)
		{
			PORTB |= (1<<PORTB1);
			_delay_ms(50);
			PORTB &=~(1<<PORTB1);
			_delay_ms(50);
		}


	DDRB |=(1<<PORTB1);
	do {
		//_delay_ms(1000);	
	
		PORTB |= (1<<PORTB1);
		_delay_ms(100);
		PORTB &=~(1<<PORTB1);
		_delay_ms(50);
		PORTB |= (1<<PORTB1);
	
		rx_status = can_get_message (&message); //gets msg from bus (pointer to the object of CanMessage type) [returns value based on result of Rx

	} while(rx_status == 0xff);


	if (message.data[0] == 0x04 && message.data[1]==0xf3)
		{
			for(int a = 0; a<20; a++)
			{
				DDRB |=(1<<PORTB1);
				PORTB |= (1<<PORTB1);
				_delay_ms(200);
				PORTB &=~(1<<PORTB1);
				_delay_ms(200);
			}
		}
else PORTB |= (1<<PORTB1);
//PORTB |= (1<<PORTB1);

}

	
//// Enable the Rx buffer interrupts
//mcp2515_write_reg(CANINTE, (1 << RX1IE) | (1 << RX0IE));
//
//// Use RX0BF as digital output
//mcp2515_bit_modify (BFPCTRL, (1 << B0BFE) | (1 << B0BFM), (1 << B0BFE));
//
//// Set pin
//mcp2515_bit_modify (BFPCTRL, (1 << B0BFE), (1 << B0BFE));
//
//// Use RX0BF and RX1BF as interrupt outputs
//mcp2515_write_reg (BFPCTRL, (1 << B1BFE) | (1 << B0BFE) | (1 << B1BFM) | (1 << B0BFM));

// Prescaler of the CLKOUT pin set to zero,
// => Output clock frequency of the MCP2515 on the CLKOUT pin

//mcp2515_bit_modify (CANCTRL, 0x07, (1 << CLKEN));


}


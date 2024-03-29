/*
 * I2C.h
 *
 * Created: 11/04/2015 10:59:18 PM
 *  Author: Terayza
 */ 


#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL

#define TRUE 1
#define FALSE 0

#include <avr/interrupt.h>

//#include "General.h"
//#include "TWI_Master.h"

/****************************************************************************
  TWI State codes
****************************************************************************/
// General TWI Master staus codes                      
#define TWI_START                    0x08  // START has been transmitted  
#define TWI_REP_START                0x10  // Repeated START has been transmitted
#define TWI_ARB_LOST                0x38  // Arbitration lost

// TWI Master Transmitter staus codes                      
#define TWI_MTX_ADR_ACK                0x18  // SLA+W has been tramsmitted and ACK received
#define TWI_MTX_ADR_NACK            0x20  // SLA+W has been tramsmitted and NACK received 
#define TWI_MTX_DATA_ACK            0x28  // Data byte has been tramsmitted and ACK received
#define TWI_MTX_DATA_NACK            0x30  // Data byte has been tramsmitted and NACK received 

// TWI Master Receiver staus codes  
#define TWI_MRX_ADR_ACK                0x40  // SLA+R has been tramsmitted and ACK received
#define TWI_MRX_ADR_NACK            0x48  // SLA+R has been tramsmitted and NACK received
#define TWI_MRX_DATA_ACK            0x50  // Data byte has been received and ACK tramsmitted
#define TWI_MRX_DATA_NACK            0x58  // Data byte has been received and NACK tramsmitted

// TWI Slave Transmitter staus codes
#define TWI_STX_ADR_ACK                0xA8  // Own SLA+R has been received; ACK has been returned
#define TWI_STX_ADR_ACK_M_ARB_LOST    0xB0  // Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been returned
#define TWI_STX_DATA_ACK            0xB8  // Data byte in TWDR has been transmitted; ACK has been received
#define TWI_STX_DATA_NACK            0xC0  // Data byte in TWDR has been transmitted; NOT ACK has been received
#define TWI_STX_DATA_ACK_LAST_BYTE    0xC8  // Last data byte in TWDR has been transmitted (TWEA = �0�); ACK has been received

// TWI Slave Receiver staus codes
#define TWI_SRX_ADR_ACK                0x60  // Own SLA+W has been received ACK has been returned
#define TWI_SRX_ADR_ACK_M_ARB_LOST    0x68  // Arbitration lost in SLA+R/W as Master; own SLA+W has been received; ACK has been returned
#define TWI_SRX_GEN_ACK                0x70  // General call address has been received; ACK has been returned
#define TWI_SRX_GEN_ACK_M_ARB_LOST    0x78  // Arbitration lost in SLA+R/W as Master; General call address has been received; ACK has been returned
#define TWI_SRX_ADR_DATA_ACK        0x80  // Previously addressed with own SLA+W; data has been received; ACK has been returned
#define TWI_SRX_ADR_DATA_NACK        0x88  // Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
#define TWI_SRX_GEN_DATA_ACK        0x90  // Previously addressed with general call; data has been received; ACK has been returned
#define TWI_SRX_GEN_DATA_NACK        0x98  // Previously addressed with general call; data has been received; NOT ACK has been returned
#define TWI_SRX_STOP_RESTART        0xA0  // A STOP condition or repeated START condition has been received while still addressed as Slave

// TWI Miscellaneous status codes
#define TWI_NO_STATE                0xF8  // No relevant state information available; TWINT = �0�
#define TWI_BUS_ERROR                0x00  // Bus error due to an illegal START or STOP condition

#define TWIM_READ    1
#define TWIM_WRITE   0

/*******************************************************
 Public Function: TWIM_Init

 Purpose: Initialise the TWI Master Interface

 Input Parameter:
     - uint16_t    TWI_Bitrate (Hz)

 Return Value: uint8_t
     - FALSE:    Bitrate too high
     - TRUE:        Bitrate OK

*******************************************************/
uint8_t TWIM_Init (uint32_t TWI_Bitrate)
    {
/*
** Set TWI bitrate
** If bitrate is too high, then error return
*/
    TWBR = ((F_CPU/TWI_Bitrate)-16)/2;
    if (TWBR < 11) return FALSE;

    return TRUE;
    }
/*******************************************************
 Public Function: TWIM_Start

 Purpose: Start the TWI Master Interface

 Input Parameter:
     - uint8_t    Device address
     - uint8_t    Type of required Operation:
                TWIM_READ: Read data from the slave
                TWIM_WRITE: Write data to the slave

 Return Value: uint8_t
      - TRUE:        OK, TWI Master accessible
     - FALSE:    Error in starting TWI Master

*******************************************************/
uint8_t TWIM_Start (uint8_t Address, uint8_t TWIM_Type)//1 = read, 0 = write
    {
		
    uint8_t        twst;
	
/*
** Send START condition
*/
	
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	//PORTC |= (1<< PORTC3);
	PORTC &= ~ (1<< PORTC2);
	
/*
** Wait until transmission completed
*/
    while (!(TWCR & (1<<TWINT)));

	PORTC &= ~(1<< PORTC3);
/*
** Check value of TWI Status Register. Mask prescaler bits.
*/
    twst = TWSR & 0xF8;
    if ((twst != TWI_START) && (twst != TWI_REP_START)) return FALSE;
/*
** Send device address
*/
    TWDR = (Address<<1) + TWIM_Type;
    TWCR = (1<<TWINT)|(1<<TWEN);
/*
** Wait until transmission completed and ACK/NACK has been received
*/
    while (!(TWCR & (1<<TWINT)));
/*
** Check value of TWI Status Register. Mask prescaler bits.
*/
    twst = TWSR & 0xF8;
    if ((twst != TWI_MTX_ADR_ACK) && (twst != TWI_MRX_ADR_ACK)) return FALSE;

    return TRUE;
    }
/*******************************************************
 Public Function: TWIM_Stop

 Purpose: Stop the TWI Master

 Input Parameter: None

 Return Value: None

*******************************************************/
void TWIM_Stop (void)
    {
/*
** Send stop condition
*/
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
/*
** Wait until stop condition is executed and bus released
*/
    while (TWCR & (1<<TWINT));
    }
/*******************************************************
 Public Function: TWIM_Write

 Purpose: Write a byte to the slave

 Input Parameter:
     - uint8_t    Byte to be sent

 Return Value: uint8_t
      - TRUE:        OK, Byte sent
     - FALSE:    Error in byte transmission

*******************************************************/
uint8_t TWIM_Write (uint8_t byte)
    {
    uint8_t   twst;
/*
** Send data to the previously addressed device
*/
    TWDR = byte;
    TWCR = (1<<TWINT)|(1<<TWEN);
/*
** Wait until transmission completed
*/
    while (!(TWCR & (1<<TWINT)));
/*
** Check value of TWI Status Register. Mask prescaler bits
*/
    twst = TWSR & 0xF8;
    if (twst != TWI_MTX_DATA_ACK) return 1;

    return 0;
    }
/*******************************************************
 Public Function: TWIM_ReadAck

 Purpose: Read a byte from the slave and request next byte

 Input Parameter: None

 Return Value: uint8_t
      - uint8_t    Read byte

*******************************************************/
uint8_t TWIM_ReadAck (void)
    {
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));    

    return TWDR;
    }
/*******************************************************
 Public Function: TWIM_ReadAck

 Purpose: Read the last byte from the slave

 Input Parameter: None

 Return Value: uint8_t
      - uint8_t    Read byte

*******************************************************/
uint8_t TWIM_ReadNack (void)
    {
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    
    return TWDR;
    }

#endif /* I2C_H_ */
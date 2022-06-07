/* 
 * File:   RS485.h
 * Author: ingenieria1
 *
 * Created on 2 de noviembre de 2016, 15:56
 */

#ifndef RS485_H
#define	RS485_H

#include "../../GeneralDefines.h"
#include "../../UART/UART.h"
#include "TX_ENABLE_PIO.h"

enum
{
//	RS485_SLV,
	RS485_MST,
	
	MAX_CHANNEL_RS485
};

#define RS485_UART	{INDEX_UART_5}

#define RS485_TRANSMIT_ENABLE_DIRECTION(u8Channel)     TX_ENABLE_struct = TX_ENABLE_PIO_Init((LDD_TUserData *)NULL);

#define RS485_TRANSMIT_ENABLE(u8Channel)               TX_ENABLE_PIO_SetVal(TX_ENABLE_struct);
#define RS485_TRANSMIT_DISABLE(u8Channel)              TX_ENABLE_PIO_ClrVal(TX_ENABLE_struct);


returnstatus_t RS485_Init(uint8_t u8Channel);

returnstatus_t RS485_Receive(uint8_t u8Channel, uint8* ptu8Dades, uint16 u16NumDades);

returnstatus_t RS485_Transmit(uint8_t u8Channel, uint8* ptu8Dades, uint16 u16NumDades, uint8 u8LastPacket);

uint32_t RS485_QuantsBytesBufferRX(uint8_t u8Channel);

void RS485_ResetBuffers(uint8_t u8Channel);



#endif	/* RS485_H */


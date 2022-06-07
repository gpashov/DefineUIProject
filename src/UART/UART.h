/*
 * UART.h
 *
 *  Created on: Nov 15, 2016
 *      Author: ingenieria1
 */

#ifndef UART_H_
#define UART_H_

//#include "PE_Types.h"
//#include "PE_Error.h"
#include "../GeneralDefines.h"

//#define	UART_0 INDEX_UART_0
//#define	UART_1 INDEX_UART_1
#define	UART_2 INDEX_UART_2
//#define	UART_3 INDEX_UART_3
#define	UART_4 INDEX_UART_4
#define	UART_5 INDEX_UART_5

typedef enum
{
#ifdef UART_0
	INDEX_UART_0,
#endif
#ifdef UART_1
	INDEX_UART_1,
#endif
#ifdef UART_2
	INDEX_UART_2,
#endif
#ifdef UART_3
	INDEX_UART_3,
#endif
#ifdef UART_4
	INDEX_UART_4,
#endif
#ifdef UART_5
	INDEX_UART_5,
#endif
	
	MAX_UARTS
}UART_nameTypeDef;

#define UART_MAX_BUFFER_RX	64//256//64	/* tamany del buffer circular de recepcio, HA DE SER POT DE 2 */


typedef struct
{
	void * HAL_StructPointer;
	uint8 ptu8BufferRx[UART_MAX_BUFFER_RX];

	uint16 u16PunterIniciRx; // Apunta a la posicio del primer caracter que s'ha rebut
	uint16 u16PunterFinalRx; // Apunta a la primera posicio lliure
	uint16 u16QuantsRx;

	uint8 u8OverflowRx;
	uint8 u8TXNotFinished;
}uart_control_t;


returnstatus_t UART_Init(uint8 u8Uart);
//Pre:  Cap
//Post: Inicialitza el canal Uart designat per u8Uart, amb els parametres seleccionats. Veure defines mes amunt. 1 stop bit, sense paritat, 8 bits.
//	Retorna 1 si tot es correcte, 0 en cas contrari.

void UART_DesactivaUart(uint8 u8Uart);
//Pre:  Cap
//Post: Deshabilita la Uart (ports i interrupcions)

uint16 UART_QuantsBytesBufferRX(uint8 u8Uart);
//Pre:  Haver cridat UART_Init
//Post: Retorna el numero de caracters rebuts, en disposicio en el buffer de rx, de la uart especificada.

returnstatus_t UART_Transmit(uint8 u8Uart,uint8* ptu8Dades, uint16 NumDades);
//Pre: Haver cridat	UART_Init
//Post: Coloca en el buffer de tx de la Uart especificada els "NumDades" caracters de la cadena "ptu8Dades"
//	Retorna 1 si tot es correcte, 0 en cas contrari (potser el buffer esta ple).

returnstatus_t UART_Receive(uint8 u8Uart,uint8* ptu8Dades, uint16 NumDades);
//Pre:  Haver cridat UART_Init
//Post: Coloca en ptu8Dades les "NumDades" mes antigues del buffer de rx.
//	Retorna 1 si tot es correcte, 0 en cas contrari (potser no hi ha tantes dades en el buffer)

void UART_ResetTX(uint8 u8Uart);
//Pre:	Haver cridat UART_Init
//	u8Uart ha de valer UART1 o bé UART2
//Post:	Reseteja el buffer de Tx

void UART_ResetRX(uint8 u8Uart);
//Pre:	Haver cridat UART_Init
//	u8Uart ha de valer UART1 o bé UART2
//Post:	Reseteja el buffer de Rx

uint8 UART_HiHaOverflow(uint8 u8Uart);
//Pre:	Haver cridat UART_Init
//	u8Uart ha de valer UART1 o bé UART2
//Post:	Retorna si hi ha error d'overflow del canal u8Uart

uint8 UART_TransmitNOTFinished(uint8 u8Uart);


// ISRs de la UART

void ISR_UART_TX_FINISHED (uint8 u8Uart);

void ISR_UART_RX (uint8 u8Uart);


#endif

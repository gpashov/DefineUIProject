/*
 * UART.c
 *
 *  Created on: Nov 15, 2016
 *      Author: ingenieria1
 */

#include "UART.h"
#ifdef UART_0
#include "HAL_UART_0.h"
#endif
#ifdef UART_1
#include "HAL_UART_1.h"
#endif
#ifdef UART_2
//#include "HAL_UART_2.h"
#endif
#ifdef UART_3
#include "HAL_UART_3.h"
#endif
#ifdef UART_4
//#include "HAL_UART_4.h"
#endif
#ifdef UART_5
//#include "HAL_UART_5.h"
#endif

uart_control_t uart_control[MAX_UARTS];

returnstatus_t UART_Init(uint8 u8Uart)
{
	
//	if(u8Uart >= MAX_UARTS)
//		return ERROR;
//	uart_control[u8Uart].HAL_StructPointer = (void *)NULL;
//	uart_control[u8Uart].u16PunterFinalRx = 0;
//	uart_control[u8Uart].u16PunterIniciRx = 0;
//	uart_control[u8Uart].u16QuantsRx = 0;
//	uart_control[u8Uart].u8OverflowRx = 0;
//	uart_control[u8Uart].u8TXNotFinished = 1;
//#ifdef UART_0
//	if(u8Uart == INDEX_UART_0)
//	{
//		uart_control[u8Uart].HAL_StructPointer = HAL_UART_0_Init((LDD_TUserData *)NULL);
//		if(uart_control[u8Uart].HAL_StructPointer == NULL)
//		{
//			return ERROR;
//		}
//		else
//		{
//			if(HAL_UART_0_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx, 1) == ERR_OK)
//			{
//				return SUCCESS;
//			}
//			else
//			{
//				return ERROR;
//			}
//		}
//	}
//#endif
//#ifdef UART_1
//	if(u8Uart == INDEX_UART_1)
//	{
//		uart_control[u8Uart].HAL_StructPointer = HAL_UART_1_Init((LDD_TUserData *)NULL);
//		if(uart_control[u8Uart].HAL_StructPointer == NULL)
//		{
//			return ERROR;
//		}
//		else
//		{
//			if(HAL_UART_1_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx, 1) == ERR_OK)
//			{
//				return SUCCESS;
//			}
//			else
//			{
//				return ERROR;
//			}
//		}
//	}
//#endif
//#ifdef UART_2
//	if(u8Uart == INDEX_UART_2)
//	{
//		uart_control[u8Uart].HAL_StructPointer = HAL_UART_2_Init((LDD_TUserData *)NULL);
//		if(uart_control[u8Uart].HAL_StructPointer == NULL)
//		{
//			return ERROR;
//		}
//		else
//		{
//			if(HAL_UART_2_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx, 1) == ERR_OK)
//			{
//				return SUCCESS;
//			}
//			else
//			{
//				return ERROR;
//			}
//		}
//	}
//#endif
//#ifdef UART_3
//	if(u8Uart == INDEX_UART_3)
//	{
//		uart_control[u8Uart].HAL_StructPointer = HAL_UART_3_Init((LDD_TUserData *)NULL);
//		if(uart_control[u8Uart].HAL_StructPointer == NULL)
//		{
//			return ERROR;
//		}
//		else
//		{
//			if(HAL_UART_3_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx, 1) == ERR_OK)
//			{
//				return SUCCESS;
//			}
//			else
//			{
//				return ERROR;
//			}
//		}
//	}
//#endif
//#ifdef UART_4
//	if(u8Uart == INDEX_UART_4)
//	{
//		uart_control[u8Uart].HAL_StructPointer = HAL_UART_4_Init((LDD_TUserData *)NULL);
//		if(uart_control[u8Uart].HAL_StructPointer == NULL)
//		{
//			return ERROR;
//		}
//		else
//		{
//			if(HAL_UART_4_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx, 1) == ERR_OK)
//			{
//				return SUCCESS;
//			}
//			else
//			{
//				return ERROR;
//			}
//		}
//	}
//#endif
//#ifdef UART_5
//	if(u8Uart == INDEX_UART_5)
//	{
//		uart_control[u8Uart].HAL_StructPointer = HAL_UART_5_Init((LDD_TUserData *)NULL);
//		if(uart_control[u8Uart].HAL_StructPointer == NULL)
//		{
//			return ERROR;
//		}
//		else
//		{
//			if(HAL_UART_5_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx, 1) == ERR_OK)
//			{
//				return SUCCESS;
//			}
//			else
//			{
//				return ERROR;
//			}
//		}
//	}
//#endif
	return ERROR;
}

void UART_DesactivaUart(uint8 u8Uart)
{
//	if(u8Uart > MAX_UARTS)
//		return;
//#ifdef UART_0
//	if(u8Uart == INDEX_UART_0)
//	{
//		HAL_UART_0_Deinit((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_1
//	if(u8Uart == INDEX_UART_1)
//	{
//		HAL_UART_1_Deinit((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_2
//	if(u8Uart == INDEX_UART_2)
//	{
//		HAL_UART_2_Deinit((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_3
//	if(u8Uart == INDEX_UART_3)
//	{
//		HAL_UART_3_Deinit((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_4
//	if(u8Uart == INDEX_UART_4)
//	{
//		HAL_UART_4_Deinit((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_5
//	if(u8Uart == INDEX_UART_5)
//	{
//		HAL_UART_5_Deinit((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//	uart_control[u8Uart].u16PunterFinalRx = 0;
//	uart_control[u8Uart].u16PunterIniciRx = 0;
//	uart_control[u8Uart].u16QuantsRx = 0;
//	uart_control[u8Uart].u8OverflowRx = 0;
//	uart_control[u8Uart].u8TXNotFinished = 1;
}

uint16 UART_QuantsBytesBufferRX(uint8 u8Uart)
{
	if(u8Uart > MAX_UARTS)
		return 0;
	return uart_control[u8Uart].u16QuantsRx;
}

returnstatus_t UART_Transmit(uint8 u8Uart,uint8* ptu8Dades, uint16 NumDades)
{
//	LDD_TError errorcode = NULL;
//	if(u8Uart > MAX_UARTS)
//		return ERROR;
	
//#ifdef UART_0
//	if(u8Uart == INDEX_UART_0)
//	{
//		errorcode = HAL_UART_0_SendBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, ptu8Dades, NumDades);
//	}
//#endif
//#ifdef UART_1
//	if(u8Uart == INDEX_UART_1)
//	{
//		errorcode = HAL_UART_1_SendBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, ptu8Dades, NumDades);
//	}
//#endif
//#ifdef UART_2
//	if(u8Uart == INDEX_UART_2)
//	{
//		errorcode = HAL_UART_2_SendBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, ptu8Dades, NumDades);
//	}
//#endif
//#ifdef UART_3
//	if(u8Uart == INDEX_UART_3)
//	{
//		errorcode = HAL_UART_3_SendBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, ptu8Dades, NumDades);
//	}
//#endif
//#ifdef UART_4
//	if(u8Uart == INDEX_UART_4)
//	{
//		errorcode = HAL_UART_4_SendBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, ptu8Dades, NumDades);
//	}
//#endif
//#ifdef UART_5
//	if(u8Uart == INDEX_UART_5)
//	{
//		errorcode = HAL_UART_5_SendBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, ptu8Dades, NumDades);
//	}
//#endif
//	if(errorcode == ERR_OK)
//	{
//		uart_control[u8Uart].u8TXNotFinished = 1;
//		errorcode = SUCCESS;
//	}
//	else
//	{
//		errorcode = ERROR;
//	}
    return (returnstatus_t)0;//errorcode;
}

returnstatus_t UART_Receive(uint8 u8Uart,uint8* ptu8Dades, uint16 NumDades)
{
	returnstatus_t temp;
	uint16 i;
	
	if(NumDades > uart_control[u8Uart].u16QuantsRx)
	{
		temp = ERROR;
	}
	else{
		for(i = 0; i < NumDades; i++)
		{
			ptu8Dades[i]=uart_control[u8Uart].ptu8BufferRx[uart_control[u8Uart].u16PunterIniciRx++];
			uart_control[u8Uart].u16PunterIniciRx = uart_control[u8Uart].u16PunterIniciRx&(UART_MAX_BUFFER_RX-1);
			uart_control[u8Uart].u16QuantsRx--;
		}
		temp = SUCCESS;
	}
	return temp;
}

void UART_ResetTX(uint8 u8Uart)
{
//#ifdef UART_0
//	if(u8Uart == INDEX_UART_0)
//	{
//		HAL_UART_0_CancelBlockTransmission((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_1
//	if(u8Uart == INDEX_UART_1)
//	{
//		HAL_UART_1_CancelBlockTransmission((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_2
//	if(u8Uart == INDEX_UART_2)
//	{
//		HAL_UART_2_CancelBlockTransmission((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_3
//	if(u8Uart == INDEX_UART_3)
//	{
//		HAL_UART_3_CancelBlockTransmission((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_4
//	if(u8Uart == INDEX_UART_4)
//	{
//		HAL_UART_4_CancelBlockTransmission((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//#ifdef UART_5
//	if(u8Uart == INDEX_UART_5)
//	{
//		HAL_UART_5_CancelBlockTransmission((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//	}
//#endif
//	uart_control[u8Uart].u8TXNotFinished = 1;
}

void UART_ResetRX(uint8 u8Uart)
{
	uart_control[u8Uart].u16PunterFinalRx = 0;
	uart_control[u8Uart].u16PunterIniciRx = 0;
	uart_control[u8Uart].u16QuantsRx = 0;
	uart_control[u8Uart].u8OverflowRx = 0;
//#ifdef UART_0
//	if(u8Uart == INDEX_UART_0)
//	{
//		HAL_UART_0_CancelBlockReception((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//		HAL_UART_0_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//	}
//#endif
//#ifdef UART_1
//	if(u8Uart == INDEX_UART_1)
//	{
//		HAL_UART_1_CancelBlockReception((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//		HAL_UART_1_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//	}
//#endif
//#ifdef UART_2
//	if(u8Uart == INDEX_UART_2)
//	{
//		HAL_UART_2_CancelBlockReception((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//		HAL_UART_2_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//	}
//#endif
//#ifdef UART_3
//	if(u8Uart == INDEX_UART_3)
//	{
//		HAL_UART_3_CancelBlockReception((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//		HAL_UART_3_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//	}
//#endif
//#ifdef UART_4
//	if(u8Uart == INDEX_UART_4)
//	{
//		HAL_UART_4_CancelBlockReception((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//		HAL_UART_4_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//	}
//#endif
//#ifdef UART_5
//	if(u8Uart == INDEX_UART_5)
//	{
//		HAL_UART_5_CancelBlockReception((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer);
//		HAL_UART_5_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//	}
//#endif
}

uint8 UART_HiHaOverflow(uint8 u8Uart)
{
	return uart_control[u8Uart].u8OverflowRx;
}

uint8 UART_TransmitNOTFinished(uint8 u8Uart)
{
	return uart_control[u8Uart].u8TXNotFinished;
}


// ISRs de la UART

void ISR_UART_TX (uint8 u8Uart)
{
	
}

void ISR_UART_TX_FINISHED (uint8 u8Uart)
{
	uart_control[u8Uart].u8TXNotFinished = 0;
}

void ISR_UART_RX (uint8 u8Uart)
{
//	if(uart_control[u8Uart].u16QuantsRx < UART_MAX_BUFFER_RX)
//	{
//		uart_control[u8Uart].u16PunterFinalRx = (uart_control[u8Uart].u16PunterFinalRx+1)&(UART_MAX_BUFFER_RX-1);
//		uart_control[u8Uart].u16QuantsRx++;
//#ifdef UART_0
//		if(u8Uart == INDEX_UART_0)
//		{
//			HAL_UART_0_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//		}
//#endif
//#ifdef UART_1
//		if(u8Uart == INDEX_UART_1)
//		{
//			HAL_UART_1_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//		}
//#endif
//#ifdef UART_2
//		if(u8Uart == INDEX_UART_2)
//		{
//			HAL_UART_2_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//		}
//#endif
//#ifdef UART_3
//		if(u8Uart == INDEX_UART_3)
//		{
//			HAL_UART_3_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//		}
//#endif
//#ifdef UART_4
//		if(u8Uart == INDEX_UART_4)
//		{
//			HAL_UART_4_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//		}
//#endif
//#ifdef UART_5
//		if(u8Uart == INDEX_UART_5)
//		{
//			HAL_UART_5_ReceiveBlock((LDD_TDeviceData *)uart_control[u8Uart].HAL_StructPointer, uart_control[u8Uart].ptu8BufferRx+uart_control[u8Uart].u16PunterFinalRx, 1);
//		}
//#endif
//	}
//	else
//	{
//		uart_control[u8Uart].u8OverflowRx = 1; // Hi ha error d'overflow.
//	}
}



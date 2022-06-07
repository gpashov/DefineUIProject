/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PE_LDD.h
**     Project     : QPExMainDeffine_V7790
**     Processor   : MK70FN1M0VMJ15
**     Version     : Component 01.028, Driver 01.04, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-04-07, 14:48, # CodeGen: 0
**     Abstract    :
**
**     Settings    :
**
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file PE_LDD.h                                                  
** @version 01.04
** @brief
**
*/         
/*!
**  @addtogroup PE_LDD_module PE_LDD module documentation
**  @{
*/         
#ifndef __PE_LDD_H
#define __PE_LDD_H

/* MODULE PE_LDD. */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "HAL_TICKS.h"
#include "HAL_LEDS.h"
#include "HAL_WIFI_RESET_PIO.h"
#include "TX_ENABLE_PIO.h"
#include "HAL_PWM_1.h"
#include "HAL_RTC.h"
#include "HAL_UART_2.h"
#include "HAL_UART_4.h"
#include "HAL_UART_5.h"
#include "Shtdn.h"
#include "tscrSPI.h"
#include "tscrIrq.h"
#include "HAL_SPI_2.h"
#include "HAL_CS_ACCEL.h"
#include "HAL_CS_FLASH.h"
#include "HAL_INTERRUPT_ACCEL.h"
#include "AD1.h"
#include "NFC1.h"
#include "LED_AG.h"
#include "LED_AY.h"
#include "LED_K12.h"
#include "LED_K34.h"
#include "FLASH1.h"
#include "usb_host.h"
#include "USB_LDD.h"
#include "HAL_USB_VBUS_ENA_PIO.h"
#include "Ventilador_PIO.h"
#include "Alarma_PIO.h"
#include "Alarma_Inpt.h"
#include "TimerTouch.h"
#include "TimeBuzzer.h"
#include "HAL_WDog.h"


/*
** ===================================================================
** Function prototypes
** ===================================================================
*/

/*
** ===================================================================
**     Method      :  Cpu_PE_FillMemory (component MK70FN1M0MJ15)
*/
/*!
**     @brief
**         Fills a memory area block by a specified value.
**     @param
**       SourceAddressPtr - Source address pointer.
**     @param
**       c - A value used to fill a memory block.
**     @param
**       len - Length of a memory block to fill.
*/
/* ===================================================================*/
void PE_FillMemory(register void* SourceAddressPtr, register uint8_t c, register uint32_t len);

/*
** ===================================================================
**     Method      :  Cpu_PE_PeripheralUsed (component MK70FN1M0MJ15)
*/
/*!
**     @brief
**         Returns information whether a peripheral is allocated by PEx 
**         or not.
**     @param
**       PrphBaseAddress - Base address of a peripheral.
**     @return
**       TRUE if a peripheral is used by PEx or FALSE if it isn't used.
*/
/* ===================================================================*/
bool PE_PeripheralUsed(uint32_t PrphBaseAddress);

/*
** ===================================================================
**     Method      :  Cpu_LDD_SetClockConfiguration (component MK70FN1M0MJ15)
*/
/*!
**     @brief
**         Changes the clock configuration of all LDD components in a 
**         project.
**     @param
**       ClockConfiguration - New CPU clock configuration changed by CPU SetClockConfiguration method.
*/
/* ===================================================================*/
void LDD_SetClockConfiguration(LDD_TClockConfiguration ClockConfiguration);

/* END PE_LDD. */


#endif

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

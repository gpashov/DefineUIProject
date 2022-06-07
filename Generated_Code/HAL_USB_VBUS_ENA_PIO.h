/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : HAL_USB_VBUS_ENA_PIO.h
**     Project     : QPExMainDeffine_V7790
**     Processor   : MK70FN1M0VMJ15
**     Component   : BitIO_LDD
**     Version     : Component 01.033, Driver 01.03, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-04-07, 14:48, # CodeGen: 0
**     Abstract    :
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : HAL_USB_VBUS_ENA_PIO
**          Pin for I/O                                    : ADC0_SE6a/PTE18/SPI0_SOUT/UART2_CTS_b/I2C0_SDA
**          Pin signal                                     : VUSB_ENABLE
**          Direction                                      : Output
**          Initialization                                 : 
**            Init. direction                              : Output
**            Init. value                                  : 0
**            Auto initialization                          : no
**          Safe mode                                      : no
**     Contents    :
**         Init   - LDD_TDeviceData* HAL_USB_VBUS_ENA_PIO_Init(LDD_TUserData *UserDataPtr);
**         GetVal - bool HAL_USB_VBUS_ENA_PIO_GetVal(LDD_TDeviceData *DeviceDataPtr);
**         PutVal - void HAL_USB_VBUS_ENA_PIO_PutVal(LDD_TDeviceData *DeviceDataPtr, bool Val);
**         ClrVal - void HAL_USB_VBUS_ENA_PIO_ClrVal(LDD_TDeviceData *DeviceDataPtr);
**         SetVal - void HAL_USB_VBUS_ENA_PIO_SetVal(LDD_TDeviceData *DeviceDataPtr);
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
** @file HAL_USB_VBUS_ENA_PIO.h
** @version 01.03
** @brief
**         The HAL BitIO component provides a low level API for unified
**         access to general purpose digital input/output pins across
**         various device designs.
**
**         RTOS drivers using HAL BitIO API are simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup HAL_USB_VBUS_ENA_PIO_module HAL_USB_VBUS_ENA_PIO module documentation
**  @{
*/         

#ifndef __HAL_USB_VBUS_ENA_PIO_H
#define __HAL_USB_VBUS_ENA_PIO_H

/* MODULE HAL_USB_VBUS_ENA_PIO. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "IO_Map.h"
#include "GPIO_PDD.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 



/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define HAL_USB_VBUS_ENA_PIO_PRPH_BASE_ADDRESS  0x400FF100U
  
/* Methods configuration constants - generated for all enabled component's methods */
#define HAL_USB_VBUS_ENA_PIO_Init_METHOD_ENABLED /*!< Init method of the component HAL_USB_VBUS_ENA_PIO is enabled (generated) */
#define HAL_USB_VBUS_ENA_PIO_GetVal_METHOD_ENABLED /*!< GetVal method of the component HAL_USB_VBUS_ENA_PIO is enabled (generated) */
#define HAL_USB_VBUS_ENA_PIO_PutVal_METHOD_ENABLED /*!< PutVal method of the component HAL_USB_VBUS_ENA_PIO is enabled (generated) */
#define HAL_USB_VBUS_ENA_PIO_ClrVal_METHOD_ENABLED /*!< ClrVal method of the component HAL_USB_VBUS_ENA_PIO is enabled (generated) */
#define HAL_USB_VBUS_ENA_PIO_SetVal_METHOD_ENABLED /*!< SetVal method of the component HAL_USB_VBUS_ENA_PIO is enabled (generated) */

/* Definition of implementation constants */
#define HAL_USB_VBUS_ENA_PIO_MODULE_BASE_ADDRESS PTE_BASE_PTR /*!< Name of macro used as the base address */
#define HAL_USB_VBUS_ENA_PIO_PORTCONTROL_BASE_ADDRESS PORTE_BASE_PTR /*!< Name of macro used as the base address */
#define HAL_USB_VBUS_ENA_PIO_PORT_MASK 0x00040000U /*!< Mask of the allocated pin from the port */



/*
** ===================================================================
**     Method      :  HAL_USB_VBUS_ENA_PIO_Init (component BitIO_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" is set to "yes" value then the device is also
**         enabled(see the description of the Enable() method). In this
**         case the Enable() method is not necessary and needn't to be
**         generated. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* HAL_USB_VBUS_ENA_PIO_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  HAL_USB_VBUS_ENA_PIO_GetVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Returns the input/output value. If the direction is [input]
**         then the input value of the pin is read and returned. If the
**         direction is [output] then the last written value is read
**         and returned (see <Safe mode> property for limitations).
**         This method cannot be disabled if direction is [input].
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Input or output value. Possible values:
**                           <false> - logical "0" (Low level)
**                           <true> - logical "1" (High level)
*/
/* ===================================================================*/
bool HAL_USB_VBUS_ENA_PIO_GetVal(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  HAL_USB_VBUS_ENA_PIO_PutVal (component BitIO_LDD)
*/
/*!
**     @brief
**         The specified output value is set. If the direction is <b>
**         input</b>, the component saves the value to a memory or a
**         register and this value will be written to the pin after
**         switching to the output mode (using <tt>SetDir(TRUE)</tt>;
**         see <a href="BitIOProperties.html#SafeMode">Safe mode</a>
**         property for limitations). If the direction is <b>output</b>,
**         it writes the value to the pin. (Method is available only if
**         the direction = <u><tt>output</tt></u> or <u><tt>
**         input/output</tt></u>).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         Val             - Output value. Possible values:
**                           <false> - logical "0" (Low level)
**                           <true> - logical "1" (High level)
*/
/* ===================================================================*/
void HAL_USB_VBUS_ENA_PIO_PutVal(LDD_TDeviceData *DeviceDataPtr, bool Val);

/*
** ===================================================================
**     Method      :  HAL_USB_VBUS_ENA_PIO_ClrVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Clears (set to zero) the output value. It is equivalent to
**         the [PutVal(FALSE)]. This method is available only if the
**         direction = _[output]_ or _[input/output]_.
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure returned by <Init> method.
*/
/* ===================================================================*/
void HAL_USB_VBUS_ENA_PIO_ClrVal(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  HAL_USB_VBUS_ENA_PIO_SetVal (component BitIO_LDD)
*/
/*!
**     @brief
**         Sets (to one) the output value. It is equivalent to the
**         [PutVal(TRUE)]. This method is available only if the
**         direction = _[output]_ or _[input/output]_.
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure returned by <Init> method.
*/
/* ===================================================================*/
void HAL_USB_VBUS_ENA_PIO_SetVal(LDD_TDeviceData *DeviceDataPtr);

/* END HAL_USB_VBUS_ENA_PIO. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif
/* ifndef __HAL_USB_VBUS_ENA_PIO_H */
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

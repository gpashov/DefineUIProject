/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : HAL_WDog.h
**     Project     : QPExMainDeffine_V7790
**     Processor   : MK70FN1M0VMJ15
**     Component   : WatchDog_LDD
**     Version     : Component 01.052, Driver 01.09, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-04-07, 14:48, # CodeGen: 0
**     Abstract    :
**          The WatchDog component provides a high level API for unified hardware access
**          across various watchdog timer devices.
**     Settings    :
**          Component name                                 : HAL_WDog
**          Device                                         : WDOG
**          Action                                         : Reset CPU
**          Period                                         : 10 sec
**          Windowed mode                                  : Disabled
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Protected                                    : no
**            Auto initialization                          : no
**          CPU clock/configuration selection              : Ignored
**     Contents    :
**         Init    - LDD_TDeviceData* HAL_WDog_Init(LDD_TUserData *UserDataPtr);
**         Enable  - LDD_TError HAL_WDog_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable - LDD_TError HAL_WDog_Disable(LDD_TDeviceData *DeviceDataPtr);
**         Clear   - LDD_TError HAL_WDog_Clear(LDD_TDeviceData *DeviceDataPtr);
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
** @file HAL_WDog.h
** @version 01.09
** @brief
**          The WatchDog component provides a high level API for unified hardware access
**          across various watchdog timer devices.
*/         
/*!
**  @addtogroup HAL_WDog_module HAL_WDog module documentation
**  @{
*/         

#ifndef __HAL_WDog_H
#define __HAL_WDog_H

/* MODULE HAL_WDog. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */

#include "WDOG_PDD.h"
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 


#define HAL_WDog_WATCHDOG_TIMEOUT 10.066329633333F /* Initialization watchdog timeout period in seconds. */
#define HAL_WDog_WATCHDOG_WINDOW 0.0F  /* Initialization watchdog window period in seconds as real number. */

/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define HAL_WDog_PRPH_BASE_ADDRESS  0x40052000U
  
/* Methods configuration constants - generated for all enabled component's methods */
#define HAL_WDog_Init_METHOD_ENABLED   /*!< Init method of the component HAL_WDog is enabled (generated) */
#define HAL_WDog_Enable_METHOD_ENABLED /*!< Enable method of the component HAL_WDog is enabled (generated) */
#define HAL_WDog_Disable_METHOD_ENABLED /*!< Disable method of the component HAL_WDog is enabled (generated) */
#define HAL_WDog_Clear_METHOD_ENABLED  /*!< Clear method of the component HAL_WDog is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */



/*
** ===================================================================
**     Method      :  HAL_WDog_Init (component WatchDog_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property <"Enable in init. code"> is set to "yes" value then
**         the device is also enabled (see the description of the
**         <Enable> method). In this case the <Enable> method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the <Deinit>
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* HAL_WDog_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  HAL_WDog_Enable (component WatchDog_LDD)
*/
/*!
**     @brief
**         Enables the watchdog.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
**                           ERR_PROTECT - Device is write protected and
**                           cannot be unlocked.
*/
/* ===================================================================*/
LDD_TError HAL_WDog_Enable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  HAL_WDog_Disable (component WatchDog_LDD)
*/
/*!
**     @brief
**         Disables the watchdog.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
**                           ERR_PROTECT - Device is write protected and
**                           cannot be unlocked.
*/
/* ===================================================================*/
LDD_TError HAL_WDog_Disable(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  HAL_WDog_Clear (component WatchDog_LDD)
*/
/*!
**     @brief
**         Clears the watchdog timer (it makes the timer restart from
**         zero).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
**                           ERR_DISABLED - The component is disabled
*/
/* ===================================================================*/
LDD_TError HAL_WDog_Clear(LDD_TDeviceData *DeviceDataPtr);

/* END HAL_WDog. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif
/* ifndef __HAL_WDog_H */
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

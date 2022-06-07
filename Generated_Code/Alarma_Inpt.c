/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Alarma_Inpt.c
**     Project     : QPExMainDeffine_V7790
**     Processor   : MK70FN1M0VMJ15
**     Component   : ExtInt_LDD
**     Version     : Component 02.156, Driver 01.02, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-04-07, 14:48, # CodeGen: 0
**     Abstract    :
**         This component, "ExtInt_LDD", provide a low level API 
**         for unified access of external interrupts handling
**         across various device designs.
**         The component uses one pin which generates interrupt on 
**         selected edge.
**     Settings    :
**          Component name                                 : Alarma_Inpt
**          Pin                                            : CMP3_IN2/PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0/I2S0_RX_FS/I2S0_RXD1
**          Pin signal                                     : AlarmaInpt_ENABLE
**          Generate interrupt on                          : falling edge
**          Interrupt                                      : INT_PORTA
**          Interrupt priority                             : medium priority
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**          Threshold level                                : 0
**     Contents    :
**         Init   - LDD_TDeviceData* Alarma_Inpt_Init(LDD_TUserData *UserDataPtr);
**         GetVal - bool Alarma_Inpt_GetVal(LDD_TDeviceData *DeviceDataPtr);
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
** @file Alarma_Inpt.c
** @version 01.02
** @brief
**         This component, "ExtInt_LDD", provide a low level API 
**         for unified access of external interrupts handling
**         across various device designs.
**         The component uses one pin which generates interrupt on 
**         selected edge.
*/         
/*!
**  @addtogroup Alarma_Inpt_module Alarma_Inpt module documentation
**  @{
*/         

/* MODULE Alarma_Inpt. */

#include "Events.h"
#include "Alarma_Inpt.h"
/* {Default RTOS Adapter} No RTOS includes */

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TUserData *UserData;             /* RTOS device data structure */
} Alarma_Inpt_TDeviceData, *Alarma_Inpt_TDeviceDataPtr; /* Device data structure type */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static Alarma_Inpt_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static Alarma_Inpt_TDeviceData * INT_PORTA__DEFAULT_RTOS_ISRPARAM;

/*
** ===================================================================
**     Method      :  Alarma_Inpt_Init (component ExtInt_LDD)
*/
/*!
**     @brief
**         This method initializes the associated peripheral(s) and the
**         component internal variables. The method is called
**         automatically as a part of the application initialization
**         code.
**     @param
**         UserDataPtr     - Pointer to the RTOS device
**                           structure. This pointer will be passed to
**                           all events as parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* Alarma_Inpt_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  Alarma_Inpt_TDeviceData *DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  /* Store the UserData pointer */
  DeviceDataPrv->UserData = UserDataPtr;
  /* Interrupt vector(s) allocation */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_PORTA__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  /* Initialization of Port Control registers */
  /* PORTA_PCR16: ISF=0,MUX=1 */
  PORTA_PCR16 = (uint32_t)((PORTA_PCR16 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x06)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x01)
                ));
  /* PORTA_PCR16: ISF=1,IRQC=0x0A */
  PORTA_PCR16 = (uint32_t)((PORTA_PCR16 & (uint32_t)~(uint32_t)(
                 PORT_PCR_IRQC(0x05)
                )) | (uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_IRQC(0x0A)
                ));
  /* NVICIP87: PRI87=0x80 */
  NVICIP87 = NVIC_IP_PRI87(0x80);
  /* NVICISER2: SETENA|=0x00800000 */
  NVICISER2 |= NVIC_ISER_SETENA(0x00800000);
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_Alarma_Inpt_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv);
}

/*
** ===================================================================
**     Method      :  Alarma_Inpt_Interrupt (component ExtInt_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Alarma_Inpt_Interrupt)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  Alarma_Inpt_TDeviceDataPtr DeviceDataPrv = INT_PORTA__DEFAULT_RTOS_ISRPARAM;

  /* Clear the interrupt flag */
  PORT_PDD_ClearPinInterruptFlag(PORTA_BASE_PTR, Alarma_Inpt_PIN_INDEX);
  /* Call OnInterrupt event */
  Alarma_Inpt_OnInterrupt(DeviceDataPrv->UserData);
}

/*
** ===================================================================
**     Method      :  Alarma_Inpt_GetVal (component ExtInt_LDD)
*/
/*!
**     @brief
**         Returns the actual value of the input pin of the component.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Returned input value. Possible values:
**                           <false> - logical "0" (Low level) <true> -
**                           logical "1" (High level)
*/
/* ===================================================================*/
bool Alarma_Inpt_GetVal(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  if ((GPIO_PDD_GetPortDataInput(PTA_BASE_PTR) & Alarma_Inpt_PIN_MASK) != 0U) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/* END Alarma_Inpt. */

#ifdef __cplusplus
}  /* extern "C" */
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

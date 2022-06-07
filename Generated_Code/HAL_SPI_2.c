/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : HAL_SPI_2.c
**     Project     : QPExMainDeffine_V7790
**     Processor   : MK70FN1M0VMJ15
**     Component   : SPIMaster_LDD
**     Version     : Component 01.111, Driver 01.08, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-04-07, 14:48, # CodeGen: 0
**     Abstract    :
**         This component "SPIMaster_LDD" implements MASTER part of synchronous
**         serial master-slave communication.
**     Settings    :
**          Component name                                 : HAL_SPI_2
**          Device                                         : SPI2
**          Interrupt service/event                        : Enabled
**            Input interrupt                              : INT_SPI2
**            Input interrupt priority                     : medium priority
**            Output interrupt                             : INT_SPI2
**            Output interrupt priority                    : medium priority
**          Settings                                       : 
**            Input pin                                    : Enabled
**              Pin                                        : PTD14/SPI2_SIN/SDHC0_D6/FBa_A22/GLCD_HFS
**              Pin signal                                 : 
**            Output pin                                   : Enabled
**              Pin                                        : PTD13/SPI2_SOUT/SDHC0_D5/FBa_A21/GLCD_DE
**              Pin signal                                 : 
**            Clock pin                                    : 
**              Pin                                        : PTD12/SPI2_SCK/FTM3_FLT0/SDHC0_D4/FBa_A20/GLCD_PCLK
**              Pin signal                                 : 
**            Chip select list                             : 0
**            CS external demultiplexer                    : Disabled
**            Attribute set list                           : 1
**              Attribute set 0                            : 
**                Width                                    : 8 bits
**                MSB first                                : yes
**                Clock polarity                           : Low
**                Clock phase                              : Capture on leading edge
**                Parity                                   : None
**                Chip select toggling                     : no
**                Clock rate index                         : 0
**                Delay between chars index                : 0
**                CS to CLK delay index                    : 0
**                CLK to CS delay index                    : 0
**            Clock rate                                   : 1.333333 �s
**            Delay between chars                          : 0.2 �s
**            CS to CLK delay                              : 0.1 �s
**            CLK to CS delay                              : 0.1 �s
**            HW input buffer size                         : 1
**            HW input watermark                           : 1
**            HW output buffer size                        : 1
**            HW output watermark                          : 1
**          Initialization                                 : 
**            Initial chip select                          : 0
**            Initial attribute set                        : 0
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnBlockSent                                : Enabled
**              OnBlockReceived                            : Enabled
**              OnError                                    : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init           - LDD_TDeviceData* HAL_SPI_2_Init(LDD_TUserData *UserDataPtr);
**         SendBlock      - LDD_TError HAL_SPI_2_SendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         ReceiveBlock   - LDD_TError HAL_SPI_2_ReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         GetDriverState - LDD_TDriverState HAL_SPI_2_GetDriverState(LDD_TDeviceData *DeviceDataPtr);
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
** @file HAL_SPI_2.c
** @version 01.08
** @brief
**         This component "SPIMaster_LDD" implements MASTER part of synchronous
**         serial master-slave communication.
*/         
/*!
**  @addtogroup HAL_SPI_2_module HAL_SPI_2 module documentation
**  @{
*/         

/* MODULE HAL_SPI_2. */
/*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. */

#include "Events.h"
#include "HAL_SPI_2.h"
/* {Default RTOS Adapter} No RTOS includes */

#ifdef __cplusplus
extern "C" {
#endif 

#define AVAILABLE_EVENTS_MASK (LDD_SPIMASTER_ON_BLOCK_RECEIVED | LDD_SPIMASTER_ON_BLOCK_SENT)

/* These constants contain pins masks */
#define HAL_SPI_2_AVAILABLE_PIN_MASK (LDD_SPIMASTER_INPUT_PIN | LDD_SPIMASTER_OUTPUT_PIN | LDD_SPIMASTER_CLK_PIN)

typedef struct {
  uint32_t TxCommand;                  /* Current Tx command */
  LDD_SPIMASTER_TError ErrFlag;        /* Error flags */
  uint16_t InpRecvDataNum;             /* The counter of received characters */
  uint8_t *InpDataPtr;                 /* The buffer pointer for received characters */
  uint16_t InpDataNumReq;              /* The counter of characters to receive by ReceiveBlock() */
  uint16_t OutSentDataNum;             /* The counter of sent characters */
  uint8_t *OutDataPtr;                 /* The buffer pointer for data to be transmitted */
  uint16_t OutDataNumReq;              /* The counter of characters to be send by SendBlock() */
  LDD_TUserData *UserData;             /* User device data structure */
} HAL_SPI_2_TDeviceData;               /* Device data structure type */

typedef HAL_SPI_2_TDeviceData* HAL_SPI_2_TDeviceDataPtr ; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static HAL_SPI_2_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static HAL_SPI_2_TDeviceDataPtr INT_SPI2__DEFAULT_RTOS_ISRPARAM;
/* Internal method prototypes */

/*
** ===================================================================
**     Method      :  HAL_SPI_2_Init (component SPIMaster_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc.
**         If the "Enable in init. code" is set to "yes" value then the
**         device is also enabled(see the description of the Enable()
**         method). In this case the Enable() method is not necessary
**         and needn't to be generated. 
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* HAL_SPI_2_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  HAL_SPI_2_TDeviceDataPtr DeviceDataPrv;

  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_SPI2__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  DeviceDataPrv->TxCommand = 0x80000000U; /* Initialization of current Tx command */
  DeviceDataPrv->ErrFlag = 0x00U;      /* Clear error flags */
  /* Clear the receive counters and pointer */
  DeviceDataPrv->InpRecvDataNum = 0x00U; /* Clear the counter of received characters */
  DeviceDataPrv->InpDataNumReq = 0x00U; /* Clear the counter of characters to receive by ReceiveBlock() */
  DeviceDataPrv->InpDataPtr = NULL;    /* Clear the buffer pointer for received characters */
  /* Clear the transmit counters and pointer */
  DeviceDataPrv->OutSentDataNum = 0x00U; /* Clear the counter of sent characters */
  DeviceDataPrv->OutDataNumReq = 0x00U; /* Clear the counter of characters to be send by SendBlock() */
  DeviceDataPrv->OutDataPtr = NULL;    /* Clear the buffer pointer for data to be transmitted */
  /* SIM_SCGC3: DSPI2=1 */
  SIM_SCGC3 |= SIM_SCGC3_DSPI2_MASK;
  /* Interrupt vector(s) priority setting */
  /* NVICIP28: PRI28=0x80 */
  NVICIP28 = NVIC_IP_PRI28(0x80);
  /* NVICISER0: SETENA|=0x10000000 */
  NVICISER0 |= NVIC_ISER_SETENA(0x10000000);
  /* PORTD_PCR14: ISF=0,MUX=2 */
  PORTD_PCR14 = (uint32_t)((PORTD_PCR14 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x05)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x02)
                ));
  /* PORTD_PCR13: ISF=0,MUX=2 */
  PORTD_PCR13 = (uint32_t)((PORTD_PCR13 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x05)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x02)
                ));
  /* PORTD_PCR12: ISF=0,MUX=2 */
  PORTD_PCR12 = (uint32_t)((PORTD_PCR12 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x05)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x02)
                ));
  /* SPI2_MCR: MSTR=0,CONT_SCKE=0,DCONF=0,FRZ=0,MTFE=0,PCSSE=0,ROOE=1,??=0,??=0,PCSIS=0,DOZE=0,MDIS=0,DIS_TXF=0,DIS_RXF=0,CLR_TXF=0,CLR_RXF=0,SMPL_PT=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,HALT=1 */
  SPI2_MCR = SPI_MCR_DCONF(0x00) |
             SPI_MCR_ROOE_MASK |
             SPI_MCR_PCSIS(0x00) |
             SPI_MCR_SMPL_PT(0x00) |
             SPI_MCR_HALT_MASK;        /* Set Configuration register */
  /* SPI2_MCR: MSTR=1,CONT_SCKE=0,DCONF=0,FRZ=0,MTFE=0,PCSSE=0,ROOE=1,??=0,??=0,PCSIS=0,DOZE=0,MDIS=0,DIS_TXF=1,DIS_RXF=1,CLR_TXF=1,CLR_RXF=1,SMPL_PT=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,HALT=1 */
  SPI2_MCR = SPI_MCR_MSTR_MASK |
             SPI_MCR_DCONF(0x00) |
             SPI_MCR_ROOE_MASK |
             SPI_MCR_PCSIS(0x00) |
             SPI_MCR_DIS_TXF_MASK |
             SPI_MCR_DIS_RXF_MASK |
             SPI_MCR_CLR_TXF_MASK |
             SPI_MCR_CLR_RXF_MASK |
             SPI_MCR_SMPL_PT(0x00) |
             SPI_MCR_HALT_MASK;        /* Set Configuration register */
  /* SPI2_CTAR0: DBR=1,FMSZ=7,CPOL=0,CPHA=0,LSBFE=0,PCSSCK=1,PASC=1,PDT=1,PBR=2,CSSCK=0,ASC=0,DT=1,BR=5 */
  SPI2_CTAR0 = SPI_CTAR_DBR_MASK |
               SPI_CTAR_FMSZ(0x07) |
               SPI_CTAR_PCSSCK(0x01) |
               SPI_CTAR_PASC(0x01) |
               SPI_CTAR_PDT(0x01) |
               SPI_CTAR_PBR(0x02) |
               SPI_CTAR_CSSCK(0x00) |
               SPI_CTAR_ASC(0x00) |
               SPI_CTAR_DT(0x01) |
               SPI_CTAR_BR(0x05);      /* Set Clock and Transfer Attributes register */
  /* SPI2_SR: TCF=1,TXRXS=0,??=0,EOQF=1,TFUF=1,??=0,TFFF=1,??=0,??=0,??=0,??=1,??=0,RFOF=1,??=0,RFDF=1,??=0,TXCTR=0,TXNXTPTR=0,RXCTR=0,POPNXTPTR=0 */
  SPI2_SR = SPI_SR_TCF_MASK |
            SPI_SR_EOQF_MASK |
            SPI_SR_TFUF_MASK |
            SPI_SR_TFFF_MASK |
            SPI_SR_RFOF_MASK |
            SPI_SR_RFDF_MASK |
            SPI_SR_TXCTR(0x00) |
            SPI_SR_TXNXTPTR(0x00) |
            SPI_SR_RXCTR(0x00) |
            SPI_SR_POPNXTPTR(0x00) |
            0x00200000U;               /* Clear flags */
  /* SPI2_RSER: TCF_RE=0,??=0,??=0,EOQF_RE=0,TFUF_RE=0,??=0,TFFF_RE=0,TFFF_DIRS=0,??=0,??=0,??=0,??=0,RFOF_RE=0,??=0,RFDF_RE=1,RFDF_DIRS=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SPI2_RSER = SPI_RSER_RFDF_RE_MASK;   /* Set DMA Interrupt Request Select and Enable register */
  /* SPI2_MCR: HALT=0 */
  SPI2_MCR &= (uint32_t)~(uint32_t)(SPI_MCR_HALT_MASK);
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_HAL_SPI_2_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the data data structure */
}

/*
** ===================================================================
**     Method      :  HAL_SPI_2_ReceiveBlock (component SPIMaster_LDD)
*/
/*!
**     @brief
**         This method specifies the number of data to receive. The
**         method returns ERR_BUSY until the specified number of
**         characters is received. The method <CancelBlockReception>
**         can be used to cancel a running receive operation.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         BufferPtr       - Pointer to A buffer where
**                           received characters will be stored.
**     @param
**         Size            - Size of the block
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_BUSY - The previous receive request is
**                           pending
*/
/* ===================================================================*/
LDD_TError HAL_SPI_2_ReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, uint16_t Size)
{
  if (((HAL_SPI_2_TDeviceDataPtr)DeviceDataPtr)->InpDataNumReq != 0x00U) { /* Is the previous receive operation pending? */
    return ERR_BUSY;                   /* If yes then error */
  }
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  ((HAL_SPI_2_TDeviceDataPtr)DeviceDataPtr)->InpDataPtr = (uint8_t*)BufferPtr; /* Store a pointer to the input data. */
  ((HAL_SPI_2_TDeviceDataPtr)DeviceDataPtr)->InpDataNumReq = Size; /* Store a number of characters to be received. */
  ((HAL_SPI_2_TDeviceDataPtr)DeviceDataPtr)->InpRecvDataNum = 0x00U; /* Set number of received characters to zero. */
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  HAL_SPI_2_SendBlock (component SPIMaster_LDD)
*/
/*!
**     @brief
**         This method sends a block of characters. The method returns
**         ERR_BUSY when the previous block transmission is not
**         completed. The method <CancelBlockTransmission> can be used
**         to cancel a transmit operation.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         BufferPtr       - Pointer to the block of data
**                           to send.
**     @param
**         Size            - Number of characters in the buffer.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_BUSY - The previous transmit request is
**                           pending
*/
/* ===================================================================*/
LDD_TError HAL_SPI_2_SendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, uint16_t Size)
{
  if (((HAL_SPI_2_TDeviceDataPtr)DeviceDataPtr)->OutDataNumReq != 0x00U) { /* Is the previous transmit operation pending? */
    return ERR_BUSY;                   /* If yes then error */
  }
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  ((HAL_SPI_2_TDeviceDataPtr)DeviceDataPtr)->OutDataPtr = (uint8_t*)BufferPtr; /* Set a pointer to the output data. */
  ((HAL_SPI_2_TDeviceDataPtr)DeviceDataPtr)->OutDataNumReq = Size; /* Set the counter of characters to be sent. */
  ((HAL_SPI_2_TDeviceDataPtr)DeviceDataPtr)->OutSentDataNum = 0x00U; /* Clear the counter of sent characters. */
  SPI_PDD_EnableDmasInterrupts(SPI2_BASE_PTR, SPI_PDD_TX_FIFO_FILL_INT_DMA); /* Enable TX interrupt */
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  HAL_SPI_2_Interrupt (component SPIMaster_LDD)
**
**     Description :
**         The ISR function handling the device receive/transmit 
**         interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(HAL_SPI_2_Interrupt)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  HAL_SPI_2_TDeviceDataPtr DeviceDataPrv = INT_SPI2__DEFAULT_RTOS_ISRPARAM;
  uint32_t StatReg = SPI_PDD_GetInterruptFlags(SPI2_BASE_PTR); /* Read status register */
  uint16_t Data;                       /* Temporary variable for data */

  if ((StatReg & SPI_PDD_RX_FIFO_OVERFLOW_INT) != 0U) { /* Is any error flag set? */
    SPI_PDD_ClearInterruptFlags(SPI2_BASE_PTR,SPI_PDD_RX_FIFO_OVERFLOW_INT); /* Clear error flags */
  }
  if ((StatReg & SPI_PDD_RX_FIFO_DRAIN_INT_DMA) != 0U) { /* Is any char in HW buffer? */
    Data = (uint16_t)SPI_PDD_ReadPopRxFIFOReg(SPI2_BASE_PTR); /* Read character from receiver */
    SPI_PDD_ClearInterruptFlags(SPI2_BASE_PTR,SPI_PDD_RX_FIFO_DRAIN_INT_DMA); /* Clear Rx FIFO drain flags */
    if (DeviceDataPrv->InpDataNumReq != 0x00U) { /* Is the receive block operation pending? */
      *(DeviceDataPrv->InpDataPtr++) = (uint8_t)Data; /* Put a character to the receive buffer and increment pointer to receive buffer */
      DeviceDataPrv->InpRecvDataNum++; /* Increment received char. counter */
      if (DeviceDataPrv->InpRecvDataNum == DeviceDataPrv->InpDataNumReq) { /* Is the requested number of characters received? */
        DeviceDataPrv->InpDataNumReq = 0x00U; /* If yes then clear number of requested characters to be received. */
        HAL_SPI_2_OnBlockReceived(DeviceDataPrv->UserData);
      }
    }
  }
  if ((StatReg & SPI_PDD_TX_FIFO_FILL_INT_DMA) != 0U) { /* Is HW buffer empty? */
    if (DeviceDataPrv->OutSentDataNum < DeviceDataPrv->OutDataNumReq) { /* Is number of sent characters less than the number of requested incoming characters? */
      DeviceDataPrv->OutSentDataNum++; /* Increment the counter of sent characters. */
      SPI_PDD_WriteMasterPushTxFIFOReg(SPI2_BASE_PTR, (uint32_t)(*((uint8_t *)DeviceDataPrv->OutDataPtr++) | DeviceDataPrv->TxCommand)); /* Put a character with command to the transmit register and increment pointer to the transmitt buffer */
      if (DeviceDataPrv->OutSentDataNum == DeviceDataPrv->OutDataNumReq) {
        DeviceDataPrv->OutDataNumReq = 0x00U; /* Clear the counter of characters to be send by SendBlock() */
        HAL_SPI_2_OnBlockSent(DeviceDataPrv->UserData);
      }
    } else {
      SPI_PDD_DisableDmasInterrupts(SPI2_BASE_PTR, SPI_PDD_TX_FIFO_FILL_INT_DMA); /* Disable TX interrupt */
    }
    SPI_PDD_ClearInterruptFlags(SPI2_BASE_PTR,SPI_PDD_TX_FIFO_FILL_INT_DMA); /* Clear Tx FIFO fill flags */
  }
}

/*
** ===================================================================
**     Method      :  HAL_SPI_2_GetDriverState (component SPIMaster_LDD)
*/
/*!
**     @brief
**         This method returns the current driver status.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - The current driver status mask.
**                           Following status masks defined in PE_Types.h
**                           can be used to check the current driver
**                           status.
**                           PE_LDD_DRIVER_DISABLED_IN_CLOCK_CONFIGURATIO
**                           N - 1 - Driver is disabled in the current
**                           mode; 0 - Driver is enabled in the current
**                           mode.  
**                           PE_LDD_DRIVER_DISABLED_BY_USER - 1 - Driver
**                           is disabled by the user; 0 - Driver is
**                           enabled by the user.        
**                           PE_LDD_DRIVER_BUSY - 1 - Driver is the BUSY
**                           state; 0 - Driver is in the IDLE state.
*/
/* ===================================================================*/
LDD_TDriverState HAL_SPI_2_GetDriverState(LDD_TDeviceData *DeviceDataPtr)
{
  LDD_TDriverState DriverState = 0x00U;
  HAL_SPI_2_TDeviceDataPtr DeviceDataPrv = (HAL_SPI_2_TDeviceDataPtr)DeviceDataPtr;

  DriverState |=((DeviceDataPrv->InpDataNumReq != 0x00U) || (DeviceDataPrv->OutDataNumReq != 0x00U))? PE_LDD_DRIVER_BUSY : 0x00U;
  return DriverState;
}

/*lint -restore Enable MISRA rule (11.4) checking. */
/* END HAL_SPI_2. */

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

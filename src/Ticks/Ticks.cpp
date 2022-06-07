/*
 * Ticks.c
 *
 *  Created on: Nov 15, 2016
 *      Author: ingenieria1
 */

#include "Ticks.h"
#include "../Buzzer/Buzzer.h"
//#include "HAL_TICKS.h"

uint32 u32Ticks;
LDD_TDeviceData* timer1ms;

void TICKS_Init(void)
{
//	u32Ticks = 0;
//	timer1ms = HAL_TICKS_Init((LDD_TUserData *)NULL);
}

uint32 TICKS_GetTicks(void)
{
	return u32Ticks;
}

uint32 TICKS_DiffTicks(uint32 u32Reference)
{
	uint32 temp;
	
	temp = u32Reference;
	return u32Ticks-temp;
}

void TICKS_ISR_Interrupt(void)
{
	u32Ticks++;
}




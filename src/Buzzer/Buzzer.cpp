/*
 * Buzzer.c
 *
 *  Created on: Nov 16, 2016
 *      Author: ingenieria1
 */

#include "Buzzer.h"
//#include "Ticks/Ticks.h"

buzzer_control_t buzzer_control;

LDD_TUserData *TimerBuzzerUserDataPtr;

const sound_control_t patrons_so[MAXIM_PATRO_SO][BUZZ_MAX_SOUNDS] =
{
		{	/* patro 0 */
				{	/* freq 0 */
						.u16Frequencia = 300,
						.u16Temps = 80,
				},
				{	/* freq 1 */
						.u16Frequencia = 0,
						.u16Temps = 20,
				},
				{	/* freq 2 */
						.u16Frequencia = 200,
						.u16Temps = 80,
				},
		},
		{	/* patro 1 */
				{	/* freq 0 */
						.u16Frequencia = 2000,
						.u16Temps = 100,
				},
				{	/* freq 1 */
						.u16Frequencia = 800,
						.u16Temps = 100,
				},
				{	/* freq 2 */
						.u16Frequencia = 0,
						.u16Temps = 100,
				},
		},
		{	/* patro 2 */
				{	/* freq 0 */
						.u16Frequencia = 1000,
						.u16Temps = 1000,
				},
				{	/* freq 1 */
						.u16Frequencia = 1300,
						.u16Temps = 1000,
				},
				{	/* freq 2 */
						.u16Frequencia = 1800,
						.u16Temps = 1000,
				},
		},
		{	/* patro 3 */
				{	/* freq 0 */
						.u16Frequencia = 1800,
						.u16Temps = 1000,
				},
				{	/* freq 1 */
						.u16Frequencia = 1300,
						.u16Temps = 1000,
				},
				{	/* freq 2 */
						.u16Frequencia = 1000,
						.u16Temps = 1000,
				},
		},
		{	/* patro 4 */
				{	/* freq 0 */
						.u16Frequencia = 2400,
						.u16Temps = 1000,
				},
				{	/* freq 1 */
						.u16Frequencia = 0,
						.u16Temps = 0,
				},
				{	/* freq 2 */
						.u16Frequencia = 0,
						.u16Temps = 0,
				},
		},
		{	/* patro 5 */
				{	/* freq 0 */
						.u16Frequencia = 800,//800
						.u16Temps = 300,
				},
				{	/* freq 1 */
						.u16Frequencia = 1200,//800
						.u16Temps = 300,
				},
//				{	/* freq 2 */
//						.u16Frequencia = 2400,//800
//						.u16Temps = 300,
//				},
		},
		{	/* patro 6 */
				{	/* freq 0 */
						.u16Frequencia = 200,
						.u16Temps = 100,
				},
				{	/* freq 1 */
						.u16Frequencia = 15000,
						.u16Temps = 100,
				},
				{	/* freq 2 */
						.u16Frequencia = 1900,
						.u16Temps = 100,
				},
		},
		{	/* patro 7 */
				{	/* freq 0 */
						.u16Frequencia = 2400,
						.u16Temps = 10,
				},
				{	/* freq 1 */
						.u16Frequencia = 0,
						.u16Temps = 10,
				},
//				{	/* freq 2 */
//						.u16Frequencia = 2400,
//						.u16Temps = 10,
//				},
		},
};

void BUZZ_Init(void)
{
//    buzzer_control.HAL_StructPointer = HAL_PWM_1_Init((LDD_TUserData *)NULL);
    
//    buzzer_control.u8Motor = 0;
//    buzzer_control.u8SoActual = 0;
//    buzzer_control.u8Repeticions = 0;
//    buzzer_control.u16TempsOFF = 10;
//    buzzer_control.u8Patro = PATRO_SO_BUT_SW_PULSED;
//    HAL_PWM_1_Disable(buzzer_control.HAL_StructPointer);
//    HAL_PWM_1_ClearValue(buzzer_control.HAL_StructPointer);
//    TimeBuzzer_Init(TimerBuzzerUserDataPtr);
}

uint8 BUZZ_Motor(void)
{
    uint16 u16Freq;
	
    uint8 BUZZ_errOK=0;
	
//	buzzer_control.u32Timer += BUZZ_TIME_INT;
	
//    switch(buzzer_control.u8Motor)
//    {
//        case 0:
//            if(buzzer_control.u8Repeticions > 0)
//            {
//            	buzzer_control.u8SoActual = 0;
//                buzzer_control.u8Motor++;
//            }
//            break;
//        case 1:
//        	if(patrons_so[buzzer_control.u8Patro][buzzer_control.u8SoActual].u16Frequencia != 0)
//        	{
//        		u16Freq = patrons_so[buzzer_control.u8Patro][buzzer_control.u8SoActual].u16Frequencia;
//        		if(u16Freq == 0)
//        		{
//        			HAL_PWM_1_Disable(buzzer_control.HAL_StructPointer);
//					HAL_PWM_1_ClearValue(buzzer_control.HAL_StructPointer);
//        		}
//        		else
//        		{
//					if(u16Freq < HAL_PWM_1_SFREQ_HZ_MIN)
//						u16Freq = HAL_PWM_1_SFREQ_HZ_MIN;
//					else if(u16Freq > HAL_PWM_1_SFREQ_HZ_MAX)
//						u16Freq = HAL_PWM_1_SFREQ_HZ_MAX;
//					HAL_PWM_1_SetFrequencyHz(buzzer_control.HAL_StructPointer, u16Freq);
//					HAL_PWM_1_SetRatio16(buzzer_control.HAL_StructPointer, 0x8000);
//					HAL_PWM_1_Enable(buzzer_control.HAL_StructPointer);
//        		}
//        	}
//        	buzzer_control.u32Timer = 0;		//Inicializamos el tiempo de referencia para el buzzer
//        	buzzer_control.u8Motor++;
//        	break;
//        case 2:
//        	if(buzzer_control.u32Timer > patrons_so[buzzer_control.u8Patro][buzzer_control.u8SoActual].u16Temps)
//            {
//                buzzer_control.u32Timer = 0;		//Inicializamos el tiempo de referencia para el buzzer
//                HAL_PWM_1_Disable(buzzer_control.HAL_StructPointer);
//                HAL_PWM_1_ClearValue(buzzer_control.HAL_StructPointer);
//                buzzer_control.u8Motor++;
//            }
//            break;
//        case 3:
//        	buzzer_control.u8SoActual++;
//        	if(buzzer_control.u8SoActual >= BUZZ_MAX_SOUNDS)
//        	{
//        		buzzer_control.u32Timer = 0;		//Inicializamos el tiempo de referencia para el buzzer
//        		buzzer_control.u8Motor++;
//        	}
//        	else
//        	{
//        		buzzer_control.u8Motor = 1;
//        	}
//        	break;
//        case 4:
//        	if(buzzer_control.u32Timer > buzzer_control.u16TempsOFF)
//        	{
//        		buzzer_control.u8Repeticions--;
//        		buzzer_control.u8Motor = 0;
        		
//        		BUZZ_errOK=1;
//        	}
//        	break;
//        default:
//            buzzer_control.u8Motor = 0;
//            break;
//    }
    
    
    return BUZZ_errOK;
    
}

returnstatus_t BUZZ_Configure(uint8 u8Repeats, uint16 u16TimeOff, uint8 u8Patro)
{
	returnstatus_t temp;
	if(buzzer_control.u8Repeticions == 0)
	{
		buzzer_control.u8Repeticions = u8Repeats;
		buzzer_control.u16TempsOFF = u16TimeOff;

		buzzer_control.u8Patro = (u8Patro < MAXIM_PATRO_SO)? u8Patro:MAXIM_PATRO_SO-1;
		temp = SUCCESS;
	}
	else
	{
		temp = ERROR;
	}
	return temp;
}



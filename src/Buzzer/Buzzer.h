/*
 * Buzzer.h
 *
 *  Created on: Nov 16, 2016
 *      Author: ingenieria1
 */

#ifndef BUZZER_H_
#define BUZZER_H_

//#include "HAL_PWM_1.h"
#include "PE_Types.h"
#include "GeneralDefines.h"
//#include "TimeBuzzer.h"

#define BUZZ_MAX_SOUNDS		3
#define BUZZ_TIME_INT		10		//Tiempo entre interrupciones para la llamada al motor del buzzer

enum
{
	PATRO_SO_RFID_KO,					//Error de RFID
	PATRO_SO_RFID_OK,					//Exito lectura RFID
	PATRO_SO_WARNING,
	PATRO_SO_CALIBRATION,				//Calibración
	PATRO_SO_FINAL_TRT,					//1min antes de fin TRT y al finalizar TRT
	PATRO_SO_ERROR,						//Al salir un error
	PATRO_SO_FINAL_TRT_CONFIG,			//Al final los 5min primeros de tratamiento (config de TRT)
	PATRO_SO_BUT_SW_PULSED,				//Al pulsar un boton o switch
	
	MAXIM_PATRO_SO
};

typedef struct
{
	uint16 u16Frequencia;
	uint16 u16Temps;
}sound_control_t;

typedef struct
{
    uint8 u8Motor;
    uint8 u8SoActual;
    uint8 u8Repeticions;
    uint8 u8Patro;
    uint16 u16TempsOFF;
    uint16 Dummy;
    uint32 u32Timer;
    LDD_TDeviceData *HAL_StructPointer;
}buzzer_control_t;

void BUZZ_Init(void);

/*
 * Se requiere crear una interrupcion que vaya llamando al motor para ir actualizando los sonidos.
 * El define BUZZ_TIME_INT debe tomar el valos del tiempo de la interrupción, y dicho tiempo
 * debe de ser inferior al tiempo minimo del sonido que se quiera reproducir.
 */
uint8 BUZZ_Motor(void);

returnstatus_t BUZZ_Configure(uint8 u8Repeats, uint16 u16TimeOff, uint8 u8Patro);


#endif /* BUZZER_H_ */

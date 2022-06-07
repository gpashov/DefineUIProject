/*
 * Perifericos.h
 *
 *  Created on: Mar 6, 2019
 *      Author: dbelmonte
 */

#ifndef PERIFERICOS_H_
#define PERIFERICOS_H_

/*** INCLUDES ***/
#include "../GeneralDefines.h"
#include "../Expansora/Expansora.h"

/*** CONSTANTES ***/
//MEJORA: Esto se puede poner en un único archivo de configuración de maquina
/* 
 * Constantes definición del remapeo en la expansora para los perifericos de la máquina. 
 * Estas constantes se tienen que adaptar en función de la definición de la maquina a nivel HW. 
 * La memoria reservada en la expansora para el remapeo la vamos a dividir a partes iguales
 * para cada posible periferico sin distinguir el modelo de periferico. Todos los perifericos
 * ocuparan el mismo espacio en el remapeo para ubicar todos sus tipos de tramas.
 * Esta decisión condiciona el funcionamiento de la librería de perifericos 
 * */
#define PRF_REMAP_MAX_N_PERIFS 4			//Número máximo de perifericos admitidos por la máquina
#define PRF_REMAP_BLOCK_SIZE 1024			//Tamaño del bloque reservado para cada periferico 
#define HPCRYO_MAX_N_PERIFS 4				//Número máximo de perifericos tipo HP cryo

/* 
 * Tipos de perifericos definidos, por cada uno de ellos hay un modulo (.c y .h) definido.
 * Es decir, si se crea un nuevo tipo de períferico hay que añadirlo aqui y crear su modulo.
 */
typedef enum
{
	PRF_TYPE_NONE = 0,
	PRF_TYPE_HP_CRYO = 1,
	
	PRF_TYPE_NUM = 2
}cPRFtypes;

/*
 * Sentidos de las tramas de perifericos posibles
 */
typedef enum
{
	PRF_FRAME_DIR_IN = 0,
	PRF_FRAME_DIR_OUT = 1
}cPRFframeDir;

/*
 * Logica de estados general de periferico
 */
typedef enum
{
	PRF_STATUS_IDLE = 1,
	PRF_STATUS_DETECTING = 2,
	PRF_STATUS_INIT = 3,
	PRF_STATUS_RUNNING = 4,
	PRF_STATUS_FINISH = 5
}cPRFstatus;

/*
 * Nombres para los ID's Hardware disponibles para los perifericos en esta UC
 */
typedef enum
{
	PRF_HW_SLOT1 = 1,
	PRF_HW_SLOT2 = 2,
	PRF_HW_SLOT3 = 3,
	PRF_HW_SLOT4 = 4
}cPRFslot;

/*** TIPOS DE DATOS ***/
/* 
 * Definicion del tipo de funcion para los punteros de los callbacks Init, Update y Finish
 * de los tipos de perifericos. Estas funciones las tiene que implementar el modulo de cada
 * tipo de periferico 
 * */
typedef returnstatus_t (*tCbkTypeGeneral)( void *);

/** TIPO DE DATOS DE PERIFERICO GENERAL **/
/*
 * Definicion del tipo de datos de cada periferico. Aqui se define el tipo de periferico y se 
 * guarda el indice en el array del tipo que sea para poder acceder a los datos asociados al tipo.
 * Se definen tambien los punteros a las funciones Update, Init y Finish que todo periferico tiene 
 * que implementar.
 */
typedef struct
{
    cPRFstatus status;					//Estado actual de la logica del periferico
	
    uint8 isUsed;						//Indica si este hueco de periferico esta en uso en el vector.
    uint8 IDperifHW;					//ID hardware del periferico, es la dirección fisica en el conector de la expansora.
    uint32 myDirInRemapFramesBuffer;	//Dirección de este periferico en el buffer de las tramas de remapeo
	
    tEXPperif *common;					//Datos comunes del periferico, sin tener en cuenta el tipo. Es un puntero a la estructura de datos del modulo expansora
    cPRFtypes type;						//Tipo de periferico
    uint8 indexInTypeArray;				//Indice del periferico en el array del datos del tipo concreto
    tCbkTypeGeneral cbkTypeInit;		//Callback a la función Init() - Inicializa el modulo del tipo de periferico
    tCbkTypeGeneral cbkTypeUpdate;		//Callback a la función Update() - Motor del modulo del tipo de periferico
    tCbkTypeGeneral cbkTypeFinish;		//Callback a la función Finish() - Finaliza el modulo del tipo de periferico
}tPRFdata;



/*** VARIABLES GLOBALES PUBLICAS ***/
//extern tPRFdata PRFdata[PRF_REMAP_MAX_N_PERIFS];

/*** FUNCIONES PUBLICAS ***/
//void PRFinit( void);
//uint8 PRFupdate( uint32 loopTime);
//returnstatus_t PRFchangeStatus( cPRFstatus status);

/** METODOS DE PERIFERICO GENERAL **/
//uint8 PRFgetFromSlot( cPRFslot slot, tPRFdata **PRFptr);

/** METODOS DE HPCRYO PUBLICOS **/

#endif /* PERIFERICOS_H_ */

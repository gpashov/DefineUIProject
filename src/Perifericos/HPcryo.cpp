/*
 * HPcryo.c
 *
 *  Created on: Mar 6, 2019
 *      Author: dbelmonte
 */

#include "../GeneralDefines.h"
//#include "App.h"
#include "Perifericos.h"
#include "HPcryo.h"
#include "../Expansora/Expansora.h"
//#include "../Ticks/Ticks.h"
//#include "../Error/gestionError.h"
#include "../AppGUI/AppGUI.h"
//#include "Temp_SAFE.h"
//#include "../AppLOG/AppLOG.h"
//#include "../GPRS/AppGPRS.h"
#include "../RFID/RFID.h"

/*** DEBUG ***/
#define HP_CRYO_DBG_ERR_CODES

/*** CONSTANTES ***/
#define HP_CRYO_UPDATE_PERIOD_MS 			100
#define HP_CRYO_REMAP_REFRESH_PERIOD_MS 	50000
#define HP_CRYO_CTRL_PERIOD_MS				100
#define HP_CRYO_VARS_REFRESH_PERIOD_MS		1500
#define HP_CRYO_TEST_VACUM_TIME				0
#define HP_CRYO_TEST_VACUM_TEMP				40.0
#define HP_CRYO_TEST_VACUM_TRT_INI_TEMP		40.0
#define HP_CRYO_CHANGE_STATUS_FLANK_TIME 	100
#define HP_CRYO_IDLE_MIN_VAC_ACCEPTED 		75.0
#define HP_CRYP_TRT_TIME_OFFSET				600									  

#define HP_CRYO_MAX_VACUM_RETRYS				200
#define HP_CRYO_CTRL_MIN_SNS_TEMP_VALUE			-13.0 //PDTE
#define HP_CRYO_CTRL_MIN_SNS_TEMP_TIME			1//5000
#define HP_CRYO_CTRL_MAX_SNS_TEMP_VALUE			35.0
#define HP_CRYO_CTRL_MAX_SNS_TEMP_TIME			3000
#define HP_CRYO_CTRL_DIF_SNS_TEMP_TIME			5000
#define HP_CRYO_CTRL_SNS_TEMP_FAIL_VALUE		100.0
#define HP_CRYO_CTRL_DELTA_MAX_SNS_TEMP_VALUE	10.0
#define HP_CRYO_CTRL_DELTA_MAX_SNS_TEMP_TIME	10000

#define HP_CRYO_DFLT_TST_VAC_TEMP_WINDOW		4.0
#define HP_CRYO_DFLT_TST_VAC_VAC_WAIT_TIME		120	
#define HP_CRYO_DFLT_TST_VAC_TEMP_WAIT_TIME		900
#define HP_CRYO_DFLT_TST_VAC_VAC_FAIL_TIME		60
#define HP_CRYO_DFLT_TST_VAC_TEMP_FAIL_TIME		300
#define HP_CRYO_DFLT_TST_VAC_MIN_SNS_TEMP		10.0
#define HP_CRYO_DFLT_TST_VAC_LOW_TEMP_TIME		180

#define HP_CRYO_DFLT_TRT_INI_TEMP 			40.0
#define HP_CRYO_DFLT_TRT_TEMP_WINDOW		4.0
#define HP_CRYO_DFLT_TRT_VAC_WAIT_TIME		120	
#define HP_CRYO_DFLT_TRT_TEMP_WAIT_TIME		900
#define HP_CRYO_DFLT_TRT_VAC_FAIL_TIME		60
#define HP_CRYO_DFLT_TRT_TEMP_FAIL_TIME		300
#define HP_CRYO_DFLT_TRT_MIN_SNS_TEMP_REL	3.0
#define HP_CRYO_DFLT_TRT_LOW_TEMP_TIME		180

#define HP_CRYO_RFID_LABELS_CODE_NUM_CHAR			2	//V7790 - LOG
#define HP_CRYO_RFID_LABEL_ERASE_INDICATOR			10
#define HP_CRYO_RFID_TIME_MAX_TO_READ				60000 //3 minutos (en milisegundos)
//#define HP_CRYO_RFID_LABEL_AND_HP_TABLE_ELEMENTS	11
#define HP_CRYO_RFID_IS_RUNNING_TOUT_MS				4000

#define HP_CRYO_TRT_VACUM_RETRY_NUM				3
#define HP_CRYO_TRT_VACUM_RETRY_TOUT			300000//180000	//3 minutos
#define HP_CRYO_TRT_ADJUST_VACUM_NUM			4
#define HP_CRYO_TRT_ADJUST_VACUM_TOUT			300000	//5 minutos
#define HP_CRYO_ADJUST_VACUM_RESET_TOUT			10000	//10s
#define HP_CRYO_ADJUST_VACUM_RETRY_WHEN_SET		(0.1)
#define HP_CRYO_ADJUST_VACUM_LUNG_WHEN_SET		(1.1)

#define HP_CRYO_VACUM_FACTOR_RETRY_STD			(0.3)
#define HP_CRYO_VACUM_FACTOR_LUNG_STD			(1.1)
#define HP_CRYO_OVER_HEAT_PERFORMANCE_FACTOR 	(1.0)
#define HP_CRYO_OVER_HEAT_ON_OFF 				1

#define HP_CRYO_CLEAN_UP_VACUM_OFFSET 			70.0
#define HP_CRYO_CLEAN_UP_UMBRAL_VACUM			20.0
#define HP_CRYO_CLEAN_UP_PATIENT_TIME 			15000
#define HP_CRYO_CLEAN_UP_DFLT_COUNTDOWN			90000
#define HP_CRYO_CLEAN_UP_DFLT_TIME_IS_CLEAN		60000
#define HP_CRYO_CLEAN_UP_DFLT_TIME_CANNOT_CLEAN	600000
#define HP_CRYO_CLEAN_UP_DFLT_CLEAN_VACUM		500.0
#define HP_CRYO_CLEAN_UP_RESET_FILTER			3
						
#define HP_CRYO_TRT_VACUM_RETRY_FIRST_TIME		300000
#define HP_CRYO_MAX_VACUM_RETRYS_IN_FIRST_TIME	5
#define HP_CRYO_TRT_VACUM_RETRY_SECOND_TIME		0
#define HP_CRYO_MAX_VACUM_RETRYS_IN_SECOND_TIME	50
#define HP_CRYO_TRT_VACUM_RETRY_THIRD_TIME		0
#define HP_CRYO_TRT_VACUM_RETRY_THIRD_TIME_TEMP	3.0

#define HP_CRYO_TRT_AUTO_DFLT_WAIT_TIME			3000
#define HP_CRYO_TRT_AUTO_DFLT_DETECTION_TIME	4000
#define HP_CRYO_TRT_AUTO_DFLT_FILTER_INC		1
#define HP_CRYO_TRT_AUTO_DFLT_FILTER_DEC		2
#define HP_CRYO_TRT_AUTO_DFLT_FILTER_OK_LVL		1		/* Son en 4 lecturas 3 ok y 1 ko */

#define HP_CRYO_SAT_RGB_TEST_SWITCH_TIME		3000
 
#define HP_CRYO_CTRL_SECOND_WINDOW_LOW_TEMP		((HP->trt.trt_temp_set)-((HP_CRYO_DFLT_LIST_TRT_TEMP_WINDOW[model])/2)-1.0)
/*V7780*/
#define HP_CRYO_CTRL_SECOND_SECURE_WINDOW_LOW_TEMP		((HP->trt.trt_temp_set)-((HP_CRYO_DFLT_LIST_TRT_SECURE_TEMP_WINDOW[model])/2)-0.3)	/*Segunda ventana de frio 0.3 por debajo de ventana medios*/
/*V7780*/

#define HP_CRYO_SLOPE_LIMIT_TO_APPLY_DELTA_ERR		0.5		/* V7780 */
#define HP_CRYO_TIME_REF_TO_APPLY_DELTA_ERR			300000	/* V7780 */	

#define HP_CRYO_TEMP_WINDOW_WHEN_UP_ERROR_TIME_REF	600000

#define HP_CRYO_TIME_CHNG_SET_TEMP_ERR_WIND_MED		240000	/* V7787 */

typedef enum
{
	HP_CRYO_REMAP_FRAME_MAIN_IN_INDEX = 0,
	HP_CRYO_REMAP_FRAME_MAIN_OUT_INDEX = 1,
	HP_CRYO_REMAP_FRAME_CFG_IN_INDEX = 2,
	HP_CRYO_REMAP_FRAME_CFG_OUT_INDEX = 3,
	HP_CRYO_REMAP_FRAME_DBG_IN_INDEX = 4,
	HP_CRYO_REMAP_FRAME_DBG_OUT_INDEX = 5,
	HP_CRYO_REMAP_FRAME_PID_IN_INDEX = 6,
	HP_CRYO_REMAP_FRAME_PID_OUT_INDEX = 7,
	HP_CRYO_REMAP_FRAME_CFG_ENABLE_OUT_INDEX = 8,
	HP_CRYO_REMAP_FRAME_PID_ENABLE_OUT_INDEX = 9,
	HP_CRYO_REMAP_FRAME_DEFINITION_IN_INDEX = 10,
	HP_CRYO_REMAP_FRAME_DEFINITION_OUT_INDEX = 11,
	
	HO_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_INDEX = 12,
	HO_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_INDEX = 13
}cHPcryoRemapFrameIndexes;

const uint16 HP_CRYO_DFLT_TRT_TEMP_WAIT_LIST_TIME[HP_CRYO_NUM_HP_MODELS] = 
{
		/*UNDEFINED*/		0,	
		/*CURVED*/			900,	
		/*TIGHT*/			900,	
		/*STRIGHT*/			900,	
		/*TINY*/			900,	
		/*TINY CURVED*/		900,	
		/*DOUBLE*/			900,
		/*OVAL*/			900,	
		/*OVAL CURVED*/		900,	
		/*ANGLED*/			900		
};

const uint16 HP_CRYO_DFLT_TRT_TEMP_FAIL_LIST_TIME[HP_CRYO_NUM_HP_MODELS] = 
{
		/*UNDEFINED*/		0,	
		/*CURVED*/			300,	
		/*TIGHT*/			300,	
		/*STRIGHT*/			300,	
		/*TINY*/			300,	
		/*TINY CURVED*/		300,	
		/*DOUBLE*/			300,
		/*OVAL*/			300,	
		/*OVAL CURVED*/		300,	
		/*ANGLED*/			300		
};
/* V7780 */
const uint16 HP_CRYO_DFLT_TRT_SECURE_TEMP_FAIL_LIST_TIME[HP_CRYO_NUM_HP_MODELS] = 
{
		/*UNDEFINED*/		0,	
		/*CURVED*/			30,	
		/*TIGHT*/			30,	
		/*STRIGHT*/			30,	
		/*TINY*/			30,	
		/*TINY CURVED*/		30,	
		/*DOUBLE*/			30,
		/*OVAL*/			30,	
		/*OVAL CURVED*/		30,	
		/*ANGLED*/			30		
};
/* V7780 */

const uint8 HP_CRYO_CTRL_DELTA_MAX_SNS_TEMP_LIST_VALUE[HP_CRYO_NUM_HP_MODELS] = 
{
		/*UNDEFINED*/		0,	
		/*CURVED*/			10,	
		/*TIGHT*/			10,	
		/*STRIGHT*/			10,	
		/*TINY*/			10,	
		/*TINY CURVED*/		10,	
		/*DOUBLE*/			17,	/*Mod_Double*/
		/*OVAL*/			10,	
		/*OVAL CURVED*/		10,	
		/*ANGLED*/			10			
};

/* V7780 */
const uint8 HP_CRYO_CTRL_SECURE_DELTA_MAX_SNS_TEMP_LIST_VALUE[HP_CRYO_NUM_HP_MODELS] = 
{
		/*UNDEFINED*/		0,	
		/*CURVED*/			5,	
		/*TIGHT*/			4,	
		/*STRIGHT*/			4,	
		/*TINY*/			5,	
		/*TINY CURVED*/		5,	
		/*DOUBLE*/			8,	/*Mod_Double*/
		/*OVAL*/			5,	
		/*OVAL CURVED*/		5,	
		/*ANGLED*/			5			
};
/* V7780 */

const float HP_CRYO_CTRL_MIN_SNS_TEMP_LIST_VALUE[HP_CRYO_NUM_HP_MODELS] = 
{
		/*UNDEFINED*/		0,	
		/*CURVED*/			-12.0,	
		/*TIGHT*/			-12.0,	
		/*STRIGHT*/			-12.0,	
		/*TINY*/			-9.0,	/*Mod_Tiny_ERROR*/
		/*TINY CURVED*/		-9.0,	/*Mod_Tiny_ERROR*/
		/*DOUBLE*/			-12.0,	
		/*OVAL*/			-12.0,	
		/*OVAL CURVED*/		-10.5,	
		/*ANGLED*/			-10.0			
};
/* V7780 */
const float HP_CRYO_CTRL_SECURE_MIN_SNS_TEMP_LIST_VALUE[HP_CRYO_NUM_HP_MODELS] = 
{
		/*UNDEFINED*/		0,	
		/*CURVED*/			-9.5,	
		/*TIGHT*/			-9.5,	
		/*STRIGHT*/			-9.5,	
		/*TINY*/			-6.5,
		/*TINY CURVED*/		-6.5,
		/*DOUBLE*/			-9.5,	
		/*OVAL*/			-9.5,	
		/*OVAL CURVED*/		-9.5,	
		/*ANGLED*/			-7.5			
};
/* V7780 */


const float HP_CRYO_DFLT_LIST_TRT_TEMP_WINDOW[HP_CRYO_NUM_HP_MODELS] = 
{
	/*UNDEFINED*/		0,	
	/*CURVED*/			4,	
	/*TIGHT*/			4,	
	/*STRIGHT*/			4,	
	/*TINY*/			4,	/*Mod_Tiny_ERROR*/
	/*TINY CURVED*/		4,	/*Mod_Tiny_ERROR*/
	/*DOUBLE*/			4,	
	/*OVAL*/			4,	
	/*OVAL CURVED*/		4,	
	/*ANGLED*/			4		
};

/* V7780 */
const float HP_CRYO_DFLT_LIST_TRT_SECURE_TEMP_WINDOW[HP_CRYO_NUM_HP_MODELS] = 
{
	/*UNDEFINED*/		0,	
	/*CURVED*/			2,	
	/*TIGHT*/			2,	
	/*STRIGHT*/			2,	
	/*TINY*/			2,
	/*TINY CURVED*/		2,
	/*DOUBLE*/			2,	
	/*OVAL*/			2,	
	/*OVAL CURVED*/		2,	
	/*ANGLED*/			2		
};
/* V7780 */

const float HP_CRYO_TEMP_MED_MANAGE_HOT_TEMP_UPPER_THRESSHOLD[HP_CRYO_NUM_HP_MODELS] =	/* V7780 - modificado */
{
	/* (consigna + temp/2 + VALUE) > TempSensor > (consigna - temp/2) */
	/*UNDEFINED*/		0,	
	/*CURVED*/			4,//0,	
	/*TIGHT*/			4,//0,	
	/*STRIGHT*/			4,//0,	
	/*TINY*/			4,//0,
	/*TINY CURVED*/		4,//0,
	/*DOUBLE*/			15,//2,	/* El error de salirse de ventana medios será más permisivo con el Double, tiene 2 grados más por encima de permisividad */
	/*OVAL*/			4,//0,	
	/*OVAL CURVED*/		4,//0,	
	/*ANGLED*/			15//1	/* El delta también tiene mayor permisividad, un grado más por encima */
};

const uint8 HP_CRYO_TIME_RESTRICTION_PER_HP[HP_CRYO_NUM_HP_MODELS] = 
{
						/* DiffT*/
		/*UNDEFINED*/		0,	
		/*CURVED*/			2,	
		/*TIGHT*/			2,	
		/*STRIGHT*/			2,	
		/*TINY*/			1,	
		/*TINY CURVED*/		1,	
		/*DOUBLE*/			2,	
		/*OVAL*/			2,	
		/*OVAL CURVED*/		2,	
		/*ANGLED*/			2	
};

const cHPcryoTrtTimes HP_CRYO_TIME_LIST_PER_HP[HP_CRYO_NUM_HP_MODELS][HP_CRYO_MAX_TIME_LIST] = 
{
						/*T1					T2						T3					*/
		/*UNDEFINED*/	{HP_CRYO_TIME_NO_TIME,	HP_CRYO_TIME_NO_TIME,	HP_CRYO_TIME_NO_TIME},
		/*CURVED*/		{HP_CRYO_TIME_70_MIN, 	HP_CRYO_TIME_50_MIN,	HP_CRYO_TIME_NO_TIME},
		/*TIGHT*/		{HP_CRYO_TIME_70_MIN, 	HP_CRYO_TIME_50_MIN,	HP_CRYO_TIME_NO_TIME},
		/*STRIGHT*/		{HP_CRYO_TIME_70_MIN, 	HP_CRYO_TIME_50_MIN,	HP_CRYO_TIME_NO_TIME},
		/*TINY*/		{HP_CRYO_TIME_45_MIN, 	HP_CRYO_TIME_NO_TIME,	HP_CRYO_TIME_NO_TIME},
		/*TINY CURVED*/	{HP_CRYO_TIME_45_MIN, 	HP_CRYO_TIME_NO_TIME,	HP_CRYO_TIME_NO_TIME},
		/*DOUBLE*/		{HP_CRYO_TIME_70_MIN, 	HP_CRYO_TIME_50_MIN,	HP_CRYO_TIME_NO_TIME},
		/*OVAL*/		{HP_CRYO_TIME_70_MIN, 	HP_CRYO_TIME_50_MIN,	HP_CRYO_TIME_NO_TIME},
		/*OVAL CURVED*/	{HP_CRYO_TIME_70_MIN, 	HP_CRYO_TIME_50_MIN,	HP_CRYO_TIME_NO_TIME},
		/*ANGLED*/		{HP_CRYO_TIME_70_MIN, 	HP_CRYO_TIME_50_MIN,	HP_CRYO_TIME_NO_TIME},
};																	 
const uint8 HP_CRYO_REMAP_FRAME_ID[HP_CRYO_N_REMAP_FRAMES][4] = 
{
		//IDframe(3 x char), 	versión(1 x u8)
		{ 'M', 'A', 'I', 				1},
		{ 'M', 'A', 'I', 				1},
		{ 'C', 'F', 'G', 				1},
		{ 'C', 'F', 'G', 				1},
		{ 'D', 'B', 'G', 				1},
		{ 'D', 'B', 'G', 				1},
		{ 'P', 'I', 'D', 				1},
		{ 'P', 'I', 'D', 				1},
		{ 'C', 'F', 'G',				1},
		{ 'P', 'I', 'D',				1},
		{ 'D', 'E', 'F',				1},
		{ 'D', 'E', 'F',				1},
		
		{ 'F', 'L', 'S', 				1},
		{ 'F', 'L', 'S', 				1}
};
const uint16 HP_CRYO_REMAP_FRAME_DATA[HP_CRYO_N_REMAP_FRAMES][4] =
{
	//DirRelBlockRemap, 					nBytes, 								slot, 	frameDir
	{ HP_CRYO_REMAP_FRAME_MAIN_IN_DIR,		HP_CRYO_REMAP_FRAME_MAIN_IN_SIZE, 		0, 		EXP_REMAP_FRAME_DIR_IN},
	{ HP_CRYO_REMAP_FRAME_MAIN_OUT_DIR, 	HP_CRYO_REMAP_FRAME_MAIN_OUT_SIZE, 		0, 		EXP_REMAP_FRAME_DIR_OUT},
	{ HP_CRYO_REMAP_FRAME_CONFIG_IN_DIR, 	HP_CRYO_REMAP_FRAME_CONFIG_IN_SIZE, 	1, 		EXP_REMAP_FRAME_DIR_IN},
	{ HP_CRYO_REMAP_FRAME_CONFIG_OUT_DIR, 	HP_CRYO_REMAP_FRAME_CONFIG_OUT_SIZE,	1, 		EXP_REMAP_FRAME_DIR_OUT},
	{ HP_CRYO_REMAP_FRAME_DEBUG_IN_DIR, 	HP_CRYO_REMAP_FRAME_DEBUG_IN_SIZE, 		2, 		EXP_REMAP_FRAME_DIR_IN},
	{ HP_CRYO_REMAP_FRAME_DEBUG_OUT_DIR, 	HP_CRYO_REMAP_FRAME_DEBUG_OUT_SIZE, 	2, 		EXP_REMAP_FRAME_DIR_OUT},
	{ HP_CRYO_REMAP_FRAME_PID_IN_DIR, 		HP_CRYO_REMAP_FRAME_PID_IN_SIZE, 		3, 		EXP_REMAP_FRAME_DIR_IN},
	{ HP_CRYO_REMAP_FRAME_PID_OUT_DIR, 		HP_CRYO_REMAP_FRAME_PID_OUT_SIZE, 		3, 		EXP_REMAP_FRAME_DIR_OUT},
	{ HP_CRYO_REMAP_FRAME_CONFIG_IN_DIR, 	1, 										4, 		EXP_REMAP_FRAME_DIR_IN},
	{ HP_CRYO_REMAP_FRAME_PID_IN_DIR, 		1, 										5, 		EXP_REMAP_FRAME_DIR_IN},
	
	{ HP_CRYO_REMAP_FRAME_DEFINITION_IN_DIR,	HP_CRYO_REMAP_FRAME_DEFINITION_IN_SIZE,		6, 		EXP_REMAP_FRAME_DIR_IN},
	{ HP_CRYO_REMAP_FRAME_DEFINITION_OUT_DIR,	HP_CRYO_REMAP_FRAME_DEFINITION_OUT_SIZE,	4, 		EXP_REMAP_FRAME_DIR_OUT},
	
	{ HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR,	HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_SIZE,	7, 		EXP_REMAP_FRAME_DIR_IN},
	{ HP_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_DIR,	HP_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_SIZE,	7, 		EXP_REMAP_FRAME_DIR_OUT}
};

const uint8 HP_CRYO_MODEL_LIST[HP_CRYO_NUM_HP_MODELS] = 
{
	HP_CRYO_MODEL_UNDEFINED,
	HP_CRYO_MODEL_CURVED,
	HP_CRYO_MODEL_TIGHT,
	HP_CRYO_MODEL_STRIGHT,
	HP_CRYO_MODEL_TINY,
	HP_CRYO_MODEL_TINY_CURVED,
	HP_CRYO_MODEL_DOUBLE,
	HP_CRYO_MODEL_OVAL,
	HP_CRYO_MODEL_OVAL_CURVED,
	HP_CRYO_MODEL_ANGLED,
};

const float HP_CRYO_DFLT_MAX_IN_TEMP[HP_CRYO_NUM_HP_MODELS] = 
{
		40.0,//HP_UNDEFINED,
		40.0,//HP_CURVED,
		40.0,//HP_TIGHT,
		40.0,//HP_STRIGHT,
		40.0,//HP_TINY,
		40.0,//HP_TINY_CURVED,
		40.0,//HP_DOUBLE,
		40.0,//HP_OVAL,
		40.0,//HP_OVAL_CURVED,
		40.0,//HP_ANGLED			
};

/* V7778 - TEMP SEC */
/*
const float HP_CRYO_TRT_TEMP_LIST[HP_CRYO_NUM_HP_MODELS] = 
{
	30.0,//HP_UNDEFINED,
	-8.0,//HP_CURVED,			
	-8.0,//HP_TIGHT,
	-8.0,//HP_STRIGHT,
	-5.0,//HP_TINY,
	-5.0,//HP_TINY_CURVED,
	-8.0,//HP_DOUBLE,
	-8.0,//HP_OVAL,
	-8.0,//HP_OVAL_CURVED,
	-6.0,//HP_ANGLED				
};
*/
const float HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[HP_CRYO_NUM_HP_MODELS][HP_CRYO_TEMPERATURE_FEATURES] =		//MOD TEKNON
{
	/*APLICADOR			EARLY_SET_POINT		END_SET_POINT	STANDARD_SET_POINT		TIME_RANGE_2	TIME_RANGE_3	LIMIT_RANGE_1	LIMIT_RANGE_2	TEMP_STEP_R2	TEMP_STEP_R3	EARLY_SET_TEMP_PERCENT_TIME	*/
	/*HP_UNDEFINED*/	{30.0,				30.0,			30.0,					0.0,			0.0,			0.0,			0.0,			0.0,			0.0,			0.0		},
	/*HP_CURVED*/		{-5.0,				-5.0,			-8.0,					5000.0,			6000.0,			1.0,			-5.0,			0.25,			0.1,			0.6		},
	/*HP_TIGHT*/		{-5.0,				-5.0,			-8.0,					5000.0,			6000.0,			1.0,			-5.0,			0.25,			0.1,			0.6		},
	/*HP_STRIGHT*/		{-5.0,				-5.0,			-8.0,					5000.0,			6000.0,			1.0,			-5.0,			0.25,			0.1,			0.6		},
	/*HP_TINY*/			{-5.0,				-5.0,			-5.0,					5000.0,			6000.0,			1.0,			-5.0,			0.25,			0.1,			0.6		},
	/*HP_TINY_CURVED*/	{-5.0,				-5.0,			-5.0,					5000.0,			6000.0,			1.0,			-5.0,			0.25,			0.1,			0.6		},
	/*HP_DOUBLE*/		{-5.0,				-5.0,			-8.0,					5000.0,			6000.0,			1.0,			-5.0,			0.25,			0.1,			0.6		},
	/*HP_OVAL*/			{-5.0,				-5.0,			-8.0,					5000.0,			6000.0,			1.0,			-5.0,			0.25,			0.1,			0.6		},
	/*HP_OVAL_CURVED*/	{-5.0,				-5.0,			-8.0,					5000.0,			6000.0,			1.0,			-5.0,			0.25,			0.1,			0.6		},
	/*HP_ANGLED*/		{-5.0,				-5.0,			-6.0,					5000.0,			6000.0,			1.0,			-5.0,			0.25,			0.1,			0.6		}
};
/* V7778 - TEMP SEC */

const uint32 HP_CRYO_TIME_LIST[HP_CRYO_MAX_TIME_LIST] =
{
	2700,
	3000,
	4200
};

const float HP_CRYO_TRT_VAC_LVL_LIST[HP_CRYO_NUM_HP_MODELS][HP_CRYO_VAC_LVL_NUM] =
{
	{ 0.0, 0.0, 0.0},			//HP_UNDEFINED,
	{ 220.0, 275.0, 330.0},		//HP_CURVED,
	{ 187.0, 242.0, 297.0},		//HP_TIGHT,
	{ 220.0, 275.0, 330.0},		//HP_STRIGHT,
	{ 110.0, 165.0, 220.0},		//HP_TINY,
	{ 110.0, 165.0, 220.0},		//HP_TINY_CURVED,
	{ 121.0, 176.0, 231.0},		//HP_DOUBLE,
	{ 110.0, 165.0, 220.0},		//HP_OVAL,
	{ 143.0, 198.0, 253.0},		//HP_OVAL_CURVED,
	{ 110.0, 165.0, 220.0} 		//HP_ANGLED,
};

const float HP_CRYO_TST_VAC_VAC_LVL_LIST[HP_CRYO_NUM_HP_MODELS][HP_CRYO_VAC_LVL_NUM] =
{
	{ 0.0, 0.0, 0.0},			//HP_UNDEFINED,
	{ 200.0, 250.0, 300.0},		//HP_CURVED,
	{ 170.0, 220.0, 270.0},		//HP_TIGHT,
	{ 200.0, 250.0, 300.0},		//HP_STRIGHT,
	{ 100.0, 150.0, 200.0},		//HP_TINY,
	{ 100.0, 150.0, 200.0},		//HP_TINY_CURVED,
	{ 110.0, 160.0, 210.0},		//HP_DOUBLE,
	{ 100.0, 150.0, 200.0},		//HP_OVAL,
	{ 130.0, 180.0, 230.0},		//HP_OVAL_CURVED,
	{ 100.0, 150.0, 200.0} 		//HP_ANGLED,
};

const uint8 HP_CYRO_LABEL_REQUESTED [HP_CRYO_NUM_LABELS][HP_CRYO_RFID_LABEL_AND_HP_TABLE_ELEMENTS] = 
{
/*	UNDEFINED			Curved				Tight				Stright 			Tiny				Tiny Curved			Double				Oval				Oval Curved			Angled(DELTA)		ERASE/NOT_ERASE		*/
	{HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	RFID_NOT_ERASE_LABEL},		//UNDEFINED
	{HP_CRYO_NOT_VALID,	HP_CRYO_DEFAULT,	HP_CRYO_DEFAULT,	HP_CRYO_DEFAULT,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_DEFAULT,	HP_CRYO_DEFAULT,	HP_CRYO_VALID,		RFID_ERASE_LABEL},			//Z0	(ERASE)		TODO
	{HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_DEFAULT,	HP_CRYO_DEFAULT,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	RFID_ERASE_LABEL},			//Z1	(ERASE)		TODO
	{HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_DEFAULT,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	RFID_ERASE_LABEL},			//Z2	(ERASE)		TODO
	{HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_DEFAULT,	RFID_ERASE_LABEL},			//Z3	(ERASE)		TODO
	{HP_CRYO_NOT_VALID,	HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		RFID_NOT_ERASE_LABEL},		//DM	(NOT_ERASE)
	{HP_CRYO_NOT_VALID,	HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		HP_CRYO_VALID,		RFID_NOT_ERASE_LABEL},		//PD 	(NOT ERASE)(FOR PRODUCTION)
	{HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	HP_CRYO_NOT_VALID,	RFID_NOT_ERASE_LABEL},		//ERASED
};

const uint8 HP_CRYO_SENSOR_GROUPS [HP_CRYO_NUM_HP_MODELS][HP_CRYO_MAX_GRUPOS_DE_SONDAS][HP_CRYO_MAX_SONDAS_GRUPO] =
{
						/*	G1		G2			G3		G4	*/
		/*Undefined*/	{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},	/*0 sensores de control*/
		/*Curved*/		{{2,3,4,0},{6,7,8,0},{0,0,0,0},{0,0,0,0}},	/*6 sensores de control*/
		/*Tight*/		{{2,3,4,0},{6,7,8,0},{0,0,0,0},{0,0,0,0}},	/*6 sensores de control*/
		/*Stright*/		{{2,3,4,0},{6,7,8,0},{0,0,0,0},{0,0,0,0}},	/*6 sensores de control*/
		/*Tiny*/		{{1,2,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},	/*2 sensores de control*/
		/*Tiny Curved*/	{{1,2,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},	/*2 sensores de control*/
		/*Double*/		{{1,2,0,0},{3,4,0,0},{5,6,0,0},{7,8,0,0}},	/*8 sensores de control*/
		/*Oval*/		{{1,2,3,0},{4,5,6,0},{0,0,0,0},{0,0,0,0}},	/*6 sensores de control*/	/*V7785*/
		/*Oval Curved*/	{{1,2,3,4},{5,6,7,8},{0,0,0,0},{0,0,0,0}},	/*8 sensores de control*/
		/*Andled*/		{{7,8,9,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}	/*3 sensores de control*/
};

/* V7785 */
const uint8 HP_CRYO_ALL_SENSOR [HP_CRYO_NUM_HP_MODELS][HP_CRYO_MAX_TEMP_SNS] =
{
						/*S1 S2 S3 S4 S5 S6 S7 S8 S9	*/
		/*Undefined*/	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},	/*0 sensores*/
		/*Curved*/		{ 1, 2, 3, 4, 5, 6, 7, 8, 0},	/*8 sensores*/
		/*Tight*/		{ 1, 2, 3, 4, 5, 6, 7, 8, 0},	/*8 sensores*/
		/*Stright*/		{ 1, 2, 3, 4, 5, 6, 7, 8, 0},	/*8 sensores*/
		/*Tiny*/		{ 1, 2, 0, 0, 0, 0, 0, 0, 0},	/*2 sensores*/
		/*Tiny Curved*/	{ 1, 2, 0, 0, 0, 0, 0, 0, 0},	/*2 sensores*/
		/*Double*/		{ 1, 2, 3, 4, 5, 6, 7, 8, 0},	/*8 sensores*/
		/*Oval*/		{ 1, 2, 3, 4, 5, 6, 7, 0, 0},	/*7 sensores*/
		/*Oval Curved*/	{ 1, 2, 3, 4, 5, 6, 7, 8, 0},	/*8 sensores*/
		/*Andled*/		{ 0, 0, 0, 0, 0, 0, 7, 8, 9},	/*3 sensores*/
};
/* V7785 */

const uint8 HP_CRYO_MAX_SNS_KO_PER_GROUP [HP_CRYO_NUM_HP_MODELS] =
{
		/*	UNDEFINED	Curved	Tight	Stright	Tiny	TinyCurved	Double	Oval	OvalCurved	Angled	*/
			0,			1,		1,		1,		0,		0,			0,		2,		2,			1		/* V7780 */
		/*	0,			2,		2,		2,		1,		1,			1,		3,		3,			2		old */
};

// Gestión de la limitación de la etiqueta DM en función de la versión codificada en App.h
#ifdef APP_SW_VER_DM_NO_LIMIT
#define HP_CRYO_LABEL_DM_TEMP ( -11.0)
#define HP_CRYO_LABEL_DM_TIME ( 4200)
#else
#define HP_CRYO_LABEL_DM_TEMP ( 10.0)
#define HP_CRYO_LABEL_DM_TIME ( 600)
#endif

const float HP_CRYO_LABEL_TEMPERATURE_LIMIT [HP_CRYO_NUM_LABELS] = 
/* 	UNDEFINED, 	Z0	  	Z1	 	Z2		Z3		DM 							PD*/
{	30.0, 		-11.0, 	-11.0, 	-11.0,	-11.0,	HP_CRYO_LABEL_DM_TEMP,		-11.0};	

const uint16 HP_CRYO_LABEL_TIME_LIMIT [HP_CRYO_NUM_LABELS] = 
/* 	UNDEFINED, 	Z0	  	Z1	 	Z2		Z3		DM 						PD*/
{	0,			4200,	4200,	4200,	4200,	HP_CRYO_LABEL_DM_TIME,	4200};

const cHPcryoLabelsCleanUpOptions HP_CRYO_LABEL_CLEANUP_REQ_LIMIT [HP_CRYO_NUM_LABELS] =
/* 	UNDEFINED, 						Z0	  						Z1	 						Z2							Z3							DM 							PD*/
{	HP_CRYO_LABEL_NOT_REQ_CLEANUP,	HP_CRYO_LABEL_REQ_CLEANUP,	HP_CRYO_LABEL_REQ_CLEANUP,	HP_CRYO_LABEL_REQ_CLEANUP,	HP_CRYO_LABEL_REQ_CLEANUP,	HP_CRYO_LABEL_REQ_CLEANUP,	HP_CRYO_LABEL_REQ_CLEANUP};

const char HP_CRYO_LABEL_CODE [HP_CRYO_NUM_LABELS][HP_CRYO_RFID_LABELS_CODE_NUM_CHAR] = 
{
	{0, 0},		//UNDEFINED
	{'Z', 0},	//Z0
	{'Z', 1},	//Z1
	{'Z', 2},	//Z2
	{'Z', 3},	//Z3
	{'D', 'M'},	//DM
	{'P', 'D'},	//PD
    {(char)164, 91},	//ERASED
};

const uint8 HP_CRYO_AUTO_MODE_AVAIBLE[HP_CRYO_NUM_HP_MODELS] = 
{
#ifdef APP_SW_VER_AUTO_ENABLE
	0,//HP_UNDEFINED,
	1,//HP_CURVED,
	1,//HP_TIGHT,
	1,//HP_STRIGHT,
	0,//HP_TINY,
	0,//HP_TINY_CURVED,
	1,//HP_DOUBLE,
	1,//HP_OVAL,
	1,//HP_OVAL_CURVED,
	1,//HP_ANGLED		
#else
	0,//HP_UNDEFINED,
	0,//HP_CURVED,
	0,//HP_TIGHT,
	0,//HP_STRIGHT,
	0,//HP_TINY,
	0,//HP_TINY_CURVED,
	0,//HP_DOUBLE,
	0,//HP_OVAL,
	0,//HP_OVAL_CURVED,
	0,//HP_ANGLED	
#endif
};

/*** TIPOS DE DATOS ***/

/*** VARIABLES GLOBALES ***/
tHPcryoData HPcryoData[HPCRYO_MAX_N_PERIFS];

/*** DECLARACION DE FUNCIONES LOCALES ***/
void HPcryoTestVacumUpdate( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoTrtUpdate( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoCleanUpUpdate( tHPcryoData *HP, tPRFdata *PRF);														  
void HPcryoFtg0Update( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoSATupdate( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoClearData( tHPcryoData *HP);
returnstatus_t HPcryoRefreshFrameMain( tHPcryoData *HP, tPRFdata *PRF);
returnstatus_t HPcryoRefreshFrameCfg( tHPcryoData *HP, tPRFdata *PRF);
returnstatus_t HPcryoRefreshFrameDbg( tHPcryoData *HP, tPRFdata *PRF);
returnstatus_t HPcryoReadFrames( tHPcryoData *HP, tPRFdata *PRF);
returnstatus_t HPcryoWriteFrames( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoInitFrameMainData( tHPcryoData *HP);
void HPcryoInitFrameCfgData( tHPcryoData *HP);
void HPcryoInitFrameDbgData( tHPcryoData *HP);
void HPcryoInitFramePIDdata( tHPcryoData *HP);

/* Memoria FLASH aplicador */
returnstatus_t HPcryoInitFrameFlashMemoryData( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoCloseFrameFlashMemoryData( tHPcryoData *HP, tPRFdata *PRF);
returnstatus_t HPcryoEraseFlashMemory ( uint32 addr, uint8 num_sectors, tHPcryoData *HP, tPRFdata *PRF);
returnstatus_t HPcryoWriteFlashMemory ( uint32 addr, uint8 nBytes, uint8 *buffer, tHPcryoData *HP, tPRFdata *PRF);
returnstatus_t HPcryoReadFlashMemory ( uint32 addr, uint8 nBytes, uint8 *buffer, tHPcryoData *HP, tPRFdata *PRF);
/* Memoria FLASH aplicador */

returnstatus_t HPcryoSetRemap( cHPcryoRemapFrameIndexes index, tPRFdata *PRF);
returnstatus_t HPcryoClearRemap( cHPcryoRemapFrameIndexes index, tPRFdata *PRF);
returnstatus_t HPcryoRefreshRemapPack( tPRFdata *PRF);
returnstatus_t HPcryoClearRemapPack( tPRFdata *PRF);
void HPcryoCtrlTempSensorValues( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoCtrlWhenError( uint32 *tout, uint32 errTime, uint16 errCode);
void HPcryoCtrlTempSensorCalibration( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoCtrlManStatus( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoCtrlTempConvEq( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoCtrlAlarmFlags( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoCtrlVacumRetrys( tHPcryoData *HP, tPRFdata *PRF);	
void HPcryoTrtAutoModeHdlr( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoTrtAutoModeRestart( tHPcryoData *HP, tPRFdata *PRF);															   

void HPcryoTrtSetPointOsc( uint32 TimeLoop, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoManageTempMedError( tHPcryoData *HP, tPRFdata *PRF);

/* V7778 - TEMP SEC */
uint8 HPcryo_Cooling_process ( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryo_Resume_Cooling ( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryo_get_lower_temp_sensor ( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryo_TRT_HP_temp_status ( tHPcryoData *HP, tPRFdata *PRF);
/* V7778 - TEMP SEC */

/* V7780 */
float HPcryo_get_temp_slope ( tHPcryoData *HP, tPRFdata *PRF);
/* V7780 */

/*
 * Función HPCryoRFIDcheckLabel
 * Descripción:
 *      Se encarga de la gestión de las llamadas al módulo RFID. Busca la toallita por defecto, lee la que se coloca, determina si es aceptable o no, si ha de borrarla o no, etc.
 *      Se ha de gestionar el parametro de devolución (SUCCESS, ERROR, RUNNING).
 * Parámetros:
 * 		- Indice de la etiqueta RFID leida	-	uint8 *Label_Read
 * 		
 * 		- Tiempo establecido para la lectura	-	uint16 RFID_time_read
 * 		
 * 		- Código de error especifico interno del módulo RFID	-	cHPcryoRFID_err *RFID_err_code
 * 		
 * 		- tHPcryoData *HP
 * 		
 * 		- tPRFdata *PRF
 * Retorno:
 *      - Estado del proceso	-	returnstatus_t
 * Errores:
 * 
 */
returnstatus_t HPCryoRFIDcheckLabel( uint8 *Label_Read, uint16 RFID_time_read, cHPcryoRFID_err *RFID_err_code, tHPcryoData *HP, tPRFdata *PRF);

/*
 * Función HPCryoRFIDreset
 * Descripción:
 *      Se encarga de realizar un reset de las variables relacionadas con la lectura RFID, además de liberar el recurso del periferico que lo tenía reservado
 * Parámetros:
 * 		- tHPcryoData *HP
 * 		
 * 		- tPRFdata *PRF
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void HPCryoRFIDreset( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoRFIDlabelLimits( uint8 lblIndex, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtVacumRetry( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoTrtAdjustVacumUpdate( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoCleanUpVacumIsFree( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoVaccFree2Clean ( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoVaccResuctionRqst ( tHPcryoData *HP, tPRFdata *PRF);
cHPcryoCleanUpStatus HPcryoCleanUpCycles( tHPcryoData *HP, tPRFdata *PRF);
cHPcryoCleanUpStatus HPcryoCleanUpPause ( tHPcryoData *HP, tPRFdata *PRF);
/*** FUNCIONES ***/
/* CALLBACKS */
returnstatus_t HPcryoInitCbk( tPRFdata *PRF)
{
	returnstatus_t ret = RUNNING;
//	tHPcryoData *HP = &( HPcryoData[PRF->indexInTypeArray]);
	
//	switch( HP->init.status)
//	{
//		case HP_CRYO_INIT_RQST_CONFIG: /* OBTENEMOS LA CONFIGURACION DEL HP */
//			/* Habilitamos la trama de configuracion OUT. Para ello primero preparamos el buffer de la IN
//			 * indicando que queremos habilitar el OUT y preparamos el buffer OUT de modo que podamos ver
//			 * cuando hemos recibido la respuesta.
//			 * Para saber que ya tenemos la respuesta utilizaremos el mismo flag que usamos para habilitar
//			 * la trama OUT ya que ambas tramas son iguales, es decir, en el buffer OUT lo ponemos a cero y
//			 * en el IN a 1. Cuando el HP haya contestado en el OUT tendremos a 1 tambien el flag y sabremos
//			 * que el resto de datos son correctos.*/
//			HP->frames.cfgIn.data.u8BloqueHabilitado = 1;
//			HP->frames.cfgOut.data.u8BloqueHabilitado = 0;
//			ret = EXPremapFrameSetData(	HP_CRYO_REMAP_FRAME_CONFIG_IN_DIR + PRF->myDirInRemapFramesBuffer, 1,
//									 	&( HP->frames.cfgIn.vector[1]));
//			if( ret == ERROR){ return ret;}
//			ret = EXPremapFrameSetData(	HP_CRYO_REMAP_FRAME_CONFIG_OUT_DIR + PRF->myDirInRemapFramesBuffer, 1,
//										&( HP->frames.cfgOut.vector[1]));
//			if( ret == ERROR){ return ret;}
//			ret = HPcryoSetRemap( HP_CRYO_REMAP_FRAME_CFG_ENABLE_OUT_INDEX, PRF);
//			if( ret == ERROR){ return ret;}
//			ret = HPcryoSetRemap( HP_CRYO_REMAP_FRAME_CFG_OUT_INDEX, PRF);
//			if( ret == ERROR){ return ret;}
						
//			/* Deshabilitamos la lectura de la frame PID out para descargar las comunicaciones.
//			 * No se va a utilizar. */
//			HP->frames.PIDin.data.u8BloqueHabilitado = 0;
//			ret = EXPremapFrameSetData(	HP_CRYO_REMAP_FRAME_PID_IN_DIR + PRF->myDirInRemapFramesBuffer, 1,
//										&( HP->frames.PIDin.vector[1]));
//			ret = HPcryoSetRemap( HP_CRYO_REMAP_FRAME_PID_ENABLE_OUT_INDEX, PRF);
//			if( ret == ERROR){ return ret;}
			
//			/* Pasamos al siguiente estado */
//			HP->init.status = HP_CRYO_INIT_GET_CONFIG_DATA;
			
//			/* Indicamos que el motor esta en proceso */
//			ret = RUNNING;
//			break;
//		case HP_CRYO_INIT_GET_CONFIG_DATA: /* LECTURA DE DATOS DE CONFIGURACION DEL HP */
//			/* Vamos leyendo el flag de activación del OUT de config hasta que valga 1. Entonces podemos
//			 * recuperar los datos de configuración del HP */
//			ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_CONFIG_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//										HP_CRYO_REMAP_FRAME_CONFIG_OUT_SIZE,
//										&( HP->frames.cfgOut.vector[1]));
//			if( ret == ERROR){ HP->init.status = HP_CRYO_INIT_RQST_CONFIG; return ret;}
			
//			/* Comprobar si ya hemos recibido los datos de configuración */
//			if( HP->frames.cfgOut.data.u8BloqueHabilitado)
//			{
//				/* Ya se han recibido los datos, primero eliminamos los remapeos que ya no vamos a usar */
//				ret = HPcryoClearRemap( HP_CRYO_REMAP_FRAME_CFG_ENABLE_OUT_INDEX, PRF);
//				if( ret == ERROR){ HP->init.status = HP_CRYO_INIT_RQST_CONFIG; return ret;}
//				//ret = HPcryoClearRemap( HP_CRYO_REMAP_FRAME_CFG_OUT_INDEX,
//				//					  PRFdata[perifIndex].IDperifHW);
//				//if( ret == ERROR){ status[HPindex] = 0; return ret;}
//				//AQUI SE DA POR SENTADO QUE LA TRAMA DE PID YA SE HA PROCESADO
//				ret = HPcryoClearRemap( HP_CRYO_REMAP_FRAME_PID_ENABLE_OUT_INDEX, PRF);
//				if( ret == ERROR){ HP->init.status = HP_CRYO_INIT_RQST_CONFIG; return ret;}
				
//				/* Inicializamos todos los buffers de las tramas */
//				HPcryoInitFrameMainData( HP);
//				HPcryoInitFrameCfgData( HP);
//				HPcryoInitFrameDbgData( HP);
//				/* NO UTILIZAMOS LA TRAMA PID
//				HPcryoInitFramePIDdata( HP); */
				
//				/* Enviamos los buffers de remapeo ya inicializados */
//				ret = EXPremapFrameSetData(	HP_CRYO_REMAP_FRAME_MAIN_IN_DIR + PRF->myDirInRemapFramesBuffer,
//											HP_CRYO_REMAP_FRAME_MAIN_IN_SIZE,
//										 	&( HP->frames.mainIn.vector[1]));
//				if( ret == ERROR){ HP->init.status = HP_CRYO_INIT_RQST_CONFIG; return ret;}
//				ret = EXPremapFrameSetData(	HP_CRYO_REMAP_FRAME_CONFIG_IN_DIR + PRF->myDirInRemapFramesBuffer,
//											HP_CRYO_REMAP_FRAME_CONFIG_IN_SIZE,
//										 	&( HP->frames.cfgIn.vector[1]));
//				if( ret == ERROR){ HP->init.status = HP_CRYO_INIT_RQST_CONFIG; return ret;}
//				ret = EXPremapFrameSetData(	HP_CRYO_REMAP_FRAME_DEBUG_IN_DIR + PRF->myDirInRemapFramesBuffer,
//											HP_CRYO_REMAP_FRAME_DEBUG_IN_SIZE,
//										 	&( HP->frames.dbgIn.vector[1]));
//				if( ret == ERROR){ HP->init.status = HP_CRYO_INIT_RQST_CONFIG; return ret;}
//				/* NO UTILIZAMOS LA TRAMA PID PARA NADA
//				ret = EXPremapFrameSetData(	HP_CRYO_REMAP_FRAME_PID_IN_DIR + PRF->myDirInRemapFramesBuffer,
//											HP_CRYO_REMAP_FRAME_PID_IN_SIZE,
//										 	&( HP->frames.PIDin.vector[1]));
//				if( ret == ERROR){ HP->init.status = HP_CRYO_INIT_RQST_CONFIG; return ret;}*/
				
//				/* Finalmente ya podemos configurar todos los remapeos. El buffer de remapeo ya esta
//				 * correctamente inicializado */
//				ret = HPcryoRefreshRemapPack( PRF);
//				if( ret == ERROR){ HP->init.status = HP_CRYO_INIT_RQST_CONFIG; return ret;}
				
//				/* Configuramos los factores de resucción y pulmon para este HP en la Expansora */
//				EXP_UCconfigHPvacumFactors( HP_CRYO_VACUM_FACTOR_RETRY_STD, HP_CRYO_VACUM_FACTOR_LUNG_STD, PRF->IDperifHW);
				
//				/* Configuramos la gestion del calor que sobra en la expansora para este HP */
//				EXP_UCconfigHPoverHeat( HP_CRYO_OVER_HEAT_ON_OFF, HP_CRYO_OVER_HEAT_PERFORMANCE_FACTOR, PRF->IDperifHW);
				
//#ifdef APP_SW_VER_NEW_CLEANUP_MODE
				
				
//				/* DEBUG DEBUG */
////				HP->cleanUp.cancelled_times = HPcryoCleanUpCancelledTimesReceiveFromHP ( HP, PRF);
////				HP->cleanUp.cancelled_times = 1;
////				HPcryoCleanUpCancelledTimesSentToHP (HP->cleanUp.cancelled_times, HP, PRF);
////
////				HP->cleanUp.cancelled_times = HPcryoCleanUpCancelledTimesReceiveFromHP ( HP, PRF);
////				HP->cleanUp.cancelled_times = 2;
////				HPcryoCleanUpCancelledTimesSentToHP (HP->cleanUp.cancelled_times, HP, PRF);
////
////				HP->cleanUp.cancelled_times = HPcryoCleanUpCancelledTimesReceiveFromHP ( HP, PRF);
////				HP->cleanUp.cancelled_times = 3;
////				HPcryoCleanUpCancelledTimesSentToHP (HP->cleanUp.cancelled_times, HP, PRF);
////
////				HP->cleanUp.cancelled_times = HPcryoCleanUpCancelledTimesReceiveFromHP ( HP, PRF);
//				/* DEBUG DEBUG */
				
				
//				/* Leemos el número de cancelaciones de la limpieza que tiene registrado el aplicador */
//				HP->cleanUp.cancelled_times = HPcryoCleanUpCancelledTimesReceiveFromHP ( HP, PRF);
//				/* Si el numero de cancelaciones leida es superior al máximo o inferior al mínimo, se considera que requiere de la limpieza forzada */
//				if(( HP->cleanUp.cancelled_times > HP_CRYO_CLEAN_UP_MAX_TIMES_CANCEL) || (HP->cleanUp.cancelled_times < 0))
//				{
//					HP->cleanUp.cancelled_times = HP_CRYO_CLEAN_UP_MAX_TIMES_CANCEL;
//				}
//#endif
				
//				/* Finalmente indicamos que el HP tiene que limpiarse */
//#ifdef APP_SW_VER_CLEANUP_ENABLE
//				HP->cleanUpRqst = HP_CRYO_CLEAN_UP_RQST_FORCED; 				//CleanUpEnable
//#endif
				
//#ifdef APP_SW_VER_NEW_CLEANUP_MODE
//				HP->cleanUpInitOrEnd = HP_CRYO_CLEAN_UP_END_OF_TRT;
//#else
//				HP->cleanUpInitOrEnd = HP_CRYO_CLEAN_UP_INIT_OF_TRT;
//#endif
				
//				HP->PrevStatusSAT = 0;		/* V7787 - Variable empleada para gestion de errores continuos con interrupción por SAT */
				
//				/* Todo correcto, el HP esta inicializado y comunicando con la expansora */
//				HP->init.status = HP_CRYO_INIT_RQST_CONFIG;
//				ret = SUCCESS;
//			}
//			else
//			{
//				/* Aun no hemos recibido los datos de configuración, seguimos esperando */
//				ret = RUNNING;
//			}
//			break;
//		default:
//			/* No podemos estar en este estado, reseteamos la logica */
//			HP->init.status = HP_CRYO_INIT_RQST_CONFIG;
//			ret = ERROR;
//			break;
//	}
	
	/* Devolvemos el estado del motor */
	return ret;
}

returnstatus_t HPcryoUpdateCbk( tPRFdata *PRF)
{
	returnstatus_t ret;
//	tHPcryoData *HP = &( HPcryoData[PRF->indexInTypeArray]);
	
//	/*V7775*/
//	uint32 TRTtime_elapse, TRTtime_total;
//	/*V7775*/
	
//	float EnvTemp;
	
//	/* Timeamos el update */
//	if( TICKS_DiffTicks( HP->time.updateTime_ms) < HP->time.updatePeriod_ms){ return RUNNING;}
//	HP->time.updateTime_ms = TICKS_GetTicks();
	
//	/* Refresco de las estructuras de remap */
//	if( TICKS_DiffTicks( HP->time.remapTime_ms) > HP->time.remapPeriod_ms)
//	{
//		HP->time.remapTime_ms = TICKS_GetTicks();
//		ret = HPcryoRefreshRemapPack( PRF);
//		if( ret == ERROR){ return ret;}
//	}
//	else
//	{
//		/* Cuando no enviamos las tramas de remap ejecutamos el refresco de las tramas y
//		 * toda la lógica que depende de sus valores. Esto es para no solapar envios de
//		 * remaps con envios y lecturas de tramas. */
		
//		/* Refresco de las variables del HP timeado */
//		//if( TICKS_DiffTicks( HP->time.refreshTime_ms) > HP->time.refreshPeriod_ms)
//		//{
//			//HP->time.refreshTime_ms = TICKS_GetTicks();
//			ret = HPcryoReadFrames( HP, PRF);
//			if( ret == ERROR){ return ret;}
//		//}
		
//		/* Controles de seguridad */
//		if( TICKS_DiffTicks( HP->time.ctrlTime_ms) > HP->time.ctrlPeriod_ms &&	//SAT
//			HP->status != HP_CRYO_SAT)											//SAT
//		{
//			HP->time.ctrlTime_ms = TICKS_GetTicks();
			
//			/* - Control de la calibración de las sondas de temperatura */
//			HPcryoCtrlTempSensorCalibration( HP, PRF);
		
//			/* - Control de las temperaturas de las nueve sondas */
//			HPcryoCtrlTempSensorValues( HP, PRF);
			
//			/* - Gestion de F.A locas - V7790 - */
			
			
//			/* - Control de estados de error del HP */
//			HPcryoCtrlManStatus( HP, PRF);
			
//			/* - Control de la ecuación de conversion de las temperaturas */
//			HPcryoCtrlTempConvEq( HP, PRF);
			
//			/* - Control de los flags de alarma generados por el HP */
//			HPcryoCtrlAlarmFlags( HP, PRF);
//		}
		
//		/* Logica del control del ajuste de vacum durante el tratamiento. Va aqui porque necesitamos
//		 * resetear los ajustes de gestión del vacum en la EXP cuando ya no hay tratamiento para evitar
//		 * glitches */
//		HPcryoTrtAdjustVacumUpdate( HP, PRF);
		
//		/* Logica de estados del HP */
//		switch( HP->status)
//		{
//			case HP_CRYO_TEST_INIT:
//				/* En este estado el HP esta realizando el test inicial. Es un estado temporal en el que solo
//				 * estamos mientras dure el test, es decir, mientras estemos en el estado MAN_INIT */
//				if( HP->frames.mainOut.data.estado != HP_CRYO_MAN_INIT)
//				{
//					/* Vamos siempre al estado IDLE */
//					HPcryoIdle( 1, HP, PRF);
//					HP->trt.TrtRequested = 0;
//				}
//				break;
//			case HP_CRYO_IDLE:
//				/* Forzamos IDLE para asegurar que se va  aeste estado */
//				HPcryoIdle( 1, HP, PRF);
				
//				/* Si hay limpieza pendiente la lanzamos */
//				if( HP->cleanUpRqst != HP_CRYO_CLEAN_UP_RQST_NONE)
//				{
//					if( HPcryoCleanUpStartDflt( HP->cleanUpRqst == HP_CRYO_CLEAN_UP_RQST_FORCED, HP, PRF))
//					{
//						/* Reseteamos la petición */
//#ifdef APP_SW_VER_CLEANUP_ENABLE
//						HP->cleanUpRqst = HP_CRYO_CLEAN_UP_RQST_NONE;		//CleanUpEnable
//#endif
//						//HP->cleanUpInitOrEnd = HP_CRYO_CLEAN_UP_NONE;
//					}
//				}
//				else if(HP->trt.TrtRequested)
//				{
//					HPcryoTrtStartDflt(	HP->trt.TrtParameters.mode,
//										HP->trt.TrtParameters.time,
//										HP->trt.TrtParameters.vacLvl,
//										HP->trt.TrtParameters.reqLabel,
//										HP->trt.TrtParameters.useDfltAlarmCfg,
//										HP, PRF);
//				}
//				else if(EXP_UCoscTempStatus())
//				{
//					/* Si se supera la Tamb -3ºC se inicia el enfriamiento del aplicador hasta Tamb -8ºC y se espera a que supere de nuevo la Tamb -3ºC*/
//					if(EXPdata.perif[PRF->IDperifHW].data.fields.version < HP_CRYO_SW_HP_THRESSHOLD_CTRL_OSC_TEMP)	/*Miramos que la versión del aplciador sea inferior a las 20*/
//					{
//						EnvTemp = EXP_UCgetEnvTemp();		/*Tomamos la temperatura ambiente*/
						
//						if(HP->frames.mainOut.data.fTempManipulo > (EnvTemp - HP_CRYO_UP_THRSHOLD_WIN_TEMP_OSC_IDLE)){	HP->status = HP_CRYO_TEST_PELTIERS_OSC_TEMP;}
//					}
//				}

//				break;
//			case HP_CRYO_TEST_VACUM:
//				/* Actualizamos el test de vacum */
//				HPcryoTestVacumUpdate( HP, PRF);
				
//				/* Según el estado del test cambiamos de estado la logica del HP */
//				switch( HP->tstVac.status)
//				{
//					case HP_CRYO_TEST_VAC_DONE:
//					case HP_CRYO_TEST_VAC_FAIL:
//						/* Hemos terminado el test de vacum con éxito o con fallo. En cualquier caso vamos
//						 * al estado de reposo */
//						HPcryoIdle( 1, HP, PRF);
//						break;
//					case HP_CRYO_TEST_VAC_RUN_WAITING_USER_START:
//					case HP_CRYO_TEST_VAC_RUN_VACUM:
//					case HP_CRYO_TEST_VAC_RUN_WAITING_USER_END:
//						/* El test se esta realizando, no hacemos nada */
//						break;
//					default:
//						/* Situación no válida, pasamos a IDLE e indicamos FAIL */
//						HPcryoTestVacumStop( 1, HP, PRF);
//						HP->tstVac.status = HP_CRYO_TEST_VAC_FAIL;
//						HPcryoIdle( 1, HP, PRF);
//						break;
//				}
//				break;
//			case HP_CRYO_TREATMENT:
//				/* Actualizamos el tratamiento */
//				HPcryoTrtUpdate( HP, PRF);
				
//				/* Según el estado del tratamiento cambiamos la logica del HP */
//				switch( HP->trt.status)
//				{
//					case HP_CRYO_TREATMENT_RUN_WAITING_RFID:
//						/* V7775 */
//						if(HP->trt.vacumRetryRlsTime != 0)
//						{
//							TRTtime_elapse = HPcryoTrtGetTimeSeconds( HP, PRF);
//							TRTtime_total =  HPcryoTrtGetTreatmentTotalTimeSeconds( HP, PRF);
//							EXP_UCupdateTRTtimeReuseLabel (PRF->IDperifHW, TRTtime_total - TRTtime_elapse);
//						}
						
//						/* Tratamiento en curso, no hacemos nada */
//						HP->trt.TrtRequested = 0;
//						break;
//						/* V7775 */
//					case HP_CRYO_TREATMENT_RUN_WAITING_USER_START:
//					case HP_CRYO_TREATMENT_RUN_VACUM:
//					case HP_CRYO_TREATMENT_RUN_COOLING:
//					case HP_CRYO_TREATMENT_RUN_WAITING_USER_END:
//					case HP_CRYO_TREATMENT_RUN_PAUSE:
//						/* Tratamiento en curso, no hacemos nada */
//						HP->trt.TrtRequested = 0;
//						break;
//					case HP_CRYO_TREATMENT_DONE:
//					case HP_CRYO_TREATMENT_FAIL:
//						/* V7790 - Reiniciamos el numero del tratamiento */
//						HP->trt.HPtreatment_Num = 0;
//						HP->trt.Label_accepted = HP_CRYO_LABEL_UNDEFINED;
//						/* Tratamiento finalizado, pasamos a reposo */
//						HPcryoIdle( 1, HP, PRF);
//						break;
//					default:
//						/* Situación no valida, pasamos a reposo e indicamos FAIL */
//						HPcryoTrtStop( 1, HP, PRF);
//						HP->trt.status = HP_CRYO_TREATMENT_FAIL;
//						HPcryoIdle( 1, HP, PRF);
//						break;
//				}
//				break;
//			case HP_CRYO_CLEAN_UP:
//				/* Actualizamos la limpieza */
//				HPcryoCleanUpUpdate( HP, PRF);
				
//				/* Segun el estado cambiamos la logica del HP */
//				switch( HP->cleanUp.status)
//				{
//					case HP_CRYO_CLEAN_UP_COUNTDOWN:
//					case HP_CRYO_CLEAN_UP_CHECK_PATIENT:
//					case HP_CRYO_CLEAN_UP_WAITING_USER:
//					case HP_CRYO_CLEAN_UP_CLEANING:
//					case HP_CRYO_CLEAN_UP_WAIT_VACUM:
//						/* Limpieza en curso, no hacemos nada */
//						break;
//					case HP_CRYO_CLEAN_UP_DONE:
//						/* Finalizado, pasamos a reposo */
//						HPcryoIdle( 0, HP, PRF);
//						/* Al completar una limpieza reseteamos el contador de limpiezas y lo grabamos en el aplicador */
//						HP->cleanUp.cancelled_times = 0;
//						HPcryoCleanUpCancelledTimesSentToHP(HP->cleanUp.cancelled_times, HP, PRF);
//						break;
//					case HP_CRYO_CLEAN_UP_FAIL:
//						/* Finalizado, pasamos a reposo */
//						HPcryoIdle( 0, HP, PRF);
						
//						/* Generamos error si hemos salido con FAIL */
//						ERR_add( Error_HPcannotRemovePlug1 + ( PRF->IDperifHW - 1));
//						break;
//					default:
//						/* Situación no valida, pasamos a reposo e indicamos FAIL */
//						HPcryoCleanUpStop( HP, PRF);
//						HP->cleanUp.status = HP_CRYO_CLEAN_UP_FAIL;
//						HPcryoIdle( 0, HP, PRF);
//						break;
//				}
//				break;
//			case HP_CRYO_TEST_PELTIERS_OSC_TEMP:
				
//				if(HP->trt.TrtRequested)
//				{
//					HPcryoIdle( 1, HP, PRF);
//					break;
//				}
				
//				EnvTemp = EXP_UCgetEnvTemp();		/*Tomamos la temperatura ambiente*/
				
//				if(HP->frames.mainOut.data.fTempManipulo < (EnvTemp - HP_CRYO_LOW_THRSHOLD_WIN_TEMP_OSC_IDLE))	/*Si la temperatura baja de 8ºC por debajo de la temperatura ambiente*/
//				{
//					HPcryoIdle( 1, HP, PRF);
//				}
//				else
//				{
//					HP->frames.mainIn.data.fConsignaTemperatura = 100.0;	/*F1 - Power 100*/	/*Ponemos el aplicador en test peltiers trabajando al 100%*/
//					HP->frames.mainIn.data.fTemperaturaInicio = 100.0;		/*F2 - Power 100*/
//					HP->frames.mainIn.data.fConsignaVacum = 0.0;			/*Vacuum - 0*/
//					HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_TESTPELTIERS;
//				}
				
//				break;
//				//SAT
//			case HP_CRYO_SAT:
//				//PDTE - Por ahora no se necesita función update HPcryoSATupdate( HP, PRF);
//				HPcryoSATupdate( HP, PRF);
//				break;
//				//SAT
//			case HP_CRYO_FATIGUE_0:
//				/* Actualizamos el proceso de fatiga 0 */
//				switch(HP->fatigue_requested)
//				{
//					/*En caso de estar en PAUSA no se realiza ninguna acción*/
//					case HP_CRYO_FAT_STOP:	break;
//					/*En caso de estar en el primer paso de la fatiga, una vez completada, se indica y se manda el HP a idle*/
//					case HP_CRYO_FAT_1:	if(HPcryoFtg1Update( PRF->IDperifHW) == PRF->IDperifHW){	HPcryoFatigaComplete ( HP_CRYO_FAT_DONE_1, HP, PRF);	HPcryoIdle( 0, HP, PRF);	};	break;
//					/*En caso de estar en el segundo paso de la fatiga, una vez completada, se indica*/
//					case HP_CRYO_FAT_2: if(HPcryoFtg2Update( PRF->IDperifHW) == PRF->IDperifHW){	HPcryoFatigaComplete ( HP_CRYO_FAT_DONE_2, HP, PRF);	};	break;
//					case HP_CRTYO_FAT_LAST_TEST: break;
//					default: break;
//				}
				
//				break;
//			default:
//				/* En caso de no estar en ningún estado esperado pasamos a IDLE */
//				HPcryoIdle( 1, HP, PRF);
//				break;
//		}
		
//		/* Enviamos los datos ya actualizados por la logica de estados timeado */
//		//if( TICKS_DiffTicks( HP->time.refreshTime_ms) > HP->time.refreshPeriod_ms)
//		//{
//		//	HP->time.refreshTime_ms = TICKS_GetTicks();
//			ret = HPcryoWriteFrames( HP, PRF);
//			if( ret == ERROR){ return ret;}
//		//}
//	}
	
	/* Continuamos con el Update activo, si devolvemos cualquier cosa que no sea RUNNING
	 * cambiará el estado del Periferico */
	return RUNNING;
}

returnstatus_t HPcryoFinishCbk( tPRFdata *PRF)
{
	returnstatus_t ret = RUNNING;
//	tHPcryoData *HP = &( HPcryoData[PRF->indexInTypeArray]);
	
//	/* Segun el estado del proceso de finish */
//	switch( HP->finish.status)
//	{
//		case HP_CRYO_FINISH_CLEAR:
//		default:
//			/* Eliminamos todos los remapeos que hemos creado para este HP. En caso de error de
//			 * comunicaciones (ret = ERROR) no podemos dar por finalizado el periferico asi que
//			 * devolvemos RUNNING para que la logica del periferico nos mantenga en este estado */
//			ret = HPcryoClearRemapPack( PRF);
//			if( ret == ERROR){ HP->finish.status = HP_CRYO_FINISH_CLEAR; return RUNNING;}
						
//			/* Liberamos la estructura de datos usada por este HP */
//			HPcryoClearData( HP);
			
//			/* Dejamos el estado inicial */
//			HP->finish.status = HP_CRYO_FINISH_CLEAR;
			
//			/* Todo OK */
//			ret = SUCCESS;
//			break;
//	}
	
	/* Devolvemos el resultado */
	return ret;
}


/* FUNCIONES PUBLICAS PARA APP */
uint8 HPcryoGetFromSlot( cPRFslot slot, tHPcryoData **HPptr, tPRFdata **PRFptr)
{
//    /* Llamamos a la función para buscar un periferico en el slot indicado */
//    if( 1 )// PRFgetFromSlot( slot, PRFptr))
//    {
//        /* Hay un periferico en el slot indicado, vamos a ver si es un HPcryo */
//        if( ( *PRFptr)->type == PRF_TYPE_HP_CRYO)
//        {
//            /* Es un tipo HPcryo, lo hemos encontrado. Preparamos el puntero al HP */
//            ( *HPptr) = &( HPcryoData[( *PRFptr)->indexInTypeArray]);
			
//            /* Devolvemos TRUE conforme hemos encontrado */
//            return 1;
//        }
//    }
	
	/* Si llegamos aqui es que no lo hemos encontrado */
	return 0;
}

cHPcryoModels HPcryoGetModel( tHPcryoData *HP, tPRFdata *PRF)
{
    return HP_CRYO_MODEL_UNDEFINED;//( PRF->common->data.fields.model);
}

cPRFslot HPcryoGetSlot( tHPcryoData *HP, tPRFdata *PRF)
{
    return PRF_HW_SLOT1;//( PRF->IDperifHW);
}

uint8 HPcryoDoubleGetSlots( uint8 *mainSlot, uint8 *offSlot, tHPcryoData *HP, tPRFdata *PRF)
{
	tPRFdata *PRFaux;
	tHPcryoData *HPaux;
	uint8 otherSlot;
	
//	/* Comprobamos que el HP es un DOUBLE */
//	if( HPcryoGetModel( HP, PRF) != HP_CRYO_MODEL_DOUBLE){ return 0;}
	
//	/* Comrpobamos que los slots estan inicializados */
//	if( HP->frames.mainOut.data.id_manipulo_asociado == 0){ return 0;}
//	if( HP->frames.mainOut.data.id_manipulo_principal == 0){ return 0;}
	
//	/* Asignamos el ID HW del principal y el asociado según seamos el principal o el asociado.
//	 * El principal siempre es el "id_manipulo_principal" tanto en el asociado como en el principal */
//	( *mainSlot) = HP->frames.mainOut.data.id_manipulo_principal;
//	if( PRF->IDperifHW != HP->frames.mainOut.data.id_manipulo_principal)
//	{
//		/* Somos el slot asociado */
//		( *offSlot) = PRF->IDperifHW;
//		otherSlot = ( *mainSlot);
//	}
//	else
//	{
//		/* Somos el slot principal */
//		( *offSlot) = HP->frames.mainOut.data.id_manipulo_asociado;
//		otherSlot = ( *offSlot);
//	}
	
//	/* Finalmente comprobamos que tenemos periferico tipo DOUBLE en el otro slot */
//	if( !HPcryoGetFromSlot( otherSlot, &HPaux, &PRFaux)){ return 0;}
//	if( HPcryoGetModel( HPaux, PRFaux) != HP_CRYO_MODEL_DOUBLE){ return 0;}
			
	/* Todo OK */
	return 1;
}

cHPcryoStatus HPcryoGetStatus( tHPcryoData *HP, tPRFdata *PRF)
{
	return ( HP->status);
}

uint8 HPcryoIsAutoModeAvaible( tHPcryoData *HP, tPRFdata *PRF)
{
	return HP_CRYO_AUTO_MODE_AVAIBLE[HPcryoGetModel( HP, PRF)];
}

uint8 HPcryoSetLEDcolor( cHPcryoLEDcolors colorID, tHPcryoData *HP, tPRFdata *PRF)
{
	/* Gestion del color para asignar un color valido para los Tiny y Tiny Curved (ya que ciertos colores no se gestionan correctamente y el led se quedaria apagado)*/
	cHPcryoModels model;
	model = HPcryoGetModel( HP, PRF);
	if(model == HP_CRYO_MODEL_TINY || model == HP_CRYO_MODEL_TINY_CURVED){	colorID = HP_CRYO_CTLLED_COLOR_LILA;	}
	/* Gestion color Tiny y Tiny Curved*/
	
	/* Asignamos los valores */
	HP->frames.mainIn.data.color_led = colorID;
	
	return 1;
}

uint8 HPcryoSetAlarmCfg( float tempWindow, uint16 vacWaitTime_s, uint16 tempWaitTime_s, 
						uint16 vacFailTime_s, uint16 tempFailTime_s, float maxInTemp,
						float minSensorTemp, uint16 lowTempTime_s, tHPcryoData *HP)
{		
	/* Asignamos los valores */
	HP->frames.mainIn.data.fVentanaTemperaturaTratamiento = tempWindow;	
	HP->frames.mainIn.data.u16MaxTiempoEsperandoVac = vacWaitTime_s;		
	HP->frames.mainIn.data.u16MaxTiempoEsperandoTemp = tempWaitTime_s;		
	HP->frames.mainIn.data.u16MaxTiempoFalloVac = vacFailTime_s;
	HP->frames.mainIn.data.u16MaxTiempoFalloTemp = tempFailTime_s;			
	HP->frames.mainIn.data.fTemperaturaMaximaEntrada = maxInTemp;		
	HP->frames.mainIn.data.fTemperaturaMinimaSensores = minSensorTemp;		
	HP->frames.mainIn.data.u16TiempoTempBaja = lowTempTime_s;	
	
	return 1;
}

uint8 HPcryoSetTriggerONcfg( uint8 nPress, uint16 minTime_ms, tHPcryoData *HP)
{		
	/* Asignamos los valores */
	HP->frames.cfgIn.data.pulsaciones_encendido.num_pulsaciones = nPress;
	HP->frames.cfgIn.data.pulsaciones_encendido.min_tiempo = minTime_ms;
	
	return 1;
}

uint8 HPcryoSetTriggerOFFcfg( uint8 nPress, uint16 minTime_ms, tHPcryoData *HP)
{
	/* Asignamos los valores */
	HP->frames.cfgIn.data.pulsaciones_apagado.num_pulsaciones = nPress;
	HP->frames.cfgIn.data.pulsaciones_apagado.min_tiempo = minTime_ms;
	
	return 1;
}

uint8 HPcryoSetOverHeat( uint8 OnOff, float performanceFactor, tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
//	ret = EXP_UCconfigHPoverHeat( OnOff, performanceFactor, HPcryoGetSlot( HP, PRF));
	return ( ret == SUCCESS);
}

uint8 HPcryoIdle( uint8 holdVacum, tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
//	/* Ahora comprobamos si tenemos que ir a algún estado debido al estado del HP */
//	if( HP->frames.mainOut.data.estado == HP_CRYO_MAN_INIT){ HP->status = HP_CRYO_TEST_INIT;}
////	else if( HP->frames.mainOut.data.estado == HP_CRYO_MAN_ALARM ||
////			 HP->frames.mainOut.data.estado == HP_CRYO_MAN_DESCONFIGURADO ||
////			 HP->frames.mainOut.data.estado == HP_CRYO_MAN_MANIPULO_DESHAB_ERROR_COMS)
////	{ HP->status = HP_CRYO_ALARM;}
//	else
//	{
//		/* Si el manípulo tiene vacum, lo pasamos a estado de PAUSE y si no a IDLE*/
//		if( HP->frames.mainOut.data.presionVaccum > HP_CRYO_IDLE_MIN_VAC_ACCEPTED && holdVacum != 0 &&
//		    HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE &&
//			HP->frames.mainIn.data.cambio_estado != HP_CRYO_MAN_IDLE)
//		{
//			/* Pasamos el HP a PAUSE. */
//			HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_PAUSE;
//			HP->idle.vacStatus = HP_CRYO_IDLE_VAC_STATUS_WITH_VAC;
//		}
//		else
//		{
//			/* Pasamos el HP a IDLE. */
//			HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
//			HP->idle.vacStatus = HP_CRYO_IDLE_VAC_STATUS_WITHOUT_VAC;
//		}
		
//		/* V7787 - Reseteamos la temperatura de consigna para que no salte en caso de estar al aplicador frio (habiendose cancelado un tratamiento o viniendo de SAT) */
//		HP->trt.trt_temp_set = HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[HPcryoGetModel( HP, PRF)][HP_CRYO_STANDARD_TEMPERATURE_SET_POINT_TRT];
		
//		/* V7787 */
//		HP->trt.TrtParameters.DemoTRT = 0;		/* Reset del flag de TRT DEMO para volver a evaluar los errores restrictivos */
		
//		/* V7790 - TEMP SAFE */
//		HP->trt.TrtParameters.ProdTRT = 0;		/* Reset del flag de TRT PROD */
		
//		Temp_SAFE_Clear (HP, PRF);
//		/* V7790 - TEMP SAFE */
		
//		/* Pasamos la lógica a IDLE */
//		HP->status = HP_CRYO_IDLE;
//	}
	return 1;
}

cHPcryoIdleVacumStatus HPcryoIdleGetVacumStatus( tHPcryoData *HP, tPRFdata *PRF)
{
	return ( HP->idle.vacStatus);
}

uint8 HPcryoStop( uint8 holdVacum, tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Llamamos a la funcion stop tratamiento o test de vacum segun el estado del HP */
//	if( HP->status == HP_CRYO_TEST_VACUM){ return HPcryoTestVacumStop( holdVacum, HP, PRF);}
//	if( HP->status == HP_CRYO_TREATMENT){ return HPcryoTrtStop( holdVacum, HP, PRF);}
	return 0;
}

uint8 HPcryoTestVacumStartDflt( cHPcryoTestVacumMode mode, cHPcryoTrtVacLvls vacLvl, 
								uint8 useDfltAlarmCfg, tHPcryoData *HP, tPRFdata *PRF)
{
	cHPcryoModels model;
		
	/* Obtenemos el modelo */
	model = HPcryoGetModel( HP, PRF);
	
	/* Llamamos a la función de inicio de tratamiento con los parametros por defecto de las tablas */
    return 0;//HPcryoTestVacumStartFree( mode, HP_CRYO_TST_VAC_VAC_LVL_LIST[model][vacLvl], useDfltAlarmCfg, HP, PRF);
}

//uint8 HPcryoTestVacumStartFree( cHPcryoTestVacumMode mode, float vacum, uint8 useDfltAlarmCfg,
//							tHPcryoData *HP, tPRFdata *PRF)
//{
//	uint8 mainSlot, offSlot;
//	cHPcryoModels model;
	
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
//	/* Solo podemos empezar si la maquina de estados esta en IDLE */
//	if( HP->status != HP_CRYO_IDLE){ return 0;}
	
//	/* Si es un DOUBLE, solo empezamos si tiene ya detectado el principal y el asociado y este es
//	 * el principal */
//	model = HPcryoGetModel( HP, PRF);
//	if( model == HP_CRYO_MODEL_DOUBLE)
//	{
//		/* Obtenemos los slots del DOUBLE, si no esta inicializado salimos */
//		if( !HPcryoDoubleGetSlots( &mainSlot, &offSlot, HP, PRF)){ return 0;}
		
//		/* Miramos si somos el principal */
//		if( mainSlot != HPcryoGetSlot( HP, PRF)){ return 0;}
//	}
		
//	/* Solo empezamos si el manípulos esta en estado IDLE */
//	if( HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE){ return 0;}
	
//	/* Si el manipulo no tiene modo auto forzamos modo manual */
//	if( !HPcryoIsAutoModeAvaible( HP, PRF)){ mode = HP_CRYO_TEST_VAC_MODE_MANUAL;}
	
//	/* Si el modo es auto el nivel de succión es el 3 del HP si no es el indicado */
//	if( mode == HP_CRYO_TEST_VAC_MODE_AUTO){ vacum = HP_CRYO_TST_VAC_VAC_LVL_LIST[model][HP_CRYO_VAC_LVL_2];}

//	/* Estamos en IDLE, configuramos las variables de tratamiento para test de vacum */
//	HP->frames.mainIn.data.u16SegundosTratamiento = HP_CRYO_TEST_VACUM_TIME;
//	HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TEST_VACUM_TEMP;
//	HP->frames.mainIn.data.fTemperaturaInicio = HP_CRYO_TEST_VACUM_TRT_INI_TEMP;
//	HP->frames.mainIn.data.fConsignaVacum = vacum;
	
//	/* Configuramos la gestión de alarmas para test de vacum */
//	if( useDfltAlarmCfg)
//	{
//		HPcryoSetAlarmCfg( 	HP_CRYO_DFLT_TST_VAC_TEMP_WINDOW, HP_CRYO_DFLT_TST_VAC_VAC_WAIT_TIME,
//							HP_CRYO_DFLT_TST_VAC_TEMP_WAIT_TIME, HP_CRYO_DFLT_TST_VAC_VAC_FAIL_TIME,
//							HP_CRYO_DFLT_TST_VAC_TEMP_FAIL_TIME, HP_CRYO_DFLT_MAX_IN_TEMP[model],
//							HP_CRYO_DFLT_TST_VAC_MIN_SNS_TEMP, HP_CRYO_DFLT_TST_VAC_LOW_TEMP_TIME, HP);
//	}
	
//	/* Pasamos el HP a estado MAN_READY */
//	HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_READY;
 
//	/* Inicializamos variables */
//	HP->tstVac.mode = mode;
//	HP->tstVac.autoIsOK = 0;
//	/* Pasamos la logica de estados a TEST_VACUM y la logica del test a USER_START */
//	HP->status = HP_CRYO_TEST_VACUM;
//	HP->tstVac.status = HP_CRYO_TEST_VAC_RUN_WAITING_USER_START;
	
//	/* Lanzamos el timeOut para permitir que se produzca la transmision a la expansora,
//	 * luego al manipulo y recibir la respuesta */
//	HP->tstVac.timeOut = TICKS_GetTicks();
	
//	/* Todo OK */
//	return 1;
//}

//uint8 HPcryoTestVacumStop( uint8 holdVacum, tHPcryoData *HP, tPRFdata *PRF)
//{
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
//	/* Solo podemos hacer stop si hay un test en marcha */
//	if( HP->status != HP_CRYO_TEST_VACUM){ return 0;}
	
//	/* Pasamos el HP a Idle, esto para el proceso */
//	HPcryoIdle( holdVacum, HP, PRF);
	
//	/* Reseteamos las variables del proceso de test vacum */
//	HP->tstVac.timeOut = 0;
//	HP->tstVac.status = HP_CRYO_TEST_VAC_DONE;
//	HP->tstVac.mode = HP_CRYO_TEST_VAC_MODE_MANUAL;	//MERGE	// 7760 - OJO!
//	HP->tstVac.autoIsOK = 0;		//MERGE
	
//	//MERGE
//	/* Apagamos el chichometro */
//	HP->frames.mainIn.data.enable_plica = 0;
	
//	/* Todo OK */
//	return 1;
//}

cHPcryoTestVacumStatus HPcryoTestVacumStatus( tHPcryoData *HP, tPRFdata *PRF)
{
	return ( HP->tstVac.status);
}

uint8 HPcryoTestVacumIsInAutoAndOK( uint8 *isOK, tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
	/* Solo si hay un test en marcha */
	if( HP->status != HP_CRYO_TEST_VACUM){ return 0;}
		
	/* Si no estamos en auto devolvemos falso */
	if( HP->tstVac.mode != HP_CRYO_TEST_VAC_MODE_AUTO){ return 0;}
	
	/* Si llegamos aqui es que hay test de vacum en modo auto. Ahora comprobamos si esta
	 * la logico del test de vacum en WAITING_USER_END que es donde tiene sentido mirar
	 * el flag de isOK */
	if( HP->tstVac.status != HP_CRYO_TEST_VAC_RUN_WAITING_USER_END){ return 0;}
	
	/* Finalmente podemos devolver el valor del flag e indicar que es válido */
	*isOK = HP->tstVac.autoIsOK;
	return 1;
}

uint8 HPcryoTestVacIsAuto( tHPcryoData *HP, tPRFdata *PRF)
{
	return (HP->tstVac.mode == HP_CRYO_TEST_VAC_MODE_AUTO);
}

uint8 HPcryoTrtStartDflt( cHPcryoTrtModes mode, cHPcryoTrtTimes time, cHPcryoTrtVacLvls vacLvl, uint8 reqLabel, 
					      uint8 useDfltAlarmCfg, tHPcryoData *HP, tPRFdata *PRF)
{
	cHPcryoModels model;
	
	/* Obtenemos el modelo */
	model = HPcryoGetModel( HP, PRF);
	
	/* Llamamos a la función de inicio de tratamiento con los parametros por defecto de las tablas */
    return 0;/*HPcryoTrtStartFree( mode, HP_CRYO_TIME_LIST[time], HP_CRYO_TRT_VAC_LVL_LIST[model][vacLvl],
								HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_STANDARD_TEMPERATURE_SET_POINT_TRT],
                                HP_CRYO_DFLT_TRT_INI_TEMP, reqLabel, useDfltAlarmCfg, HP, PRF);*/
}

uint8 HPcryoTrtStartFree( cHPcryoTrtModes mode, uint16 time_s, float vacum, float temp, float trtIniTemp,
                          uint8 reqLabel, uint8 useDfltAlarmCfg, tHPcryoData *HP, tPRFdata *PRF)
{
//	uint8 mainSlot, offSlot;
//	cHPcryoModels model;
	
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
//	/* Solo podemos empezar si la maquina de estados esta en IDLE */
//	if( HP->status != HP_CRYO_IDLE){ return 0;}
	
//	/* Si es un DOUBLE, solo empezamos si tiene ya detectado el principal y el asociado y este es
//	 * el principal */
//	model = HPcryoGetModel( HP, PRF);
//	if( model == HP_CRYO_MODEL_DOUBLE)
//	{
//		/* Obtenemos los slots del DOUBLE, si no esta inicializado salimos */
//		if( !HPcryoDoubleGetSlots( &mainSlot, &offSlot, HP, PRF)){ return 0;}
		
//		/* Miramos si somos el principal */
//		if( mainSlot != HPcryoGetSlot( HP, PRF)){ return 0;}
//	}
	
//	/* Solo empezamos si el manípulos esta en estado IDLE */
//	if( HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE){ return 0;}
//	/* Si el manipulo no tiene modo auto forzamos modo manual */
//	if( !HPcryoIsAutoModeAvaible( HP, PRF)){ mode = HP_CRYO_TRT_MODE_MANUAL;}
	
//	/* Si el modo es auto el nivel de succión es el 3 del HP si no es el indicado */
//	if( mode == HP_CRYO_TRT_MODE_AUTO){ vacum = HP_CRYO_TRT_VAC_LVL_LIST[model][HP_CRYO_VAC_LVL_2];}
		
//	/* Inicializamos las variables del proceso de treatment */
//	HP->trt.timeOut = 0;
//	HP->trt.rqLbl = 0;
//	HP->trt.startTime = 0;
//	HP->trt.pauseTime = 0;
//	HP->trt.trtTime_s = time_s;
//	HP->trt.mode = mode;
//	HP->trt.beforePause = HP_CRYO_TREATMENT_DONE;
//	HP->trt.status = HP_CRYO_TREATMENT_DONE;
//	HP->trt.vacumRetryCnt = HP_CRYO_TRT_VACUM_RETRY_NUM;
//	HP->trt.vacumRetryTimeOut = HP_CRYO_TRT_VACUM_RETRY_TOUT;
//	HP->trt.vacumRetryRlsTime = 0;
//	HP->trt.vacumRetryRqstUserToMoveHP = 0;
//	HP->trt.adjustVacumCnt = HP_CRYO_TRT_ADJUST_VACUM_NUM;
//	HP->trt.adjustVacumTimeOut = HP_CRYO_TRT_ADJUST_VACUM_TOUT;
//	HP->trt.adjustVacumStatus = HP_CRYO_ADJUST_VACUM_IDLE;
//	HP->trt.adjustVacumValue = 0.0;
//	HP->trt.adjustVacumResetTime = 0;
//	HP->trt.Label_reuse = 0;
//	HP->trt.trt_secure_plus_three = 0;
//	HP->trt.set_temp_reached = 0;			//V7778
//	HPcryoTrtAutoModeRestart( HP, PRF);
	
//	/* Estamos en IDLE, configuramos las variables de tratamiento */
//	HP->frames.mainIn.data.u16SegundosTratamiento = time_s + HP_CRYP_TRT_TIME_OFFSET;
//	HP->frames.mainIn.data.fConsignaVacum = vacum;
//	/* V7778 - TEMP SEC */
//	if(EXP_UCtempSecureStatus())
//	{
//		HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_SET_POINT_END_TRT];
//		HP->trt.trt_temp_set = HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_SET_POINT_END_TRT];
//	}
//	else
//	{
//		HP->frames.mainIn.data.fConsignaTemperatura = temp;
//		HP->trt.trt_temp_set = temp;
//	}
//	/* V7778 - TEMP SEC */
//	HP->frames.mainIn.data.fTemperaturaInicio = trtIniTemp;
		
//	/* Configuramos la gestión de alarmas para tratamiento */
//	if( useDfltAlarmCfg)
//	{
//		if(EXP_UCerrSecureStatus())	/* V7780 */
//		{
//			HPcryoSetAlarmCfg( 	HP_CRYO_DFLT_LIST_TRT_SECURE_TEMP_WINDOW[model], HP_CRYO_DFLT_TRT_VAC_WAIT_TIME,
//								HP_CRYO_DFLT_TRT_TEMP_WAIT_LIST_TIME[model], HP_CRYO_DFLT_TRT_VAC_FAIL_TIME,
//								HP_CRYO_DFLT_TRT_SECURE_TEMP_FAIL_LIST_TIME[model], HP_CRYO_DFLT_MAX_IN_TEMP[model],
//								temp - HP_CRYO_DFLT_TRT_MIN_SNS_TEMP_REL, HP_CRYO_DFLT_TRT_LOW_TEMP_TIME, HP);
//		}
//		else
//		{
//			HPcryoSetAlarmCfg( 	HP_CRYO_DFLT_LIST_TRT_TEMP_WINDOW[model], HP_CRYO_DFLT_TRT_VAC_WAIT_TIME,
//								HP_CRYO_DFLT_TRT_TEMP_WAIT_LIST_TIME[model], HP_CRYO_DFLT_TRT_VAC_FAIL_TIME,
//								HP_CRYO_DFLT_TRT_TEMP_FAIL_LIST_TIME[model], HP_CRYO_DFLT_MAX_IN_TEMP[model],
//								temp - HP_CRYO_DFLT_TRT_MIN_SNS_TEMP_REL, HP_CRYO_DFLT_TRT_LOW_TEMP_TIME, HP);
//		}
//	}
	
//	/* Asignamos si es necesaria la lbl, en función de si lo es o no cambamos la situacion inicial */
//	HP->trt.rqLbl = reqLabel;
//	if( reqLabel)
//	{
//		/* Se requiere etiqueta RF-ID, mantenemos estado MAN_IDLE e indicamos estado inicial de
//		 * obtención de RF-ID para el update */
//		HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
//		HP->trt.status = HP_CRYO_TREATMENT_RUN_WAITING_RFID;
//	}
//	else
//	{
//		/* No se requiere de RF-ID, pasamos a MAN_READY e indicamos USER_START */
//		HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_READY;
//		HP->trt.status = HP_CRYO_TREATMENT_RUN_WAITING_USER_START;
//	}
	
//	/* Lanzamos el timeOut para permitir que se produzca la transmision a la expansora,
//	 * luego al manipulo y recibir la respuesta */
//	HP->trt.timeOut = TICKS_GetTicks();
			
//	/* Pasamos la logica de estados a TREATMENT */
//	HP->status = HP_CRYO_TREATMENT;
							   
    /* Todo OK */
    return 1;
}

uint8 HPcryoTrtStop( uint8 holdVacum, tHPcryoData *HP, tPRFdata *PRF)
{
    /* Comprobamos que el periferico este en estado RUNNING */
    if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
    /* Solo podemos hacer stop si hay un test en marcha */
    if( HP->status != HP_CRYO_TREATMENT){ return 0;}
		
    /* Pasamos el HP a Idle, esto para el proceso */
    HPcryoIdle( holdVacum, HP, PRF);
		
    /* Reseteamos las variables del proceso de treatment */
    HP->trt.timeOut = 0;
    HP->trt.rqLbl = 0;
    HP->trt.startTime = 0;
    HP->trt.pauseTime = 0;
    HP->trt.trtTime_s = 0;
    //HP->trt.mode = HP_CRYO_TRT_MODE_AUTO;  //HP_CRYO_TRT_MODE_MANUAL; //V7760
    HP->trt.beforePause = HP_CRYO_TREATMENT_DONE;
    HP->trt.status = HP_CRYO_TREATMENT_DONE;
    HP->trt.vacumRetryCnt = 0;
    HP->trt.vacumRetryTimeOut = 0;
    HP->trt.vacumRetryRlsTime = 0;
    HP->trt.vacumRetryRqstUserToMoveHP = 0;
    HP->trt.adjustVacumCnt = 0;
    HP->trt.adjustVacumStatus = HP_CRYO_ADJUST_VACUM_IDLE;
    HP->trt.adjustVacumValue = 0.0;
    HP->trt.adjustVacumTimeOut = 0;
    HP->trt.adjustVacumResetTime = 0;
    HP->trt.autoMode.status = HP_CRYO_TRT_AUTO_IDLE;
    HP->trt.autoMode.tmr = 0;
    HP->trt.autoMode.waitTime = 0;
    HP->trt.autoMode.detectionTime = 0;
    HP->trt.autoMode.detectionFilterAcum = 0;
    HP->trt.autoMode.detectionFilterInc = 0;
    HP->trt.autoMode.detectionFilterDec = 0;
    HP->trt.autoMode.detectionFilterIsOKlvl = 0;
    HP->trt.autoMode.isOK = 0;
    HP->trt.Label_reuse = 0;
    HP->trt.trt_secure_plus_three = 0;
    HP->trt.set_temp_reached = 0;		//V7778
			
    /* Todo OK */
	
    /* Apagamos el chichometro */
    HP->frames.mainIn.data.enable_plica = 0;
	
    return 1;
}

uint8 HPcryoTrtPause( tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
//	/* Solo podemos pausar si se esta haciendo un tratamiento y no estamos
//	 * en RFID. En RFID no podemos ir a PAUSE porque podriamos perder una toallita */
//	if( HP->status != HP_CRYO_TREATMENT){ return 0;}
//	if( HP->trt.status == HP_CRYO_TREATMENT_RUN_WAITING_RFID){ return 0;}
//	if( HP->trt.status == HP_CRYO_TREATMENT_RUN_PAUSE){ return 0;}
	
//	/* Memorizamos en que estado estamos actualmente dentro
//	 * de la secuencia de tratamiento */
//	HP->trt.beforePause = HP->trt.status;
	
//	/* Si estamos contando tiempo de tratamiento cogemos el tiempo actual */
//	HP->trt.pauseTime = 0;
//	if( HP->trt.startTime != 0){ HP->trt.pauseTime = TICKS_GetTicks();}
	
//	/*V7778 - SEC TEMP*/
//	//if(EXP_UCtempSlopeStatus()){	HPcryo_Resume_Cooling(HP, PRF);	}		//aqui
//	/*V7778 - SEC TEMP*/
	
//	/* Enviamos la logica de tratamiento a PAUSE */
//	HP->trt.status = HP_CRYO_TREATMENT_RUN_PAUSE;
	
	/* Todo OK */
	return 1;
}

uint8 HPcryoTrtResume( tHPcryoData *HP, tPRFdata *PRF)
{
	uint32 elapsedTime;

//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
//	/* Solo podemos hacer RESUME si estamos en tratamiento y PAUSE */
//	if( HP->status != HP_CRYO_TREATMENT){ return 0;}
//	if( HP->trt.status != HP_CRYO_TREATMENT_RUN_PAUSE){ return 0;}
	
//	/* Solo retomamos si el manípulos esta en estado IDLE o PAUSE. Son los estados a los
//	 * que tiene que ir cuando se pasa a PAUSA la logica del trt */
////	if( HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE &&
////		HP->frames.mainOut.data.estado != HP_CRYO_MAN_PAUSE	)
////	{ return 0;}
	
//	/* Dependiendo del estado en el que estuviera el HP antes de PAUSE actuamos */
//	switch( HP->trt.beforePause)
//	{
//		case HP_CRYO_TREATMENT_RUN_WAITING_USER_START:
//			/* Pasamos a ready el handpiece */
//			HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_READY;
//			break;
//		case HP_CRYO_TREATMENT_RUN_VACUM:
//		case HP_CRYO_TREATMENT_RUN_COOLING:
//			/* Reiniciamos el tratamiento con el tiempo restante, solo si al hacer pausa
//			 * se ha podido enviar el HP a MAN_PAUSE. Es posible que se haya pulsado el boton
//			 * durante la pausa y el HP ya este en IDLE con lo que pararíamos el tratamiento */
//			if( HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE &&
//				HP->frames.mainOut.data.estado != HP_CRYO_MAN_FINISHING)
//			{
//				/* Calculamos el tiempo que hemos estado en pausa para restarlo del tiempo de
//				tratamiento */
//				elapsedTime = ( HP->trt.pauseTime - HP->trt.startTime) / 1000;
//				HP->frames.mainIn.data.u16SegundosTratamiento = ( HP->trt.trtTime_s + HP_CRYP_TRT_TIME_OFFSET) - elapsedTime;
				
//				/* Reasignamos el startTime para que no cuente el tiempo en pausa de modo
//				que al pedir el tiempo de tratamiento no contemos la ventana de pausa */
//				HP->trt.startTime = HP->trt.startTime + ( TICKS_GetTicks() - HP->trt.pauseTime);
				
//				/*V7778 - SEC TEMP*/
//				//if(EXP_UCtempSlopeStatus){	HPcryo_Resume_Cooling(HP, PRF);	}
//				/*V7778 - SEC TEMP*/
				
//				/* Relanzamos el tratamiento */
//				HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_WAITINGSETPOINTS;
//			}
//		case HP_CRYO_TREATMENT_RUN_WAITING_USER_END:
//			/* El HP ya estaba en pause esperando al usuario para finalizar. */
//			//HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_PAUSE;
//			break;
//		default:
//			/* Estado no coherente. Dejamos que la logica de estados se encargue */
//			break;
//	}
	
//	/* Recuperamos el estado previo al PAUSE */
//	HP->trt.status = HP->trt.beforePause;
	
//	/* Lanzamos el timeOut para permitir que se produzca la transmision a la expansora,
//	 * luego al manipulo y recibir la respuesta */
//	HP->trt.timeOut = TICKS_GetTicks();
	
	return 1;
}

uint32 HPcryoTrtGetTimeSeconds( tHPcryoData *HP, tPRFdata *PRF)
{
	uint32 seconds;

//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
//	/* Solo si hay tratamiento en marcha y estamos contando tiempo */
//	if( HP->status != HP_CRYO_TREATMENT){ return 0;}
//	if( HP->trt.startTime == 0){ return 0;}
	
//	if( HP->trt.status == HP_CRYO_TREATMENT_RUN_WAITING_USER_END){ return HP->trt.trtTime_s;}
	
//	if(((HP->trt.status == HP_CRYO_TREATMENT_RUN_WAITING_USER_START)||		//V7775
//		(HP->trt.status == HP_CRYO_TREATMENT_RUN_VACUM)) &&
//		(HP->trt.vacumRetryCnt == HP_CRYO_TRT_VACUM_RETRY_NUM))
//		{return 0;}
	
//	/* Estamos en tratamiento y se está contando tiempo, dependiendo de si
//	 * estamos en PAUSE o no calculamos los segundos */
//	if( HP->trt.status == HP_CRYO_TREATMENT_RUN_PAUSE)
//	{ seconds = ( ( HP->trt.pauseTime - HP->trt.startTime) / 1000);}
//	else
//	{
//		if( HP->trt.vacumRetryRlsTime != 0){ seconds = ( HP->trt.vacumRetryRlsTime - HP->trt.startTime) / 1000;}
//		else{ seconds = ( TICKS_DiffTicks( HP->trt.startTime) / 1000);}
//	}
	
	/* Devolvemos el tiempo transcurrido */
	return seconds;
}

uint32 HPcryoTrtGetTreatmentTotalTimeSeconds( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Devolvemos el tiempo total de tratamiento */
	return HP->trt.trtTime_s;
}

cHPcryoTreatmentStatus HPcryoTrtStatus( tHPcryoData *HP, tPRFdata *PRF)
{
	return ( HP->trt.status);
}

uint8 HPcryoTrtAdjustVacumDflt( cHPcryoTrtVacLvls vacLvl, tHPcryoData *HP, tPRFdata *PRF)
{
	cHPcryoModels model;
		
	/* Obtenemos el modelo */
	model = HPcryoGetModel( HP, PRF);
		
	/* Llamamos a la función de inicio de ajuste de vacum con los parametros por defecto de las tablas */
    return 0;//HPcryoTrtAdjustVacumFree( HP_CRYO_TRT_VAC_LVL_LIST[model][vacLvl], HP, PRF);
}

//uint8 HPcryoTrtAdjustVacumFree( float vacum, tHPcryoData *HP, tPRFdata *PRF)
//{
//	/* Comprobamos si ya hemos hecho el número máximo de ajustes de vacum */
//	if( HPcryoTrtAdjustVacumAvailable( HP, PRF))
//	{
//		/* Podemos ajustar el vacum, arrancamos la máquina de estados y restamos al contador */
//		HP->trt.adjustVacumCnt--;
//		HP->trt.adjustVacumValue = vacum;
//		HP->trt.adjustVacumStatus = HP_CRYO_ADJUST_VACUM_SET;
//		HP->trt.adjustVacumResetTime = 0;
//		HP->trt.adjustVacumTimeOut = HP_CRYO_TRT_ADJUST_VACUM_TOUT;
//		/* Reseteamos el proceso de modo AUTO */
//		HPcryoTrtAutoModeRestart( HP, PRF);
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}
uint8 HPcryoTrtAdjustVacumAvailable( tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
//	/* Solo si hay tratamiento en marcha */
//	if( HP->status != HP_CRYO_TREATMENT){ return 0;}
	
//	/* Solo si durante el tratamiento se ha llegado al frio*/
//	if( HP->trt.status != HP_CRYO_TREATMENT_RUN_COOLING && HP->trt.status != HP_CRYO_TREATMENT_RUN_VACUM){ return 0; }
	
//	/* Solo se permitirá reajustar si el modo de tratamiento es MANUAL */
//	if( HP->trt.mode == HP_CRYO_TRT_MODE_AUTO){ return 0; }
	
//	/* Comprobamos si llevamos demasiado tiempo de tratamiento para cambiar el vacum */
//	if( HP->trt.startTime != 0)
//	{
//		if( TICKS_DiffTicks( HP->trt.startTime) >= HP->trt.adjustVacumTimeOut){ return 0;}
//	}
	
//	/* Comprobamos si ya hemos hecho el número máximo de ajustes de vacum */
//	if( HP->trt.adjustVacumCnt == 0){ return 0;}
	
	/* Si llegamos aqui es que se puede realizar el ajuste de vacum */
	return 1;
}

uint8 HPcryoTrtVacumRetryAvailable( tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
//	/* La maquina de estados esta en TREATMENT */
//	if( HP->status != HP_CRYO_TREATMENT){ return 0;}

//	/* Podemos reintentar vacum si el tiempo es menor que el timeout establecido */
//	if( HP->trt.startTime != 0)
//	{
//		if( TICKS_DiffTicks( HP->trt.startTime) >= HP->trt.vacumRetryTimeOut){ return 0;}
//	}
	
	/* Vacum retry disponible */
	return 1;
}

uint8 HPcryoTrtVacumRetryIsUserRqstToMoveHP( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Devolvemos si hay petición */
	return HP->trt.vacumRetryRqstUserToMoveHP;	
}

uint8 HPcryoTrtResuctionsNum( tHPcryoData *HP, tPRFdata *PRF)
{
    return 0;//EXP_UCgetVacumRetrys( HPcryoGetSlot( HP, PRF));
}

uint8 HPcryoTrtIsInAutoAndOK( uint8 *isOK, tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
	/* Solo si hay tratamiento en marcha */
	if( HP->status != HP_CRYO_TREATMENT){ return 0;}
		
	/* Si no estamos en auto devolvemos falso */
	if( HP->trt.mode != HP_CRYO_TRT_MODE_AUTO){ return 0;}
	
	/* Si llegamos aqui es que hay tratamiento en modo auto. Ahora comprobamos si esta
	 * la logico del modo auto en tratamiento en RESULT que es donde tiene sentido mirar
	 * el flag de isOK */
	if( HP->trt.autoMode.status != HP_CRYO_TRT_AUTO_RESULT){ return 0;}
	
	/* Finalmente podemos devolver el valor del flag e indicar que es válido */
	*isOK = HP->trt.autoMode.isOK;
	return 1;
} 

uint8 HPcryoTrtIsAuto( tHPcryoData *HP, tPRFdata *PRF)
{
	return (HP->trt.mode == HP_CRYO_TRT_MODE_AUTO);
}

uint8 HPcryoCleanUpStartDflt( uint8 forceClean, tHPcryoData *HP, tPRFdata *PRF)
{
return 0;   //	/* Llamamos a la Free con parametros predefinidos */
//	return HPcryoCleanUpStartFree( forceClean, HP_CRYO_CLEAN_UP_DFLT_COUNTDOWN, HP_CRYO_CLEAN_UP_DFLT_TIME_IS_CLEAN,
//								   HP_CRYO_CLEAN_UP_DFLT_TIME_CANNOT_CLEAN, HP_CRYO_CLEAN_UP_DFLT_CLEAN_VACUM,
//								   HP, PRF);
}

uint8 HPcryoCleanUpStartFree( uint8 forceClean, uint32 countDown_ms, uint32 timeIsClean, uint32 timeCannotClean, 
		 	 	 	 	 	  float cleanVacum, tHPcryoData *HP, tPRFdata *PRF)
{					 
	uint8 mainSlot, offSlot;
	cHPcryoModels model;
	
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
	/* Solo podemos empezar si la maquina de estados esta en IDLE */
	if(HP->status != HP_CRYO_IDLE){ return 0;}
	
	/* Si es un DOUBLE, solo empezamos si tiene ya detectado el principal y el asociado y este es 
	 * el principal */
	model = HPcryoGetModel( HP, PRF);
	if( model == HP_CRYO_MODEL_DOUBLE)
	{
		/* Obtenemos los slots del DOUBLE, si no esta inicializado salimos */
		if( !HPcryoDoubleGetSlots( &mainSlot, &offSlot, HP, PRF)){ return 0;}
		
		/* Miramos si somos el principal */
		if( mainSlot != HPcryoGetSlot( HP, PRF)){ return 0;}
	}
	
	/* Solo empezamos si el manípulos esta en estado IDLE */
	if( HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE){ return 0;}
			
	/* Inicializamos variables */
	if( forceClean == 0){ HP->cleanUp.status = HP_CRYO_CLEAN_UP_COUNTDOWN;}
	else{ HP->cleanUp.status = HP_CRYO_CLEAN_UP_WAIT_VACUM;}
	HP->cleanUp.time_ms = 0;
	HP->cleanUp.countDown_ms = countDown_ms;
	HP->cleanUp.checkPatientTime_ms = 0;
	HP->cleanUp.forceClean = forceClean;
	HP->cleanUp.cycle.tmrIsClean_ms = 0;
	HP->cleanUp.cycle.tmrCannotClean_ms = 0;				   
	HP->cleanUp.cycle.timeIsClean = timeIsClean;
	HP->cleanUp.cycle.timeCannotClean = timeCannotClean;
	HP->cleanUp.cycle.cleanVacum = cleanVacum;
	HP->cleanUp.cycle.NoUmbralVacResetFilter = 0;
										 
	/* Pasamos la logica de estado a cleaning */
	HP->status = HP_CRYO_CLEAN_UP;
	
	/* Todo OK */
	return 1;
}

uint8 HPcryoCleanUpReset( uint8 forceClean, uint32 countDown_ms, uint32 timeIsClean, uint32 timeCannotClean, 
	 	 	  float cleanVacum, tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 mainSlot, offSlot;
	cHPcryoModels model;
	
	/* Si es un DOUBLE, solo empezamos si tiene ya detectado el principal y el asociado y este es 
	 * el principal */
	model = HPcryoGetModel( HP, PRF);
	if( model == HP_CRYO_MODEL_DOUBLE)
	{
		/* Obtenemos los slots del DOUBLE, si no esta inicializado salimos */
		if( !HPcryoDoubleGetSlots( &mainSlot, &offSlot, HP, PRF)){ return 0;}
		
		/* Miramos si somos el principal */
		if( mainSlot != HPcryoGetSlot( HP, PRF)){ return 0;}
	}
			
	/* Inicializamos variables */
	if( forceClean == 0){ HP->cleanUp.status = HP_CRYO_CLEAN_UP_COUNTDOWN;}
	else{ HP->cleanUp.status = HP_CRYO_CLEAN_UP_WAIT_VACUM;}
	HP->cleanUp.time_ms = 0;
	HP->cleanUp.countDown_ms = countDown_ms;
	HP->cleanUp.checkPatientTime_ms = 0;
	HP->cleanUp.forceClean = forceClean;
	HP->cleanUp.cycle.tmrIsClean_ms = 0;
	HP->cleanUp.cycle.tmrCannotClean_ms = 0;				   
	HP->cleanUp.cycle.timeIsClean = timeIsClean;
	HP->cleanUp.cycle.timeCannotClean = timeCannotClean;
	HP->cleanUp.cycle.cleanVacum = cleanVacum;
	HP->cleanUp.cycle.NoUmbralVacResetFilter = 0;
										 
	/* Pasamos la logica de estado a cleaning */
	HP->status = HP_CRYO_CLEAN_UP;
	
	/* Todo OK */
	return 1;
}

uint8 HPcryoCleanUpStop( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
	/* Solo podemos hacer stop si clean up esta en marcha */
	if( HP->status != HP_CRYO_CLEAN_UP){ return 0;}
		
	/* Pasamos el HP a Idle, esto para el proceso */
	HPcryoIdle( 0, HP, PRF);
		
	/* Reseteamos las variables del proceso de clean up */
	HP->cleanUp.status = HP_CRYO_CLEAN_UP_DONE;
	HP->cleanUp.time_ms = 0;
	HP->cleanUp.countDown_ms = 0;
	HP->cleanUp.checkPatientTime_ms = 0;
	HP->cleanUp.forceClean = 0;
	HP->cleanUp.cycle.tmrIsClean_ms = 0;
	HP->cleanUp.cycle.tmrCannotClean_ms = 0;
	HP->cleanUp.cycle.timeIsClean = 0;
	HP->cleanUp.cycle.timeCannotClean = 0;
	HP->cleanUp.cycle.cleanVacum = 0.0;
	HP->cleanUp.cycle.NoUmbralVacResetFilter = 0;
			
	/* Todo OK */
	return 1;
}

cHPcryoCleanUpStatus HPcryoCleanUpStatus( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Devolvemos el estado de clean up */
	return ( HP->cleanUp.status);
}

cHPcryoCleanUpMoments HPcryoCleanUpInitOrEnd( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Devolver el momento en el que se está solicitando hacer la limpieza*/
	return ( HP->cleanUpInitOrEnd);
}

uint32 HPcryoCleanUpGetCountDownSeconds( tHPcryoData *HP, tPRFdata *PRF)
{
	uint32 seconds;
	
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
//	/* La logica tiene que estar en clean up */
//	if( HP->status != HP_CRYO_CLEAN_UP){ return 0;}
		
//	/* El proceso tiene que estar en COUNTDOWN */
//	if( HP->cleanUp.status != HP_CRYO_CLEAN_UP_COUNTDOWN){ return 0;}
	
//	/* Si llegamos aqui es que estamos en countdown */
//	if( HP->cleanUp.countDown_ms > TICKS_DiffTicks( HP->cleanUp.time_ms))
//	{ seconds = (( HP->cleanUp.countDown_ms - TICKS_DiffTicks( HP->cleanUp.time_ms)) / 1000);}
//	else
//	{seconds = 0;}
	return seconds;	
}

uint8 HPcryoCleanUpAllowClean( uint8 go, tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
	/* La logica tiene que estar en clean up */
	if( HP->status != HP_CRYO_CLEAN_UP){ return 0;}
		
	/* El proceso tiene que estar en WAITING USER */
	if( HP->cleanUp.status != HP_CRYO_CLEAN_UP_WAITING_USER){ return 0;}
	
	/* Cambiamos el estado según indique el usuario */
	if( go != 0)
	{ 
		/* Vamos al estado de espera del recurso vacum indicando que no es necesario
		 * comprobar si hay paciente */
		HP->cleanUp.status = HP_CRYO_CLEAN_UP_WAIT_VACUM;
		HP->cleanUp.forceClean = 1;
	}
	else
	{
		/* Vamos a countDown, reseteamos el contador de tiempo */
		HP->cleanUp.time_ms = 0;
		HP->cleanUp.status = HP_CRYO_CLEAN_UP_COUNTDOWN;
	}
	
	/* Todo OK */
	return 1;
}

uint8 HPcryoCleanUpFinishCountDown( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
	/* La logica tiene que estar en clean up */
	if( HP->status != HP_CRYO_CLEAN_UP){ return 0;}
		
	/* El proceso tiene que estar en WAITING USER */
	if( HP->cleanUp.status != HP_CRYO_CLEAN_UP_COUNTDOWN){ return 0;}
	
	/* Vamos al estado de espera del recurso vacum indicando que no es necesario
	 * comprobar si hay paciente */
	HP->cleanUp.status = HP_CRYO_CLEAN_UP_WAIT_VACUM;
	
	/* Todo OK */
	return 1;
}

//SAT
/* ESTADO DE SAT */
uint8 HPcryoSATcoolingTestStart( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 mainSlot, offSlot;
	cHPcryoModels model;
	
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
	/* Solo podemos empezar si la maquina de estados esta en IDLE o en SAT. Ya que dentro del 
	 * estado de SAT podemos iniciar varios tests */
	if( HP->status != HP_CRYO_IDLE && HP->status != HP_CRYO_SAT){ return 0;}
	
	/* Si es un DOUBLE, solo empezamos si tiene ya detectado el principal y el asociado y este es 
	 * el principal */
	model = HPcryoGetModel( HP, PRF);
	if( model == HP_CRYO_MODEL_DOUBLE)
	{
		/* Obtenemos los slots del DOUBLE, si no esta inicializado salimos */
		if( !HPcryoDoubleGetSlots( &mainSlot, &offSlot, HP, PRF)){ return 0;}
		
		/* Miramos si somos el principal */
		if( mainSlot != HPcryoGetSlot( HP, PRF)){ return 0;}
	}	
	
	if(HP->frames.mainOut.data.estado == HP_CRYO_MAN_INPROGRESS){	HPcryoTrtSetPointOsc( HP_CRYO_TIME_LOOP_OSC_SET_POINT_TEMP, HP, PRF);	}
	
	/* Solo empezamos si el manípulos esta en estado IDLE */
	if( HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE){ return 0;}
	
	/* Si estamos realizando el test del vacum no podemos iniciar el de frío, son excluyentes.
	 * Tampoco podemos inicar el test de cooling si ya esta en marcha */ 
	if( HP->SAT.testRun.bits.vacum != 0){ return 0;}
	if( HP->SAT.testRun.bits.cooling != 0){ return 0;}
	
	/* Se puede iniciar el test de frío, para ello lanzamos un tratamiento */
	HP->frames.mainIn.data.u16SegundosTratamiento = 60000;
	HP->frames.mainIn.data.fConsignaVacum = 0.0;
	HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_STANDARD_TEMPERATURE_SET_POINT_TRT];
	HP->frames.mainIn.data.fTemperaturaInicio = HP_CRYO_DFLT_TRT_INI_TEMP;
	HPcryoSetAlarmCfg( 	HP_CRYO_DFLT_LIST_TRT_TEMP_WINDOW[model], HP_CRYO_DFLT_TRT_VAC_WAIT_TIME,
						HP_CRYO_DFLT_TRT_TEMP_WAIT_LIST_TIME[model], HP_CRYO_DFLT_TRT_VAC_FAIL_TIME,
						HP_CRYO_DFLT_TRT_TEMP_FAIL_LIST_TIME[model], HP_CRYO_DFLT_MAX_IN_TEMP[model],
						HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_STANDARD_TEMPERATURE_SET_POINT_TRT] - HP_CRYO_DFLT_TRT_MIN_SNS_TEMP_REL, 
						HP_CRYO_DFLT_TRT_LOW_TEMP_TIME, HP);
	
	/* Enviamos directamente al estado WAITING SET POINTS */
	HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_WAITINGSETPOINTS;
		
	/* Indicamos que se esta realizando el test de frío y que estamos en SAT */
	HP->SAT.testRun.bits.cooling = 1;
	HP->status = HP_CRYO_SAT;
	HP->PrevStatusSAT = 1;
	
	/* Todo OK */
	return 1;
}

uint8 HPcryoSATcoolingTestStop( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
	/* Solo podemos hacer stop si estamos en SAT */
	if( HP->status != HP_CRYO_SAT){ return 0;}
	
	/* Solo se para el test si éste se esta ejecutando */
	if( HP->SAT.testRun.bits.cooling == 0){ return 0;}
		
	/* Pasamos el HP a Idle, esto para el proceso */
	HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
	
	/* Reseteamos variables */
	HP->SAT.testRun.bits.cooling = 0;

	/* Todo OK */
	return 1;
}

uint8 HPcryoSATvacumTestStart( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 mainSlot, offSlot;
	cHPcryoModels model;
	
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
	/* Solo podemos empezar si la maquina de estados esta en IDLE o en SAT. Ya que dentro del 
	 * estado de SAT podemos iniciar varios tests */
	if( HP->status != HP_CRYO_IDLE && HP->status != HP_CRYO_SAT){ return 0;}
	
	/* Si es un DOUBLE, solo empezamos si tiene ya detectado el principal y el asociado y este es 
	 * el principal */
	model = HPcryoGetModel( HP, PRF);
	if( model == HP_CRYO_MODEL_DOUBLE)
	{
		/* Obtenemos los slots del DOUBLE, si no esta inicializado salimos */
		if( !HPcryoDoubleGetSlots( &mainSlot, &offSlot, HP, PRF)){ return 0;}
		
		/* Miramos si somos el principal */
		if( mainSlot != HPcryoGetSlot( HP, PRF)){ return 0;}
	}	
	
	/* Solo empezamos si el manípulos esta en estado IDLE */
	if( HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE){ return 0;}
	
	/* Si estamos realizando el test del frío no podemos iniciar el de vacum, son excluyentes.
	 * Tampoco podemos inicar el test de vacum si ya esta en marcha */ 
	if( HP->SAT.testRun.bits.vacum != 0){ return 0;}
	if( HP->SAT.testRun.bits.cooling != 0){ return 0;} //esto no hace falta e impide que se reseteen las variables.
	
	/* Se puede iniciar el test de vacum, para ello usamos el estado ENABLE_VAC y configuramos la consigna */
	HP->frames.mainIn.data.fConsignaVacum = HP_CRYO_TRT_VAC_LVL_LIST[model][HP_CRYO_VAC_LVL_2];
	HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_ENABLEVAC;
	
	/* Indicamos que se esta realizando el test de frío y que estamos en SAT */
	HP->SAT.testRun.bits.vacum = 1;
	HP->status = HP_CRYO_SAT;
	HP->PrevStatusSAT = 1;
		
	/* Todo OK */
	return 1;
}

uint8 HPcryoSATvacumTestStop( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
	/* Solo podemos hacer stop si estamos en SAT */
	if( HP->status != HP_CRYO_SAT){ return 0;}
	
	/* Solo se para el test si éste se esta ejecutando */
	if( HP->SAT.testRun.bits.vacum == 0){ return 0;} //esto no hace falta e impide que se reseteen las variables
		
	/* Pasamos el HP a Idle, esto para el proceso */
	HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
	
	/* Reseteamos variables */
	HP->SAT.testRun.bits.vacum = 0;
	
	/* Todo OK */
	return 1;
}

uint8 HPcryoSATbodyFillSensorTestStart( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 mainSlot, offSlot;
	cHPcryoModels model;
		
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
	/* Solo podemos empezar si la maquina de estados esta en IDLE o en SAT. Ya que dentro del 
	 * estado de SAT podemos iniciar varios tests */
	if( HP->status != HP_CRYO_IDLE && HP->status != HP_CRYO_SAT){ return 0;}
		
	/* Si es un DOUBLE, solo empezamos si tiene ya detectado el principal y el asociado y este es 
	 * el principal */
	model = HPcryoGetModel( HP, PRF);
	if( model == HP_CRYO_MODEL_DOUBLE)
	{
		/* Obtenemos los slots del DOUBLE, si no esta inicializado salimos */
		if( !HPcryoDoubleGetSlots( &mainSlot, &offSlot, HP, PRF)){ return 0;}
		
		/* Miramos si somos el principal */
		if( mainSlot != HPcryoGetSlot( HP, PRF)){ return 0;}
	}	
	
	/* Simplemente encendemos el chichometro */
	HP->frames.mainIn.data.enable_plica = 1;
	
	/* Indicamos manipulo en SAT y test de chichometro */
	HP->SAT.testRun.bits.bodyFillSensor = 1;
	
	/* Todo OK */
	return 1;
}

uint8 HPcryoSATbodyFillSensorTestStop( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
	/* Solo se para el test si éste se esta ejecutando */
	if( HP->SAT.testRun.bits.bodyFillSensor == 0){ return 0;}
		
	/* Simplemente apagamos el chichometro */
	HP->frames.mainIn.data.enable_plica = 0;
	
	/* Reseteamos variables */
	HP->SAT.testRun.bits.bodyFillSensor = 0;
	
	/* Todo OK */
	return 1;
}

uint8 HPcryoSATbodyFillSensorIsDetecting( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
	/* Solo se para el test si éste se esta ejecutando */
	if( HP->SAT.testRun.bits.bodyFillSensor == 0){ return 0;}
		
	/* Se esta ejecutando test de chichometro, devolvemos la lectura */
	return ( HP->frames.mainOut.data.estado_entradas.bit_field.detec_plica_dcha != 0 ||
			 HP->frames.mainOut.data.estado_entradas.bit_field.detec_plica_iza != 0);	
}

uint8 HPcryoSAT_RGBtestStart( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 mainSlot, offSlot;
	cHPcryoModels model;
		
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
	
	/* Solo podemos empezar si la maquina de estados esta en IDLE o en SAT. Ya que dentro del 
	 * estado de SAT podemos iniciar varios tests */
	if( HP->status != HP_CRYO_IDLE && HP->status != HP_CRYO_SAT){ return 0;}
		
	/* Si es un DOUBLE, solo empezamos si tiene ya detectado el principal y el asociado y este es 
	 * el principal */
	model = HPcryoGetModel( HP, PRF);
	if( model == HP_CRYO_MODEL_DOUBLE)
	{
		/* Obtenemos los slots del DOUBLE, si no esta inicializado salimos */
		if( !HPcryoDoubleGetSlots( &mainSlot, &offSlot, HP, PRF)){ return 0;}
		
		/* Miramos si somos el principal */
		if( mainSlot != HPcryoGetSlot( HP, PRF)){ return 0;}
	}
	
	/* No podemos iniciar si ya esta el test en marcha */
	if( HP->SAT.testRun.bits.RGB != 0){ return 0;}
	
	/* Arrancamos el test */
	HP->SAT.RGB.tmr = 0;
	HP->SAT.RGB.switchTime = HP_CRYO_SAT_RGB_TEST_SWITCH_TIME;
	HP->SAT.RGB.curColor = 0;
	HP->SAT.RGB.colors[0] = HP_CRYO_CTLLED_COLOR_ROJO;
	HP->SAT.RGB.colors[1] = HP_CRYO_CTLLED_COLOR_VERDE;
	HP->SAT.RGB.colors[2] = HP_CRYO_CTLLED_COLOR_AZUL;
	HP->SAT.testRun.bits.RGB = 1;
	HP->status = HP_CRYO_SAT;
	HP->PrevStatusSAT = 1;
	
	/* Todo OK */
	return 1;
}

uint8 HPcryoSAT_RGBtestStop( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
	/* Solo se para el test si éste se esta ejecutando */
	if( HP->SAT.testRun.bits.RGB == 0){ return 0;}
	
	/* Pasamos el HP a Idle, esto para el proceso */
	//HPcryoIdle( 0, HP, PRF); //Bug de gestion, te para el cooling al pasar a IDLE pero el test cooling consta como en marcha. No hacer esto. Por otro lado resetear todas las variables del SAT al salir de la pantalla.
		
	/* Reseteamos variables */
	HP->SAT.testRun.bits.RGB = 0;
	HP->SAT.RGB.tmr = 0;
	HP->SAT.RGB.switchTime = HP_CRYO_SAT_RGB_TEST_SWITCH_TIME;
	HP->SAT.RGB.curColor = 0;
	HP->SAT.RGB.colors[0] = HP_CRYO_CTLLED_COLOR_ROJO;
	HP->SAT.RGB.colors[1] = HP_CRYO_CTLLED_COLOR_VERDE;
	HP->SAT.RGB.colors[2] = HP_CRYO_CTLLED_COLOR_AZUL;
	
	/* Todo OK */
	return 1;
}

void HPcryoSATallTestStop( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Paramos todos los test */
	HPcryoSATcoolingTestStop( HP, PRF);
	HPcryoSATvacumTestStop( HP, PRF);
	HPcryoSATbodyFillSensorTestStop( HP, PRF);
	HPcryoSAT_RGBtestStop( HP, PRF);
	
	HPcryoIdle( 0, HP, PRF);
}
//SAT

//uint32 RFID_time_ref[4];	//DEBUG	-	Tiempos de referencia para calculo de tiempos del modulo RFID
//uint32 RFID_time_diff[4];	//DEBUG	-	Diferencia de tiempos con los de referencia

/* FUNCIONES PUBLICAS PARA PERIFERICO */
void HPcryoInit( void)
{
	uint8 i;
	tHPcryoData *HP;
	
	//for ( i=0;i<4;i++) RFID_time_ref[i] = 0;	//DEBUG	-	Inicialización de tiempos para debugar
	//for ( i=0;i<4;i++) RFID_time_diff[i] = 0;	//DEBUG	-	Inicialización de tiempos para debugar
	
	/* Inicializamos el vector de estructuras de datos de este tipo de periferico */
	for( i = 0; i < HPCRYO_MAX_N_PERIFS; i++)
	{
		HP = &( HPcryoData[i]);
		HPcryoClearData( HP);
	}
}

uint8 HPcryoIsThisModelYours( uint32 model)
{
	uint8 cnt;
	
	/* Buscamos el modelo en la lista, si lo encontramos devolvemos TRUE */
	for( cnt = 0; cnt < HP_CRYO_NUM_HP_MODELS; cnt++)
	{
		if( HP_CRYO_MODEL_LIST[cnt] == model){ return 1;}
	}
	
	/* No hemos encontrado el modelo, devolvemos FALSE */
	return 0;
}

/* FUNCIONES PRIVADAS */
void HPcryoTestVacumUpdate( tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Memorizamos el último cambio de estado, si cambiamos el estado deseado durante el proceso
//	 * tenemos que activar el timeOut. De este modo podemos hacerlo sistematicamente */
//	cHPcryoHWstatus lastChange = HP->frames.mainIn.data.cambio_estado;
		
//	/* Primero comprobamos que el proceso del test esta en marcha, es decir, no puede ser que
//	 * entremos con el motor valiendo DONE o FAIL */
//	if( HP->tstVac.status != HP_CRYO_TEST_VAC_DONE && HP->tstVac.status != HP_CRYO_TEST_VAC_FAIL)
//	{
//		/* Comprobamos si estamos ejecutando un flanco de cambio de estado */
//		if( HP->tstVac.timeOut != 0)
//		{
//			/* Estamos esperando al flanco */
//			if( TICKS_DiffTicks( HP->tstVac.timeOut) > HP_CRYO_CHANGE_STATUS_FLANK_TIME){ HP->tstVac.timeOut = 0;}
//		}
//		else
//		{
//			/* Según el estado del manípulo */
//			switch( HP->frames.mainOut.data.estado)
//			{
//				/* IDLE, aqui o bien se ha terminado el proceso o bien no se ha producido correctamente el
//				 * flanco para el cambio de estado. */
//				case HP_CRYO_MAN_IDLE:
//					/* Si estamos en USER_START significa que posiblemente el flanco de cambio de estado no sea
//					 * OK, si no estamos en USER_START asumimos que el proceso ha terminado con éxito */
//					if( HP->tstVac.status != HP_CRYO_TEST_VAC_RUN_WAITING_USER_START)
//					{
//						HP->tstVac.status = HP_CRYO_TEST_VAC_DONE;
//					}
//					else
//					{
//						/* Estamos en USER_START, gestionamos el flanco de cambio de estado si el cambio
//						 * de estado no es a READY pasamos a READY y si es a
//						 * READY pasamos a IDLE para forzar el flanco. Despues lanzamos la espera */
//						if( HP->frames.mainIn.data.cambio_estado != HP_CRYO_MAN_READY)
//						{
//							/* No esta en READY, pasamos a READY y lanzamos la espera */
//							HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_READY;
//						}
//						else
//						{
//							HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
//						}
//					}
//					break;
//				case HP_CRYO_MAN_READY:
//					/* Estamos a la espera de que el usuario pulse el boton */
//					HP->tstVac.status = HP_CRYO_TEST_VAC_RUN_WAITING_USER_START;
//					break;
//				case HP_CRYO_MAN_WAITINGSETPOINTS:
//					/* A la espera de que el HP acabe de realizar la succión */
//					HP->tstVac.status = HP_CRYO_TEST_VAC_RUN_VACUM;
//					break;
//				case HP_CRYO_MAN_INPROGRESS:
//					/* La succión ha concluido, pasamos a PAUSE para evitar que se arranque la hidráulica
//					 * del HP */
//					HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_PAUSE;
//					HP->tstVac.status = HP_CRYO_TEST_VAC_RUN_WAITING_USER_END;
//					break;
//				case HP_CRYO_MAN_PAUSE:
//					/* Estamos a la espera de que el usuario pulse para acabar el test y soltar el vacum */
//					HP->tstVac.status = HP_CRYO_TEST_VAC_RUN_WAITING_USER_END;
	 
//					/* Si estamos en modo auto tenemos que comprobar si la plica ha llegado e indicarlo
//					 * al usuario */
//					if( HP->tstVac.mode == HP_CRYO_TEST_VAC_MODE_AUTO)
//					{
//						/* Encendemos los LED's y comprobamos si la plica ha llegado */
//						HP->frames.mainIn.data.enable_plica = 1;		//V7760 - Una vez se analice aquí los valores, se actualizarán las imagenes del test para decir si es OK o KO
//						HP->tstVac.autoIsOK = ( HP->frames.mainOut.data.estado_entradas.bit_field.detec_plica_dcha ||
//												HP->frames.mainOut.data.estado_entradas.bit_field.detec_plica_iza);
//					}
//					break;
//				case HP_CRYO_MAN_FINISHING:
//					/* El HP esta soltando el vacum, tras esto pasara a IDLE */
//					HP->tstVac.status = HP_CRYO_TEST_VAC_RUN_WAITING_USER_END;
			
//					/* Apagamos el detector de plica */
//					HP->frames.mainIn.data.enable_plica = 0;
//					break;
//				case HP_CRYO_MAN_MANIPULO_DESHAB_ERROR_COMS:
//				case HP_CRYO_MAN_DESCONFIGURADO:
//				case HP_CRYO_MAN_ALARM:
//					/* Estados de alarma, la logica de gestión de errores se encarga
//					 * de la politica a seguir. No cambiamos nada en el estado del
//					 * test de vacum */
//					break;
//				default:
//					/* No esta en ninguno de los estados previstos. Damos por fallido el test */
//					HP->tstVac.status = HP_CRYO_TEST_VAC_FAIL;
//					break;
//			}
//		}
		
//		/* Comprobamos si ha habido cambio en el estado deseado para activar el timeOut */
//		if( HP->frames.mainIn.data.cambio_estado != lastChange){ HP->tstVac.timeOut = TICKS_GetTicks();}
//	}
}

/*DEBUG*/
//uint32 touh, touh2, touh3;
//uint32 diftouh, diftouh2, diftouh3;
//LDD_RTC_TTime TimeRTC;
/*DEBUG*/

void HPcryoTrtUpdate( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 cnt;
	uint8 i;
	uint32 TRTtime_elapse, TRTtime_total;
	uint8 MainSlotDouble, SecondSlotDouble;
	tHPcryoData *HPdouble;
	tPRFdata *PRFdouble;
	uint32 model;
	static uint32 log_HP_refTime[HPCRYO_MAX_N_PERIFS] = {0,0,0,0};
	static uint32 LOG_Maq_time_ref = 0;

	//Variables que han de gestionarse para emplear de forma externa la configuración especial del tratamiento en función de la etiqueta RFID leida
	uint8 Label_Read_index;
	cHPcryoRFID_err RFID_err_code;
	
//	/* Memorizamos el último cambio de estado, si cambiamos el estado deseado durante el proceso
//	 * tenemos que activar el timeOut. De este modo podemos hacerlo sistematicamente */
//	cHPcryoHWstatus lastChange = HP->frames.mainIn.data.cambio_estado;
	
//	model = PRF->common->data.fields.model;
	
//	HP->trt.RFIDstatus = RUNNING;
	
//	/* Primero comprobamos que el proceso esta en marcha, es decir, no puede ser que
//	 * entremos con el motor valiendo DONE o FAIL */
//	if( HP->trt.status != HP_CRYO_TREATMENT_DONE && HP->trt.status != HP_CRYO_TREATMENT_FAIL)
//	{
//		/* Comprobamos si estamos ejecutando un flanco de cambio de estado */
//		if( HP->trt.timeOut != 0)
//		{
//			/* Estamos esperando al flanco */
//			if( TICKS_DiffTicks( HP->trt.timeOut) > HP_CRYO_CHANGE_STATUS_FLANK_TIME){ HP->trt.timeOut = 0;}
//		}
		
//		if( HP->trt.timeOut == 0)
//		{
//			/* No estamos esperando al flanco, podemos mirar el estado del HP contando que nuestra
//			 * ultima orden de cambio ya se ha ejecutado */
//			/* Miramos si estamos en PAUSE */
//			if( HP->trt.status == HP_CRYO_TREATMENT_RUN_PAUSE)
//			{
//				/* Gestion en estado PAUSE */
//				switch( HP->frames.mainOut.data.estado)
//				{
//					case HP_CRYO_MAN_IDLE:
//						/* En IDLE no hacemos nada. El estado ya es correcto */
//						break;
//					case HP_CRYO_MAN_TESTPELTIERS:
//					case HP_CRYO_MAN_READY:
//						/* No podemos estar en READY, pasamos a IDLE */
//						HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
//						break;
//					case HP_CRYO_MAN_WAITINGSETPOINTS:
//					case HP_CRYO_MAN_INPROGRESS:
//						/* Si estamos con el tratamiento en marcha pasamos a PAUSE */
//						HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_PAUSE;
//						break;
//					case HP_CRYO_MAN_PAUSE:
//						/* Pasamos a pause para forzar el flanco. Si ya hemos ido
//						 * a WAITING antes para reanudar pero el HP ha pasado solo
//						 * a PAUSE tendremos WAITING en el ultimo resume y al hacer
//						 * el nuevo no haremos el flanco */
//						HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_PAUSE;
//						break;
//					case HP_CRYO_MAN_FINISHING:
//						/* En estos estados no es necesario cambiar */
//						break;
//					case HP_CRYO_MAN_MANIPULO_DESHAB_ERROR_COMS:
//					case HP_CRYO_MAN_DESCONFIGURADO:
//					case HP_CRYO_MAN_ALARM:
//						/* Estados de alarma, la logica de gestión de errores se encarga
//						 * de la politica a seguir. No cambiamos nada en el estado del
//						 * tratamiento */
//						break;
//					default:
//						/* Caso no posible. Damos por fallido el tratamiento */
//						HP->trt.status = HP_CRYO_TREATMENT_FAIL;
//						break;
//				}
//			}
//			else
//			{
//				/* Gestion cuando no estamos en PAUSE */
//				switch( HP->frames.mainOut.data.estado)
//				{
//					case HP_CRYO_MAN_IDLE:
//						/* Estamos en IDLE, si estamos en estado de espera al RF-ID ya estamos bien.
//						 * Si no tenemos que pasar a READY si estamos en USER_START o hemos terminado
//						 * el tratamiento si estamos en otro estado.
//						 * Primero reseteamos el contador de errores de resucción */
//						for( cnt = 0; cnt <= HP_CRYO_MAX_VACUM_RETRYS; cnt++)
//						{ ERR_delete( Error_NResuccionesMAN1 + HPcryoGetSlot( HP, PRF) - 1);}
						
//						/* Logica de MAN_IDLE */
//						if( HP->trt.status == HP_CRYO_TREATMENT_RUN_WAITING_RFID)
//						{
//							HP->trt.RFIDstatus = HPCryoRFIDcheckLabel( &Label_Read_index, HP_CRYO_RFID_TIME_MAX_TO_READ, &RFID_err_code, HP, PRF);
//							/*V7775*/
//							for (i = HP_CRYO_LABEL_ZO; i<HP_CRYO_NUM_LABELS; i++)
//							{
//								if ((HP_CYRO_LABEL_REQUESTED [i][HPcryoGetModel( HP, PRF)] == HP_CRYO_DEFAULT) ||
//									 (HP_CYRO_LABEL_REQUESTED [i][HPcryoGetModel( HP, PRF)] == HP_CRYO_VALID))
//								{
//									if(EXP_UCreuseLabel (PRF->IDperifHW, i))
//									{
//										AppGUI_RFIDpopup_ReuseOption (1);	//Indicamos al popup que si se puede reusar la label
//										break;
//									}
//								}
//							}
//							if(HP->trt.Label_reuse)
//							{
//								HP->trt.RFIDstatus = SUCCESS;
//								Label_Read_index =  EXP_UCreuseLabelType (PRF->IDperifHW);
//								HP->frames.mainIn.data.u16SegundosTratamiento = EXP_UCreuseLabelTRTtime(PRF->IDperifHW) + HP_CRYP_TRT_TIME_OFFSET;
//								HP->trt.trtTime_s = EXP_UCreuseLabelTRTtime(PRF->IDperifHW);
//								HP->trt.Label_reuse = 0;
//							}
//							/*V7775*/
//							/* Procesado del RF-ID. Primero lock al recurso RF-ID PDTE */
//							switch (HP->trt.RFIDstatus)		//Llamada a la función que realiza la gestión de la lectura con el módulo RFID
//							{
//								case RUNNING:		//En caso de que el proceso esté en este estado, se continuará con el proceso sin ninguna alteración
//									break;
//								case SUCCESS:		//En caso de que la lectura haya tenido exito se procederá con el siguiente paso del tratamiento
//									HP->trt.Label_accepted = Label_Read_index;
//									/* RF-ID OK, toallita correcta. Aplicamos los limites asociados a la toallita detectada */
//									HPcryoRFIDlabelLimits( Label_Read_index, HP, PRF);
//									EXP_UCperifNEWlabel (PRF->IDperifHW, Label_Read_index, HPcryoTrtGetTreatmentTotalTimeSeconds( HP, PRF));	/*V7775*/
									 
//									/* Incrementamos el contador de tratamientos - V7790 */
//									MemoryMap.var.var_flash.TreatmentCount++;
//									//EXPdata.UC.Config_Param.data.treatment_num++;
//									//while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
									
//									HP->trt.HPtreatment_Num = MemoryMap.var.var_flash.TreatmentCount;
									
//									 /* Pasamos al siguiente estado en el tratamiento */
//									HP->trt.status = HP_CRYO_TREATMENT_RUN_WAITING_USER_START;
//									HP->trt.RFIDpopupTimer = TICKS_GetTicks();			//V7760 - Tomar referencia de tiempo de cuando se ha leido con extio la etiqueta RFID
//									HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_READY;
									
//									HPCryoRFIDreset ( HP, PRF);					//Se realiza un reset de los parametros relacionados con la reserva del recurso del RFID
									
//									BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );		//Se indica de forma sonora el exito de la lectura
//									break;
//								case ERROR:			//En caso de que el proceso devuelva error
//									if(RFID_err_code == HP_CRYO_RFID_LABEL_INVALID)				//Si ha sido provocado por la lectura de una etiqueta erronea
//									{
//										BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );				//se indica co nuna señal sonora y se permite seguir leyendo más etiquetas
//									}
//									if (RFID_err_code == HP_CRYO_RFID_FAILURE)					//Si el error es por un error durante la lectura
//									{
//										HPCryoRFIDreset ( HP, PRF);								//Se realiza un reset de los parametros relacionados con la reserva del recurso del RFID
//										HPcryoStop(1, HP, PRF);									//Paramos el tratamiento
//									}
//									break;
//								default:							//En cualquier otro estado reseteamos las variables de reserva de recurso
//									HPCryoRFIDreset ( HP, PRF);
//									//ERROR
//									break;
//							}
//						}
//						else if( HP->trt.status == HP_CRYO_TREATMENT_RUN_WAITING_USER_START)
//						{
//							/* Estamos en USER_START y el manípulo esta en IDLE. Posible fallo de flanco
//							 * en la orden de cambio de estado */
//							if( HP->frames.mainIn.data.cambio_estado == HP_CRYO_MAN_READY)
//							{HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;}
//							else
//							{HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_READY;}
//						}
//						else
//						{
//							/* Estamos en MAN_IDLE y no es ni USER_START ni RF-ID. Aqui puede ser fin de tratamiento
//							 * o bien reintento de succión, con lo que tenemos que volver a MAN_READY o RF-ID si se han
//							 * sobrepasado los reintentos máximos. */
//							if( !HPcryoTrtVacumRetry( HP, PRF)){ HP->trt.status = HP_CRYO_TREATMENT_DONE;}
//						}
//						break;
//					case HP_CRYO_MAN_READY:
//						/* Estamos a la espera de que el usuario pulse el boton */
//						HP->trt.status = HP_CRYO_TREATMENT_RUN_WAITING_USER_START;
//						HP->trt_OscTemp_timer = TICKS_GetTicks();

//						//if(AppGPRS_GetMCCstatus() == RUNNING){AppGPRS_reset();}		//V7790 - GPRS reset modulo (cancela comunicaciones en caso de iniciar tratamiento)
						
//						Temp_SAFE_Clear (HP, PRF);			/* V7790 - TEMP SAFE - CORRECCION: Al pausar el tratamiento resetear variables */
						
//						AppLOG_saveTRT(HP, PRF);			/* V7790LOG- Trt */
//						if((TICKS_DiffTicks(LOG_Maq_time_ref) > APP_LOG_TIME_TO_REC_MACHINE))
//						{
//							LOG_Maq_time_ref = TICKS_GetTicks();
//							AppLOG_saveMachine();									/* V7790 - LOG maquina */
//						}
//						break;
//					case HP_CRYO_MAN_WAITINGSETPOINTS:
//						/* A la espera de que el HP acabe de realizar la succión */
//						HP->trt.status = HP_CRYO_TREATMENT_RUN_VACUM;
						
//						/*V7778*/
//						if(EXP_UCtempSlopeStatus()){	HPcryo_Resume_Cooling(HP, PRF);	}		//aqui
//						/*V7778*/

//						AppLOG_saveTRT(HP, PRF);			/* V7790LOG- Trt */
//						if((TICKS_DiffTicks(LOG_Maq_time_ref) > APP_LOG_TIME_TO_REC_MACHINE))
//						{
//							LOG_Maq_time_ref = TICKS_GetTicks();
//							AppLOG_saveMachine();									/* V7790 - LOG maquina */
//						}
						
//						/* Control de resucciones */
//						HPcryoCtrlVacumRetrys( HP, PRF);
//						break;
//					case HP_CRYO_MAN_INPROGRESS:
//						/* La succión ha concluido, estamos en tratamiento */
//						HP->trt.status = HP_CRYO_TREATMENT_RUN_COOLING;
						
//						/* Empezamos a contar el tiempo de tratamiento */
//						if( HP->trt.startTime == 0){ HP->trt.startTime = TICKS_GetTicks();}
//						else
//						{
//							/* Ya estamos contando tiempo, comprobamos si ha habido reintento y tenemos
//							 * que descontar el tiempo con el HP "parado" */
//							if( HP->trt.vacumRetryRlsTime != 0)//> HP->trt.startTime)
//							{
//								if(HP->trt.vacumRetryCnt == HP_CRYO_TRT_VACUM_RETRY_NUM)	//V7775
//								{
//									HP->trt.startTime = TICKS_GetTicks();					//V7775
//								}
//								else
//								{
//									HP->trt.startTime += ( TICKS_DiffTicks( HP->trt.vacumRetryRlsTime));
//								}
//								HP->trt.vacumRetryRlsTime = 0;
//							}
//						}
						
//						/* Comprobamos si ha transcurrido el total de tiempo del tratamiento */
//						if( TICKS_DiffTicks( HP->trt.startTime) >= HP->trt.trtTime_s * 1000)
//						{
//							/* Tiempo de tratamiento transcurrido, pasamos a MAN_PAUSE para terminar el tratamiento */
//							if( HP->frames.mainIn.data.cambio_estado == HP_CRYO_MAN_PAUSE)
//							{HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_INPROGRESS;}
//							else
//							{HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_PAUSE;}
//						}
						
//						/* Control de resucciones */
//						HPcryoCtrlVacumRetrys( HP, PRF);
						
//						/* Control modo automático */
//						#ifdef APP_SW_VER_AUTO_ENABLE
//						HPcryoTrtAutoModeHdlr( HP, PRF);
//						#endif
						
//						/* Si no se llena la plica se pausa el tratamiento - V7760 */
						
						
//						/* V7778 - TEMP SEC */
//						/* Control de bajada de temperatura regulada */
//						if(EXP_UCtempSlopeStatus()){	HPcryo_Cooling_process(HP, PRF);	}

//						if(model == HP_CRYO_MODEL_DOUBLE)
//						{
//							HPcryoDoubleGetSlots( &MainSlotDouble, &SecondSlotDouble, HP, PRF);
//							if(HPcryoGetFromSlot( SecondSlotDouble, &HPdouble, &PRFdouble))
//							{
//								HPdouble->frames.mainIn.data.fConsignaTemperatura = HP->frames.mainIn.data.fConsignaTemperatura;
//								HPdouble->trt.trt_temp_set = HP->trt.trt_temp_set;
//							}
//						}
						
//						/* V7790 - TEMP SAFE */
//						Temp_SAFE_Update(1000, HP, PRF);
						
//						AppLOG_saveTRT(HP, PRF);			/* V7790LOG- Trt */
//						if((TICKS_DiffTicks(LOG_Maq_time_ref) > APP_LOG_TIME_TO_REC_MACHINE))
//						{
//							LOG_Maq_time_ref = TICKS_GetTicks();
//							AppLOG_saveMachine();									/* V7790 - LOG maquina */
//						}
						
					
//						/* V7778 - TEMP SEC */
						
//						/* Control para variar la consigna de temperatura (temperatura bailonga) - Soluciona el problema para lo manipulos con versiçon de SW interior a la V20 (Problema con sondas de temperatura clavadas) */
//						HPcryoTrtSetPointOsc( HP_CRYO_TIME_LOOP_OSC_SET_POINT_TEMP, HP, PRF);  /*V7778*/
						
//						/*V7775*/
//						TRTtime_elapse = HPcryoTrtGetTimeSeconds( HP, PRF);
//						TRTtime_total =  HPcryoTrtGetTreatmentTotalTimeSeconds( HP, PRF);
//						EXP_UCupdateTRTtimeReuseLabel (PRF->IDperifHW, TRTtime_total - TRTtime_elapse);
						
//						/* Automáticamente lanzamos el proceso de limpieza tras el tratamiento *//*V7775 si se ha completado el 85% del tratamiento*/
//						if((HP->cleanUp.LabelRQcleanup == HP_CRYO_LABEL_REQ_CLEANUP)&&(TRTtime_elapse > (HP->trt.trtTime_s*HP_CRYO_TRT_PERCENT_COMPLETE_2_CLEAN)))
//						{
//#ifdef APP_SW_VER_CLEANUP_ENABLE
//							HP->cleanUpRqst = HP_CRYO_CLEAN_UP_RQST_WITH_CHECK;			//CleanUpEnable
//#endif
//							HP->cleanUpInitOrEnd = HP_CRYO_CLEAN_UP_END_OF_TRT;
//						}
//						break;
//					case HP_CRYO_MAN_PAUSE:
//						/* Depende de si venimos de hacer pausa al tratamiento o si el tratamiento ha concluido
//						 * por si solo. En ambos casos estará el HP en MAN_PAUSE */
//						HP->trt.status = HP_CRYO_TREATMENT_RUN_WAITING_USER_END;

//						AppLOG_saveTRT(HP, PRF);			/* V7790LOG- Trt */
//						if((TICKS_DiffTicks(LOG_Maq_time_ref) > APP_LOG_TIME_TO_REC_MACHINE))
//						{
//							LOG_Maq_time_ref = TICKS_GetTicks();
//							AppLOG_saveMachine();									/* V7790 - LOG maquina */
//						}
//						break;
//					case HP_CRYO_MAN_FINISHING:
//						/* El HP esta soltando el vacum, tras esto pasara a IDLE */
//						HP->trt.status = HP_CRYO_TREATMENT_RUN_WAITING_USER_END;

//						AppLOG_saveTRT(HP, PRF);			/* V7790LOG- Trt */
//						if((TICKS_DiffTicks(LOG_Maq_time_ref) > APP_LOG_TIME_TO_REC_MACHINE))
//						{
//							LOG_Maq_time_ref = TICKS_GetTicks();
//							AppLOG_saveMachine();									/* V7790 - LOG maquina */
//						}
//						break;
//					case HP_CRYO_MAN_MANIPULO_DESHAB_ERROR_COMS:
//					case HP_CRYO_MAN_DESCONFIGURADO:
//					case HP_CRYO_MAN_ALARM:
//						/* Estados de alarma, la logica de gestión de errores se encarga
//						 * de la politica a seguir. No cambiamos nada en el estado del
//						 * tratamiento */
//						break;
//					default:
//						/* No esta en ninguno de los estados previstos. Damos por fallido el test */
//						HP->trt.status = HP_CRYO_TREATMENT_FAIL;
//						break;
//				}
//			}
			
//			/* Comprobamos si ha habido cambio en el estado deseado para activar el timeOut */
//			if( HP->frames.mainIn.data.cambio_estado != lastChange){ HP->trt.timeOut = TICKS_GetTicks();}
//		}
//	}
}

/* - Fatiga - */

/*Pone al HP en el estado de FATIGA e indica que no se ha completado ninguna fatiga*/
uint8 HPcryoFatiga ( tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
//	/* Solo podemos ir al Fatiga si la maquina de estados esta en IDLE */
//	if( HP->status != HP_CRYO_IDLE){ return 0;}
	
//	HP->status = HP_CRYO_FATIGUE_0;
	
//	HPcryoFatigaComplete (HP_CRYO_FAT_DONE_NONE, HP, PRF);
	
	return 1;
}

/*Se lanza la fatiga que se indique (Fatiga1 o Fatiga2)*/
uint8 HPcryoFatigaStart ( cHPcrypFatigueRqst fatiga, tHPcryoData *HP, tPRFdata *PRF)
{
	/* Comprobamos que el periferico este en estado RUNNING */
	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
	/* Solo podemos ir al Fatiga si la maquina de estados esta en IDLE */
	if( HP->status != HP_CRYO_FATIGUE_0){ return 0;}
	
	if ((fatiga > HP_CRYO_FAT_STOP) && (fatiga < HP_CRYO_FAT_MAX))
	{
		HP->fatigue_requested = fatiga;
		HP->fatigue_substep = 0;
	}
	else{ return 0;}
	
	return 1;
}

/*Se para el proceso de fatiga*/
uint8 HPcryoFatigaStop ( tHPcryoData *HP, tPRFdata *PRF)
{
	HP->fatigue_requested = HP_CRYO_FAT_STOP;
	
	return 1;
}

/*Registra que fatiga ha sido completada*/
//uint8 HPcryoFatigaComplete ( cHPcrypFatigueComplete fatigaDone, tHPcryoData *HP, tPRFdata *PRF)
//{
//	/* Comprobamos que el periferico este en estado RUNNING */
//	if( PRF->status != PRF_STATUS_RUNNING){ return 0;}
		
//	/* Solo podemos ir al Fatiga si la maquina de estados esta en FATIGA */
//	if( HP->status != HP_CRYO_FATIGUE_0){ return 0;}
	
//	HP->fatigue_done = fatigaDone;
//	HP->fatigue_substep = 0;
	
//	return 1;
//}

/*Indica que fatiga ha sido completada*/
cHPcrypFatigueComplete HPcryoFatigaState ( tHPcryoData *HP, tPRFdata *PRF)
{
	return HP->fatigue_done;
}

/*Proceso de Fatiga1*/
cHPcryoFatigueStatus HPcryoFtg1Update( cPRFslot perif)
{
	uint8 count = 0;		//usado para acumular
	static uint32 t_ref;	//usado para hacer filtros de tiempo
	uint8 i; 				//usado para bucles
	tHPcryoData *HP;
	tPRFdata *PRF;
	
//	if(HPcryoGetFromSlot( perif, &HP, &PRF))
//	{
//		switch (HP->fatigue_substep)
//		{
//		case 0:											/*Primero comprobamos que el manipulo que vayamos a testear y los anteriores estén conectados, y los posteriores estén desconectados*/
//			for(i=PRF_HW_SLOT1;i<=PRF_HW_SLOT4;i++)
//			{
//				if(i<=perif)
//				{	if(HPcryoGetFromSlot( i, &HP, &PRF))
//					{
//						if(PRF->isUsed)	{  count++; }
//						HP->frames.mainIn.data.fConsignaTemperatura = 0.0;		/*Los HP conectados tienen que tener las variables inicializadas*/
//						HP->frames.mainIn.data.fTemperaturaInicio = 0.0;
//						HP->frames.mainIn.data.fConsignaVacum = 0.0;
//					}
//				}
//				else{	if(HPcryoGetFromSlot( i, &HP, &PRF) == 0)	count++;	}
//			}
//			if(count == PRF_REMAP_MAX_N_PERIFS){	if(HPcryoGetFromSlot( perif, &HP, &PRF)){HP->fatigue_substep = 1;}	t_ref = TICKS_GetTicks();	}		/*Si todos los conectores están como se espera, se continúa con el siguiente proceso*/
//			break;
//		case 1:
//			if(HPcryoGetFromSlot( perif, &HP, &PRF))
//			{
//				if (HP->frames.mainOut.data.estado != HP_CRYO_MAN_TESTPELTIERS)			/*El HP inicia el Vacuum*/
//				{
//					HP->frames.mainIn.data.fConsignaTemperatura = 0.0;	/*F1 - Power 0*/
//					HP->frames.mainIn.data.fTemperaturaInicio = 0.0;	/*F2 - Power 0*/
//					HP->frames.mainIn.data.fConsignaVacum = 300.0;		/*Vacuum - 300*/
//					HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_TESTPELTIERS;
//				}
//				else
//				{
//					t_ref = TICKS_GetTicks();		/*Tomamos referencia de tiempo para los 20 segundos*/
//					HP->fatigue_substep = 2;
//				}
//			}
//			else{	HP->fatigue_substep = 0;	}	/*En caso de que el HP falle en el proceso se resetea*/
//			break;
//		case 2:
//			if(HPcryoGetFromSlot( perif, &HP, &PRF))
//			{
//				if (HP->frames.mainOut.data.presionVaccum < 10.0){	t_ref = TICKS_GetTicks();	}		/* Si no se supera un mínimo de presión, se sigue actualizando el tiempo de referencia*/
								
//				if(TICKS_DiffTicks(t_ref) > 20000)		/*Una vez pasan los 20 segundos*/
//				{
//					if(HP->frames.mainOut.data.presionVaccum < 100.0)		/*Se comprueba que el vacuum está por debajo de una consigna que indique que los tubos no están pinzados ni obstruidos*/
//					{
//						HP->frames.mainIn.data.fConsignaTemperatura = 0.0;			/*A continuación mandamos el HP a pause y reiniciamos los valores de consigna*/
//						HP->frames.mainIn.data.fTemperaturaInicio = 0.0;
//						HP->frames.mainIn.data.fConsignaVacum = 0.0;
//						HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_PAUSE;
//						return perif;
//					}
//				}
//			}
//			else{	HP->fatigue_substep = 0;	}	/*En caso de que el HP falle en el proceso se resetea*/
//			break;
//		default: break;
//		}
//	}
	return HP_CRYO_FAT_Running;
}

/*Proceso de Fatiga2*/
cHPcryoFatigueStatus HPcryoFtg2Update( cPRFslot perif)
{
	tHPcryoData *HP;
	tPRFdata *PRF;
	static float temp_dch_ref[PRF_REMAP_MAX_N_PERIFS], temp_izq_ref[PRF_REMAP_MAX_N_PERIFS];	//Referencias de temperatura
	
//	if(HPcryoGetFromSlot( perif, &HP, &PRF))
//	{
//		switch (HP->fatigue_substep)
//		{
//		case 0:
//			if(HPcryoGetFromSlot( perif, &HP, &PRF))
//			{
//				temp_dch_ref[perif-1] = HP->frames.dbgOut.data.MedidasTemperatura[0];	/*Tomamo referencias de temperatura para comprobar el funcionamiento de las fuentes*/
//				temp_izq_ref[perif-1] = HP->frames.dbgOut.data.MedidasTemperatura[1];
				
//				HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_TESTPELTIERS;
//				HP->frames.mainIn.data.fConsignaVacum = 300.0;						/*Vacuum 300*/
				
//				if((temp_dch_ref[perif-1]<40) && (temp_izq_ref[perif-1]<40))			/*Si las referencias de teperatura están en un rango adecuado continuamos*/
//				{
//					HP->frames.mainIn.data.fConsignaTemperatura = 100.0;					/*F1 - 100%*/
//					HP->frames.mainIn.data.fTemperaturaInicio = 100.0;						/*F2 - 100%*/
//					HP->fatigue_substep = 1;
//				}
//			}
//			break;
//		case 1:
//			if(HPcryoGetFromSlot( perif, &HP, &PRF))
//			{
//				if(HP->frames.mainOut.data.presionVaccum > (300.0*0.8))		/*Si el vacuum es superior al 80% de su consigna*/
//				{
//					if((HP->frames.dbgOut.data.MedidasTemperatura[0] > (temp_dch_ref[perif-1] + 3.0)) && (HP->frames.dbgOut.data.MedidasTemperatura[1] > (temp_izq_ref[perif-1] + 3.0)))	/*Y las temperaturas han superado al menos 3ºC su referencia*/
//					{
//						return perif;	/*Finalizamos el proceso*/
//					}
//					else
//					{
//						HP->frames.mainIn.data.fConsignaTemperatura = 100.0;	/*F1 - 100%*/
//						HP->frames.mainIn.data.fTemperaturaInicio = 100.0;		/*F2 - 100%*/
//					}
//				}
//				else{	HP->frames.mainIn.data.fConsignaVacum = 300.0;		/*Vacuum 300*/		}
//			}
//			else{	HP->fatigue_substep = 0;	}	/*En caso de que el HP falle en el proceso se resetea*/
//			break;
//		default: break;
//		}
//	}
	return HP_CRYO_FAT_Running;
}

void HPcryoFtg3Update( tHPcryoData *HP, tPRFdata *PRF){}
void HPcryoFtg4Update( tHPcryoData *HP, tPRFdata *PRF){}
void HPcryoFtg5Update( tHPcryoData *HP, tPRFdata *PRF){}

/* - SAT - */

void HPcryoSATupdate( tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Miramos si el HP tiene el test de LED RGB en marcha */
//	if( HP->SAT.testRun.bits.RGB != 0)
//	{
//		/* Test en marcha, vamos cambiando el color */
//		if( HP->SAT.RGB.tmr == 0){ HP->SAT.RGB.tmr = TICKS_GetTicks();}
//		else
//		{
//			if( TICKS_DiffTicks( HP->SAT.RGB.tmr) > HP->SAT.RGB.switchTime)
//			{
//				HP->SAT.RGB.tmr = TICKS_GetTicks();
//				HP->SAT.RGB.curColor = ( HP->SAT.RGB.curColor + 1) % HP_CRYO_SAT_RGB_TEST_MAX_COLORS;
//				HPcryoSetLEDcolor( HP->SAT.RGB.colors[HP->SAT.RGB.curColor], HP, PRF);
//			}
//		}
//	}
//	else
//	{
//		/* EL test no esta en marcha, reseteamos variables */
//		HP->SAT.RGB.tmr = 0;
//		HP->SAT.RGB.switchTime = HP_CRYO_SAT_RGB_TEST_SWITCH_TIME;
//		HP->SAT.RGB.curColor = 0;
//		HP->SAT.RGB.colors[0] = HP_CRYO_CTLLED_COLOR_ROJO;
//		HP->SAT.RGB.colors[1] = HP_CRYO_CTLLED_COLOR_VERDE;
//		HP->SAT.RGB.colors[2] = HP_CRYO_CTLLED_COLOR_AZUL;
//	}
	
//	if (HP->SAT.testRun.byte == 0x00)
//	{
//		HPcryoIdle( 0, HP, PRF);
//	}
}

void HPcryoClearData( tHPcryoData *HP)
{
	uint8 j;
	
	HP->isUsed = 0;
	HP->cleanUpRqst = HP_CRYO_CLEAN_UP_RQST_NONE;
	HP->cleanUp.LabelRQcleanup = HP_CRYO_LABEL_REQ_CLEANUP;
	HP->cleanUpInitOrEnd = HP_CRYO_CLEAN_UP_NONE;
	HP->status = HP_CRYO_TEST_INIT;
	HP->time.updateTime_ms = 0;
	HP->time.remapTime_ms = 0;
	HP->time.ctrlTime_ms = 0;
	HP->time.refreshTime_ms = 0;
	HP->time.updatePeriod_ms = HP_CRYO_UPDATE_PERIOD_MS;
	HP->time.remapPeriod_ms = HP_CRYO_REMAP_REFRESH_PERIOD_MS;
	HP->time.ctrlPeriod_ms = HP_CRYO_CTRL_PERIOD_MS;
	HP->time.refreshPeriod_ms = HP_CRYO_VARS_REFRESH_PERIOD_MS;
	HP->idle.vacStatus = HP_CRYO_IDLE_VAC_STATUS_WITHOUT_VAC;
	HP->tstVac.timeOut = 0;
	HP->tstVac.status = HP_CRYO_TEST_VAC_DONE;
	HP->trt.status = HP_CRYO_TREATMENT_DONE;
	HP->trt.timeOut = 0;
	HP->trt.rqLbl = 0;
	HP->trt.RFID_reserved = 0;
//	HP->trt.RFID_read_label = RFID_NO_LABEL;
	HP->trt.RFIDpopupTimer = 0;
    HP->trt.RFIDstatus = (returnstatus_t)0;
	HP->trt.beforePause = HP_CRYO_TREATMENT_DONE;
	HP->trt.pauseTime = 0;
	HP->trt.startTime = 0;
	HP->trt.trtTime_s = 0;
	HP->trt.vacumRetryRqstUserToMoveHP = 0;
	HP->trt.mode = HP_CRYO_TRT_MODE_AUTO; //HP_CRYO_TRT_MODE_MANUAL;						  						
	HP->trt.adjustVacumCnt = 0;
	HP->trt.adjustVacumTimeOut = 0;
	HP->trt.adjustVacumStatus = HP_CRYO_ADJUST_VACUM_IDLE;
	HP->trt.adjustVacumValue = 0.0;
	HP->trt.adjustVacumResetTime = 0;
	HP->trt.vacumRetryCnt = 0;
	HP->trt.vacumRetryTimeOut = 0;
	HP->trt.vacumRetryRlsTime = 0;					   
	HP->trt.autoMode.status = HP_CRYO_TRT_AUTO_IDLE;  
	HP->trt.autoMode.tmr = 0;
	HP->trt.autoMode.waitTime = 0;
	HP->trt.autoMode.detectionTime = 0;
	HP->trt.autoMode.detectionFilterAcum = 0;
	HP->trt.autoMode.detectionFilterInc = 0;
	HP->trt.autoMode.detectionFilterDec = 0;
	HP->trt.autoMode.detectionFilterIsOKlvl = 0;
	HP->trt.autoMode.isOK = 0;								 
	HP->ctrl.minTempTimeOut = 0;
	HP->ctrl.maxTempTimeOut = 0;
	HP->ctrl.difTempTimeOut = 0;
	HP->ctrl.deltaTempTimeOut = 0;
	HP->cleanUp.status = HP_CRYO_CLEAN_UP_DONE;
	HP->cleanUp.time_ms = 0;
	HP->cleanUp.countDown_ms = 0;
	HP->cleanUp.checkPatientTime_ms = 0;
	HP->cleanUp.forceClean = 0;
	HP->cleanUp.cycle.tmrIsClean_ms = 0;
	HP->cleanUp.cycle.tmrCannotClean_ms = 0;
	HP->cleanUp.cycle.timeIsClean = 0;
	HP->cleanUp.cycle.timeCannotClean = 0;
	HP->cleanUp.cycle.cleanVacum = 0.0;	
	HP->cleanUp.cycle.NoUmbralVacResetFilter = 0;
	HP->SAT.testRun.byte = 0;		
	HP->SAT.RGB.tmr = 0;
	HP->SAT.RGB.switchTime = HP_CRYO_SAT_RGB_TEST_SWITCH_TIME;
	HP->SAT.RGB.curColor = 0;
	HP->SAT.RGB.colors[0] = HP_CRYO_CTLLED_COLOR_ROJO;
	HP->SAT.RGB.colors[1] = HP_CRYO_CTLLED_COLOR_VERDE;
	HP->SAT.RGB.colors[2] = HP_CRYO_CTLLED_COLOR_AZUL;
	for( j = 0; j < HP_CRYO_MAX_TEMP_SNS; j++){ HP->ctrl.difTempLastSnsValue[j] = 0.0;}
	HP->init.status = HP_CRYO_INIT_RQST_CONFIG;
	HP->finish.status = HP_CRYO_FINISH_CLEAR;
	for( j = 0; j < HP_CRYO_REMAP_FRAME_MAIN_IN_SIZE + 1; j++){ HP->frames.mainIn.vector[j] = 0;}
	for( j = 0; j < HP_CRYO_REMAP_FRAME_MAIN_OUT_SIZE + 1; j++){ HP->frames.mainOut.vector[j] = 0;}
	for( j = 0; j < HP_CRYO_REMAP_FRAME_CONFIG_IN_SIZE + 1; j++){ HP->frames.cfgIn.vector[j] = 0;}
	for( j = 0; j < HP_CRYO_REMAP_FRAME_CONFIG_OUT_SIZE + 1; j++){ HP->frames.cfgOut.vector[j] = 0;}
	for( j = 0; j < HP_CRYO_REMAP_FRAME_DEBUG_IN_SIZE + 1; j++){ HP->frames.dbgIn.vector[j] = 0;}
	for( j = 0; j < HP_CRYO_REMAP_FRAME_DEBUG_OUT_SIZE + 1; j++){ HP->frames.dbgOut.vector[j] = 0;}
	for( j = 0; j < HP_CRYO_REMAP_FRAME_PID_IN_SIZE + 1; j++){ HP->frames.PIDin.vector[j] = 0;}
	for( j = 0; j < HP_CRYO_REMAP_FRAME_PID_OUT_SIZE + 1; j++){ HP->frames.PIDout.vector[j] = 0;}	
	HP->warningFlags.caudal_entrada = 0;
	HP->warningFlags.circuito_temp_desconocido = 0;
	HP->warningFlags.espera_temp = 0;
	HP->warningFlags.espera_vac = 0;
	HP->warningFlags.hidraulica = 0;
	HP->warningFlags.seguridad_frio = 0;
	HP->warningFlags.sin_tramas_main = 0;
	HP->warningFlags.sonda_error = 0;
	HP->warningFlags.temp_clavada = 0;
	HP->warningFlags.temp_entrada = 0;
	HP->warningFlags.temperatura_window = 0;
	HP->warningFlags.test_sondas_fallido = 0;
	HP->warningFlags.vac_lvl = 0;
	HP->trt.trt_secure_plus_three = 0;
	HP->trt.set_temp_reached = 0;		//V7778
}

returnstatus_t HPcryoRefreshFrameMain( tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
	
//	/* Leemos los datos del buffer de la expansora sobre la trama MAIN_OUT */
//	ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_MAIN_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_MAIN_OUT_SIZE,
//								&( HP->frames.mainOut.vector[1]));
//	if( ret == ERROR){ return ret;}
	
//	/* Escribimos los datos de la trama MAIN_IN en el buffer de la expansora */
//	ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_MAIN_IN_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_MAIN_IN_SIZE,
//								&( HP->frames.mainIn.vector[1]));
	return ret;
}

returnstatus_t HPcryoRefreshFrameCfg( tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
	
//	/* Leemos los datos del buffer de la expansora sobre la trama MAIN_OUT */
//	ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_CONFIG_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_CONFIG_OUT_SIZE,
//								&( HP->frames.cfgOut.vector[1]));
//	if( ret == ERROR){ return ret;}
	
//	/* Escribimos los datos de la trama MAIN_IN en el buffer de la expansora */
//	ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_CONFIG_IN_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_CONFIG_IN_SIZE,
//								&( HP->frames.cfgIn.vector[1]));
	return ret;
}

returnstatus_t HPcryoRefreshFrameDbg( tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
	
//	/* Leemos los datos del buffer de la expansora sobre la trama MAIN_OUT */
//	ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_DEBUG_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_DEBUG_OUT_SIZE,
//								&( HP->frames.dbgOut.vector[1]));
//	if( ret == ERROR){ return ret;}
	
//	/* Escribimos los datos de la trama MAIN_IN en el buffer de la expansora */
//	ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_DEBUG_IN_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_DEBUG_IN_SIZE,
//								&( HP->frames.dbgIn.vector[1]));
	return ret;
}

returnstatus_t HPcryoReadFrames( tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
	
//	/* Leemos la trama MAIN */
//	ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_MAIN_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_MAIN_OUT_SIZE,
//								&( HP->frames.mainOut.vector[1]));
//	if( ret == ERROR){ return ret;}
	
//	/* Leemos la trama CFG */
//	ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_CONFIG_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_CONFIG_OUT_SIZE,
//								&( HP->frames.cfgOut.vector[1]));
//	if( ret == ERROR){ return ret;}
		
//	/* Leemos la trama DBG */
//	ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_DEBUG_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_DEBUG_OUT_SIZE,
//								&( HP->frames.dbgOut.vector[1]));
	return ret;
}

returnstatus_t HPcryoWriteFrames( tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
	
//	/* Escribimos la trama MAIN */
//	ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_MAIN_IN_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_MAIN_IN_SIZE,
//								&( HP->frames.mainIn.vector[1]));
//	if( ret == ERROR){ return ret;}
	
//	/* Escribimos la trama CFG */
//	ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_CONFIG_IN_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_CONFIG_IN_SIZE,
//								&( HP->frames.cfgIn.vector[1]));
//	if( ret == ERROR){ return ret;}
	
//	/* Escribimos la trama DBG */
//	ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_DEBUG_IN_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_DEBUG_IN_SIZE,
//								&( HP->frames.dbgIn.vector[1]));
	return ret;
}

void HPcryoInitFrameMainData( tHPcryoData *HP)
{
	/* Valores iniciales para la trama MAIN IN */
	HP->frames.mainIn.data.block_size = sizeof( tHPcryoRemapFrameMAIN_IN);
	HP->frames.mainIn.data.dummy = 0;
	HP->frames.mainIn.data.enable_plica = 0;					
	HP->frames.mainIn.data.color_led = HP_CRYO_CTLLED_COLOR_APAGADO;	
	HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;			
	HP->frames.mainIn.data.u16SegundosTratamiento = 0;		
	HP->frames.mainIn.data.fConsignaVacum = 0.0;					
	HP->frames.mainIn.data.fConsignaTemperatura = 30.0;				
	HP->frames.mainIn.data.fTemperaturaInicio = 30.0;			
	HPcryoSetAlarmCfg( 	HP_CRYO_DFLT_TRT_TEMP_WINDOW, HP_CRYO_DFLT_TRT_VAC_WAIT_TIME,
						HP_CRYO_DFLT_TRT_TEMP_WAIT_TIME, HP_CRYO_DFLT_TRT_VAC_FAIL_TIME,
						HP_CRYO_DFLT_TRT_TEMP_FAIL_TIME, HP_CRYO_DFLT_MAX_IN_TEMP[1],
						HP_CRYO_DFLT_TST_VAC_MIN_SNS_TEMP, HP_CRYO_DFLT_TRT_LOW_TEMP_TIME, HP);
	
	
	/* Valores iniciales para la trama MAIN OUT */
	HP->frames.mainOut.data.block_size = sizeof( tHPcryoRemapFrameMAIN_OUT);
	HP->frames.mainOut.data.estado_entradas.value = 0;
	HP->frames.mainOut.data.id_manipulo_asociado = 0;
	HP->frames.mainOut.data.id_manipulo_principal = 0;
	HP->frames.mainOut.data.avisos.u16Avisos = 0;
	HP->frames.mainOut.data.estado = HP_CRYO_MAN_INIT;
	HP->frames.mainOut.data.fTempManipulo = 0.0;
	HP->frames.mainOut.data.fTempIzquierda = 0.0;
	HP->frames.mainOut.data.fTempDerecha = 0.0;	
	HP->frames.mainOut.data.presionVaccum = 0.0;				
}

void HPcryoInitFrameCfgData( tHPcryoData *HP)
{
	uint8 cnt;
	
	/* Valores iniciales para la trama CFG IN. Son la copia de los valores de la CFG OUT.
	 * Para esto, se asume que la estructura OUT ya esta correctamente rellenada. */
	for( cnt = 0; cnt < HP_CRYO_REMAP_FRAME_CONFIG_IN_SIZE + 1; cnt++)
	{
		HP->frames.cfgIn.vector[cnt] = HP->frames.cfgOut.vector[cnt];
	}
	
	/* Asignamos los valores que queremos configurar */
	HP->frames.cfgIn.data.block_size = sizeof( tHPcryoRemapFrameCONFIG_IN_OUT);
	HP->frames.cfgIn.data.u8BloqueHabilitado = 1;	
	HPcryoSetTriggerONcfg( 1, 800, HP);
	HPcryoSetTriggerOFFcfg( 2, 300, HP);
}

void HPcryoInitFrameDbgData( tHPcryoData *HP)
{
	uint8 cnt;
	
	/* Valores para la trama DBG IN */
	HP->frames.dbgIn.data.block_size = sizeof( tHPcryoRemapFrameDEBUG_IN);
	HP->frames.dbgIn.data.u8BloqueHabilitado = 1;
	
	/* Valores por defecto para la trama DBG OUT */
	HP->frames.dbgOut.data.block_size = sizeof( tHPcryoRemapFrameDEBUG_OUT);
	for( cnt = 0; cnt < 9; cnt++){ HP->frames.dbgOut.data.MedidasTemperatura[cnt] = 0.0;}
	for( cnt = 0; cnt < 3; cnt++){ HP->frames.dbgOut.data.Calibraciones[cnt] = 0.0;}
	HP->frames.dbgOut.data.puertoSPI.u32TramasKO = 0;
	HP->frames.dbgOut.data.puertoSPI.u32TramasOK = 0;
	HP->frames.dbgOut.data.temp_interna = 0.0;
	HP->frames.dbgOut.data.vdda = 0.0;
	HP->frames.dbgOut.data.NivelPlica = 0.0;
}

void HPcryoInitFramePIDdata( tHPcryoData *HP)
{
	/* Esta trama no se utiliza */
}

/* Comandos para gestionar la memoria Flash del aplicador */
returnstatus_t HPcryoInitFrameFlashMemoryData( tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
	
//	HP->frames.Flash_In.data.BloqueHabilitado = 1;
//	HP->frames.Flash_In.data.action.u8Actions = 0;
//	ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer,
//								HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_SIZE/*64*/,
//								&( HP->frames.Flash_In.vector[1]));
////	ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer + 64,
////								7,
////								&( HP->frames.Flash_In.vector[1+64]));
//	HPcryoSetRemap( HO_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_INDEX, PRF);
//	HPcryoSetRemap( HO_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_INDEX, PRF);
	
	return ret;
}

void HPcryoCloseFrameFlashMemoryData( tHPcryoData *HP, tPRFdata *PRF)
{
	HPcryoClearRemap( HO_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_INDEX, PRF);
	HPcryoClearRemap( HO_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_INDEX, PRF);
}

returnstatus_t HPcryoEraseFlashMemory ( uint32 addr, uint8 num_sectors, tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
//	for(;num_sectors>0;num_sectors--)
//	{
//		/* Actualizamos la estructura de entrada */
//		/* reset de comandos */
//		HP->frames.Flash_In.data.action.bit_field.clear_flags = 0;
//		HP->frames.Flash_In.data.action.bit_field.erase = 0;
//		HP->frames.Flash_In.data.action.bit_field.write = 0;
//		HP->frames.Flash_In.data.action.bit_field.read = 0;
//		/* reset de comandos */
//		HP->frames.Flash_In.data.num_bytes = 1;
//		HP->frames.Flash_In.data.addr = addr;
//		ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer + 2,
//								5,	/* Tamaño dle num_bytes y del addr */
//								&( HP->frames.Flash_In.vector[1+2]));
		
//		if(ret==ERROR){break;}
		
//		/* Enviamos el comando */
//		HP->frames.Flash_In.data.action.bit_field.erase = 1;
//		ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer + 1,
//										1,	/* tamaño del action */
//										&( HP->frames.Flash_In.vector[1+1]));

//		if(ret==ERROR){break;}
//		do
//		{
//			ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_DIR + PRF->myDirInRemapFramesBuffer + 1,
//										1,	/* tamaño del action */
//										&( HP->frames.Flash_Out.vector[1+1]));
//		}while((HP->frames.Flash_Out.data.status.bit_field.op_in_progress == 1)||(HP->frames.Flash_Out.data.status.bit_field.erase_completed == 0));
		
//		if(ret==ERROR){break;}

//		HP->frames.Flash_In.data.action.bit_field.clear_flags = 1;
//		ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer + 1,
//										1,	/* tamaño del action */
//										&( HP->frames.Flash_In.vector[1+1]));
		
//		addr += HP_CRYO_EXTERNAL_FLASH_MEMORY_SECTOR_SIZE;
		
//	}
	return ret;
}

returnstatus_t HPcryoWriteFlashMemory ( uint32 addr, uint8 nBytes, uint8 *buffer, tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
	uint8 NumOpWriteReq;
	uint8 i,j;	/* variable auxiliar para recorrer bucle */
	
//	NumOpWriteReq = nBytes/64;	/* obtenemos el numero de veces que se va a tener que llamar al comando escribir */
	
//	for(i=0;i<=NumOpWriteReq;i++)
//	{
//		/* Actualizamos la estructura de entrada */
//		/* reset de comandos */
//		HP->frames.Flash_In.data.action.bit_field.clear_flags = 0;
//		HP->frames.Flash_In.data.action.bit_field.erase = 0;
//		HP->frames.Flash_In.data.action.bit_field.write = 0;
//		HP->frames.Flash_In.data.action.bit_field.read = 0;
//		/* reset de comandos */
//		HP->frames.Flash_In.data.addr = addr + (i*64);
//		if(i<NumOpWriteReq){	HP->frames.Flash_In.data.num_bytes = 64;	}	/* Si se va a completar el buffer completo */
//		else{	HP->frames.Flash_In.data.num_bytes = (nBytes - (i*64));	}		/* Si los bytes no completan el buffer */
//		if(HP->frames.Flash_In.data.num_bytes == 0){	break;	}
//		for(j=0;j<HP->frames.Flash_In.data.num_bytes;j++)
//		{
//			HP->frames.Flash_In.data.ptu8data[j] = buffer[j+i*64];
//		}
//		ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer + 2,
//									HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_SIZE,	/* Tamaño del num_bytes, addr y buffer */
//									&( HP->frames.Flash_In.vector[1+2]));
		
//		if(ret==ERROR){break;}
		
//		/* Enviamos el comando */
//		HP->frames.Flash_In.data.action.bit_field.write = 1;
//		ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer + 1,
//										1,	/* tamaño del action */
//										&( HP->frames.Flash_In.vector[1+1]));

//		if(ret==ERROR){break;}
//		do
//		{
//			ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_DIR + PRF->myDirInRemapFramesBuffer + 1,
//										1,	/* tamaño del action */
//										&( HP->frames.Flash_Out.vector[1+1]));
//		}while((HP->frames.Flash_Out.data.status.bit_field.op_in_progress == 1)||(HP->frames.Flash_Out.data.status.bit_field.write_completed == 0));
		
//		if(ret==ERROR){break;}

//		HP->frames.Flash_In.data.action.bit_field.clear_flags = 1;
//		ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer + 1,
//										1,	/* tamaño del action */
//										&( HP->frames.Flash_In.vector[1+1]));
//	}
	return ret;
}

returnstatus_t HPcryoReadFlashMemory ( uint32 addr, uint8 nBytes, uint8 *buffer, tHPcryoData *HP, tPRFdata *PRF)
{
	returnstatus_t ret;
	uint8 NumOpReadReq;
	uint8 i,j;	/* variable auxiliar para recorrer bucle */
	
//	NumOpReadReq = nBytes/64;	/* obtenemos el numero de veces que se va a tener que llamar al comando de lectura */
	
//	for(i=0;i<=NumOpReadReq;i++)
//	{
//		/* Actualizamos la estructura de entrada */
//		/* reset de comandos */
//		HP->frames.Flash_In.data.action.bit_field.clear_flags = 0;
//		HP->frames.Flash_In.data.action.bit_field.erase = 0;
//		HP->frames.Flash_In.data.action.bit_field.write = 0;
//		HP->frames.Flash_In.data.action.bit_field.read = 0;
//		/* reset de comandos */
//		HP->frames.Flash_In.data.addr = addr + (i*64);
//		if(i<NumOpReadReq){	HP->frames.Flash_In.data.num_bytes = 64;	}	/* Si se va a completar el buffer completo */
//		else{	HP->frames.Flash_In.data.num_bytes = (nBytes - (i*64));	}	/* Si los bytes no completan el buffer */
//		if(HP->frames.Flash_In.data.num_bytes == 0){	break;	}
//		ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer,
//									/*64*/HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_SIZE,	/* Tamaño dle num_bytes, addr y buffer */
//									&( HP->frames.Flash_In.vector[1]));
		
//		if(ret==ERROR){break;}
		
//		/* Enviamos el comando */
//		HP->frames.Flash_In.data.action.bit_field.read = 1;
//		ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer + 1,
//									1,	/* tamaño del action */
//										&( HP->frames.Flash_In.vector[1+1]));

//		if(ret==ERROR){break;}
//		do
//		{
//			ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_DIR + PRF->myDirInRemapFramesBuffer + 1,
//										1,	/* tamaño del action */
//										&( HP->frames.Flash_Out.vector[1+1]));
//		}while((HP->frames.Flash_Out.data.status.bit_field.op_in_progress == 1)||(HP->frames.Flash_Out.data.status.bit_field.read_completed == 0));
		
//		if(ret==ERROR){break;}
		
//		ret = EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//									7 + HP->frames.Flash_In.data.num_bytes,	/* tamaño del action */
//									&( HP->frames.Flash_Out.vector[1]));
		
//		if(ret==ERROR){break;}
		
//		for(j=0;j<HP->frames.Flash_Out.data.num_bytes;j++)
//		{
//			buffer[j+i*64] = HP->frames.Flash_Out.data.ptu8data[j];
//		}

//		HP->frames.Flash_In.data.action.bit_field.clear_flags = 1;
//		ret = EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + PRF->myDirInRemapFramesBuffer + 1,
//										1,	/* tamaño del action */
//										&( HP->frames.Flash_In.vector[1+1]));
//	}
	
	return ret;
}
/* Comandos para gestionar la memoria Flash del aplicador */


returnstatus_t HPcryoSetRemap( cHPcryoRemapFrameIndexes index, tPRFdata *PRF)
{
	returnstatus_t ret;
//	tEXPremap remap;
	
//	/* Generamos los datos de la estructura remap */
//	remap.fields.id[0] = HP_CRYO_REMAP_FRAME_ID[index][0];
//	remap.fields.id[1] = HP_CRYO_REMAP_FRAME_ID[index][1];
//	remap.fields.id[2] = HP_CRYO_REMAP_FRAME_ID[index][2];
//	remap.fields.id[3] = HP_CRYO_REMAP_FRAME_ID[index][3];
//	remap.fields.dirRelToBuff = HP_CRYO_REMAP_FRAME_DATA[index][0] + PRF->myDirInRemapFramesBuffer;
//	remap.fields.nBytes = HP_CRYO_REMAP_FRAME_DATA[index][1];
	
//	/* Enviamos el remap */
//	ret = EXPsendRemap( &remap, PRF->IDperifHW, HP_CRYO_REMAP_FRAME_DATA[index][2],
//						HP_CRYO_REMAP_FRAME_DATA[index][3]);
	
	/* Devolvemos el resultado */
	return ret;
	
}

returnstatus_t HPcryoClearRemap( cHPcryoRemapFrameIndexes index, tPRFdata *PRF)
{
	returnstatus_t ret;
//	tEXPremap remap;
		
//	/* Generamos los datos de la estructura remap para inhabilitarla. Ponemos un ID inválido y 0 en
//	 * el número de bytes a enviar */
//	remap.fields.id[0] = 'N';
//	remap.fields.id[1] = 'U';
//	remap.fields.id[2] = 'L';
//	remap.fields.id[3] = 1;
//	remap.fields.dirRelToBuff = HP_CRYO_REMAP_FRAME_DATA[index][0] + PRF->myDirInRemapFramesBuffer;
//	remap.fields.nBytes = 0;
		
//	/* Enviamos el remap */
//	ret = EXPsendRemap( &remap, PRF->IDperifHW, HP_CRYO_REMAP_FRAME_DATA[index][2],
//						HP_CRYO_REMAP_FRAME_DATA[index][3]);
		
	/* Devolvemos el resultado */
	return ret;
}

returnstatus_t HPcryoRefreshRemapPack( tPRFdata *PRF)
{
	returnstatus_t ret;
	
	ret = HPcryoSetRemap( HP_CRYO_REMAP_FRAME_MAIN_IN_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoSetRemap( HP_CRYO_REMAP_FRAME_MAIN_OUT_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoSetRemap( HP_CRYO_REMAP_FRAME_CFG_IN_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoSetRemap( HP_CRYO_REMAP_FRAME_CFG_OUT_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoSetRemap( HP_CRYO_REMAP_FRAME_DBG_IN_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoSetRemap( HP_CRYO_REMAP_FRAME_DBG_OUT_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	return SUCCESS;
}

returnstatus_t HPcryoClearRemapPack( tPRFdata *PRF)
{
	returnstatus_t ret;
		
	ret = HPcryoClearRemap( HP_CRYO_REMAP_FRAME_MAIN_IN_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoClearRemap( HP_CRYO_REMAP_FRAME_MAIN_OUT_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoClearRemap( HP_CRYO_REMAP_FRAME_CFG_IN_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoClearRemap( HP_CRYO_REMAP_FRAME_CFG_OUT_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoClearRemap( HP_CRYO_REMAP_FRAME_DBG_IN_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	ret = HPcryoClearRemap( HP_CRYO_REMAP_FRAME_DBG_OUT_INDEX, PRF);
	if( ret == ERROR){ return ret;}
	return SUCCESS;
}
//PDTE FALLO DE F.A. LOCA
void HPcryoCtrlTempSensorValues( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 cnt;
	//float max, min;
	uint16 HPindex = HPcryoGetSlot( HP, PRF) - 1;
	uint8 group, sns, sns_comp, err_group;
	uint8 sensor_num;
	cHPcryoModels model;
	/* V7778 - TEMP SEC */
	static float HPprevSNSmeasured[HPCRYO_MAX_N_PERIFS][HP_CRYO_MAX_TEMP_SNS];	//Matriz de temperaturas anteriores por aplicador
	uint8 calib_limit;															//Limite de valor calibración en funcion de cto medida
	/* V7778 - TEMP SEC */
	/*V7780*/
	static uint8 HPapplyDeltaErrFlag[HPCRYO_MAX_N_PERIFS];
	static uint32 HPapplyDeltaErrTimeRefFlag[HPCRYO_MAX_N_PERIFS];
	uint8 Delta_Err_Launched_FLag = 0;
	uint8 Max_Temp_Err_Launched_FLag = 0;
	/*V7780*/

//	/* Comprobaciones */
//	/* - Valor mínimo */
//	model = HPcryoGetModel(HP,PRF);
	
//	cnt = 0;
//	if((EXP_UCerrSecureStatus())&&(!HP->trt.TrtParameters.DemoTRT))		/* V7780 */ /* V7787 */
//	{
//		while( cnt < HP_CRYO_MAX_TEMP_SNS &&
//			 ( HP->frames.dbgOut.data.MedidasTemperatura[cnt] > HP_CRYO_CTRL_SECURE_MIN_SNS_TEMP_LIST_VALUE[model] ||
//			   HP->frames.dbgOut.data.MedidasTemperatura[cnt] == HP_CRYO_CTRL_SNS_TEMP_FAIL_VALUE))
//		{ cnt++;}
//	}
//	else
//	{
//		while( cnt < HP_CRYO_MAX_TEMP_SNS &&
//			 ( HP->frames.dbgOut.data.MedidasTemperatura[cnt] > HP_CRYO_CTRL_MIN_SNS_TEMP_LIST_VALUE[model] ||
//			   HP->frames.dbgOut.data.MedidasTemperatura[cnt] == HP_CRYO_CTRL_SNS_TEMP_FAIL_VALUE))
//		{ cnt++;}
//	}
	
//	/* -- Comprobamos el resultado de la busqueda */
//	if( cnt < HP_CRYO_MAX_TEMP_SNS)
//	{
//		/* Alguna sonda esta por debajo del mínimo */
//		HPcryoCtrlWhenError( &( HP->ctrl.minTempTimeOut), HP_CRYO_CTRL_MIN_SNS_TEMP_TIME,
//							 Error_HPctrlMinTemp1 + HPindex);
//	}
//	else
//	{
//		/* Todas las sondas OK */
//		ERR_delete( Error_HPctrlMinTemp1 + HPindex);
//		HP->ctrl.minTempTimeOut = 0;
//	}
	
//	/* - Error de segunda ventana de frío - */
//	model = HPcryoGetModel(HP,PRF);
	
//	for( cnt = 1; cnt < HP_CRYO_MAX_TEMP_SNS; cnt++)
//	{
//		if((EXP_UCerrSecureStatus())&&(!HP->trt.TrtParameters.DemoTRT))		/* V7780 */ /* V7787 */
//		{
//			if(HP->frames.dbgOut.data.MedidasTemperatura[cnt]<(HP_CRYO_CTRL_SECOND_SECURE_WINDOW_LOW_TEMP))
//			{
//				ERR_add( Error_HPsecondWindowLowTemp1 + HPindex);
//			}
//		}
//		else
//		{
//			if(HP->frames.dbgOut.data.MedidasTemperatura[cnt]<(HP_CRYO_CTRL_SECOND_WINDOW_LOW_TEMP))
//			{
//				ERR_add( Error_HPsecondWindowLowTemp1 + HPindex);
//			}
//		}
//	}
	
//	/* - Valor máximo */
//	err_group = 0;
//	cnt = 0;
	
//	if((EXP_UCerrSecureStatus())&&(!HP->trt.TrtParameters.DemoTRT))		/*V7780*/
//	{
//		for( sns = 0; sns < HP_CRYO_MAX_TEMP_SNS; sns++)		/*Recorremos todas las sondas del grupo*/
//		{
//			if(HP->frames.dbgOut.data.MedidasTemperatura[sns] < HP_CRYO_CTRL_SNS_TEMP_FAIL_VALUE)
//			{
//				if((HP->frames.dbgOut.data.MedidasTemperatura[sns] > HP_CRYO_CTRL_MAX_SNS_TEMP_VALUE))
//				{
//					/* Un sonda da mide más del máximo */
//					HPcryoCtrlWhenError( &( HP->ctrl.maxTempTimeOut), HP_CRYO_CTRL_MAX_SNS_TEMP_TIME, Error_HPctrlMaxTemp1 + HPindex);
//					Delta_Err_Launched_FLag = 1;
//				}
//			}
//		}
//		if(!Delta_Err_Launched_FLag)
//		{
//			/* Todas las sondas OK */
//			ERR_delete( Error_HPctrlMaxTemp1 + HPindex);
//			HP->ctrl.maxTempTimeOut = 0;
//		}
//	}
//	else
//	{
//		for(group = 0; group<HP_CRYO_MAX_GRUPOS_DE_SONDAS; group++)		/*Recorremos todos los grupos de sondas*/
//		{
//			for( sns = 0; sns < HP_CRYO_MAX_SONDAS_GRUPO; sns++)		/*Recorremos todas las sondas del grupo*/
//			{
//				sensor_num = HP_CRYO_SENSOR_GROUPS [HPcryoGetModel(HP,PRF)][group][sns];
				
//				if(sensor_num!=0)		/*Repasamos que exista esa sonda en el grupo*/
//				{
//					if((HP->frames.dbgOut.data.MedidasTemperatura[sensor_num-1] > HP_CRYO_CTRL_MAX_SNS_TEMP_VALUE) && (HP->frames.dbgOut.data.MedidasTemperatura[sensor_num-1] < HP_CRYO_CTRL_SNS_TEMP_FAIL_VALUE))
//					{
//						cnt++;
//					}
//				}
//			}
//			if(cnt>(HP_CRYO_MAX_SNS_KO_PER_GROUP[HPcryoGetModel(HP,PRF)])){	err_group++;	}
//			cnt = 0;
//		}
//		if(err_group>0)		/*Si al final de comprobar todos los grupos la vble acumuladora es superior a 0 lanzamos el error*/
//		{
//			/* Algun grupo de sondas estan por encima del máximo */
//			HPcryoCtrlWhenError( &( HP->ctrl.maxTempTimeOut), HP_CRYO_CTRL_MAX_SNS_TEMP_TIME,
//								 Error_HPctrlMaxTemp1 + HPindex);
//		}
//		else
//		{
//			/* Todas las sondas OK */
//			ERR_delete( Error_HPctrlMaxTemp1 + HPindex);
//			HP->ctrl.maxTempTimeOut = 0;
//		}
//	}
	
////	/* - Valor máximo */
////	cnt = 0;
////	while( cnt < HP_CRYO_MAX_TEMP_SNS &&
////		 ( HP->frames.dbgOut.data.MedidasTemperatura[cnt] < HP_CRYO_CTRL_MAX_SNS_TEMP_VALUE ||
////		   HP->frames.dbgOut.data.MedidasTemperatura[cnt] >= HP_CRYO_CTRL_SNS_TEMP_FAIL_VALUE))	//además de tener en cuenta el valor 100 se añade el ">" para contemplar también el valor 200 (Albert)
////	{ cnt++;}
////
////	/* -- Comprobamos el resultado de la busqueda */
////	if( cnt < HP_CRYO_MAX_TEMP_SNS)
////	{
////		/* Alguna sonda esta por encima del máximo */
////		HPcryoCtrlWhenError( &( HP->ctrl.maxTempTimeOut), HP_CRYO_CTRL_MAX_SNS_TEMP_TIME,
////							 Error_HPctrlMaxTemp1 + HPindex);
////	}
////	else
////	{
////		/* Todas las sondas OK */
////		ERR_delete( Error_HPctrlMaxTemp1 + HPindex);
////		HP->ctrl.maxTempTimeOut = 0;
////	}
	

//	/* - Cambios en el valor */
//	cnt = 0;
//	while( cnt < HP_CRYO_MAX_TEMP_SNS &&
//		   HP->frames.dbgOut.data.MedidasTemperatura[cnt] == HP->ctrl.difTempLastSnsValue[cnt])
//	{ cnt++;}
	
//	/* -- Comprobamos resultado de la busqueda */
//	if( cnt >=  HP_CRYO_MAX_TEMP_SNS)
//	{
//		/* Todas las sondas han conservado el valor */
//		HPcryoCtrlWhenError( &( HP->ctrl.difTempTimeOut), HP_CRYO_CTRL_DIF_SNS_TEMP_TIME,
//							 Error_HPctrlDifTempFreeze1 + HPindex);
//	}
//	else
//	{
//		/* Alguna sonda ha cambiado de valor, es OK */
//		ERR_delete( Error_HPctrlDifTempFreeze1 + HPindex);
//		HP->ctrl.difTempTimeOut = 0;
//	}
	
//	/* -- Copiamos los valores para la siguiente llamada */
//	for( cnt = 0; cnt < HP_CRYO_MAX_TEMP_SNS; cnt++)
//	{
//		HP->ctrl.difTempLastSnsValue[cnt] = HP->frames.dbgOut.data.MedidasTemperatura[cnt];
//	}
	
//	/* - Diferencia máxima entre sondas */
//	if((EXP_UCerrSecureStatus()) && (EXP_UCerrDeltaTempSecureStatus()) && (!HP->trt.TrtParameters.DemoTRT))		/*V7780*//* V7787 */
//	{
//		if((HP->trt.set_temp_reached) &&
//		   (HPcryo_get_temp_slope(HP, PRF) < HP_CRYO_SLOPE_LIMIT_TO_APPLY_DELTA_ERR) &&
//		   (TICKS_DiffTicks(HPapplyDeltaErrTimeRefFlag[HPindex])>HP_CRYO_TIME_REF_TO_APPLY_DELTA_ERR))
//		{
//			HPapplyDeltaErrFlag[HPindex] = 1;
//		}
		
//		if(HP->status != HP_CRYO_TREATMENT)
//		{
//			HPapplyDeltaErrFlag[HPindex] = 0;
//			HPapplyDeltaErrTimeRefFlag[HPindex] = TICKS_GetTicks();
//		}
		
//		if(HPapplyDeltaErrFlag[HPindex])
//		{
//			for( sns = 0; sns < HP_CRYO_MAX_TEMP_SNS; sns++)		/*Recorremos todas las sondas del grupo*/
//			{
//				for( sns_comp = 0; sns_comp < HP_CRYO_MAX_TEMP_SNS; sns_comp++)		/*Recorremos el resto de sondas para hacer la comparativa*/
//				{
//					if((HP->frames.dbgOut.data.MedidasTemperatura[sns] < HP_CRYO_CTRL_SNS_TEMP_FAIL_VALUE) &&
//					   (HP->frames.dbgOut.data.MedidasTemperatura[sns_comp] < HP_CRYO_CTRL_SNS_TEMP_FAIL_VALUE))
//					{
//						if(abs((HP->frames.dbgOut.data.MedidasTemperatura[sns] - HP->frames.dbgOut.data.MedidasTemperatura[sns_comp])) > HP_CRYO_CTRL_SECURE_DELTA_MAX_SNS_TEMP_LIST_VALUE[model]) 		/*Evaluamos la temperatura, si supera o no el delta*/
//						{
//							/* Delta mayor que el permitido */
//							HPcryoCtrlWhenError( &( HP->ctrl.deltaTempTimeOut), HP_CRYO_CTRL_DELTA_MAX_SNS_TEMP_TIME, Error_HPctrlDeltaTempMax1 + HPindex);
//							Max_Temp_Err_Launched_FLag = 1;
//						}
//					}
//				}
//			}
//			if(!Max_Temp_Err_Launched_FLag)
//			{
//				/* Delta correcto */
//				ERR_delete( Error_HPctrlDeltaTempMax1 + HPindex);
//				HP->ctrl.deltaTempTimeOut = 0;
//			}
//		}
//	}
//	else
//	{
//		err_group = 0;		/*Reseteamos la variable de control de errores por grupo*/
//		cnt=0;
		
//		for(group = 0; group<HP_CRYO_MAX_GRUPOS_DE_SONDAS; group++)		/*Recorremos todos los grupos de sondas*/
//		{
//			HP->SnsGroupKO[group] = 0;
			
//			for( sns = 0; sns < HP_CRYO_MAX_SONDAS_GRUPO; sns++)		/*Recorremos todas las sondas del grupo*/
//			{
//				if((HP_CRYO_SENSOR_GROUPS [model][group][sns])!=0)		/*Repasamos que exista esa sonda en el grupo*/
//				{
//					for( sns_comp = 0; sns_comp < HP_CRYO_MAX_TEMP_SNS; sns_comp++)		/*Recorremos el resto de sondas para hacer la comparativa*/
//					{
//						if(abs((HP->frames.dbgOut.data.MedidasTemperatura[(HP_CRYO_SENSOR_GROUPS [model][group][sns])-1] - HP->frames.dbgOut.data.MedidasTemperatura[sns_comp])) > HP_CRYO_CTRL_DELTA_MAX_SNS_TEMP_LIST_VALUE[model])	/*Evaluamos la temperatura, si supera o no el delta*/
//						{
//							if(HP->frames.dbgOut.data.MedidasTemperatura[(HP_CRYO_SENSOR_GROUPS [model][group][sns])-1] > HP->frames.dbgOut.data.MedidasTemperatura[sns_comp]){	cnt++;}		/*Se comprueba si la que está fallando es la evaluada o la otra, e incrementamos el contador*/
//						}
//					}
//					if(cnt>0){	HP->SnsGroupKO[group]++; cnt=0;	}		/*Si ha saltado que la sonda da error se acumula*/
//				}
//			}
//			if(HP->SnsGroupKO[group] > HP_CRYO_MAX_SNS_KO_PER_GROUP[HPcryoGetModel(HP,PRF)]){	err_group++;	}		/*Si el grupo da error lo guardamos en una vble acumuladora*/
//		}
//		if(err_group>0)		/*Si al final de comprobar todos los grupos la vble acumuladora es superior a 0 lanzamos el error*/
//		{
//			/* Delta mayor que el permitido */
//			HPcryoCtrlWhenError( &( HP->ctrl.deltaTempTimeOut), HP_CRYO_CTRL_DELTA_MAX_SNS_TEMP_TIME,
//								 Error_HPctrlDeltaTempMax1 + HPindex);
//		}
//		else
//		{
//			/* Delta correcto */
//			ERR_delete( Error_HPctrlDeltaTempMax1 + HPindex);
//			HP->ctrl.deltaTempTimeOut = 0;
//		}
//	}

//	/* V7778 - TEMP SEC */
	
//	for( cnt = 1; cnt < HP_CRYO_MAX_TEMP_SNS; cnt++)	//Recorremos todas las sondas de temperatura
//	{
//		if(HP->PrevStatusSAT)		/* V7787 - Mientras se está en la pantalla de SAT no se van registrando temperaturas, en caso de venir de SAT registrar antes de evaluar el error */
//		{
//			HPprevSNSmeasured[HPindex][cnt] = HP->frames.dbgOut.data.MedidasTemperatura[cnt];
//		}
//		if(HP->status != HP_CRYO_TEST_INIT)				//Solo aplicamos la evaluacion del error si estamos fuera del init
//		{
//			if((HP->frames.dbgOut.data.MedidasTemperatura[cnt] < (HPprevSNSmeasured[HPindex][cnt] - 3)) ||	//Si los nuevos valores de temperatura salem de rango, ERROR
//			  (HP->frames.dbgOut.data.MedidasTemperatura[cnt] > (HPprevSNSmeasured[HPindex][cnt] + 3)))
//			{
//				ERR_add( Error_HPsondaStep1 + HPindex);
//			}
//		}
//		HPprevSNSmeasured[HPindex][cnt] = HP->frames.dbgOut.data.MedidasTemperatura[cnt];		//Se actualizan los valores de temperatura registrados
//	}
//	if(HP->PrevStatusSAT)
//	{
//		HP->PrevStatusSAT = 0;	/* V7787 - Un vez se ha registrado tras venir de SAT, no volver a registrar hasta darse de nuevo el caso */
//	}
	
	
//	if((EXP_UCerrSecureStatus()) && (!HP->trt.TrtParameters.DemoTRT))		/*V7780*/ /* V7787 */
//	{
//		calib_limit = HP_CRYO_CALIB_SECURE_LIMIT;		/*Sin metodo seguro restrictivo (+-20)*/
//	}
//	else
//	{
//		//if(HP->frames.dbgOut.data.circuito_utilizado != 0)		//Ajustamos los valores limite de la calibración en funciópn del circuito de medida
//		//{
//			calib_limit = HP_CRYO_CALIB_LIMIT_NTC;				/*Con metodo seguro restrictivo (+-50)*/
//		//}
//		//else{	calib_limit = HP_CRYO_CALIB_LIMIT_PT1000;	}
//	}
	
//	if(HP->status != HP_CRYO_TEST_INIT)
//	{
//		if((model == HP_CRYO_MODEL_TINY) || (model == HP_CRYO_MODEL_TINY_CURVED))	//Si el modelo del aplicador es Tiny o Tiny Curved solo se mira una calibración
//		{
//			if((HP->frames.dbgOut.data.Calibraciones[0] > calib_limit) || (HP->frames.dbgOut.data.Calibraciones[0] < (-1*calib_limit)))	//Se evalua si alguna calibración está fuera de rango
//			{
//				ERR_add( Error_HPcalibOutRange1 + HPindex);		//En tal caso, salta el error
//			}
//		}
//		else
//		{
//			if((HP->frames.dbgOut.data.Calibraciones[0] > calib_limit) || (HP->frames.dbgOut.data.Calibraciones[0] < (-1*calib_limit)) ||	//Se evalua si alguna calibración está fuera de rango
//			   (HP->frames.dbgOut.data.Calibraciones[1] > calib_limit) || (HP->frames.dbgOut.data.Calibraciones[1] < (-1*calib_limit)) ||
//			   (HP->frames.dbgOut.data.Calibraciones[2] > calib_limit) || (HP->frames.dbgOut.data.Calibraciones[2] < (-1*calib_limit)) )
//			{
//				ERR_add( Error_HPcalibOutRange1 + HPindex);		//En tal caso, salta el error
//			}
//		}
//	}
//	/* V7778 - TEMP SEC */
	
//	/* V7780 */
//	/*Error que detecta sondas rotas*/
//	if((EXP_UCerrSecureStatus()) && (!HP->trt.TrtParameters.DemoTRT))	/* V7787 */
//	{
//		for( sns = 0; sns < HP_CRYO_MAX_TEMP_SNS; sns++)		/*V7790 BUG (miraba solo 4 sondas) Recorremos todas las sondas del grupo*/
//		{
//			sensor_num = HP_CRYO_ALL_SENSOR [model][sns];
	
//			if(sensor_num!=0)
//			{
//				if(HP->frames.dbgOut.data.MedidasTemperatura[sensor_num - 1] >= HP_CRYO_CTRL_SNS_TEMP_FAIL_VALUE)		/*V7790 BUG -> ">=" */
//				{
//					ERR_add( Error_HPsondaRotaHP1 + HPindex);		//En tal caso, salta el error
//				}
//			}
//		}
//	}
	/* V7780 */
}

void HPcryoCtrlWhenError( uint32 *tout, uint32 errTime, uint16 errCode)
{
//	/* Lanzamos el timer si esta parado, si no lo esta comprobamos si ya ha alcanzado el tiempo de error */
//	if( ( *tout) == 0)
//	{ ( *tout) = TICKS_GetTicks();}
//	else
//	{
//		if( TICKS_DiffTicks( ( *tout)) > errTime)
//		{
//			ERR_add(errCode);
//			( *tout) = 0;
//		}
//	}
}
//PDTE
void HPcryoCtrlTempSensorCalibration( tHPcryoData *HP, tPRFdata *PRF)
{
	//ERRadd(cal)???
}

void HPcryoCtrlManStatus( tHPcryoData *HP, tPRFdata *PRF)
{
	tHPcryoWarnings warn;
	uint8 offset;
	
//	warn.u16Avisos = HP->frames.mainOut.data.avisos.u16Avisos;
	
//	/* Calculamos el offset para el codigo de error */
//	offset = HPcryoGetSlot( HP, PRF) - 1;
	
//	/* Comprobamos si el manipulo esta en alarma */
//	if( HP->frames.mainOut.data.estado == HP_CRYO_MAN_ALARM)
//	{
//		/* El HP esta en ALARM, esto puede ser debido a el pulsador de emergencia "SETA" o
//		 * a que ha fallado el test de inicio "TEST_INIT". No es necesario distinguir */
//		if(/*(BusAlarm_SETA_flagOn() != Error_BusAlarma_Seta)*/!BusAlarm_IsAlarmOn() && !warn.bit_field.test_sondas_fallido)
//		{
//			ERR_add( Error_HPstatusAlarma1 + offset);
//		}
//	}
//	else{ ERR_delete( Error_HPstatusAlarma1 + offset);}
	
//	/* Comprobamos si el manipulo esta desconfigurado. Esto solo puede pasar al principio
//	 * y no podremos sacar el HP de este estado */
//	if( HP->frames.mainOut.data.estado == HP_CRYO_MAN_DESCONFIGURADO)
//	{ ERR_add( Error_HPstatusDescfg1 + offset);}
//	else{ ERR_delete( Error_HPstatusDescfg1 + offset);}
	
//	/* Error de fallo de comunicaciones con complementos necesarios por el HP */
//	/*if( HP->frames.mainOut.data.estado == HP_CRYO_MAN_MANIPULO_DESHAB_ERROR_COMS)
//	{ ERR_add( Error_HPstatusDeshab485com1 + offset);}
//	else{ ERR_delete( Error_HPstatusDeshab485com1 + offset);}*/
}

void HPcryoCtrlTempConvEq( tHPcryoData *HP, tPRFdata *PRF)
{
	//PDTE
}

void HPcryoCtrlAlarmFlags( tHPcryoData *HP, tPRFdata *PRF)
{
	tHPcryoWarnings warn;
	tHPcryoProtections prot;
	uint8 offset;
		
//	/* Calculamos el offset para el codigo de error */
//	offset = HPcryoGetSlot( HP, PRF) - 1;
		
//	/* Asignamos el word de flags */
//	warn.u16Avisos = HP->frames.mainOut.data.avisos.u16Avisos;
//	prot.u16Warnings = HP->frames.dbgOut.data.warnings.u16Warnings;
	
//	/* Fallo por timeout del tiempo de tratamiento programado */
//	//flags.bit_field.timeout; Err_TimeOutMan1
	
//	/* Fallo de tiempo de espera para alcanzar el vacum de consigna */
//	if( warn.bit_field.espera_vac)
//	{ 	if(!HP->warningFlags.espera_vac){ERR_add( Err_TimeOutVacm1 + offset);}
//		HP->warningFlags.espera_vac = 1;	}
//	else{ ERR_delete( Err_TimeOutVacm1 + offset); HP->warningFlags.espera_vac = 0;}
	
//	/* Fallo de no alcanzar la presion de vacio necesaria */
//	if( warn.bit_field.vac)
//	{ 	if(!HP->warningFlags.vac_lvl){ERR_add( Err_TimeOutVacEstable1 + offset);}
//		HP->warningFlags.vac_lvl = 1;	}
//	else{ ERR_delete( Err_TimeOutVacEstable1 + offset); HP->warningFlags.vac_lvl = 0;}
	
//	/* Fallo al no tener la hidraulica activada o arrancada cuando se ha requerido */
//	if( warn.bit_field.hidraulica)
//	{ 	if(!HP->warningFlags.hidraulica){ERR_add( Err_HidraulicaMan1 + offset);}
//		HP->warningFlags.hidraulica = 1;	}
//	else{ ERR_delete( Err_HidraulicaMan1 + offset); HP->warningFlags.hidraulica = 0;}
	
//	/* Fallo al llegar el H2O demasiado caliente al HP */
//	if( warn.bit_field.temp_entrada)
//	{ 	if(!HP->warningFlags.temp_entrada){ERR_add( Err_TempEntradaAlta1 + offset);}
//		HP->warningFlags.temp_entrada = 1;	}
//	else{ ERR_delete( Err_TempEntradaAlta1 + offset); HP->warningFlags.temp_entrada = 0;}
	
//	/* Fallo de caudal de entrada al HP */
//	if( warn.bit_field.caudal_entrada)
//	{ 	if(!HP->warningFlags.caudal_entrada){ERR_add( Err_CaudalimetroMan1 + offset);}
//		HP->warningFlags.caudal_entrada = 1;	}
//	else{ ERR_delete( Err_CaudalimetroMan1 + offset); HP->warningFlags.caudal_entrada = 0;}
	
//	/* Fallo de timeout de espera para alcanzar la temperatura de consigna, llegar a la ventana */
//	if( warn.bit_field.espera_temp)
//	{ 	if(!HP->warningFlags.espera_temp){ERR_add( Err_ToutTempIniciTrart1 + offset);}
//		HP->warningFlags.espera_temp = 1;	}
//	else{ ERR_delete( Err_ToutTempIniciTrart1 + offset); HP->warningFlags.espera_temp = 0;}
	
//	/* Fallo al no mantener la temperatura dentro de la ventana/2 */
//	if( warn.bit_field.temperatura)
//	{
//		if(HPcryoManageTempMedError( HP, PRF))		/* Gestion del error para temperaturas altas */
//		{
//			if(!HP->warningFlags.temperatura_window)
//			{
//				ERR_add( Err_ToutTempFinalTrat1 + offset);
//			}
//			HP->warningFlags.temperatura_window = 1;
//		}
//	}
//	else{ ERR_delete( Err_ToutTempFinalTrat1 + offset); HP->warningFlags.temperatura_window = 0;}
	
//	/* Fallo al no tener sondas de temperatura suficientes para el control */
//	if( warn.bit_field.sonda_error)
//	{ 	if(!HP->warningFlags.sonda_error){ERR_add(  Err_NPltInsf1 + offset);}
//		HP->warningFlags.sonda_error = 1;	}
//	else{ ERR_delete( Err_NPltInsf1 + offset); HP->warningFlags.sonda_error = 0;}
	
//	/* Fallo al detectar alguna medida de temperatura por debajo de la minima */
//	if( warn.bit_field.seguridad_frio)
//	{ 	if(!HP->warningFlags.seguridad_frio){ERR_add( Err_SeguridadFrioMan1 + offset);}
//		HP->warningFlags.seguridad_frio = 1;	}
//	else{ ERR_delete( Err_SeguridadFrioMan1 + offset); HP->warningFlags.seguridad_frio = 0;}
	
//	/* Fallo al pararse un PID por la saturacion del calor que sobra */
//	//flags.bit_field.pid_off_calor; Err_PIDoff1
	
//	/* Fallo al no recibir tramas de MAIN en el HP */
//	if( warn.bit_field.sin_tramas_main)
//	{ 	if(!HP->warningFlags.sin_tramas_main){ERR_add( Err_HPsinTramasMain1 + offset);}
//		HP->warningFlags.sin_tramas_main = 1;	}
//	else{ ERR_delete( Err_HPsinTramasMain1 + offset); HP->warningFlags.sin_tramas_main = 0;}
	
//	/* Fallo al desconectarse el secundario del HP, tipicamente el DOUBLE */
//	//flags.bit_field.sin_tramas_secundario;
	
//	/* Fallo al no reconocer el circuito de sensado de temperaturas (NTC o PT1K) */
//	if( warn.bit_field.circuito_temp_desconocido)
//	{ 	if(!HP->warningFlags.circuito_temp_desconocido){ERR_add( Error_CircTempDesc1 + offset);}
//		HP->warningFlags.circuito_temp_desconocido = 1;	}
//	else{ ERR_delete( Error_CircTempDesc1 + offset); HP->warningFlags.circuito_temp_desconocido = 0;}
	
//	/* Fallo al no superar el test de las sondas inicial hecho durante la inicializacion */
//	if( warn.bit_field.test_sondas_fallido)
//	{ 	if(!HP->warningFlags.test_sondas_fallido){ERR_add( Error_TestSondasFallo1 + offset);}
//		HP->warningFlags.test_sondas_fallido = 1;	}
//	else if(Temp_SAFE_Frostbite(HP, PRF) > 0){}
//	else{ ERR_delete( Error_TestSondasFallo1 + offset); HP->warningFlags.test_sondas_fallido = 0;}
	
//	/* Fallo por quedarse las temepraturas clavadas */
//	if( prot.bit_field.temp_clavada)
//	{ 	if(!HP->warningFlags.temp_clavada){ERR_add( Error_HPprotFlagTempClavada1 + offset);}
//		HP->warningFlags.temp_clavada = 1;	}
//	else{ ERR_delete( Error_HPprotFlagTempClavada1 + offset); HP->warningFlags.temp_clavada = 0;}
	
//	//DEBUG
//#ifdef HP_CRYO_DBG_ERR_CODES
//	uint8 errMsg, wrnMsg;
//	uint32 errCode, wrnCode;
		
//	ERR_interface_msg( PRF->IDperifHW, &errCode, &errMsg, &wrnCode, &wrnMsg);
//	HP->frames.mainIn.data.u16dummy = (uint16)errCode;
//	ERR_interface_msg( Maq, &errCode, &errMsg, &wrnCode, &wrnMsg);
//	if( errCode != Error_ok){	HP->frames.mainIn.data.dummy = ( uint8)( errCode - ERROR_CODE_MACHINE_OFFSET);	}
//	else{	HP->frames.mainIn.data.dummy = Error_ok;	}
//#endif
//}

//void HPcryoCtrlVacumRetrys( tHPcryoData *HP, tPRFdata *PRF)
//{
//	/* Por defecto ponemos a 0 */
//	HP->trt.vacumRetryRqstUserToMoveHP = 0;
	
//	/* Comprobamos si el tratamiento esta en marcha mirando el tiempo */
//	if( HP->trt.startTime != 0)
//	{
//		/* Dependiendo de la ventana de tiempo en la que estemos */
//		if( TICKS_DiffTicks( HP->trt.startTime) <= HP_CRYO_TRT_VACUM_RETRY_FIRST_TIME)
//		{
//			/* Dentro de la primera ventana de tiempo, comprobamos si hemos pasado el numero máximo de resucciones */
//			if( EXP_UCgetVacumRetrys( HPcryoGetSlot( HP, PRF)) > HP_CRYO_MAX_VACUM_RETRYS_IN_FIRST_TIME)
//			{
//				/* Se han superado el numero máximo de reintentos en el primero intervalo de tiempo. Se avisa al
//				 * usuario para que recoloque el cabezal */
//				HP->trt.vacumRetryRqstUserToMoveHP = 1;
//			}
//		}
////		else if( TICKS_DiffTicks( HP->trt.startTime) <= (( HP->trt.trtTime_s / 2)*1000))
////		{
////			/* Dentro de la segunda ventana de tiempo, comprobamos si hemos pasado el numero máximo de resucciones */
////			if( EXP_UCgetVacumRetrys( HPcryoGetSlot( HP, PRF)) > HP_CRYO_MAX_VACUM_RETRYS_IN_SECOND_TIME)
////			{
////				/* Se han superado el numero máximo de reintentos en el segundo intervalo de tiempo. Activamos alarma */
////				ERR_add( Error_NResuccionesMAN1 + HPcryoGetSlot( HP, PRF) - 1);
////			}
////		}
//		else /*if( TICKS_DiffTicks( HP->trt.startTime) <= (HP->trt.trtTime_s*1000))*/
//		{
//			/* Dentro de la tercera ventana de tiempo, comprobamos si hemos pasado el numero máximo de resucciones */
//			if( EXP_UCgetVacumRetrys( HPcryoGetSlot( HP, PRF)) > HP_CRYO_MAX_VACUM_RETRYS_IN_THIRD_TIME)
//			{
//				/* Se han superado el numero máximo de reintentos en el tercer intervalo de tiempo. Cambiamos la
//				 * temperatura de consigna */
//				HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_VACUM_RETRY_THIRD_TIME_TEMP;
//				if(HP->trt.trt_secure_plus_three == 0)
//				{
//					HP->trt.trt_secure_plus_three_time_ref = TICKS_GetTicks();
//					HP->trt.trt_secure_plus_three = 1;
//				}
//			}
//		}
//	}
}

returnstatus_t HPCryoRFIDcheckLabel( uint8 *Label_Read_index, uint16 RFID_time_read, cHPcryoRFID_err *RFID_err_code, tHPcryoData *HP, tPRFdata *PRF)
{
    //static uint32 count2 = 0;	//DEBUG	-	Contabiliza veces que se sale del bucle de lectura RFID
	
    //Variables auxiliares
    uint8 i;
	
    //Variables estaticas
    static uint8 read_started = 0;									//Flag que indica que la lectura de una tarjeta ha comenzado
    static uint8 label = 0;											//Indice de la etiqueta
    static uint8 RFID_read_Default_label = 1; 						//Estado del proceso --> Leer etiqueta por defecto o Leer otra etiqueta
//    static char Label_requested[HP_CRYO_RFID_LABELS_CODE_NUM_CHAR];	//Etiqueta que se va a solicitar en función del manipulo conectado
//    static char Label_Read[HP_CRYO_RFID_LABELS_CODE_NUM_CHAR];		//Etiqueta leida
    static uint32 time_rfid = 0;									//Registro de control de tiempo que se permite permanecer en el proceso de lectura de la etiqueta
	
    //Variables
    uint8 isRunning;												//Indica si se hay etiqueta para bloquear el proceso de modo que se acelere
    uint32 isRunningTout;											//TimeOut del bloqueo cuando hay etiqueta
    uint8 offset = HPcryoGetSlot( HP, PRF) - 1;						/* Calculamos el offset para el codigo de error */
//    K70_RFID_CPU_ERR_tt RFID_module_Err;							//Código especifico del error RFID
    returnstatus_t rfid_status = RUNNING;							//Estado del proceso de comprobación de la etiqueta (lectura, borrado, gestión de lectura de distintas etiquetas)
    returnstatus_t rfid_read_status;								//Estado del proceso de la lectura de la etiqueta
	
    *RFID_err_code = HP_CRYO_RFID_OK;			//Error que devuelve por defecto (Err_Ok)
	
//	if (RFID_lock() == RFID_NOW_IN_USE)			//Si puede reservar el recurso del RFID (por que está libre)
//	{
//		HP->trt.RFID_reserved = HP_CRYO_RFID_reserved;		//Se activa un flag interno del manipulo que indica que tiene el RFID reservado
//		RFID_read_Default_label = 1;						//Se inicializa el proceso indicando que primero ha de leerse la etiqueta por defecto
//		label = 0;											//Se inicializa la etiqueta que se va a leer, a continuación se procederá a buscar en la tabla corrrespondiente la etiqueta requerida para ese manipulo
//		time_rfid = TICKS_GetTicks();
//		read_started = 0;
//	}	//Si he conseguido reservar el recuros del RFID, actualizo la variable del periferico que lo ha reservado y tomo la referencia de tiempo que puede tardar el proceso
	
//	if (HP->trt.RFID_reserved == HP_CRYO_RFID_reserved)		//Si el periferico que intenta emplear el RFID es el que tiene reservado el recurso
//	{
//		/* Bloqueamos el proceso cuando no estamos en los estados de espera de presencia y lectura de la etiqueta */
//		isRunning = 1;
//		isRunningTout = TICKS_GetTicks();
		
//		do
//		{
//			if(RFID_read_Default_label)		//Si toca leer primero la etiqueta por defecto
//			{
//				for (i = HP_CRYO_LABEL_ZO; i<HP_CRYO_NUM_LABELS; i++) 	//Recorremos todas las etiquetas
//				{
//					if (HP_CYRO_LABEL_REQUESTED [i][HPcryoGetModel( HP, PRF)] == HP_CRYO_DEFAULT)		//Una vez encontramos la etiqueta predeterminada para el manipulo en cuestión, la guardamos como solicitada
//					{
//						Label_requested[0] = HP_CRYO_LABEL_CODE [i][0];		//Cadena de caracteres que identifica a la etiqueta RFID
//						Label_requested[1] = HP_CRYO_LABEL_CODE [i][1];
//						label = i;											//Indice de la etiqueta que toca leer (Por defecto)
//					}
//				}
				
//				//Se realiza el proceso de la lectura y borrado de la etiqueta con los datos asociados al manipulo conectado y su etiqueta por defecto
//				rfid_read_status = RFID_read_label(Label_requested, Label_Read, HP_CYRO_LABEL_REQUESTED [label][HP_CRYO_RFID_LABEL_ERASE_INDICATOR], &RFID_module_Err);
				
//				switch (rfid_read_status)		//Gestion de los estados del proceso de la lectura
//				{
//					case IDLE: break;
//					case RUNNING:											//Unico estado donde por exceso de tiempo se puede abortar el proceso
//						HP->trt.RFID_read_label = RFID_NO_LABEL;
//						if (!read_started)						//Si se ha comenzado la lectura de una etiqueta
//						{
//							time_rfid = TICKS_GetTicks();		//Tomamos la referencia de tiempo
//							read_started = 1;					//Activamos un flag que indica que no se ha de inicializar de nuevo el tiempo para la lectura de la etiqueta
//						}
//						else{}
						
//						if (TICKS_DiffTicks(time_rfid) > RFID_time_read)		//Si se excede el tiempo seleccionado
//						{
//							RFID_free();											//Se libera el recurso
//							read_started = 0;
//							isRunning = 0;											//No estamos leyendo etiqueta
//							HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;		//Se limpia registro del periferico que ha reservado el recurso
//							ERR_add(Err_ComRFID1 + offset);							//Activamos un error de comunicación con el modulo RFID
//							*RFID_err_code = HP_CRYO_RFID_FAILURE;					//Devolvemos el codigo de error de time out
//							rfid_status = ERROR;									//Devolvemos que el proceso finaliza con error
//							return rfid_status;
//						}
//						break;
							
//					case ERROR:						//En caso de que se hara devuelto del módulo RFID un aviso de error
//						read_started = 0;			//Se reinicia el flag de comenzado proceso de lectura de tarjeta
						
//						if ((RFID_module_Err == K70_RFID_CPU_ERR_CANNOT_ERASE)|| (RFID_module_Err == K70_RFID_CPU_ERR_CANNOT_READ_ERASED))
//						{
//							read_started = 0;									//Indicamos que el proceso de lectura ha finalizado
//							isRunning = 0;										//No estamos leyendo etiqueta
//							*Label_Read_index = label;							//Devolvemos el índice de la etiqueta leida
//							RFID_free();										//Se libera el recurso
//							HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;	//Se limpia registro del periferico que ha reservado el recurso
//							rfid_status = SUCCESS;								//Devolvemos que el proceso finaliza con exito
//							ERR_delete(Err_ComRFID1 + offset);
//							if(HP->trt.RFID_read_label == RFID_NO_LABEL){	HP->trt.RFID_read_label = RFID_LABEL_OK;	}

//							return rfid_status;
//						}
//						else if ((RFID_module_Err != K70_RFID_CPU_ERR_OK) && (RFID_module_Err != K70_RFID_CPU_ERR_LABEL_INVALID))		//Si el código de error es distinto del Err_Ok y el de etiqueta invaloda
//						{
//							HP->trt.RFID_read_label = RFID_NO_LABEL;
//							RFID_free();											//Se libera el recurso
//							isRunning = 0;											//No estamos leyendo etiqueta
//							HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;		//Se limpia registro del periferico que ha reservado el recurso
//							ERR_add(Err_ComRFID1 + offset);							//Activamos un error de comunicación con el modulo RFID
//							*RFID_err_code = HP_CRYO_RFID_FAILURE;					//Devolvemos el codigo de error de time out
//							rfid_status = ERROR;									//Devolvemos que el proceso finaliza con error
//							return rfid_status;
//						}
//						else if (RFID_module_Err == K70_RFID_CPU_ERR_LABEL_INVALID)		//En caso de que el código de error sea el de etiqueta invalida
//						{
//							for (i = HP_CRYO_LABEL_ZO; i<HP_CRYO_NUM_LABELS; i++) 		//Recorremos todas las etiquetas
//							{
//								if ((HP_CYRO_LABEL_REQUESTED [i][HPcryoGetModel( HP, PRF)] == HP_CRYO_VALID)&&						//Se busca alguna etiqueta con validez para el manipulo
//									(Label_Read[0] == HP_CRYO_LABEL_CODE [i][0])&&(Label_Read[1] == HP_CRYO_LABEL_CODE [i][1]))		//y que coincida con la etiqueta leida
//								{
//									if(HP->trt.RFID_read_label == RFID_NO_LABEL){	HP->trt.RFID_read_label = RFID_LABEL_OK;	}
//									if (HP_CYRO_LABEL_REQUESTED [i][HP_CRYO_RFID_LABEL_ERASE_INDICATOR] == RFID_NOT_ERASE_LABEL)
//									{
//										/* Asignamos la etiqueta encontrada para el parametro de salida */ /* DAVID BUUUG*/
//										read_started = 0;									//Indicamos que el proceso de lectura ha finalizado
//										isRunning = 0;										//No estamos leyendo etiqueta
//										*Label_Read_index = i;								//Devolvemos el índice de la etiqueta leida
//										RFID_free();										//Se libera el recurso
//										HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;	//Se limpia registro del periferico que ha reservado el recurso
//										rfid_status = SUCCESS;								//Devolvemos que el proceso finaliza con exito
//										ERR_delete(Err_ComRFID1 + offset);
										
//										//RFID_time_diff[0] = TICKS_DiffTicks(RFID_time_ref[0]);		//DEBUG	-	Calculo del tiempo que ha tarda todo el proceso desde que se pulsó play
//										//RFID_time_diff[2] = TICKS_DiffTicks(RFID_time_ref[2]);		//DEBUG	-	Calculo del tiempo que tardael proceso de lectura del modulo RFID
										
//										return rfid_status;
//									}
//									else																												//Si se requiere de borrarla
//									{
//										RFID_read_Default_label = 0;			//Indico que ya he realizado la lectura de la etiqueta por defecto y a continuación borraré la que me ha leido como valida
//										Label_requested[0] = Label_Read[0];		//Indico que la etiqueta buscada ahora es la misma que la leida
//										Label_requested[1] = Label_Read[1];
//										label = i;								//Indico el índice de la etiqueta
//									}
//								}
//								else if((HP_CYRO_LABEL_REQUESTED [i][HPcryoGetModel( HP, PRF)] == HP_CRYO_NOT_VALID) &&
//										(Label_Read[0] == HP_CRYO_LABEL_CODE [i][0])&&(Label_Read[1] == HP_CRYO_LABEL_CODE [i][1]))
//								{
//									if(i != HP_CRYO_LABEL_ERASED)
//									{
//										if(HP->trt.RFID_read_label == RFID_NO_LABEL){	HP->trt.RFID_read_label = RFID_WRONG_LABEL;	}
//									}
//									else
//									{
//										if(HP->trt.RFID_read_label == RFID_NO_LABEL){	HP->trt.RFID_read_label = RFID_LABEL_ERASED;	}
//									}
//								}
//							}
							
//							if(HP->trt.RFID_read_label == RFID_NO_LABEL){	HP->trt.RFID_read_label = RFID_LABEL_UNKNOWN;	}
							
//							if(RFID_read_Default_label)							//Si no he encontrado la etiqueta leida entre las validas registradas en la tabla
//							{
								
//								isRunning = 0;									//No estamos leyendo etiqueta
//								*RFID_err_code = HP_CRYO_RFID_LABEL_INVALID;	//Devolvemos el codigo de error de etiqueta no contemplada para el manipulo conectado
//								rfid_status = ERROR;							//Devolvemos que el proceso finaliza con error
//								return rfid_status;
//							}
//						}
//						break;
							
//					case SUCCESS:										//En caso de haber tenido exito en la lectura de la etiqueta definida por defecto
//						read_started = 0;									//Indicamos que el proceso de lectura ha finalizado
//						isRunning = 0;										//No estamos leyendo etiqueta
//						*Label_Read_index = label;							//Devolvemos el índice de la etiqueta leida
//						RFID_free();										//Se libera el recurso
//						HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;	//Se limpia registro del periferico que ha reservado el recurso
//						rfid_status = SUCCESS;								//Devolvemos que el proceso finaliza con exito
//						ERR_delete(Err_ComRFID1 + offset);
//						if(HP->trt.RFID_read_label == RFID_NO_LABEL){	HP->trt.RFID_read_label = RFID_LABEL_OK;	}
						
//						//RFID_time_diff[0] = TICKS_DiffTicks(RFID_time_ref[0]);		//DEBUG	-	Calculo del tiempo que ha tarda todo el proceso desde que se pulsó play
//						//RFID_time_diff[2] = TICKS_DiffTicks(RFID_time_ref[2]);		//DEBUG	-	Calculo del tiempo que tardael proceso de lectura del modulo RFID
						
//						return rfid_status;
//						break;
							
//					case BLOCKING:		//En caso de estar en un proceso "bloqueante" no se puede abortar el proceso, se continúa hasta que llegue a otro estado
//						//isRunning = read_started;
//						break;
//					default:
//						//ERROR
//						break;
//				}
//			}
//			else
//			{
//				//Se realiza el proceso de la lectura y borrado de la etiqueta con los datos asociados al manipulo conectado y su etiqueta por defecto
//				rfid_read_status = RFID_read_label(Label_requested, Label_Read, HP_CYRO_LABEL_REQUESTED [label][HP_CRYO_RFID_LABEL_ERASE_INDICATOR], &RFID_module_Err);
				
//				switch (rfid_read_status)		//Gestion de los estados del proceso de la lectura
//				{
//					case IDLE: break;
//					case RUNNING:												//Unico estado donde por exceso de tiempo se puede abortar el proceso
//						if (TICKS_DiffTicks(time_rfid) > RFID_time_read)		//Si se excede el tiempo seleccionado
//						{
//							read_started = 1;									//Indicamos que el proceso de lectura ha finalizado
//							RFID_read_Default_label = 1;						//Reiniciamos el proceso y volveremos a leer la etiqueta por defecto
//							RFID_free();										//Se libera el recurso
//							isRunning = 0;										//No estamos leyendo etiqueta
//							HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;	//Se limpia registro del periferico que ha reservado el recurso
//							ERR_add(Err_ComRFID1 + offset);						//Activamos un error de comunicación con el modulo RFID
//							*RFID_err_code = HP_CRYO_RFID_FAILURE;				//Devolvemos el codigo de error de time out
//							rfid_status = ERROR;								//Devolvemos que el proceso finaliza con error
//							return rfid_status;
//						}
//						break;
							
//					case ERROR:
//						read_started = 0;										//Indicamos que el proceso de lectura ha finalizado
						
//						if ((RFID_module_Err == K70_RFID_CPU_ERR_CANNOT_ERASE)|| (RFID_module_Err == K70_RFID_CPU_ERR_CANNOT_READ_ERASED))
//						{
//							read_started = 0;									//Indicamos que el proceso de lectura ha finalizado
//							isRunning = 0;										//No estamos leyendo etiqueta
//							*Label_Read_index = label;							//Devolvemos el índice de la etiqueta leida
//							RFID_free();										//Se libera el recurso
//							HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;	//Se limpia registro del periferico que ha reservado el recurso
//							rfid_status = SUCCESS;								//Devolvemos que el proceso finaliza con exito
//							ERR_delete(Err_ComRFID1 + offset);
//							if(HP->trt.RFID_read_label == RFID_NO_LABEL){	HP->trt.RFID_read_label = RFID_LABEL_OK;	}

//							return rfid_status;
//						}
//						else if (RFID_module_Err != K70_RFID_CPU_ERR_OK)
//						{
//							isRunning = 0;										//No estamos leyendo etiqueta
//							RFID_read_Default_label = 1;						//Reiniciamos el proceso y volveremos a leer la etiqueta por defecto
//							RFID_free();										//Se libera el recurso
//							HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;	//Se limpia registro del periferico que ha reservado el recurso
//							ERR_add(Err_ComRFID1 + offset);						//Activamos un error de comunicación con el modulo RFID
//							*RFID_err_code = HP_CRYO_RFID_FAILURE;				//Devolvemos el codigo de error de time out
//							rfid_status = ERROR;								//Devolvemos que el proceso finaliza con error
//							return rfid_status;
//						}
//						break;
							
//					case SUCCESS:
//						read_started = 0;										//Indicamos que el proceso de lectura ha finalizado
//						isRunning = 0;											//No estamos leyendo etiqueta
//						*Label_Read_index = label;								//Devolvemos el índice de la etiqueta leida
//						RFID_read_Default_label = 1;							//Reiniciamos el proceso y volveremos a leer la etiqueta por defecto
//						RFID_free();											//Se libera el recurso
//						HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;		//Se limpia registro del periferico que ha reservado el recurso
//						rfid_status = SUCCESS;									//Devolvemos que el proceso finaliza con exito
//						ERR_delete(Err_ComRFID1 + offset);
//						return rfid_status;
//						break;
							
//					case BLOCKING:		//En caso de estar en un proceso "bloqueante" no se puede abortar el proceso, se continúa hasta que llegue a otro estado
//						//isRunning = read_started;
//						break;
//					default:
//						//ERROR
//						break;
//				}
//			}
//		/*
//		 * Mientras el flag NO sea RFID_NO_LABEL_DETECTED se mantendrá en el bucle bloqueante para continuar con la lectura RFID.
//		 * Se saldrá si se supera el tiempo de tout que es de 3 segundos (el propio proceso de lectura RFID completo tarda 1580ms).
//		 * También se sale en caso de errores, o en caso de quedarse en bucle en estados donde se permita el aborto de la operación.
//		 * Al tiempo propio de la lectura se le tiene que sumar los 1,7 segundos que tarda en pintar el popup y al tiempo que tarde
//		 * en recorrer los updates de los perifericos que haya hasta el que ha reservado el recurso del RFID. Esto puede provocar que
//		 * si toca el update del mismo periferico que reserva el RFID, se haga la lectura completa antes de que se pinte el popup, por
//		 * lo que no aparecerá por pantalla.
//		 */
//		}while( (RFID_label_detection()!= RFID_NO_LABEL_DETECTED) &&
//				isRunning &&
//				TICKS_DiffTicks( isRunningTout) < HP_CRYO_RFID_IS_RUNNING_TOUT_MS);
		
//		//count2++;									//DEBUG	-	Contador para conocer el numero de veces que sale del bucle de lectura
//		//RFID_time_ref[3] = TICKS_GetTicks();		//DEBUG	-	tiempo de referencia para contabilizar el tiempo que está fuera del bucle de lectura RFID
		
//		//Si se ha salido por Time Out, aviso sonoro de error
//		if (TICKS_DiffTicks( isRunningTout) > HP_CRYO_RFID_IS_RUNNING_TOUT_MS)		//V7790
//		{
//			if((RFID_getStatus() == RFID_STAT_WRITE_RESULT) ||
//			   (RFID_getStatus() == RFID_STAT_WAIT_READING_RESULT) ||
//			   (RFID_getStatus() == RFID_STAT_CHECK_MODELERASE) ||
//			   (RFID_getStatus() == RFID_STAT_VALIDATE))
//			{

//				read_started = 0;									//Indicamos que el proceso de lectura ha finalizado
//				isRunning = 0;										//No estamos leyendo etiqueta
//				*Label_Read_index = label;							//Devolvemos el índice de la etiqueta leida
//				RFID_free();										//Se libera el recurso
//				HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;	//Se limpia registro del periferico que ha reservado el recurso
//				rfid_status = SUCCESS;								//Devolvemos que el proceso finaliza con exito
//				ERR_delete(Err_ComRFID1 + offset);
//				if(HP->trt.RFID_read_label == RFID_NO_LABEL){	HP->trt.RFID_read_label = RFID_LABEL_OK;	}
//			}
//			else
//			{	rfid_status = ERROR;	}
//		}
//	}
	return rfid_status;
}


void HPCryoRFIDreset( tHPcryoData *HP, tPRFdata *PRF)
{
//	if (HP->trt.RFID_reserved == HP_CRYO_RFID_reserved)		//Si el periferico tiene reservado el recurso del RFID
//	{
//		HP->trt.RFID_reserved = HP_CRYO_RFID_not_reserved;	//Se indica que ya no tiene el recurso reservado
//		RFID_free();										//Se libera el recurso
//	}
}

void HPcryoRFIDlabelLimits( uint8 lblIndex, tHPcryoData *HP, tPRFdata *PRF)
{
	/* Aplicamos limite de temperatura, nos quedamos con la mas alta entre la 
	 * consignada y la limitación de la toallita */
	if( HP->frames.mainIn.data.fConsignaTemperatura < HP_CRYO_LABEL_TEMPERATURE_LIMIT[lblIndex])
	{
		/* La toallita limita mas que la consigna actual, asignamos la temperatura de la toallita */
		HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_LABEL_TEMPERATURE_LIMIT[lblIndex];
		HP->trt.trt_temp_set = HP_CRYO_LABEL_TEMPERATURE_LIMIT[lblIndex];							/* V7778 - TEMP SEC */
	}
	
	/* Ajustamos el tiempo de tratamiento al menor entre la taollita y el actual consignado */
	if( HP->frames.mainIn.data.u16SegundosTratamiento > (HP_CRYO_LABEL_TIME_LIMIT[lblIndex] + HP_CRYP_TRT_TIME_OFFSET))
	{
		/* La toallita limita mas que el tiempo actual, asignamos el tiempo de trt de la toallita */
		HP->frames.mainIn.data.u16SegundosTratamiento = HP_CRYO_LABEL_TIME_LIMIT[lblIndex] + HP_CRYP_TRT_TIME_OFFSET;
		HP->trt.trtTime_s = HP_CRYO_LABEL_TIME_LIMIT[lblIndex];											 
	}
	
	/* V7787 */
	//Aplicar medidas para ajustar errores al tratamiento de DEMO
	cHPcryoModels model;				/* V7790 */
	model = HPcryoGetModel( HP, PRF);	/* V7790 */
	
#ifndef APP_SW_VER_DM_NO_LIMIT
	if(lblIndex == HP_CRYO_LABEL_DM)
	{
		HP->trt.TrtParameters.DemoTRT = 1;
		
		HPcryoSetAlarmCfg( 	HP_CRYO_DFLT_LIST_TRT_TEMP_WINDOW[model], HP_CRYO_DFLT_TRT_VAC_WAIT_TIME,
							HP_CRYO_DFLT_TRT_TEMP_WAIT_LIST_TIME[model], HP_CRYO_DFLT_TRT_VAC_FAIL_TIME,
							HP_CRYO_DFLT_TRT_TEMP_FAIL_LIST_TIME[model], HP_CRYO_DFLT_MAX_IN_TEMP[model],
							HP->trt.trt_temp_set - HP_CRYO_DFLT_TRT_MIN_SNS_TEMP_REL, HP_CRYO_DFLT_TRT_LOW_TEMP_TIME, HP);
	}
#endif
	/* V7787 */
	
	/* V7790 */
	if(lblIndex == HP_CRYO_PROD_LABEL_PD)
	{
		HP->trt.TrtParameters.ProdTRT = 1;
	}
	/* V7790 */
	
	HP->cleanUp.LabelRQcleanup = HP_CRYO_LABEL_CLEANUP_REQ_LIMIT[lblIndex];
}

uint8 HPcryoTrtVacumRetry( tHPcryoData *HP, tPRFdata *PRF)
{	
//	/* Comprobamos que se puede repetir el vacum */
//	if( !HPcryoTrtVacumRetryAvailable( HP, PRF)){ return 0;}
	
//	/* El manípulo en MAN_IDLE, es decir, ha terminado el ciclo de tratamiento */
//	if( (HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE) && (HP->frames.mainOut.data.estado != HP_CRYO_MAN_INPROGRESS)){ return 0;}	//V7760 AUTO - se ha añadido el in progress
	
//	/* Se puede reintentar el vacum, lo ejecutamos. Primero, inicializamos algunas variables para el reintento */
//	HP->trt.timeOut = 0;
//	HP->trt.pauseTime = 0;
//	HP->trt.beforePause = HP_CRYO_TREATMENT_DONE;
//	HP->trt.adjustVacumCnt = HP_CRYO_TRT_ADJUST_VACUM_NUM;
//	HP->trt.adjustVacumTimeOut = HP_CRYO_TRT_ADJUST_VACUM_TOUT;
//	HP->trt.adjustVacumStatus = HP_CRYO_ADJUST_VACUM_IDLE;
//	HP->trt.adjustVacumValue = 0.0;
//	HP->trt.adjustVacumResetTime = 0;
	
//	/* Reseteamos el proceso de modo AUTO */
//	HPcryoTrtAutoModeRestart( HP, PRF);
	
//	/* Reseteamos el flag de peticion al usuario de recolocar el HP. Cuando se produce una recolocacion
//	 * la EXP resetea el contador de resucciones, esto hara que este flag vaya sincronizado con el numero
//	 * de resucciones dentro del primer intervalo de tiempo en el que se puede recolocar y se controlan
//	 * las resucciones. Es decir, cuando recoloques se resetea el flag de aviso y el contador de resucciones
//	 * por el propio proceso de recolocar que quita el vacum */
//	HP->trt.vacumRetryRqstUserToMoveHP = 0;
	
//	/* Cogemos el tiempo en el que se ha "soltado" el aplicador para poder luego calcular el
//	 * tiempo transcurrido desde que se ha soltado el HP hasta que se vuelve a colocar (IN_PROGRESS) */
//	if (HP->trt.startTime != 0)
//	{
//		HP->trt.vacumRetryRlsTime = TICKS_GetTicks();
//	}
	
//	/* Comprobamos si necesitamos nueva toallita */
//	if( HP->trt.rqLbl && HP->trt.vacumRetryCnt == 0)
//	{
//		/* Se requiere toallita para el reintento */
//		HP->trt.vacumRetryCnt = HP_CRYO_TRT_VACUM_RETRY_NUM;
//		HP->trt.status = HP_CRYO_TREATMENT_RUN_WAITING_RFID;
//	}
//	else
//	{
//		/* No se requiere toallita, descontamos del numero de reintentos antes de cambiar toallita */
//		if( HP->trt.vacumRetryCnt > 0){ HP->trt.vacumRetryCnt--;}
//		HP->trt.status = HP_CRYO_TREATMENT_RUN_WAITING_USER_START;
//	}
	
	/* Indicamos que se ha preparado el reintento */
	return 1;	
}

//uint8 HPcryoTrtErrConVaccManage ( tHPcryoData *HP, tPRFdata *PRF)
//{
//	/* El manípulo en MAN_IDLE, es decir, ha terminado el ciclo de tratamiento */
//	if( (HP->frames.mainOut.data.estado != HP_CRYO_MAN_IDLE) && (HP->frames.mainOut.data.estado != HP_CRYO_MAN_INPROGRESS)){ return 0;}	//V7760 - se ha añadido el in progress
//	
//	/* Se puede reintentar el vacum, lo ejecutamos. Primero, inicializamos algunas variables para el reintento */
//	HP->trt.timeOut = 0;
//	HP->trt.pauseTime = 0;
//	HP->trt.beforePause = HP_CRYO_TREATMENT_DONE;
//	HP->trt.adjustVacumCnt = HP_CRYO_TRT_ADJUST_VACUM_NUM;
//	HP->trt.adjustVacumTimeOut = HP_CRYO_TRT_ADJUST_VACUM_TOUT;
//	HP->trt.adjustVacumStatus = HP_CRYO_ADJUST_VACUM_IDLE;
//	HP->trt.adjustVacumResetTime = 0;
//	
//	/* Cogemos el tiempo en el que se ha "soltado" el aplicador para poder luego calcular el 
//	 * tiempo transcurrido desde que se ha soltado el HP hasta que se vuelve a colocar (IN_PROGRESS) */
//	if (HP->trt.startTime != 0)	HP->trt.vacumRetryRlsTime = TICKS_GetTicks();
//	
//	HP->trt.status = HP_CRYO_TREATMENT_RUN_WAITING_USER_START;
//	
//	/* Indicamos que se ha preparado el reintento */
//	return 1;
//}

void HPcryoTrtAdjustVacumUpdate( tHPcryoData *HP, tPRFdata *PRF)
{
	float vacValue;
	float vacMin, vacMax;
	                   
//	/* Logica de estados */
//	switch( HP->trt.adjustVacumStatus)
//	{
//		case HP_CRYO_ADJUST_VACUM_IDLE:
//			/* En IDLE reseteamos la configuración del vacum.
//			 * Cuando se requiera un nuevo vacum se tiene que pasar a
//			 * estado "SET" */
//			if( TICKS_DiffTicks( HP->trt.adjustVacumResetTime) > HP_CRYO_ADJUST_VACUM_RESET_TOUT)
//			{
//				/* Reseteamos la configuración de vacum */
//				EXP_UCconfigHPvacumFactors( HP_CRYO_VACUM_FACTOR_RETRY_STD, HP_CRYO_VACUM_FACTOR_LUNG_STD, PRF->IDperifHW);
//				HP->trt.adjustVacumResetTime = TICKS_GetTicks();
//			}
//			break;
//		case HP_CRYO_ADJUST_VACUM_SET:
//			/* Ponemos la nueva consigna de vacum y cambiamos los valores de % de resucción y pulmon */
//			HP->frames.mainIn.data.fConsignaVacum = HP->trt.adjustVacumValue;
//			EXP_UCconfigHPvacumFactors( HP_CRYO_ADJUST_VACUM_RETRY_WHEN_SET, HP_CRYO_ADJUST_VACUM_LUNG_WHEN_SET, PRF->IDperifHW);
			
//			/* Hemos finalizado, pasamos a WAIT */
//			HP->trt.adjustVacumStatus = HP_CRYO_ADJUST_VACUM_WAIT;
//			break;
//		case HP_CRYO_ADJUST_VACUM_WAIT:
//			/* Esperamos a que el vacum del HP alcance el valor de consigna */
//			vacValue = HP->frames.mainOut.data.presionVaccum;
//			vacMin = HP->frames.mainIn.data.fConsignaVacum * ( 1.0 - HP_CRYO_ADJUST_VACUM_RETRY_WHEN_SET);
//			vacMax = HP->frames.mainIn.data.fConsignaVacum * HP_CRYO_ADJUST_VACUM_LUNG_WHEN_SET;
//			if( ( vacMin <= vacValue && vacValue <= vacMax) || HPcryoGetStatus( HP, PRF) != HP_CRYO_TREATMENT)
//			{
//				/* Dejamos los valores de % de resucción y pulmón a los standard */
//				EXP_UCconfigHPvacumFactors( HP_CRYO_VACUM_FACTOR_RETRY_STD, HP_CRYO_VACUM_FACTOR_LUNG_STD, PRF->IDperifHW);
				
//				/* Hemos finalizado, pasamos a IDLE */
//				HP->trt.adjustVacumStatus = HP_CRYO_ADJUST_VACUM_IDLE;
//			}
//			break;
//		default:
//			/* Estado no válido, pasamos a IDLE */
//			HP->trt.adjustVacumStatus = HP_CRYO_ADJUST_VACUM_IDLE;
//			break;
//	}
}

void HPcryoCleanUpUpdate( tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Logica de estados a partir del estado del HP */
//	switch( HP->frames.mainOut.data.estado)
//	{
//		case HP_CRYO_MAN_IDLE:
//			/* El HP esta en IDLE, o bien hemos terminado el proceso de limpieza o bien tenemos
//			 * que iniciarlo. Si estamos en CLEANING debemos empezar la limpieza y si estamos en
//			 * DONE es que hemos terminado */
//			HP->cleanUp.cycle.timeCleanPaused = 0;
			
//			if( HP->cleanUp.status == HP_CRYO_CLEAN_UP_CLEANING ||
//				HP->cleanUp.status == HP_CRYO_CLEAN_UP_CHECK_PATIENT)
//			{
//				/* Gestionde flanco */
//				if( HP->frames.mainIn.data.cambio_estado == HP_CRYO_MAN_IDLE)
//				{
//					HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_ENABLEVAC;
//				}
//				else
//				{
//					HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
//				}
//			}
//			else if( HP->cleanUp.status == HP_CRYO_CLEAN_UP_COUNTDOWN)
//			{
//				/* Estamos a la espera de iniciar el proceso de limpieza, si no estamos contando
//				 * tiempo empezamos a contarlo */
//				if( HP->cleanUp.time_ms == 0){ HP->cleanUp.time_ms = TICKS_GetTicks();}
//				if( TICKS_DiffTicks( HP->cleanUp.time_ms) > HP->cleanUp.countDown_ms)
//				{
//					/* Se ha acabado el proceso de cuenta atras, pasamos al estado de espera al vacum */
//					HP->cleanUp.status = HP_CRYO_CLEAN_UP_WAIT_VACUM;
//					HP->cleanUp.time_ms = 0;
//				}
//			}
//			else if( HP->cleanUp.status == HP_CRYO_CLEAN_UP_WAITING_USER)
//			{
//				/* A la espera de la respuesta del usuario, puede ser 2 opciones:
//				 * 1) Proceder con la limpieza
//				 * 2) Resetear la cuenta atras
//				 * Directamente se asignara a la variable status el nuevo estado en la llamada a la función
//				 * de toma de decisión */
//			}
//			else if( HP->cleanUp.status == HP_CRYO_CLEAN_UP_WAIT_VACUM)
//			{
//				/* Estamos a la espera de que se libere el recurso vacum. Vamos comprobando si
//				 * lo tenemos libre y avanzamos al estado pertinente cuando lo tengamos */
//				if( HPcryoCleanUpVacumIsFree( HP, PRF))
//				{
//					/* Recurso libre, avanzamos. */
//					if( HP->cleanUp.forceClean == 0)
//					{
//						HP->cleanUp.checkPatientTime_ms = 0;
//						HP->cleanUp.status = HP_CRYO_CLEAN_UP_CHECK_PATIENT;
//					}
//					else
//					{
//						HP->cleanUp.cycle.tmrIsClean_ms = 0;
//						HP->cleanUp.cycle.tmrCannotClean_ms = 0;
//						HP->cleanUp.status = HP_CRYO_CLEAN_UP_CLEANING;
//						HP->cleanUp.cycle.NoUmbralVacResetFilter = 0;
//						HP->cleanUp.cycle.timeCleanPaused = 0;
//						HP->cleanUp.cycle.timeRefCleanPaused = 0;
//					}
					
//					/* Enviamos el HP a ENABLEVAC */
//					HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_ENABLEVAC;
//				}
//			}
//			else
//			{
//				/* O bien es DONE o bien es FAIL, en cualquier caso hemos terminado el proceso de
//				 * limpieza */
//			}
//			break;
//		case HP_CRYO_MAN_ENABLEVAC:
//			/* Podemos estar detectando al paciente o bien limpiando */
//			if( HP->cleanUp.status == HP_CRYO_CLEAN_UP_CHECK_PATIENT)
//			{
//				/* Consignamos presion de detección y comprobamos si la alcanzamos en un tiempo
//				 * establecido. Si la alcanzamos es que hay tapon o paciente y debemos esperar
//				 * ordenes, si no se alcanza podemos pasar al proceso de limpieza  */
//				/* Cogemos el tiempo inicial */
//				if( HP->cleanUp.checkPatientTime_ms == 0){ HP->cleanUp.checkPatientTime_ms = TICKS_GetTicks();}
				
//				/* Asignamos la presión de test */
//				HP->frames.mainIn.data.fConsignaVacum = HP_CRYO_TRT_VAC_LVL_LIST[HPcryoGetModel( HP, PRF)][2];
				
//				/* Comprobamos si hemos alcanzado la presion o hemos terminado el tiempo de detección */
//				if( HP->frames.mainOut.data.presionVaccum >
//					( HP->frames.mainIn.data.fConsignaVacum - HP_CRYO_CLEAN_UP_VACUM_OFFSET))
//				{
//					/* Detectado tapon o paciente, esperamos ordenes */
//					HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
//					HP->cleanUp.status = HP_CRYO_CLEAN_UP_WAITING_USER;
//					HP->cleanUp.checkPatientTime_ms = 0;
//				}
//				else if( TICKS_DiffTicks( HP->cleanUp.checkPatientTime_ms) > HP_CRYO_CLEAN_UP_PATIENT_TIME)
//				{
//					/* No hemos detectado al paciente ni al tapón, pasamos a cleaning */
//					HP->cleanUp.status = HP_CRYO_CLEAN_UP_CLEANING;
//					HP->cleanUp.checkPatientTime_ms = 0;
//					HP->frames.mainIn.data.fConsignaVacum = 0.0;
//					HP->cleanUp.cycle.NoUmbralVacResetFilter = 0;
//					HP->cleanUp.cycle.timeCleanPaused = 0;
//					HP->cleanUp.cycle.timeRefCleanPaused = 0;
//				}
//			}
//			else if( HP->cleanUp.status == HP_CRYO_CLEAN_UP_CLEANING)
//			{
//				/*Si algún manipulo solicita vacuum (por tratamiento) se pausa el proceso de limpieza hasta que acabe y se pueda reanudar el proceso de limpieza*/
				
//				if(HPcryoVaccFree2Clean(HP, PRF))	/*Si no hay ningún manipulo solicitando vacuum para tratamiento*/
//				{
//					if(HP->cleanUp.cycle.timeRefCleanPaused != 0)
//					  {HP->cleanUp.cycle.timeCleanPaused += TICKS_DiffTicks(HP->cleanUp.cycle.timeRefCleanPaused);}	/*Acumulo el tiempo que se ha permanecido en Pausa*/
//					HP->cleanUp.cycle.timeRefCleanPaused = 0;	/*Reseteo la referencia*/
					
//					/* Ejecutamos los ciclos de vacum y comprobamos el resultado de la función */
//					HP->cleanUp.status = HPcryoCleanUpCycles( HP, PRF);
//					if( HP->cleanUp.status != HP_CRYO_CLEAN_UP_CLEANING)
//					{
//						/* Hemos terminado el proceso de limpieza, enviamos a IDLE */
//						HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
//					}
//				}
//				else	/*Si hay un manipulo solicitando vacuum para tratamiento*/
//				{
//					/*Se toma la referencia de tiempo para restarla al total que lleve el proceso de limpieza*/
//					if(HP->cleanUp.cycle.timeRefCleanPaused == 0){	HP->cleanUp.cycle.timeRefCleanPaused = TICKS_GetTicks();	}
					
//					/*HP->cleanUp.status = */HPcryoCleanUpPause( HP, PRF);
//				}
//			}
////			else if(HP->cleanUp.status == HP_CRYO_CLEAN_UP_PAUSE)
////			{
////				/* Si ya no hay ningún manipulo solicitando vacuum con tratamiento */
////				if (HPcryoVaccFree2Clean(HP, PRF))  {	HP->cleanUp.status = HP_CRYO_CLEAN_UP_CLEANING;	}
////				else								{ HPcryoCleanUpPause( HP, PRF); }
////			}
//			else
//			{
//				/* Estado no valido en ENABLEVAC, volvemos a IDLE */
//				HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
//			}
//			break;
//		case HP_CRYO_MAN_PAUSE:
//			HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;
//			break;
//		case HP_CRYO_MAN_STANDBY:
//			/*Para no perder la limpieza, me espero a que se salga de standby para continuar*/
//			HPcryoCleanUpReset( 0, HP_CRYO_CLEAN_UP_DFLT_COUNTDOWN, HP_CRYO_CLEAN_UP_DFLT_TIME_IS_CLEAN,
//							   HP_CRYO_CLEAN_UP_DFLT_TIME_CANNOT_CLEAN, HP_CRYO_CLEAN_UP_DFLT_CLEAN_VACUM,
//							   HP, PRF);

//			HP->cleanUpInitOrEnd = HP_CRYO_CLEAN_UP_END_OF_TRT;

//			break;
//		case HP_CRYO_MAN_INIT:
//		case HP_CRYO_MAN_MANIPULO_DESHAB_ERROR_COMS:
//		case HP_CRYO_MAN_DESCONFIGURADO:
//		case HP_CRYO_MAN_ALARM:
//			/* Estados de alarma, la logica de gestión de errores se encarga
//			 * de la politica a seguir. No cambiamos nada en el estado de
//			 * limpieza */
//			break;
//		default:
//			/* No estamos en ninguno de los estados previstos, fallo de cleaning */
//			HP->cleanUp.status = HP_CRYO_CLEAN_UP_FAIL;
//			break;
//	}
}

uint8 HPcryoCleanUpVacumIsFree( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 cnt;
	
	/* La limpieza requiere de que solo un HP la este ejecutando, comprobamos si hay otro HPcryo limpiandose. */
	for( cnt = 0; cnt < HPCRYO_MAX_N_PERIFS; cnt++)
	{
		/* Miramos si hay otro HP que no seamos "nosotros" */
		if( HPcryoData[cnt].isUsed && (HP != &( HPcryoData[cnt])))
		{
			/* Comprobamos que este en estado clean up */
			if( HPcryoData[cnt].status == HP_CRYO_CLEAN_UP)
			{
				/* Si esta en alguno de los estados que requieren la bomba de vacum indicamos
				 * que no esta disponible */
				if( HPcryoData[cnt].cleanUp.status == HP_CRYO_CLEAN_UP_CLEANING ||
					HPcryoData[cnt].cleanUp.status == HP_CRYO_CLEAN_UP_CHECK_PATIENT)
				{ return 0;}
			}			
		}
	}
	
	/* Si llegamos aqui es que esta disponible la bomba */
	return 1;
}

cHPcryoCleanUpStatus HPcryoCleanUpCycles( tHPcryoData *HP, tPRFdata *PRF)
{	
//	/* Ciclos de limpieza del manipulo */
//	/* 1 - Arrancamos el vacum a la presion de limpieza */
//	HP->frames.mainIn.data.fConsignaVacum = HP->cleanUp.cycle.cleanVacum;
	
//	/* 2 - Comprobamos si estamos haciendo vacum */
//	if( HP->frames.mainOut.data.presionVaccum < HP_CRYO_CLEAN_UP_UMBRAL_VACUM)
//	{
//		if (HP->cleanUp.cycle.NoUmbralVacResetFilter > HP_CRYO_CLEAN_UP_RESET_FILTER)
//		{
//			/* 3a - No hacemos vacum nosotros, reseteamos los temporizadores */
//			HP->cleanUp.cycle.tmrCannotClean_ms = 0;
//			HP->cleanUp.cycle.tmrIsClean_ms = 0;
//		}
//		else{HP->cleanUp.cycle.NoUmbralVacResetFilter++;}
//	}
//	else
//	{
//		/* 3b - Estamos haciendo vacum, comprobamos si alcanzamos la consigna o no */
//		if( HP->frames.mainOut.data.presionVaccum >=
//			( HP->cleanUp.cycle.cleanVacum - HP_CRYO_CLEAN_UP_VACUM_OFFSET))
//		{
//			/* Presión de consigna alcanzada */
//			/* 4 - Arrancamos el tiempo total de error si aun no lo hemos arrancado y reseteamos el
//			 * contador de tiempo de limpieza OK */
//			if( HP->cleanUp.cycle.tmrCannotClean_ms == 0)
//			{ HP->cleanUp.cycle.tmrCannotClean_ms = TICKS_GetTicks();}
//			HP->cleanUp.cycle.tmrIsClean_ms = 0;
//			HP->cleanUp.cycle.NoUmbralVacResetFilter = 0;
			
//			/* 5 - Comprobamos si hemos pasado mas tiempo del máximo
//			 * permitido en el proceso de limpieza. Si se ha agotado fallo si no continuamos */
//			if( TICKS_DiffTicks( HP->cleanUp.cycle.tmrCannotClean_ms - HP->cleanUp.cycle.timeCleanPaused) > HP->cleanUp.cycle.timeCannotClean)
//			{
//				/* Se ha agotado el tiempo, no se ha podido limpiar */
//				return HP_CRYO_CLEAN_UP_FAIL;
//			}
//		}
//		else
//		{
//			/* Estamos haciendo vacum pero no alcanzamos la consigna */
//			/* 4 - Arrancamos el tiempo de validación de limpieza si aun no lo hemos arrancado y reseteamos
//			 * el contador de tiempo total de error */
//			if( HP->cleanUp.cycle.tmrIsClean_ms == 0)
//			{ HP->cleanUp.cycle.tmrIsClean_ms = TICKS_GetTicks();}
//			HP->cleanUp.cycle.tmrCannotClean_ms = 0;
//			HP->cleanUp.cycle.NoUmbralVacResetFilter = 0;
			
//			/* 5 - Comprobamos si ha pasado el tiempo de validación de limpieza, si es así la limpieza
//			 * ha finalizado con éxito */
//			if( TICKS_DiffTicks( HP->cleanUp.cycle.tmrIsClean_ms) > HP->cleanUp.cycle.timeIsClean)
//			{
//				/* Limpieza con éxito */
//				return HP_CRYO_CLEAN_UP_DONE;
//			}
//		}
//	}
	
	/* Si llegamos aqui es que no se ha acabado aun el proceso de limpieza */
	return HP_CRYO_CLEAN_UP_CLEANING;
}

cHPcryoCleanUpStatus HPcryoCleanUpPause ( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Si no tenemos presión por tener un tapón */
	if( HP->frames.mainOut.data.presionVaccum < ( HP->cleanUp.cycle.cleanVacum - HP_CRYO_CLEAN_UP_VACUM_OFFSET))
	{
		/* 1- Quitamos el vacuum */
		HP->frames.mainIn.data.fConsignaVacum = 0;
		
		/* 2- Reseteamos variables del proceso de limpieza */
		HP->cleanUp.cycle.NoUmbralVacResetFilter = 0;
		HP->cleanUp.cycle.tmrCannotClean_ms = 0;
		//HP->cleanUp.cycle.tmrIsClean_ms = 0;
	}
	
	return HP_CRYO_CLEAN_UP_PAUSE;
}

uint8 HPcryoVaccFree2Clean ( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 cnt;
		
//	/* Comprobamos si ningún manipulo esté intentando coger la bomba para un tratamiento */
//	for( cnt = 0; cnt < HPCRYO_MAX_N_PERIFS; cnt++)
//	{
//		/* Miramos si hay otro HP que quiera usar la bomba en un tratamiento o un test de vacuum*/
//		if( HPcryoData[cnt].isUsed)
//		{
//			/* Comprobamos que este en estado de tratamiento o intentando hacer un test de vacuum */
//			if(( HPcryoData[cnt].status == HP_CRYO_TREATMENT && HPcryoData[cnt].trt.status == HP_CRYO_TREATMENT_RUN_VACUM) ||
//			   ( HPcryoData[cnt].status == HP_CRYO_TEST_VACUM && HPcryoData[cnt].tstVac.status == HP_CRYO_TEST_VAC_RUN_VACUM ) ||
//			   ( HPcryoVaccResuctionRqst(HP, PRF)))
//			{
//				/* Si esta en alguno de los estados que requieren la bomba de vacum indicamos
//				 * que no esta disponible */
//				return 0;
//			}
//		}
//	}
	
	/* Si llegamos aqui es que esta disponible la bomba */
	return 1;
}

uint8 HPcryoVaccResuctionRqst ( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 cnt;
	float diff_vacuum;
	
//	/* Comnprobar si algún aplicador que esté en tratamiento tiene un nivel de vacuum que vaya a requerir realizar una resucción */
//	for( cnt = 0; cnt < HPCRYO_MAX_N_PERIFS; cnt++)
//	{
//		if( HPcryoData[cnt].isUsed)
//		{
//			diff_vacuum = HPcryoData[cnt].frames.mainIn.data.fConsignaVacum - HPcryoData[cnt].frames.mainOut.data.presionVaccum;

//			if((HPcryoData[cnt].status == HP_CRYO_TREATMENT) && (diff_vacuum >= (HPcryoData[cnt].frames.mainIn.data.fConsignaVacum*HP_CRYO_VACUM_FACTOR_RETRY_STD)))
//			{
//				return 1;	//Hay solicitud para resuccionar
//			}
//		}
//	}
	
	/* Si llegamos aqui es que esta disponible la bomba */
	return 0;
}

void HPcryoTrtAutoModeHdlr( tHPcryoData *HP, tPRFdata *PRF)
{
//	/* Comprobamos si es modo auto */
//	if( HP->trt.mode == HP_CRYO_TRT_MODE_AUTO)
//	{
//		/* Es modo auto, de entrada activamos el chichometro */
//		HP->frames.mainIn.data.enable_plica = 1;
						
//		/* En función del estado actual del proceso de auto */
//		switch( HP->trt.autoMode.status)
//		{
//			case HP_CRYO_TRT_AUTO_IDLE:
//				/* En este estado no hacemos nada, solo reseteamos las variables */
//				HP->trt.autoMode.tmr = 0;
//				HP->trt.autoMode.detectionFilterAcum = 0;
//				HP->trt.autoMode.isOK = 0;
				
//				/* Apagamos el chichometro */
//				HP->frames.mainIn.data.enable_plica = 0;
//				break;
//			case HP_CRYO_TRT_AUTO_WAIT_TIME:
//				/* Comprobamos si hemos pasado el tiempo de espera inical
//				 * antes de comprobar la plica */
//				if( HP->trt.autoMode.tmr == 0){ HP->trt.autoMode.tmr = TICKS_GetTicks();}
//				if( TICKS_DiffTicks( HP->trt.autoMode.tmr) > HP->trt.autoMode.waitTime)
//				{
//					/* Tiempo de espera inical completado, pasamos a la detección */
//					HP->trt.autoMode.tmr = 0;
//					HP->trt.autoMode.detectionFilterAcum = 0;
//					HP->trt.autoMode.isOK = 0;
//					HP->trt.autoMode.status = HP_CRYO_TRT_AUTO_DETECTING;
//				}
//				break;
//			case HP_CRYO_TRT_AUTO_DETECTING:
//				/* Filtramos la lectura de la plica */
//				if( HP->frames.mainOut.data.estado_entradas.bit_field.detec_plica_dcha != 0 ||
//					HP->frames.mainOut.data.estado_entradas.bit_field.detec_plica_iza != 0)
//				{
//					/* Plica detectada, incrementamos filtro contador */
//					HP->trt.autoMode.detectionFilterAcum += HP->trt.autoMode.detectionFilterInc;
//				}
//				else
//				{
//					/* Plica detectada, incrementamos filtro contador */
//					if( HP->trt.autoMode.detectionFilterAcum > HP->trt.autoMode.detectionFilterDec)
//					{ HP->trt.autoMode.detectionFilterAcum -= HP->trt.autoMode.detectionFilterDec;}
//					else{ HP->trt.autoMode.detectionFilterAcum = 0;}
//				}
								
//				/* Comprobamos si ha pasado el tiempo de filtrado */
//				if( HP->trt.autoMode.tmr == 0){ HP->trt.autoMode.tmr = TICKS_GetTicks();}
//				if( TICKS_DiffTicks( HP->trt.autoMode.tmr) > HP->trt.autoMode.detectionTime)
//				{
//					/* Tiempo de filtrado completado, asignamos el resultado */
//					HP->trt.autoMode.isOK = (HP->trt.autoMode.detectionFilterAcum >= HP->trt.autoMode.detectionFilterIsOKlvl);
					
//					/* Reseteamos variables */
//					HP->trt.autoMode.tmr = 0;
//					HP->trt.autoMode.detectionFilterAcum = 0;
//					HP->trt.autoMode.status = HP_CRYO_TRT_AUTO_RESULT;
//				}
//				break;
//			case HP_CRYO_TRT_AUTO_RESULT:
//				/* Tenemso el resultado, comprobamos si ha pasado el tiempo de recolocar y cambiar
//				 * vacum para parar el tratamiento en caso de que no sea OK */
//				if( HP->trt.autoMode.isOK == 0)
//				{
//					/* V7760 AUTO - Al no ser OK el llenado de la plica hay que pausar el tratamiento y evaluar las recolocaciones disponibles que quedan */
//					HPcryoTrtVacumRetry( HP, PRF);								//Se evalua las recolocaciones que se pueden realizar
//					HP->frames.mainIn.data.cambio_estado = HP_CRYO_MAN_IDLE;	//Se manda el aplicador a IDLE
//					BUZZ_Configure(1, 100, PATRO_SO_FINAL_TRT );				//Aviso sonoro

					
					
//					/* No es ok el resultado del modo auto, miramos si aun se puede "solucionar" */
////					if( !HPcryoTrtVacumRetryAvailable( HP, PRF) /*&& !HPcryoTrtAdjustVacumAvailable( HP, PRF)*/)	//Descomentado, prueba V7760
////					{																								//Descomentado, prueba V7760
////						/* Ya no se puede solucionar, paramos el tratamiento */
////						HPcryoTrtStop( 1, HP, PRF);
////					}																								//Descomentado, prueba V7760
//				}
//				/* Apagamos el chichometro */
//				HP->frames.mainIn.data.enable_plica = 0;
//				break;
//			default:
//				break;
//		}
//	}
//	else
//	{
//		/* No es modo auto, desactivamos el chichometro */
//		HP->frames.mainIn.data.enable_plica = 0;
//	}
}

void HPcryoTrtAutoModeRestart( tHPcryoData *HP, tPRFdata *PRF)
{
	/* Si no estamos en auto no asignamos nada */
	if( HP->trt.mode == HP_CRYO_TRT_MODE_AUTO)
	{
		HP->trt.autoMode.status = HP_CRYO_TRT_AUTO_WAIT_TIME;  
		HP->trt.autoMode.tmr = 0;
		HP->trt.autoMode.waitTime = HP_CRYO_TRT_AUTO_DFLT_WAIT_TIME;
		HP->trt.autoMode.detectionTime = HP_CRYO_TRT_AUTO_DFLT_DETECTION_TIME;
		HP->trt.autoMode.detectionFilterAcum = 0;
		HP->trt.autoMode.detectionFilterInc = HP_CRYO_TRT_AUTO_DFLT_FILTER_INC;
		HP->trt.autoMode.detectionFilterDec = HP_CRYO_TRT_AUTO_DFLT_FILTER_DEC;
		HP->trt.autoMode.detectionFilterIsOKlvl = HP_CRYO_TRT_AUTO_DFLT_FILTER_OK_LVL;
		HP->trt.autoMode.isOK = 0;
	}
}
uint8 HPcryoGetTimeRestriction (cHPcryoTrtTimes *TimeRestricted, tHPcryoData *HP, tPRFdata *PRF)
{
	cHPcryoModels HPmodel;
	HPmodel = HPcryoGetModel( HP, PRF);
	if (HP_CRYO_TIME_RESTRICTION_PER_HP[HPmodel] == 1)						
	{
		*TimeRestricted = HP_CRYO_TIME_LIST_PER_HP[HPmodel][0];
		return 1;
	}
	return 0;   
}

uint8 HPcryoReconfigHP( cHPcryoModels model2cfg, tHPcryoData *HP, tPRFdata *PRF)
{
	uint32 time2wait;
	
//	/*Habilitar Remap OUT*/
//	HPcryoSetRemap( HP_CRYO_REMAP_FRAME_DEFINITION_OUT_INDEX, PRF);
	
//	/*Espera de 100ms*/
//	time2wait = TICKS_GetTicks();
//	while(TICKS_DiffTicks(time2wait)<100);
	
//	/*Lectura*/
//	EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_DEFINITION_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//						  HP_CRYO_REMAP_FRAME_DEFINITION_OUT_SIZE,
//						  &( HP->frames.Define_Out.vector[1]));
	
//	/*Deshabilitar Remap OUT*/
//	HPcryoClearRemap( HP_CRYO_REMAP_FRAME_DEFINITION_OUT_INDEX, PRF);
	
//	/*Actualizar Buffer*/
//	HP->frames.Define_In.data.block_size = HP_CRYO_REMAP_FRAME_DEFINITION_IN_SIZE;
	
//	HP->frames.Define_In.data.u8TAG = 0x25;
	
//	switch(model2cfg)		/*Para indicar el número de fuentes que emplea el modelo*/
//	{
//		case HP_CRYO_MODEL_CURVED:
//		case HP_CRYO_MODEL_TIGHT:
//		case HP_CRYO_MODEL_STRIGHT:
//		case HP_CRYO_MODEL_OVAL:
//		case HP_CRYO_MODEL_OVAL_CURVED:
//		case HP_CRYO_MODEL_ANGLED:
//			HP->frames.Define_In.data.u16NumeroFuentesUso = 0x0002;	break;
//		case HP_CRYO_MODEL_TINY:
//		case HP_CRYO_MODEL_TINY_CURVED:
//			HP->frames.Define_In.data.u16NumeroFuentesUso = 0x0001;	break;
//		case HP_CRYO_MODEL_DOUBLE:
//			HP->frames.Define_In.data.u16NumeroFuentesUso = 0x0004;	break;
//		default: return 0; break;
//	}
	
//	HP->frames.Define_In.data.u32Modelo = model2cfg;	/*Modelo que se quiere proframar en el HP*/
	
//	HP->frames.Define_In.data.ptu8DatosVerificacion[0] = 0x33;	/*Byte de verificación a 51 (0x33) para que realice el test de sondas*/
	
//	HP->frames.Define_In.data.ptu8DatosVerificacion[1] = HP->frames.Define_Out.data.ptu8DatosVerificacion[1];	/*Los bits reservados los dejamos igual que estaban, para ello se hace la lectura previa*/
//	HP->frames.Define_In.data.ptu8DatosVerificacion[2] = HP->frames.Define_Out.data.ptu8DatosVerificacion[2];
//	HP->frames.Define_In.data.ptu8DatosVerificacion[3] = HP->frames.Define_Out.data.ptu8DatosVerificacion[3];
	
//	/*Escritura*/
//	EXPremapFrameSetData( HP_CRYO_REMAP_FRAME_DEFINITION_IN_DIR + PRF->myDirInRemapFramesBuffer,
//						  HP_CRYO_REMAP_FRAME_DEFINITION_IN_SIZE,
//						  &( HP->frames.Define_In.vector[1]));
	
//	/*Habilitar Remap IN*/
//	HPcryoSetRemap( HP_CRYO_REMAP_FRAME_DEFINITION_IN_INDEX, PRF);
	
//	/*Espera de 100ms*/
//	time2wait = TICKS_GetTicks();
//	while(TICKS_DiffTicks(time2wait)<100);
	
//	/*Deshabilitar Remap IN*/
//	HPcryoClearRemap( HP_CRYO_REMAP_FRAME_DEFINITION_IN_INDEX, PRF);
	
//	/*Deshabilitar Periferico*/
//	EXPdeshabilitarPeriferico(PRF->IDperifHW);
	
//	/*Espera de 100ms*/
//	time2wait = TICKS_GetTicks();
//	while(TICKS_DiffTicks(time2wait)<100);
	
//	/*Habilitar Periferico*/
//	EXPhabilitarPeriferico(PRF->IDperifHW);
	
	return 1;
}

void HPcryoTrtSetPointOsc( uint32 TimeLoop, tHPcryoData *HP, tPRFdata *PRF)
{	
//	if((EXPdata.perif[PRF->IDperifHW].data.fields.version < HP_CRYO_SW_HP_THRESSHOLD_CTRL_OSC_TEMP) && HPcryo_TRT_HP_temp_status(HP, PRF))		/* V7778 - TEMP SEC */
//	{
//		if((TICKS_DiffTicks(HP->trt_OscTemp_timer)>TimeLoop)&&(HP->frames.mainIn.data.fConsignaTemperatura != HP_CRYO_LABEL_DM_TEMP))	/*Entramos cada 10 segundos si no estamos en un tratamiento de DEMO*/
//		{
//			HP->trt_OscTemp_timer = TICKS_GetTicks();
			
//			/* Gestion de la oscilación en la consigna de temperatura si no se han superado las 50 resucciones */
//			if( EXP_UCgetVacumRetrys( HPcryoGetSlot( HP, PRF)) < HP_CRYO_MAX_VACUM_RETRYS_IN_THIRD_TIME)
//			{
//				/* V7778 - TEMP SEC */
//				if(EXP_UCtempSecureStatus())
//				{
//					if((HPcryoTrtGetTimeSeconds( HP, PRF) > (HP->trt.trtTime_s * HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[PRF->common->data.fields.model][HP_CRYO_PERCENT_TRT_TIME_EARLY_TEMP])) ||
//					   (HP->trt.trt_temp_set > HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[PRF->common->data.fields.model][HP_CRYO_TEMPERATURE_SET_POINT_EARLY_TRT]) )
//					{
//						if(HP->frames.mainIn.data.fConsignaTemperatura != HP->trt.trt_temp_set){	HP->frames.mainIn.data.fConsignaTemperatura = HP->trt.trt_temp_set;	}
//						else{	HP->frames.mainIn.data.fConsignaTemperatura = HP->trt.trt_temp_set + HP_CRYO_DELTA_TEMP_OSC;	}
//					}
//					else
//					{
//						if(HP->frames.mainIn.data.fConsignaTemperatura != HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[PRF->common->data.fields.model][HP_CRYO_TEMPERATURE_SET_POINT_EARLY_TRT])
//						{	HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[PRF->common->data.fields.model][HP_CRYO_TEMPERATURE_SET_POINT_EARLY_TRT];	}
//						else
//						{	HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[PRF->common->data.fields.model][HP_CRYO_TEMPERATURE_SET_POINT_EARLY_TRT] + HP_CRYO_DELTA_TEMP_OSC;	}
//					}
//				}
//				else
//				{
//					if(HP->frames.mainIn.data.fConsignaTemperatura != HP->trt.trt_temp_set){	HP->frames.mainIn.data.fConsignaTemperatura = HP->trt.trt_temp_set;	}
//					else{	HP->frames.mainIn.data.fConsignaTemperatura = HP->trt.trt_temp_set + HP_CRYO_DELTA_TEMP_OSC;	}
//				}
//				/* V7778 - TEMP SEC */
//			}
//			/* En caso de haber superado las 50 resucciones */
//			else
//			{
//				/* Se han superado el numero máximo de reintentos en el tercer intervalo de tiempo. Cambiamos la
//				 * temperatura de consigna */
//				if(HP->frames.mainIn.data.fConsignaTemperatura != HP_CRYO_TRT_VACUM_RETRY_THIRD_TIME_TEMP)
//				{	HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_VACUM_RETRY_THIRD_TIME_TEMP;		}
//				else{	HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_VACUM_RETRY_THIRD_TIME_TEMP + HP_CRYO_DELTA_TEMP_OSC;	}
//			}
//		}
//	}
	
}

uint8 HPcryoManageTempMedError( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 i; 							/* Variable auxiliar para recorrer sensores de temperatura */
	cHPcryoModels HP_model;				/* Modelo del aplicador */
	uint8 TempSensor_OK;				/* Flag que indica el numero de sondas OK */
	static uint32 HP_error_ref_time[HPCRYO_MAX_N_PERIFS] = {0,0,0,0};	/* Referencia de tiempo para que salte el error tras cierto periodo */
	uint16 HPindex = HPcryoGetSlot( HP, PRF) - 1;
	float TempWind;
	float ExtraHeatThress;
	float lower_thress_temp;		/* V7787 */
	
//	TempSensor_OK = 0;						/* Inicialización del numero de sondas OK */
//	HP_model = HPcryoGetModel( HP, PRF);	/* Obtenemos el modelo del aplicador */
	
//	if(HP->status != HP_CRYO_TREATMENT)
//	{
//		HP_error_ref_time[HPindex] = 0;
//	}
	
//	if((EXP_UCerrSecureStatus()) && (!HP->trt.TrtParameters.DemoTRT))	/* Inicialización de parametros de seguridad en función del modo programado en el equipo *//* V7787 - Añadido que no aplicar medidas restrictivas si el TRT es de DEMO */
//	{
//		TempWind = (float)HP_CRYO_DFLT_LIST_TRT_SECURE_TEMP_WINDOW[HP_model];
//		ExtraHeatThress = (float)HP_CRYO_TEMP_MED_MANAGE_HOT_TEMP_UPPER_THRESSHOLD[HP_model];
//	}
//	else
//	{
//		TempWind = (float)HP_CRYO_DFLT_LIST_TRT_TEMP_WINDOW[HP_model];
//		ExtraHeatThress = (float)HP_CRYO_TEMP_MED_MANAGE_HOT_TEMP_UPPER_THRESSHOLD[HP_model];
//	}
	
//	/* V7787 */
//	if((HPcryoGetTRTplusThree(HP, PRF)) && (HPcryoGetTRTplusThreeTime(HP, PRF) > HP_CRYO_TIME_CHNG_SET_TEMP_ERR_WIND_MED))
//	{
//		lower_thress_temp = (float)HP->frames.mainIn.data.fConsignaTemperatura;
//	}
//	else if((HPcryoGetTRTplusThree(HP, PRF)) && (HPcryoGetTRTplusThreeTime(HP, PRF) < HP_CRYO_TIME_CHNG_SET_TEMP_ERR_WIND_MED))
//	{
//		lower_thress_temp = (float)HP->trt.trt_temp_set;
//	}
//	else
//	{
//		lower_thress_temp = (float)HP->frames.mainIn.data.fConsignaTemperatura;
//	}
//	/* V7787 */
	
//	for(i=0; i<HP_CRYO_MAX_TEMP_SNS; i++)	/* Se recorren todas las sondas */
//	{
//		if((float)HP->frames.dbgOut.data.MedidasTemperatura[i] < ((float)lower_thress_temp-(TempWind/2)))//((float)HP->frames.mainIn.data.fConsignaTemperatura-(TempWind/2))) //V7787
//		{
//			return 1;		/* Se permite lanzar el error */
//		}
//		/* (consigna + temp/2 + VALUE) > TempSensor */
//		if((float)HP->frames.dbgOut.data.MedidasTemperatura[i] < ((float)HP->frames.mainIn.data.fConsignaTemperatura+(TempWind/2)+ExtraHeatThress))
//		{
//			TempSensor_OK++;	/* Damos la temperatura por buena si está dentro de los límites establecidos */
//		}
//	}
	
//	if(TempSensor_OK == 0)	/* En caso de que todas las sondas estén por encima de ventana medios + VALUE */
//	{
//		if(HP_error_ref_time[HPindex] == 0)						/* Si el error no ha saltado antes */
//		{	HP_error_ref_time[HPindex] = TICKS_GetTicks();	}	/* Tomamos la referencia de tiempo */
//		else if(TICKS_DiffTicks(HP_error_ref_time[HPindex])>HP_CRYO_TEMP_WINDOW_WHEN_UP_ERROR_TIME_REF)		/* Si se superan los 10 minutos con el error activo */
//		{
//			return 1;	/* Ninguna sonda se encuentra dentro de los límites aceptables y se permite que el error se lance */
//		}
//	}
//	else
//	{
//		HP_error_ref_time[HPindex] = 0;
//	}

	return 0;	/* Si llega aquí es que alguna sonda o todas están dentro de los límites aceptables y el error se pasará por alto */
}

void HPcryoCleanUpCancelledTimesSentToHP ( uint8 cancelled_times, tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 bufferSend[1];
	bufferSend[0] = cancelled_times;
	
//	if(EXPdata.perif[PRF->IDperifHW].data.fields.version > HP_CRYO_SW_HP_THRESSHOLD_CTRL_MEM_FLASH_ACCESS)	/* Control de versión del aplicador */
//	{
//		HPcryoInitFrameFlashMemoryData( HP, PRF);															/* Inicio de las tramas remap In y Out */
		
//		HPcryoEraseFlashMemory ( HP_CRYP_MEMORY_FLASH_ADDR_TO_USE, 1, HP, PRF);								/* Borramos el bloque de memoria que se va a emplear */
//		HPcryoWriteFlashMemory ( HP_CRYP_MEMORY_FLASH_ADDR_TO_USE, sizeof(cancelled_times), bufferSend, HP, PRF);/* Escribimos el valor de cancelaciones en la Flash del aplicador */
		
//		HPcryoCloseFrameFlashMemoryData( HP, PRF);															/* Hacemos un clear de los flags de los remaps */
//	}
}

uint8 HPcryoCleanUpCancelledTimesReceiveFromHP ( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 bufferReceive[1];
	
//	if(EXPdata.perif[PRF->IDperifHW].data.fields.version > HP_CRYO_SW_HP_THRESSHOLD_CTRL_MEM_FLASH_ACCESS)	/* Control de versión del aplicador */
//	{
//		HPcryoInitFrameFlashMemoryData( HP, PRF);															/* Inicio de las tramas remap In y Out */
		
//		HPcryoReadFlashMemory ( HP_CRYP_MEMORY_FLASH_ADDR_TO_USE, 1, bufferReceive, HP, PRF);						/* Leemos el numero de cancelaciones de la Flash del aplicador */
		
//		HPcryoCloseFrameFlashMemoryData( HP, PRF);															/* Hacemos un clear de los flags de los remaps */
//		return bufferReceive[0];	/* Devolvemos el valor de las cancelaciones */
//	}
//	else
	{
		return HP_CRYO_CLEAN_UP_MAX_TIMES_CANCEL;				/* En caso de que el aplicador tenga una versión de SW inferior a la requerida, se fuerza a la limpieza */
	}
}

uint8 HPcryoCleanUpCancelAllowed ( uint8 slot)
{
	tHPcryoData *HP;
	tPRFdata *PRF;
	
//	if(HPcryoGetFromSlot(slot, &HP, &PRF))
//	{
//		if(HP->cleanUp.cancelled_times < HP_CRYO_CLEAN_UP_MAX_TIMES_CANCEL)	/* Si el número máximo de cancelaciones no se ha alcanzado se permite volver a cancelar */
//		{
//			return 1;
//		}
//	}
	return 0;
}

uint8 HPcryoCleanUpNumberOfCancellations ( cPRFslot slot)
{
	tHPcryoData *HP;
	tPRFdata *PRF;
	
	if(HPcryoGetFromSlot(slot, &HP, &PRF))
	{
		return HP->cleanUp.cancelled_times;		/* Devuelve el número de cancelaciones realizadas */
	}
	return 0;
}

float HPcryoHPtemperature ( cPRFslot slot)
{
	tHPcryoData *HP;
	tPRFdata *PRF;
	float LowerTemp;		/* Temperatura más baja medida por el aplicador */
	float DiffTemp;			/* Diferencia entre la temperatura medida y la consigna */
	uint8 TempWindow = 2;	/* Ventana para aplicar la corrección a la temperatura medida */
	
//	if(HPcryoGetFromSlot(slot, &HP, &PRF))
//	{
//		/* Tomamos la temperatura más baja */
//		if(HP->frames.mainOut.data.fTempIzquierda < HP->frames.mainOut.data.fTempDerecha)
//		{	LowerTemp = HP->frames.mainOut.data.fTempIzquierda;		}
//		else
//		{	LowerTemp = HP->frames.mainOut.data.fTempDerecha;	}
		
//		/* Miramos si la temperatura que estamos midiendo está dentro de la ventana de aplicación de corrección */
//		if((LowerTemp < (HP->trt.trt_temp_set+TempWindow)) && (LowerTemp > (HP->frames.mainIn.data.fConsignaTemperatura-TempWindow)))
//		{
//			DiffTemp = LowerTemp - HP->trt.trt_temp_set;	/* Cálculo de la diferencia entre la temperatura y la consigna */
			
//			if(DiffTemp>0)	/* Si la diferencia es positiva */
//			{	LowerTemp = HP->trt.trt_temp_set + (DiffTemp * (DiffTemp/TempWindow));		}			/* Se aplica la corrección */
//			else			/* Si la diferencia es negativa */
//			{	LowerTemp = HP->trt.trt_temp_set + ((-1) * DiffTemp * (DiffTemp/TempWindow));		}	/* Se aplica la corrección */
//		}
//	}
	return LowerTemp;
}

void HPcryoGetBit51 ( tHPcryoData *HP, tPRFdata *PRF)
{
	uint32 time2wait;
		
//	/*Habilitar Remap OUT*/
//	HPcryoSetRemap( HP_CRYO_REMAP_FRAME_DEFINITION_OUT_INDEX, PRF);
	
//	/*Espera de 100ms*/
//	time2wait = TICKS_GetTicks();
//	while(TICKS_DiffTicks(time2wait)<100);
	
//	/*Lectura*/
//	EXPremapFrameGetData( HP_CRYO_REMAP_FRAME_DEFINITION_OUT_DIR + PRF->myDirInRemapFramesBuffer,
//						  HP_CRYO_REMAP_FRAME_DEFINITION_OUT_SIZE,
//						  &( HP->frames.Define_Out.vector[1]));
}

uint8 HPcryoGetTRTplusThree ( tHPcryoData *HP, tPRFdata *PRF)
{
	return HP->trt.trt_secure_plus_three;
}

uint32 HPcryoGetTRTplusThreeTime ( tHPcryoData *HP, tPRFdata *PRF)
{
    return 0;//TICKS_DiffTicks(HP->trt.trt_secure_plus_three_time_ref);
}

/* V7778 - TEMP SEC */

uint8 HPcryo_Cooling_process ( tHPcryoData *HP, tPRFdata *PRF)
{
	float lower_temp;
	uint32 model;
	
//	if(HP->status != HP_CRYO_TREATMENT)			//Si no se encuentra el aplicador en estado de TRT, salimos sin aplicar medida
//	{
//		HP->trt.set_temp_reached = 0;		//Consigna no alcanzada
//		return HP->trt.set_temp_reached;
//	}
	
//	if(HPcryoGetTRTplusThree(HP, PRF))			//Si se ha puesto en modo seguro +3 grados, no se aplica medida
//	{
//		HP->trt.set_temp_reached = 1;		//Consigna alcanzada
//		return HP->trt.set_temp_reached;
//	}

//	lower_temp = HP->frames.dbgOut.data.MedidasTemperatura[HPcryo_get_lower_temp_sensor(HP, PRF)];	//Obtenemos la temperatura más baja del aplicador
//	model = PRF->common->data.fields.model;															//Obtenemos el modelo del aplicador
	
//	if(lower_temp > HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_RANGE_LIMIT_1])	//Si nos encontramos en el primer tramo de la bajada (>1ºC)
//	{
//		HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_RANGE_LIMIT_1] - 1;	//Se asigna la consigna +0ºC
//		HP->trt.time_ref_range2 = TICKS_GetTicks();			//Se actualiza la referencia de tiempo del segundo tramo de bajada
//		HP->trt.set_temp_reached = 0;						//Se indica que no se ha llegado a consigna
//	}
//	else if(HP->frames.mainIn.data.fConsignaTemperatura > (HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_RANGE_LIMIT_2] + HP_CRYO_DELTA_TEMP_OSC))	//Si nos encontramos en el segundo tramo de bajada (<1ºC) (>-5ºC)   //  V7787 añadido "+ osc"
//	{
//		if(TICKS_DiffTicks(HP->trt.time_ref_range2)>HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_TIME_STEP_RANGE_2])	//Si superamos el paso de tiempo para cambiar la consigna
//		{
//			HP->trt.time_ref_range2 = TICKS_GetTicks();		//Se actualiza la referencia de tiempo del segundo tramo de bajada
//			HP->frames.mainIn.data.fConsignaTemperatura -= HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_STEP_2];		//Actualizamos la consigna para bajar de temperatura
//		}
//		HP->trt.time_ref_range3 = TICKS_GetTicks();		//Se actualiza la referencia de tiempo del tercer tramo de bajada
//		HP->trt.set_temp_reached = 0;					//Se indica que no se ha llegado a consigna
//	}
//	else if(HP->frames.mainIn.data.fConsignaTemperatura > (HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_SET_POINT_EARLY_TRT] + HP_CRYO_DELTA_TEMP_OSC))		//Si nos encontramos en el tercer tramo de bajada (<-5ºC)(>consigna)
//	{
//		if(TICKS_DiffTicks(HP->trt.time_ref_range3)>HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_TIME_STEP_RANGE_3])	//Si superamos el paso de tiempo para cambiar la consigna
//		{
//			HP->trt.time_ref_range3 = TICKS_GetTicks();		//Se actualiza la referencia de tiempo del tercer tramo de bajada
//			HP->frames.mainIn.data.fConsignaTemperatura -= HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_STEP_3];		//Actualizamos la consigna para bajar de temperatura
//		}
//		HP->trt.set_temp_reached = 0;		//Se indica que no se ha llegado a consigna
//	}
//	else if((HPcryoTrtGetTimeSeconds( HP, PRF) < (HP->trt.trtTime_s * HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_PERCENT_TRT_TIME_EARLY_TEMP])) &&
//			(EXP_UCtempSecureStatus()))		//Si estamos en el primero 60% del tratamiento
//	{
//		if(HP->trt.set_temp_reached == 0){	HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_SET_POINT_EARLY_TRT];	}		//La consigna es la inicial programada (consigna final + 2ºC)
//		HP->trt.set_temp_reached = 1;					//Se indica que se ha llegado a consigna
//		HP->trt.time_ref_range3 = TICKS_GetTicks();		//Se actualiza la referencia de tiempo del tercer tramo de bajada
//	}
//	else if(HP->frames.mainIn.data.fConsignaTemperatura <= (HP->trt.trt_temp_set + HP_CRYO_DELTA_TEMP_OSC))		//Si la temperatura está dentro de la consigna final
//	{
//		if(HP->trt.set_temp_reached == 0){	HP->frames.mainIn.data.fConsignaTemperatura = HP->trt.trt_temp_set;	}		//Asignamos la consigna final solo una vez (para permitir las oscilaciones)
//		HP->trt.set_temp_reached = 1;		//Se indica que se ha llegado a consigna
//	}
//	else		//Para realizar la ultima rampa de bajada de temperatura (-6ºC -> -8ºC)
//	{
//		if(TICKS_DiffTicks(HP->trt.time_ref_range3)>HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_TIME_STEP_RANGE_3])	//Si superamos el paso de tiempo para cambiar la consigna
//		{
//			HP->trt.time_ref_range3 = TICKS_GetTicks();		//Se actualiza la referencia de tiempo del tercer tramo de bajada
//			HP->frames.mainIn.data.fConsignaTemperatura -= HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_STEP_3];		//Actualizamos la consigna para bajar de temperatura
//		}
//		HP->trt.set_temp_reached = 0;		//Se indica que no se ha llegado a consigna
//	}
	
//	if(HP->trt.trt_temp_set >= HP->frames.mainIn.data.fConsignaTemperatura)			//Si la consigna actual es mayor que la consigna final programada
//	{
//		if(HP->trt.set_temp_reached == 0){	HP->frames.mainIn.data.fConsignaTemperatura = HP->trt.trt_temp_set;	}		//Asignamos la temperatura final solo una vez
//		HP->trt.set_temp_reached = 1;		//Damos por alcanzada la temperatura de consigna
//		return HP->trt.set_temp_reached;
//	}

	return HP->trt.set_temp_reached;
}

uint8 HPcryo_Resume_Cooling ( tHPcryoData *HP, tPRFdata *PRF)
{
	float lower_temp;
	uint32 model;
	
//	lower_temp = HP->frames.dbgOut.data.MedidasTemperatura[HPcryo_get_lower_temp_sensor(HP, PRF)];	//Obtenemos la temperatura más baja del aplicador
//	model = PRF->common->data.fields.model;
	
//	if(lower_temp > HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_RANGE_LIMIT_1])	//Si la temperatura del aplicador es superior al límite 1 de temperatura
//	{
//		HP->frames.mainIn.data.fConsignaTemperatura = HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[model][HP_CRYO_TEMPERATURE_RANGE_LIMIT_1] - 1;	//Se asigna la consigna +0ºC
//	}
//	else		//En caso contrario
//	{
//		HP->frames.mainIn.data.fConsignaTemperatura = lower_temp;		//Consignamos el valor de la sonda más baja y retomamos el proceso de bajada de temperatura
//	}
	
//	HP->trt.time_ref_range2 = TICKS_GetTicks();		//Actualizar referencias de tiempos para las rampas de bajada
//	HP->trt.time_ref_range3 = TICKS_GetTicks();
	
	HP->trt.set_temp_reached = 0;
	
	return HP->trt.set_temp_reached;
}

uint8 HPcryo_TRT_HP_temp_status ( tHPcryoData *HP, tPRFdata *PRF)
{
//	if(!EXP_UCtempSlopeStatus()){	return 1;	}
	return HP->trt.set_temp_reached;	//Devuelve el estado de la bajata de temperatura, si se ha alcanzado el valor de consigna
}

uint8 HPcryo_get_lower_temp_sensor ( tHPcryoData *HP, tPRFdata *PRF)
{
	uint8 i;					//Variable auxiliar
	float temperature_low;		//Variable para comparar temperaturas
	uint8 sns_index = 0;		//indice del sensor
	
	temperature_low = 500.0;	//Inicializacion
	
	for(i=0;i<HP_CRYO_MAX_TEMP_SNS;i++)		//Se recorren todos los sensores
	{
		if(HP->frames.dbgOut.data.MedidasTemperatura[i]<temperature_low)		//Se busca el valor de temperatura más bajo
		{
			temperature_low = HP->frames.dbgOut.data.MedidasTemperatura[i];		//Se almacena el valor de temperatura mas bajo para ir comparando
			sns_index = i;														//Se almacena el indice del sensor que está midiendo el valor mas bajo
		}
	}
	return sns_index;		//Devuelve el indice del sensor con la temperatura mas baja
}

/* V7778 - TEMP SEC */

/* V7780 */
float HPcryo_get_temp_slope ( tHPcryoData *HP, tPRFdata *PRF)
{
	static float HPprevSNSmeasured[HPCRYO_MAX_N_PERIFS][HP_CRYO_MAX_TEMP_SNS];	//Matriz de temperaturas anteriores por aplicador
	uint16 HPindex = HPcryoGetSlot( HP, PRF) - 1;
	uint8 group, sns, sensor_num;
	float slope = 0;
	uint8 num_sns = 0;
	cHPcryoModels model;
	
//	model = HPcryoGetModel(HP,PRF);		//Tomamos el modelo del aplicador
	
//	for( sns = 0; sns < HP_CRYO_MAX_SONDAS_GRUPO; sns++)			/*Recorremos todas las sondas del grupo*/
//	{
//		sensor_num = HP_CRYO_ALL_SENSOR [model][sns];		/*Tomamos el índice de la sonda*/

//		if(sensor_num!=0)											/*Si no existe esa sonda en ese grupo saltamos a la siguiente*/
//		{
//			if(HP->status != HP_CRYO_TREATMENT)						/*En caso de no estar en tratamiento actualizamos las temperaturas almacenadas*/
//			{HPprevSNSmeasured[HPindex][sensor_num-1] = HP->frames.dbgOut.data.MedidasTemperatura[sensor_num-1];}
			
//			slope = abs(HP->frames.dbgOut.data.MedidasTemperatura[sensor_num-1] - HPprevSNSmeasured[HPindex][sensor_num-1]);	/*Realizamos el valor absolito de la diferencia entre las medidas de las sondas actuales y la medida anterior*/
//			HPprevSNSmeasured[HPindex][sensor_num-1] = HP->frames.dbgOut.data.MedidasTemperatura[sensor_num-1];					/*Actualizamos las medidas*/
//			num_sns++;		/*Acumulamos el numero de sondas empleadas en el calculo*/
//		}
//	}
	
//	slope /= num_sns;	/*Sacamos la media de la pendiente de todas las sondas*/
	
	return slope;
}
/* V7780 */

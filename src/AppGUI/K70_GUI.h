/*
 * Libreria             -       Graphic User Interface (GUI)
 * PCB                  -       CoreK70
 * Versi�n              -       1.00
 * Fecha compilaci�n    -       xx/xx/2016
 * 
 * Descripci�n:
 *      El objetivo de esta librer�a es aportar las herramientas necesarias para la creaci�n de interfaces gr�ficas que 
 *      permiten la comunicaci�n entre el usuario y el equipo. 
 *      La interfaz se divide en diferentes pantallas y estas en diferentes capas que permiten crear transparencias 
 *      entre im�genes. Los elementos que permiten crear las diferentes pantallas son los widgets y pueden ser de los 
 *      siguientes tipos: Bot�n, interruptor, visor de imagen, visor num�rico, ventana emergente y timer (falta programar).
 *      Esta libreria requiere que el archivo que contiene todas las im�genes necesarias para crear la interfaz en 
 *      formato CCN (pack.ccn), el archivo del �ndice de estas im�genes (pack.lut) y el archivo con la definici�n de la 
 *      interfaz (interface.csv) est�n grabados en la nandFlash. Por ahora para poder grabar las im�genes en la nandFlash 
 *      hay que copiarlas previamente desde un USB.
 *      A trav�s de esta librer�a tambi�n se puede controlar el back light de la pantalla, ya que esta enmascara la llamada a 
 *      la funci�n de control del back light de la librer�a GFX.
 *      Tambi�n es posible crear interfaces con un fondo de color s�lido sin necesidad de a�adir una imagen de ese color.
 *      Es posible cambiar las caracter�sticas de los widgets mediante las funciones apropiadas y que los widgets bot�n, 
 *      pulsador y ventana emergente realicen funciones al ser pulsadas o soltadas (callbacks). 
 *      Para usar esta libreria es necesario compilar tambi�n la librer�a K70_GFX.h y la librer�a K70_CCN.h.
 *      Esta librer�a no est� pensada para entornos multitarea ni protegida con mutex.
 *      
 * Compilacion:
 *      Para utilizar esta librer�a en una aplicaci�n hay que configurar las propiedades del proyecto de la aplicaci�n 
 *      tal como se describe a continuaci�n:
 *      - En:           "C/C++ Build - Settings - ARM Ltd Windows GCC C Compiler - Directories"
 *        A�adir:       "${SystemDrive}\libK70\libCoreK70\Headers"
 *      - En:           "C/C++ Build - Settings - ARM Ltd Windows GCC C Linker - Miscellaneous - Other objects"
 *        A�adir:       "${SystemDrive}/libK70/libCoreK70/Debug/libCoreK70_GFX.a"
 *      - En:           "C/C++ Build - Settings - ARM Ltd Windows GCC C Linker - Miscellaneous - Linker flags"
 *        A�adir:       "--start-group "${SystemDrive}/libK70/libCoreK70/Debug/libCoreK70_GFX.a" -Xlinker --end-group"
 *      - En:           "C/C++ Build - Settings - ARM Ltd Windows GCC C Linker - Linker Order"
 *        Subir "${SystemDrive}/libK70/libCoreK70/Debug/libCoreK70_GFX.a" a la primera posici�n 
 *      
 * Uso:
 * 		FALTAAAA!!
 * 		
 * 		
 * 		1) LLamar a la funci�n GFXinit() para inicializar la librer�a. A esta funci�n tambi�n hay que pasarle el tipo de
 * 		compresi�n que se va a utilizar y los punteros a los archivos .LUT (archivo con el �ndice de las im�genes) y al 
 * 		.CCN (archivo con las im�genes comprimidas).
 * 		2) LLamar a la funci�n GFXconfigScreen() para configurar si se quiere pintar el fondo de un color s�lido si no se
 * 		dispone de una imagen que ocupe toda la pantalla.
 * 		3) Si se quiere modificar el back light se debe llamar a la funci�n GFXbackL().
 * 		4) Para crear una escena, hay que llamar a la funci�n GFXinitScene() e indicar el n�mero de capas que va a tener
 * 		la escena.
 * 		5) Luego ya podemos a�adir las capas que queremos usar con la funci�n GFXaddLayer() y a�adir los iconos en la capa
 * 		con la funci�n GFXaddIcon().
 * 		6) Para configurar las diferentes caracter�sticas de los iconos hay que usar las funciones: GFXconfigVisibility(),
 * 		GFXconfigPosition() y GFXconfigImage().
 * 		7) Para eliminar los iconos, las capas y la escena, hay que llamar a las funciones GFXremoveIcon(), GFXremoveLayer()
 * 		y GFXremoveScene() respectivamente.
 * 		8) Si se quiere refrescar la pantalla hay que llamar a la funci�n GFXrefresh().
 * 		9) Por �ltimo llamar a la funci�n GFXfinish() para finalizar la librer�a.
 *      
 * Ejemplo:
 *      Hay una demostraci�n de todas las funciones de la librer�a en el proyecto: Demo_CoreK70_GUI.       
 *      
 */  

#ifndef GUI_H_
#define GUI_H_

#include "GeneralDefines.h"
//#include  "../DDR/DDR.h"

/*Esta constante est� delante de la definici�n de tipos porque se necesita para la estructura del visor de imagen*/
#define GUInumVimg 12/*N�mero de imagenes diferentes a mostrar en el visor num�rico(set de n�meros del 0-9, 
 *el signo menos(-) y el signo de separaci�n decimal( . � ,)*/


//#define NUM_MANIPULOS 4 // N�mero de manipulos.


/* - Definicion de tipos */
/*- 	Estructura rectangulo*/
typedef struct { 
	
	uint16	posx;
	uint16	posy;
	uint16	w;
	uint16 	h;
	
}GUIstRect;

typedef struct{
	
	uint32	idImg;
	void 	*ptrImg;
	
}GUIstImagen;


typedef struct{
	
	GUIstRect areaTS;
	GUIstImagen imgTS;
	
}stTS;






/*-		Estructura pulsaci�n pantalla t�ctil*/

/*-		Estructura com�n para todos los widgets*/
typedef struct{
	uint32 	id; 			//Id del widget, no se debe repetir
	uint8	screen; 		//Pantalla en la que est� situado el widget, el valor de la pantalla tiene que empezar por 0 y seguir en orden
	uint8 	widgetType; 	/*Tipo de widget: 1=bot�n, 2=interruptor, 3=visor de imagen, 4=visor num�rico, 5=ventana emergente y 
							timer=falta por programar*/
	void* 	stWidgetType; 	//Estructura especifica de cada tipo de widget
	uint8	exist; 			//Indica si tenemos que tener en cuenta el widget
	uint8	existAnt; 		//Variable auxiliar para controlar la existencia del icono.
	uint8 	enable; 		//Variable que indica si el widget est� tipo marca de agua (idle) pero se muestra por pantalla
	uint8 	visible; 		//Indica si el widget es visible
	uint8	posLayer; 		//Indica en que capa del GFX est� situado el widget (para hacer correctamente las transparencias)
	uint8 	needRefresh;	/*Indica si es necesario refrescar la imagen que se muestra en pantalla.
							0:No hay que refrescar 1:Hay que refrescar*/
	uint8	visAnt; 		//Variable auxiliar para controlar la visibilidad del icono en pantalla.
	void (*cbkUpdate)();	//Puntero a la funci�n de actualizaci�n del widget
	void (*cbkRefresh)(); 	//Puntero a la funci�n de refresco del widget
}stWidget;

/*-		Estructura del widget bot�n*/
typedef struct{
	
	uint8	prsRls; 			//Bot�n pulsado o no pulsado: 0=released, 1=press
	uint8	state; 			//Estado en la m�quina de estados del update del bot�n
	uint32 	idIco; 		//Id interno del icono del bot�n
	uint32	idImgPrs; 	//Id para el archivo LUT de la imagen pulsada
	uint32	idImgRls; 	//Id para el archivo LUT de la imagen no pulsada
	uint32	timer; 		//Falta definir como ser� este timer para la pulsaci�n continuada
	stTS	TS; 				//Imagen y area t�ctil del bot�n
	/*Callbbacks del bot�n*/
	void (*cbkPrs)(void*); 	//Callback para el bot�n pulsado
	void (*cbkRls)(void*); 	//Callback para el bot�n no pulsado
	void (*cbkCon)(void*); 	//Callback para la pulsaci�n continuada
	/*Posiciones de las imagenes*/
	uint16	posxImgPrs;	
	uint16	posyImgPrs;
	uint16	posxImgRls;
	uint16	posyImgRls;
	
}stButton;	

/*-		Estructura del widget interruptor*/
typedef struct{
	uint8	prsRls; 		//Interrutor pulsado o no pulsado: 0=released, 1=press
	uint8	onOff; 			//Interruptor on o off: 0=off, 1=on
	uint8	state; 			//Estado en la m�quina de estados del update del interruptor
	uint32 	idIco; 			//Id interno del icono del interruptor
	uint32	idImgOn; 		//Id para el archivo LUT del interruptor on
	uint32	idImgOff; 		//Id para el archivo LUT del interruptor off
	uint32	idImgPrsOn; 	//Id para el archivo LUT al pulsar el interruptor para on
	uint32	idImgPrsOff;	//Id para el archivo LUT al pulsar el interruptor para off
	stTS	TS; 				//Imagen y area t�ctil del interruptor
	/*Callbacks del interruptor*/
	void (*cbkOn)(void*); 		//Callback para el interruptor on
	void (*cbkOff)(void*); 		//Callback para el interruptor off
	/*Posiciones de las imagenes*/
	uint16	posxImgOn;
	uint16	posyImgOn;
	uint16	posxImgOff;
	uint16	posyImgOff;
	uint16	posxImgPrsOn;
	uint16	posyImgPrsOn;
	uint16	posxImgPrsOff;
	uint16	posyImgPrsOff;
}stSwitch;

/*-		Estructura del widget visor de imagen*/
typedef struct{
	uint32	idIco;	//Id interno del icono del visor num�rico
	uint32	idImg;	//Id para el archivo LUT de la imagen a mostrar
	/*Posici�n de la imagen*/
	uint16	posx;
	uint16	posy;
}stImgViewer;



/*-		Estructura del widget visor num�rico*/
typedef struct{
	/*Caracter�sticas de la imagen de fondo del visor num�rico*/
	
	float  numAnter;
	
	uint32	idIcoImgVwr;	//Id interno del icono de la imagen de fondo
	uint8	imgVwrOn;		//Indica si el visor num�rico tiene imagen de fondo: 0=No tiene fondo, 1=Tiene fondo
	uint16	posxImgVwr;		
	uint16	posyImgVwr;
	uint16	wImgVwr;
	uint16	hImgVwr;
	
	uint32	idImgVwr;		//Id para el archivo LUT de la imagen a mostrar en el fondo
	/*Caracter�sticas de los d�gitos del visor num�rico*/
	uint8	posLayerDig;	//Indica en que capa del GFX estan situados los d�gitos (para hacer correctamente las transparencias)
	uint8	iDigit; 		//N�mero de d�gitos del visor
	uint16	sepDig; 		//Distancia entre d�gitos en p�xels
	uint16	wDig;
	uint16	hDig;	
	uint32	idImg[GUInumVimg];	/*Array con los Ids para el archivo LUT de todas las posibles caracteres a mostrar en el visor
								num�rico(set de n�meros del 0-9, el signo menos(-) y el signo de separaci�n decimal( . � ,)*/
	uint32	*idIcoDig;		//Vector con los ids internos de los d�gitos
	uint16	*posxDig;		//Vector con las posiciones x de cada d�gito
	uint16	*posyDig;		//Vector con las posiciones y de cada d�gito
	uint32	*idImgDig;		/*Vector con los ids para el archivo LUT de la imagen que corresponder� a cada d�gito
							para mostrar por pantalla*/
	uint8	*visDig;		//Vector con la visibilidad de cada d�gito
	char	*bufNum;		//Array auxiliar de caracteres para colocar correctamente el d�gito en pantalla
}stNumViewer;

typedef int (*fCallback)(void);


/*-		Estructura del widget ventana emergente*/
typedef struct{
	
	uint8	prsState;		/*Estado de la pulsaci�n: 0=no pulsado, 1=pulsado fuera del pop-up, 2=pulsado en el bot�n que abre la
	 	 	 	 	 	 	 ventana, 3=pulsado dentro del pop-up pero no de una opci�n y 4=pulsado en una opci�n*/
	uint8	prsOption;		//Opci�n pulsada de la ventana emergente
	
	uint8	state; 			//Estado en la m�quina de estados del update de la ventana emergente

	/*Vector con la lista de widgets*/
	
	uint32 numWidgets;
	
	uint32 numWidgetsDisable;
	
	uint8 PopUpListEnbaleOrDisable; //0 - Disable all 1-Disable list

	uint32 *listaWidgets;   // Puntero con la lista de widgets Pop Up
	
	uint32 *listWidgetsDisable;  // Puntero con la lista de widgets que deshabilita el Pop Up. 
		
	uint32 idWidgetPopUpAnt;   //Variable para guardar si hay algun popUp activo anterior
	
	uint8 enableAnt; //Variable para controlar el estado de habilitaci�n anterior del popUp
	
	uint8 popUpSup; //Variable que indica que hay un popUp por encima de este

}stPopUp;


// Definicion de varialbes CallBacks



/*-		Estructura de las diferentes pantallas de la interfaz*/

typedef struct{
	uint32	iWidget;	//N�mero de widgets de la pantallaGUIconfigInterface
	uint8	iLayers;	//N�mero de capas de la pantalla
	stWidget *pWidget;	//Vector a todos los widgets de la pantalla
}stScreen;

/*-		Estructura de toda la interfaz*/
typedef struct{
	uint8	iScreen;	//N�mero de pantallas de la interfaz
	stScreen *pScreen;	//Vector a las pantallas de la interfaz
}stInterface;


/* - Constantes */
//#define GUIfields 30	//N�mero de todos los campos del vector de widgets
//#define GUIpixColorTscr 0xFF000000

/* -    Listado de errores */
//#define K70_GUI_ERR_BASE	0x0400
//extern const uint16 K70_GUI_ERR_OK;
//extern const uint16 K70_GUI_ERR_ALLOC_SCREENS;
//extern const uint16 K70_GUI_ERR_ALLOC_WIDGETS;
//extern const uint16 K70_GUI_ERR_ALLOC_BUTTON;
//extern const uint16 K70_GUI_ERR_ALLOC_SWITCH;
//extern const uint16 K70_GUI_ERR_ALLOC_IMG_VIEWER;
//extern const uint16 K70_GUI_ERR_ALLOC_NUM_VIEWER;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS_IMG;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS_VIS;
//extern const uint16 K70_GUI_ERR_ALLOC_NUM_BUFFER;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS_POS_X;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS_POS_Y;
//extern const uint16 K70_GUI_ERR_ALLOC_POP_UP;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS_IMG;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS_POS_X;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS_POS_Y;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS_CBKS;
//extern const uint16 K70_GUI_ERR_CANNOT_FIND_WIDGET;


/* - Variables globales (NUNCA) */
//debug
//uint8 GUIerrors; //Variable que nos permite mostrar por el hyperterminal los posibles errores de la libreria
//double GUInumVnum; //debug


/* - Funciones */
/*
 * Funci�n GUIinit
 * Descripci�n:
 *      Inicializa la librer�a para su uso. Debe ser la primera funci�n en ser llamada antes de ninguna otra. 
 *      Esta funci�n inicializa las variables internas, inicializa la librer�a del driver gr�fico K70_GFX.h e inicializa el
 *      touch screen con el bus spi pasado por el usuario.
 *      En el caso de la inicializaci�n de la libreria GFX es necesario:
 *      1) Pasarle los punteros a los archivos de imagenes. 
 *      2) Seleccionar si se quiere pintar el fondo con un color s�lido y que se repinte el fondo de este color cada vez que 
 *      se borra una imagen de la pantalla. Esta opci�n est� pensada para el caso que no se disponga de una imagen de fondo
 *      que ocupe toda la pantalla. Si seleccionamos un color de fondo, pero no ponemos la variable de selecci�n a 1, no se 
 *      actualizara el color de fondo de pantalla aunque le pasemos un color.
 *      3)  Configurar la intensidad del back light del LCD mediante PWM.
 * Par�metros:
 * 		1)imgType - uint8:
 * 				Tipo de la compresi�n de las imagenes: por ahora solo hay un tipo de compresi�n de imagen: CCN.
 * 				0:Ning�n tipo
 * 				1:CCN
 * 		2)ptrPackCCN - uint8*:
 * 				Puntero al pack CCN, donde est�n todas las im�genes comprimidas.
 * 		3)ptrPackLUT - uint8*:
 * 				Puntero al pack LUT, donde est� el �ndice de las imagenes.
 * 		4)bBottomRef uint8:
 * 				Variable que define si se quiere poner un color de fondo:
 * 					0: No se quiere pintar el fondo.
 * 					1: Se quiere pintar el fondo de un color s�lido.
 * 		5)colorBottomRef uint32:
 * 				Color del fondo. Formato: 0xAARRGGBB.
 * 		6)bright - uint32:
 * 		 		Intensidad del back light. Formato: de 0x00(min) a 0xFF(max).
 * 		7)spifd - MQX_FILE_PTR*:
 * 				Bus spi creado por el usuario para la comunicaci�n con la touch screen. Hay un ejemplo de la creaci�n de 
 * 				este bus en la funci�n DemoGUIspi() del programa de demo DemoCoreK70_GUI
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 *      K70_GFX_ERR_ALLOC_SCREEN: Libreria GFX: No es posible alojar la pantalla.
 *      K70_GFX_ERR_IMG_TYPE: Libreria GFX: Tipo de imagenes incorrecto.
 */


//uint16 GUIinit(uint8 imgType,uint8 *ptrPackCCN,uint8 *ptrPackLUT,uint8 bBottomRef, uint32 colorBottomRef,uint8 bright, tK70_DDRdataPtr DDRdata);//TSPIMQX_FILE_PTR *spifd);


//void TSPIGUItscrUpdate(stPosTS posTS);


//uint16 GUIconfigSPI(void);






//uint16 GUIconfigSPI(uint32 prphBaseAddr,void **tscrSPIfun,uint8 cs, uint8 attribSet);

/*
 * Funci�n GUIconfigInterface
 * Descripci�n:
 *      Funci�n que configura toda la interfaz. Primero reserva el espacio para todas las pantallas y los widgets de la interfaz,
 *      seguidamente rellena la estructura de los widgets ordenados por capas y reserva espacio para la estructura especifica de
 *      cada widget segun el tipo de widget (boton: stButton, interruptor: stSwitch,...) y tambi�n la rellena con los widgets
 *      pasados en el par�metro del vector de la interfaz.
 *      Esta funci�n configura toda la interfaz pero no muestra a�n nada por pantalla, hay que llamar a la funci�n GUIinitScreen()
 *      para empezar a mostrar los widgets por pantalla.   
 * Par�metros:
 * 		1)interface - uint32[][GUIfields]:
 * 				Array de 2 dimensiones con todos los datos de la interfaz. El array tiene tantas filas como widgets tiene la 
 * 				interfaz y tantas columnas como el n�mero m�ximo de campos del widget con m�s campos, este parametro est� definido
 * 				como constante en los defines de esta libreria con el nombre de GUIfields.
 * 		2)screens - uint8:
 * 				N�mero de pantallas diferentes de la interfaz.
 * 		3)widgets - uint32:
 * 				N�mero de widgets totales de la interfaz.
 * 		4)numLayers - uint8[]:
 * 				N�mero de capas en cada pantalla, por orden de pantallas.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 *      K70_GUI_ERR_ALLOC_SCREENS: No es posible alojar las pantallas.
 *      K70_GUI_ERR_ALLOC_WIDGETS: No es posible alojar los widgets.
 *      K70_GUI_ERR_ALLOC_BUTTON: No es posible alojar la estructura del boton.
 *      K70_GUI_ERR_ALLOC_SWITCH: No es posible alojar la estructura del interruptor.
 *      K70_GUI_ERR_ALLOC_IMG_VIEWER: No es posible alojar la estructura del visor de imagen.
 *      K70_GUI_ERR_ALLOC_NUM_VIEWER: No es posible alojar la estructura del visor numerico.
 *      K70_GUI_ERR_ALLOC_POP_UP: No es posible alojar la estructura de la ventana emergente.
 *      K70_GUI_ERR_ALLOC_DIGITS: No es posible alojar los digitos del visor.
 *      K70_GUI_ERR_ALLOC_DIGITS_IMG: No es posible alojar las imagenes de los digitos del visor.
 *      K70_GUI_ERR_ALLOC_DIGITS_VIS: No es posible alojar la visibilidad de los digitos del visor.
 *      K70_GUI_ERR_ALLOC_NUM_BUFFER: No es posible alojar el buffer para el numero del visor.
 *      K70_GUI_ERR_ALLOC_DIGITS_POS_X: No es posible alojar las posiciones x de los digitos del visor.
 *      K70_GUI_ERR_ALLOC_DIGITS_POS_Y: No es posible alojar las posiciones y de los digitos del visor.
 *      K70_GUI_ERR_ALLOC_OPTIONS: No es posible alojar las opciones de la ventana emergente.
 *      K70_GUI_ERR_ALLOC_OPTIONS_POS_X: No es posible alojar las posiciones x de las opciones de la pantalla emergente.
 *      K70_GUI_ERR_ALLOC_OPTIONS_POS_Y: No es posible alojar las posiciones y de las opciones de la pantalla emergente.
 *      K70_GUI_ERR_ALLOC_OPTIONS_CBKS: No es posible alojar los callbacks de las opciones de la ventana emergente.
 *      
 */

//uint16 GUIconfigInterface(const uint32 interface[][GUIfields],uint8 screens,uint32 widgets,uint8 *numLayers);

/*
 * Funci�n GUIinitScreen
 * Descripci�n:
 *      Funci�n que inicia la pantalla indicada por el usuario mostrandola por pantalla. Los pasos que sigue esta funci�n son los
 *      siguientes:
 *      1) Si hay alguna pantalla no finalizada mostrandose, la finaliza.
 *      2) Inicia la escena del GFX con las capas que tiene la pantalla.
 *      3) Cuenta los widgets que hay en cada capa y a�ade la capa a la escena del GFX.
 *      4) Una vez ha a�adido las capas, a�ade los widgets de todas las capas.
 *      5) Refresca la pantalla con toda la informaci�n ya configurada.   
 * Par�metros:
 * 		1)screen - uint8:
 * 				Pantalla que se quiere mostrar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 *      
 *      
 */
//uint16 GUIinitScreen(uint8 screen);

/*
 * Funci�n GUIfinishScreen
 * Descripci�n:
 * 		Finaliza la pantalla actual borrando todos los widgets que se muestran por pantalla, finalizando la escena en el GFX.
 * 		As� deja la pantalla sin nada preparada para iniciar otra pantalla o para finalizar la libreria GUI.  
 * Par�metros:
 * 		1)screen - uint8:
 * 				Pantalla que se quiere finalizar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 *      K70_GFX_ERR_ICON_NOT_FOUND: Icono no encontrado.
 *      K70_GFX_ERR_IMG_TYPE: Tipo de imagenes incorrecto.
 *      K70_GFX_ERR_ICO_POSITION: Posici�n del icono fuera de los m�rgenes de la pantalla.
 *      K70_GFX_ERR_LAYER_NOT_FOUND: Capa no encontrada.
 *      K70_GFX_ERR_ICO_POSITION: Posici�n del icono fuera de los m�rgenes de la pantalla.
 */
//uint16 GUIfinishScreen(uint8 screen);

/*
 * Funci�n GUIupdate
 * Descripci�n:
 * 		Actualiza el estado de los widgets que est�n en la pantalla actual (no tienen porque estar mostrandose
 * 		en la pantalla fisicamente).
 * Par�metros:
 * 		No requiere par�metros.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIupdate(void);

/*
 * Funci�n GUIrefresh
 * Descripci�n:
 * 		Funci�n que permite refrescar la pantalla, si el par�metro de entrada forceRfsh est� a 0 s�lo refresca los widgets 
 * 		que estan en la pantalla actual que necesiten refresco, si est� a 1 se fuerza el refresco de toda la pantalla aunque
 * 		no haya ning�n cambio.
 * Par�metros:
 * 		1)forceRfsh - uint8:
 * 				Indica si se quiere forzar el refresco de toda la pantalla: 
 * 					0:Refresco de los widgets que necesitan refresco. 
 * 					1:Refresco de toda la pantalla.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIrefresh(uint8 forceRfsh);

/*
 * Funci�n GUIbackL
 * Descripci�n:
 *      Configura la intensidad del back light del LCD mediante PWM.
 * Par�metros:
 * 		 1)bright - uint32:
 * 		 		Intensidad del back light. Formato: de 0x00(min) a 0xFF(max).
 * Retorno:
 *        Error - uint16:
 *				Devuelve el c�digo de error.
 * Errores:
 *      K70_GFX_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIbackL(uint8 bright);

/*
 * Funci�n GUIfinish
 * Descripci�n:
 * 		Se debe llamar a esta funci�n para finalizar la librer�a. Debe ser la �ltima funci�n del programa.
 * 		Si no habiamos finalizado anteriormente la pantalla actual, la finalizamos para borrar los widgets de la pantalla.
 * 		Finalizamos tambien la libreria GFX: En el caso de que no se haya finalizado la escena, se finaliza, se
 * 		apaga el backlight y el LCD, se libera la memoria de los buffers de la pantalla y finaliza la libreria CCN.
 * 		Por �timo se liberan las memorias reservadas de toda la interfaz.
 * Par�metros:
 *      No requiere par�metros.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIfinish(tK70_DDRdataPtr DDRdata);

/*
 * Funci�n GUIsetWidgetExistance
 * Descripci�n:
 * 		Permite configurar la existencia de un widget. Si el widget no existe no se tendr� en cuenta ni en la actualizaci�n de
 * 		estado (GUIupdate) ni en el refresco de pantalla (GUIrefresh).
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget del que se quiere cambiar la existencia.
 * 		2)exist - uint8:
 * 				Par�metro que controla la existencia.
 * 					0: El widget pasa a no existir.
 * 					1: El widgtet pasa a existir.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIsetWidgetExistance(uint32 id,uint8 exist);

/*
 * Funci�n GUIsetWidgetVisibility
 * Descripci�n:
 * 		Permite configurar la visibilidad de un widget. Si el widget no est� visible se tendr� en cuenta en la actualizaci�n de
 * 		estado (GUIupdate) pero no se tendr� en cuenta en el refresco de pantalla (GUIrefresh).
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget del que se quiere cambiar la existencia.
 * 		2)vis - uint8:
 * 				Par�metro que controla la visibilidad.
 * 					0: Widget no visible.
 * 					1: Widget visible.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIsetWidgetVisibility(uint32 id,uint8 vis);


/*
 * Funci�n GUIsetWidgetEnable
 * Descripci�n:
 * 		Permite configurar la habilitacion  de un widget. Si el widget no est� visible se tendr� en cuenta en la actualizaci�n de
 * 		estado (GUIupdate) pero no se tendr� en cuenta en el refresco de pantalla (GUIrefresh).
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget del que se quiere cambiar la existencia.
 * 		2)vis - uint8:
 * 				Par�metro que controla la visibilidad.
 * 					0: Widget no habilitado
 * 					1: Widget habiltiado.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */

//uint16 GUIsetWidgetEnable(uint32 id,uint8 enable);


/* - 	Funciones p�blicas del widget bot�n*/
/*
 * Funci�n GUIsetButonPosition
 * Descripci�n:
 * 		Permite configurar la posici�n del bot�n. Se puede cambiar la posici�n de la imagen pulsada, la de la imagen no pulsada y
 * 		el area t�ctil.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget bot�n del que se quiere cambiar la posici�n.
 * 		2)posxImgPrs - uint16
 * 				Posici�n x de la imagen pulsada.
 * 		3)posyImgPrs - uint16
 * 				Posici�n y de la imagen pulsada.
 * 		4)posxImgRls - uint16
 * 				Posici�n x de la imagen no pulsada.
 * 		5)posyImgRls - uint16
 * 				Posici�n y de la imagen no pulsada.
 * 		6)areaTS - GUIstRect:
 * 				Estructura rectangulo con la posici�n x, posici�n y, el ancho y el alto.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 *      
 *      
 *      
 */




//uint16 GUIsetButonPosition(uint8 id,uint16 posxImgPrs,uint16 posyImgPrs,uint16 posxImgRls,uint16 posyImgRls,GUIstRect areaTS);

/*
 * Funci�n GUIsetImgButton
 * Descripci�n:
 * 		Permite configurar la imagen del visor de imagen.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget visor de imagen del que se quiere cambiar la posici�n.
 * 		2)idImg - uint32
 * 				Id de la imagen que queremos mostrar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIsetImgButton(uint32 id,uint32 idImg, uint8 presOrRel);

//uint16 GUIsetTscImgButton(uint32 id,uint32 idImg);
/* - 	Funciones p�blicas del widget interruptor*/
/*
 * Funci�n GUIsetSwitchPosition
 * Descripci�n:
 * 		Permite configurar la posici�n del bot�n. Se puede cambiar la posici�n de la imagen on, la de la imagen off,
 * 		la de la imagen pulsada on, la de la imagen pulsada off y el area t�ctil.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget interruptor del que se quiere cambiar la posici�n.
 * 		2)posxImgOn - uint16
 * 				Posici�n x de la imagen on
 * 		3)posyImgOn - uint16
 * 				Posici�n y de la imagen on
 * 		4)posxImgOff - uint16
 * 				Posici�n x de la imagen off
 * 		5)posyImgOff - uint16
 * 				Posici�n y de la imagen off
 * 		6)posxImgPrsOn - uint16
 * 				Posici�n x de la imagen pulsada on
 * 		7)posyImgPrsOn - uint16
 * 				Posici�n y de la imagen pulsada on
 * 		8)posxImgPrsOff - uint16
 * 				Posici�n x de la imagen pulsada off
 * 		9)posyImgPrsOff - uint16
 * 				Posici�n y de la imagen pulsada off	
 * 		10)areaTS - GUIstRect:
 * 				Estructura rectangulo con la posici�n x, posici�n y, el ancho y el alto.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIsetSwitchPosition(uint32 id,uint16 posxImgOn,uint16 posyImgOn,uint16 posxImgOff,uint16 posyImgOff,
//		uint16 posxImgPrsOn,uint16 posyImgPrsOn,uint16 posxImgPrsOff,uint16 posyImgPrsOff, GUIstRect areaTS);
//uint16 GUIsetSwitchImg( uint32 id, uint32 imgOnPrs, uint32 imgOffPrs, uint32 imgOnRls, uint32 imgOffRls);
//uint16 GUIsetSwitchTscImg( uint32 id, uint32 imgTSCR);
//uint16 GUIsetSwitchStatus( uint32 id, uint8 OnOff);

/* - 	Funciones p�blicas del widget visor de imagen*/
/*
 * Funci�n GUIsetImgViewerPosition
 * Descripci�n:
 * 		Permite configurar la posici�n del visor de imagen.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget visor de imagen del que se quiere cambiar la posici�n.
 * 		2)posx - uint16
 * 				Posici�n x del visor de imagen
 * 		3)posy - uint16
 * 				Posici�n y del visor de imagen
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIsetImgViewerPosition(uint32 id,uint16 posx,uint16 posy);

/*
 * Funci�n GUIsetImgViewerImage
 * Descripci�n:
 * 		Permite configurar la imagen del visor de imagen.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget visor de imagen del que se quiere cambiar la posici�n.
 * 		2)idImg - uint32
 * 				Id de la imagen que queremos mostrar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIsetImgViewerImage(uint32 id,uint32 idImg);

/* - 	Funciones p�blicas del widget visor num�rico*/
/*
 * Funci�n GUIsetNumViewerPosition
 * Descripci�n:
 * 		Permite configurar la posici�n del visor num�rico.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget visor num�rico del que se quiere cambiar la posici�n.
 * 		2)posxImgVwr - uint16
 * 				Posici�n x del visor num�rico.
 * 		3)posyImgVwr - uint16
 * 				Posici�n y del visor num�rico.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIsetNumViewerPosition(uint32 id,uint16 posxImgVwr,uint16 posyImgVwr);

/*
 * Funci�n GUIsetNumViewerNum
 * Descripci�n:
 * 		Permite configurar el n�mero del visor num�rico.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget visor num�rico del que se quiere cambiar el n�mero.
 * 		2)num - double
 * 				N�mero que queremos mostrar.
 * 		3)dec - uint8
 * 				N�mero de decimales que tiene el n�mero a mostrar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */
//uint16 GUIsetNumViewerNum(uint32 id,float num,uint8 dec);


//uint16 GUIsetNumViewerNum2(uint32 id, float num,uint8 dec,uint8 visb);

//void float_to_string(float f, char r[], uint8 dec);

//int n_tu(int number, int count);


/* - 	Funciones p�blicas del widget ventana emergente*/
/*
 * Funci�n GUIsetPopUpOptionsImages
 * Descripci�n:
 * 		Permite configurar las im�genes de las opciones de la ventana emergente.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget ventana emergente del que se quiere cambiar la imagen de las opciones.
 * 		2)idImg - uint32*:
 * 				Vector a los ids de las im�genes de las opciones.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */





/*
 * Funci�n GUIsetPopUpCallbacks
 * Descripci�n:
 * 		Permite configurar los callbacks de las opciones de la ventana emergente.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget ventana emergente del que se quiere cambiar los callbacks.
 * 		2)cbk - uint32*:
 * 				Vector a los ids de los callbacks de las opciones.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */


/*
 * Funci�n GUIsetPopUpButtonPosition
 * Descripci�n:
 * 		Permite configurar la posici�n del bot�n que despliega la ventana emergente.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget ventana emergente del que se quiere cambiar la posici�n del bot�n.
 * 		2)posxBut - uint16:
 * 				Posici�n x del bot�n.
 * 		3)posyBut - uint16:
 * 				Posici�n y del bot�n.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */


/*
 * Funci�n GUIsetPopUpWindowPosition
 * Descripci�n:
 * 		Permite configurar la posici�n de la ventana emergente.
 * Par�metros:
 *      1)id - uint8:
 * 		 		Id del widget ventana emergente del que se quiere cambiar la posici�n.
 * 		2)posxBut - uint16:
 * 				Posici�n x de la ventana emergente.
 * 		3)posyBut - uint16:
 * 				Posici�n y de la ventana emergente.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el c�digo de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ning�n error.
 */


// Otman : Falta descripcion de cada funcion.

//uint16 GUIsetPopUpWidgets(uint32 id, const uint32 *idWidgets,  uint32 *idWidgetsDisable);

//uint16 GUIsetPopUpWidgets2(uint8 id, uint32 *idWidgets);

//uint16 GUIactivePopUp(uint32 id);

//uint16 GUIdisablePopUp(uint32 id);

//uint16 GUIgetPopUpStatus( uint32 id, uint8 *status);

/* - 	Funcion privada para los dem�s programas de widgets*/
/*
 * Funci�n GUIgetInterface
 * Descripci�n:
 * 		Devuelve la interfaz con la que se est� trabajando.
 * Par�metros:
 *      No requiere par�metros.
 * Retorno:
 *      GUIinterf - stInterface:
 *      		Interfaz con la que se est� trabajando.
 * Errores:
 *      No genera errores.
 */

//stInterface* GUIgetInterface(void);

//stWidget *GUIgetWidget( uint32 id);

#endif /* GUI_H_ */

#include "widgetswrapper.h"

WidgetsWrapper::WidgetsWrapper(QObject *parent)
    : QObject{parent}
{

}

void WidgetsWrapper::changeScreen(EAppGUIscreen screenId)
{
    emit changeScreenSignal(screenId);
}

void WidgetsWrapper::GUIsetNumViewerNum(uint32 id, double num, uint8 dec)
{
    char prova[50];
    float_to_string(num, prova, dec);
    QString qstr(prova);

    switch(id)
    {
    case numVwrTimeHP1: break;
    case numVwrTimeHP2: break;
    case numVwrTimeHP3: break;
    case numVwrTimeHP4: break;
    case numVwrResucctionCountHP1: break;
    case numVwrResucctionCountHP2: break;
    case numVwrResucctionCountHP3: break;
    case numVwrResucctionCountHP4: break;
    case numVwrPopUpRFIDrestTime: break;
    case numVwrPopUpErrHP1: break;
    case numVwrPopUpErrHP2: break;
    case numVwrPopUpErrHP3: break;
    case numVwrPopUpErrHP4: break;
    case numVwrPopUpErrUC: break;
    case numVwrPopUpErrTRTtimeHP1: break;
    case numVwrPopUpErrTRTtimeHP2: break;
    case numVwrPopUpErrTRTtimeHP3: break;
    case numVwrPopUpErrTRTtimeHP4: break;
    case numVwrPopUpCleanHP1: break;
    case numVwrPopUpCleanHP2: break;
    case numVwrPopUpCleanHP3: break;
    case numVwrPopUpCleanHP4: break;
    case numVwrPopUpCleanNumCancelHP1: break;
    case numVwrPopUpCleanNumCancelHP2: break;
    case numVwrPopUpCleanNumCancelHP3: break;
    case numVwrPopUpCleanNumCancelHP4: break;
    case numVwrPantallaCalc:        setCalcNumber(qstr); break;
    case numVwrModeloMaqCfg:        setConfModel(qstr); break;
    case numVwrVersionSoftwareCfg:  setConfVersion(qstr); break;
    case numVwrPaginaSATscreen: break;
    case numVwr1: break;
    case numVwr2: break;
    case numVwr3: break;
    case numVwr4: break;
    case numVwr5: break;
    case numVwr6: break;
    case numVwr7: break;
    case numVwr8: break;
    case numVwr9: break;
    case numVwr10: break;
    case numVwr11: break;
    case numVwr12: break;
    case numVwr13: break;
    case numVwr14: break;
    case numVwr15: break;
    case numVwr16: break;
    case numVwr17: break;
    case numVwr18: break;
    case numVwr19: break;
    case numVwr20: break;
    case numVwr21: break;
    case numVwr22: break;
    case numVwr23: break;
    case numVwr24: break;
    case numVwr25: break;
    case numVwr26: break;
    case numVwr27: break;
    case numVwr28: break;
    case numVwrError1: break;
    case numVwrError2: break;
    case numVwrError3: break;
    case numVwrError4: break;
    case numVwrError5: break;
    case numVwrTempAmb: break;
    case numVwrTempBomba: break;
    case numVwrTempRetorno: break;
    case numVwrCaudalRetorno: break;
    case numVwrVtobera: break;
    case numVwrRth: break;
    case numVwrCPI: break;
    case numVwrCaudalRetornoHP1: break;
    case numVwrCaudalRetornoHP2: break;
    case numVwrCaudalRetornoHP3: break;
    case numVwrCaudalRetornoHP4: break;
    case numVwrVacuumHP1: break;
    case numVwrVacuumHP2: break;
    case numVwrVacuumHP3: break;
    case numVwrVacuumHP4: break;
    case numVwrFatigaTime: break;
    case numVwrErrFatiga1: break;
    case numVwrErrFatiga2: break;
    case numVwrErrFatiga3: break;
    case numVwrErrFatiga4: break;
    case numVwrErrFatiga5: break;
    default: /* Do nothing. */ break;
    }
}

void WidgetsWrapper::GUIsetSwitchStatus(uint32 id, uint8 OnOff)
{
    switch (id) {
    case swInitScrAvisos: break;
    case swCtrlPnlTstVacHP1: break;
    case swCtrlPnlTstVacHP2: break;
    case swCtrlPnlTstVacHP3: break;
    case swCtrlPnlTstVacHP4: break;
    case swDotZone0: break;
    case swDotZone1: break;
    case swDotZone2: break;
    case swDotZone3: break;
    case swDotZone4: break;
    case swDotZone5: break;
    case swDotZone6: break;
    case swDotZone7: break;
    case swDotZone8: break;
    case swDotZone9: break;
    case swDotZone10: break;
    case swDotZone11: break;
    case swDotZone12: break;
    case swDotZone13: break;
    case swDotZone14: break;
    case swPopUpTstVacLowLvl: break;
    case swPopUpTstVacMidLvl: break;
    case swPopUpTstVacHighLvl: break;
    case swPopUpRecommInfo: break;
    case swTrtScrAvisos: break;
    case swCalcScrAvisos: break;
    case swCfgResuctionViewer: break;
    case swCfgTemperatureViewer: break;
    case swCfgScrAvisos: break;
    case swLanFrances: break;
    case swLanCastellano: break;
    case swLanIngles: break;
    case swLanItaliano: break;
    case swLanAleman: break;
    case swLanPolaco: break;
    case swLanRuso: break;
    case swLanPortugues: break;
    case swLanChino: break;
    case swLanJapones: break;
    case swLanCoreano: break;
    case swLanScrAvisos: break;
    case swVacuum: break;
    case swFrio: break;
    case swRFID: break;
    case swTestLed: break;
    case swTestLedRGB: break;
    case swFatigueFailBeep: break;
    default: /* Do nothing */ break;
    }
}

QString WidgetsWrapper::calcNumber()
{
    return calcNumberStr;
}

QString WidgetsWrapper::confModel()
{
    return confModelStr;
}

QString WidgetsWrapper::confVersion()
{
    return confVersionStr;
}

void WidgetsWrapper::setCalcNumber(QString txt)
{
    if (txt == calcNumberStr)
    {
        return;
    }
    else
    {
        calcNumberStr = txt;
        emit calcNumberChanged(calcNumberStr);
    }
}

void WidgetsWrapper::setConfModel(QString txt)
{
    if (txt == confModelStr)
    {
        return;
    }
    else
    {
        confModelStr = txt;
        emit confModelChanged(confModelStr);
    }
}

void WidgetsWrapper::setConfVersion(QString txt)
{
    if (txt == confVersionStr)
    {
        return;
    }
    else
    {
        confVersionStr = txt;
        emit confVersionChanged(confVersionStr);
    }
}

void WidgetsWrapper::float_to_string(double f, char r[], uint8 dec)
{
    long long int length, length2, i, iNumber, coma_position, sign, coma_space;
    double fNumber2, fNumber_in;

    coma_space = 1;		//espacio reservado para la coma
    sign = -1;   		//inicialización de la variable?
    if (f < 0)			//Si el valor es negativo
    {
        sign = '-';		//asignamos al signo el número del caracter menos
        f *= -1;		//ponemos positivo el número
    }

    fNumber_in = f;		//Numero introducido
    fNumber2 = f;		//guardamos el valor como float
    iNumber = f;			//casteamos el valor como long long int, eliminando los decimales
    length = 0;  		//inicialización de la variable de la longitud del número previo a la coma
    length2 = 0;		//inicialización de la variable de la lontitud del número posterior a la coma


    while( (fNumber2 - (float)iNumber) != 0.0 && !((fNumber2 - (float)iNumber) < 0.0) )		//le restamos al númeor con decimales la parte entera y se comprueba si vale 0 y si es mayor que 0.0
    {
        fNumber2 = f * (n_tu(10.0, length2 + 1));		//desplazamos a la izquierda de la coma el número (28.47 --> 284.7) multipicandolo por 10.
        iNumber = fNumber2;								//actualizamos los valores para volver a comprobar en la condición del while si el número se ha quedado sin decimales

        length2++;										//control del número de decimales
    }

    /* Calculate length decimal part */
    for (length = (f >= 1) ? 0 : 1; f >= 1; length++)	//Bucle empleado para el calculo de la longitud de la parte entera del número
        f /= 10;

    coma_position = length;						//asignamos la posición a la coma
    if (length2 > 0) length += coma_space;      // If there are digits in the decimal part, add the comma length.
    length = length + dec;			//calculamos la longitud total con la parte entera, la decimal
    iNumber = fNumber_in * (n_tu(10.0, dec));		//calculamos el número completo tomando la parte decimal como entera (24.95 --> 2495)
    if (sign == '-')							//En caso de que tengamos signo negativo
    {
        length++;								//incrementamos la longitud de caracteres
        coma_position++;						//y desplazamos la posición de la coma
    }

    for (i = length; i >= 0 ; i--)						//Recorremos el vector de caracteres desde el valor superior (la longitud completa del número)
    {
        if (i == (length))				r[i] = '\0';	//Para indicar el final del número
        else if(i == (coma_position))	r[i] = '.';		//colocar la coma
        else if(sign == '-' && i == 0)	r[i] = '-';		//colocar el signo
        else
        {
            r[i] = (iNumber % 10) + '0';					//sacar el número a representar en la posicion indicada
            iNumber /=10;								//actualizando el número quitando el ya guardado para representar
        }
    }
}

int WidgetsWrapper::n_tu(int number, int count)
{
    int result = 1;				//Si el contador directamente es 0 el resultado devuelto será 1
    while(count-- > 0)			//mientras que el contador sea superior a 0. Además se va reduciendo la cuenta a cada vuelta
        result *= number;		//se acumula el número pasado por parametro

    return result;				//se devuelve el acumulado
}

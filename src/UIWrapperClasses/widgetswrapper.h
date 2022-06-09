#ifndef WIDGETSWRAPPER_H
#define WIDGETSWRAPPER_H

#include <QObject>
#include "AppGUI/AppGuiInterfaceStructure.h"

class WidgetsWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString calcNumber READ calcNumber NOTIFY calcNumberChanged)
    Q_PROPERTY(QString confModel READ confModel NOTIFY confModelChanged)
    Q_PROPERTY(QString confVersion READ confVersion NOTIFY confVersionChanged)

public:
    explicit WidgetsWrapper(QObject *parent = nullptr);

    // Widgets data getters and setters
    QString calcNumber();
    QString confModel();
    QString confVersion();
    void setCalcNumber(QString txt);
    void setConfModel(QString txt);
    void setConfVersion(QString txt);

    void changeScreen(EAppGUIscreen screenId);

    // Treatment area selection functions
    void bodyZoom(bool zoomed);
    void bodyGenderSelect(EAppGUIbodys gender);
    void bodyAreaSelect(EAppGUIfullBodyAreas area);
    void dotZoneAssignHp(uint8 dot, EAppGUI_HPsIDs hpIndex);
    void dotZoneSelect(uint8 dot, bool isSelected);

    // Widgets update functions. Used by the application
    void GUIsetNumViewerNum(uint32 id, double num, uint8 dec);
    void GUIsetSwitchStatus( uint32 id, uint8 OnOff);
    uint16 GUIsetWidgetVisibility(uint32 id,uint8 vis);
    uint16 GUIsetWidgetEnable(uint32 id,uint8 enable);
    void GUIsetImgViewerPosition(uint32 id,uint16 posx,uint16 posy);


signals:
    void changeScreenSignal(EAppGUIscreen screenId);

    // Widgets visibility signals

    void infoSwitchVisibilityChanged(bool newVisibility);
    void returnButtonVisibilityChanged(bool newVisibility);

    // Widgets enabled signals
    void infoSwitchEnabled(bool enable);
    void returnButtonEnabled(bool enable);

    // Text widgets update signals
    void calcNumberChanged(QString text);
    void confModelChanged(QString text);
    void confVersionChanged(QString text);

    // Switches update signals

    // Main menu
    void mainMenuOpened(bool menuOpened);
    void mainMenuEnabled(bool menuEnabled);

    // Body areas
    void bodyZoomed(bool zoomed);
    void bodyGenderSelected(EAppGUIbodys gender);
    void bodyAreaSelected(EAppGUIfullBodyAreas area);

    // Dot zones full body
    void trtDotFullBodyVisibilityChanged(EAppGUI_HPsIDs hpIndex, bool newVisibility);
    void trtDotFullBodyPositionChanged(EAppGUI_HPsIDs hpIndex, uint32 posX, uint32 posY);

    // Zoomed body dots
    void dotZoneEnabled(uint32 id, bool enable);
    void dotZoneHpAssigned(uint8 dot, EAppGUI_HPsIDs hpIndex);
    void dotZoneSelected(uint8 dot, bool isSelected);

private:
    void float_to_string(double f, char r[], uint8 dec);
    int n_tu(int number, int count);


    // TEXT WIDGETS DATA

    // Calculator screen
    QString calcNumberStr;

    // Configuration screen
    QString confModelStr;
    QString confVersionStr;
};

#endif // WIDGETSWRAPPER_H

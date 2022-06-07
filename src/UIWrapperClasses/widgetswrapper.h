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

    // Widgets update functions. Used by the application
    void GUIsetNumViewerNum(uint32 id, double num, uint8 dec);
    void GUIsetSwitchStatus( uint32 id, uint8 OnOff);


signals:
    void changeScreenSignal(EAppGUIscreen screenId);

    // Text widgets update signals
    void calcNumberChanged(QString text);
    void confModelChanged(QString text);
    void confVersionChanged(QString text);

    // Switches update signals

    // Main menu
    void mainMenuOpened(bool menuOpened);
    void mainMenuEnabled(bool menuEnabled);

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

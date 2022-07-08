cmake_minimum_required(VERSION 3.18)

project(DefineUIProjectApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Gui Qml Quick)
qt_add_executable(DefineUIProjectApp
    src/main.cpp
    src/Callback/cbk.h
    src/Callback/cbk.cpp
    src/UIWrapperClasses/callbackwrapper.h
    src/UIWrapperClasses/callbackwrapper.cpp
    src/UIWrapperClasses/widgetswrapper.h
    src/UIWrapperClasses/widgetswrapper.cpp
    src/GPRS/AppGPRS.h
    src/GPRS/AppGPRS.cpp
    src/AppGUI/AppGUI.h
    src/AppGUI/AppGUI.cpp
    src/AppGUI/K70_GUI.h
    src/AppGUI/AppGuiInterfaceStructure.h
    src/AppGUI/AppGuiInterfaceStructure.cpp
    src/Perifericos/HPcryo.h
    src/Perifericos/HPcryo.cpp
    src/RFID/RFID.h
    src/RFID/RFID.cpp
    src/AppLOG/AppLOG.h
    src/AppLOG/AppLOG.cpp
    src/UART/UART.h
    src/UART/UART.cpp
    src/Ticks/Ticks.h
    src/Ticks/Ticks.cpp
    src/Error/gestionError.h
    src/Error/gestionError.cpp
    src/Expansora/Expansora.h
    src/Expansora/Expansora.cpp
    src/Buzzer/Buzzer.h
    src/Buzzer/Buzzer.cpp
    src/BOOT/boot.h
    src/BOOT/boot.cpp
    src/RTC/RTC.h
    src/RTC/RTC.cpp
)

qt_add_resources(DefineUIProjectApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(DefineUIProjectApp PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Qml
)

target_include_directories(DefineUIProjectApp PUBLIC
    $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}/src>)
target_include_directories(DefineUIProjectApp PUBLIC
    $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}/Generated_Code>)

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)


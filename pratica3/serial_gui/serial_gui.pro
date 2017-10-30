TEMPLATE = app
TARGET = serial_gui

QT = core gui widgets serialport

SOURCES += \
    main.cpp \
    serial/serial.cpp \
    gui/mainwindow.cpp \
    gui/tabs/generaltab.cpp \
    gui/tabs/musictab.cpp \
    gui/tabs/teachintab.cpp \

HEADERS += \
    serial/serial.h \
    gui/mainwindow.h \
    gui/tabs/generaltab.h \
    gui/tabs/musictab.h \
    gui/tabs/teachintab.h \


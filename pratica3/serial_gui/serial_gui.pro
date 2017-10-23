TEMPLATE = app
TARGET = serial_gui

QT = core gui widgets serialport

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    serial.cpp

HEADERS += \
    mainwindow.h \
    serial.h

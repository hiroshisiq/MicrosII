#include "serial.h"
#include <QtSerialPort/QSerialPort>
#include <iostream>

#define serialPortName "ttyACM0"
#define baudRate 9600

Serial::Serial() {
    // Create and configure serial port
    _serialPort.setPortName(serialPortName);
    _serialPort.setBaudRate(baudRate, QSerialPort::AllDirections);

    // Open serial port in read/write mode
    if (!_serialPort.open(QIODevice::ReadWrite)) {
        std::cout << "Error while open port\n";
    }
}

Serial::~Serial() {
    _serialPort.close();
}

QTextStream cinput(stdin);
QTextStream coutput(stdout);

void Serial::readPort() {
    QByteArray readData;

    while (_serialPort.waitForReadyRead(75)) {
        readData.append(_serialPort.readAll());
    }

    coutput << readData;
}

void Serial::writePort(const QByteArray &writeData) {
    _serialPort.write(writeData);
}

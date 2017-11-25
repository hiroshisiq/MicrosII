#ifndef SERIAL_H
#define SERIAL_H

#include <QCoreApplication>
#include <QtCore/QDebug>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Serial {
public:
    Serial();
    ~Serial();

    void readPort();
    void readPort(QByteArray* readData);
    void writePort(const QByteArray &writeData);

private:
    QSerialPort _serialPort;
};

#endif // SERIAL_H

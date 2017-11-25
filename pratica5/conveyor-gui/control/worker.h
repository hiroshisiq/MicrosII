#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <serial/serial.h>
#include <gui/mainwindow.h>

class Worker : public QObject {
    Q_OBJECT
private:
    Serial* _serial;
    MainWindow* _main;
    Observer* _b;

public:
    void setSerial(Serial* serial) { _serial = serial; }
    void setMainWindow(MainWindow* main) { _main = main; }
    void setObserver(Observer* b) { _b = b; }

public slots:
    void doWork();

signals:
    void resultReady();
};

#endif // WORKER_H

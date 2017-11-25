#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

#include <control/worker.h>
#include <serial/serial.h>
#include <gui/mainwindow.h>

class Controller : public QObject {
    Q_OBJECT
    QThread workerThread;

public:
    Controller(Serial* serial, MainWindow* main, Observer* b);
    ~Controller();

public slots:
    void handleResults();

signals:
    void operate();
};

#endif // CONTROLLER_H

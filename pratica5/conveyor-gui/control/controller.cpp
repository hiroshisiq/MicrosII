#include "controller.h"

Controller::Controller(Serial *serial, MainWindow *main, Observer *b) {
    // Create a worker
    Worker *worker = new Worker;
    worker->moveToThread(&workerThread);

    // Configure
    worker->setSerial(serial);
    worker->setMainWindow(main);
    worker->setObserver(b);

    // Connect signals and slots
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Controller::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &Controller::handleResults);
    //connect(worker, &Worker::delay, this, &Controller::delay);

    // Start thread
    workerThread.start();
}

Controller::~Controller()  {
    workerThread.quit();
    workerThread.wait();
}

void Controller::handleResults() {
    // [TODO]
}


#include "worker.h"
#include <unistd.h>

void Worker::doWork() {
    while(true) {
        // Send information
        if(_serial != NULL) {
            _serial->writePort(this->getInfoToSend());
        }

        // Read information
        handleReceivedInfo();

        // Update gui
        if(_main != NULL) {
            _main->updateInfo();
        }

        // Wait 100ms
        usleep(100*1000);
    }

    emit resultReady();
}

QByteArray Worker::getInfoToSend() {
    // Byte code
    // | 0  | 1  | 2  | 3   | 4  | 5  | 6  | 7  |
    // | NS | TS | RM | RNM | RL | P  | -  | -  |
    // Where:
    // NS = normal start
    // TS = test start
    // RM = reject metal
    // RNM = reject non-metal
    // RL = right or left (true means left)
    // P = activate piston

    // Generate byte
    char info = 0x00;

    // Set info
    if(Observer::getNormalStart()   ) info |= 0x01;
    if(Observer::getTestStart()     ) info |= 0x02;
    if(Observer::getRejectMetal()   ) info |= 0x04;
    if(Observer::getRejectNonMetal()) info |= 0x08;
    if(Observer::getTurnLeft()      ) info |= 0x10;
    if(Observer::getAdvancePiston() ) info |= 0x20;

    // Return
    return QByteArray(1, info);
}

void Worker::handleReceivedInfo() {
    // Receive information
    QByteArray* info = new QByteArray();
    _serial->readPort(info);

    // Take the last info and ignore the rest
    char lastInfo = 0x00;
    if(!info->isEmpty()) {
        lastInfo = info->at(info->size()-1);
    }

    // Free pointer
    free(info);

    // Set capacitive sensor status
    bool capStatus = (lastInfo & 0x01) == 0x01;
    Observer::setCapSensor(capStatus);

    // Set capacitive sensor status
    bool indStatus = (lastInfo & 0x02) == 0x02;
    Observer::setIndSensor(indStatus);

    // Set capacitive sensor status
    bool optStatus = (lastInfo & 0x04) == 0x04;
    Observer::setOptSensor(optStatus);
}

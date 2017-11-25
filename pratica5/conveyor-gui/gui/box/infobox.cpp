#include "infobox.h"

InfoBox::InfoBox(QGroupBox *parent) : QGroupBox(parent) {
    this->setTitle("Information");

    QVBoxLayout *layout = new QVBoxLayout(this);

    _status = new QLabel("Status: Stop");
    _cap    = new QLabel("Capacitive Sensor: HIGH");
    _ind    = new QLabel("Inductive Sensor:   HIGH");
    _opt    = new QLabel("Optical Sensor:      HIGH");

    layout->addWidget(_status);
    layout->addWidget(_cap);
    layout->addWidget(_ind);
    layout->addWidget(_opt);

    this->setLayout(layout);

}

void InfoBox::updateInfo() {
    // Update status
    if(Observer::getNormalStart() || Observer::getTestStart()) {
        _status->setText(("Status: Running"));
    } else {
        _status->setText(("Status: Stop"));
    }

    // Update Capacitive Sensor
    if(Observer::getCapSensor()) {
        _cap->setText(("Capacitive Sensor: HIGH"));
    } else {
        _cap->setText(("Capacitive Sensor: LOW "));
    }

    // Update Inductive Sensor
    if(Observer::getIndSensor() == true) {
        _ind->setText(("Inductive Sensor:   HIGH"));
    } else {
        _ind->setText(("Inductive Sensor:   LOW "));
    }

    // Update Optical Sensor
    if(Observer::getOptSensor() == true) {
        _opt->setText(("Optical Sensor:      HIGH"));
    } else {
        _opt->setText(("Optical Sensor:      LOW "));
    }
}

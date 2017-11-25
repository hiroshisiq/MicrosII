#include "optionsbox.h"

OptionsBox::OptionsBox(QGroupBox *parent) : QGroupBox(parent) {
//  this->setGraphicsEffect();
    this->setTitle("Options");

    QVBoxLayout *layout = new QVBoxLayout(this);

    _rejectMetalCB    = new QCheckBox("Reject Metal"    , this);
    _rejectNonMetalCB = new QCheckBox("Reject Non-Metal", this);

    layout->addWidget(_rejectMetalCB);
    layout->addWidget(_rejectNonMetalCB);

    this->setLayout(layout);

    // Connect button signal to appropriate slot
    connect(_rejectMetalCB,    SIGNAL (clicked()), this, SLOT (handleMCB()) );
    connect(_rejectNonMetalCB, SIGNAL (clicked()), this, SLOT (handleNMCB()));
}

void OptionsBox::handleMCB() {

    Observer::setCapSensor(true);

    if(_rejectMetalCB->isChecked()) {
        Observer::setRejectMetal(true);
        Observer::setCapSensor(false);
    } else {
        Observer::setRejectMetal(false);
        Observer::setCapSensor(true);
    }
}

void OptionsBox::handleNMCB() {
    if(_rejectNonMetalCB->isChecked()) {
        Observer::setRejectNonMetal(true);
    } else {
        Observer::setRejectNonMetal(false);
    }
}

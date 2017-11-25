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
    connect(_rejectMetalCB,    SIGNAL (stateChanged()), this, SLOT (handleMCB()) );
    connect(_rejectNonMetalCB, SIGNAL (stateChanged()), this, SLOT (handleNMCB()));
}

void OptionsBox::handleMCB() {
    if(_rejectMetalCB->isChecked()) {
        Observer::setRejectMetal(true);
    } else {
        Observer::setRejectMetal(false);
    }
}

void OptionsBox::handleNMCB() {
    if(_rejectNonMetalCB->isChecked()) {
        Observer::setRejectNonMetal(true);
    } else {
        Observer::setRejectNonMetal(false);
    }
}

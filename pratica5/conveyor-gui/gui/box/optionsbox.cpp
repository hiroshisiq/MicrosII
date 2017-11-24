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
}

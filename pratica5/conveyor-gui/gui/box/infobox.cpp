#include "infobox.h"

InfoBox::InfoBox(QGroupBox *parent) : QGroupBox(parent) {
    this->setTitle("Information");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel* a = new QLabel("Status: Stop");
    QLabel* c = new QLabel("Capacitive Sensor: HIGH");
    QLabel* d = new QLabel("Inductive Sensor:   HIGH");
    QLabel* e = new QLabel("Optical Sensor:       HIGH");

    layout->addWidget(a);
    layout->addWidget(c);
    layout->addWidget(d);
    layout->addWidget(e);

    this->setLayout(layout);

}

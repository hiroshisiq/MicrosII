#include "musictab.h"
#include <QGridLayout>

MusicTab::MusicTab() {
    QGridLayout *layout = new QGridLayout(this);
    layout->setVerticalSpacing(50);

    // Create buttons
    _playIM = new QPushButton("Imperial March (Star Wars)");
    _playIM->setMinimumHeight(90);
    _playSA = new QPushButton("Still Alive (Portal)");
    _playSA->setMinimumHeight(90);

    // Add buttons
    layout->addWidget(_playIM,0,0);
    layout->addWidget(_playSA,1,0);

    // Set the layout with all buttons to this widget
    this->setLayout(layout);

    // Connect button signal to appropriate slot
    connect(_playIM, SIGNAL (clicked()), this, SLOT (handlePlayIM()));
    connect(_playSA, SIGNAL (clicked()), this, SLOT (handlePlaySA()));
}

void MusicTab::handlePlayIM() {    
    // Send command
    QString str = "t";
    _serial->writePort(str.toUtf8());
}

void MusicTab::handlePlaySA() {
    // Send command
    QString str = "y";
    _serial->writePort(str.toUtf8());
}

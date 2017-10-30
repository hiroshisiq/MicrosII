#include "generaltab.h"

GeneralTab::GeneralTab(){
    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(20);

    // Add buttons
    for(int j=0; j<2; j++) {
        for(int i=0; i<4; i++) {
            QPushButton *btn1 = new QPushButton();
            _buttons.append(btn1);
            _buttons.at(j*4 + i)->setMinimumHeight(50);
            _buttons.at(j*4 + i)->setMinimumWidth(200);
            layout->addWidget(btn1, i, j);
        }
    }

    // Rename buttons
    renameButtons();

    // Set the layout with all buttons to this widget
    this->setLayout(layout);

    // Connect button signal to appropriate slot
    connect(_buttons.at(0), SIGNAL (clicked()), this, SLOT (handleButton0()));
    connect(_buttons.at(1), SIGNAL (clicked()), this, SLOT (handleButton1()));
    connect(_buttons.at(2), SIGNAL (clicked()), this, SLOT (handleButton2()));
    connect(_buttons.at(3), SIGNAL (clicked()), this, SLOT (handleButton3()));
    connect(_buttons.at(4), SIGNAL (clicked()), this, SLOT (handleButton4()));
    connect(_buttons.at(5), SIGNAL (clicked()), this, SLOT (handleButton5()));
    connect(_buttons.at(6), SIGNAL (clicked()), this, SLOT (handleButton6()));
    connect(_buttons.at(7), SIGNAL (clicked()), this, SLOT (handleButton7()));
}

void GeneralTab::renameButtons() {
    _buttons.at(0)->setText("One step right");
    _buttons.at(1)->setText("Half turn right");
    _buttons.at(2)->setText("One turn right");
    _buttons.at(3)->setText("Five turns right");
    _buttons.at(4)->setText("One step left");
    _buttons.at(5)->setText("Half turn left");
    _buttons.at(6)->setText("One turn left");
    _buttons.at(7)->setText("Five turns left");
}

void GeneralTab::handleButton0() {
    // Send command
    QString str = "1";
    if(_serial != NULL) {
        _serial->writePort(str.toUtf8());
    }
}

void GeneralTab::handleButton1() {
    // Send command
    QString str = "2";
    _serial->writePort(str.toUtf8());
}

void GeneralTab::handleButton2() {
    // Send command
    QString str = "3";
    _serial->writePort(str.toUtf8());
}

void GeneralTab::handleButton3() {
    // Send command
    QString str = "4";
    _serial->writePort(str.toUtf8());
}

void GeneralTab::handleButton4() {
    // Send command
    QString str = "5";
    _serial->writePort(str.toUtf8());
}

void GeneralTab::handleButton5() {
    // Send command
    QString str = "6";
    _serial->writePort(str.toUtf8());
}

void GeneralTab::handleButton6() {
    // Send command
    QString str = "7";
    _serial->writePort(str.toUtf8());
}

void GeneralTab::handleButton7() {
    // Send command
    QString str = "8";
    _serial->writePort(str.toUtf8());
}

QByteArray GeneralTab::toByteArray(QString text) {
    return text.toUtf8();
}

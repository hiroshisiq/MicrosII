#include "mainwindow.h"
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    for(int i=0; i<8; i++) {
        QPushButton *btn1 = new QPushButton();
        _buttons.append(btn1);
        layout->addWidget(btn1);
    }

    renameButtons();

    _label = new QLabel();
    _label->setText("Waiting for commands...");
    _label->setAlignment(Qt::AlignCenter);
    layout->addWidget(_label);

    widget->setLayout(layout);
    setCentralWidget(widget);

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

void MainWindow::renameButtons() {
    _buttons.at(0)->setText("One step right");
    _buttons.at(1)->setText("Half turn right");
    _buttons.at(2)->setText("One turn right");
    _buttons.at(3)->setText("Five turns right");
    _buttons.at(4)->setText("One step left");
    _buttons.at(5)->setText("Half turn left");
    _buttons.at(6)->setText("One turn left");
    _buttons.at(7)->setText("Five turns left");
}

void MainWindow::handleButton0() {
    // Send command
    QString str = "1";
    _serial->writePort(str.toUtf8());

    // change the text
    _label->setText("Last command: One step right");
}

void MainWindow::handleButton1() {
    // Send command
    QString str = "2";
    _serial->writePort(str.toUtf8());

    // change the text
    _label->setText("Last command: Half turn right");
}

void MainWindow::handleButton2() {
    // Send command
    QString str = "3";
    _serial->writePort(str.toUtf8());

    // change the text
    _label->setText("Last command: One turn right");
}

void MainWindow::handleButton3() {
    // Send command
    QString str = "4";
    _serial->writePort(str.toUtf8());

    // change the text
    _label->setText("Last command: Five turns right");
}

void MainWindow::handleButton4() {
    // Send command
    QString str = "5";
    _serial->writePort(str.toUtf8());

    // change the text
    _label->setText("Last command: One step left");
}

void MainWindow::handleButton5() {
    // Send command
    QString str = "6";
    _serial->writePort(str.toUtf8());

    // change the text
    _label->setText("Last command: Half turn left");
}

void MainWindow::handleButton6() {
    // Send command
    QString str = "7";
    _serial->writePort(str.toUtf8());

    // change the text
    _label->setText("Last command: One turn left");
}

void MainWindow::handleButton7() {
    // Send command
    QString str = "8";
    _serial->writePort(str.toUtf8());

    // change the text
    _label->setText("Last command: Five turns left");
}

QByteArray MainWindow::toByteArray(QString text) {
    return text.toUtf8();
}

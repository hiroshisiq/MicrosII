#include "mainwindow.h"
#include <QCoreApplication>

#include <gui/tabs/generaltab.h>
#include <gui/tabs/musictab.h>
#include <gui/tabs/teachintab.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    _tabWidget = new QTabWidget();
    _tabWidget->addTab(_general = new GeneralTab(), tr("General"));
    _tabWidget->addTab(_music = new MusicTab(), tr("Music"));
    _tabWidget->addTab(_teachIn = new TeachInTab(), tr("Teach In"));

    layout->addWidget(_tabWidget);
    _serial = NULL;

    widget->setLayout(layout);
    setCentralWidget(widget);
}

void MainWindow::setSerial(Serial *serial) {
    _general->setSerial(serial);
    _music->setSerial(serial);
}

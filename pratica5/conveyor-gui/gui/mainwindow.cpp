#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *widget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(widget);

    // Create tabs
    _tabWidget = new QTabWidget();
    _tabWidget->addTab(_conf = new ConfigurationTab(), tr("Configure"));
    _tabWidget->addTab(_test = new TestTab()         , tr("Test"));

    // Add tabs to window
    layout->addWidget(_tabWidget);

    widget->setLayout(layout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow() {}

void MainWindow::updateInfo() {
    _conf->updateInfo();
    _test->updateInfo();
    _test->disableTab(Observer::getNormalStart());
    _conf->disableTab(Observer::getTestStart() || Observer::getAdvancePiston());
}

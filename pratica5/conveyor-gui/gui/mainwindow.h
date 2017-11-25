#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>

#include <gui/tabs/configurationtab.h>
#include <gui/tabs/testtab.h>
#include <gui/box/infobox.h>

#include <control/observer.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateInfo();

private:
    QTabWidget* _tabWidget;
    ConfigurationTab* _conf;
    TestTab* _test;
    QGroupBox* _info;
};

#endif // MAINWINDOW_H

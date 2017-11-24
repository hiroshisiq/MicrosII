#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include <gui/tabs/configurationtab.h>
#include <gui/tabs/testtab.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget* _tabWidget;
    QWidget* _conf;
    QWidget* _test;
};

#endif // MAINWINDOW_H

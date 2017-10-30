#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include <serial/serial.h>
#include <gui/tabs/generaltab.h>
#include <gui/tabs/musictab.h>

namespace Ui {
    class MainWindow;
 }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setSerial(Serial *serial);

private:
   Serial *_serial;
   QTabWidget *_tabWidget;
   GeneralTab *_general;
   MusicTab *_music;
   QWidget *_teachIn;
};

#endif // MAINWINDOW_H

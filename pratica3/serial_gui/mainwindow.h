#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include "serial.h"

namespace Ui {
    class MainWindow;
 }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setSerial(Serial *serial) { _serial = serial; }

private slots:
   void handleButton0();
   void handleButton1();
   void handleButton2();
   void handleButton3();
   void handleButton4();
   void handleButton5();
   void handleButton6();
   void handleButton7();

private:
   QList<QPushButton*> _buttons;
   QLabel *_label;
   Serial *_serial;

   void renameButtons();
   QByteArray toByteArray(QString text);
};

#endif // MAINWINDOW_H

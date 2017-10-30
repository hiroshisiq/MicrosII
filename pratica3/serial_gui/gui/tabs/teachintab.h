#ifndef TEACHINTAB_H
#define TEACHINTAB_H

#include <QWidget>
#include <QPushButton>

#include <serial/serial.h>

class TeachInTab : public QWidget{
    Q_OBJECT
public:
    TeachInTab();

private slots:
   void handle();

private:
    QPushButton *_pointless;
    int counter = 0;
};

#endif // TEACHINTAB_H

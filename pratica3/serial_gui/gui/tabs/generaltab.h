#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include <serial/serial.h>

class GeneralTab : public QWidget{
    Q_OBJECT
public:
    explicit GeneralTab();
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

#endif // GENERALTAB_H

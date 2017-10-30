#ifndef MUSICTAB_H
#define MUSICTAB_H

#include <QWidget>
#include <QPushButton>

#include <serial/serial.h>

class MusicTab : public QWidget{
    Q_OBJECT
public:
    explicit MusicTab();
    void setSerial(Serial *serial) { _serial = serial; }

private slots:
   void handlePlaySA();
   void handlePlayIM();

private:
    QPushButton *_playSA;
    QPushButton *_playIM;
    Serial *_serial;
};

#endif // MUSICTAB_H

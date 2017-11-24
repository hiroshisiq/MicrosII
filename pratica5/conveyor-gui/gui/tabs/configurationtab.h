#ifndef CONFIGURATIONTAB_H
#define CONFIGURATIONTAB_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include <gui/box/optionsbox.h>
#include <gui/box/infobox.h>

class ConfigurationTab : public QWidget{
    Q_OBJECT
public:
    explicit ConfigurationTab();

private slots:
   void handleButton0();

private:
   QPushButton* _button;
   QGroupBox* _optionsBox;
   QGroupBox* _infoBox;

   QByteArray toByteArray(QString text);
};

#endif // CONFIGURATIONTAB_H

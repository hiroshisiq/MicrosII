#ifndef CONFIGURATIONTAB_H
#define CONFIGURATIONTAB_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include <gui/box/optionsbox.h>
#include <gui/box/infobox.h>

#include<control/observer.h>

class ConfigurationTab : public QWidget{
    Q_OBJECT
public:
    explicit ConfigurationTab();
    void updateInfo();
    void disableTab(bool disable);

private slots:
   void handleStartButton();

private:
   QPushButton* _button;
   QGroupBox* _optionsBox;
   InfoBox* _infoBox;

   QByteArray toByteArray(QString text);
};

#endif // CONFIGURATIONTAB_H

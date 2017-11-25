#ifndef OPTIONSBOX_H
#define OPTIONSBOX_H

#include <QGroupBox>
#include <QCheckBox>
#include <QBoxLayout>

#include <control/observer.h>

class OptionsBox : public QGroupBox {
    Q_OBJECT
public:
    explicit OptionsBox(QGroupBox *parent = nullptr);

signals:

public slots:
   void handleMCB();
   void handleNMCB();

private:
    QCheckBox *_rejectMetalCB;
    QCheckBox *_rejectNonMetalCB;
};

#endif // OPTIONSBOX_H

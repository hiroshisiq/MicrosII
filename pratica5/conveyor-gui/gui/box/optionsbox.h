#ifndef OPTIONSBOX_H
#define OPTIONSBOX_H

#include <QGroupBox>
#include <QCheckBox>
#include <QBoxLayout>

class OptionsBox : public QGroupBox {
    Q_OBJECT
public:
    explicit OptionsBox(QGroupBox *parent = nullptr);

signals:

public slots:

private:
    QCheckBox *_rejectMetalCB;
    QCheckBox *_rejectNonMetalCB;
};

#endif // OPTIONSBOX_H

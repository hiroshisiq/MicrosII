#ifndef INFOBOX_H
#define INFOBOX_H

#include <QGroupBox>
#include <QBoxLayout>
#include <QLabel>

class InfoBox : public QGroupBox {
    Q_OBJECT
public:
    explicit InfoBox(QGroupBox *parent = nullptr);

signals:

public slots:
};

#endif // INFOBOX_H

#ifndef INFOBOX_H
#define INFOBOX_H

#include <QGroupBox>
#include <QBoxLayout>
#include <QLabel>

#include <control/observer.h>

class InfoBox : public QGroupBox {
    Q_OBJECT
private:
    QLabel *_status, *_cap, *_ind, *_opt;
public:
    explicit InfoBox(QGroupBox *parent = nullptr);
    void updateInfo();

signals:

public slots:
};

#endif // INFOBOX_H

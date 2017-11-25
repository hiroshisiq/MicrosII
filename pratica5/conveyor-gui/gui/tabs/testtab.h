#ifndef TESTTAB_H
#define TESTTAB_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include <gui/box/testbox.h>
#include <gui/box/infobox.h>

class TestTab : public QWidget {
    Q_OBJECT
public:
    explicit TestTab(QWidget *parent = nullptr);
    void updateInfo();
    void disableTab(bool disable);

signals:

public slots:

private:
    QGroupBox* _testBox;
    InfoBox* _infoBox;
};

#endif // TESTTAB_H

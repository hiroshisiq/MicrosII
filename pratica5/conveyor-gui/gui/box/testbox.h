#ifndef TESTBOX_H
#define TESTBOX_H

#include <QGroupBox>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>

#include <control/observer.h>

class TestBox : public QGroupBox {
    Q_OBJECT
public:
    explicit TestBox(QGroupBox *parent = nullptr);

public slots:
    void handleRadioB();
    void handleStartB();
    void handlePistonB();

private:
    // Radio buttons
    QRadioButton* _left;
    QRadioButton* _right;
    QButtonGroup* _directionGroup;

    // Push Buttons
    QPushButton* _startButton;
    QPushButton* _pistonButton;
};

#endif // TESTBOX_H

#include "testbox.h"

TestBox::TestBox(QGroupBox *parent) : QGroupBox(parent) {
    this->setTitle("Test Options");
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create button group
    QButtonGroup* directionGroup = new QButtonGroup();
    directionGroup->setExclusive(true);
    QWidget* radioGroup = new QWidget();
    QHBoxLayout* hLayout = new QHBoxLayout(radioGroup);

    // Add radio buttons to group
    directionGroup->addButton(_left  = new QRadioButton("left") );
    directionGroup->addButton(_right = new QRadioButton("right"));
    hLayout->addWidget(_left);
    hLayout->addWidget(_right);
    _right->setChecked(true);

    // Creat push buttons
    _startButton = new QPushButton(tr("Start Conveyor"));
    _pistonButton = new QPushButton(tr("Advance Piston"));

    //layout->addWidget(directionGroup);
    layout->addWidget(new QLabel(tr("Direction:")));
    layout->addWidget(radioGroup);
    layout->addWidget(_startButton);
    layout->addWidget(_pistonButton);

    this->setLayout(layout);

    // Connect button signal to appropriate slot
    connect(_left,         SIGNAL (toggled()), this, SLOT (handleRadioB()) );
    connect(_startButton,  SIGNAL (clicked()), this, SLOT (handleStartB()) );
    connect(_pistonButton, SIGNAL (clicked()), this, SLOT (handlePistonB()));
}

void TestBox::handleRadioB() {
    if(_left->isChecked()) {
        Observer::setTurnLeft(true);
    } else {
        Observer::setTurnLeft(false);
    }
}

void TestBox::handleStartB() {
    if(Observer::getTestStart() == false) {
        _startButton->setText(tr("Stop Conveyor"));
    } else {
        _startButton->setText(tr("Start Conveyor"));
    }

    // Inverte test start state
    Observer::setTestStart(!Observer::getTestStart());
}

void TestBox::handlePistonB() {
    if(Observer::getAdvancePiston() == false) {
        _pistonButton->setText(tr("Retreat Piston"));
    } else {
        _pistonButton->setText(tr("Advance Piston"));
    }

    // Inverte test start state
    Observer::setAdvancePiston(!Observer::getAdvancePiston());

}

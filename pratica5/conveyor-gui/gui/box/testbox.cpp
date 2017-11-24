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
    _left->setChecked(true);

    // Creat push buttons
    _startButton = new QPushButton(tr("Start Conveyor"));
    _pistonButton = new QPushButton(tr("Advance Piston"));

    //layout->addWidget(directionGroup);
    layout->addWidget(new QLabel(tr("Direction:")));
    layout->addWidget(radioGroup);
    layout->addWidget(_startButton);
    layout->addWidget(_pistonButton);


    this->setLayout(layout);
}

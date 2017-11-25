#include "testtab.h"

TestTab::TestTab(QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(20);

    _testBox = new TestBox();
    layout->addWidget(_testBox, 0, 0);

    _infoBox = new InfoBox();
    layout->addWidget(_infoBox, 0, 1);

    // Set the layout with all buttons to this widget
    this->setLayout(layout);
}

void TestTab::updateInfo() {
    _infoBox->updateInfo();
}

void TestTab::disableTab(bool disable) {
    this->setDisabled(disable);
}

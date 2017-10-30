#include "teachintab.h"
#include <QGridLayout>

TeachInTab::TeachInTab() {
    QGridLayout *layout = new QGridLayout(this);
    _pointless = new QPushButton("Pointless Button");
    _pointless->setMinimumHeight(100);
    layout->addWidget(_pointless,1,0);

    connect(_pointless, SIGNAL (clicked()), this, SLOT (handle()));
}

void TeachInTab::handle() {
    counter++;

    if(counter > 30) {
        _pointless->setText("Xupa Vareta");
    }    
}

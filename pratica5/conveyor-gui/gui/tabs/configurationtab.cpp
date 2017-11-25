#include "configurationtab.h"

ConfigurationTab::ConfigurationTab() {
    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(20);

    _button = new QPushButton(tr("Start"));
    layout->addWidget(_button, 1, 0);

    _optionsBox = new OptionsBox();
    layout->addWidget(_optionsBox, 0, 0);

    _infoBox = new InfoBox();
    layout->addWidget(_infoBox, 0, 1, 2, 1);

    // Set the layout with all buttons to this widget
    this->setLayout(layout);

    // Connect button signal to appropriate slot
    connect(_button, SIGNAL (clicked()), this, SLOT (handleStartButton()));
}

void ConfigurationTab::handleStartButton() {
    if(Observer::getNormalStart() == false) {
        _button->setText(tr("Stop"));
    } else {
        _button->setText(tr("Start"));
    }

    // Inverte normal start state
    Observer::setNormalStart(!Observer::getNormalStart());
}

void ConfigurationTab::updateInfo() {
    _infoBox->updateInfo();
}

void ConfigurationTab::disableTab(bool disable) {
    this->setDisabled(disable);
}

QByteArray ConfigurationTab::toByteArray(QString text) {
    return text.toUtf8();
}

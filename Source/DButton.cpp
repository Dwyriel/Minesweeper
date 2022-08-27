#include "DButton.h"

DButton::DButton(QWidget *parent) : QPushButton(parent) {
    id = 0;
    connect(this, &QPushButton::pressed, this, &DButton::buttonWasPressed);
}

void DButton::buttonWasPressed() {
    emit ButtonPressed(id);
}

void DButton::setId(int i) {
    id = i;
}
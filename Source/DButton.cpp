#include "DButton.h"

DButton::DButton(QWidget *parent) : QPushButton(parent) {
    id = 0;
}

void DButton::setId(int i) {
    id = i;
}

void DButton::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::RightButton)
        emit RightButtonPressed(id);
    if(e->button() == Qt::LeftButton)
        emit ButtonPressed(id);
}

bool DButton::isMarked() {
    return marked;
}

void DButton::setMarked(bool value) {
    marked = value;
}

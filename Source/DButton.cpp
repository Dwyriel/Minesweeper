#include "DButton.h"

DButton::DButton(QWidget *parent) : QPushButton(parent) {
    id = 0;
    this->setAutoRepeat(false);
}

void DButton::setId(int i) {
    id = i;
}

void DButton::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton)
        emit rightButtonPressed(id);
    if (e->button() == Qt::LeftButton)
        emit buttonPressed(id, false);
}

void DButton::keyPressEvent(QKeyEvent *e) {
    if ((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return || e->key() == Qt::Key_Space) && !e->isAutoRepeat()) {
        emit buttonPressed(id, false);
        return;
    }
    if(e->key() == Qt::Key_Up || e->key() == Qt::Key_Down){
        emit arrowKeyPressed(id, e->key());
        return;
    }
    QPushButton::keyPressEvent(e);
}

bool DButton::isMarked() {
    return marked;
}

void DButton::setMarked(bool value) {
    marked = value;
}

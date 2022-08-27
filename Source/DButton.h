#ifndef UNTITLED_DBUTTON_H
#define UNTITLED_DBUTTON_H

#include <QPushButton>

class DButton : public QPushButton {
Q_OBJECT

public:
    explicit DButton(QWidget *parent = 0);

    void setId(int i);

private:
    int id;

signals:
    void ButtonPressed(int id);

private slots:
    void buttonWasPressed();

public slots:
};

#endif //UNTITLED_DBUTTON_H

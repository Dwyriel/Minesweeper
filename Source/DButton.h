#ifndef UNTITLED_DBUTTON_H
#define UNTITLED_DBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class DButton : public QPushButton {
Q_OBJECT

public:
    explicit DButton(QWidget *parent = 0);

    void setId(int i);

    bool isMarked();

    void setMarked(bool value);

protected:
    void mousePressEvent(QMouseEvent *e) override;

    void keyPressEvent(QKeyEvent *e) override;

private:
    int id;
    bool marked = false;

signals:
    void buttonPressed(int id, bool rec);

    void rightButtonPressed(int id);

    void arrowKeyPressed(int id, int key);

private slots:

public slots:
};

#endif //UNTITLED_DBUTTON_H

#ifndef UNTITLED_DBUTTON_H
#define UNTITLED_DBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class DButton : public QPushButton {
Q_OBJECT

public:
    explicit DButton(QWidget *parent = 0);

    void SetId(int i);

    bool IsMarked();

    void SetMarked(bool value);

protected:
    void mousePressEvent(QMouseEvent *e) override;

    void keyPressEvent(QKeyEvent *e) override;

private:
    int id;
    bool marked = false;

signals:
    void ButtonPressed(int id, bool rec);

    void RightButtonPressed(int id);

    void ArrowKeyPressed(int id, int key);

private slots:

public slots:
};

#endif //UNTITLED_DBUTTON_H

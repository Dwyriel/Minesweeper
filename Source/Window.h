#ifndef UNTITLED_WINDOW_H
#define UNTITLED_WINDOW_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include "DButton.h"

class Window : public QWidget {
Q_OBJECT
public:
    explicit Window(int width, int height, QWidget *parent = 0);

private:
    int height = 10, width = 10, spacing = 3, buttonSize = 30, maxMines = 30;
    DButton **m_buttons;
    QGridLayout *m_grid;
    int *mineField = nullptr;
    bool isFirstClick = true;

    void ResetGame();

    void FirstClick(int x, int y);

signals:
private slots:
    void ButtonPressed(int id);

public slots:
};

#endif //UNTITLED_WINDOW_H

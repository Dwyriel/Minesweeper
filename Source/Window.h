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
    explicit Window(int width, int height, int maxMines, QWidget *parent = 0);

private:
    const int spacing = 3, buttonSize = 30;
    int m_width = 10, m_height = 10, maxMines = 18;
    DButton **m_buttons;
    QGridLayout *m_grid;
    int *mineField = nullptr;
    bool isFirstClick = true;

    void ResetGame();

    void FirstClick(int x, int y);

    void checkWinCondition();

    void checkNearbyTiles(int x, int y, int id);

    static void showMessageBox(QString title, QString body);

signals:
private slots:
    void ButtonPressed(int id);

    void RightButtonPressed(int id);

    void ArrowKeyPressed(int id, int key);

public slots:
};

#endif //UNTITLED_WINDOW_H

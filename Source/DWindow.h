#ifndef UNTITLED_WINDOW_H
#define UNTITLED_WINDOW_H

#include <vector>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include "DButton.h"
#include "GlobalVars.h"

class DWindow : public QWidget {
Q_OBJECT
public:
    explicit DWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    const int spacing = 3, buttonSize = 30;
    int m_width = 10, m_height = 10, maxMines = 20, rounds = 0;
    DButton **m_buttons;
    QGridLayout *m_grid;
    int *mineField = nullptr;
    bool isFirstClick = true;

    void ResetGame();

    void FirstClick(int id);

    void CheckWinCondition();

    void CheckNearbyTiles(int x, int y, int id);

    static void ShowMessageBox(QString title, QString body, QWidget *parent = nullptr);

signals:
    void WindowClosed();

private slots:

    void ButtonPressed(int id, bool recursive = false);

    void RightButtonPressed(int id);

    void ArrowKeyPressed(int id, int key);

public slots:
};

#endif //UNTITLED_WINDOW_H

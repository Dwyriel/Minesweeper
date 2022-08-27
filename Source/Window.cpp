#include "Window.h"

Window::Window(int width, int height, QWidget *parent) : QWidget(parent) {
    setWindowTitle("Minesweeper");
    setBaseSize((buttonSize + spacing) * height, (buttonSize + spacing) * width);
    resize(baseSize());
    m_grid = new QGridLayout(this);
    m_grid->setHorizontalSpacing(spacing);
    m_grid->setVerticalSpacing(spacing);
    m_buttons = new DButton *[height * width];
    mineField = new int[height * width];
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            int currIndex = y * width + x;
            m_buttons[currIndex] = new DButton(this);
            //buttons[currIndex]->setText(QString::fromStdString(std::to_string(y) + " " + std::to_string(x)));
            m_buttons[currIndex]->setMinimumSize(buttonSize, buttonSize);
            m_buttons[currIndex]->setMaximumSize(buttonSize * 10, buttonSize * 10);
            m_buttons[currIndex]->setId(currIndex);
            m_grid->addWidget(m_buttons[currIndex], x, y);
            QObject::connect(m_buttons[currIndex], &DButton::ButtonPressed, this, &Window::ButtonPressed);
            mineField[currIndex] = 0;
        }
}

void Window::ButtonPressed(int id) {
    int x = id % width;
    int y = id / width;
    if (isFirstClick)
        FirstClick(x, y); //gemerate game
    m_buttons[y * width + x]->setDisabled(true);
    if (mineField[y * width + x] == 1) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("You died");
        msgBox.setText("You stepped on a mine :(");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        ResetGame();
    } else {
        int minesNearby = 0;
        for (int ix = -1; ix < 2; ix++)
            for (int iy = -1; iy < 2; iy++)
                if (x + ix >= 0 && x + ix < width && y + iy >= 0 && y + iy < height)
                    if (mineField[(y + iy) * width + (x + ix)])
                        minesNearby++;
        if (minesNearby > 0)
            m_buttons[y * width + x]->setText(QString::number(minesNearby));
    }
}

void Window::ResetGame() {
    isFirstClick = true;
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            int index = y * width + x;
            mineField[index] = 0;
            m_buttons[index]->setText("");
            m_buttons[index]->setDisabled(false);
        }
}

void Window::FirstClick(int x, int y) {
    int mines = maxMines;
    if (mines > (height * width) / 2)
        mines = (height * width) / 2;
    while (mines) {
        int randx = rand() % width;
        int randy = rand() % height;
        if (mineField[randy * width + randx] == 0 && randx != x && randy != y) {
            mineField[randy * width + randx] = 1;
            mines--;
        }
    }
    isFirstClick = false;
}
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
            //buttons[currIndex]->setText(QString::fromStdString(std::to_string(y) + "," + std::to_string(x)));
            m_buttons[currIndex]->setMinimumSize(buttonSize, buttonSize);
            m_buttons[currIndex]->setMaximumSize(buttonSize * 10, buttonSize * 10);
            m_buttons[currIndex]->setId(currIndex);
            m_grid->addWidget(m_buttons[currIndex], x, y);
            QObject::connect(m_buttons[currIndex], &DButton::ButtonPressed, this, &Window::ButtonPressed);
            QObject::connect(m_buttons[currIndex], &DButton::RightButtonPressed, this, &Window::RightButtonPressed);
            mineField[currIndex] = 0;
        }
}

void Window::RightButtonPressed(int id) {
    if (!m_buttons[id]->isEnabled())
        return;
    m_buttons[id]->setMarked(!m_buttons[id]->isMarked());
    m_buttons[id]->setText(m_buttons[id]->isMarked() ? "\U0001F6A9" : "");
}

void Window::ButtonPressed(int id) {
    int x = id % width;
    int y = id / width;
    if (m_buttons[id]->isMarked())
        return;
    if (isFirstClick)
        FirstClick(x, y); //generate game
    m_buttons[id]->setDisabled(true);
    if (mineField[id] == 1) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("You died");
        msgBox.setText("You stepped on a mine \U0001F915");
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
            m_buttons[id]->setText(QString::number(minesNearby));
        else {
            for (int ix = -1; ix < 2; ix++)
                for (int iy = -1; iy < 2; iy++)
                    if (x + ix >= 0 && x + ix < width && y + iy >= 0 && y + iy < height)
                        if (m_buttons[(y + iy) * width + (x + ix)]->isEnabled())
                            ButtonPressed((y + iy) * width + (x + ix));
        }
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
            m_buttons[index]->setMarked(false);
        }
}

void Window::FirstClick(int x, int y) {
    int mines = maxMines;
    if (mines > (height * width) / 2)
        mines = (height * width) / 2;
    while (mines) {
        int randx = rand() % width;
        int randy = rand() % height;
        bool canBePlaced;
        if ((randx >= x - 1 && randx <= x + 1) && (randy >= y - 1 && randy <= y + 1))
            continue;
        if (mineField[randy * width + randx] == 0 && randx != x && randy != y) {
            mineField[randy * width + randx] = 1;
            mines--;
        }
    }
    isFirstClick = false;
}
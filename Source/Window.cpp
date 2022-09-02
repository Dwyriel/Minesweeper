#include "Window.h"

Window::Window(int width, int height, int maxMines, QWidget *parent) : QWidget(parent) {
    this->m_height = height;
    this->m_width = width;
    this->maxMines = maxMines;
    setWindowTitle("Minesweeper");
    setBaseSize((buttonSize + spacing) * width, (buttonSize + spacing) * height);
    resize(baseSize());
    m_grid = new QGridLayout(this);
    m_grid->setHorizontalSpacing(spacing);
    m_grid->setVerticalSpacing(spacing);
    m_buttons = new DButton *[width * height];
    mineField = new int[width * height];
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            int currIndex = x * height + y;
            m_buttons[currIndex] = new DButton(this);
            //m_buttons[currIndex]->setText(QString::fromStdString(std::to_string(x) + "," + std::to_string(y)));
            m_buttons[currIndex]->setMinimumSize(buttonSize, buttonSize);
            m_buttons[currIndex]->setMaximumSize(buttonSize * 10, buttonSize * 10);
            m_buttons[currIndex]->setId(currIndex);
            m_grid->addWidget(m_buttons[currIndex], y, x);
            QObject::connect(m_buttons[currIndex], &DButton::ButtonPressed, this, &Window::ButtonPressed);
            QObject::connect(m_buttons[currIndex], &DButton::RightButtonPressed, this, &Window::RightButtonPressed);
            QObject::connect(m_buttons[currIndex], &DButton::ArrowKeyPressed, this, &Window::ArrowKeyPressed);
            mineField[currIndex] = 0;
        }
}

void Window::ArrowKeyPressed(int id, int key) {
    int y = id % m_height;
    int x = id / m_height;
    y = y + (key == Qt::Key_Up ? -1 : 1);
    if (y < 0) {
        y = m_height - 1;
        x--;
    } else if (y >= m_height) {
        y = 0;
        x++;
    }
    x = (x < 0) ? m_width - 1 : (x >= m_width) ? x = 0 : x;
    //y = y < 0 ? m_height - 1 : y >= m_height ? 0 : y;
    int nextId = x * m_height + y;
    if (!m_buttons[nextId]->isEnabled())
        ArrowKeyPressed(nextId, key);
    m_buttons[nextId]->setFocus();
}

void Window::RightButtonPressed(int id) {
    if (!m_buttons[id]->isEnabled())
        return;
    m_buttons[id]->setMarked(!m_buttons[id]->isMarked());
    m_buttons[id]->setText(m_buttons[id]->isMarked() ? "\U0001F6A9" : "");
}

void Window::ButtonPressed(int id) {
    int x = id % m_height;
    int y = id / m_height;
    if (m_buttons[id]->isMarked())
        return;
    if (isFirstClick)
        FirstClick(x, y); //generate game
    m_buttons[id]->setDisabled(true);
    if (mineField[id] == 1) {
        m_buttons[id]->setText("\U0001F4A3");
        showMessageBox("You died", "You stepped on a mine \U0001F915");
        ResetGame();
    } else {
        int minesNearby = 0;
        for (int ix = -1; ix < 2; ix++)
            for (int iy = -1; iy < 2; iy++)
                if (x + ix >= 0 && x + ix < m_height && y + iy >= 0 && y + iy < m_width)
                    if (mineField[(y + iy) * m_height + (x + ix)])
                        minesNearby++;
        if (minesNearby > 0)
            m_buttons[id]->setText(QString::number(minesNearby));
        else {
            for (int ix = -1; ix < 2; ix++)
                for (int iy = -1; iy < 2; iy++)
                    if (x + ix >= 0 && x + ix < m_height && y + iy >= 0 && y + iy < m_width)
                        if (m_buttons[(y + iy) * m_height + (x + ix)]->isEnabled())
                            ButtonPressed((y + iy) * m_height + (x + ix));
        }
    }
    int totalButtonsLeft = 0;
    for (int i = 0; i < m_width * m_height; i++) {
        if (m_buttons[i]->isEnabled())
            totalButtonsLeft++;
    }
    if (totalButtonsLeft == maxMines) {
        showMessageBox("You won", "You cleared the field, Gratz \U0001F970");
        ResetGame();
    }
}

void Window::ResetGame() {
    isFirstClick = true;
    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++) {
            int index = x * m_height + y;
            mineField[index] = 0;
            m_buttons[index]->setText("");
            m_buttons[index]->setDisabled(false);
            m_buttons[index]->setMarked(false);
        }
}

void Window::FirstClick(int x, int y) {
    int mines = maxMines;
    if (mines > (m_width * m_height) / 2)
        mines = (m_width * m_height) / 2;
    while (mines) {
        int randx = rand() % m_height;
        int randy = rand() % m_width;
        bool canBePlaced;
        if ((randx >= x - 1 && randx <= x + 1) && (randy >= y - 1 && randy <= y + 1))
            continue;
        if (mineField[randy * m_height + randx] == 0 && randx != x && randy != y) {
            mineField[randy * m_height + randx] = 1;
            mines--;
        }
    }
    isFirstClick = false;
}

void Window::showMessageBox(QString title, QString body) {
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(body);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

#include "DWindow.h"
DWindow::DWindow(QWidget *parent) : QWidget(parent) {
    this->m_height = GlobalVars::Height;
    this->m_width = GlobalVars::Width;
    this->maxMines = GlobalVars::MaxMines;
    setWindowTitle("Minesweeper");
    setWindowIcon(QIcon::fromTheme("face-angel"));
    setBaseSize((buttonSize + spacing) * m_width, (buttonSize + spacing) * m_height);
    resize(baseSize());
    m_grid = new QGridLayout(this);
    m_grid->setHorizontalSpacing(spacing);
    m_grid->setVerticalSpacing(spacing);
    m_buttons = new DButton *[m_width * m_height];
    mineField = new int[m_width * m_height];
    for (int y = 0; y < m_height; y++) //generate buttons and connect their events
        for (int x = 0; x < m_width; x++) {
            int currIndex = x * m_height + y;
            m_buttons[currIndex] = new DButton(this);
            //m_buttons[currIndex]->setText(QString::fromStdString(std::to_string(x) + "," + std::to_string(y)));
            m_buttons[currIndex]->setMinimumSize(buttonSize, buttonSize);
            m_buttons[currIndex]->setMaximumSize(buttonSize * 10, buttonSize * 10);
            m_buttons[currIndex]->setId(currIndex);
            m_grid->addWidget(m_buttons[currIndex], y, x);
            QObject::connect(m_buttons[currIndex], &DButton::buttonPressed, this, &DWindow::buttonPressed);
            QObject::connect(m_buttons[currIndex], &DButton::rightButtonPressed, this, &DWindow::flagKeyPressed);
            QObject::connect(m_buttons[currIndex], &DButton::arrowKeyPressed, this, &DWindow::arrowKeyPressed);
            QObject::connect(m_buttons[currIndex], &DButton::flagKeyPress, this, &DWindow::flagKeyPressed);
            mineField[currIndex] = 0;
        }
}

void DWindow::closeEvent(QCloseEvent *event) {
    emit windowClosed();
    QWidget::closeEvent(event);
}

void DWindow::arrowKeyPressed(int id, int key) {
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
        arrowKeyPressed(nextId, key);
    m_buttons[nextId]->setFocus();
}

void DWindow::flagKeyPressed(int id) {
    if (!m_buttons[id]->isEnabled())
        return;
    m_buttons[id]->setMarked(!m_buttons[id]->isMarked());
    m_buttons[id]->setText(m_buttons[id]->isMarked() ? "\U0001F6A9" : "");
}

bool DWindow::buttonPressed(int id, bool recursive) {
    if(!recursive)
        rounds++;
    int x = id % m_height;
    int y = id / m_height;
    if (m_buttons[id]->isMarked())
        return false;
    if (isFirstClick && !recursive) //generate game
        firstClick(id);
    m_buttons[id]->setDisabled(true);
    if (mineField[id] == 1) {
        m_buttons[id]->setText("\U0001F4A3");
        showMessageBox("You died", "<font size = 5>You stepped on a mine \U0001F915</font>", this);
        resetGame();
        return true;
    } else {
        if (checkNearbyTiles(x, y, id))
            return true;
    }
    return checkWinCondition();
}

void DWindow::resetGame() {
    isFirstClick = true;
    rounds = 0;
    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++) {
            int index = x * m_height + y;
            mineField[index] = 0;
            m_buttons[index]->setText("");
            m_buttons[index]->setDisabled(false);
            m_buttons[index]->setMarked(false);
        }
}

void DWindow::firstClick(int id) {
    maxMines = maxMines > ((m_width * m_height) - 9) ? ((m_width * m_height) - 9) : maxMines;
    int mines = maxMines;
    int lowX_lowY = id - m_height - 1, highX_lowY = id - m_height + 1;
    int lowX_medY = id - 1, highX_medY = id + 1;
    int lowX_highY = id + m_height - 1, highX_highY = id + m_height + 1;
    std::vector<int> placesToPlant;
    for (int i = 0; i < m_width * m_height; i++){
        if((i >= lowX_lowY && i <= highX_lowY) || (i >= lowX_medY && i <= highX_medY) || (i >= lowX_highY && i <= highX_highY))
            continue;
        placesToPlant.emplace_back(i);
    }
    while(mines){
        int randNum = rand() % placesToPlant.size();
        mineField[placesToPlant[randNum]] = 1;
        placesToPlant.erase(placesToPlant.begin() + randNum);
        mines--;
    }
    isFirstClick = false;
}

bool DWindow::checkNearbyTiles(int x, int y, int id) {
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
                        if(buttonPressed((y + iy) * m_height + (x + ix), true))
                            return true;
    }
    return false;
}

bool DWindow::checkWinCondition() {
    int totalButtonsLeft = 0;
    for (int i = 0; i < m_width * m_height; i++) {
        if (m_buttons[i]->isEnabled())
            totalButtonsLeft++;
    }
    if (totalButtonsLeft == maxMines) {
        showMessageBox("You won", (rounds <= 3) ? "<font size = 5>No cheating \U0001F92D</font>" : "<font size = 5>You found all the mines, Gratz \U0001F970</font>", this);
        resetGame();
        return true;
    }
    return false;
}

void DWindow::showMessageBox(QString title, QString body, QWidget *parent) {
    QMessageBox msgBox = QMessageBox(parent);
    msgBox.setWindowTitle(title);
    msgBox.setWindowIcon(QIcon::fromTheme("dialog-warning"));
    msgBox.setText(body);
    msgBox.setStyleSheet("font-size = 20px");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

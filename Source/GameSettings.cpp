#include "GameSettings.h"

GameSettings::GameSettings(QWidget *parent) {
    setFixedSize(175, 120);
    setWindowTitle("Setting");
    setWindowIcon(QIcon::fromTheme("preferences-system"));
    setWindowFlags(Qt::Window);
    //m_gridSizeLabel
    m_gridSizeLabel = new QLabel(QObject::tr("Grid Size:"), this);
    m_gridSizeLabel->setGeometry(10, 10, 60, 20);
    m_gridSizeLabel->setAlignment(Qt::AlignCenter);
    m_gridSizeLabel->setStyleSheet("font-weight: bold;");
    //m_xLineEdit
    m_xLineEdit = new QLineEdit(this);
    m_xLineEdit->setGeometry(75, 10, 35, 20);
    m_xLineEdit->setAlignment(Qt::AlignCenter);
    m_xLineEdit->setValidator(new QIntValidator(1, 99, this));
    m_xLineEdit->setText(QString::number(GlobalVars::Width));
    //m_gridSeparatorLabel
    m_gridSeparatorLabel = new QLabel(QObject::tr("x"), this);
    m_gridSeparatorLabel->setGeometry(115, 10, 10, 20);
    m_gridSeparatorLabel->setAlignment(Qt::AlignCenter);
    //m_yLineEdit
    m_yLineEdit = new QLineEdit(this);
    m_yLineEdit->setGeometry(130, 10, 35, 20);
    m_yLineEdit->setAlignment(Qt::AlignCenter);
    m_yLineEdit->setValidator(new QIntValidator(1, 99, this));
    m_yLineEdit->setText(QString::number(GlobalVars::Height));
    //m_minesLabel
    m_minesLabel = new QLabel(QObject::tr("Mines:"), this);
    m_minesLabel->setGeometry(45, 35, 40, 20);//29
    m_minesLabel->setAlignment(Qt::AlignCenter);
    m_minesLabel->setStyleSheet("font-weight: bold;");
    //m_minesLineEdit
    m_minesLineEdit = new QLineEdit(this);
    m_minesLineEdit->setGeometry(90, 35, 35, 20);//74
    m_minesLineEdit->setAlignment(Qt::AlignCenter);
    m_minesLineEdit->setValidator(new QIntValidator(1, 999, this));
    m_minesLineEdit->setText(QString::number(GlobalVars::MaxMines));
    //m_errorLabel
    m_errorLabel = new QLabel(QObject::tr("Some error"), this);
    m_errorLabel->setGeometry(10, 60, 155, 20);
    m_errorLabel->setAlignment(Qt::AlignCenter);
    m_errorLabel->setStyleSheet("color : red;");
    m_errorLabel->hide();
    //m_playButton
    m_playButton = new QPushButton(QObject::tr("Play"), this);
    m_playButton->setGeometry(42, 85, 90, 25);
    connect(m_playButton, &QPushButton::clicked, this, &GameSettings::PlayButtonPressed);
}

void GameSettings::PlayButtonPressed() {
    int x, y, mines;
    x = m_xLineEdit->text().toInt();
    y = m_yLineEdit->text().toInt();
    mines = m_minesLineEdit->text().toInt();
    if (x < 1 || y < 1 || mines < 1) {
        QString str = mines < 1 ? "Too few mines" : ((x < 1 ? "X " : "Y ") + QString("") + "can't be smaller than 0");
        showError(str);
        return;
    }
    m_errorLabel->hide();
    GlobalVars::Width = x;
    GlobalVars::Height = y;
    GlobalVars::MaxMines = mines;
    close();
    m_window = new DWindow(this);
    m_window->setWindowFlags(Qt::Window);
    m_window->setAttribute(Qt::WA_DeleteOnClose, true);
    QObject::connect(m_window, SIGNAL(destroyed(QObject * )), this, SLOT(show()));
    m_window->show();
}

void GameSettings::showError(const QString &error) {
    m_errorLabel->setText(error);
    m_errorLabel->show();
}

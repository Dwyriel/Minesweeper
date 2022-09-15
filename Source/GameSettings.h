#ifndef MINESWEEPER_GAMESETTINGS_H
#define MINESWEEPER_GAMESETTINGS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QValidator>
#include "GlobalVars.h"
#include "DWindow.h"

class GameSettings : public QWidget {
Q_OBJECT
public:
    explicit GameSettings(QWidget *parent = nullptr);

private:
    QLabel *m_gridSizeLabel, *m_gridSeparatorLabel, *m_minesLabel, *m_errorLabel;
    QLineEdit *m_xLineEdit, *m_yLineEdit, *m_minesLineEdit;
    QPushButton *m_playButton;
    DWindow *m_window;

    void ShowError(const QString &error);

private slots:

    void ChildWindowClosed();

    void PlayButtonPressed();
};


#endif //MINESWEEPER_GAMESETTINGS_H

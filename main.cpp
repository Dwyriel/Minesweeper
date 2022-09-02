#include <QApplication>
#include "Source/DWindow.h"
#include "Source/GameSettings.h"

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    QApplication app(argc, argv);
    GameSettings gameSettings = GameSettings(nullptr);
    gameSettings.show();
    return QApplication::exec();
}

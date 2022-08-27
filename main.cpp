#include <QApplication>
#include <QMessageBox>
#include "Source/Window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window window = Window(10, 10, nullptr);
    window.show();
    return QApplication::exec();
}

#include <QApplication>
#include "Source/Window.h"

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    QApplication app(argc, argv);
    Window window = Window(10, 10, 20, nullptr);
    window.setWindowIcon(QIcon::fromTheme("face-angel"));
    window.show();
    return QApplication::exec();
}

// # III_course/2025-09-24-qt-notepad/main.cpp
#include <QApplication>
#include "notepad.h"

int main() {
    QApplication app(argc, argv);
    Notepad window;
    window.show();
    return app.exec();
}

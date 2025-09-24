// # III_course/2025-09-24-qt-notepad/main.cpp
#include <QApplication>
#include "notepad.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Notepad window;
    window.show();
    return app.exec();
}

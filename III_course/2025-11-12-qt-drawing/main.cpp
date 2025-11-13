//
// Created by tysser on 12.11.25.
//

// III_course/2025-11-12-qt-drawing/main.cpp

#include <QApplication>
#include "drawing.h"

int main(int argc, char *argv[]) {

    // створюємо глобальний Qt-додаток і даємо йому аргументи командного рядка
    QApplication app(argc, argv);

    // створюємо головне вікно програми
    Drawing w;

    // показуємо його на екрані
    w.show();

    // запускаємо головний цикл Qt (обробка подій: миша, клавіатура, таймери)
    return QApplication::exec();
}
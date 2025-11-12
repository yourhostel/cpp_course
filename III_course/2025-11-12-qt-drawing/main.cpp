//
// Created by tysser on 12.11.25.
//

// III_course/2025-11-12-qt-drawing/main.cpp

#include <QApplication>
#include "drawing.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Drawing w;
    w.show();
    return QApplication::exec();
}
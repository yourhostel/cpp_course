//
// Created by tysser on 01.11.25.
//

// III_course/2025-11-01-qt-tabulation/main.cpp

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}

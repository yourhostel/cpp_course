//
// Created by tysser on 03.11.25.
//

// III_course/2025-11-03-qt-gui-basics/student_form/main.cpp

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
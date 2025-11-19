// III_course/2025-11-19-qt-practical-13-postgresql/students/main.cpp

#include <QApplication>
#include "students.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Students w;
    w.show();
    return QApplication::exec();
}
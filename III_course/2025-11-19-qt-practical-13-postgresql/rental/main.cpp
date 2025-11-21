// III_course/2025-11-19-qt-practical-13-postgresql/rental/main.cpp

#include <QApplication>
#include "rental.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Rental r;
    r.show();
    return QApplication::exec();
}
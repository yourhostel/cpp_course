// cpp_course/III_course/2026-02-09-qt-network-sockets-chat/server/main.cpp

#include <QApplication>
#include "server.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Server window;
    window.show();
    return QApplication::exec();
}
// cpp_course/III_course/2026-02-09-qt-network-sockets-chat/client/main.cpp

#include <QApplication>
#include "client.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Client window;
    window.show();
    return QApplication::exec();
}
// III_course/2026-02-15-creating-own-components/main.cpp

//
// Created by tysser on 15.02.26.
//

#include <QApplication>

#include "Components.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Components window;
    window.show();
    return app.exec();
}

// cpp_course/III_course/2026-02-09-qt-network-sockets-chat/server/server.cpp

//
// Created by tysser on 09.02.26.
//

#include "server.h"
#include "ui_server.h"

Server::Server(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::Server)
{
    ui->setupUi(this);
}

Server::~Server()
{
    delete ui;
}
// cpp_course/III_course/2026-02-09-qt-network-sockets-chat/client/client.cpp

//
// Created by tysser on 09.02.26.
//

#include "client.h"
#include "ui_client.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::Client)
{
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}
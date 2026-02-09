// cpp_course/III_course/2026-02-09-qt-network-sockets-chat/server/server.h

//
// Created by tysser on 09.02.26.
//

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server final : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget* parent = nullptr);
    ~Server() override;

private:
    Ui::Server* ui;
};

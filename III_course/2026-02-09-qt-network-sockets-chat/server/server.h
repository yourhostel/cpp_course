// cpp_course/III_course/2026-02-09-qt-network-sockets-chat/server/server.h

//
// Created by tysser on 09.02.26.
//

#pragma once

#include <QMainWindow>

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QHash>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server final : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget* parent = nullptr);
    ~Server() override;

private slots:
    void onStartClicked();
    void onStopClicked();

    void onNewConnection();
    void onClientDisconnected();

    void onClockTick();

    void onReadyRead();

private:
    void appendLog(const QString& text);
    void updateUsersView();

    // буфери для накопичення
    void broadcastUsers();
    void broadcastMessage(const QString& fromNick, const QString& text);

    QHash<QTcpSocket*, QString> clients;
    QHash<QTcpSocket*, QByteArray> rxBuffers;

    QTcpServer* tcpServer;
    QTimer* clockTimer;

private:
    void handleLine(QTcpSocket* s, const QString& line);
    void handleNick(QTcpSocket* s, const QString& nickRaw);
    void handleTo(QTcpSocket* s, const QString& rest);
    void handleMsg(QTcpSocket* s, const QString& textRaw);

    Ui::Server* ui;
};

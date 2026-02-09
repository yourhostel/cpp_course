// cpp_course/III_course/2026-02-09-qt-network-sockets-chat/client/client.h

//
// Created by tysser on 09.02.26.
//

#pragma once

#include <QMainWindow>

#include <QTcpSocket>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client final : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget* parent = nullptr);
    ~Client() override;

private slots:
    void onConnectClicked();
    void onSendClicked();

    void onConnected();
    void onDisconnected();
    void onReadyRead();

    void onClockTick();

private:
    void appendChat(const QString& text);

    QTcpSocket* socket;
    QTimer* clockTimer;

    QByteArray rxBuffer;

    QString myNick;

    Ui::Client* ui;
};

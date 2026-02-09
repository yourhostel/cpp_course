// cpp_course/III_course/2026-02-09-qt-network-sockets-chat/server/server.cpp

//
// Created by tysser on 09.02.26.
//

#include "server.h"
#include "ui_server.h"

#include <QDateTime>
#include <QHostAddress>

Server::Server(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::Server),
      tcpServer(new QTcpServer(this)),
      clockTimer(new QTimer(this))
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &Server::onStartClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &Server::onStopClicked);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);

    connect(clockTimer, &QTimer::timeout, this, &Server::onClockTick);
    clockTimer->start(1000);
    onClockTick();

    ui->stopButton->setEnabled(false);
}

Server::~Server()
{
    onStopClicked();
    delete ui;
}

// Оновлює годинник у UI раз на секунду.
void Server::onClockTick()
{
    ui->clockLabel->setText(QTime::currentTime().toString("HH:mm:ss"));
}

// Додає рядок у лог сесії на сервері з часовою міткою.
void Server::appendLog(const QString& text)
{
    const auto ts = QDateTime::currentDateTime().toString("HH:mm:ss");
    ui->sessionLogTextEdit->append(ts + " " + text);
}

// Запускає TCP сервер: читає IP і порт з UI, викликає listen, перемикає кнопки.
// Якщо IP порожній, слухає всі інтерфейси через QHostAddress::Any.
void Server::onStartClicked()
{
    const quint16 port = ui->portLineEdit->text().toUShort();

    const QHostAddress addr = ui->ipLineEdit->text().isEmpty()
        ? QHostAddress::Any
        : QHostAddress(ui->ipLineEdit->text());

    if (!tcpServer->listen(addr, port))
    {
        appendLog("Помилка запуску сервера: " + tcpServer->errorString());
        return;
    }

    appendLog("Сервер запущено: " + tcpServer->serverAddress().toString()
              + ":" + QString::number(tcpServer->serverPort()));

    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

// Зупиняє TCP сервер: закриває listen, від’єднує всіх клієнтів, чистить таблиці стану, оновлює UI.
// disconnectFromHost асинхронний
void Server::onStopClicked()
{
    if (tcpServer->isListening())
        tcpServer->close();

    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
        if (it.key())
            it.key()->disconnectFromHost();
    }

    clients.clear();
    rxBuffers.clear();

    updateUsersView();

    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);

    appendLog("Сервер зупинено");
}

// Приймає всі pending connections і реєструє кожен сокет у таблицях, підключає сигнали disconnected і readyRead.
// Цикл while потрібен, бо може прилетіти кілька підключень за раз.
void Server::onNewConnection()
{
    while (tcpServer->hasPendingConnections())
    {
        QTcpSocket* s = tcpServer->nextPendingConnection();

        clients.insert(s, "unknown");
        rxBuffers.insert(s, QByteArray());

        appendLog("Підключення: " + s->peerAddress().toString()
                  + ":" + QString::number(s->peerPort()));

        connect(s, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
        connect(s, &QTcpSocket::readyRead, this, &Server::onReadyRead);

        broadcastUsers();
    }
}

// Обробляє відключення конкретного клієнта: прибирає з таблиць, викликає deleteLater, оновлює список користувачів.
// sender це саме QTcpSocket, тому беремо його через qobject_cast.
void Server::onClientDisconnected()
{
    auto* s = qobject_cast<QTcpSocket*>(sender());
    if (!s)
        return;

    appendLog("Відключення: " + s->peerAddress().toString()
              + ":" + QString::number(s->peerPort()));

    clients.remove(s);
    rxBuffers.remove(s);

    s->deleteLater();

    broadcastUsers();
}

// Перемальовує список підключених користувачів у UI сервера.
// Це тільки візуалізація, клієнтам нічого не надсилає.
void Server::updateUsersView()
{
    QStringList rows;
    for (auto it = clients.cbegin(); it != clients.cend(); ++it)
        rows << it.value();

    ui->connectedUsersTextEdit->setText(rows.join("\n"));
}

// Формує пакет USERS і розсилає всім підключеним клієнтам, також оновлює UI сервера.
// У список потрапляє "unknown" доки клієнт не надіслав NICK.
void Server::broadcastUsers()
{
    QStringList nicks;
    for (auto it = clients.cbegin(); it != clients.cend(); ++it)
        nicks << it.value();

    ui->connectedUsersTextEdit->setText(nicks.join("\n"));

    const QString payload = "USERS " + nicks.join(";") + "\n";
    const QByteArray bytes = payload.toUtf8();

    for (auto it = clients.begin(); it != clients.end(); ++it)
        it.key()->write(bytes);
}

// TODO: Розглянути винесення розбору протоколу та обробки команд
// в окремий клас ProtocolHandler для відокремлення мережевої
// логіки від бізнес-логіки.

// Розсилає повідомлення всім клієнтам у форматі FROM.
// Це broadcast для загального чату, адресні повідомлення робляться окремо через TO.
void Server::broadcastMessage(const QString& fromNick, const QString& text)
{
    const QString payload = "FROM " + fromNick + ": " + text + "\n";
    const QByteArray bytes = payload.toUtf8();

    for (auto it = clients.begin(); it != clients.end(); ++it)
        it.key()->write(bytes);
}

// Розібирає один рядок протоколу
void Server::handleLine(QTcpSocket* s, const QString& line)
{
    if (line.startsWith("NICK "))
    {
        handleNick(s, line.mid(5));
        return;
    }

    if (line.startsWith("TO "))
    {
        handleTo(s, line.mid(3));
        return;
    }

    if (line.startsWith("MSG "))
    {
        handleMsg(s, line.mid(4));
        return;
    }

    appendLog("Невідомий пакет: " + line);
}

// NICK <nick>
void Server::handleNick(QTcpSocket* s, const QString& nickRaw)
{
    const QString nick = nickRaw.trimmed();
    clients[s] = nick.isEmpty() ? "unknown" : nick;

    appendLog("Нік: " + clients[s]);
    broadcastUsers();
}

// TO <nick1;nick2;...> <text>
void Server::handleTo(QTcpSocket* s, const QString& rest)
{
    // rest: "nick1;nick2 текст"
    const int spacePos = rest.indexOf(' ');
    if (spacePos <= 0)
    {
        appendLog("Некоректний TO пакет");
        return;
    }

    const QString targetsPart = rest.left(spacePos);
    const QString text = rest.mid(spacePos + 1);

    const QString from = clients.value(s, "unknown");
    const QStringList targets = targetsPart.split(';', Qt::SkipEmptyParts);

    // лог на сервері
    // appendLog("TO from " + from + " to " + targets.join(", ")); // без повідомлення
    appendLog("TO from " + from + " to " + targets.join(", ") + ": " + text);

    // відправляємо тільки вибраним адресатам
    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
        if (targets.contains(it.value()))
            it.key()->write(("FROM " + from + ": " + text + "\n").toUtf8());
    }
}

// MSG <text>  це всім
void Server::handleMsg(QTcpSocket* s, const QString& textRaw)
{
    const QString text = textRaw;
    const QString from = clients.value(s, "unknown");
    appendLog("MSG from " + from + ": " + text); // лог на сервері
    broadcastMessage(from, text);
}

// Головний слот readyRead  тільки буферизація і поділ на рядки
void Server::onReadyRead()
{
    auto* s = qobject_cast<QTcpSocket*>(sender());
    if (!s)
        return;

    // додаємо прочитане у буфер конкретного клієнта
    QByteArray& buf = rxBuffers[s];
    buf += s->readAll();

    // протокол рядковий, роздільник '\n'
    while (true)
    {
        const int nl = buf.indexOf('\n');
        if (nl < 0)
            break; // чекаємо поки прийде кінець рядка

        const QByteArray lineBytes = buf.left(nl);
        buf.remove(0, nl + 1);

        const QString line = QString::fromUtf8(lineBytes).trimmed();
        if (line.isEmpty())
            continue;

        // обробка команд протоколу
        handleLine(s, line);
    }
}


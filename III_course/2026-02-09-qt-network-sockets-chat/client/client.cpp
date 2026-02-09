// cpp_course/III_course/2026-02-09-qt-network-sockets-chat/client/client.cpp

//
// Created by tysser on 09.02.26.
//

#include "client.h"
#include "ui_client.h"

#include <QDateTime>
#include <QHostAddress>

Client::Client(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::Client),
      socket(new QTcpSocket(this)),
      clockTimer(new QTimer(this))
{
    ui->setupUi(this);

    connect(ui->connectButton, &QPushButton::clicked, this, &Client::onConnectClicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &Client::onSendClicked);
    connect(ui->inputLineEdit, &QLineEdit::returnPressed, this, &Client::onSendClicked);

    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);

    connect(clockTimer, &QTimer::timeout, this, &Client::onClockTick);
    clockTimer->start(1000);
    onClockTick();

    ui->chatPlainTextEdit->setReadOnly(true);
    ui->sendButton->setEnabled(false);
}

Client::~Client()
{
    socket->disconnectFromHost();
    delete ui;
}

// TODO: Винести форматування часу та додавання рядка з міткою
// у спільний утилітний модуль для клієнта і сервера.
void Client::onClockTick()
{
    ui->clockLabel->setText(QTime::currentTime().toString("HH:mm:ss"));
}

void Client::appendChat(const QString& text)
{
    const auto ts = QDateTime::currentDateTime().toString("HH:mm:ss");
    ui->chatPlainTextEdit->appendPlainText(ts + " " + text);
}

void Client::onConnectClicked()
{
    if (socket->state() == QAbstractSocket::ConnectedState)
        return;

    myNick = ui->nickLineEdit->text().trimmed();
    if (myNick.isEmpty())
    {
        appendChat("Впиши нік перед підключенням");
        return;
    }

    const QString host = ui->ipLineEdit->text().trimmed();
    const quint16 port = ui->portLineEdit->text().toUShort();

    socket->connectToHost(host, port);
    appendChat("Підключення до " + host + ":" + QString::number(port));
}

void Client::onConnected()
{
    appendChat("Підключено");
    ui->sendButton->setEnabled(true);

    socket->write(("NICK " + myNick + "\n").toUtf8());
}

void Client::onDisconnected()
{
    appendChat("Відключено");
    ui->sendButton->setEnabled(false);

    ui->usersListWidget->clear();
}

void Client::onSendClicked()
{
    // Перевірка стану з’єднання
    // Не дозволяємо відправку, якщо клієнт не підключений
    if (socket->state() != QAbstractSocket::ConnectedState)
        return;

    // Беремо текст із поля введення
    const QString text = ui->inputLineEdit->text().trimmed();

    // Порожні повідомлення не відправляємо
    if (text.isEmpty())
        return;

    // Отримуємо вибраних користувачів із QListWidget
    // Якщо нікого не вибрано це широкомовне повідомлення
    const auto selected = ui->usersListWidget->selectedItems();

    if (selected.isEmpty())
    {
        // Формат протоколу MSG текст, сервер розішле всім
        const QString packet = "MSG " + text + "\n";
        socket->write(packet.toUtf8());
    }
    else
    {
        // Формуємо список адресатів
        // Формат: TO nick1;nick2;nick3 текст
        QStringList targets;
        targets.reserve(selected.size());
        for (const auto* item : selected)
            targets << item->text(); // беремо нік прямо з QListWidget

        socket->write(("TO " + targets.join(";") + " " + text + "\n").toUtf8());
    }

    // Локально відображаємо відправлене повідомлення незалежно від типу (MSG або TO)
    appendChat("Я: " + text);

    // Очищаємо поле введення
    ui->inputLineEdit->clear();
}

// TODO: зробити декомпозицію
void Client::onReadyRead()
{
    // Дочитуємо всі доступні байти із сокета у буфер
    // Це потрібно, бо TCP може приносити дані частинами
    rxBuffer += socket->readAll();

    while (true)
    {
        // Шукаємо кінець одного логічного пакета
        // Протокол у нас рядковий, розділювач \n
        const int nl = rxBuffer.indexOf('\n');
        if (nl < 0)
            break; // повного рядка ще немає, чекаємо далі

        // Вирізаємо один повний рядок
        const QByteArray lineBytes = rxBuffer.left(nl);
        rxBuffer.remove(0, nl + 1);

        // Перетворюємо у QString та прибираємо зайві пробіли
        const QString line = QString::fromUtf8(lineBytes).trimmed();
        if (line.isEmpty())
            continue; // ігноруємо порожні рядки

        // ===== Обробка списку користувачів =====
        if (line.startsWith("USERS "))
        {
            // Формат: USERS nick1;nick2;nick3
            const QStringList users =
                line.mid(6).split(';', Qt::SkipEmptyParts);

            // Очищаємо поточний список у UI
            ui->usersListWidget->clear();

            // Додаємо всіх, крім себе
            // myNick вже ініціалізований при підключенні
            for (const QString& u : users)
            {
                if (u == myNick)
                    continue; // себе не показуємо

                ui->usersListWidget->addItem(u);
            }
            continue; // переходимо до наступного рядка
        }

        // ===== Обробка звичайного повідомлення =====
        if (line.startsWith("FROM "))
        {
            // Формат: FROM Nick: text
            // У чат виводимо без службового префікса
            appendChat(line.mid(5));
            continue;
        }

        // ===== Будь-який інший пакет =====
        // Виводимо як є, якщо сервер пришле щось нестандартне
        appendChat(line);
    }
}

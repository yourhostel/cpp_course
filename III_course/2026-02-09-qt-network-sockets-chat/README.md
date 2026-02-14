# `Qt6 TCP Client-Server Chat` [![YouTube](https://img.shields.io/badge/YouTube-Video-red?logo=youtube&logoColor=white)](https://youtu.be/zU6_6mor4UU)
(Практичне заняття №1. ЗМ2. ЛЗ1.)

Навчальний проект, що реалізує базову клієнт-серверну систему чату з використанням Qt6 та C++23.

Проект розроблено в рамках курсу об'єктно-орієнтованого програмування та зосереджено на:
- Архітектурі застосунку Qt6 Widgets
- Структурі проекту на основі CMake
- Розділенні виконуваних файлів клієнта та сервера
- Підготовці до TCP-сокетного зв'язку за допомогою модуля Qt Network

---

# Технологічний стек

- C++23
- Qt 6 (Widgets, Network)
- CMake
- Ninja

## Структура проекту

```text
│
├── client/
│ ├── main.cpp
│ ├── client.h
│ ├── client.cpp
│ ├── client.ui
│ └── CMakeLists.txt
│
├── server/
│ ├── main.cpp
│ ├── server.h
│ ├── server.cpp
│ ├── server.ui
│ └── CMakeLists.txt
│
└── CMakeLists.txt
```

---

## Компоненти UI сервера

| Назва компоненту       | Тип компоненту | Значення               |
|------------------------|----------------|------------------------|
| Server(клас)           | QMainWindow    | Сервер чату            |
| centralWidget          | QWidget        |                        |
| mainLayout             | QVBoxLayout    |                        |
| controlLayout          | QGridLayout    |                        |
| clockLabel             | QLabel         | 00:00:00               |
| ipLabel                | QLabel         | IP:                    |
| ipLineEdit             | QLineEdit      | 127.0.0.1              |
| portLabel              | QLabel         | Порт:                  |
| portLineEdit           | QLineEdit      | 5000                   |
| startButton            | QPushButton    | Запустити              |
| stopButton             | QPushButton    | Зупинити               |
| sessionLogLayout       | QVBoxLayout    |                        |
| sessionLogLabel        | QLabel         | Лог сесії              |
| sessionLogTextEdit     | QTextEdit      |                        |
| connectedUsersLayout   | QVBoxLayout    |                        |
| connectedUsersLabel    | QLabel         | Підключені користувачі |
| connectedUsersTextEdit | QTextEdit      |                        |

![1.png](screenshots/1.png)

---

## Компоненти UI клієнта

| Назва компоненту         | Тип компоненту | Значення                  |
|--------------------------|----------------|---------------------------|
| Client                   | QMainWindow    | Клієнт чату               |
| centralWidget            | QWidget        |                           |
| centralLayout            | QHBoxLayout    |                           |
| chatLayout               | QVBoxLayout    |                           |
| chatLabel                | QLabel         | Вікно чата:               |
| chatPlainTextEdit        | QPlainTextEdit |                           |
| usersListLayout          | QVBoxLayout    |                           |
| connectButton            | QPushButton    | З'єднати                  |
| usersListLabel           | QLabel         | Список користувачів:      |
| usersListWidget          | QListWidget    |                           |
| connectionSettingsLayout | QVBoxLayout    |                           |
| groupBox                 | QGroupBox      | Налаштування підключення: |
| ipLabel                  | QLabel         | IP:                       |
| ipLineEdit               | QLineEdit      | 127.0.0.1                 |
| nickLabel                | QLabel         | Нікнейм:                  |
| nickLineEdit             | QLineEdit      |                           |
| portLabel                | QLabel         | Порт:                     |
| portLineEdit             | QLineEdit      | 5000                      |
| inputLayout              | QGridLayout    |                           |
| clockLabel               | QLabel         | 00:00:00                  |
| inputLabel               | QLabel         | Повідомлення:             |
| inputLineEdit            | QLineEdit      |                           |
| sendButton               | QPushButton    | Надіслати                 |

![2.png](screenshots/2.png)

- **usersListWidget**
  - Обраний `QListWidget`, оскільки список користувачів є набором дискретних елементів, які потрібно динамічно оновлювати та вибирати для адресної відправки без парсингу тексту.

  - Застосовано `selectionMode: ExtendedSelection`, що дозволяє вибирати одного або кількох адресатів.  
  - Редагування елементів вимкнено (`NoEditTriggers`), щоб користувач не міг змінювати нік у списку вручну.

- **chatPlainTextEdit**
  - Обраний `QPlainTextEdit`, бо для логу повідомлень потрібен швидкий вивід великої кількості простого тексту і дешеве додавання рядків без важкого `rich text` механізму.
  - Порівняно з `QTextEdit`, `QPlainTextEdit` легший для такого сценарію і менше схильний до випадкового форматування.

---

## Модель роботи TCP у Qt6

- У проєкті використано асинхронну модель сокетів **Qt**.
  - Сервер використовує `QTcpServer`, який:
    - викликає `listen`
    - генерує сигнал `newConnection`
    - для кожного клієнта створює окремий `QTcpSocket`
  - Клієнт використовує `QTcpSocket`, який:
    - викликає `connectToHost`
    - генерує сигнал `connected`
    - приймає дані через сигнал `readyRead`
    - працює неблокуюче у подієвому циклі **Qt**
  - Обмін даними реалізовано поверх простого текстового протоколу з розділенням пакетів символом нового рядка `\n`.
  - Передача даних здійснюється через виклики `write`, які працюють асинхронно.
  - Отримання даних відбувається через сигнал `readyRead`, після чого дані зчитуються у буфер та обробляються згідно з прикладним текстовим протоколом.
    - Сервер:
      - `onReadyRead()` займається тільки буферизацією і виділенням рядків.
      - `handleLine()` виконує диспетчеризацію команд.
      - `handleNick()`, `handleTo()`, `handleMsg()` реалізують прикладну логіку протоколу.
    - Клієнт:
      Уся логіка обробки протоколу вбудована прямо в `Client::onReadyRead()`.
        - буферизація,
        - розбиття по `\n`
        - розбір `USERS`
        - розбір `FROM`
        - оновлення UI
  - При розірванні зʼєднання генерується сигнал `disconnected`.
  - Сервер підтримує окремий стан для кожного клієнта, включаючи відповідний `QTcpSocket` і буфер прийому.

![3.1.png](screenshots/3.1.png)

- Клієнт і сервер працюють як окремі процеси в межах однієї Linux машини.
  - Для тестування сервер і кілька клієнтів запускаються окремими процесами через скрипт `run.sh`.
  - Кожен процес має власний `QEventLoop`, який ізольовано обробляє свої події.
- Встановлення TCP-з’єднання відбувається через ядро Linux.
  - Listening сокет приймає запит.
  - Після `accept` сервер отримує окремий сокет для конкретної сесії.
- Події мережевого рівня трансформуються у **Qt** сигнали, які викликають відповідні слоти.
- У кожному процесі мережева логіка виконується в одному головному потоці.
  - Додаткові потоки для роботи сокетів у цій реалізації не використовуються.

## Bash для запуску кількох клієнтів одночасно

У `CMakeLists.txt` має відповідати `project(chat_server)` та `project(chat_client)`.

```bash
#!/usr/bin/env bash

# Строгий режим виконання:
# -e  зупинити скрипт при будь-якій помилці
# -u  помилка при використанні неініціалізованої змінної
set -eu

# Кількість клієнтів
CLIENTS=4

# Шлях до каталогу збірки (cmake-build-*)
BASE="/шлях/до/білду"

# Шляхи до виконуваних файлів
SERVER="$BASE/server/chat_server"
CLIENT="$BASE/client/chat_client"

# Запуск сервера у фоновому режимі
"$SERVER" &
server_pid=$!

# Невелика пауза, щоб сервер встиг почати слухати порт
sleep 0.5

# Запуск кількох клієнтів
for ((i=1; i<=CLIENTS; i++)); do
    "$CLIENT" &
done

# Очікування завершення сервера
wait $server_pid
```

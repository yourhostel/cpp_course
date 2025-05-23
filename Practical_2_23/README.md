# Файли та файлові потоки


| Бібліотека            | Призначення                                                                 | Стандарт       |
|------------------------|------------------------------------------------------------------------------|----------------|
| `<fstream>`            | Класичне читання/запис потоків (`ifstream`, `ofstream`, `fstream`)          | C++98          |
| `<filesystem>`         | Робота з файлами, шляхами, розмірами, копіюванням, видаленням               | C++17 (оновл. в C++20) |
| `<cstdio>`             | C-style API: `fopen`, `fread`, `fwrite`, `fseek`                            | C++98          |
| `<span>`               | Безпечне представлення діапазонів пам’яті (зручно з файлами)                | C++20          |
| `<ranges>`             | Потокове читання з файлів як range, наприклад `istream_view`                | C++20          |
| `<syncstream>`         | Паралельний вивід у потоки без блокувань (переважно для логів)              | C++20          |
| Boost.Iostreams        | Продвинута робота з потоками, фільтрами, стисненням                         | Зовнішня бібліотека |
| Memory-mapped файли    | Через OS або Boost.Interprocess (нема в std наразі)                         | -              |

## Приклади роботи з файлами у C++ (C++20/23)

Цей файл містить приклади використання стандартних засобів C++ для роботи з текстовими та бінарними файлами:

- **read_file_basic** — читає файл `example.txt` построчно через `std::getline`.
- **write_file_basic** — створює `output.txt` і записує в нього текст.
- **filesystem_info** — перевіряє наявність `example.txt`, виводить розмір і абсолютний шлях (`<filesystem>`).
- **read_file_ranges** — читає `example.txt` по словам через `std::ranges::istream_view<std::string>`.
- **read_binary_buffer** — зчитує `example.bin` в буфер, виводить байти у вигляді ASCII/HEX/escape (`\x..`) з точним контролем.
- **copy_file** — копіює `example.bin` у `example_copy.bin`.

> Шлях до файлів задається через `BASE_PATH`, щоб зручно працювати з відносно розташованими файлами у проєкті.

---

## Вимоги
- Стандарт: **C++23**
- Компілятор: `g++ 13+` або `clang++ 16+`
- Увімкнено: `std::ranges`, `std::filesystem`, `std::hex`, `std::isprint`

---

## Створення `example.bin` вручну (у Bash):
```bash
printf "ABCDEF" > example.bin
printf "\x00\x01\xFF" >> example.bin
```

## Режими відкривання файлів (std::ios)

| Режим             | Призначення                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| `std::ios::in`     | Відкрити файл для **читання**                                               |
| `std::ios::out`    | Відкрити файл для **запису** (очистить файл, якщо він існує)                |
| `std::ios::trunc`  | **Очистити** файл при відкритті (truncate)                                  |
| `std::ios::ate`    | Відкрити файл і **перемістити курсор у кінець**, але читати можна звідусюди |
| `std::ios::app`    | Відкрити для **дозапису** в кінець (завжди пише в кінець)                   |
| `std::ios::binary` | Відкрити файл у **бінарному режимі** (без перетворень `\n`, `\r\n`)         |

> std::ios::nocreate — не входить у стандарт C++ і в g++ відсутній. !
> Його сенс був такий:
> Відкрий файл ТІЛЬКИ якщо він існує, інакше — не створюй.

У сучасному C++ — перевірка вручну:
```c++
if (!fs::exists("file.txt")) {
    std::cerr << "Файл не існує!\n";
    return;
}

std::ifstream file("file.txt");
```
або
```c++
std::ifstream file("file.txt");
if (!file) {
    std::cerr << "Файл не відкрито\n";
}
```
---

Приклади:
```c++
// Читання текстового файлу
std::ifstream in("data.txt", std::ios::in);

// Запис з очищенням
std::ofstream out("log.txt", std::ios::out | std::ios::trunc);

// Дозапис в кінець
std::ofstream log("log.txt", std::ios::out | std::ios::app);

// Бінарне читання
std::ifstream bin("image.png", std::ios::in | std::ios::binary);
```
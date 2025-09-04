// file_io_examples.cpp

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string_view>
#include <ranges>
#include <vector>
#include <string>

namespace fs = std::filesystem;

// повний шлях некрасиво постійно писати можно додати константу шляху на папку
const std::string BASE_PATH = "/home/tysser/Scripts/jetbrains/cpp_course/Practical_2_23/";

// або зробити функцію-обгортку
std::string full_path(const std::string& filename)
{
    return BASE_PATH + filename;
}

//
// читання з файлу
//
void read_file_basic()
{
    std::ifstream file(BASE_PATH + "example.txt");
    if (!file)
    {
        std::cerr << "Не вдалося відкрити файл\n";
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << '\n';
    }
    file.close();
}

//
// запис у файл
//
void write_file_basic()
{
    std::ofstream file(BASE_PATH + "output.txt");
    if (!file)
    {
        std::cerr << "Не вдалося створити файл\n";
        return;
    }

    file << "Привіт, файл!\n";
    file << "Це новий рядок\n";
    file.close();
}

//
// робота з файловою системою
//
void filesystem_info()
{
    std::string path = full_path("example.txt");
    if (fs::exists(path))
    {
        std::cout << "Файл існує\n";
        std::cout << "Розмір: " << fs::file_size(path) << " байт\n";
        std::cout << "Абсолютний шлях: " << fs::absolute(path) << '\n';
    }
    else
    {
        std::cout << "Файл не знайдено\n";
    }
}

//
// Сучасний: зчитування файлу через ranges
//
void read_file_ranges()
{
    std::ifstream file(full_path("example.txt"));
    if (!file)
    {
        std::cerr << "Не вдалося відкрити файл\n";
        return;
    }
    // читає до першого whitespace (' ', \t, \n) потім наступна ітерація
    for (std::string line : std::ranges::istream_view<std::string>(file))
    {
        std::cout << ">> " << line << '\n';
    }
}

//
// буферизоване читання
//
void read_binary_buffer()
{
    std::ifstream file(full_path("example.bin"), std::ios::binary);
    if (!file)
    {
        std::cerr << "Не вдалося відкрити бінарний файл\n";
        return;
    }

    std::vector<char> buffer(1024);
    file.read(buffer.data(), buffer.size());
    std::streamsize bytes_read = file.gcount();
    std::cout << "Прочитано " << bytes_read << " байт\n";

    std::cout << "Вміст (ASCII/HEX):\n";
    for (int i = 0; i < bytes_read; ++i)
    {
            // ми явно **кастимо до `unsigned char`**,
            // бо std::isprint(...) очікує unsigned char
            unsigned char c = buffer[i];

        // Перевіряємо, чи байт є друкованим символом ASCII
        // (тобто A–Z, 0–9, ?, *, пробіл, пунктуація...)
        if (std::isprint(c))
            std::cout << c << ' ';

        // Якщо символ не друкований, то виводимо його
        // в hex-форматі типу \x41, \x00, \xFF
        else
            // \\x — щоб вивести буквально \x
            // std::hex — перемикаємо cout у шістнадцятковий режим
            // std::uppercase — великі літери A–F
            // static_cast<int>(c) — перетворюємо байт unsigned char на int,
            // бо cout не вміє напряму друкувати char як число
            // std::dec — повертаємо формат cout назад у десятковий,
            // щоб інші числа (типу bytes_read) не поламались
            std::cout << "\\x" << std::hex << std::uppercase << static_cast<int>(c) << std::dec << ' ';
    }
    std::cout << '\n';

    // 0x41 0x42 0x43 0x44 0x45 0x46 0x00 0x01 0xFF
    for (int i = 0; i < bytes_read; ++i)
    {
        unsigned char c = buffer[i];
        std::cout << "0x"
                  << std::hex << std::uppercase
                  << std::setw(2) << std::setfill('0')
                  << static_cast<int>(c)
                  << ' ';
    }
    std::cout << '\n';

    // \x41 \x42 \x43 \x44 \x45 \x46 \x00 \x01 \xF
    for (int i = 0; i < bytes_read; ++i)
    {
        unsigned char c = buffer[i];
        std::cout << "\\x"
                  << std::hex << std::uppercase
                  << std::setw(2) << std::setfill('0')
                  << static_cast<int>(c)
                  << ' ';
    }
    std::cout << '\n';
}

//
// копіювання файлу
//
void copy_file()
{
    fs::copy_file(full_path("example.bin"), full_path("example_copy.bin"), fs::copy_options::overwrite_existing);
    std::cout << "Файл скопійовано\n";
}

//
// Точка входу
//
int main()
{
    // read_file_basic();
    // write_file_basic();
    // filesystem_info();
    // read_file_ranges();
    // read_binary_buffer();
    copy_file();

    return 0;
}

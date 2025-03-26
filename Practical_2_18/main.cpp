#include <iostream>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>

using namespace std;

// Функція, яка демонструє використання append()
void exampleAppend() {
    // Приклад 1: злиття двох std::string
    std::string привітання = "Привіт, ";
    std::string імʼя = "Сергію!";
    привітання.append(імʼя);  // Додаємо імʼя до привітання

    std::cout << привітання << std::endl;  // Виведе: Привіт, Сергію!

    // Приклад 2: додавання символів з контейнера
    std::vector<char> значення = {'2', '3', '.', '5', 'C'};
    std::string текст = "Температура: ";

    // Додаємо символи з вектора, використовуючи ітератори
    текст.append(значення.begin(), значення.end());

    std::cout << текст << std::endl;  // Виведе: Температура: 23.5C
}

// Конвертація з UTF‑32 в UTF‑8
std::string to_utf8(const std::u32string& u32) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.to_bytes(u32);
}

// Функція, яка демонструє використання assign()
void exampleAssign() {
    // Приклад 1: Присвоєння нового значення рядку з іншого рядка
    std::u32string рядок;
    const std::u32string новийТекст = U"Привіт Assign!";
    рядок.assign(новийТекст);  // Копіюємо значення новийТекст у рядок

    std::cout << "Рядок після assign з рядка: " << to_utf8(рядок) << std::endl;

    // Приклад 2: Присвоєння символів з вектора
    std::vector<char32_t> дані = {
        U'П', U'р', U'и', U'в', U'і', U'т', U' ',
        U'c', U'h', U'a', U'r', U'3', U'2', U'_', U't', U' ',
        U'\U0001F600',  // emoji 😀
        U'漢'           // ієрогліф
    };
    рядок.assign(дані.begin(), дані.end());  // Присвоєння з діапазону ітераторів

    std::cout << "Рядок після assign з вектора: " << to_utf8(рядок) << std::endl;

    // Приклад 3: Присвоєння одного символу кілька разів
    рядок.assign(5, '*');  // ***** (п'ять зірочок)

    std::cout << "Рядок після assign символу '*': " << to_utf8(рядок) << std::endl;
}

int main() {
    // exampleAppend();
    exampleAssign();

    return 0;
}

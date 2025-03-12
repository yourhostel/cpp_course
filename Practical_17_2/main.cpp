// main.cpp

#include <iostream>
#include <random>
#include <iomanip>
#include <cstring>

using namespace std;

// Функція для генерації випадкового числа у заданому діапазоні
int randInRange(const int min, const int max) {
    static random_device rd;
    // Використовуємо std::mt19937 замість rand() для більш рівномірного розподілу
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void printCharCodesFromInput() {
    constexpr size_t N = 20; // Максимальна довжина рядка
    char c[N]; // Масив символів

    cout << "Enter line: ";
    cin.getline(c, N); // Введення рядка

    const size_t t = strlen(c); // Визначення довжини

    for (size_t i = 0; i < t; i++) {
        // Виводимо значення типу char (може бути від’ємним)
        cout << static_cast<int>(c[i]) << " ";
    }

    cout << endl;
}

void replaceDotsAndCount() {
    string input;

    cout << "Enter string: ";
    getline(cin, input); // Зчитуємо рядок повністю (без обмеження байтами)

    size_t symbolCount = 0; // Лічильник символів
    size_t byteIndex = 0;   // Лічильник байтів
    int dotCount = 0;       // Лічильник замінених крапок

    // Спочатку підраховуємо символи та визначаємо потрібний розмір пам’яті
    while (byteIndex < input.size()) {
        if ((input[byteIndex] & 0xC0) != 0x80) { // Початок нового символу UTF-8
            if (symbolCount == 15) { // Якщо досягли 15 символів, зупиняємося
                break;
            }
            symbolCount++;
        }
        byteIndex++;
    }

    // Виділяємо пам’ять рівно під 15 символів + 1 для '\0'
    vector<char> result(byteIndex + 1, '\0');

    // Копіюємо дані в новий масив, замінюючи '.' на '_'
    for (size_t i = 0; i < byteIndex; i++) {
        result[i] = (input[i] == '.') ? '_' : input[i];
        if (input[i] == '.') {
            dotCount++; // Підраховуємо кількість замін
        }
    }

    cout << "length = " << symbolCount << endl;
    cout << "Number of dots: " << dotCount << endl;
    cout << "Updated string: " << result.data() << endl;
}

int main() {
    // printCharCodesFromInput();
    replaceDotsAndCount();

    return 0;
}

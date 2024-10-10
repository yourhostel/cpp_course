#include <iostream>
#include <windows.h>
#include <cmath>
#include <format>
#include <numbers> // Для використання константи pi

using namespace std;

// Встановлює кодування UTF-8
void setUtf8Encoding() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Функція для введення x, y і обчислення a, b, c
void calculate_abc() {
    double x, y;

    // Введення значень x та y
    cout << "Введіть значення x=";
    cin >> x;
    cout << "Введіть значення y=";
    cin >> y;

    // Обчислення a
    double a = log(abs(y - sqrt(abs(x))) * (x - (y / (x + pow(x, 2) / 4))));

    // Обчислення b
    double b = exp(x) * ((pow(y, 2) + 12 * x * y - 3 * pow(x, 2)) / (18 * y - 1));

    // Обчислення c
    double c = (std::numbers::pi + cos(x * y)) / (sin(y) - x * std::numbers::pi) + 6 / x;

    // Виведення результатів
    cout << format("a = {:.4f}\n", a);
    cout << format("b = {:.4f}\n", b);
    cout << format("c = {:.4f}\n", c);
}

// Функція для обчислення довжини кола та площі круга
void calculate_circle() {
    double R;

    // Введення значення радіуса R
    cout << "Введіть значення радіуса R=";
    cin >> R;

    // Перевірка, що R є додатним числом
    if (R <= 0) {
        cout << "Радіус повинен бути додатним числом.\n";
        return;
    }

    // Обчислення довжини кола L = 2 * π * R
    double L = 2 * numbers::pi * R;

    // Обчислення площі круга S = π * R^2
    double S = numbers::pi * R * R;

    // Виведення результатів
    cout << format("Довжина кола L = {:.4f}\n", L);
    cout << format("Площа круга S = {:.4f}\n", S);
}

// Функція для обчислення значення y
void calculate_y() {
    const double x = 1.52; // Задане значення x
    const double c = 5;    // Задане значення c

    // Обчислення b = sqrt(x)
    double b = sqrt(x);

    // Обчислення a = cbrt(abs(b + c))
    double a = cbrt(abs(b + c));

    // Обчислення y = a * sin^2(b) + b * cos(a^2)
    double y = a * pow(sin(b), 2) + b * cos(pow(a, 2));

    // Виведення результатів
    cout << format("Значення a = {:.4f}\n", a);
    cout << format("Значення b = {:.4f}\n", b);
    cout << format("Значення y = {:.4f}\n", y);
}

int main()
{
    setUtf8Encoding();
    cout << "calculate_abc :" << "\n";
    calculate_abc();
    cout << "\n" << "calculate_circle :" << "\n";
    calculate_circle();
    cout << "\n" << "calculate_y :" << "\n";
    calculate_y();
    return 0;
}

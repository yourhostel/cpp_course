﻿#include <iostream>  // Підключаємо бібліотеку для вводу-виводу
#include <windows.h> // Підключаємо бібліотеку для роботи з функціями Windows

using namespace std;

int main() {
    // Встановлюємо кодування для виводу та вводу в консоль
    SetConsoleCP(1251); // Встановлює кодування для вводу (CP1251 для кирилиці)
    SetConsoleOutputCP(1251); // Встановлює кодування для виводу (CP1251 для кирилиці)

    char name[20]; // Оголошуємо масив символів для збереження імені

    // Виводимо питання та зчитуємо ім'я користувача
    cout << "Як тебе звати?" << endl;
    cin >> name;

    // Виводимо привітання з введеним ім'ям
    cout << "Привіт, " << name << endl;

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    return 0; // Повертаємо 0, що означає успішне завершення програми
}
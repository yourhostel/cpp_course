#include <iostream>
#include <windows.h>

using namespace std;
void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Приклад 1.
const int n = 10; // Розмір масиву

// Функція для обчислення суми від'ємних елементів масиву
void sumNegativeElements()
{
    int a[n];
    int suma = 0; // Змінна для зберігання суми

    cout << "Введіть масив А (10 елементів):\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i]; // Введення елементів масиву
        if (a[i] < 0) // Перевірка на від'ємність
        {
            suma += a[i]; // Додавання до суми
        }
    }

    cout << "Сума від'ємних елементів = " << suma << endl;
}

int main()
{
    // setlocale(LC_ALL, "uk_UA"); // for my Linux system.
    setUtf8Encoding(); // for my Windows system.

    // sumNegativeElements();
    return 0;
}

#include <iostream>
#include "console_utils.h" // Підключаємо наші функції кодування

using namespace std;

// Функція для обробки введення чисел та виведення їх суми
void processSum() {
    // Встановлюємо кодування для кирилиці
    setCyrillicEncoding();

    int num1, num2, num3;
    int sum;

    cout << "Введіть перше число: ";
    cin >> num1;

    cout << "Введіть друге число: ";
    cin >> num2;

    cout << "Введіть третє число: ";
    cin >> num3;

    sum = num1 + num2 + num3;

    cout << "Сума чисел: " << sum << endl;


    // Повертаємо кодування до UTF-8
    setUtf8Encoding();

}

int main() {
    // Викликаємо функцію обробки
    processSum();

    return 0;

}


#include <iostream>
#include <windows.h>
#include <random>

using namespace std;

void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Основна функція для перестановки першої та останньої цифри числа
int swapFirstAndLastDigits(int number)
{
    int firstDigit = number / 10000;         // Перша цифра
    int lastDigit = number % 10;            // Остання цифра
    int middlePart = (number % 10000) / 10; // Середня частина числа

    if (lastDigit > firstDigit)
    {
        // Перестановка цифр
        return lastDigit * 10000 + middlePart * 10 + firstDigit;
    }

    // Якщо умова не виконується, повертаємо початкове число
    return number;
}

// Шаблон для запиту коректного вводу значення
template <integral T>
T getValidatedInput(const string& prompt)
{
    T value;

    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.good() && value >= 10000 && value <= 99999) // Умови для п’ятизначного числа
        {
            return value; // Повертаємо коректне значення
        }

        cout << "Некоректне число. Спробуй ще раз." << endl;

        // Скидаємо потік вводу, якщо помилка
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Функція для взаємодії з користувачем
void executeDigitSwap()
{
    // Запитуємо п'ятизначне число
    int number = getValidatedInput<int>("Введіть п'ятизначне натуральне число: ");

    // Викликаємо основну функцію
    int result = swapFirstAndLastDigits(number);

    // Виводимо результат
    cout << "Результат: " << result << endl;
}

// Основна функція для знаходження найбільшої цифри числа
int findMaxDigit(int number)
{
    int maxDigit = 0;

    // Послідовно виділяємо цифри числа
    while (number > 0)
    {
        int currentDigit = number % 10; // Отримуємо останню цифру
        if (currentDigit > maxDigit)
        {
            maxDigit = currentDigit; // Оновлюємо максимальну цифру
        }
        number /= 10; // Видаляємо останню цифру
    }

    return maxDigit;
}

// Шаблон для запиту корректного вводу значення
template <integral T>
T getValidatedInput2(const string& prompt)
{
    T value;

    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.good() && value > 0) // Умови для натурального числа
        {
            return value; // Повертаємо коректне значення
        }

        cout << "Некоректне число. Спробуйте ще раз." << endl;

        // Скидаємо потік вводу, якщо помилка
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Функція для взаємодії з користувачем
void executeFindMaxDigit()
{
    // Запитуємо натуральне число
    int number = getValidatedInput2<int>("Введіть натуральне число: ");

    // Викликаємо основну функцію
    int result = findMaxDigit(number);

    // Виводимо результат
    cout << "Найбільша цифра числа: " << result << endl;
}

// Основна функція для зміни порядку цифр числа
int reverseDigits(int number)
{
    int reversed = 0;

    while (number > 0)
    {
        int currentDigit = number % 10; // Отримуємо останню цифру
        reversed = reversed * 10 + currentDigit; // Додаємо цифру до нового числа
        number /= 10; // Видаляємо останню цифру
    }

    return reversed;
}

// Функція для взаємодії з користувачем
void executeReverseDigits()
{
    // Запитуємо натуральне число
    int number = getValidatedInput2<int>("Введіть натуральне число: ");

    // Викликаємо основну функцію
    int result = reverseDigits(number);

    // Виводимо результат
    cout << "Число після зміни порядку цифр: " << result << endl;
}

int main()
{
    setUtf8Encoding();

    // executeDigitSwap(); // Виконання першої задачі
    // executeFindMaxDigit(); // Виконання другої задачі
    executeReverseDigits(); // Виконання третьої задачі
    return 0;
}

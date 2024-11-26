#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Функція для обчислення значення суми ряду
double calculateSeriesSum(double x)
{
    double sum = 0.0;

    for (int k = 1; k <= 10; ++k)
    {
        // Обчислення факторіалу k
        double factorial = 1.0;
        for (int i = 1; i <= k; ++i)
        {
            factorial *= i;
        }

        // Обчислення поточного члена ряду
        double term = pow(x, 2 * k) / (pow(2, k) * factorial);
        sum += term; // Накопичення суми
    }

    return sum;
}

// Функція для виконання обчислення
void executeSeriesCalculation()
{
    double x;
    cout << "Введіть значення x: ";
    cin >> x;

    double result = calculateSeriesSum(x); // Виклик основної функції обчислення
    cout << "Значення суми S: " << result << endl;
}

// Функція для виконання обчислення послідовності для одного числа
int collatzSteps(int number)
{
    int steps = 0;

    cout << "Послідовність для числа " << number << ": ";

    while (number != 1)
    {
        cout << number << " "; // Виводимо поточне число

        if (number % 2 == 0)
        {
            number /= 2; // Якщо парне, ділимо на 2
        }
        else
        {
            number = number * 3 + 1; // Якщо непарне, множимо на 3 і додаємо 1
        }
        steps++;
    }
    cout << "1" << endl; // Завершуємо послідовність

    return steps; // Повертаємо кількість кроків
}

// Функція для перевірки діапазону чисел
void checkSyracuseRange(int start, int end)
{
    for (int number = start; number <= end; ++number)
    {
        cout << "Число " << number << ": ";
        int steps = collatzSteps(number);
        cout << "Кількість кроків = " << steps << endl;
    }
}

// Функція для виконання перевірки
void executeSyracuseCheck()
{
    int start, end;
    cout << "Введіть початок діапазону: ";
    cin >> start;
    cout << "Введіть кінець діапазону: ";
    cin >> end;

    if (start <= 0 || end <= 0 || start > end)
    {
        cout << "Помилка: діапазон має бути додатнім і початок не може перевищувати кінець." << endl;
        return;
    }

    checkSyracuseRange(start, end);
}

// Функція для виведення символів * по діагоналях квадрата
void printDiagonals(int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // Умова для діагоналей: головна або побічна діагональ
            if (i == j || i + j == size - 1)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl; // Перехід на новий рядок
    }
}

// Функція для виконання програми
void executeDiagonalPrinting()
{
    int size;
    cout << "Введіть розмір квадрата: " << endl;
    cin >> size;

    if (size <= 0)
    {
        cout << "Розмір квадрата має бути додатнім!" << endl;
        return;
    }

    printDiagonals(size);
}

int main()
{
    setUtf8Encoding();

    //executeSeriesCalculation();
    //executeSyracuseCheck();
    executeDiagonalPrinting();
    return 0;
}

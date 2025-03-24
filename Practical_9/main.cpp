#include <iostream>
#include <windows.h>
#include <cmath>
#include <random>

using namespace std;

void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Функція для обчислення значення суми
double calculateSum(double x)
{
    double sum = 0.0;
    int k = 2;

    while (k <= 9)
    {
        // Обчислення поточного члена ряду
        double term = (tan(x) - (x * x) / k) / (k * k - 1);
        sum += term; // накопичення суми
        k++; // перехід до наступного значення k
    }

    return sum;
}

// Функція для запиту введення, виклику обчислення та виведення результату
void executeCalculation()
{
    double x;
    cout << "Введіть значення x: " << endl;
    cin >> x;

    double result = calculateSum(x); // Виклик основної функції обчислення
    cout << "Значення суми: " << result << endl;
}

// Функція для обчислення максимальної кількості розташованих поспіль додатних чисел
int findMaxPositiveSequence()
{
    int maxSequence = 0; // змінна для зберігання максимальної довжини послідовності
    int currentSequence = 0; // змінна для поточної довжини послідовності
    int num;

    cout << "Введіть послідовність чисел (закінчіть ввод числом 0):" << endl;

    while (true)
    {
        cin >> num;

        if (num == 0)
        {
            break; // завершити цикл, якщо введено 0
        }

        if (num > 0)
        {
            currentSequence++; // збільшуємо поточну довжину послідовності
            if (currentSequence > maxSequence)
            {
                maxSequence = currentSequence; // оновлюємо максимальну довжину
            }
        }
        else
        {
            currentSequence = 0; // обнуляємо поточну довжину послідовності при негативному числі
        }
    }

    return maxSequence;
}

// Функція для виконання обчислення і виводу результату
void executeCalculation2()
{
    int result = findMaxPositiveSequence();
    cout << "Максимальна кількість розташованих поспіль додатних чисел: " << result << endl;
}

// Функція для обчислення номера дня, на який пробіг стане не менше y
int findTargetDay(double x, double y)
{
    int day = 1;
    double distance = x;

    while (distance < y)
    {
        distance *= 1.1; // збільшуємо дистанцію на 10%
        day++; // переходимо до наступного дня
    }

    return day;
}

// Функція для виконання обчислення та виводу результату
void executeCalculation3()
{
    double x, y;
    cout << "Введіть початковий пробіг (x): " << endl;
    cin >> x;
    cout << "Введіть цільовий пробіг (y): " << endl;
    cin >> y;

    int targetDay = findTargetDay(x, y);
    cout << "Номер дня, на який пробіг спортсмена становитиме не менше " << y << " км: " << targetDay << endl;
}

int main()
{
    setUtf8Encoding();
    //executeCalculation();
    //executeCalculation2();
    executeCalculation3();
    return 0;
}


#include <iostream>
#include <windows.h>
#include <random>

using namespace std;

// локальна константа використовується у 2 та 3 завданнях
// обчислюємо на етапі компіляції, а не в рантаймі
constexpr double epsilon = 1e-4;

void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Функція для обчислення факторіала
double factorial(int num)
{
    double result = 1.0;
    for (int i = 1; i <= num; ++i)
    {
        result *= i;
    }
    return result;
}

// Рекурсивна функція для обчислення факторіала
double  recursive_factorial(const int num)
{
    if (num <= 1) return 1.0; // базовий випадок: факторіал 0 та 1 дорівнює 1
    return num * recursive_factorial(num - 1); // рекурсивний випадок
}

// Функція для обчислення суми ряду
double calculateSeriesSum(double x, int n)
{
    double sum = 0.0;

    for (int k = 1; k <= n; ++k)
    {
        // Чисельник і знаменник окремо
        double numerator = pow(x, 2 * k - 1); // x^(2k-1)
        double denominator = pow(2, 2 * k - 1) * recursive_factorial(2 * k - 1); // 2^(2k-1) * (2k-1)!

        // Застосування (-1)^(k+1) до дробу
        double term = pow(-1, k + 1) * (numerator / denominator);

        sum += term; // Додаємо член до суми
    }

    return sum;
}

// Функція для виконання обчислення
void executeSeriesCalculation()
{
    double x;
    int n;

    cout << "Введіть значення x: " << endl;
    cin >> x;
    cout << "Введіть значення n (натуральне число): " << endl;
    cin >> n;

    if (n <= 0)
    {
        cout << "Помилка: n має бути натуральним числом!" << endl;
        return;
    }

    double result = calculateSeriesSum(x, n);
    cout << "Сума ряду: " << result << endl;
}

// Функція для обчислення суми ряду
double calculateSeriesSum(double epsilon)
{
    double sum = 0.0;
    int n = 1;

    while (true)
    {
        // Обчислення поточного члена ряду
        double term = factorial(n) / pow(n, n);
        if (fabs(term) < epsilon) // Якщо модуль члена менший за epsilon, зупиняємо цикл
        {
            break;
        }
        sum += term; // Додаємо член до суми
        ++n;
    }

    return sum;
}

// Функція для виконання обчислення
void executeSeriesCalculation2()
{

    cout << "Використовується epsilon = " << epsilon << endl;

    double result = calculateSeriesSum(epsilon);
    cout << "Сума членів ряду: " << result << endl;
}

// Функція для обчислення наближеного значення суми ряду
double calculateArctanApprox(double x, double epsilon)
{
    double sum = 0.0;
    double term = x; // Перший член ряду
    int m = 1;

    while (fabs(term) >= epsilon)
    {
        sum += term; // Додаємо поточний член до суми

        // Обчислюємо наступний член ряду
        ++m;
        term = pow(-1, m - 1) * pow(x, 2 * m - 1) / (2 * m - 1);
    }

    return sum;
}

// Функція для виконання обчислення та порівняння результатів
void executeArctanComparison()
{
    double x;

    cout << "Введіть значення x (x ∈ [-1; 1]): " << endl;
    cin >> x;

    if (x < -1 || x > 1)
    {
        cout << "Помилка: x має бути в межах [-1; 1]!" << endl;
        return;
    }

    // Обчислення наближеного значення суми ряду
    double approx = calculateArctanApprox(x, epsilon);
    // Точне значення arctan(x)
    double exact = atan(x);

    // Виведення результатів
    cout << "Наближене значення суми ряду: " << approx << endl;
    cout << "Точне значення arctg(x): " << exact << endl;
    cout << "Різниця між значеннями: " << fabs(approx - exact) << endl;
}

int main()
{
    setUtf8Encoding();

    // executeSeriesCalculation();
    // executeSeriesCalculation2();
    executeArctanComparison();

    return 0;
}

#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Функція для першого завдання: Сума двох найбільших чисел
double sumOfTwoLargest(double a, double b, double c)
{
    if (a <= b && a <= c) return b + c;  // a найменше
    if (b <= a && b <= c) return a + c;  // b найменше
    return a + b;                        // c найменше

}

// Функція для першого завдання: Сума двох найбільших чисел(2 спосіб)
double sumOfTwoLargest2(double a, double b, double c)
{
    double max1 = max(a, max(b, c));  // Знаходимо найбільше число
    double min1 = min(a, min(b, c));  // Знаходимо найменше число
    return a + b + c - min1;          // Сума двох найбільших чисел
}

// Функція для перевірки положення точки щодо осей
int checkPointOnAxes(int x, int y)
{
    if (x == 0 && y == 0) return 0; // Точка в початку координат
    if (x == 0) return 1;            // Точка на осі Y
    if (y == 0) return 2;            // Точка на осі X
    return 3;                        // Точка не лежить на жодній з осей
}

void printPointPosition(int x, int y)
{
    switch (checkPointOnAxes(x, y))
    {
    case 0:
        cout << "Точка (" << x << ", " << y << ") знаходиться в початку координат" << "\n\n";
        break;
    case 1:
        cout << "Точка (" << x << ", " << y << ") лежить на осі Y" << "\n\n";
        break;
    case 2:
        cout << "Точка (" << x << ", " << y << ") лежить на осі X" << "\n\n";
        break;

    default: cout << "Точка (" << x << ", " << y << ") не лежить на жодній з осей" << "\n\n";
    }
}

// Функція для третього завдання: Перевірка, чи три точки на одній прямій
bool checkCollinear(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1) ? 0 : 1;
}

// Функція для виведення результату перевірки
void printCollinearResult(int x1, int y1, int x2, int y2, int x3, int y3)
{
    switch (checkCollinear(x1, y1, x2, y2, x3, y3)) {
    case 0:
        cout << "Точки (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << "), (" << x3 << ", " << y3 << ") лежать на одній прямій." << "\n\n";
        break;
    case 1:
        cout << "Точки (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << "), (" << x3 << ", " << y3 << ") не лежать на одній прямій." << "\n\n";
        break;
    }
}

// Функція для четвертого завдання: Порівняння площ трикутника та квадрата
int compareTriangleAndSquare(double a, double b, double c)
{
    // Знаходимо найменшу сторону трикутника для квадрата
    double minSide = min(a, min(b, c));

    // Площа квадрата
    double squareArea = minSide * minSide;

    // Площа трикутника за формулою Герона
    double s = (a + b + c) / 2.0;
    double triangleArea = sqrt(s * (s - a) * (s - b) * (s - c));

    // Повертаємо код залежно від порівняння площ
    return (triangleArea > squareArea) ? 0 : 1;
}

// Функція для виведення результату порівняння площ
void printComparisonResult(double a, double b, double c)
{
    switch (compareTriangleAndSquare(a, b, c)) {
    case 0:
        cout << "Площа трикутника більша за площу квадрата." << "\n\n";
        break;
    case 1:
        cout << "Площа квадрата більша за площу трикутника." << "\n\n";
        break;
    }
}

int main()
{
    setUtf8Encoding();

    // Приклад використання функції для першого завдання
    double a = 5.0, b = 7.0, c = -14.0;
    cout << "Сума двох найбільших чисел (перший варіант): " << sumOfTwoLargest(a, b, c) << endl;
    cout << "Сума двох найбільших чисел (другий варіант): " << sumOfTwoLargest2(a, b, c) << "\n\n";

    // Приклад використання функції для другого завдання
    int x = 4, y = 4;
    printPointPosition(x, y);

    // Приклад використання функції для третього завдання
    int x1 = 1, y1 = 1, x2 = 2, y2 = 2, x3 = 3, y3 = 3;
    printCollinearResult(x1, y1, x2, y2, x3, y3);

    // Приклад використання функції для четвертого завдання
    double side1 = 6.0, side2 = 8.0, side3 = 10.0;
    printComparisonResult(side1, side2, side3);

    return 0;
}

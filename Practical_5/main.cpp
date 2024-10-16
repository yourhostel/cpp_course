#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}
/*
1. Дано три дійсних числа, що визначають довжину сторін деякого трикутника.
З’ясувати, чи існує такий трикутник.
*/

bool isTriangle(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

void checkTriangle()
{
    double a, b, c;
    cout << "Введіть довжини сторін трьохкутника: " << endl;;
    cin >> a >> b >> c;
    if (isTriangle(a, b, c)) {
        cout << "Такий трикутник існує." << endl;
    } else {
        cout << "Такий трикутник не існує." << endl;
    }

}

/*
2. Задано координати лівої верхньої і правої нижньої вершин прямокутника (х1,
у1) і (х2, у2). Визначити чи належить точка А (х, у) цьому прямокутнику.
*/
bool checkPointInRect(double x1, double y1, double x2, double y2, double x, double y) {
    return (x >= x1 && x <= x2 && y >= y2 && y <= y1);
}

void checkPoint()
{
    double x1, y1, x2, y2, x, y;
    cout << "Введіть координати лівої верхньої вершини прямокутника (x1, y1): " << endl;;
    cin >> x1 >> y1;
    cout << "Введіть координати правої нижньої вершини прямокутника (x2, y2): " << endl;;
    cin >> x2 >> y2;
    cout << "Введіть координати точки (x, y): " << endl;;
    cin >> x >> y;

    if (checkPointInRect(x1, y1, x2, y2, x, y))
    {
        cout << "Точка належить прямокутнику." << endl;
    }
    else
    {
        cout << "Точка не належить прямокутнику." << endl;
    }
}

/*
3. Ввести два числа і визначити, що більше: сума квадратів чи квадрат суми цих чисел.
Відповідь вивести у вигляді повідомлення.
*/

string whichIsGreater(double a, double b)
{
    double sumOfSquares = a * a + b * b;
    double squareOfSum = (a + b) * (a + b);

    if (sumOfSquares > squareOfSum) return "Сума квадратів більша.";

    if (squareOfSum > sumOfSquares) return "Квадрат суми більший.";

    return "Вони рівні.";
}

void checkWhichIsGreater()
{
    double a, b;
    cout << "Введіть два числа: " << endl;
    cin >> a >> b;

    string result = whichIsGreater(a, b);
    cout << result << endl;
}

/*
4. Обчислити значення виразу y залежно від умов:
y =
    (a * sin^2(zx) + cos(zx)) / (cos^3(zx) + zx) при x < ln(a)
    ln(a) <= x <= b, при x знаходиться у межах ln(a) і b
    sqrt(2.5a^3 + (b - zx)^6) при x > b
*/

double calculateValue(double x, double z, double a, double b) {
    if (x < log(a)) return a * pow(sin(x), 2) + cos(z * x);

    if (x >= log(a) && x <= b) return pow(cos(a + z * x), 3);

    return sqrt(2.5 * pow(a, 3) + pow(b - z * pow(x, 2), 6));
}

void calculateValueResult() {
    double x, z = 1.2, a = 1.5, b = -1.7;

    cout << "Введіть значення x: " << endl;
    cin >> x;

    double result = calculateValue(x, z, a, b);

    cout << "Результат обчислення: " << result << endl;
}

int main()
{
    setUtf8Encoding();

    // Перевірка трикутника
    cout << "checkTriangle :" << "\n";
    checkTriangle();

    // Перевірка, чи належить точка прямокутнику
    cout << "checkPoint :" << "\n";
    checkPoint();

    // Перевірка, що більше: сума квадратів чи квадрат суми
    cout << "checkWhichIsGreater :" << "\n";
    checkWhichIsGreater();

    // Обчислення значення функції
    cout << "calculateValueResult :" << "\n";
    calculateValueResult();

    return 0;
}

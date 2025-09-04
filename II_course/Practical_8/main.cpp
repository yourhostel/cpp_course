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

// Функція для обчислення значення f(x) = e^x + 3 * sin(x)
void calculateFunctionValues()
{
    cout << "Обчислення значення функції f(x) = e^x + 3 * sin(x) на відрізку [0; 2] з кроком h = 0.5" << endl;

    for (int i = 0; i <= 4; i++)
    {
        // h — це стала, яка обчислюється під час компіляції й не змінюватиметься протягом програми.
        constexpr double h = 0.5; // constexpr - значення змінної, функції чи виразу можна обчислити під час компіляції, а не під час виконання програми
        const double x = i * h; // обчислення x на основі i
        const double f_x = exp(x) + 3 * sin(x); // обчислення значення функції
        cout << "f(" << x << ") = " << f_x << endl;
    }
}

// Функція для обчислення суми S = ∑(i=1 to 9) i * sin((i + 2) * x)
double calculateSum(const double x) {
    double S = 0.0;

    for (int i = 1; i <= 9; ++i) {
        S += i * sin((i + 2) * x); // обчислення i * sin((i + 2) * x) та додавання до суми
    }

    return S;
}

// Функція для введення x, обчислення та виведення результату
void executeCalculation() {
    double x;
    cout << "Введіть значення x: " << endl;
    cin >> x;

    const double result = calculateSum(x);
    cout << "Значення суми S: " << result << endl;
}

// Функція для виведення квадратів натуральних чисел, що не перевищують N
void printSquaresUpToN(const int N) {
    int i = 1;

    cout << "Квадрати натуральних чисел, що не перевищують " << N << ":" << endl;

    while (i * i <= N) {
        cout << i * i << " ";
        ++i;
    }
    cout << endl;
}

// Функція для введення числа N і запуску обчислень
void executeSquareCalculation() {
    int N;
    cout << "Введіть число N: " << endl;
    cin >> N;

    printSquaresUpToN(N);
}

// Функція для гри у вгадування числа
void playGuessingGame()
{
    random_device rd; // джерело ентропії
    mt19937 gen(rd()); // генератор випадкових чисел Mersenne Twister
    uniform_int_distribution<> dist(0, 100); // діапазон від 0 до 100
    const int target = dist(gen); // генеруємо випадкове число

    int guess;
    constexpr int attempts = 10;

    cout << "Гра: Вгадайте число від 0 до 100. У вас є 10 спроб." << endl;

    for (int i = 1; i <= attempts; ++i)
    {
        cout << "Спроба " << i << ": Введіть ваше число: " << endl;
        cin >> guess;

        if (guess == target)
        {
            cout << "Вітаємо! Ви вгадали число " << target << " за " << i << " спроб(у/и)." << endl;
            return;
        }
        else if (guess < target)
        {
            cout << "Загадане число більше." << endl;
        }
        else
        {
            cout << "Загадане число менше." << endl;
        }
    }

    // Якщо за 10 спроб число не вгадане
    cout << "На жаль, ви не вгадали число за 10 спроб. Загадане число було: " << target << endl;
}

auto main() -> int // trailing return type є частиною стандарту C++11 (arrow function)
{
    setUtf8Encoding();
    //calculateFunctionValues();
    //executeCalculation();
    //executeSquareCalculation();
    playGuessingGame();
    return 0;
}

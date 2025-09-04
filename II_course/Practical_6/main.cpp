#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

void setUtf8Encoding()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

double calculateY(double x, int L)
{
    switch (L)
    {
    case 1: return sqrt(x) + exp(x);
    case 2: return log(abs(x)) + 0.8;
    case 3: return pow(x, 2) / pow(log10(abs(x)), 2);  // x^2 / (lg(|x|))^2
    case 4: return x * pow(cos(x), 2) + sqrt(abs(x));
    case 5: return exp(0.8 * x) + abs(x);
    default: return 0.0; // Некоректне значення
    }
}

void calculateCircleElements(double R)
{
    double D = 2 * R;
    double L = 2 * M_PI * R;
    double S = M_PI * pow(R, 2);

    cout << "Радіус: " << R << endl;
    cout << "Діаметр: " << D << endl;
    cout << "Довжина: " << L << endl;
    cout << "Площа: " << S << endl;
}

void printMinutesDescription(int N) {
    if (N < 0 || N > 59) {

        cout << "Число не в діапазоні 0-59" << endl;
        return;
    }

    cout << N << " ";

    if ((N % 100 >= 11 && N % 100 <= 19)) {
        cout << "хвилин" << endl;
    } else {
        switch (N % 10) {
        case 1:
            cout << "хвилина" << endl;
            break;
        case 2:
        case 3:
        case 4:
            cout << "хвилини" << endl;
            break;
        default:
            cout << "хвилин" << endl;
            break;
        }
    }
}

int main()
{
    setUtf8Encoding();

    double x;
    int L, N;

    // // Завдання 1
    // cout << "Введіть x: "  << endl;
    // cin >> x;
    // cout << "Виберіть L (від 1 до 5): " << endl;
    // cin >> L;
    // cout << "Результат: " << calculateY(x, L) << endl;
    //
    // // Завдання 2
    // double R;
    // cout << "Введіть радіус R: " << endl;
    // cin >> R;
    // calculateCircleElements(R);

    // Завдання 3
    cout << "Введіть кількість хвилин (0-59): " << endl;
    cin >> N;
    printMinutesDescription(N);
    return 0;
}

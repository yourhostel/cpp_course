// III_course/2025-09-21-one-dimensional-arrays/oda.cpp
#include <cmath>
#include <optional>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

//task1:
void test_task1();

//task2:
void test_task2();


int main()
{
    // test_task1();
    test_task2();

    return 0;
}

//task1:
// добуток модулів елементів Y
double task1()
{
    constexpr double Y[7] = {-2.2, 0.2, 3.1, 2.1, -3.1, 6.1, 0.5};
    double P = 1.0;
    for (const double y : Y) P *= fabs(y);
    return P;
}

void test_task1()
{
    const double res = task1();
    cout << "\n--- task1 ---\n";
    cout << fixed << setprecision(6)
        << "Добуток модулів = " << res << "\n";
}

// task2:
// обчислення довжин векторів з матриці A(m,n)
optional<bool> task2(const int m, const int n, const double* A, double* L, string& err)
{
    err.clear();

    if (m <= 0 || n <= 0)
    {
        err = "m і n повинні бути >0";
        return nullopt;
    }
    if (m > 5 || n > 6)
    {
        err = "Перевищено розмірності (m<=5, n<=6)";
        return nullopt;
    }

    for (int j = 0; j < n; j++)
    {
        double s = 0.0;
        for (int i = 0; i < m; i++)
        {
            const double val = A[i * n + j]; // доступ до A[i][j] через вказівник
            s += val * val;
        }
        L[j] = sqrt(s);
    }

    return true; // успіх
}

void test_task2()
{
    cout << "\n--- task2 ---\n";
    string err;

    constexpr int m = 3;
    constexpr int n = 4;
    constexpr double A[m][n] = {
        {1, 2, -3, 4},
        {0, -1, 5, 2},
        {2, 4, 1, 0}
    };

    double L[n]; // масив довжин

    // Навмисний фейл: n=0
    { // ізолюємо scope
        double L[1]; // фіктивний масив
        const auto res = task2(m, 0, &A[0][0], L, err);
        if (!res) {
            cout << "Очікувано ERROR: " << err << "\n";
        }
    }

    // Навмисний фейл: m=6
    { // ізолюємо scope
        double L[n];
        const auto res = task2(6, n, &A[0][0], L, err);
        if (!res) {
            cout << "Очікувано ERROR: " << err << "\n";
        }
    }

    if (const auto res = task2(m, n, &A[0][0], L, err); !res)
    {
        cout << "ERROR: " << err << "\n";
        return;
    }

    cout << fixed << setprecision(6);
    for (int j = 0; j < n; j++)
    {
        cout << "Вектор " << j << " -> довжина = " << L[j] << "\n";
    }

    // пошук максимуму
    double maxL = L[0];
    int pos = 0;
    for (int j = 1; j < n; j++)
    {
        if (L[j] > maxL)
        {
            maxL = L[j];
            pos = j;
        }
    }

    cout << "Максимальна довжина = " << maxL
        << " (номер " << pos << ")\n";
}

// III_course/2025-09-17-linear-programming/lp.cpp
# include <iostream>
# include <random>
# include <cmath>
# include <optional>
# include <iomanip>

using namespace std;

// task1
optional<double> task1(double x, string& err);
void test_task1();

// task2
// Загальна форма, для створення умов помилки
optional<double> task2_eval(double x, double a, double eps, string& err);

// обгортка для версії за умовою: x=3, a=-1.7, eps=1e-12
optional<double> task2(string& err)
{
    return task2_eval(3.0, -1.7, 1e-12, err);
}

void test_task2();

int main()
{
    // test_task1();
    test_task2();

    return 0;
}

//task1:

// y = e^2 * lg(x^4) * ((x - 0.5)^2 - cos x) / sqrt(|x+1| + |x|)
// err: для побічного ефекту щоб вивести помилку на зовні
optional<double> task1(const double x, string& err)
{
    err.clear();

    // x != 0 (бо lg(x^4) вимагає x^4 > 0)
    if (x == 0.0)
    {
        err = "Помилка: x = 0 (lg(x^4) не визначено)";
        return nullopt;
    }

    // A = lg(x^4)
    const double A = log10(pow(x, 4.0));

    // B = (x - 0.5)^2 - cos(x)
    const double xm = x - 0.5; // допоміжна змінна
    const double B = xm * xm - cos(x);

    // C = sqrt(|x+1| + |x|)
    const double C = sqrt(fabs(x + 1.0) + fabs(x));

    // y = e^2 * A * (B / C)
    const double y = exp(2.0) * A * (B / C);

    return y;
}

void test_task1()
{
    string err;

    // Набір тестових значень
    double xs[] = {1.0, -2.0, 0.3, 0.0};

    // для красивого виводу чисел
    cout << fixed << setprecision(6);

    for (const double x : xs)
    {
        // чекаємо на помилку
        auto res = task1(x, err);

        cout << "x = " << setw(6) << x << " => ";

        if (res)
            // якщо значення дійсне
            cout << "y = " << *res << "\n";
        else
            // якщо nullopt
            cout << "ERROR: " << err << "\n";
    }
}

// task2:

// t = ln|m-y| + cos^3(m*y)
// m = sqrt(|x+a|) + 1.3*lg(pi/3)
// y = a * cbrt(sin^4(x^3))
// x=3, a=-1.7
// універсальна для тестів
optional<double> task2_eval(const double x, double a, double eps, string& err)
{
    err.clear();

    const double PI = acos(-1.0);

    // y = a * cbrt(sin^4(x^3))
    const double s = sin(x * x * x);        // sin(x^3)
    const double y = a * cbrt(pow(s, 4.0)); // sin^4(...) >= 0

    // m = sqrt(|x+a|) + 1.3 * lg(pi/3)
    const double m = sqrt(fabs(x + a)) + 1.3 * log10(PI / 3.0);

    // перевірка ln|m - y|
    if (fabs(m - y) <= eps) {
        err = "Помилка: ln|m−y| не визначено (|m−y| ≈ 0)";
        return nullopt;
    }

    // t = ln|m-y| + cos^3(m*y)
    const double t = log(fabs(m - y)) + pow(cos(m * y), 3.0);
    return t;
}

void test_task2()
{
    cout << "\n--- Task 2 ---\n";
    string err;

    // 1) Стандартний кейс з умови
    if (const auto t = task2(err)) {
        cout << "x=3, a=-1.7 → t = " << fixed << setprecision(6) << *t << "\n";
    } else {
        cout << "x=3, a=-1.7 → ERROR: " << err << "\n";
    }

    // 2) Кілька довільних 'a' для демонстрації
    constexpr double x = 3.0;
    const double eps = 1e-12;
    double a_values[] = {-3.0, -1.0, 0.0, 1.0, 2.0};

    for (const double a : a_values) {
        auto t = task2_eval(x, a, eps, err);
        cout << "x=3, a=" << setw(6) << a << " => ";
        if (t) cout << "t=" << setprecision(6) << *t << "\n";
        else   cout << "ERROR: " << err << "\n";
    }

    // 3) Навмисно ламаємо: підбираємо 'a' приблизно 2.522, робимо eps "ширше", щоб гарантовано зловити
    constexpr double a_near = 2.521378925185;   // близько до кореня m = y при x = 3
    constexpr double eps_relaxed = 1e-6;

    const auto t_fail = task2_eval(x, a_near, eps_relaxed, err);
    cout << "Навмисний фейл: x=3, a=" << a_near << ", eps=" << eps_relaxed << " => ";
    if (t_fail) cout << "t=" << setprecision(6) << *t_fail << " (неочікувано)\n";
    else        cout << "ERROR: " << err << " (очікувано)\n";
}
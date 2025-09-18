# include <iostream>
# include <random>
# include <cmath>
# include <optional>
# include <iomanip>

using namespace std;

optional<double> task1(double x, string& err);
void test_task1();

int main() {
    test_task1();

    return 0;
}

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

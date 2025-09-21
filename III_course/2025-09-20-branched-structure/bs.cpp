// III_course/2025-09-20-branched-structure/bs.cpp
# include <iostream>
# include <random>
# include <cmath>
# include <iomanip>
# include <optional>

using namespace std;

//task1:
optional<double> task1(double x, string& err);
void test_task1();

//task2:
void task2();
void test_task2();

//task3:
void test_task3();

int main() {
    // test_task1();
    test_task2();
    // test_task3();

    return 0;
}

//task1:
optional<double> task1(double x, string& err) {
    err.clear();

    if (x >= 10.0) {
        err = "Помилка: x ≥ 10 поза ОДЗ";
        return nullopt;
    }

    if (x <= 0.0) {
        return exp(x + 1.0);
    } else if (x <= 1.0) {
        return atan(x - 9.0);
    } else { // 1 < x < 10
        const double root = sqrt(x*x + 3.0);
        return x*x*x * root;
    }
}

void test_task1() {
    string err;
    const double xs[] = { -2.0, 0.0, 0.5, 1.0, 5.0, 9.999, 10.0, 11.0 };

    cout << "\n--- task1 ---\n";
    cout << fixed << setprecision(6);
    for (double x : xs) {
        auto y = task1(x, err);
        cout << "x=" << setw(7) << x << " => ";
        if (y) cout << "y=" << *y << "\n";
        else   cout << "ERROR: " << err << "\n";
    }
}

//task2:
void task2() {
    constexpr double dt = 1.1;
    constexpr double tmax = 6.5;
    constexpr double EPS = 1e-12;

    for (double t = 0.0; t <= tmax + 1e-15; t += dt) {
        const double den = 2.0 * cos(t) + 1.0;

        cout << fixed << setprecision(6);
        cout << "t = " << setw(6) << t << " => ";

        if (fabs(den) <= EPS) {
            cout << "ERROR: знаменник ≈ 0\n";
        } else {
            const double z = (2.3 * t + 8.0) / den;
            cout << "z = " << z << "\n";
        }
    }
}

void test_task2_error() {
    cout << "\nНавмисна перевірка (t=2.0943951023931953)\n";
    constexpr double t = 2.0943951023931953;
    if (const double den = 2.0*cos(t) + 1.0; fabs(den) <= 1e-12)
        cout << "t=" << t << " => ERROR: знаменник ≈ 0\n";
    else {
        const double z = (2.3*t+8.0)/den;
        cout << "t=" << t << " => z=" << z << "\n";
    }
}

void test_task2() {
    cout << "\n--- task2 ---\n";
    task2();
    test_task2_error();
}



//task3:
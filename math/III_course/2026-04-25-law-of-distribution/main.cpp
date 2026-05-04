#include <iostream>
#include <iomanip>
#include "stats.hpp"
#include "print.hpp"
#include <cmath>
#include <vector>

using namespace stats; // StatKit власна бібліотека
using namespace print::tables; // власна бібліотека для друку таблиць
using namespace std;

void task_1()
{
    constexpr double lambda = 1.0;

    std::vector<table_row<double>> data;

    for (int m = 0; m <= 7; ++m)
        data.push_back({
            static_cast<double>(m),
            poisson_pmf<double>(m, lambda)
        });

    print_distribution_table("Завдання", "1 Пуассон", "m", "p", data);
}

void task_2()
{
    constexpr double p = 0.1;
    constexpr double q = 0.9;

    std::vector<table_row<double>> data;

    for (int m = 1; m <= 10; ++m)
        data.push_back({
            static_cast<double>(m),
            pow(q, m - 1) * p
        });

    print_distribution_table("Завдання", "2 Геометричний розподіл", "m", "p", data);
}

int main()
{
    cout << fixed << setprecision(6);
    cout << "Law of Distribution \n\n" << endl;

    task_1();
    task_2();
    return 0;
}
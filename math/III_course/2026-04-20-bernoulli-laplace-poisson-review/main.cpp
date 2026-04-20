#include <iostream>
#include <iomanip>
#include "stats.hpp"

using namespace stats; // StatKit власна бібліотека

void task_1()
{
    const int n = 5;
    const double p = 0.3;

    std::cout << std::fixed << std::setprecision(6);

    // а) рівно 1 нестандартний
    const double p_exact_1 = bernoulli_exact(n, 1, p);

    // б) принаймні 1
    // P(X >= 1) = 1 - P(X = 0)
    const double p_at_least_1 = 1.0 - bernoulli_exact(n, 0, p);

    // альтернативно через CDF:
    // const double p_at_least_1 = 1.0 - binomial_cdf(n, 0, p);

    std::cout << "Задача 1\n";

    std::cout << "a) P(X = 1) = " << p_exact_1 << "\n";
    std::cout << "b) P(X >= 1) = " << p_at_least_1 << "\n";
}

void task_2()
{
    const int n = 100;
    const double p = 0.1;

    std::cout << std::fixed << std::setprecision(6);

    // а) менше 15 осіб
    // P(X < 15) = P(X <= 14)
    const double p_less_15 = binomial_cdf(n, 14, p);

    // б) від 5 до 12 осіб
    // P(5 <= X <= 12) = P(X <= 12) - P(X <= 4)
    const double p_5_12 =
        binomial_cdf(n, 12, p) - binomial_cdf(n, 4, p);

    // в) більше 20 осіб
    // P(X > 20) = 1 - P(X <= 20)
    const double p_more_20 = 1.0 - binomial_cdf(n, 20, p);

    std::cout << "Задача 2\n";
    std::cout << "Точний біноміальний розрахунок\n";
    std::cout << "a) P(X < 15) = " << p_less_15 << "\n";
    std::cout << "b) P(5 <= X <= 12) = " << p_5_12 << "\n";
    std::cout << "c) P(X > 20) = " << p_more_20 << "\n\n";

    // Наближення через інтегральну теорему Лапласа
    // а) P(X < 15) ~ P(X <= 14), тому беремо [0; 14]
    const double laplace_less_15 = laplace_integral(n, 0, 14, p);

    // б) P(5 <= X <= 12)
    const double laplace_5_12 = laplace_integral(n, 5, 12, p);

    // в) P(X > 20) = 1 - P(X <= 20)
    const double laplace_more_20 = 1.0 - laplace_integral(n, 0, 20, p);

    std::cout << "Наближення Лапласа\n";
    std::cout << "a) P(X < 15) = " << laplace_less_15 << "\n";
    std::cout << "b) P(5 <= X <= 12) = " << laplace_5_12 << "\n";
    std::cout << "c) P(X > 20) = " << laplace_more_20 << "\n";
}

void task_5()
{
    const double lambda = 3.0; // λ = np = 300 * 0.01

    std::cout << std::fixed << std::setprecision(6);

    // а) не більше 5 пасажирів
    const double p_le_5 = poisson_cdf(5, lambda);

    // б) не менше 3 пасажирів
    const double p_ge_3 = 1.0 - poisson_cdf(2, lambda);

    std::cout << "Задача 5 (Пуассон)\n";
    std::cout << "a) P(X <= 5) = " << p_le_5 << "\n";
    std::cout << "b) P(X >= 3) = " << p_ge_3 << "\n";
}

void task_2_1()
{
    std::cout << std::fixed << std::setprecision(6);

    // Прибуток:
    // сонячна: 290 - 100 = 190
    // похмура: 260 - 100 = 160
    // холодна: 225 - 100 = 125
    //
    // Імовірності:
    // сонячна: 0.5
    // холодна: 0.1
    // похмура: 1 - 0.5 - 0.1 = 0.4

    const auto dist = discrete::make_table_distribution(
        std::vector<double>{190.0, 160.0, 125.0},
        std::vector<double>{0.5, 0.4, 0.1}
    );

    std::cout << "Завдання 2.1\n";
    std::cout << "Ряд розподілу X\n";
    std::cout << "X = 190, P = " << dist.pmf(190.0) << "\n";
    std::cout << "X = 160, P = " << dist.pmf(160.0) << "\n";
    std::cout << "X = 125, P = " << dist.pmf(125.0) << "\n";

    const double mean = dist.mean();
    const double variance = dist.variance();
    const double sigma = dist.standard_deviation();

    std::cout << "M[X] = " << mean << "\n";
    std::cout << "D[X] = " << variance << "\n";
    std::cout << "sigma[X] = " << sigma << "\n\n";
}

void task_2_6()
{
    std::cout << std::fixed << std::setprecision(6);

    // У кожній покупці:
    // приз з імовірністю 0.1
    // без призу з імовірністю 0.9
    //
    //Нехай Y = кількість призів за 5 покупок.
    // Тоді Y ~ Bin(5, 0.1)
    //
    // Шукана величина X = 100 * Y

    const int n = 5;
    const double p = 0.1;

    std::vector<double> x_values;
    std::vector<double> probabilities;

    for (int k = 0; k <= n; ++k)
    {
        x_values.push_back(100.0 * k);
        probabilities.push_back(bernoulli_exact(n, k, p));
    }

    const auto dist = discrete::make_table_distribution(
        std::move(x_values),
        std::move(probabilities)
    );

    std::cout << "Завдання 2.6\n";
    std::cout << "Ряд розподілу X\n";

    for (int k = 0; k <= n; ++k)
    {
        const double x = 100.0 * k;
        std::cout << "X = " << x << ", P = " << dist.pmf(x) << "\n";
    }

    std::cout << "M[X] = " << dist.mean() << "\n";
    std::cout << "D[X] = " << dist.variance() << "\n";
    std::cout << "sigma[X] = " << dist.standard_deviation() << "\n\n";
}

int main()
{
    // task_1();
    // task_2();
    // task_5();
    task_2_1();
    task_2_6();

    // run_stats_demo();
    return 0;
}
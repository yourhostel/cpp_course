//
// Created by tysser on 21.03.26.
//

#include <iostream>
#include <ostream>

#include "NormalDistributionPlotter.h"

void test()
{
    constexpr double a = 1000.0;
    constexpr double x = 1000.0;
    constexpr double sigma = 30.0;
    const NormalDistributionPlotter plotter(a, sigma);

    plotter.plot_density_with_interval(
        850.0,
        1150.0,
        940.0,
        1060.0,
        "Щільність нормального розподілу. Завдання 9.30"
    );

    std::cout << "y = " << plotter.density(x) << std::endl;

    constexpr double n = 2.0;
    const double l_phi = NormalDistributionPlotter::laplace_phi(n);

    std::cout << "Ф(" << n << ") = " << l_phi << std::endl;
    std::cout << "P(940 < X < 1060) = " << 2.0 * l_phi << std::endl;
}

template <typename F>
void try_test(F f)
{
    try
    {
        f();
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Помилка некоректних аргументів: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Помилка виконання: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Загальна помилка: " << e.what() << std::endl;
    }
}

int main()
{
    try_test(test);
    return 0;
}

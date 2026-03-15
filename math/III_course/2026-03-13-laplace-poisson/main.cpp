//
// Created by tysser on 15.03.26.
//

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

#include "Probability.h"

// ++++++++++++++++++++++++++++++ Bernoulli +++++++++++++++++++++++++++++++++++++
void bernoulli(const long long n,
               const long long k,
                  const double p,
                  const double q)
{
    auto single = [&](const long long i)
    {
        const double comb = Probability::combination_by_product(n, i);
        return comb * std::pow(p, i) * std::pow(q, n - i);
    };


    std::cout << "Bernoulli: " << single(k) << std::endl;
}

// ++++++++++++++++++++++++++++++ Laplace +++++++++++++++++++++++++++++++++++++++
double laplace_x(const long long n,
                 const long long k,
                 const double p,
                 const double sqrt_n_p_q)
{
    return (k - n * p) / sqrt_n_p_q;
}

// Щільність нормального розподілу
double laplace_local_phi(const double x)
{
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-x * x / 2.0);
}

void laplace_local(const long long n,
             const long long k,
             const double p,
             const double sqrt_n_p_q)
{
    double x = laplace_x(n, k, p, sqrt_n_p_q);
    std::cout << "Laplace:   " << (1 / sqrt_n_p_q) * laplace_local_phi(x) << std::endl;
}

// +++++++++++++++++++++++ Laplace's integral theorem +++++++++++++++++++++++++++
double laplace_phi(double x)
{
    return 0.5 * std::erf(x / std::sqrt(2.0));
}

void laplace_integral_phi()
{
    std::cout << "Ф(2.13) = " << laplace_phi(2.13) << std::endl;
    std::cout << "Ф(0.71) = " << laplace_phi(0.71) << std::endl;
}

// ++++++++++++++++++++++++++++++ Poisson +++++++++++++++++++++++++++++++++++++++
void poisson(const long long n, const long long k, const double p)
{
    const double lambda = n * p;
    std::cout << "Poisson:   " << std::pow(lambda, k) * std::exp(-lambda) / std::tgamma(k + 1) << std::endl;
}

// ++++++++++++++++++++++++++++++ validator +++++++++++++++++++++++++++++++++++++++
constexpr auto BLACK   = "\033[30m";
constexpr auto RED     = "\033[31m";
constexpr auto GREEN   = "\033[32m";
constexpr auto YELLOW  = "\033[33m";
constexpr auto BLUE    = "\033[34m";
constexpr auto MAGENTA = "\033[35m";
constexpr auto CYAN    = "\033[36m";
constexpr auto WHITE   = "\033[37m";

constexpr auto RESET = "\033[0m";

bool validator(long long n, long long k, double p)
{
    bool ok = true;

    if (n > 1000000)
    {
        std::cout << RED << "Помилка: " << RESET
                  << "n занадто велике для прямого обчислення у типі double\n";
        ok = false;
    }

    if (n <= 0)
    {
        std::cout << RED << "Помилка: " << RESET << "n повинно бути додатним цілим числом\n";
        ok = false;
    }

    if (k > 1000)
    {
        std::cout << RED << "Помилка: " << RESET
                  << "k занадто велике для обчислення факторіала у типі double\n";
        ok = false;
    }

    if (k < 0)
    {
        std::cout << RED << "Помилка: " << RESET << "k не може бути від’ємним\n";
        ok = false;
    }

    if (k > n)
    {
        std::cout << RED << "Помилка: " << RESET << "k не може бути більшим за n\n";
        ok = false;
    }

    if (!(p >= 0.0 && p <= 1.0))
    {
        std::cout << RED << "Помилка: " << RESET << "p повинно належати інтервалу [0,1]\n";
        ok = false;
    }

    if (p == 0.0)
    {
        std::cout << YELLOW << "Попередження: " << RESET << "p = 0, успіхи неможливі\n";
    }

    if (p == 1.0)
    {
        std::cout << YELLOW << "Попередження: " << RESET << "p = 1, кожне випробування буде успішним\n";
    }

    return ok;
}

int prompt_out(long long& n, long long& k, double& p)
{
    std::string input;

    std::cout << "Введіть загальну кількість випробувань n = ";
    std::cin >> input;
    if (input == "q")
        return 2;
    n = std::stoll(input);

    std::cout << "Введіть ймовірність p = ";
    std::cin >> input;
    if (input == "q")
        return 2;
    p = std::stod(input);

    std::cout << "Введіть очікувану кількість успіхів k = ";
    std::cin >> input;
    if (input == "q")
        return 2;
    k = std::stoll(input);

    if (validator(n, k, p))
        return 1;

    return 0;
}

void prompt()
{
    long long n;
    long long k;
    double p;

    while (true)
    {
        int check = prompt_out(n, k, p);

        if (check == 2)
            break;

        if (check == 0)
            continue;

        const double q = 1 - p;
        const double sqrt_n_p_q = std::sqrt(n * p * q);

        std::cout << std::fixed << std::setprecision(6);

        std::cout << GREEN << std::string(80, '=') << RESET << "\n";
        std::cout << "P(X = " << k << ") для "
          << n << " випробувань при ймовірності успіху p = "
          << p << "\n";
        std::cout << GREEN << std::string(80, '-') << RESET << "\n";
        bernoulli(n, k, p, q);
        laplace_local(n, k, p, sqrt_n_p_q);
        poisson(n, k, p);
        std::cout << GREEN << std::string(80, '=') << RESET << "\n\n";
    }
}

int main()
{
    prompt();
    // laplace_integral_phi();

}

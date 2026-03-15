//
// Created by tysser on 13.03.26.
//

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

#include "Probability.h"

static double probability_equal(
    const long long k,
    const std::function<double(long long)>& single)
{
    return single(k);
}

static double probability_less(
    const long long k,
    const std::function<double(long long)>& single)
{
    double sum = 0.0;

    for (long long i = 0; i < k; ++i)
        sum += single(i);

    return sum;
}

static double probability_greater(
    const long long k,
    const std::function<double(long long)>& single)
{
    double sum = 0.0;

    for (long long i = 0; i <= k; ++i)
        sum += single(i);

    return 1.0 - sum;
}

static double probability_at_least_one(
    const std::function<double(long long)>& single)
{
    return 1.0 - single(0);
}

double binomial_probability(
    const long long n,
    const long long k,
    const double p,
    const char mode)
{
    auto single = [&](const long long i)
    {
        const double comb = Probability::combination_by_product(n, i);
        return comb * std::pow(p, i) * std::pow(1.0 - p, n - i);
    };

    switch (mode)
    {
    case '=':
        return probability_equal(k, single);

    case '<':
        return probability_less(k, single);

    case '>':
        return probability_greater(k, single);

    case 'a':
        return probability_at_least_one(single);

    default:
        return 0.0;
    }
}


void test()
{
    constexpr long long n = 100;
    constexpr double p = 0.01;

    const double a = binomial_probability(n, 3, p, '=');
    const double b = binomial_probability(n, 3, p, '<');
    const double c = binomial_probability(n, 3, p, '>');
    const double d = binomial_probability(n, 0, p, 'a');

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "P(X = 3)  = " << a << '\n';
    std::cout << "P(X < 3)  = " << b << '\n';
    std::cout << "P(X > 3)  = " << c << '\n';
    std::cout << "P(X >= 1) = " << d << '\n';
}

int main()
{
    //test();


    return 0;
}
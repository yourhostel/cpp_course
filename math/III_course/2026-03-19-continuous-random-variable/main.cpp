//
// Created by tysser on 19.03.26.
//

#include <iostream>

#include "DistributionRepository.h"
#include "DistributionStatistics.h"

constexpr auto RED     = "\033[31m";
constexpr auto GREEN   = "\033[32m";
constexpr auto YELLOW  = "\033[33m";

constexpr auto RESET = "\033[0m";

double probability(const distribution_case& c)
{
    return c.distribution_function(c.beta) -
           c.distribution_function(c.alpha);
}

void plots(const DistributionRepository& repository, const int task)
{
    repository.plot_distribution_function(task);
    repository.plot_density_function(task);
}

void statistics(const DistributionRepository& repository, const int task)
{
    const distribution_case& c = repository.get_case(task);

    const double ex = DistributionStatistics::expectation(
        c.density_function,
        c.a,
        c.b
    );

    const double var = DistributionStatistics::variance(
        c.density_function,
        c.a,
        c.b
    );

    const double sigma = DistributionStatistics::standard_deviation(
        c.density_function,
        c.a,
        c.b
    );

    const double p = probability(c);

    std::cout << YELLOW << "Task: " << c.label << RESET << '\n';
    std::cout << "P(alpha <= X <= beta) = " << p << '\n';
    std::cout << "M(X) = " << ex << '\n';
    std::cout << "D(X) = " << var << '\n';
    std::cout << "sigma(X) = " << sigma << '\n';
    std::cout << GREEN << std::string(80,'=') << RESET << '\n';
}

int main() {
    constexpr int task = 2;
    const DistributionRepository repository;


    plots(repository, task);
    statistics(repository, task);

    // for (int i = 1; i <= 30; ++i)
    // {
    //     statistics(repository, i);
    // }
}
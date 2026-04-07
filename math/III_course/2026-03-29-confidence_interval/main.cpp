//
// Created by tysser on 29.03.26.
//
#include <string>
#include <iostream>
#include <iomanip>
#include <boost/math/distributions/normal.hpp>

constexpr auto YELLOW  = "\033[33m";
constexpr auto CYAN    = "\033[36m";
constexpr auto RESET = "\033[0m";

struct task
{
    std::string id;
    double x_bar;
    int n;
    double sigma;
};

double central_probability(const double gamma)
{
    return (1.0 + gamma) / 2.0;
}

double normal_quantile(const double p)
{
    const boost::math::normal_distribution<> dist(0.0, 1.0);
    return boost::math::quantile(dist, p);
}

double margin_of_error(const double t, const double sigma, const int n)
{
    return t * sigma / std::sqrt(n);
}

std::pair<double, double> confidence_interval(
    const double x_bar,
    const int n,
    const double sigma,
    const double gamma
)
{
    const double p = central_probability(gamma);
    const double t = normal_quantile(p);
    const double eps = margin_of_error(t, sigma, n);

    return {x_bar - eps, x_bar + eps};
}

struct result
{
    std::string id;
    task t;
    double h_1;
    double h_2;
};

std::vector<result> compute_intervals(
    const std::vector<task>& tasks,
    const double gamma
)
{
    std::vector<result> results;
    results.reserve(tasks.size());

    std::ranges::for_each(tasks, [&](const task& t)
    {
        const auto [h1, h2] = confidence_interval(t.x_bar, t.n, t.sigma, gamma);

        results.push_back(result{
            t.id,
            t,
            h1,
            h2
        });
    });

    return results;
}

void print_results(const std::vector<result>& results, const double gamma)
{
    std::ranges::for_each(results, [&](const result& r)
    {
        std::cout << YELLOW << "Task " << r.id << RESET << '\n';

        std::cout
            << CYAN
            << "x_bar = " << std::setw(6) << std::fixed << std::setprecision(2) << r.t.x_bar
            << "   n = " << std::setw(3) << r.t.n
            << "   sigma = " << std::setw(2) << r.t.sigma
            << "   gamma = " << gamma
            << RESET <<'\n';

        std::cout
            << "Interval   h_1 = " << std::setw(6) << r.h_1
            << "   h_2 = " << std::setw(6) << r.h_2
            << "\n\n";
    });
}

void test()
{
    const std::vector<task> tasks =
    {
        {"1", 75.17, 36, 6},
        {"2", 75.16, 49, 7},
        {"3", 75.15, 64, 8},
        {"4", 75.14, 81, 9},
        {"5", 75.13, 100, 10},
        {"6", 75.12, 121, 11},
        {"7", 75.11, 144, 12},
        {"8", 75.10, 169, 13},
        {"9", 75.09, 196, 14},
        {"10", 75.08, 225, 15}
    };

    const auto results = compute_intervals(tasks, 0.95);
    print_results(results, 0.95);
}

int main()
{
    test();
    return 0;
}

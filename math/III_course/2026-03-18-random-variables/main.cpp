//
// Created by tysser on 19.03.26.
//

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#include "print.hpp"

using namespace print::tables;

// =================== 6.1 ===================
std::vector<double> geometric_distribution(int n, double p)
{
    std::vector<double> probs;
    double q = 1.0 - p;

    for (int k = 1; k <= n; ++k)
    {
        if (k < n)
            probs.push_back(std::pow(q, k - 1) * p);
        else
            probs.push_back(std::pow(q, n - 1));
    }

    return probs;
}

struct Sample
{
    std::string number;
    int n;
    double p;
};

std::string build_visual(int k, int n)
{
    std::string result;

    for (int i = 1; i <= n; ++i)
    {
        if (i < k)
            result += "0 ";
        else if (i == k)
            result += "1 ";
        else
            result += "x ";
    }

    return result;
}

void task_6_1()
{
    std::vector<Sample> tasks = {
        {"6.1", 5, 0.9},
        {"6.2", 4, 0.7},
        {"6.3", 5, 0.8},
        {"6.4", 4, 0.8},
        {"6.5", 5, 0.7},
        {"6.6", 4, 0.9}
    };

    for (const auto& t : tasks)
    {
        auto probs = geometric_distribution(t.n, t.p);

        std::cout << "Variant " << t.number << "\n";

        for (int k = 1; k <= t.n; ++k)
        {
            std::cout << std::setw(10) << ("P(X=" + std::to_string(k) + ")")
                << " = "
                << std::setw(10) << std::fixed << std::setprecision(6) << probs[k - 1]
                << "    "
                << build_visual(k, t.n)
                << "\n";
        }

        std::cout << "\n";
    }
}

// =================== 6.7 ===================

#include <vector>

std::vector<table_row<double>> failure_distribution(const std::vector<double>& p)
{
    const int n = static_cast<int>(p.size());

    std::vector<double> probs(n + 1, 0.0);

    const int total = 1 << n;

    for (int mask = 0; mask < total; ++mask)
    {
        int m = 0;
        double probability = 1.0;

        for (int i = 0; i < n; ++i)
            if (mask & (1 << i)) probability *= p[i], ++m;
            else probability *= 1.0 - p[i];

        probs[m] += probability;
    }

    std::vector<table_row<double>> result;

    for (int m = 0; m <= n; ++m)
        result.push_back({
            static_cast<double>(m),
            probs[m]
        });

    return result;
}

void task_6_7()
{
    struct failure_task
    {
        std::string number;
        std::vector<double> p;
    };

    std::vector<failure_task> tasks = {
        {"6.7", {0.5, 0.6, 0.7}},
        {"6.8", {0.6, 0.7, 0.8}},
        {"6.9", {0.7, 0.8, 0.5}},
        {"6.10", {0.3, 0.8, 0.6}},
        {"6.11", {0.4, 0.7, 0.5}},
        {"6.12", {0.3, 0.6, 0.4}}
    };

    for (const auto& t : tasks)
    {
        auto data = failure_distribution(t.p);
        print_distribution_table("Variant", t.number, "m", "p", data);
    }
}

int main(int argc, const char* argv[])
{
    // task_6_1 ();
    task_6_7();
    return 0;
}

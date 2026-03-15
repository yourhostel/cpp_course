//
// Created by tysser on 15.03.26.
//

#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

double expectation(const std::vector<int>& x,
                   const std::vector<double>& p)
{
    double sum = 0.0;

    for(size_t i = 0; i < x.size(); ++i)
        sum += x[i] * p[i];

    return sum;
};

double expectation_square(const std::vector<int>& x,
                          const std::vector<double>& p)
{
    double sum = 0.0;

    for(size_t i = 0; i < x.size(); ++i)
        sum += x[i] * x[i] * p[i];

    return sum;
}

double variance(const std::vector<int>& x,
                const std::vector<double>& p)
{
    double m = expectation(x, p);
    double m2 = expectation_square(x, p);

    return m2 - m * m;
}

double standard_deviation(const std::vector<int>& x,
             const std::vector<double>& p)
{
    return std::sqrt(variance(x, p));
}

int main()
{
    struct distribution
    {
        std::string number;
        std::vector<int> x_i;
        std::vector<double> p_i;
    };

    std::vector<distribution> tasks = {
        {"7.1",  {-2, 1, 3, 5},  {0.2, 0.28, 0.42, 0.1}},
        {"7.2",  {-5, 2, 3, 4},  {0.4, 0.29, 0.11, 0.2}},
        {"7.3",  {-3, -2, 1, 3}, {0.35, 0.15, 0.2, 0.3}},
        {"7.4",  {-4, 0, 2, 5},  {0.1, 0.2, 0.25, 0.45}},
        {"7.5",  {-2, 2, 5, 8},  {0.27, 0.21, 0.22, 0.3}},
        {"7.6",  {-1, 1, 5, 7},  {0.2, 0.33, 0.24, 0.23}},
        {"7.7",  {-2, -1, 3, 5}, {0.22, 0.3, 0.21, 0.27}},
        {"7.8",  {-5, 2, 3, 4},  {0.2, 0.28, 0.42, 0.1}},
        {"7.9",  {-3, -2, 1, 3}, {0.4, 0.29, 0.1, 0.21}},
        {"7.10", {-4, 0, 2, 5},  {0.35, 0.15, 0.2, 0.3}},
        {"7.11", {-2, 2, 5, 8},  {0.1, 0.2, 0.25, 0.45}},
        {"7.12", {-1, 1, 5, 7},  {0.27, 0.21, 0.22, 0.3}},
        {"7.13", {-2, 3, 4, 5},  {0.15, 0.25, 0.25, 0.35}},
        {"7.14", {-5, -2, 3, 4}, {0.1, 0.23, 0.22, 0.45}},
        {"7.15", {-4, 1, 2, 5},  {0.13, 0.21, 0.22, 0.44}},
        {"7.16", {-2, 2, 4, 6},  {0.14, 0.26, 0.25, 0.35}},
        {"7.17", {-3, -2, 2, 6}, {0.21, 0.22, 0.27, 0.3}},
        {"7.18", {-1, 3, 5, 6},  {0.18, 0.21, 0.23, 0.38}},
        {"7.19", {-5, -1, 3, 5}, {0.21, 0.22, 0.25, 0.32}},
        {"7.20", {-2, -1, 4, 9}, {0.2, 0.28, 0.42, 0.1}},
        {"7.21", {-5, -2, -1, 4},{0.4, 0.29, 0.1, 0.21}},
        {"7.22", {-4, -1, 0, 5}, {0.35, 0.15, 0.2, 0.3}},
        {"7.23", {-1, 2, 4, 7},  {0.1, 0.2, 0.25, 0.45}},
        {"7.24", {-5, -3, -2, 1},{0.2, 0.31, 0.22, 0.27}},
        {"7.25", {-2, 2, 5, 6},  {0.25, 0.22, 0.23, 0.3}},
        {"7.26", {-4, 2, 4, 6},  {0.22, 0.2, 0.23, 0.35}},
        {"7.27", {-3, -2, 1, 6}, {0.2, 0.23, 0.32, 0.25}},
        {"7.28", {-4, 0, 2, 5},  {0.3, 0.32, 0.22, 0.16}},
        {"7.29", {-1, 3, 5, 8},  {0.25, 0.4, 0.2, 0.15}},
        {"7.30", {-3, 1, 3, 5},  {0.05, 0.25, 0.52, 0.18}}
    };

    std::cout << std::setw(6)  << "Номер"
              << std::setw(12) << "M(X)"
              << std::setw(12) << "D(X)"
              << std::setw(12) << "Sigma"
              << "\n";

    std::cout << std::fixed << std::setprecision(4);

    for(const auto& t : tasks)
    {
        double m = expectation(t.x_i, t.p_i);
        double d = variance(t.x_i, t.p_i);
        double s = standard_deviation(t.x_i, t.p_i);

        std::cout << std::setw(6)  << t.number
                  << std::setw(12) << m
                  << std::setw(12) << d
                  << std::setw(12) << s
                  << "\n";
    }

    return 0;
}

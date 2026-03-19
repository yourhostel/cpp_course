//
// Created by tysser on 19.03.26.
//

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

constexpr auto BLACK   = "\033[30m";
constexpr auto RED     = "\033[31m";
constexpr auto GREEN   = "\033[32m";
constexpr auto YELLOW  = "\033[33m";
constexpr auto BLUE    = "\033[34m";
constexpr auto MAGENTA = "\033[35m";
constexpr auto CYAN    = "\033[36m";
constexpr auto WHITE   = "\033[37m";

constexpr auto RESET = "\033[0m";

// =================== 6.1 ===================
std::vector<double> geometric_distribution(int n, double p)
{
    std::vector<double> probs;
    double q = 1.0 - p;

    for(int k = 1; k <= n; ++k)
    {
        if(k < n)
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

    for(int i = 1; i <= n; ++i)
    {
        if(i < k)
            result += "0 ";
        else if(i == k)
            result += "1 ";
        else
            result += "x ";
    }

    return result;
}

void task_6_1 ()
{
    std::vector<Sample> tasks = {
        {"6.1", 5, 0.9},
        {"6.2", 4, 0.7},
        {"6.3", 5, 0.8},
        {"6.4", 4, 0.8},
        {"6.5", 5, 0.7},
        {"6.6", 4, 0.9}
    };

    for(const auto& t : tasks)
    {
        auto probs = geometric_distribution(t.n, t.p);

        std::cout << "Variant " << t.number << "\n";

        for(int k = 1; k <= t.n; ++k)
        {
            std::cout << std::setw(10) << ("P(X=" + std::to_string(k) + ")")
          << " = "
          << std::setw(10) << std::fixed << std::setprecision(6) << probs[k-1]
          << "    "
          << build_visual(k, t.n)
          << "\n";
        }

        std::cout << "\n";
    }
}

// =================== 6.7 ===================

#include <vector>

std::vector<double> failure_distribution(const std::vector<double>& p)
{
    int n = p.size();
    std::vector<double> result(n + 1, 0.0);

    int total = 1 << n;

    for(int mask = 0; mask < total; ++mask)
    {
        int k = 0;
        double prob = 1.0;

        for(int i = 0; i < n; ++i)
        {
            if(mask & (1 << i))
            {
                prob *= p[i];
                ++k;
            }
            else
            {
                prob *= (1.0 - p[i]);
            }
        }

        result[k] += prob;
    }

    return result;
}

std::string center(const std::string& s, int width)
{
    int len = s.size();

    if(len >= width)
        return s;

    int left = (width - len) / 2;
    int right = width - len - left;

    return std::string(left, ' ') + s + std::string(right, ' ');
}

#include <iostream>
#include <iomanip>
#include <sstream>

void print_distribution_table(const std::string& number,
                              const std::vector<double>& probs)
{
    const int width = 10;

    std::cout << GREEN << "Variant " << number << RESET << "\n";

    // рядок X
    std::cout << center("X", width);
    for(int i = 0; i < probs.size(); ++i)
        std::cout << center(std::to_string(i), width);
    std::cout << "\n";

    // розділювач
    for(int i = 0; i <= probs.size(); ++i)
        std::cout << YELLOW << std::string(width, '-');
    std::cout << RESET << "\n";

    // рядок P
    std::cout << center("P", width);

    for(double p : probs)
    {
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << p;
        std::cout << center(ss.str(), width);
    }

    std::cout << "\n\n";
}

void task_6_7 ()
{
    struct failure_task
    {
        std::string number;
        std::vector<double> p;
    };

    std::vector<failure_task> tasks = {
        {"6.7",  {0.5, 0.6, 0.7}},
        {"6.8",  {0.6, 0.7, 0.8}},
        {"6.9",  {0.7, 0.8, 0.5}},
        {"6.10", {0.3, 0.8, 0.6}},
        {"6.11", {0.4, 0.7, 0.5}},
        {"6.12", {0.3, 0.6, 0.4}}
    };

    for(const auto& t : tasks)
    {
        auto probs = failure_distribution(t.p);
        print_distribution_table(t.number, probs);
    }
};

int main(int argc, const char * argv[])
{
    // task_6_1 ();
    task_6_7();
    return 0;
}
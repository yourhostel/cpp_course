//
// Created by tysser on 07.04.26.
//

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <vector>
#include "Plotter.h"

constexpr auto GREEN   = "\033[32m";
constexpr auto YELLOW  = "\033[33m";
constexpr auto CYAN    = "\033[36m";
constexpr auto RESET = "\033[0m";

// ============================================
// Варіаційний ряд
// ============================================
std::vector<int> make_variation_series(std::vector<int> data)
{
    std::ranges::sort(data);
    return data;
}

// ============================================
// Статистичний розподіл вибірки;
// ============================================
std::map<int, int> make_statistical_distribution(const std::vector<int>& data)
{
    std::map<int, int> distribution;

    std::ranges::for_each(data, [&](const int value)
    {
        ++distribution[value];
    });

    return distribution;
}

std::map<int, double> make_relative_distribution(const std::map<int, int>& dist)
{
    std::map<int, double> result;

    if (dist.empty()) return result;

    int total = 0;

    std::ranges::for_each(dist | std::views::values, [&](const int n)
    {
        total += n;
    });

    std::ranges::for_each(dist, [&](const auto& pair)
    {
        const auto& [x, n] = pair;
        result[x] = static_cast<double>(n) / total;
    });

    return result;
}

/**
 * Центрує текст у полі фіксованої ширини.
 * @param s
 * Текст, який потрібно вирівняти по центру.
 * @param width
 * Ширина поля, у якому виконується центрування.
 * @return
 * Рядок з доданими пробілами зліва і справа,
 * підготовлений до табличного виводу.
 */
std::string center(const std::string& s, const int width)
{
    const int len = s.size();

    if(len >= width) return s;

    const int left = (width - len) / 2;
    const int right = width - len - left;

    return std::string(left, ' ') + s + std::string(right, ' ');
}

/**
 * Виводить таблицю розподілу для одного варіанта
 * @tparam T
 * @param number
 * @param dist
 */
template <typename T>
void print_distribution_table(const std::map<int, T>& dist)
{
    constexpr int width = 10;

    std::cout << center("X", width);
    for (const auto& x : dist | std::views::keys)
        std::cout << center(std::to_string(x), width);
    std::cout << "\n";

    for (std::size_t i = 0; i <= dist.size(); ++i)
        std::cout << YELLOW << std::string(width, '-');
    std::cout << RESET << "\n";

    std::cout << center("N", width);

    for (const auto& v : dist | std::views::values)
    {
        std::ostringstream ss;

        if constexpr (std::is_floating_point_v<T>)
            ss << std::fixed << std::setprecision(3) << v;
        else
            ss << v;

        std::cout << center(ss.str(), width);
    }

    std::cout << "\n\n";
}

// ============================================
// Полігон відносних частот
// ============================================
std::map<int, double> make_relative_frequency_polygon(const std::map<int, int>& dist)
{
    std::map<int, double> result;

    int N = 0;
    for (const auto& n : dist | std::views::values) N += n;

    std::ranges::for_each(dist, [&](const auto& pair)
    {
        const auto& [x, n] = pair;
        result[x] = static_cast<double>(n) / N;
    });

    return result;
}

// ============================================
// Емпірична функція розподілу
// ============================================
void print_empirical_row(
    const int mode,
    const std::string& fraction,
    const std::string& left = "",
    const std::string& right = ""
)
{
    constexpr int frac_w = 7;
    constexpr int left_w = 4;
    constexpr int right_w = 4;
    constexpr int x_w = 3;
    constexpr int sign_w = 3;

    std::cout << "|";
    std::cout << std::format("{:^{}}", fraction, frac_w);
    std::cout << ", ";

    switch (mode)
    {
    case 0:
        {
            std::cout << std::format("{:^{}}", " x", x_w);
            std::cout << std::format("{:^{}}", "<", sign_w);
            std::cout << std::format("{:^{}}", right, right_w);
            break;
        }
    case 1:
        {
            std::cout << std::format("{:^{}}", left, left_w);
            std::cout << std::format("{:^{}}", "<=", sign_w);
            std::cout << std::format("{:^{}}", "x", x_w);
            std::cout << std::format("{:^{}}", "<", sign_w);
            std::cout << std::format("{:^{}}", right, right_w);
            break;
        }
    case 2:
        {
            std::cout << std::format("{:^{}}", "x", x_w);
            std::cout << std::format("{:^{}}", " >=", sign_w);
            std::cout << std::format("{:^{}}", left, right_w);
            break;
        }
    default:
        throw std::invalid_argument("mode має бути 0, 1 або 2");
    }
    std::cout << '\n';
}

int sample_size(const std::map<int, int>& dist)
{
    int total = 0;

    for (const auto& n : dist | std::views::values)
        total += n;

    return total;
}

void render_empirical_function(const std::map<int, int>& dist)
{
    if (dist.empty())
        throw std::invalid_argument("dist не повинна бути порожньою");

    const int total = sample_size(dist);

    print_empirical_row(0, "0", "", std::to_string(dist.begin()->first));

    int acc = 0;
    auto it = dist.begin();

    while (it != dist.end())
    {
        acc += it->second;

        std::string fraction = std::format("{}/{}", acc, total);
        fraction = std::string(CYAN) + fraction + RESET;

        auto next = std::next(it);

        if (next != dist.end())
        {
            print_empirical_row(
                1,
                fraction,
                std::to_string(it->first),
                std::to_string(next->first)
            );
        }
        else
        {
            print_empirical_row(
                2,
                fraction,
                std::to_string(it->first)
            );
        }

        it = next;
    }

    std::cout << "\n";
}

// ============================================
// Емпірична функція розподілу побудова точок F(x)
// ============================================
std::vector<std::pair<double, double>> make_empirical_function_points(const std::map<int, int>& dist)
{
    std::vector<std::pair<double,double>> points;

    if (dist.empty()) return points;

    std::vector<int> xs;
    std::vector<int> ns;

    for (const auto& [x, n] : dist)
    {
        xs.push_back(x);
        ns.push_back(n);
    }

    std::vector<int> prefix(ns.size());
    std::partial_sum(ns.begin(), ns.end(), prefix.begin());

    const int total = prefix.back();

    points.emplace_back(xs.front() - 0.5, 0.0);

    int prev = 0;

    for (std::size_t i = 0; i < xs.size(); ++i)
    {
        const double x = xs[i];

        const double y_prev = static_cast<double>(prev) / total;
        const double y_new  = static_cast<double>(prefix[i]) / total;

        points.emplace_back(x, y_prev);
        points.emplace_back(x, y_new);

        if (i + 1 < xs.size()) points.emplace_back(xs[i + 1], y_new);

        prev = prefix[i];
    }

    points.emplace_back(xs.back() + 0.5, 1.0);

    return points;
}


void test()
{
    std::map<std::string, std::vector<int>> tasks =
    {
        {"1.1", {2,6,5,6,7,6,5,6,9,2,7,6,5,6,5,7,6,2,6,5,9,7,6,5,6}},
        {"1.2", {1,5,3,5,6,5,8,5,1,5,3,5,6,5,3,5,5,6,3,5}},
        {"1.3", {5,3,5,5,4,5,5,7,5,9,5,4,5,7,5,9,5,4,5,7,5,7,5,5,5}},
        {"1.4", {5,1,2,5,8,2,5,10,1,5,2,5,8,2,5,2,5,8,2,5}},
        {"1.5", {5,4,2,3,4,5,4,8,4,2,3,4,5,8,4,2,3,4,5,3,4,5,4,5,4}},
        {"1.6", {7,5,7,6,7,9,7,10,7,6,7,7,9,7,10,6,7,9,7,10,6,7,9,6,7}},
        {"1.7", {1,2,4,7,8,1,2,4,7,8,1,2,4,7,8,1,2,4,7,2,4,7,2,4,4}},
        {"1.8", {3,5,6,8,10,3,5,6,8,10,5,6,8,10,5,6,8,6,8,6}},
        {"1.9", {3,1,3,2,3,4,5,3,2,3,4,3,5,2,3,4,5,2,3,4,3,4,3,4,3}},
        {"1.10", {5,2,5,4,5,7,5,8,5,4,5,7,5,8,4,5,7,5,7,5}},
        {"1.11", {7,4,6,7,8,7,10,6,7,7,8,7,10,7,6,7,8,10,7,8,7,10,7,8,7}},
        {"1.12", {4,1,4,3,4,6,4,8,1,4,3,4,6,4,3,4,6,4,6,4}},
        {"1.13", {2,5,4,5,6,7,2,4,5,6,2,4,5,6,4,5,4,5,4,5,4,5,4,5,5}},
        {"1.14", {3,4,5,8,5,10,4,5,8,10,5,4,5,8,4,5,8,5,8,5}},
        {"1.15", {6,4,5,6,10,6,11,4,6,5,6,10,11,5,6,10,11,6,10,6}},
        {"1.16", {1,5,2,5,6,5,8,5,1,5,2,5,6,5,1,5,2,5,6,2,5,6,5,2,5}},
        {"1.17", {2,4,5,6,5,9,5,2,5,4,5,6,5,9,2,4,5,6,9,5,6,9,5,6,5}},
        {"1.18", {4,2,3,4,5,4,7,4,2,3,4,5,7,3,4,4,5,7,3,4}},
        {"1.19", {3,5,6,8,6,9,6,5,6,8,9,6,5,6,8,9,6,8,9,6,8,9,6,8,6}},
        {"1.20", {2,5,3,5,7,5,8,3,5,7,5,8,3,5,7,3,5,7,5,7}},
        {"1.21", {3,5,6,8,9,3,5,6,8,9,5,6,8,9,5,6,8,9,3,6,8,6,8,6,3}},
        {"1.22", {4,1,2,4,5,4,6,1,4,2,4,5,6,1,2,4,5,2,4,5,2,4,2,4,4}},
        {"1.23", {1,4,5,7,10,1,4,5,7,4,5,7,4,5,4,5,4,5,5,5}},
        {"1.24", {1,2,4,5,6,1,2,4,5,6,4,2,4,5,6,4,2,4,5,2,4,5,4,5,4}},
        {"1.25", {1,2,3,5,6,1,2,3,5,6,1,2,3,5,6,2,3,5,2,3,2,3,2,3,3}},
        {"1.26", {4,2,4,3,4,5,4,6,4,2,4,3,4,4,5,3,4,5,3,4}},
        {"1.27", {2,4,5,7,5,8,2,5,4,5,7,8,2,5,4,5,7,5,2,4,5,7,5,4,5}},
        {"1.28", {2,5,3,5,6,7,5,2,3,5,6,5,7,2,3,5,6,3,5,5}},
        {"1.29", {1,2,3,5,3,6,1,3,2,3,5,3,6,3,1,2,3,5,1,2,3,5,2,3,3}},
        {"1.30", {1,2,3,5,2,6,1,2,3,5,6,1,2,3,2,5,1,2,3,1,2,3,2,3,2}}
    };

    const std::string v = "1.23";

    // задана вибірка
    std::cout << GREEN << "Variant " << v << RESET << "\n";
    std::cout << CYAN << "Вибірка:\n" << RESET;
    for (const auto x : tasks[v]) std::cout << x << " ";
    std::cout << "\n";

    // варіаційний ряд
    std::cout << CYAN << "Варіаційний ряд:\n" << RESET;
    for (const auto x : make_variation_series(tasks[v])) std::cout << x << " ";
    std::cout << "\n\n";

    const auto dist = make_statistical_distribution(tasks[v]);
    const auto rel =  make_relative_distribution(dist);

    std::cout << CYAN << "Статистичний розподіл:\n" << RESET;
    print_distribution_table(dist);
    std::cout << CYAN << "Розподіл відносних частот:\n" << RESET;
    print_distribution_table(rel);
    std::cout << CYAN << "Емпірична функція розподілу:\n" << RESET;
    render_empirical_function(dist);

    const auto points = make_empirical_function_points(dist);

    Plotter::plot_empirical_function(v, points);

    Plotter::plot_relative_frequency_polygon(v, make_relative_frequency_polygon(dist));
}

int main()
{
    test();
    return 0;
}

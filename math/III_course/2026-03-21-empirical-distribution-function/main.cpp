//
// Created by tysser on 21.03.26.
//

#include <format>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

struct sample
{
    std::string id;
    std::vector<int> x;
    std::vector<int> n;
};

const std::vector<sample> cases =
{
    { "1",  { -1, 1, 2, 3, 4, 5 },     { 3, 8, 20, 16, 7, 2 } },
    { "2",  { 1, 2, 3, 4, 5, 6 },      { 5, 8, 15, 12, 7, 3 } },
    { "3",  { -2, -1, 0, 1, 2, 3 },    { 2, 8, 20, 9, 8, 3 } },
    { "4",  { -2, -1, 0, 1, 2, 3 },    { 3, 12, 20, 8, 5, 2 } },
    { "5",  { -3, -2, -1, 0, 1, 2 },   { 2, 6, 25, 10, 5, 2 } },
    { "6",  { -4, -3, -1, 0, 2, 3 },   { 1, 7, 23, 10, 7, 2 } },
    { "7",  { -1, 0, 1, 2, 4, 5 },     { 3, 9, 18, 10, 8, 2 } },
    { "8",  { -2, -1, 2, 3, 4, 5 },    { 5, 10, 15, 8, 7, 5 } },
    { "9",  { -3, -2, -1, 1, 2, 3 },   { 1, 7, 25, 10, 5, 2 } },
    { "10", { 0, 1, 2, 3, 5, 6 },      { 2, 7, 20, 10, 8, 3 } }
};

/**
 * Виводить один рядок емпіричної функції розподілу у табличному вигляді.
 *
 * 0 - початковий інтервал: F(x) = 0 при x < x_1
 * 1 - внутрішній інтервал: F(x) = k/n при x_i <= x < x_{i+1}
 * 2 - останній інтервал: F(x) = 1 при x >= x_n
 *
 * Параметри:
 * mode      Тип рядка (0, 1 або 2).
 * fraction  Значення F(x) у вигляді рядка (наприклад "3/56").
 * left      Ліва межа інтервалу.
 * right     Права межа інтервалу.
 */
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

/**
 * Обчислює загальний обсяг вибірки.
 *
 * Формула:
 * n = sum(n_i)
 *
 * Параметри:
 * c  Структура вибірки.
 *
 * Повертає:
 * Загальну кількість спостережень.
 */
int sample_size(const sample& c)
{
    return std::accumulate(c.n.begin(), c.n.end(), 0);;
}

/**
 * Будує емпіричну функцію розподілу F_n(x) для дискретної вибірки,
 * заданої варіаційним рядом (x_i, n_i).
 *
 * Формула:
 * F_n(x) = (1/n) * sum(n_i), де сума береться по всіх x_i <= x
 *
 * Параметри:
 * c  Структура вибірки, що містить значення x_i та їх частоти n_i.
 */
void render_empirical_function(const sample& c)
{
    if (c.x.empty() || c.n.empty())
    {
        throw std::invalid_argument("x і n не повинні бути порожніми");
    }

    if (c.x.size() != c.n.size())
    {
        throw std::invalid_argument("x і n повинні мати однакову довжину");
    }

    const int total = sample_size(c);

    if (total <= 0)
    {
        throw std::invalid_argument("загальний обсяг вибірки має бути додатним");
    }

    print_empirical_row(0, "0", "", std::to_string(c.x.front()));

    int acc = 0;

    for (std::size_t i = 0; i < c.x.size(); ++i)
    {
        acc += c.n[i];
        const std::string fraction = std::format("{}/{}", acc, total);

        if (i + 1 < c.x.size())
        {
            print_empirical_row(
                1,
                fraction,
                std::to_string(c.x[i]),
                std::to_string(c.x[i + 1])
            );
        }
        else
        {
            print_empirical_row(
                2,
                fraction,
                std::to_string(c.x[i])
            );
        }
    }
}

/**
 * Обчислює вибіркове середнє для згрупованих даних.
 *
 * Формула:
 * x_mean = (1/n) * sum(x_i * n_i)
 *
 * Параметри:
 * c  Структура вибірки (x_i, n_i).
 *
 * Повертає:
 * Значення вибіркового середнього.
 */
double sample_mean(const sample& c)
{
    int total = 0;
    double sum = 0.0;

    for (size_t i = 0; i < c.x.size(); ++i)
    {
        total += c.n[i];
        sum += c.x[i] * c.n[i];
    }

    return sum / total;
}

/**
 * Обчислює вибіркову дисперсію (зміщену) для згрупованих даних.
 *
 * Формула:
 * s0^2 = (1/n) * sum(n_i * (x_i - x_mean)^2)
 *
 * Параметри:
 * c  Структура вибірки (x_i, n_i).
 *
 * Повертає:
 * Значення вибіркової дисперсії (з дільником n).
 */
double sample_variance(const sample& c)
{
    const int total = sample_size(c);
    const double mean = sample_mean(c);

    double sum = 0.0;
    for (size_t i = 0; i < c.x.size(); ++i)
    {
        const double diff = c.x[i] - mean;
        sum += c.n[i] * diff * diff;
    }

    return sum / total; // дільник n
}

/**
 * Обчислює виправлену (незміщену) вибіркову дисперсію.
 *
 * Формула:
 * s^2 = (n/(n-1)) * s0^2
 *
 * Параметри:
 * c  Структура вибірки (x_i, n_i).
 *
 * Повертає:
 * Значення незміщеної оцінки дисперсії.
 */
double sample_variance_unbiased(const sample& c)
{
    const int total = sample_size(c);

    if (total < 2)
        throw std::invalid_argument("n < 2");

    return sample_variance(c) * total / (total - 1);
}

void test()
{
    for (const auto& c : cases)
    {
        std::cout << "\033[33m" << "Variant " << c.id << "\033[0m" << "\n";
        render_empirical_function(c);
        std::cout << "\033[35m" << "Вибіркове середнє: " << sample_mean(c) << "\033[0m" << "\n";
        std::cout << "\033[36m" << "Незміщена дисперсія: " << sample_variance_unbiased(c) << "\033[0m" << "\n\n";
    }
}

int main()
{
    test();
    return 0;
}
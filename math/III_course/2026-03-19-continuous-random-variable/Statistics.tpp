#pragma once
// ====================================================================
// ****************** Для неперервного розподілу **********************
// ====================================================================

template<typename Function>
double Statistics::integrate(Function f, const double a, const double b)
{
    // Малий зсув, щоб уникнути проблем у точках,
    // де функція може бути не визначена або прямує до нескінченності
    constexpr double eps = 1e-8;

    const double left = a + eps;
    const double right = b - eps;

    // Кількість підінтервалів, має бути парною для методу Сімпсона
    constexpr int n = 10000;

    // Крок сітки
    const double h = (right - left) / n;

    // Початкова сума: значення на краях
    double sum = f(left) + f(right);

    // Основний цикл по вузлах
    for (int i = 1; i < n; ++i)
    {
        const double x = left + i * h;

        // Коефіцієнти Сімпсона:
        // 4 для непарних індексів, 2 для парних
        sum += (i % 2 == 0 ? 2.0 : 4.0) * f(x);
    }

    // Остаточна формула
    return sum * h / 3.0;
}

template<typename Function>
double Statistics::expectation(Function f, double a, double b)
{
    return integrate(
        [&](double x) {
            return x * f(x);
        },
        a,
        b
    );
}

template<typename Function>
double Statistics::second_moment(Function f, double a, double b)
{
    return integrate(
        [&](double x) {
            return x * x * f(x);
        },
        a,
        b
    );
}

template<typename Function>
double Statistics::variance(Function f, double a, double b)
{
    const double ex = expectation(f, a, b);
    const double ex2 = second_moment(f, a, b);

    return ex2 - ex * ex;
}

template<typename Function>
double Statistics::standard_deviation(Function f, double a, double b)
{
    return std::sqrt(variance(f, a, b));
}

// ====================================================================
// ******************** Для емпіричної вибірки ************************
// ====================================================================

template<typename Container>
double Statistics::expectation(const Container& data)
{
    if (data.empty()) throw std::invalid_argument("data is empty");

    double sum = 0.0;
    for (const auto& x : data) sum += static_cast<double>(x);

    return sum / static_cast<double>(data.size());
}

template<typename Container>
double Statistics::second_moment(const Container& data)
{
    if (data.empty()) throw std::invalid_argument("data is empty");

    double sum = 0.0;
    for (const auto& x : data)
    {
        const auto value = static_cast<double>(x);
        sum += value * value;
    }

    return sum / static_cast<double>(data.size());
}

template<typename Container>
double Statistics::variance(const Container& data)
{
    const double ex = expectation(data);
    const double ex2 = second_moment(data);

    return ex2 - ex * ex;
}

template<typename Container>
double Statistics::variance_stable(const Container& data)
{
    if (data.empty()) throw std::invalid_argument("data is empty");

    const double mean = expectation(data);

    double sum = 0.0;
    for (const auto& x : data)
    {
        const double diff = static_cast<double>(x) - mean;
        sum += diff * diff;
    }

    return sum / static_cast<double>(data.size());
}

template<typename Container>
double Statistics::variance_unbiased(const Container& data) {
    if (data.size() < 2) throw std::invalid_argument("data size must be at least 2");

    const double ex = expectation_empirical(data);
    double sum = 0.0;

    for (const auto& x : data)
    {
        const double diff = static_cast<double>(x) - ex;
        sum += diff * diff;
    }

    return sum / static_cast<double>(data.size() - 1);
}

template<typename Container>
double Statistics::standard_deviation(const Container& data)
{
    return std::sqrt(variance_empirical(data));
}

template<typename Container>
double Statistics::standard_deviation_unbiased(const Container& data)
{
    return std::sqrt(variance_unbiased(data));
}

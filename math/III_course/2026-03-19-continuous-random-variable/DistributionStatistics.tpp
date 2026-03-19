#pragma once
template<typename Function>
double DistributionStatistics::integrate(Function f, double a, double b) {
    // Малий зсув, щоб уникнути проблем у точках,
    // де функція може бути не визначена або прямує до нескінченності
    const double eps = 1e-8;

    const double left = a + eps;
    const double right = b - eps;

    // Кількість підінтервалів, має бути парною для методу Сімпсона
    const int n = 10000;

    // Крок сітки
    const double h = (right - left) / n;

    // Початкова сума: значення на краях
    double sum = f(left) + f(right);

    // Основний цикл по вузлах
    for (int i = 1; i < n; ++i) {
        const double x = left + i * h;

        // Коефіцієнти Сімпсона:
        // 4 для непарних індексів, 2 для парних
        sum += (i % 2 == 0 ? 2.0 : 4.0) * f(x);
    }

    // Остаточна формула
    return sum * h / 3.0;
}

template<typename Function>
double DistributionStatistics::expectation(Function f, double a, double b) {
    return integrate(
        [&](double x) {
            return x * f(x);
        },
        a,
        b
    );
}

template<typename Function>
double DistributionStatistics::second_moment(Function f, double a, double b) {
    return integrate(
        [&](double x) {
            return x * x * f(x);
        },
        a,
        b
    );
}

template<typename Function>
double DistributionStatistics::variance(Function f, double a, double b) {
    const double ex = expectation(f, a, b);
    const double ex2 = second_moment(f, a, b);

    return ex2 - ex * ex;
}

template<typename Function>
double DistributionStatistics::standard_deviation(Function f, double a, double b) {
    return std::sqrt(variance(f, a, b));
}
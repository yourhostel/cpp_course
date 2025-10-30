#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <cmath>

using FuncPtr = double(*)(double);

inline double funcSin(const double x)    { return std::sin(x); }
inline double funcSquare(const double x) { return x * x; }
inline double funcExp(const double x)    { return std::exp(x); }

inline double simpson(const double a, const double b, const int n, const FuncPtr f)
{
    const double h = (b - a) / n;
    const double sum = f(a) + f(b);

    double oddSum = 0.0;
    double evenSum = 0.0;

    for (int i = 1; i < n; i++)
    {
        const double x = a + i * h;

        if (i % 2 == 0)
            evenSum += f(x);
        else
            oddSum += f(x);
    }

    return (h / 3.0) * (sum + 4.0 * oddSum + 2.0 * evenSum);
}

#endif //MATH_FUNCTIONS_H

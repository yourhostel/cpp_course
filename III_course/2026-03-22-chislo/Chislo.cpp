//
// Created by tysser on 22.03.26.
//

#include "Chislo.h"

#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

Chislo::Chislo(const long value) : value_(value)
{
    validate_positive_value(value_);
}

void Chislo::validate_positive_value(const long value)
{
    if (value <= 0)
        throw std::invalid_argument("value має бути додатним");
}

void Chislo::validate_non_negative(const long n)
{
    if (n < 0)
        throw std::invalid_argument("n має бути невід'ємним");
}

Chislo::~Chislo() = default;

long Chislo::get_value() const
{
    return value_;
}

void Chislo::set_value(const long value)
{
    validate_positive_value(value);
    value_ = value;
}

long Chislo::factorial(const long n, const factorial_type type) const
{
    switch (type)
    {
        case factorial_type::iterative:
            return factorial_iterative(n);
        case factorial_type::recursive:
            return factorial_recursive(n);
        case factorial_type::stl:
            return factorial_stl(n);
        case factorial_type::gamma:
            return factorial_gamma(n);
        default:
            throw std::invalid_argument("Invalid type_function. Use 'iterative', 'recursive', 'stl', or 'gamma'.");
    }
}

long Chislo::factorial(const long n) const
{
    return factorial(n, factorial_type::iterative);
}

long Chislo::factorial_iterative(const long n)
{
    validate_non_negative(n);
    long result = 1;
    for (long i = 2; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}

long Chislo::factorial_recursive(const long n)
{
    validate_non_negative(n);
    if (n <= 1) return 1;
    return n * factorial_recursive(n - 1);
}

long Chislo::factorial_stl(const long n)
{
    validate_non_negative(n);
    std::vector<long> v(n);
    std::iota(v.begin(), v.end(), 1);
    return std::accumulate(v.begin(), v.end(), 1L, std::multiplies<>());
}

long Chislo::factorial_gamma(const long n)
{
    validate_non_negative(n);
    const double result = std::tgamma(static_cast<double>(n) + 1.0);
    return static_cast<long>(result);
}
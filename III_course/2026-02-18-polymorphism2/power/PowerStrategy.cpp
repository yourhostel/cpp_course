//
// Created by tysser on 19.02.26.
//

#include "PowerStrategy.h"
#include <limits>
#include <stdexcept>

void PowerStrategy::validate_power(double n, int p) const
{
    if(n == 0.0 && p < 0)
        throw std::runtime_error("undefined: division by zero");

    if(p == std::numeric_limits<int>::min())
        throw std::overflow_error("overflow: abs(INT_MIN) not representable");
}

void PowerStrategy::normalize_sign(double n, int p, double& base, int& absP) const
{
    absP = (p < 0) ? -p : p;
    base = (p < 0) ? 1.0 / n : n;
}

double PowerStrategy::power(double n, int p) const
{
    validate_power(n, p);

    double base;
    int absP;
    normalize_sign(n, p, base, absP);

    double result = 1.0;
    for(int i = 0; i < absP; ++i)
        result *= base;

    return result;
}

double PowerStrategy::power(double n) const
{
    return power(n, 2);
}

double PowerStrategy::power_recursive_core(double base, int absP) const
{
    if(absP == 0) return 1.0;
    return base * power_recursive_core(base, absP - 1);
}

double PowerStrategy::power_recursive(double n, int p) const
{
    validate_power(n, p);

    double base;
    int absP;
    normalize_sign(n, p, base, absP);

    return power_recursive_core(base, absP);
}

double PowerStrategy::power_recursive(double n) const
{
    return power_recursive(n, 2);
}

//
// Created by tysser on 19.02.26.
//

#include "FastPowerStrategy.h"

double FastPowerStrategy::power(double n, int p) const
{
    validate_power(n, p);

    double base;
    int absP;
    normalize_sign(n, p, base, absP);

    double result = 1.0;

    while(absP > 0)
    {
        if((absP % 2) == 1)
            result *= base;

        base *= base;
        absP /= 2;
    }

    return result;
}

double FastPowerStrategy::power_recursive_core(double base, int absP) const
{
    if(absP == 0) return 1.0;

    double half = power_recursive_core(base, absP / 2);

    if((absP % 2) == 0) return half * half;
    return base * half * half;
}

double FastPowerStrategy::power_recursive(double n, int p) const
{
    validate_power(n, p);

    double base;
    int absP;
    normalize_sign(n, p, base, absP);

    return power_recursive_core(base, absP);
}
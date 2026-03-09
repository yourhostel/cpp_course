//
// Created by tysser on 08.03.26.
//

#include "Probability.h"

long long Probability::mirror_index(long long n, long long r)
{
    return (r <= n - r) ? r : (n - r);
}

double Probability::combination_by_product(long long n, long long r)
{
    long long r_prime = mirror_index(n, r);

    double result = 1.0;

    for (long long t = 1; t <= r_prime; ++t)
    {
        result *= static_cast<double>(n - r_prime + t) / t;
    }

    return result;
}

double Probability::probability(
    long long total_count,
    long long sample_count,
    const std::vector<long long>& type_sizes,
    const std::vector<long long>& selected_counts
)
{
    double numerator = 1.0;

    for (std::size_t i = 0; i < type_sizes.size(); ++i)
    {
        numerator *= combination_by_product(type_sizes[i], selected_counts[i]);
    }

    double denominator = combination_by_product(total_count, sample_count);

    return numerator / denominator;
}
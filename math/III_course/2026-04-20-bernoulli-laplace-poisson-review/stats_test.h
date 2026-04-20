#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include "stats.hpp"

inline void run_stats_demo()
{
    using stats::phi;
    using stats::normal_cdf;
    using stats::laplace_phi;
    using stats::inverse_laplace_phi;
    using stats::z_critical;
    using stats::normal_two_tailed_p_value;
    using stats::bernoulli_exact;
    using stats::binomial_cdf;
    using stats::laplace_local;
    using stats::laplace_integral;
    using stats::laplace_integral_cc;
    using stats::poisson_pmf;
    using stats::poisson_cdf;
    using stats::binomial_mean;
    using stats::binomial_variance;
    using stats::poisson_mean;
    using stats::poisson_variance;
    using stats::normal_mean;
    using stats::normal_variance;
    using stats::make_standard_normal;
    using stats::make_normal;
    using stats::make_binomial;
    using stats::make_poisson;

    std::cout << std::fixed << std::setprecision(10);

    try
    {
        std::cout << "=== detail checks ===\n";
        std::cout << "phi(0) = " << phi(0.0) << '\n';
        std::cout << "normal_cdf(1) = " << normal_cdf(1.0) << '\n';
        std::cout << "laplace_phi(1) = " << laplace_phi(1.0) << '\n';
        std::cout << "inverse_laplace_phi(0) = " << inverse_laplace_phi(0.0) << '\n';
        std::cout << "z_critical(0.05) = " << z_critical(0.05) << '\n';
        std::cout << "normal_two_tailed_p_value(1.96) = " << normal_two_tailed_p_value(1.96) << '\n';

        std::cout << "\n=== bernoulli / binomial ===\n";
        std::cout << "bernoulli_exact(10, 3, 0.4) = " << bernoulli_exact(10, 3, 0.4) << '\n';
        std::cout << "binomial_cdf(10, 3, 0.4) = " << binomial_cdf(10, 3, 0.4) << '\n';
        std::cout << "laplace_local(100, 40, 0.4) = " << laplace_local(100, 40, 0.4) << '\n';
        std::cout << "laplace_integral(100, 35, 45, 0.4) = " << laplace_integral(100, 35, 45, 0.4) << '\n';
        std::cout << "laplace_integral_cc(100, 35, 45, 0.4) = " << laplace_integral_cc(100, 35, 45, 0.4) << '\n';

        std::cout << "\n=== poisson ===\n";
        std::cout << "poisson_pmf(3, 2.5) = " << poisson_pmf(3, 2.5) << '\n';
        std::cout << "poisson_cdf(3, 2.5) = " << poisson_cdf(3, 2.5) << '\n';

        std::cout << "\n=== means / variances ===\n";
        std::cout << "binomial_mean(10, 0.4) = " << binomial_mean(10, 0.4) << '\n';
        std::cout << "binomial_variance(10, 0.4) = " << binomial_variance(10, 0.4) << '\n';
        std::cout << "poisson_mean(2.5) = " << poisson_mean(2.5) << '\n';
        std::cout << "poisson_variance(2.5) = " << poisson_variance(2.5) << '\n';
        std::cout << "normal_mean() = " << normal_mean<double>() << '\n';
        std::cout << "normal_variance() = " << normal_variance<double>() << '\n';

        std::cout << "\n=== wrappers ===\n";
        auto standard_normal = make_standard_normal<double>();
        auto normal = make_normal<double>(2.0, 3.0);
        auto binom = make_binomial<double>(10, 0.4);
        auto pois = make_poisson<double>(2.5);

        std::cout << "standard_normal.pdf(0) = " << standard_normal.pdf(0.0) << '\n';
        std::cout << "standard_normal.cdf(0) = " << standard_normal.cdf(0.0) << '\n';
        std::cout << "standard_normal.quantile(0.975) = " << standard_normal.quantile(0.975) << '\n';
        std::cout << "standard_normal.mean() = " << standard_normal.mean<double>() << '\n';
        std::cout << "standard_normal.variance() = " << standard_normal.variance<double>() << '\n';

        std::cout << "normal.pdf(2) = " << normal.pdf(2.0) << '\n';
        std::cout << "normal.cdf(2) = " << normal.cdf(2.0) << '\n';
        std::cout << "normal.quantile(0.5) = " << normal.quantile(0.5) << '\n';
        std::cout << "normal.mean() = " << normal.mean<double>() << '\n';
        std::cout << "normal.variance() = " << normal.variance<double>() << '\n';

        std::cout << "binom.pdf(3) = " << binom.pdf(3.0) << '\n';
        std::cout << "binom.cdf(3) = " << binom.cdf(3.0) << '\n';
        std::cout << "binom.quantile(0.5) = " << binom.quantile(0.5) << '\n';
        std::cout << "binom.mean() = " << binom.mean<double>() << '\n';
        std::cout << "binom.variance() = " << binom.variance<double>() << '\n';

        std::cout << "pois.pdf(3) = " << pois.pdf(3.0) << '\n';
        std::cout << "pois.cdf(3) = " << pois.cdf(3.0) << '\n';
        std::cout << "pois.quantile(0.5) = " << pois.quantile(0.5) << '\n';
        std::cout << "pois.mean() = " << pois.mean<double>() << '\n';
        std::cout << "pois.variance() = " << pois.variance<double>() << '\n';

        std::cout << "\n=== edge / exception checks ===\n";

        try
        {
            std::cout << "inverse_laplace_phi(0.7) = " << inverse_laplace_phi(0.7) << '\n';
        }
        catch (const std::exception& e)
        {
            std::cout << "expected exception: " << e.what() << '\n';
        }

        try
        {
            std::cout << "bernoulli_exact(10, 11, 0.4) = " << bernoulli_exact(10, 11, 0.4) << '\n';
        }
        catch (const std::exception& e)
        {
            std::cout << "expected exception: " << e.what() << '\n';
        }

        try
        {
            std::cout << "poisson_pmf(3, -1) = " << poisson_pmf(3, -1.0) << '\n';
        }
        catch (const std::exception& e)
        {
            std::cout << "expected exception: " << e.what() << '\n';
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "unexpected exception: " << e.what() << '\n';
    }
}
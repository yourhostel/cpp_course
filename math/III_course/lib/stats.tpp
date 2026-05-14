//
// Created by tysser on 20.04.26.
//

#pragma once
#include <ranges>
#include <functional>

namespace stats
{
    namespace detail
    {
        template <floating_point_like Real>
        inline void require_finite(const Real value, const std::string_view name)
        {
            if (!std::isfinite(value))
            {
                throw std::domain_error(std::string{name} + " must be finite");
            }
        }

        template <floating_point_like Real>
        inline void require_positive(const Real value, const std::string_view name)
        {
            require_finite(value, name);
            if (!(value > Real{0}))
            {
                throw std::domain_error(std::string{name} + " must be > 0");
            }
        }

        template <floating_point_like Real>
        inline void require_non_negative(const Real value, const std::string_view name)
        {
            require_finite(value, name);
            if (value < Real{0})
            {
                throw std::domain_error(std::string{name} + " must be >= 0");
            }
        }

        template <floating_point_like Real>
        inline void require_probability_closed(const Real value, const std::string_view name)
        {
            require_finite(value, name);
            if (value < Real{0} || value > Real{1})
            {
                throw std::domain_error(std::string{name} + " must be in [0, 1]");
            }
        }

        template <floating_point_like Real>
        inline void require_probability_open(const Real value, const std::string_view name)
        {
            require_finite(value, name);
            if (!(value > Real{0} && value < Real{1}))
            {
                throw std::domain_error(std::string{name} + " must be in (0, 1)");
            }
        }

        inline void require_non_negative_int(const int n, const std::string_view name)
        {
            if (n < 0)
            {
                throw std::domain_error(std::string{name} + " must be >= 0");
            }
        }

        inline void require_ordered_int_interval(
            const int lo,
            const int hi,
            const std::string_view lo_name,
            const std::string_view hi_name)
        {
            if (lo > hi)
            {
                throw std::domain_error(
                    std::string{lo_name} + " must be <= " + std::string{hi_name}
                );
            }
        }

        inline void require_binomial_k(const int m, const int n, const std::string_view name)
        {
            require_non_negative_int(n, "n");
            if (m < 0 || m > n)
            {
                throw std::domain_error(std::string{name} + " must be in [0, n]");
            }
        }

        template <floating_point_like Real>
        [[nodiscard]] inline constexpr Real inv_sqrt_2pi() noexcept
        {
            return Real{1} /
                std::sqrt(
                    Real{2} * boost::math::constants::pi<Real>()
                );
        }
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real phi(const Real x) noexcept
    {
        return detail::inv_sqrt_2pi<Real>() * std::exp(Real{-0.5} * x * x);
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real normal_cdf(const Real x)
    {
        const boost::math::normal_distribution<Real> dist(Real{0}, Real{1});
        return boost::math::cdf(dist, x);
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real laplace_phi(const Real x)
    {
        return normal_cdf(x) - Real{0.5};
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real inverse_laplace_phi(const Real y)
    {
        detail::require_finite(y, "y");

        if (!(y > Real{-0.5} && y < Real{0.5}))
        {
            throw std::domain_error("y must be in (-0.5, 0.5)");
        }

        const boost::math::normal_distribution<Real> dist(Real{0}, Real{1});
        return boost::math::quantile(dist, y + Real{0.5});
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real z_critical(const Real alpha)
    {
        detail::require_probability_open(alpha, "alpha");

        const boost::math::normal_distribution<Real> dist(Real{0}, Real{1});
        return boost::math::quantile(dist, Real{1} - alpha);
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real normal_two_tailed_p_value(const Real z)
    {
        detail::require_finite(z, "z");

        const Real abs_z = std::abs(z);
        const Real tail = Real{1} - normal_cdf(abs_z);
        const Real p = Real{2} * tail;

        return std::clamp(p, Real{0}, Real{1});
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real bernoulli_exact(const int n, const int m, const Real p)
    {
        detail::require_non_negative_int(n, "n");
        detail::require_binomial_k(m, n, "m");
        detail::require_probability_closed(p, "p");

        const boost::math::binomial_distribution<Real> dist(
            static_cast<Real>(n),
            p
        );

        return boost::math::pdf(dist, static_cast<Real>(m));
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real binomial_cdf(const int n, const int m, const Real p)
    {
        detail::require_non_negative_int(n, "n");
        detail::require_probability_closed(p, "p");

        if (m < 0)
        {
            return Real{0};
        }

        if (m >= n)
        {
            return Real{1};
        }

        const boost::math::binomial_distribution<Real> dist(
            static_cast<Real>(n),
            p
        );

        return boost::math::cdf(dist, static_cast<Real>(m));
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real laplace_local(const int n, const int m, const Real p)
    {
        detail::require_non_negative_int(n, "n");
        detail::require_binomial_k(m, n, "m");
        detail::require_probability_open(p, "p");

        const Real q = Real{1} - p;
        const Real npq = static_cast<Real>(n) * p * q;

        detail::require_positive(npq, "n * p * q");

        const Real x =
            (static_cast<Real>(m) - static_cast<Real>(n) * p) / std::sqrt(npq);

        return phi(x) / std::sqrt(npq);
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real laplace_integral(
        const int n,
        const int m1,
        const int m2,
        const Real p)
    {
        detail::require_non_negative_int(n, "n");
        detail::require_ordered_int_interval(m1, m2, "m1", "m2");
        detail::require_probability_open(p, "p");

        const Real q = Real{1} - p;
        const Real sigma = std::sqrt(static_cast<Real>(n) * p * q);

        detail::require_positive(sigma, "sigma");

        const Real x1 =
            (static_cast<Real>(m1) - static_cast<Real>(n) * p) / sigma;
        const Real x2 =
            (static_cast<Real>(m2) - static_cast<Real>(n) * p) / sigma;

        const Real result = normal_cdf(x2) - normal_cdf(x1);
        return std::clamp(result, Real{0}, Real{1});
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real laplace_integral_cc(
        const int n,
        const int m1,
        const int m2,
        const Real p)
    {
        detail::require_non_negative_int(n, "n");
        detail::require_ordered_int_interval(m1, m2, "m1", "m2");
        detail::require_probability_open(p, "p");

        const Real q = Real{1} - p;
        const Real sigma = std::sqrt(static_cast<Real>(n) * p * q);

        detail::require_positive(sigma, "sigma");

        const Real x1 =
            (static_cast<Real>(m1) - Real{0.5} - static_cast<Real>(n) * p) / sigma;
        const Real x2 =
            (static_cast<Real>(m2) + Real{0.5} - static_cast<Real>(n) * p) / sigma;

        const Real result = normal_cdf(x2) - normal_cdf(x1);
        return std::clamp(result, Real{0}, Real{1});
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real poisson_pmf(const int m, const Real lambda)
    {
        detail::require_non_negative_int(m, "m");
        detail::require_non_negative(lambda, "lambda");

        const boost::math::poisson_distribution<Real> dist(lambda);
        return boost::math::pdf(dist, static_cast<Real>(m));
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real poisson_cdf(const int m, const Real lambda)
    {
        detail::require_non_negative(lambda, "lambda");

        if (m < 0)
        {
            return Real{0};
        }

        const boost::math::poisson_distribution<Real> dist(lambda);
        return boost::math::cdf(dist, static_cast<Real>(m));
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real binomial_mean(const int n, const Real p) noexcept
    {
        return static_cast<Real>(n) * p;
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real binomial_variance(const int n, const Real p) noexcept
    {
        return static_cast<Real>(n) * p * (Real{1} - p);
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real poisson_mean(const Real lambda) noexcept
    {
        return lambda;
    }

    template <floating_point_like Real>
    [[nodiscard]] inline Real poisson_variance(const Real lambda) noexcept
    {
        return lambda;
    }

    template <floating_point_like Real>
    [[nodiscard]] inline constexpr Real normal_mean() noexcept
    {
        return Real{0};
    }

    template <floating_point_like Real>
    [[nodiscard]] inline constexpr Real normal_variance() noexcept
    {
        return Real{1};
    }

    template <typename Distribution>
    constexpr distribution_wrapper<Distribution>::distribution_wrapper(
        Distribution distribution) noexcept(std::is_nothrow_move_constructible_v<Distribution>)
        : distribution_(std::move(distribution))
    {
    }

    template <typename Distribution>
    [[nodiscard]] constexpr const Distribution&
    distribution_wrapper<Distribution>::native() const noexcept
    {
        return distribution_;
    }

    template <typename Distribution>
    template <floating_point_like Real>
    [[nodiscard]] Real distribution_wrapper<Distribution>::pdf(const Real x) const
    {
        detail::require_finite(x, "x");
        return boost::math::pdf(distribution_, x);
    }

    template <typename Distribution>
    template <floating_point_like Real>
    [[nodiscard]] Real distribution_wrapper<Distribution>::cdf(const Real x) const
    {
        detail::require_finite(x, "x");
        return boost::math::cdf(distribution_, x);
    }

    template <typename Distribution>
    template <floating_point_like Real>
    [[nodiscard]] Real distribution_wrapper<Distribution>::quantile(const Real p) const
    {
        detail::require_probability_closed(p, "p");
        return boost::math::quantile(distribution_, p);
    }

    template <typename Distribution>
    template <floating_point_like Real>
    [[nodiscard]] Real distribution_wrapper<Distribution>::mean() const
    {
        return static_cast<Real>(boost::math::mean(distribution_));
    }

    template <typename Distribution>
    template <floating_point_like Real>
    [[nodiscard]] Real distribution_wrapper<Distribution>::variance() const
    {
        return static_cast<Real>(boost::math::variance(distribution_));
    }

    template <floating_point_like Real>
    [[nodiscard]] inline auto make_standard_normal()
    {
        return distribution_wrapper{
            boost::math::normal_distribution<Real>(Real{0}, Real{1})
        };
    }

    template <floating_point_like Real>
    [[nodiscard]] inline auto make_normal(const Real mean, const Real sigma)
    {
        detail::require_finite(mean, "mean");
        detail::require_positive(sigma, "sigma");

        return distribution_wrapper{
            boost::math::normal_distribution<Real>(mean, sigma)
        };
    }

    template <floating_point_like Real>
    [[nodiscard]] inline auto make_binomial(const int n, const Real p)
    {
        detail::require_non_negative_int(n, "n");
        detail::require_probability_closed(p, "p");

        return distribution_wrapper{
            boost::math::binomial_distribution<Real>(static_cast<Real>(n), p)
        };
    }

    template <floating_point_like Real>
    [[nodiscard]] inline auto make_poisson(const Real lambda)
    {
        detail::require_non_negative(lambda, "lambda");

        return distribution_wrapper{
            boost::math::poisson_distribution<Real>(lambda)
        };
    }
}

namespace stats::discrete
{
    template <floating_point_like Real>
    class table_distribution final
    {
    public:
        table_distribution(std::vector<Real> values,
                           std::vector<Real> probabilities)
            : values_(std::move(values)),
              probabilities_(std::move(probabilities))
        {
            if (values_.empty())
            {
                throw std::domain_error("values must not be empty");
            }

            if (values_.size() != probabilities_.size())
            {
                throw std::domain_error(
                    "values and probabilities must have the same size"
                );
            }

            for (const auto value : values_)
            {
                stats::detail::require_finite(value, "value");
            }

            for (const auto probability : probabilities_)
            {
                stats::detail::require_probability_closed(probability, "probability");
            }

            constexpr Real eps = static_cast<Real>(1e-9);

            const auto sum = std::reduce(
                probabilities_.cbegin(),
                probabilities_.cend(),
                Real{0}
            );

            if (std::abs(sum - Real{1}) > eps)
            {
                throw std::domain_error("probabilities must sum to 1");
            }
        }

        [[nodiscard]] const std::vector<Real>& values() const noexcept
        {
            return values_;
        }

        [[nodiscard]] const std::vector<Real>& probabilities() const noexcept
        {
            return probabilities_;
        }

        [[nodiscard]] std::size_t size() const noexcept
        {
            return values_.size();
        }

        [[nodiscard]] Real pmf(const Real x) const
        {
            stats::detail::require_finite(x, "x");

            auto result = Real{0};

            for (std::size_t i = 0; i < values_.size(); ++i)
            {
                if (values_[i] == x)
                {
                    result += probabilities_[i];
                }
            }

            return std::clamp(result, Real{0}, Real{1});
        }

        [[nodiscard]] Real cdf(const Real x) const
        {
            stats::detail::require_finite(x, "x");

            auto result = Real{0};

            for (std::size_t i = 0; i < values_.size(); ++i)
            {
                if (values_[i] <= x)
                {
                    result += probabilities_[i];
                }
            }

            return std::clamp(result, Real{0}, Real{1});
        }

        [[nodiscard]] Real mean() const noexcept
        {
            return std::transform_reduce(
                values_.cbegin(),
                values_.cend(),
                probabilities_.cbegin(),
                Real{0}
            );
        }

        [[nodiscard]] Real variance() const noexcept
        {
            const auto mu = mean();

            const auto second_moment = std::transform_reduce(
                values_.cbegin(),
                values_.cend(),
                probabilities_.cbegin(),
                Real{0},
                std::plus<>{},
                [](const Real x, const Real p)
                {
                    return x * x * p;
                }
            );

            const auto result = second_moment - mu * mu;
            return result < Real{0} ? Real{0} : result;
        }

        [[nodiscard]] Real standard_deviation() const noexcept
        {
            return std::sqrt(variance());
        }

    private:
        std::vector<Real> values_;
        std::vector<Real> probabilities_;
    };

    template <floating_point_like Real>
    [[nodiscard]] inline table_distribution<Real>
    make_table_distribution(std::vector<Real> values,
                            std::vector<Real> probabilities)
    {
        return table_distribution<Real>(
            std::move(values),
            std::move(probabilities)
        );
    }

    template <floating_point_like Real>
    [[nodiscard]] inline auto make_bernoulli(const Real p)
    {
        stats::detail::require_probability_closed(p, "p");

        return distribution_wrapper{
            boost::math::bernoulli_distribution<Real>(p)
        };
    }

    template <floating_point_like Real>
    [[nodiscard]] inline auto make_geometric(const Real p)
    {
        stats::detail::require_probability_open(p, "p");

        return distribution_wrapper{
            boost::math::geometric_distribution<Real>(p)
        };
    }

    template <floating_point_like Real>
    [[nodiscard]] inline auto make_hypergeometric(const unsigned successes,
                                                  const unsigned draws,
                                                  const unsigned population)
    {
        if (population == 0U)
        {
            throw std::domain_error("population must be > 0");
        }

        if (successes > population)
        {
            throw std::domain_error("successes must be <= population");
        }

        if (draws > population)
        {
            throw std::domain_error("draws must be <= population");
        }

        return distribution_wrapper{
            boost::math::hypergeometric_distribution<Real>(
                successes,
                draws,
                population
            )
        };
    }

    template <floating_point_like Real>
    [[nodiscard]] inline auto make_negative_binomial(const unsigned failures,
                                                     const Real p)
    {
        stats::detail::require_probability_open(p, "p");

        return distribution_wrapper{
            boost::math::negative_binomial_distribution<Real>(
                static_cast<Real>(failures),
                p
            )
        };
    }
}

namespace stats::sample
{
    template <std::ranges::input_range Range, typename ValueFn, typename WeightFn>
    [[nodiscard]] double weighted_mean(
        const Range& range,
        ValueFn value_fn,
        WeightFn weight_fn
    )
    {
        const double weight_sum = std::ranges::fold_left(
            range | std::views::transform([&weight_fn](const auto& item)
            {
                return static_cast<double>(std::invoke(weight_fn, item));
            }),
            0.0,
            std::plus{}
        );

        detail::require_positive(weight_sum, "weight_sum");

        const double weighted_value_sum = std::ranges::fold_left(
            range | std::views::transform([&value_fn, &weight_fn](const auto& item)
            {
                const double value = static_cast<double>(std::invoke(value_fn, item));
                const double weight = static_cast<double>(std::invoke(weight_fn, item));

                return value * weight;
            }),
            0.0,
            std::plus{}
        );

        return weighted_value_sum / weight_sum;
    }

    template <std::ranges::input_range Range, typename ValueFn, typename WeightFn>
    [[nodiscard]] double weighted_variance(
        const Range& range,
        ValueFn value_fn,
        WeightFn weight_fn
    )
    {
        const double mean = weighted_mean(range, value_fn, weight_fn);

        const double weight_sum = std::ranges::fold_left(
            range | std::views::transform([&weight_fn](const auto& item)
            {
                return static_cast<double>(std::invoke(weight_fn, item));
            }),
            0.0,
            std::plus{}
        );

        detail::require_positive(weight_sum, "weight_sum");

        const double squared_deviation_sum = std::ranges::fold_left(
            range | std::views::transform([mean, &value_fn, &weight_fn](const auto& item)
            {
                const double value = static_cast<double>(std::invoke(value_fn, item));
                const double weight = static_cast<double>(std::invoke(weight_fn, item));
                const double deviation = value - mean;

                return weight * deviation * deviation;
            }),
            0.0,
            std::plus{}
        );

        return squared_deviation_sum / weight_sum;
    }

    template <std::ranges::input_range Range, typename ValueFn, typename WeightFn>
    [[nodiscard]] double corrected_weighted_variance(
        const Range& range,
        ValueFn value_fn,
        WeightFn weight_fn
    )
    {
        const double mean = weighted_mean(range, value_fn, weight_fn);

        const double weight_sum = std::ranges::fold_left(
            range | std::views::transform([&weight_fn](const auto& item)
            {
                return static_cast<double>(std::invoke(weight_fn, item));
            }),
            0.0,
            std::plus{}
        );

        if (weight_sum <= 1.0)
        {
            throw std::domain_error("weight_sum must be greater than 1");
        }

        const double squared_deviation_sum = std::ranges::fold_left(
            range | std::views::transform([mean, &value_fn, &weight_fn](const auto& item)
            {
                const double value = static_cast<double>(std::invoke(value_fn, item));
                const double weight = static_cast<double>(std::invoke(weight_fn, item));
                const double deviation = value - mean;

                return weight * deviation * deviation;
            }),
            0.0,
            std::plus{}
        );

        return squared_deviation_sum / (weight_sum - 1.0);
    }

    [[nodiscard]] inline double standard_deviation(const double variance)
    {
        detail::require_non_negative(variance, "variance");

        return std::sqrt(variance);
    }
}

namespace stats::intervals
{
    template <floating_point_like Real>
    inline Real normal_critical(const Real gamma)
    {
        detail::require_probability_open(gamma, "gamma");

        const boost::math::normal_distribution<Real> dist(0, 1);

        return boost::math::quantile(
            dist,
            (Real{1} + gamma) / Real{2}
        );
    }

    template <floating_point_like Real>
    inline confidence_interval<Real> mean_confidence_interval_known_sigma(
        const Real x_bar,
        const Real sigma,
        const int n,
        const Real gamma
    )
    {
        detail::require_finite(x_bar, "x_bar");
        detail::require_positive(sigma, "sigma");

        if (n <= 0)
            throw std::domain_error("n must be positive");

        detail::require_probability_open(gamma, "gamma");

        const Real t_gamma = normal_critical<Real>(gamma);
        const Real delta = t_gamma * sigma / std::sqrt(static_cast<Real>(n));

        return {
            x_bar - delta,
            x_bar + delta
        };
    }

    template <floating_point_like Real>
    inline Real chi_squared_critical(
        const Real p,
        const Real k
    )
    {
        // перевіряє, що 0 < p < 1 коректне для квантиля
        detail::require_probability_open(p, "p");
        // перевіряє, що k > 0
        detail::require_positive(k, "k");

        const boost::math::chi_squared_distribution<Real> dist(k);

        return boost::math::quantile(dist, p);
    }

    template <floating_point_like Real>
    inline confidence_interval<Real> sigma_confidence_interval(
        const Real s,
        const int n,
        const Real gamma
    )
    {
        // Перевіряє, що s > 0, і що число скінченне.
        // кидає std::domain_error якщо ні
        detail::require_positive(s, "s");

        if (n <= 1)
            throw std::domain_error("n must be greater than 1");

        // перевіряє що 0 < gamma < 1 тобто що надійність оцінки є коректною ймовірністю
        detail::require_probability_open(gamma, "gamma");

        const Real k = static_cast<Real>(n - 1);

        const Real p_left = (Real{1} - gamma) / Real{2};
        const Real p_right = (Real{1} + gamma) / Real{2};

        const Real chi_left =
            chi_squared_critical<Real>(p_left, k);

        const Real chi_right =
            chi_squared_critical<Real>(p_right, k);

        return {
            s * std::sqrt(k / chi_right),
            s * std::sqrt(k / chi_left)
        };
    }
}

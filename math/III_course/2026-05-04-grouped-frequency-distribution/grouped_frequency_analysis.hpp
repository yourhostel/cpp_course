#pragma once

#include <vector>
#include <string>
#include <utility>
#include <ranges>
#include <cstdlib>

#include "stats.hpp"
#include "grouped_frequency_tasks.hpp"

namespace grouped_frequency::analysis
{
    /**
     * Результат обчислення вибіркових характеристик
     * для інтервального статистичного ряду.
     *
     * mean математичне сподівання вибірки
     * variance вибіркова дисперсія з дільником n
     * corrected_variance виправлена дисперсія з дільником n - 1
     * standard_deviation корінь з variance
     */
    struct grouped_sample_statistics
    {
        double mean;
        double variance;
        double corrected_variance;
        double standard_deviation;
    };

    /**
     * Обчислення середини інтервалу.
     *
     * Вхід "2-6"
     * Вихід 4.0
     *
     * Використовується як представник значення інтервалу x_i
     */
    inline double midpoint(const std::string& interval)
    {
        const std::size_t pos = interval.find('-');

        const double a = std::stod(interval.substr(0, pos));
        const double b = std::stod(interval.substr(pos + 1));

        return (a + b) / 2.0;
    }

    /**
     * Допоміжний адаптер для завершення pipeline через оператор |
     *
     * Дозволяє застосувати довільну функцію як останній крок:
     * data | ... | pipe_closure{ lambda }
     */
    template <typename F>
    struct pipe_closure
    {
        F f;

        template <typename T>
        friend auto operator|(T&& value, const pipe_closure& closure)
        {
            return closure.f(std::forward<T>(value));
        }
    };

    template <typename F>
    pipe_closure(F) -> pipe_closure<F>;

    /**
     * Обчислення характеристик для одного статистичного ряду.
     *
     * Вхід:
     * std::vector<interval_frequency>
     *
     * Алгоритм:
     * 1. Перетворення інтервалів у пари midpoint і frequency
     * 2. Обчислення характеристик через stats::sample
     *
     * Вихід:
     * grouped_sample_statistics
     *
     * Приклад використання:
     *
     * const auto& task = grouped_frequency::tasks[0];
     * const auto result =
     *     grouped_frequency::analysis::calculate(task.data);
     *
     * result.mean
     * result.variance
     * result.corrected_variance
     * result.standard_deviation
     */
    inline grouped_sample_statistics calculate(
        const std::vector<interval_frequency>& data
    )
    {
        return data
            | std::views::transform([](const interval_frequency& x)
            {
                return std::pair
                {
                    midpoint(x.interval),
                    x.frequency
                };
            })
            | std::ranges::to<std::vector<std::pair<double, int>>>()
            | pipe_closure{
                [](const auto& d)
                {
                    const auto value = [](const auto& x) { return x.first; };
                    const auto weight = [](const auto& x) { return x.second; };

                    const double mean =
                        stats::sample::weighted_mean(d, value, weight);

                    const double variance =
                        stats::sample::weighted_variance(d, value, weight);

                    return grouped_sample_statistics
                    {
                        .mean = mean,
                        .variance = variance,
                        .corrected_variance =
                        stats::sample::corrected_weighted_variance(d, value, weight),
                        .standard_deviation =
                        stats::sample::standard_deviation(variance)
                    };
                }
            };
    }
}

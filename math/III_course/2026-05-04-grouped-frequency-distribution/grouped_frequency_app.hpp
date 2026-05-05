#pragma once

#include "print.hpp"
#include "grouped_frequency_tasks.hpp"
#include "grouped_frequency_analysis.hpp"

#include <vector>
#include <ranges>
#include <functional>
#include <memory>
#include <iostream>
#include <format>

using namespace print::charts;
using namespace print::tables;
using namespace grouped_frequency;

namespace grouped_frequency::app
{
    inline std::vector<histogram_bar>
    to_relative_histogram_data(const grouped_frequency_task& task)
    {
        const int total = std::ranges::fold_left(
            task.data | std::views::transform(&interval_frequency::frequency),
            0,
            std::plus{}
        );

        return task.data
            | std::views::transform([total](const auto& item)
            {
                return histogram_bar
                {
                    .category = item.interval,
                    .value = static_cast<double>(item.frequency) / total
                };
            })
            | std::ranges::to<std::vector<histogram_bar>>();
    }

    inline std::vector<table_row<std::string>>
    to_table_data(const grouped_frequency_task& task)
    {
        return task.data
            | std::views::transform([](const auto& item)
            {
                return table_row<std::string>
                {
                    .value_first = item.interval,
                    .value_second = std::to_string(item.frequency)
                };
            })
            | std::ranges::to<std::vector<table_row<std::string>>>();
    }

    inline const grouped_frequency_task*
    find_task(const std::string& input)
    {
        if (input.starts_with('i'))
        {
            const std::size_t index = std::stoul(input.substr(1));
            return index < tasks.size() ? &tasks[index] : nullptr;
        }

        const auto it = task_index.find(input);
        return it != task_index.end() ? &tasks.at(it->second) : nullptr;
    }

    inline void print_statistics(const analysis::grouped_sample_statistics& s)
    {
        std::cout << CYAN << "X̄" << " = " << s.mean << RESET
            << " (вибіркове середнє)\n";

        std::cout << MAGENTA << "σв²" << " = " << s.variance << RESET
            << " (вибіркова дисперсія)\n";

        std::cout << YELLOW << "S²" << " = " << s.corrected_variance << RESET
            << " (виправлена вибіркова дисперсія)\n";

        std::cout << GREEN << "σв" << " = " << s.standard_deviation << RESET
            << " (вибіркове середнє квадратичне відхилення)\n";
    }

    inline std::unique_ptr<QChartView>
    show_task_chart(const grouped_frequency_task& task)
    {
        const auto histogram_data = to_relative_histogram_data(task);
        const auto table_data = to_table_data(task);

        print_distribution_table(
            "Завдання",
            task.task_number,
            "interval",
            "n_i",
            table_data
        );

        const auto stats = analysis::calculate(task.data);

        print_statistics(stats);

        const histogram_options options
        {
            .window_title = std::format("Завдання № {}", task.task_number),
            .set_name = "Відносна частота",
            .chart_title = "Гістограма відносних частот",
            .y_axis_title = "Частка",
            .x_axis_title = "Інтервали",
            .y_min = 0.0,
            .y_max = 0.4,
            .width = 800,
            .height = 600,
            .precision = 2
        };

        auto chart_view = create_histogram_chart_view(histogram_data, options);
        chart_view->show();

        return chart_view;
    }
}

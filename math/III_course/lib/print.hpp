//
// Created by tysser on 25.04.26.
//

#pragma once
#include <string>
#include <vector>
#include <memory>


class QChartView;

namespace print::tables
{
    inline std::string center(const std::string& s, int width);

    template <typename T>
    void print_distribution_table(const std::string& task_name, const std::string& number,
                                         const std::vector<T>& probs);
}

namespace print::charts
{
    struct histogram_bar
    {
        std::string category;
        double value;
    };

    struct histogram_options
    {
        std::string window_title;   // назва вікна

        std::string set_name;
        std::string chart_title;
        std::string y_axis_title;
        std::string x_axis_title;

        double y_min = 0.0;
        double y_max = 1.0;

        int width = 800;
        int height = 600;

        int precision = 2;
    };

    inline std::unique_ptr<QChartView> create_histogram_chart_view(
        const std::vector<histogram_bar>& data,
        const histogram_options& options
    );
}

#include "print.tpp"

//
// Created by tysser on 25.04.26.
//

#pragma once

constexpr auto BLACK = "\033[30m";
constexpr auto RED = "\033[31m";
constexpr auto GREEN = "\033[32m";
constexpr auto YELLOW = "\033[33m";
constexpr auto BLUE = "\033[34m";
constexpr auto MAGENTA = "\033[35m";
constexpr auto CYAN = "\033[36m";
constexpr auto WHITE = "\033[37m";

constexpr auto RESET = "\033[0m";

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QApplication>
#include <QValueAxis>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <algorithm>
#include <ranges>


namespace print::tables
{
    template <typename T>
    struct table_row
    {
        T value_first;
        T value_second;
    };

    inline std::string center(const std::string& s, int width)
    {
        const int len = static_cast<int>(s.size());

        if (len >= width) return s;

        const int left = (width - len) / 2;
        const int right = width - len - left;

        return std::string(left, ' ') + s + std::string(right, ' ');
    }

    template <typename T>
    void print_distribution_table(const std::string& task_name,
                                  const std::string& number,
                                  const std::string& first_row_name,
                                  const std::string& second_row_name,
                                  const std::vector<T>& data)
    {
        constexpr int width = 12;

        std::cout << GREEN << task_name << " " << number << RESET << "\n";

        // перший рядок
        std::cout << center(first_row_name, width);
        for (const auto& row : data)
        {
            std::ostringstream ss;
            ss << row.value_first;
            std::cout << center(ss.str(), width);
        }
        std::cout << "\n";

        // розділювач
        for (std::size_t i = 0; i <= data.size(); ++i)
            std::cout << YELLOW << std::string(width, '-');
        std::cout << RESET << "\n";

        // другий рядок
        std::cout << center(second_row_name, width);
        for (const auto& row : data)
        {
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(6) << row.value_second;
            std::cout << center(ss.str(), width);
        }

        std::cout << "\n\n";
    }
}

namespace print::charts
{
    inline std::unique_ptr<QChartView> create_histogram_chart_view(
        const std::vector<histogram_bar>& data,
        const histogram_options& options
    )
    {
        // кореневий віджет
        auto chart_view = std::make_unique<QChartView>();

        // заголовок вікна
        if (!options.window_title.empty())
            chart_view->setWindowTitle(QString::fromStdString(options.window_title));

        // графік
        auto* chart = new QChart();
        chart_view->setChart(chart);

        // набір значень для стовпчиків
        auto* set = new QBarSet(QString::fromStdString(options.set_name));
        set->setLabelColor(Qt::black);

        QStringList categories;

        // заповнюємо підписи осі X і значення стовпчиків
        std::ranges::for_each(data, [&](const auto& item)
        {
            const auto& [category, value] = item;

            categories << QString::fromStdString(category);
            *set << value;
        });

        // серія стовпчиків
        auto* series = new QBarSeries();
        series->append(set);

        chart->addSeries(series);

        // заголовок графіка
        chart->setTitle(QString::fromStdString(options.chart_title));
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // вісь X
        auto* axis_x = new QBarCategoryAxis();
        axis_x->append(categories);

        if (!options.x_axis_title.empty())
            axis_x->setTitleText(QString::fromStdString(options.x_axis_title));

        chart->addAxis(axis_x, Qt::AlignBottom);
        series->attachAxis(axis_x);

        // вісь Y
        auto* axis_y = new QValueAxis();
        axis_y->setTitleText(QString::fromStdString(options.y_axis_title));
        axis_y->setRange(options.y_min, options.y_max);

        chart->addAxis(axis_y, Qt::AlignLeft);
        series->attachAxis(axis_y);

        // підписи значень над стовпчиками
        series->setLabelsVisible(true);
        series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
        series->setLabelsFormat("@value");
        series->setLabelsPrecision(options.precision);

        // щоб верхній підпис не обрізався, залишаємо запас зверху
        chart->setMargins(QMargins(20, 40, 20, 20));

        // згладжування і розмір
        chart_view->setRenderHint(QPainter::Antialiasing);
        chart_view->resize(options.width, options.height);

        return chart_view;
    }
}

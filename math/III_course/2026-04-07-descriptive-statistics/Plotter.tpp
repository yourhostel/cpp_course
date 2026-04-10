//
// Created by tysser on 07.04.26.
//
#pragma once
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <ranges>

inline void Plotter::plot_relative_frequency_polygon(const std::string& variant_number,
                                                     const std::map<int, double>& polygon)
{
    if (polygon.empty()) return;

    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) return;

    const int x_min = polygon.begin()->first;
    const int x_max = polygon.rbegin()->first;

    const double x_padding = 0.5;

    const auto y_max_it = std::ranges::max_element(
        polygon | std::views::values
    );
    const double y_max = *y_max_it;
    const double y_padding = y_max * 0.1;

    fprintf(gp, "set title 'Полігон відносної частоти, варіант %s'\n", variant_number.c_str());
    fprintf(gp, "set grid\n");
    fprintf(gp, "set xlabel 'x'\n");
    fprintf(gp, "set ylabel 'p'\n");

    fprintf(gp, "set xrange [%f:%f]\n", x_min - x_padding, x_max + x_padding);
    fprintf(gp, "set yrange [0:%f]\n", y_max + y_padding);

    fprintf(gp, "set style line 1 lc rgb '#008080' lw 2 pt 7 ps 1.2\n");
    fprintf(gp, "unset key\n");

    fprintf(gp, "$data << EOD\n");
    for (const auto& [x, y] : polygon)
        fprintf(gp, "%d %.6f\n", x, y);
    fprintf(gp, "EOD\n");

    fprintf(gp, "plot $data with linespoints ls 1\n");

    pclose(gp);
}

inline void Plotter::plot_empirical_function(
    const std::string& variant,
    const std::vector<std::pair<double, double>>& points)
{
    if (points.empty()) return;

    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) return;

    const double x_min = points.front().first;
    const double x_max = points.back().first;

    const double x_padding = 0.5;

    fprintf(gp, "set title 'Емпірична функція розподілу, варіант %s'\n", variant.c_str());
    fprintf(gp, "set grid\n");
    fprintf(gp, "set xlabel 'x'\n");
    fprintf(gp, "set ylabel 'F(x)'\n");
    fprintf(gp, "set xrange [%f:%f]\n", x_min - x_padding, x_max + x_padding);
    fprintf(gp, "set yrange [0:1.1]\n");
    fprintf(gp, "set style line 1 lc rgb '#008080' lw 2\n");
    fprintf(gp, "unset key\n");

    fprintf(gp, "$data << EOD\n");

    fprintf(gp, "%f %f\n", x_min - x_padding, 0.0);
    fprintf(gp, "%f %f\n", points.front().first, 0.0);

    for (const auto& [x, y] : points)
        fprintf(gp, "%f %f\n", x, y);

    fprintf(gp, "%f %f\n", x_max + x_padding, 1.0);

    fprintf(gp, "EOD\n");

    fprintf(gp, "plot $data with steps ls 1\n");

    pclose(gp);
}
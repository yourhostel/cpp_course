//
// Created by tysser on 07.04.26.
//

#pragma once

#include <map>
#include <string>

class Plotter final
{
public:
    static void plot_relative_frequency_polygon(const std::string& variant_number,
                                         const std::map<int, double>& polygon);

    static void plot_empirical_function(const std::string& variant,
                                    const std::vector<std::pair<double,double>>& points);
};

#include "Plotter.tpp"

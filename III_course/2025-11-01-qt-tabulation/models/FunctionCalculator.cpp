//
// Created by tysser on 01.11.25.
//

// models/FunctionCalculator.cpp

#include "FunctionCalculator.h"

std::vector<Point> FunctionCalculator::tabulate(
        const std::function<double(double)>& func,
        const double a, const double b, const double h)
{
    std::vector<Point> result;

    for (double x = a; x <= b; x += h) {
        result.push_back({x, func(x)});
    }

    return result;
}

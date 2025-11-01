//
// Created by tysser on 01.11.25.
//

// controllers/TabulationController.cpp
#include "TabulationController.h"

std::vector<Point> TabulationController::calculate(double a, double b, double h,
                                                   const std::function<double(double)>& f)
{
    std::vector<Point> data;
    for(double x = a; x <= b; x += h) {
        data.push_back({x, f(x)});
    }
    return data;
}
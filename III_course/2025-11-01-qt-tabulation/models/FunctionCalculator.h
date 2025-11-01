//
// Created by tysser on 01.11.25.
//

// models/FunctionCalculator.h
#ifndef FUNCTIONCALCULATOR_H
#define FUNCTIONCALCULATOR_H

#include <vector>
#include <functional>
#include "Point.h"

class FunctionCalculator {
public:
    static std::vector<Point> tabulate(
        const std::function<double(double)>& func,
        double a, double b, double h
    );
};

#endif //FUNCTIONCALCULATOR_H

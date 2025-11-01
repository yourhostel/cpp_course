//
// Created by tysser on 01.11.25.
//

// controllers/FunctionController.cpp
#include "FunctionController.h"
#include <cmath>
#include <map>

std::function<double(double)> FunctionController::getFunction(const QString &name)
{
    static std::map<QString, std::function<double(double)>> functions = {
        {"sin(x)", [](const double x) { return sin(x); }},
        {"cos(x)", [](const double x) { return cos(x); }},
        {"x^2 + 2x + 1", [](const double x) { return x*x + 2*x + 1; }},
    };

    if (functions.contains(name)) {
        return functions[name];
    }

    return [](double x) { return 0.0; }; // дефолт — 0
}

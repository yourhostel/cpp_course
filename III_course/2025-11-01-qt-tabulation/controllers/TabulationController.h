//
// Created by tysser on 01.11.25.
//

// controllers/TabulationController.h
#ifndef TABULATIONCONTROLLER_H
#define TABULATIONCONTROLLER_H

#include <vector>
#include "Point.h"
#include <functional>

class TabulationController {
public:
    static std::vector<Point> calculate(double a, double b, double h,
                                        const std::function<double(double)>& f);
};

#endif //TABULATIONCONTROLLER_H

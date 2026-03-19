//
// Created by tysser on 19.03.26.
//

#ifndef CPP_COURSE_DISTRIBUTIONSTATISTICS_H
#define CPP_COURSE_DISTRIBUTIONSTATISTICS_H

#include <cmath>

class DistributionStatistics {
public:
    template<typename Function>
    static double expectation(Function f, double a, double b);

    template<typename Function>
    static double variance(Function f, double a, double b);

    template<typename Function>
    static double standard_deviation(Function f, double a, double b);

private:
    template<typename Function>
    static double second_moment(Function f, double a, double b);

    template<typename Function>
    static double integrate(Function f, double a, double b);
};

#include "DistributionStatistics.tpp"

#endif //CPP_COURSE_DISTRIBUTIONSTATISTICS_H
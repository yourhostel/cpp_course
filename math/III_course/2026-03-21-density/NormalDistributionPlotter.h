//
// Created by tysser on 21.03.26.
//

#pragma once
#include <string>


class NormalDistributionPlotter
{
public:
    NormalDistributionPlotter(double mean, double sigma);

    [[nodiscard]] double density(double x) const;

    static double standard_normal_density(double x);
    static double laplace_phi(double x);

    void plot_density_with_interval(
    double x_min,
    double x_max,
    double interval_left,
    double interval_right,
    const std::string& title = "Normal distribution density"
    ) const;

private:
    double mean_;
    double sigma_;
};

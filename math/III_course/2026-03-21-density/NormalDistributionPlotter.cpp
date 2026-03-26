//
// Created by tysser on 21.03.26.
//

#include "NormalDistributionPlotter.h"
#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <string>

void NormalDistributionPlotter::validate_plot_arguments(
    const double x_min,
    const double x_max,
    const double interval_left,
    const double interval_right
)
{
    const char* msg =
        (x_min >= x_max) ? "x_min має бути меншим за x_max" :
        (interval_left >= interval_right) ? "interval_left має бути меншим за interval_right" :
        (interval_left < x_min || interval_right > x_max) ? "інтервал має знаходитись у межах діапазону побудови" :
        nullptr;

    msg ? throw std::invalid_argument(msg) : void();
}

NormalDistributionPlotter::NormalDistributionPlotter(const double mean, const double sigma) : mean_(mean), sigma_(sigma)
{
        if (sigma_ <= 0.0)throw std::invalid_argument("sigma має бути додатним");
}

// Щільність нормального розподілу N (0, 1)
double NormalDistributionPlotter::standard_normal_density(const double x)
{
    return (1.0 / std::sqrt(2.0 * std::numbers::pi_v<double>)) * std::exp(-x * x / 2.0);
}

// Щільність нормального розподілу N (a, sigma^2)
double NormalDistributionPlotter::density(const double x) const
{
    return (1.0 / sigma_) * standard_normal_density((x - mean_) / sigma_);
}

// Таблична функція Лапласа (не CDF)
double NormalDistributionPlotter::laplace_phi(const double x)
{
    return 0.5 * std::erf(x / std::sqrt(2.0));
}

void NormalDistributionPlotter::plot_density_with_interval(
    const double x_min,
    const double x_max,
    const double interval_left,
    const double interval_right,
    const std::string& title
) const
{
    validate_plot_arguments(x_min, x_max, interval_left, interval_right);

    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) {
        throw std::runtime_error("не вдалося запустити gnuplot");
    }

    constexpr int samples = 3000;
    const double step = (x_max - x_min) / static_cast<double>(samples);

    fprintf(gp, "set title '%s'\n", title.c_str());
    fprintf(gp, "set grid\n");
    fprintf(gp, "set xrange [%f:%f]\n", x_min, x_max);
    fprintf(gp, "set xlabel 'x'\n");
    fprintf(gp, "set ylabel 'f(x)'\n");
    fprintf(gp, "set key off\n");
    fprintf(gp, "set style line 1 lc rgb '#0b6e99' lw 2\n");
    fprintf(gp, "set style line 2 lc rgb '#cc0000' lw 2 dt 2\n");
    fprintf(gp, "set style fill solid 0.35 noborder\n");

    fprintf(gp, "$curve << EOD\n");
    for (double x = x_min; x <= x_max; x += step)
    {
        fprintf(gp, "%f %f\n", x, density(x));
    }
    fprintf(gp, "EOD\n");

    fprintf(gp, "$shade << EOD\n");
    fprintf(gp, "%f 0\n", interval_left);

    for (double x = interval_left; x <= interval_right; x += step)
    {
        fprintf(gp, "%f %f\n", x, density(x));
    }
    fprintf(gp, "%f 0\n", interval_right);
    fprintf(gp, "EOD\n");

    const double left_y = density(interval_left);
    const double right_y = density(interval_right);

    fprintf(
        gp,
        "plot "
        "$shade with filledcurves x1 lc rgb '#7ec8e3', "
        "$curve with lines ls 1, "
        "'-' with lines ls 2, "
        "'-' with lines ls 2\n"
    );

    fprintf(gp, "%f 0\n", interval_left);
    fprintf(gp, "%f %f\n", interval_left, left_y);
    fprintf(gp, "e\n");

    fprintf(gp, "%f 0\n", interval_right);
    fprintf(gp, "%f %f\n", interval_right, right_y);
    fprintf(gp, "e\n");

    pclose(gp);
}
//
// Created by tysser on 19.03.26.
//

#include "DistributionRepository.h"

#include <cmath>
#include <stdexcept>

DistributionRepository::DistributionRepository() {
cases_ = {
    {"8.1",  2.0, 3.0, -1.0, 1.0,
        [](double x){ return x - 2.0; },
        [](double x){ return 1.0; }
    },
    {"8.2",  1.0, 2.0, -1.0, 1.5,
        [](double x){ return (x*x - x)/2.0; },
        [](double x){ return (2.0*x - 1.0)/2.0; }
    },
    {"8.3",  2.0, 3.0, 0.0, 2.5,
        [](double x){ return 9.0*(x*x - 4.0)/(5.0*x*x); },
        [](double x){ return 72.0/(5.0*x*x*x); }
    },
    {"8.4",  2.0, 4.0, 2.0, 3.0,
        [](double x){ return 2.0 - 4.0/x; },
        [](double x){ return 4.0/(x*x); }
    },
    {"8.5",  0.0, 1.0, 0.0, 0.5,
        [](double x){ return std::sqrt(x); },
        [](double x){ return 1.0/(2.0*std::sqrt(x)); }
    },
    {"8.6", -1.0, 3.0, 0.0, 1.0,
        [](double x){ return (x+1.0)*(x+1.0)/16.0; },
        [](double x){ return (x+1.0)/8.0; }
    },
    {"8.7",  3.0, 4.0, 0.5, 1.0,
        [](double x){ return x - 3.0; },
        [](double x){ return 1.0; }
    },
    {"8.8",  0.0, 1.0, 0.2, 1.0,
        [](double x){ return (x*x + x)/2.0; },
        [](double x){ return (2.0*x + 1.0)/2.0; }
    },
    {"8.9", -2.0,-1.0, -2.0, 0.0,
        [](double x){ return -2.0/x - 1.0; },
        [](double x){ return 2.0/(x*x); }
    },
    {"8.10", 0.0, 1.0/3.0, -2.0, 0.25,
        [](double x){ return 3.0*x*x + 2.0*x; },
        [](double x){ return 6.0*x + 2.0; }
    },
    {"8.11", 2.0, 4.0, -2.0, 3.0,
        [](double x){ return x/2.0 - 1.0; },
        [](double x){ return 0.5; }
    },
    {"8.12", 4.0, 9.0, 1.0, 3.0,
        [](double x){ return (x-4.0)*(x-4.0)/25.0; },
        [](double x){ return 2.0*(x-4.0)/25.0; }
    },
    {"8.13",-2.0, 0.0, 0.0, 1.0,
        [](double x){ return (x+2.0)*(x+2.0)/4.0; },
        [](double x){ return (x+2.0)/2.0; }
    },
    {"8.14", 0.0, 1.0, 0.0, 0.5,
        [](double x){ return std::sqrt(x*x*x); },
        [](double x){ return 1.5*std::sqrt(x); }
    },
    {"8.15", 1.0, 2.0, 1.5, 2.5,
        [](double x){ return (4.0/3.0)*(1.0 - 1.0/(x*x)); },
        [](double x){ return 8.0/(3.0*x*x*x); }
    },
    {"8.16", 0.0, 4.0, 1.0, 2.0,
        [](double x){ return 0.5*std::sqrt(x); },
        [](double x){ return 1.0/(4.0*std::sqrt(x)); }
    },
    {"8.17", 0.0, 1.0, 0.5, 2.5,
        [](double x){ return std::pow(x,3.0/4.0); },
        [](double x){ return 3.0/(4.0*std::pow(x,1.0/4.0)); }
    },
    {"8.18", 1.0, 2.0, 0.0, 1.5,
        [](double x){ return 2.0 - 2.0/x; },
        [](double x){ return 2.0/(x*x); }
    },
    {"8.19", 0.0, 1.0, -1.0, 0.5,
        [](double x){ return std::pow(x*x,1.0/3.0); },
        [](double x){ return 2.0/(3.0*std::pow(x,1.0/3.0)); }
    },
    {"8.20",-1.0, 1.0, 1.0, 2.0,
        [](double x){ return (x+1.0)*(x+1.0)/4.0; },
        [](double x){ return (x+1.0)/2.0; }
    },
    {"8.21", 1.0, 2.0, 1.0, 1.5,
        [](double x){ return (x-1.0)*(x-1.0); },
        [](double x){ return 2.0*(x-1.0); }
    },
    {"8.22",-1.0, 0.0, -0.5, 1.0,
        [](double x){ return 1.0 - std::pow(x*x*x*x,1.0/3.0); },
        [](double x){ return -(4.0/3.0)*x/std::pow(x*x*x*x,2.0/3.0); }
    },
    {"8.23", 0.0, 4.0, 2.0, 3.0,
        [](double x){ return 0.125*std::sqrt(x*x*x); },
        [](double x){ return 3.0*std::sqrt(x)/16.0; }
    },
    {"8.24", 2.0, 5.0, 3.0, 4.0,
        [](double x){ return (x-2.0)*(x-2.0)/9.0; },
        [](double x){ return 2.0*(x-2.0)/9.0; }
    },
    {"8.25", 1.0, 4.0, 2.0, 3.5,
        [](double x){ return (x-1.0)*(x-1.0)/9.0; },
        [](double x){ return 2.0*(x-1.0)/9.0; }
    },
    {"8.26", 1.0, 4.0, 1.0, 2.0,
        [](double x){ return std::sqrt(x) - 1.0; },
        [](double x){ return 1.0/(2.0*std::sqrt(x)); }
    },
    {"8.27", 0.0, 1.0, 0.5, 2.0,
        [](double x){ return std::pow(x*x*x*x,1.0/3.0); },
        [](double x){ return 4.0/(3.0*std::pow(x,1.0/3.0)); }
    },
    {"8.28", 3.0, 5.0, 3.0, 4.5,
        [](double x){ return (x-3.0)*(x-3.0)/4.0; },
        [](double x){ return (x-3.0)/2.0; }
    },
    {"8.29", 0.0, 2.0, 1.0, 1.5,
        [](double x){ return x*x*x/8.0; },
        [](double x){ return 3.0*x*x/8.0; }
    },
    {"8.30", 1.0, 4.0, 1.0, 3.0,
        [](double x){ return (std::sqrt(x*x*x) - 1.0)/7.0; },
        [](double x){ return 3.0*std::sqrt(x)/14.0; }
    }
};
}

const distribution_case& DistributionRepository::get_case(std::size_t variant_number) const {
    if (variant_number == 0 || variant_number > cases_.size()) {
        throw std::out_of_range("variant_number must be in range [1, 30]");
    }
    return cases_[variant_number - 1];
}

std::size_t DistributionRepository::size() const {
    return cases_.size();
}

void DistributionRepository::plot_distribution_function(std::size_t variant_number) const {
    const distribution_case& current_case = get_case(variant_number);

    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) {
        return;
    }

    const double a = current_case.a;
    const double b = current_case.b;

    fprintf(gp, "set title 'F(x), variant %s'\n", current_case.label.c_str());
    fprintf(gp, "set grid\n");
    fprintf(gp, "set xrange [%f:%f]\n", a - 1.0, b + 1.0);
    fprintf(gp, "set yrange [-0.1:1.1]\n");
    fprintf(gp, "set samples 2000\n");
    fprintf(gp, "unset key\n");

    fprintf(gp, "set style line 1 lc rgb '#008080' lw 2\n");
    fprintf(gp, "set style line 2 lc rgb '#008080' pt 7 ps 1.2\n");

    fprintf(gp, "$data << EOD\n");
    const double step = (b - a) / 1000.0;
    for (double x = a; x <= b; x += step) {
        fprintf(gp, "%f %f\n", x, current_case.distribution_function(x));
    }
    fprintf(gp, "EOD\n");

    fprintf(
        gp,
        "plot "
        "(x<=%f ? 0 : 1/0) with lines ls 1, "
        "$data with lines ls 1, "
        "(x>%f ? 1 : 1/0) with lines ls 1, "
        "'-' with points ls 2\n",
        a, b
    );

    fprintf(gp, "%f 0\n", a);
    fprintf(gp, "%f 1\n", b);
    fprintf(gp, "e\n");

    pclose(gp);
}

void DistributionRepository::plot_density_function(std::size_t variant_number) const {
    const distribution_case& current_case = get_case(variant_number);

    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) {
        return;
    }

    const double a = current_case.a;
    const double b = current_case.b;

    fprintf(gp, "set title 'f(x), variant %s'\n", current_case.label.c_str());
    fprintf(gp, "set grid\n");
    fprintf(gp, "set xrange [%f:%f]\n", a - 1.0, b + 1.0);
    fprintf(gp, "set yrange [-0.1:2.0]\n");
    fprintf(gp, "set samples 2000\n");
    fprintf(gp, "unset key\n");

    fprintf(gp, "set style line 1 lc rgb '#008080' lw 2\n");
    fprintf(gp, "set style line 2 lc rgb '#008080' pt 7 ps 1.2\n");

    fprintf(gp, "$data << EOD\n");
    const double step = (b - a) / 1000.0;
    for (double x = a; x <= b; x += step) {
        fprintf(gp, "%f %f\n", x, current_case.density_function(x));
    }
    fprintf(gp, "EOD\n");

    fprintf(
        gp,
        "plot "
        "(x<=%f ? 0 : 1/0) with lines ls 1, "
        "$data with lines ls 1, "
        "(x>=%f ? 0 : 1/0) with lines ls 1, "
        "'-' with points ls 2\n",
        a, b
    );

    fprintf(gp, "%f 0\n", a);
    fprintf(gp, "%f 0\n", b);
    fprintf(gp, "e\n");

    pclose(gp);
}
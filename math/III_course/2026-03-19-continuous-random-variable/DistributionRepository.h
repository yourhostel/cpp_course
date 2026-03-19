//
// Created by tysser on 19.03.26.
//

#ifndef CPP_COURSE_DISTRIBUTIONREPOSITORY_H
#define CPP_COURSE_DISTRIBUTIONREPOSITORY_H
#include <functional>
#include <string>

struct distribution_case {
    std::string label;
    double a;
    double b;
    double alpha;
    double beta;
    std::function<double(double)> distribution_function;
    std::function<double(double)> density_function;
};

class DistributionRepository
{
public:
    DistributionRepository();

    [[nodiscard]] const distribution_case& get_case(std::size_t variant_number) const;
    [[nodiscard]] std::size_t size() const;

    void plot_distribution_function(std::size_t variant_number) const;
    void plot_density_function(std::size_t variant_number) const;

private:
    std::vector<distribution_case> cases_;
};

#endif //CPP_COURSE_DISTRIBUTIONREPOSITORY_H
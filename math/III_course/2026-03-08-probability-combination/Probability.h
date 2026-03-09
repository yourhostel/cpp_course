//
// Created by tysser on 08.03.26.
//

#ifndef CPP_COURSE_PROBABILITY_H
#define CPP_COURSE_PROBABILITY_H

#include <vector>

class Probability
{
public:
    static long long mirror_index(long long n, long long r);

    static double combination_by_product(long long n, long long r);

    static double probability(
        long long total_count,
        long long sample_count,
        const std::vector<long long>& type_sizes,
        const std::vector<long long>& selected_counts
    );
};

#endif //CPP_COURSE_PROBABILITY_H
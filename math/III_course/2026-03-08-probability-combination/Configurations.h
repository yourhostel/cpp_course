//
// Created by tysser on 09.03.26.
//

#ifndef CPP_COURSE_CONFIGURATIONS_H
#define CPP_COURSE_CONFIGURATIONS_H

#include <vector>

class Configurations
{
public:

    // Генерує всі конфігурації (x1,...,xk)
    static std::vector<std::vector<long long>> configurations(
        const std::vector<long long>& type_sizes, // N_i кількість типів
        long long sample_count,                   // m розмір вибірки
        long long target_type,                    // j індекс типу
        long long min_count                       // h мінімум x_j
    );

private:

    // Рекурсивна генерація конфігурацій
    static void generate(
        const std::vector<long long>& type_sizes,     // N_i обмеження типів
        long long index,                              // поточний тип
        long long remaining,                          // залишок m
        long long target_type,                        // j тип події
        long long min_count,                          // h мінімум x_j
        std::vector<long long>& current,              // поточний x
        std::vector<std::vector<long long>>& result   // результат
    );
};

#endif //CPP_COURSE_CONFIGURATIONS_H
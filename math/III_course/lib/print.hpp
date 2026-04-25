//
// Created by tysser on 25.04.26.
//

#pragma once
#include <string>
#include <vector>


namespace print::tables
{
    inline std::string center(const std::string& s, int width);

    template <typename T>
    void print_distribution_table(const std::string& task_name, const std::string& number,
                                         const std::vector<T>& probs);
}

#include "print.tpp"

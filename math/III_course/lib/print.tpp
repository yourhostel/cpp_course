//
// Created by tysser on 25.04.26.
//

#pragma once

constexpr auto BLACK = "\033[30m";
constexpr auto RED = "\033[31m";
constexpr auto GREEN = "\033[32m";
constexpr auto YELLOW = "\033[33m";
constexpr auto BLUE = "\033[34m";
constexpr auto MAGENTA = "\033[35m";
constexpr auto CYAN = "\033[36m";
constexpr auto WHITE = "\033[37m";

constexpr auto RESET = "\033[0m";

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


namespace print::tables
{
    template <typename T>
    struct table_row
    {
        T value_first;
        T value_second;
    };

    inline std::string center(const std::string& s, int width)
    {
        const int len = static_cast<int>(s.size());

        if (len >= width) return s;

        const int left = (width - len) / 2;
        const int right = width - len - left;

        return std::string(left, ' ') + s + std::string(right, ' ');
    }

    template <typename T>
    void print_distribution_table(const std::string& task_name,
                                         const std::string& number,
                                         const std::string& first_row_name,
                                         const std::string& second_row_name,
                                         const std::vector<T>& data)
    {
        constexpr int width = 12;

        std::cout << GREEN << task_name << " " << number << RESET << "\n";

        // перший рядок
        std::cout << center(first_row_name, width);
        for (const auto& row : data)
        {
            std::ostringstream ss;
            ss << row.value_first;
            std::cout << center(ss.str(), width);
        }
        std::cout << "\n";

        // розділювач
        for (std::size_t i = 0; i <= data.size(); ++i)
            std::cout << YELLOW << std::string(width, '-');
        std::cout << RESET << "\n";

        // другий рядок
        std::cout << center(second_row_name, width);
        for (const auto& row : data)
        {
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(6) << row.value_second;
            std::cout << center(ss.str(), width);
        }

        std::cout << "\n\n";
    }
}

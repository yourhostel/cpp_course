// 2026-03-08-probability-combination/Validator.h
//
// Created by tysser on 08.03.26.
//


#ifndef CPP_COURSE_VALIDATOR_H
#define CPP_COURSE_VALIDATOR_H
#include <concepts>
#include <vector>

template<typename T>
concept IntegerType = std::integral<T>;

template<typename T>
concept CountType = IntegerType<T> && (!std::same_as<T, bool>);

template<CountType T>
/*
Повертає:
true якщо всі умови коректності виконані
false якщо знайдено хоча б одну помилку
*/
class Validator
{
public:
    static bool validate(
        // Загальна кількість об'єктів у сукупності N.
        T total_count,
        // Кількість типів об'єктів k.
        T type_count,
        // Масив кількостей об'єктів кожного типу N_i.
        // Розмір масиву повинен дорівнювати type_count.
        const std::vector<T>& type_sizes,
        // Кількість об'єктів, які вибираються із сукупності m.
        T sample_count,
        // Масив кількостей вибраних об'єктів кожного типу x_i.
        // Розмір масиву повинен дорівнювати type_count.
        const std::vector<T>& selected_counts
    );

private:
    static bool validate_total_count(T total_count);
    static bool validate_type_count(T type_count);
    static bool validate_type_sizes_count(T type_count, const std::vector<T>& type_sizes);
    static bool validate_selected_counts_count(T type_count, const std::vector<T>& selected_counts);
    static bool validate_sample_count(T total_count, T sample_count);
    static bool validate_type_sizes_non_negative(const std::vector<T>& type_sizes);
    static bool validate_type_sizes_sum(T total_count, const std::vector<T>& type_sizes);
    static bool validate_selected_counts_non_negative(const std::vector<T>& selected_counts);
    static bool validate_selected_not_greater_than_type_sizes(
        const std::vector<T>& type_sizes,
        const std::vector<T>& selected_counts
    );
    static bool validate_selected_counts_sum(T sample_count, const std::vector<T>& selected_counts);
};

#include "Validator.tpp"

#endif //CPP_COURSE_VALIDATOR_H
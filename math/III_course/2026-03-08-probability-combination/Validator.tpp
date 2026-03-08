// 2026-03-08-probability-combination/validator.tpp
//
// Created by tysser on 08.03.26.
//

#ifndef VALIDATOR_TPP
#define VALIDATOR_TPP

#include <cstddef>
#include <iostream>

template<CountType T>
bool Validator<T>::validate(
    T total_count,
    T type_count,
    const std::vector<T>& type_sizes,
    T sample_count,
    const std::vector<T>& selected_counts
)
{
    bool ok = true;

    if (!validate_total_count(total_count))
    {
        ok = false;
    }

    if (!validate_type_count(type_count))
    {
        ok = false;
    }

    if (!validate_type_sizes_count(type_count, type_sizes))
    {
        ok = false;
    }

    if (!validate_selected_counts_count(type_count, selected_counts))
    {
        ok = false;
    }

    if (!validate_sample_count(total_count, sample_count))
    {
        ok = false;
    }

    if (!validate_type_sizes_non_negative(type_sizes))
    {
        ok = false;
    }

    if (!validate_type_sizes_sum(total_count, type_sizes))
    {
        ok = false;
    }

    if (!validate_selected_counts_non_negative(selected_counts))
    {
        ok = false;
    }

    if (!validate_selected_not_greater_than_type_sizes(type_sizes, selected_counts))
    {
        ok = false;
    }

    if (!validate_selected_counts_sum(sample_count, selected_counts))
    {
        ok = false;
    }

    return ok;
}

template<CountType T>
bool Validator<T>::validate_total_count(T total_count)
{
    if (total_count < 0)
    {
        std::cout << "Помилка: total_count не може бути від'ємним\n";
        return false;
    }

    return true;
}

template<CountType T>
bool Validator<T>::validate_type_count(T type_count)
{
    if (type_count < 0)
    {
        std::cout << "Помилка: type_count не може бути від'ємним\n";
        return false;
    }

    return true;
}

template<CountType T>
bool Validator<T>::validate_type_sizes_count(T type_count, const std::vector<T>& type_sizes)
{
    if (type_sizes.size() != static_cast<std::size_t>(type_count))
    {
        std::cout << "Помилка: розмір type_sizes не відповідає type_count\n";
        return false;
    }

    return true;
}

template<CountType T>
bool Validator<T>::validate_selected_counts_count(T type_count, const std::vector<T>& selected_counts)
{
    if (selected_counts.size() != static_cast<std::size_t>(type_count))
    {
        std::cout << "Помилка: розмір selected_counts не відповідає type_count\n";
        return false;
    }

    return true;
}

template<CountType T>
bool Validator<T>::validate_sample_count(T total_count, T sample_count)
{
    if (sample_count < 0 || sample_count > total_count)
    {
        std::cout << "Помилка: sample_count повинен бути в межах [0, total_count]\n";
        return false;
    }

    return true;
}

template<CountType T>
bool Validator<T>::validate_type_sizes_non_negative(const std::vector<T>& type_sizes)
{
    bool ok = true;

    for (std::size_t i = 0; i < type_sizes.size(); ++i)
    {
        if (type_sizes[i] < 0)
        {
            std::cout << "Помилка: type_sizes[" << i << "] не може бути від'ємним\n";
            ok = false;
        }
    }

    return ok;
}

template<CountType T>
bool Validator<T>::validate_type_sizes_sum(T total_count, const std::vector<T>& type_sizes)
{
    T sum_type_sizes = 0;

    for (const T value : type_sizes)
    {
        sum_type_sizes += value;
    }

    if (sum_type_sizes != total_count)
    {
        std::cout << "Помилка: сума type_sizes повинна дорівнювати total_count\n";
        return false;
    }

    return true;
}

template<CountType T>
bool Validator<T>::validate_selected_counts_non_negative(const std::vector<T>& selected_counts)
{
    bool ok = true;

    for (std::size_t i = 0; i < selected_counts.size(); ++i)
    {
        if (selected_counts[i] < 0)
        {
            std::cout << "Помилка: selected_counts[" << i << "] не може бути від'ємним\n";
            ok = false;
        }
    }

    return ok;
}

template<CountType T>
bool Validator<T>::validate_selected_not_greater_than_type_sizes(
    const std::vector<T>& type_sizes,
    const std::vector<T>& selected_counts
)
{
    bool ok = true;

    const std::size_t size =
        type_sizes.size() < selected_counts.size()
        ? type_sizes.size()
        : selected_counts.size();

    for (std::size_t i = 0; i < size; ++i)
    {
        if (selected_counts[i] > type_sizes[i])
        {
            std::cout << "Помилка: selected_counts[" << i
                      << "] не може перевищувати type_sizes[" << i << "]\n";
            ok = false;
        }
    }

    return ok;
}

template<CountType T>
bool Validator<T>::validate_selected_counts_sum(T sample_count, const std::vector<T>& selected_counts)
{
    T sum_selected_counts = 0;

    for (const T value : selected_counts)
    {
        sum_selected_counts += value;
    }

    if (sum_selected_counts != sample_count)
    {
        std::cout << "Помилка: сума selected_counts повинна дорівнювати sample_count\n";
        return false;
    }

    return true;
}

#endif
//
// Created by tysser on 09.04.26.
//

#pragma once
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
#include "Function.h"

// ======================================================
// Конструктори та деструктор
// ======================================================

template <typename T>
Function<T>::Function()
    : x_values_(nullptr),
      y_values_(nullptr),
      size_(0),
      y_column_(1)
{
}

template <typename T>
Function<T>::Function(const std::size_t size, const int y_column)
    : x_values_(nullptr),
      y_values_(nullptr),
      size_(0),
      y_column_(y_column)
{
    resize_storage(size);
}

template <typename T>
Function<T>::~Function()
{
    free_memory();
}

// ======================================================
// Гетери стану обєкта
// ======================================================

template <typename T>
std::size_t Function<T>::get_size() const
{
    return size_;
}

template <typename T>
int Function<T>::get_y_column() const
{
    return y_column_;
}

// ======================================================
// Керування внутрішнім сховищем
// ======================================================

template <typename T>
void Function<T>::resize_storage(const std::size_t new_size)
{
    free_memory();

    if (new_size == 0) return;

    x_values_ = new T[new_size];
    y_values_ = new T[new_size];
    size_ = new_size;
}

template <typename T>
void Function<T>::free_memory()
{
    delete[] x_values_;
    delete[] y_values_;

    x_values_ = nullptr;
    y_values_ = nullptr;
    size_ = 0;
}

template <typename T>
void Function<T>::set_point(std::size_t index, T x, T y)
{
    if (index >= size_) return;

    x_values_[index] = x;
    y_values_[index] = y;
}

// ======================================================
// Потокове введення і виведення
// ======================================================

template <typename T>
void Function<T>::read_from_stream(std::istream& in)
{
    if (!in || size_ == 0) return;

    T x{}; T y1{}; T y2{};

    std::size_t read_count = 0;

    for (; read_count < size_; ++read_count)
    {
        if (!(in >> x >> y1 >> y2)) break;

        set_point(read_count, x, (y_column_ == 1) ? y1 : y2);
    }

    size_ = read_count;
}

template <typename T>
void Function<T>::write_to_stream(std::ostream& out) const
{
    if (!out || size_ == 0) return;

    draw_ascii_graph(out);
}

// ======================================================
// Форматне перетворення файлу
// ======================================================

template <typename T>
void Function<T>::convert_file_format(
    const std::string& input_path,
    const std::string& output_path
)
{
    std::ifstream in(input_path);
    std::ofstream out(output_path);

    if (!in || !out) return;

    tab_separated_fixed(in, out);
}

template <typename T>
void Function<T>::tab_separated_fixed(
    std::istream& in,
    std::ostream& out
)
{
    T x{}; T y1{}; T y2{};

    out << std::fixed << std::setprecision(3) << std::showpos;

    while (in >> x >> y1 >> y2)
    {
        out << std::setw(10) << x << '\t'
            << std::setw(10) << y1 << '\t'
            << std::setw(10) << y2 << '\n';
    }
}

// ======================================================
// Методи відображення
// ======================================================

template <typename T>
std::string Function<T>::build_row(const std::size_t row, T y_min, T y_max) const
{
    std::string line(size_ * HORIZONTAL_SCALE, ' ');

    std::vector<std::size_t> positions(size_ * HORIZONTAL_SCALE);
    std::iota(positions.begin(), positions.end(), 0);

    std::transform(
        positions.begin(),
        positions.end(),
       line.begin(),
    [this, row, y_min, y_max](const std::size_t pos)
        {
            if (pos % HORIZONTAL_SCALE != 0) return ' ';

            const std::size_t i = pos / HORIZONTAL_SCALE;
            const T y = y_values_[i];

            if (y_max == y_min) return GRAPH_SYMBOL;

            const auto y_row = static_cast<std::size_t>(
                std::round((y_max - y) / (y_max - y_min) * (GRAPH_HEIGHT - 1))
            );

            return (y_row == row) ? GRAPH_SYMBOL : ' ';
        }
    );

    return line;
}

template <typename T>
void Function<T>::draw_ascii_graph(std::ostream& out) const
{
    if (!out || size_ == 0) return;

    auto [min_it, max_it] = std::minmax_element(y_values_, y_values_ + size_);

    const T y_min = *min_it;
    const T y_max = *max_it;

    out << std::fixed << std::setprecision(LABEL_WIDTH - 5);

    for (std::size_t row = 0; row < GRAPH_HEIGHT; ++row)
    {
        const T level = y_max - (y_max - y_min) * row / (GRAPH_HEIGHT - 1);

        out << std::setw(LABEL_WIDTH) << level << " |"
            << build_row(row, y_min, y_max)
            << '\n';
    }

    print_axis_line(out, size_ * HORIZONTAL_SCALE);
}

template <typename T>
void Function<T>::print_min_max(std::ostream& out) const
{
    if (!out || size_ == 0) return;

    auto [min_it, max_it] = std::minmax_element(y_values_, y_values_ + size_);

    T y_min = *min_it;
    T y_max = *max_it;

    out << "min = " << y_min << '\n';
    out << "max = " << y_max << '\n';
}

template <typename T>
void Function<T>::print_axis_line(std::ostream& out, const std::size_t width) const
{
    out << std::string(LABEL_WIDTH + 1, ' ') << '+'
        << std::string(width, '-') << '\n';

    out << std::string(LABEL_WIDTH + 1, ' ') << "x ->\n";
}

template <typename T>
void Function<T>::print_y_scale(std::ostream& out, T y_min, T y_max) const
{
    out << "y_max = " << y_max << '\n';
    out << "y_min = " << y_min << '\n';
}
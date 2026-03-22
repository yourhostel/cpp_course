//
// Created by tysser on 22.03.26.
//

#include "Matrix.h"
#include <iostream>

Matrix::Matrix(const int size) : Chislo(size)
{
    if (size > max_size)
    {
        throw std::invalid_argument("перевищено максимальний розмір");
    }
}

Matrix::~Matrix() = default;

void Matrix::input()
{
    const long value_ = get_value();
    for (long i = 0; i < value_; ++i)
    {
        std::cin >> data_[i];
        if (data_[i] < 0)
        {
            throw std::invalid_argument("елементи мають бути невід'ємні");
        }
    }
}

//
// Created by tysser on 25.03.26.
//

#pragma once

#include <cstddef>

template<typename T>
class SparseItem
{
private:
    std::size_t logical_index_;
    T value_;

public:
    SparseItem();
    SparseItem(std::size_t logical_index, const T& value);

    [[nodiscard]] std::size_t logical_index() const;

    T& value();
    const T& value() const;
};

#include "SparseItem.tpp"
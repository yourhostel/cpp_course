//
// Created by tysser on 25.03.26.
//

#pragma once

#include <cstddef>
#include <list>
#include "SparseItem.h"

template<typename T>
class SparseArray
{
private:
    std::size_t logical_size_;
    std::list<SparseItem<T>> data_;

    typename std::list<SparseItem<T>>::iterator find_item(std::size_t index);
    typename std::list<SparseItem<T>>::const_iterator find_item(std::size_t index) const;

public:
    SparseArray();
    explicit SparseArray(std::size_t logical_size);

    SparseArray(const SparseArray<T>& other);
    SparseArray<T>& operator=(const SparseArray<T>& other);

    [[nodiscard]] std::size_t logical_size() const;
    [[nodiscard]] std::size_t physical_size() const;

    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;

    void show() const;
};

#include "SparseArray.tpp"
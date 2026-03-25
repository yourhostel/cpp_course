//
// Created by tysser on 25.03.26.
//

#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <list>
#include "SparseItem.h"

template<typename T>
typename std::list<SparseItem<T>>::iterator SparseArray<T>::find_item(std::size_t index)
{
    return std::find_if(data_.begin(), data_.end(),
        [index](const SparseItem<T>& item)
        {
            return item.logical_index() == index;
        });
}

template<typename T>
typename std::list<SparseItem<T>>::const_iterator SparseArray<T>::find_item(std::size_t index) const
{
    return std::find_if(data_.cbegin(), data_.cend(),
        [index](const SparseItem<T>& item)
        {
            return item.logical_index() == index;
        });
}

template<typename T>
SparseArray<T>::SparseArray() : logical_size_(0)
{
}

template<typename T>
SparseArray<T>::SparseArray(const std::size_t logical_size) : logical_size_(logical_size)
{
}

template<typename T>
SparseArray<T>::SparseArray(const SparseArray<T>& other) = default;

template<typename T>
SparseArray<T>& SparseArray<T>::operator=(const SparseArray<T>& other) = default;

template<typename T>
std::size_t SparseArray<T>::logical_size() const
{
    return logical_size_;
}

template<typename T>
std::size_t SparseArray<T>::physical_size() const
{
    return data_.size();
}

template<typename T>
T& SparseArray<T>::operator[](const std::size_t index)
{
    if (index >= logical_size_)
    {
        throw std::out_of_range("Індекс виходить за межі логічного масиву");
    }

    auto it = find_item(index);

    if (it != data_.end())
    {
        return it->value();
    }

    data_.push_back(SparseItem<T>(index, T()));
    return data_.back().value();
}

template<typename T>
void SparseArray<T>::show() const
{
    std::cout << "Логічний розмір: " << logical_size_ << '\n';

    std::for_each(data_.cbegin(), data_.cend(),
        [](const SparseItem<T>& item)
        {
            std::cout << "index = " << item.logical_index()
                      << ", value = " << item.value() << '\n';
        });
}

template<typename T>
const T& SparseArray<T>::at(const std::size_t index) const
{
    if (index >= logical_size_)
    {
        throw std::out_of_range("Індекс виходить за межі логічного масиву");
    }

    auto it = find_item(index);
    if (it == data_.cend())
    {
        throw std::runtime_error("Елемент не знайдено");
    }

    return it->value();
}
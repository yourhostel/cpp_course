//
// Created by tysser on 25.03.26.
//

#pragma once

template<typename T>
SparseItem<T>::SparseItem() : logical_index_(0), value_(T())
{
}

template<typename T>
SparseItem<T>::SparseItem(const std::size_t logical_index, const T& value)
    : logical_index_(logical_index), value_(value)
{
}

template<typename T>
std::size_t SparseItem<T>::logical_index() const
{
    return logical_index_;
}

template<typename T>
T& SparseItem<T>::value()
{
    return value_;
}

template<typename T>
const T& SparseItem<T>::value() const
{
    return value_;
}

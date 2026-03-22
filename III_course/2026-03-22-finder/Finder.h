//
// Created by tysser on 22.03.26.
//

#pragma once
#include <utility>
#include <vector>
#include <algorithm>

template<typename T>
class Finder {

    std::vector<T> data_;

public:
    explicit Finder(std::vector<T> data) : data_(std::move(data)) {}

    auto find_first(const T& key) const;

    template<typename Predicate>
    auto find_first_if(Predicate pred) const;

    template<typename Predicate>
    std::vector<T> find_all_if(Predicate pred) const ;

    auto begin() const;
    auto end() const;
};

#include "Finder.tpp"

//
// Created by tysser on 22.03.26.
//

#pragma once
#include "Chislo.h"
#include <array>

class Matrix : public Chislo
{
public:
    static constexpr int max_size = 100;
    std::array<long, max_size> data_{};


    explicit Matrix(int size);
    ~Matrix() override;
    void input();
};
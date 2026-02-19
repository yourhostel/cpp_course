//
// Created by tysser on 19.02.26.
//

#ifndef CPP_COURSE_FASTPOWERSTRATEGY_H
#define CPP_COURSE_FASTPOWERSTRATEGY_H

#pragma once
#include "PowerStrategy.h"

class FastPowerStrategy : public PowerStrategy
{
public:
    [[nodiscard]] double power(double n, int p) const override;
    [[nodiscard]] double power_recursive_core(double base, int absP) const override;
    [[nodiscard]] double power_recursive(double n, int p) const override;
};

#endif //CPP_COURSE_FASTPOWERSTRATEGY_H
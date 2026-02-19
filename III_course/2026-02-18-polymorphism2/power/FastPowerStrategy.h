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
    /*
    Ітеративне бінарне піднесення до степеня.

    Використовує двійкове розкладання показника.
    Кожної ітерації показник ділиться на 2,
    основа зводиться в квадрат.
    Часова складність O(log |p|).
    */
    [[nodiscard]] double power(double n, int p) const override;

    /*
    Обчислює степінь через рекурсивний виклик
    з показником absP / 2.
    Якщо показник парний повертає half * half.
    Якщо непарний повертає base * half * half.
    Глибина рекурсії O(log |p|).
    */
    [[nodiscard]] double power_recursive_core(double base, int absP) const override;

    /*
    Рекурсивне бінарне піднесення до степеня
    з попередньою валідацією та нормалізацією знака
    делегує обчислення в power_recursive_core.
    */
    [[nodiscard]] double power_recursive(double n, int p) const override;
};

#endif //CPP_COURSE_FASTPOWERSTRATEGY_H
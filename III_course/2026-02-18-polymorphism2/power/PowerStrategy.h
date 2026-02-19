//
// Created by tysser on 19.02.26.
//

#ifndef CPP_COURSE_POWERSTRATEGY_H
#define CPP_COURSE_POWERSTRATEGY_H


#pragma once

class PowerStrategy
{
public:
    /*
    Валідація вхідних параметрів перед обчисленням степеня.
    Гарантує коректність вхідних даних і запобігає невизначеній поведінці.

    Перевірки:
    1. Заборона 0 у від’ємному степені, бо це означає ділення на нуль.
    2. Заборона INT_MIN через неможливість взяти модуль.
    */
    void validate_power(double n, int p) const;

    /*
    Нормалізація знака показника степеня.

    Після виконання:
    absP >= 0
    base дорівнює n або 1/n
    */
    void normalize_sign(double n, int p, double& base, int& absP) const;

    /*
    Ітеративне лінійне піднесення до степеня.

    Реалізація:
    Послідовне множення основи absP разів.
    Часова складність O(|p|).
    */
    [[nodiscard]] virtual double power(double n, int p) const;

    /*
    Перевантаження для піднесення до квадрату.
    Еквівалентно power(n, 2).
    */
    [[nodiscard]] double power(double n) const;

    /*
    Допоміжна рекурсивна функція для лінійного піднесення.

    Реалізація:
    Рекурсивне множення base на себе absP разів.
    Глибина рекурсії O(|p|).
    */
    [[nodiscard]] virtual double power_recursive_core(double base, int absP) const;

    /*
    Рекурсивне лінійне піднесення до степеня з попередньою
    валідацією та нормалізацією.

    Часова складність O(|p|).
    */
    [[nodiscard]] virtual double power_recursive(double n, int p) const;

    /*
    Перевантаження для рекурсивного піднесення до квадрату.
    Еквівалентно power_recursive(n, 2).
    */
    [[nodiscard]] double power_recursive(double n) const;

    virtual ~PowerStrategy() = default;
};

#endif //CPP_COURSE_POWERSTRATEGY_H
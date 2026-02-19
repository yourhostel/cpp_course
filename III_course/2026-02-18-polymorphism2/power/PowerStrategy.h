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
    Призначення:
    Валідація вхідних параметрів перед обчисленням степеня.
    Гарантує, що подальша нормалізація та обчислення не приведуть
    до невизначеної поведінки або математично некоректного результату.

    Параметри:
    n  – основа степеня
    p  – показник степеня типу int

    Перевірки:
    1. Забороняє 0 у від’ємному степені, бо це означає ділення на нуль.
    2. Забороняє INT_MIN, бо його модуль не представимий у типі int.
    */
    void validate_power(double n, int p) const;

    /*
    Приводить задачу піднесення до степеня до стандартної форми,
    у якій показник завжди невід’ємний.

    Після виконання:
    absP >= 0
    base дорівнює або n, або 1/n

    Параметри:
    n     – початкова основа
    p     – початковий показник
    base  – вихідна змінна для нормалізованої основи
    absP  – вихідна змінна для модуля показника
    */
    void normalize_sign(double n, int p, double& base, int& absP) const;

    [[nodiscard]] virtual double power(double n, int p) const;
    [[nodiscard]] double power(double n) const;
    [[nodiscard]] virtual double power_recursive_core(double base, int absP) const;
    [[nodiscard]] virtual double power_recursive(double n, int p) const;
    [[nodiscard]] double power_recursive(double n) const;

    virtual ~PowerStrategy() = default;
};

#endif //CPP_COURSE_POWERSTRATEGY_H
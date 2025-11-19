//
// Created by tysser on 19.11.25.
//

#ifndef CPP_COURSE_CALC_H
#define CPP_COURSE_CALC_H
// III_course/2025-11-18-topic-14/Calc.cpp

// Арифметичний калькулятор
struct Calc {

    double _a;   // акумулятор
    double _x;   // значення

    explicit Calc(const double a = 0, const double x = 0) : _a(a), _x(x) {}

    // a = a + x
    double add()       { return _a += _x; }

    // a = a - x
    double sub()       { return _a -= _x; }

    // a = a * x
    double mul()       { return _a *= _x; }

    // a = a / x
    double divide()    { return _a /= _x; }

    // а = x (записати нове значення)
    double load()      { return _a = _x; }

    // скинути регістри
    void clear()       { _a = 0; _x = 0; }
};

#endif //CPP_COURSE_CALC_H
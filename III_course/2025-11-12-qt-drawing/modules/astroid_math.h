//
// Created by tysser on 13.11.25.
//

// III_course/2025-11-12-qt-drawing/modules/astroid_math.h
#ifndef ASTROID_MATH_H
#define ASTROID_MATH_H

// III_course/modules/analog_clock.h
#include <cmath>
#include <QPoint>

// радіус астроїди
constexpr int ASTROID_A = 100;

// кількість точок, з яких складається фігура
constexpr int ASTROID_STEPS = 180;

// пі, наближене значення
constexpr float Pi = 3.141593;

namespace AstroidMath {

    // обчислює одну точку астроїди за параметром i
    // формула x = a * cos^3(t), y = a * sin^3(t)
    // t = 2*pi*i/ASTROID_STEPS
    inline QPoint computePixel(const int i, int a)
    {
        const int px = static_cast<int>(a * pow(std::cos(2 * Pi * i / ASTROID_STEPS), 3));
        const int py = static_cast<int>(a * pow(std::sin(2 * Pi * i / ASTROID_STEPS), 3));
        return {px, py};
    }

}

#endif //ASTROID_MATH_H

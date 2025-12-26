//
// Created by tysser on 26.12.25.
//

// cpp_course/III_course/2025-12-26-semester-assessments/classes/SolidOfRevolution.cpp
#include "SolidOfRevolution.h"
#include <numbers>
#include <iostream>

Cone::Cone(const double radius, const double height) : radius_(radius), height_(height) {}

double Cone::volume() const
{
    return std::numbers::pi * radius_ * radius_ * height_ / 3.0;
}

void Cone::printInfo() const
{
    std::cout << "Конус: r=" << radius_
          << ", h=" << height_
          << ", V=" << volume() << '\n';
}

Cylinder::Cylinder(const double radius, const double height) : radius_(radius), height_(height) {}

double Cylinder::volume() const
{
    return std::numbers::pi * radius_ * radius_ * height_;
}

void Cylinder::printInfo() const
{
    std::cout << "Циліндр: r=" << radius_
              << ", h=" << height_
              << ", V=" << volume() << '\n';
}


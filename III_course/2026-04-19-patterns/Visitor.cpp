//
// Created by tysser on 19.04.26.
//

#include "Visitor.h"

#include <iostream>

Circle::Circle(const int radius) : radius_(radius) {}

int Circle::get_radius() const
{
    return radius_;
}

void Circle::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

Rectangle::Rectangle(const int width, const int height)
    : width_(width), height_(height) {}

int Rectangle::get_width() const
{
    return width_;
}

int Rectangle::get_height() const
{
    return height_;
}

void Rectangle::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void PrintVisitor::visit(Circle& circle)
{
    std::cout << "Circle: radius = " << circle.get_radius() << std::endl;
}

void PrintVisitor::visit(Rectangle& rectangle)
{
    std::cout << "Rectangle: width = " << rectangle.get_width()
              << ", height = " << rectangle.get_height() << std::endl;
}

//
// Created by tysser on 26.12.25.
//

// cpp_course/III_course/2025-12-26-semester-assessments/classes/University.cpp
#include "University.h"

University::University(std::string name) : name_(std::move(name)) {}

void University::printInfo() const
{
    std::cout << "Університет: " << name_ << '\n';
}

Faculty::Faculty(std::string name) : University(std::move(name)) {}

void Faculty::printInfo() const
{
    std::cout << "Факультет: " << name_ << '\n';
}

Department::Department(std::string name)
    : University(std::move(name)) {}

void Department::printInfo() const
{
    std::cout << "Кафедра: " << name_ << '\n';
}
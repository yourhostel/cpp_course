//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Position.h
#ifndef CPP_COURSE_POSITION_H
#define CPP_COURSE_POSITION_H

#include <string>
#include <iostream>
#include "Accountant.h"

using std::string;
using std::cout;
using std::endl;

class Employee;
class Accountant;

class Position {

    friend void Accountant::payroll(const Employee&) const;

    string _name;
    unsigned int _salary;

    [[nodiscard]] unsigned int getSalary() const;

public:
    Position(const Position&) = delete;
    Position& operator=(const Position&) = delete;

    Position(const char*, unsigned int);

    ~Position();
    [[nodiscard]] const string& getPositionName() const;
};

#endif //CPP_COURSE_POSITION_H
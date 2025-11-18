//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Position.cpp
#include "Position.h"
#include "Accountant.h"

Position::Position(const char* name, const unsigned int salary)
    : _name(name), _salary(salary)
{
    cout << "A Position " << _name << "(" << _salary << ") was created" << endl;
}

Position::~Position()
{
    cout << "A Position " << _name << " was deleted" << endl;
}

const string& Position::getPositionName() const
{
    return _name;
}

unsigned int Position::getSalary() const
{
    return _salary;
}

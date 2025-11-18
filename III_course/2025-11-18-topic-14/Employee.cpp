//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Employee.cpp
#include "Employee.h"
#include "Person.h"
#include "Position.h"

// Конструктор - приватний, викликає лише Employer
Employee::Employee(const Person& who, const Position& what)
    : _who(who), _what(what)
{
    cout << "Employee " << _who.getName()
         << " takes a position " << _what.getPositionName() << endl;
}

// Деструктор
Employee::~Employee()
{
    cout << "Employee " << _who.getName()
         << " fired from " << _what.getPositionName() << endl;
}

// Селектори
const Person& Employee::who() const { return _who; }
const Position& Employee::what() const { return _what; }


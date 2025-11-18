//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Accountant.h
#ifndef CPP_COURSE_ACCOUNTANT_H
#define CPP_COURSE_ACCOUNTANT_H

#include <iostream>
using std::cout;
using std::endl;

#include "Person.h"
#include "Employer.h"

// Клас бухгалтерів
class Accountant {
    friend class Employer;
    friend class Employee;
    friend class Position;
public:
    void payroll() const;
    ~Accountant();
    Accountant(const Accountant&) = delete;
    Accountant& operator=(const Accountant&) = delete;

private:
    Accountant(const Employer&, const Person&);

    void payroll(const Employee&) const;

    const Employer& _myEmployer;
    const Person& _who;
};

#endif //CPP_COURSE_ACCOUNTANT_H
//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Employee.h
#ifndef CPP_COURSE_EMPLOYEE_H
#define CPP_COURSE_EMPLOYEE_H

#include <iostream>
using std::cout;
using std::endl;

class Person;
class Position;
class Employer;

// Службовець як одиниця штатного розпису
class Employee {

    friend class Employer;    // Лише працедавець може створювати Employee

private:
    const Person& _who;       // Особа, що займає посаду (посилання!)
    const Position& _what;    // Посада (посилання!)

    // Закритий конструктор - створювати можна лише через Employer
    Employee(const Person& who, const Position& what);

    ~Employee();              // Звільнення працівника (повідомлення)

public:
    // Заборонені копіювання
    Employee(const Employee&) = delete;
    Employee& operator=(const Employee&) = delete;

    [[nodiscard]] const Person& who() const;
    [[nodiscard]] const Position& what() const;
};


#endif //CPP_COURSE_EMPLOYEE_H
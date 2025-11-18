//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Employer.h
#ifndef CPP_COURSE_EMPLOYER_H
#define CPP_COURSE_EMPLOYER_H

#include <iostream>

using std::cout;
using std::endl;

class Person;
class Position;
class Employee;
class Accountant;

// Клас працедавця
class Employer {

    friend class Accountant;

private:
    // Структура робочих місць
    struct Staff {
        Employee* _pemployee; // вказівник на працівника
        bool _free;           // чи вакантне місце
    };

    size_t _volume;         // кількість посад
    Staff* _office;         // масив посад
    Accountant* _accountant{};// бухгалтер
    const Person& _me;      // особа працедавця

public:
    // Забороняємо копіювання
    Employer(const Employer&) = delete;
    Employer& operator=(const Employer&) = delete;

    Employer(const Person& boss,
             size_t volume,
             const Person& accountant);

    ~Employer();

    [[nodiscard]] size_t volume() const { return _volume; }

    void hire(const Person&, const Position&) const; // наймання
    void fire(size_t index) const;                   // звільнення
    void pay() const;                          // делегує бухгалтеру
};

#endif //CPP_COURSE_EMPLOYER_H
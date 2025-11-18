//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Accountant.cpp
#include "Accountant.h"
#include "Employer.h"
#include "Employee.h"
#include "Position.h"
#include "Person.h"

// Конструктор: наймання бухгалтера працедавцем
Accountant::Accountant(const Employer& employer,
                       const Person& accountant)
    : _myEmployer(employer), _who(accountant)
{
    cout << "Accountant " << _who.getName() << " is hired" << endl;
}

// Деструктор
Accountant::~Accountant()
{
    cout << "Accountant was deleted" << endl;
}

// Масове нарахування зарплати
void Accountant::payroll() const
{
    cout << "---Start payroll" << endl;

    for (size_t i = 0; i < _myEmployer._volume; i++)
    {
        if (!_myEmployer._office[i]._free)
        {
            payroll(*_myEmployer._office[i]._pemployee);
        }
    }

    cout << "---Stop payroll" << endl;
}

// Нарахування одному працівникові
void Accountant::payroll(const Employee& employee) const
{
    // Тільки payroll має доступ до Position::getSalary()
    cout << "Pay "
         << employee.who().getName()
         << " amount "
         << employee.what().getSalary()
         << endl;
}


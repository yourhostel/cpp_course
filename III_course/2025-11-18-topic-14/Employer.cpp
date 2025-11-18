//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Employer.cpp
#include "Employer.h"
#include "Person.h"
#include "Employee.h"
#include "Accountant.h"

// Конструктор працедавця
Employer::Employer(const Person& boss,
                   const size_t volume,
                   const Person& accountant)
    : _volume(volume),
      _office(new Staff[_volume]),
      _accountant(new Accountant(*this, accountant)),
      _me(boss)
{
    cout << "Employer " << _me.getName()
         << " with " << _volume
         << " positions was created" << endl;

    // Спочатку всі місця — вакантні
    for (size_t i = 0; i < _volume; i++) {
        _office[i]._free = true;
        _office[i]._pemployee = nullptr;
    }
}

// Деструктор працедавця
Employer::~Employer()
{
    cout << "Employer " << _me.getName()
         << " with " << _volume << " positions was deleted"
         << endl;

    // Звільняємо всіх працівників
    for (size_t i = 0; i < _volume; i++)
        if (!_office[i]._free)
            delete _office[i]._pemployee;

    delete[] _office;
    delete _accountant;
}

// Наймання працівника
void Employer::hire(const Person& person, const Position& position) const
{
    // Пошук вільної позиції
    size_t i = 0;
    while (i < _volume && !_office[i]._free)
        i++;

    if (i == _volume)
    {
        cout << "No free positions for "
             << person.getName() << endl;
        return;  // Вправа 5.4
    }

    // Створюємо працівника
    const auto p = new Employee(person, position);
    _office[i]._free = false;
    _office[i]._pemployee = p;
}

// Звільнення працівника
void Employer::fire(const size_t index) const
{
    if (index >= _volume)
        return;

    if (_office[index]._free)
        return;

    delete _office[index]._pemployee;
    _office[index]._pemployee = nullptr;
    _office[index]._free = true;
}

// Делегування платіжної відомості бухгалтеру
void Employer::pay() const
{
    _accountant->payroll();
}


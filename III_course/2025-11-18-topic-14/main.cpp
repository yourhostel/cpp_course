//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/main.cpp

#include "Person.h"
#include "Position.h"
#include "Employer.h"
#include "Employee.h"
#include "Accountant.h"
void test_task();
void access_check();

int main() {

    // access_check(); // запускаємо тест доступів
    test_task(); // запускаємо дослідницькі завдання

    return 0;
}

// Тестування завдання
void test_task()
{
    const Person boss("Boss");
    const Person w1("Worker1");
    const Person w2("Worker2");
    const Person accountant("Acc");

    const Position pos("Engineer", 1000);

    const Employer firm(boss, 1, accountant);

    firm.hire(w1, pos);  // зайняло єдину позицію
    firm.hire(w2, pos);  // тут має бути: "No free positions"
}

void access_check()
{
    const Person boss("Ivan Boss");
    const Person worker("Petro Worker");
    const Person accountant("Olena Accountant");

    const Position pos("Engineer", 1000);

    const Employer firm(boss, 1, accountant);

    firm.hire(worker, pos);

    firm.pay();

    // 1) Employee не можна створити напряму
    // Employee e(p1, pos);            // ERROR: constructor is private

    // 2) Не можна лізти до зарплати
    // cout << pos.getSalary();        // ERROR: private

    // 3) Не можна викликати payroll(Employee&)
    // Accountant a(boss, p1);         // ERROR: constructor private
    // a.payroll(e);                   // ERROR: private
}
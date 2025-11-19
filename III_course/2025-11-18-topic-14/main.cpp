//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/main.cpp

#include "Person.h"
#include "Position.h"
#include "Employer.h"
#include "Calc.h"
#include "Employee.h"
#include "Accountant.h"

void test_task_1_2();
void access_check();

//Сигнатура exe() Вправа 5.11
double exe(Calc& c, double (Calc::*op)());
void test_task_3();

int main() {

    // access_check(); // запускаємо тест доступів 5.4 / 5.5
    // test_task_1_2(); // запускаємо вправи 5.4 / 5.5
    test_task_3(); // запускаємо вправу 5.11

    return 0;
}

// Тестування завдання
void test_task_1_2()
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

//
double exe(Calc& c, double (Calc::*op)())
{
    return (c.*op)();   // виклик методу через pointer-to-member
}

void test_task_3()
{
    Calc c(10, 5); // a=10, x=5

    exe(c, &Calc::add);     // 10 + 5 = 15
    cout << c._a << endl;

    exe(c, &Calc::mul);     // 15 * 5 = 75
    cout << c._a << endl;

    c._x = 3;
    exe(c, &Calc::sub);     // 75 - 3 = 72
    cout << c._a << endl;

    c._x = 9;
    exe(c, &Calc::divide);  // 72 / 9 = 8
    cout << c._a << endl;
}
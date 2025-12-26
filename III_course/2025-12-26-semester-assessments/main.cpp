//
// Created by tysser on 26.12.25.
//

// cpp_course/III_course/2025-12-26-semester-assessments/main.cpp
#include "University.h"
#include "FindInRange.h"
#include "SolidOfRevolution.h"
#include "NumberPair.h"

#include <iostream>
#include <vector>
#include <memory>

void demoUniversityHierarchy()
{
    std::cout << "========================= 1 =========================\n\n";

    std::vector<std::unique_ptr<University>> units;

    units.push_back(std::make_unique<University>("Київський університет"));
    units.push_back(std::make_unique<Faculty>("Факультет інформатики"));
    units.push_back(std::make_unique<Department>("Кафедра програмної інженерії"));

    for (const auto& unit : units) unit->printInfo();
}

void demoSolidsOfRevolution()
{
    std::cout << "\n========================= 2 =========================\n\n";

    std::vector<std::unique_ptr<SolidOfRevolution>> figures;

    figures.push_back(std::make_unique<Cone>(3.0, 5.0));
    figures.push_back(std::make_unique<Cylinder>(2.0, 10.0));

    for (const auto& figure : figures) figure->printInfo();
}

void demoFindInRange()
{
    std::cout << "\n========================= 3 =========================\n\n";

    const std::vector<int> ints {1, 5, 10, 15, 20};
    const std::vector<double> doubles {0.5, 2.3, 4.8, 7.1};
    const std::vector<char> chars {'a', 'd', 'k', 'z'};

    const auto intsInRange = findInRange(ints, 5, 15);
    const auto doublesInRange = findInRange(doubles, 2.0, 5.0);
    const auto charsInRange = findInRange(chars, 'c', 'm');

    std::cout << "ints: ";
    for (const int v : intsInRange) std::cout << v << ' ';
    std::cout << '\n';

    std::cout << "doubles: ";
    for (const double v : doublesInRange) std::cout << v << ' ';
    std::cout << '\n';

    std::cout << "chars: ";
    for (const char v : charsInRange) std::cout << v << ' ';
    std::cout << '\n';
}

void demoNumberPair()
{
    std::cout << "\n========================= 4 =========================\n\n";

    // 1. Напряму:
    // const NumberPair<int, double> p1(10, 3.14);
    // const NumberPair<long, int> p2(100000L, 42);
    // const NumberPair<int, char> p3(65, 'A');

    // p1.print();
    // p2.print();
    // p3.print();

    // 2. Через variant:
    // Псевдонім типу(type alias). compile-time перелік можливих типів.
    // Використовується замість більш небезпечного union
    using PairVariant =
    std::variant<
        NumberPair<int, double>,
        NumberPair<long, int>,
        NumberPair<int, char>
    >;

    std::vector<PairVariant> pairs;

    // Передаємо аргументи конструктора, без створення тимчасового обьекта
    pairs.emplace_back(NumberPair{10, 3.14});
    pairs.emplace_back(NumberPair{100000L, 42});
    pairs.emplace_back(NumberPair{65, 'A'});

    for (const auto& p_variant : pairs)
 // for (std::size_t i = 0; i < pairs.size(); ++i) // приклад для звичайного циклу
    {
        // std::visit це механізм виклику коду залежно від того,
        // який тип зараз лежить у std::variant
        std::visit([](const auto& pair) {
            pair.print();
        }, p_variant);
    }
}

int main()
{
    demoUniversityHierarchy();
    demoSolidsOfRevolution();
    demoFindInRange();
    demoNumberPair();

    return 0;
}

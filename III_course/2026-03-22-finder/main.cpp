//
// Created by tysser on 22.03.26.
//

#include <iostream>
#include "Finder.h"

struct accommodation
{
    int id{};
    std::string place_code{};

    bool operator==(const accommodation& other) const
    {
        return id == other.id && place_code == other.place_code;
    }
};

void test()
{

    std::vector<accommodation> data =
    {
        {1, "A102"},
        {2, "A101"},
        {3, "B202"},
        {4, "A101"},
        {5, "C303"},
        {6, "A101"},
        {7, "C307"}
    };

    const Finder<accommodation> f(data);

    // 1. Пошук точного збігу
    const accommodation key{3, "B202"};
    auto it = f.find_first(key);

    if (it != f.end())
    {
        std::cout << "Знайдено точний збіг: " << "{ id: " << it->id << " place_code: " << it->place_code << " }\n\n";
    }


    // 2. Пошук за умовою (лямбда)
    auto it2 = f.find_first_if([](const accommodation& a)
    {
        return a.place_code == "A101";
    });

    if (it2 != f.end()) std::cout << "Перший з place_code A101: " << "{ id: " << it2->id  << " place_code: " << it2->place_code << " }\n\n";

    // 3. Пошук всіх за умовою
    auto all = f.find_all_if([](const accommodation& a)
    {
        return a.place_code == "A101";
    });

    std::cout << "Усі з place_code A101:\n\n";

    std::ranges::for_each(all, [](const accommodation& a)
    {
        std::cout << "{ id: " << a.id << " place_code: " << a.place_code << " }\n";
    });

};

int main()
{

    test();
    return 0;
};
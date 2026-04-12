//
// Created by tysser on 12.04.26.
//

#pragma once
#include <string>
#include <iostream>

struct Person
{
    int id;
    std::string name;
    int age;

    bool operator==(const Person& other) const
    {
        return id == other.id;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Person& person)
{
    os << "{ id: " << person.id
       << ", name: " << person.name
       << ", age: " << person.age << " }";
    return os;
}

//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Person.cpp
#include "Person.h"

Person::Person(const char name[]) : _name(name)
{
    cout << "A person " << _name << " was created" << endl;
}

Person::Person(const Person&)  // не реалізовувати
{
    // Порожньо - спеціально, щоб виклик копіювання зламав компонування
}

Person::~Person()
{
    cout << "A person " << _name << " was deleted" << endl;
}

const string& Person::getName() const
{
    return _name;
}

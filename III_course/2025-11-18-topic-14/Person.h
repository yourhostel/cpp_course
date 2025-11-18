//
// Created by tysser on 18.11.25.
//

// III_course/2025-11-18-topic-14/Person.h
#ifndef CPP_COURSE_PERSON_H
#define CPP_COURSE_PERSON_H

#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

// Клас осіб потенційних працівників
class Person {
private:
    string _name;

public:
    // Заборонене присвоєння
    Person& operator=(const Person&) = delete;

    explicit Person(const char []);
    // оголошений, але без реалізації
    Person(const Person&);
    ~Person();

    [[nodiscard]] const string& getName() const;
};


#endif //CPP_COURSE_PERSON_H
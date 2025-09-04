// 04_struct_person.cpp
#include <iostream>
#include <vector>
using namespace std;

struct Person {
    string surname;
    int age;

    void input() {
        cout << "Прізвище: ";
        cin >> surname;
        cout << "Вік: ";
        cin >> age;
    }

    static Person find_youngest(const vector<Person>& people) {
        Person youngest = people[0];
        for (const auto& p : people)
            if (p.age < youngest.age)
                youngest = p;
        return youngest;
    }
};

// 01_struct_student.cpp
#include <iostream>
#include <vector>
using namespace std;

struct Student {
    string surname;
    int kurs;
    string group;
    vector<int> exams;

    void input() {
        cout << "Прізвище: ";
        cin >> surname;
        cout << "Курс: ";
        cin >> kurs;
        cout << "Група: ";
        cin >> group;
        cout << "Оцінки (5 штук): ";
        exams.resize(5);
        for (int& mark : exams)
            cin >> mark;
    }

    void print() const {
        cout << "Прізвище: " << surname << "\n"
             << "Курс: " << kurs << "\n"
             << "Група: " << group << "\n"
             << "Оцінки: ";
        for (int mark : exams)
            cout << mark << " ";
        cout << endl;
    }

    void upgrade_course() {
        for (int mark : exams)
            if (mark < 60)
                return;
        kurs++;
        size_t pos = group.find('-');
        if (pos != string::npos && pos + 1 < group.size())
            group[pos + 1] = '0' + kurs;
    }
};

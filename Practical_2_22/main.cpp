// main.cpp
#include <iostream>
#include <vector>
#include "01_struct_student.cpp"
#include "02_class_complex.cpp"
#include "03_class_point.cpp"
#include "04_struct_person.cpp"

using namespace std;

int main() {
    // 01 - Студенти
    vector<Student> students(3); // масив із 3 студентів
    for (auto& s : students) {
        s.input();
        s.upgrade_course();
    }

    cout << "\nІнформація про студентів після переведення:\n";
    for (const auto& s : students) {
        s.print();
    }

    // 02 - Комплексні числа
    Complex z;
    cin >> z;
    int n;
    cout << "Введіть степінь кореня: ";
    cin >> n;
    for (int k = 0; k < n; ++k) {
        Complex r = z.root(n, k);
        cout << "Корінь #" << k << ": " << r << endl;
    }

    // 03 - Точки
    Point p1, p2;
    cout << "Введіть координати першої точки:\n";
    p1.input();
    cout << "Введіть координати другої точки:\n";
    p2.input();
    cout << "Відстань між точками: " << p1.distance_to(p2) << endl;
    cout << "Відстань першої точки до початку: " << p1.distance_to_origin() << endl;

    // 04 - Люди
    vector<Person> people(3);
    for (auto& p : people)
        p.input();
    Person youngest = Person::find_youngest(people);
    cout << "Наймолодший: " << youngest.surname << ", вік " << youngest.age << endl;

    return 0;
}

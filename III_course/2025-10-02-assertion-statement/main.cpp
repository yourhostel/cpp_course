// # III_course/2025-10-02-assertion-statement/main.cpp
#include <cassert>
#include <iostream>
#include <boost/pfr/core.hpp>
using namespace std;

void division_by_whole();

[[noreturn]] void try_catch_probe();

double divide(int a,int b);
void ask_and_divide();

void quasi_reflection();

int main() {
    // division_by_whole();
    // try_catch_probe();
    // ask_and_divide();
       quasi_reflection();

    return 0;
}

void quasi_reflection()
{
    struct Point // Працює тільки с простими агрегаторами без кастомних бойлерплейтів(сетери, гетери, конструктори тощо)
    {
        double x;
        double y;
        double z;
    };

    Point p = {5, 3, 7};

    using namespace boost::pfr;
    for_each_field(p,[](auto& f)
    {
        cout << f << ' ';
    });

    cout << "\n" //
        << "x: " << p.x //
        << "; y: " << p.y //
        << "; z: " << p.z //
        << "\n";

    for_each_field(p, [](auto& f, const size_t i)
    {
        f = f + 1;
        cout << "i = " << i //
             << "; f = " << f //
             << "\n";
    });

    cout << "\n" //
        << "x: " << p.x //
        << "; y: " << p.y //
        << "; z: " << p.z //
        << "\n";
}

// Функція для ділення
double divide(const int a, const int b) {
    if (b == 0) {
        throw runtime_error("Ділення на нуль!"); // кидаємо виключення
    }
    return static_cast<double>(a) / b;
}

// Питає користувача і ловить виключення
void ask_and_divide()
{
    int m, n;

    while (true) {
        cout << "Введи ділене (m): ";
        cin >> m;
        cout << "Введи дільник (n): ";
        cin >> n;

        try {
            const double result = divide(m, n); // чекаємо throw
            cout << "Результат = " << result << endl;
            break; // якщо успіх — виходимо з циклу
        }
        catch (const runtime_error& e) {
            cout << "Помилка: " << e.what() << endl;
            cout << "Спробуй ще раз!\n";
        }
    }
}

void division_by_whole()
{
    // Ділення націло
    int m,n;
    cout<<"give m="; cin>>m;
    cout<<"give n="; cin>>n;
    int q=0, r=m;
    // int q=1, r=m; // <- для навмисного виклику
    // Макрос перевіряє інваріант, що міститься в ньому (m==n*q+r)&&(r>=0):
    // його порушення свідчитиме про помилку в ініціалізації
    assert((m==n*q+r)&&(r>=0));

    while(r>=n) {
        q++; r-=n;
        // q--; r+=n; // <- для навмисного виклику
        // Іще раз перевіряємо інваріант: його порушення свідчить про
        // некоректність тіла циклу
        assert((m==n*q+r)&&(r>=0));
    }
    // До інваріанта додано умову закінчення циклу r<n. Тут він не може
    // порушитися, оскільки у такому разі не відбудеться виходу із циклу
    assert((m==n*q+r)&&(r>=0)&&(r<n));
    cout<<"q="<<q<<" r="<<r<<endl;
}

[[noreturn]] void try_catch_probe()
{
    try {
        for(int i=0; ;++i) // Повторюємо, доки вдається
            auto* px = new double [0x7ffffff]; // Розміщуємо 134217727 дійсних значень
    }
    catch(const bad_alloc&) {
        cout<<"Вільної пам'яті немає"<<endl;
    }
}
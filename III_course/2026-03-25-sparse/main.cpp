//
// Created by tysser on 25.03.26.
//

#include <iostream>

#include "SparseArray.h"

int main()
{
    try
    {
        std::cout << "Приклад для int\n";
        SparseArray<int> a(10);
        a[2] = 15;
        a[7] = 30;
        a[2] = 99;
        a.show();

        std::cout << "\nПриклад для float\n";
        SparseArray<float> b(8);
        b[1] = 3.14f;
        b[5] = 2.71f;
        b.show();

        std::cout << "\nПриклад для double\n";
        SparseArray<double> c(12);
        c[0] = 1.234;
        c[11] = 9.876;
        c.show();

        std::cout << "\nПриклад для std::string\n";
        SparseArray<std::string> d(6);
        d[3] = "hello";
        d[5] = "world";
        d.show();

        std::cout << "\nПеревірка конструктора копіювання\n";
        const SparseArray<int> copy_array(a);
        copy_array.show();

        std::cout << "\nПеревірка операції присвоєння\n";
        const SparseArray<int> assigned_array = a;
        assigned_array.show();

        std::cout << "\nДоступ до конкретного елемента\n";
        std::cout << "a[2] = " << a[2] << '\n';
        std::cout << "a[4] до присвоєння створюється автоматично\n";
        std::cout << "a[4] = " << a[4] << '\n';
        a.show();
    }
    catch (const std::exception& e)
    {
        std::cout << "Помилка: " << e.what() << '\n';
    }

    catch(...)
    {
        // оброблення будь якого винятку
    }
    return 0;
}


//
// Created by tysser on 22.03.26.
//

#include <complex>
#include <iostream>
#include "Chislo.h"
#include "Matrix.h"

template <typename M, typename  C>
void print_type_factorial(M matrix, C chislo)
{
    for (long i = 0; i < matrix->get_value(); ++i)
    {
        const long x = matrix->data_[i];

        std::cout << "  " << x << "!\n";

        std::cout << "\033[32m" << "  iterative: "
          << chislo->factorial(x) << "\033[0m" << '\n';

        std::cout << "\033[33m" << "  recursive: "
                  << chislo->factorial(x, factorial_type::recursive) << "\033[0m" << '\n';

        std::cout << "\033[34m" << "  stl: "
                  << chislo->factorial(x, factorial_type::stl) << "\033[0m" << '\n';

        std::cout << "\033[35m" << "  gamma: "
                  << chislo->factorial(x, factorial_type::gamma) << "\033[0m" << '\n';
        std::cout << std::string(80, '-') << '\n';
    }
}

void run()
{
    int size;
    std::cout << "Введіть розмір масиву: ";
    std::cin >> size;
    std::cout << "Введіть обчислювальні елементи: ";

    Matrix* matrix = new Matrix(size);
    matrix->input(); // Метод з Matrix

    Chislo* chislo = matrix; // Тепер доступні методи з Chislo

    std::cout << "Масив:\n";
    for (long i = 0; i < matrix->get_value(); ++i) std::cout << matrix->data_[i] << " ";

    std::cout << "\nФакторіали елементів масиву:\n";
    print_type_factorial(matrix, chislo);

    delete chislo;
}

template <typename F>
void try_run(F f)
{
    try
    {
       f();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main()
{
    try_run(run);

    return 0;
}

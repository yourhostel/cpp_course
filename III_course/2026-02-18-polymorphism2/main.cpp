#include <iostream>
#include "PowerStrategy.h"
#include "FastPowerStrategy.h"

struct Box
{
    double base;
    int power;
};

Box prompt()
{
    Box b;

    std::cout << "Enter base: ";
    std::cin >> b.base;

    std::cout << "Enter power: ";
    std::cin >> b.power;

    return b;
}

int main()
{
    Box b = prompt();

    PowerStrategy baseStrategy;
    FastPowerStrategy fastStrategy;

    PowerStrategy* base = &baseStrategy;
    PowerStrategy* fast = &fastStrategy;

    try
    {
        // base
        std::cout << base->power(b.base, b.power) << std::endl;
        std::cout << base->power(b.base) << std::endl;
        std::cout << base->power_recursive(b.base, b.power) << std::endl;
        std::cout << base->power_recursive(b.base) << std::endl;

        // fast
        std::cout << fast->power(b.base, b.power) << std::endl;
        std::cout << fast->power(b.base) << std::endl;
        std::cout << fast->power_recursive(b.base, b.power) << std::endl;
        std::cout << fast->power(b.base) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}

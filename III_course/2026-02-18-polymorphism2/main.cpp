#include <iostream>
#include "PowerStrategy.h"
#include "FastPowerStrategy.h"

// ================== Testing for task1 ==================
struct Box
{
    double base;
    int power;
};

Box prompt()
{
    Box b{};

    std::cout << "Enter base: ";
    std::cin >> b.base;

    std::cout << "Enter power: ";
    std::cin >> b.power;

    return b;
}

void test1()
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
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// ================== Testing for task2 ==================
void zeroSmaller(int& a, int& b)
{
    if(a < b)
        a = 0;
    else if(b < a)
        b = 0;
}

void test2()
{
    std::pair<int,int> cases[] =
    {
        {5, 10},
        {10, 5},
        {7, 7}
    };

    for(size_t i = 0; i < std::size(cases); ++i)
    {
        int arg1 = cases[i].first;
        int arg2 = cases[i].second;

        std::cout << std::string(21, '=') << ' '
                  << i + 1 << ' '
                  << std::string(21, '=') << "\n\n";

        std::cout << "Before: arg1 = " << arg1
                  << ", arg2 = " << arg2 << '\n';

        zeroSmaller(arg1, arg2);

        std::cout << "After:  arg1 = " << arg1
                  << ", arg2 = " << arg2 << "\n\n";
    }
}

// ================== Testing for task3 ==================
class Distance
{
public:
    double meters;

    bool operator>(const Distance& other) const
    {
        return meters > other.meters;
    }
};

Distance maxDistance(const Distance& d1, const Distance& d2)
{
    return (d1 > d2) ? d1 : d2;
}

void test3()
{
    Distance d1{10.5};
    Distance d2{7.2};

    Distance result = maxDistance(d1, d2);

    std::cout << result.meters << std::endl;  // очікуємо 10.5
}

int main()
{

    //test1();
    //test2();
    test3();


    return 0;
}

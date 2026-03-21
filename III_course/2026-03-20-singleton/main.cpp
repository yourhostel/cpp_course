//
// Created by tysser on 20.03.26.
//

#include <cassert>
#include <iostream>

class singleton
{
public:
    static singleton& instance()
    {
        static singleton instance;
        return instance;
    }

    int value = 0;

private:
    singleton() = default;

    singleton(const singleton&) = delete;
    singleton& operator=(const singleton&) = delete;
};

int main()
{
    singleton& s1 = singleton::instance();
    singleton& s2 = singleton::instance();

    assert(&s1 == &s2);

    if(&s1 == &s2)
        std::cout << "один і той самий екземпляр\n";
    else
        std::cout << "різні екземпляри\n";

    s1.value = 42;

    if(s2.value == 42)
        std::cout << "стан спільний\n";
    else
        std::cout << "стан не спільний\n";


    return 0;
}
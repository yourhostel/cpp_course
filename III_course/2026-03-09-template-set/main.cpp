#include <iomanip>
#include <iostream>
#include <ostream>
#include <random>

#include "Set.h"

template<typename T>
T typed_random_value(std::mt19937& gen, T min_value, T max_value, int scale = 1);

template<typename T>
Set<T> random_set(int min_size, int max_size, T min_value, T max_value, int scale = 1);

template<typename T>
void show_generated(const Set<T>& a, const Set<T>& b);

template<typename T>
void show_operations(const Set<T>& c, const Set<T>& d, const Set<T>& e);

template<typename T>
void show_contains(const Set<T>& b, const T& value);

template<typename T>
void show_add(Set<T> b, const T& value);

template<typename T>
void show_remove(Set<T> b, const T& value);

template<typename T>
void show_state(Set<T> b);

int main()
{
    using T = long double;
    // std::cout << std::fixed << std::setprecision(5);
    T test = 5;

    const Set<T> a = random_set<T>(4, 8, 0, 1, 10);
    const Set<T> b = random_set<T>(4, 20, 0, 10, 1000);

    Set<T> c = a.unite(b);
    Set<T> d = a.intersect(b);
    Set<T> e = a.difference(b);

    show_generated (a, b);

    //show_operations (c, d, e);
    // show_contains(b, test);
    show_add(b, test);
    // show_remove(b, test);
    // show_state(b);

    return 0;
}

template<typename T>
T typed_random_value(std::mt19937& gen, T min_value, T max_value, int scale)
{
    if constexpr (std::floating_point<T>)
    {
        std::uniform_real_distribution<T> dist(min_value, max_value);
        T value = dist(gen);

        if (scale > 1)
            value = std::round(value * scale) / scale;  // 10 100 1000

        return value;
    }
    else if constexpr (std::integral<T>)
    {
        std::uniform_int_distribution<T> dist(min_value, max_value);
        return dist(gen);
    }
    else
    {
        static_assert(std::floating_point<T> || std::integral<T>,
                      "Непідтримуваний тип для typed_random_value");
    }
    return T{};
}

template<typename T>
Set<T> random_set(const int min_size,
                  const int max_size,
                          T min_value,
                          T max_value,
                  const int scale)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> length_dist(min_size, max_size);

    Set<T> result;

    int len = length_dist(gen);

    for (int i = 0; i < len; ++i)
    {
        result.add(typed_random_value<T>(gen, min_value, max_value, scale));
    }

    return result;
}

template<typename T>
void show_generated(const Set<T>& a, const Set<T>& b)
{
    std::cout << "\nЗгенеровано множину a: \n";
    std::cout << "a: size " << a.size() << " = ";
    a.print();

    std::cout << "\n\nЗгенеровано множину b: \n";
    std::cout << "b: size " << b.size() << " = ";
    b.print();

    std::cout << '\n';
}

template<typename T>
void show_operations(const Set<T>& c, const Set<T>& d, const Set<T>& e)
{
    std::cout << "\nОб'єднання множин a ∪ b:\n";
    std::cout << "c: size " << c.size() << " = ";
    c.print();

    std::cout << "\n\nПеретин множин a ∩ b:\n";
    std::cout << "d: size " << d.size() << " = ";
    d.print();

    std::cout << "\n\nРізниця множин a \\ b:\n";
    std::cout << "e: size " << e.size() << " = ";
    e.print();

    std::cout << '\n';
}

template<typename T>
void show_contains(const Set<T>& b, const T& value)
{
    std::cout << "\nПеревірка contains для множини b:\n";
    std::cout << "contains(" << value << ") = " << std::boolalpha << b.contains(value) << '\n';
}

template<typename T>
void show_add(Set<T> b, const T& value)
{
    std::cout << "\nДемонстрація add для множини b:\n";
    b.add(value);

    std::cout << "Додали add(" << value << "): ";
    b.print();
    std::cout << '\n';
}

template<typename T>
void show_remove(Set<T> b, const T& value)
{
    std::cout << "\nДемонстрація remove для множини b:\n";

    bool removed = b.remove(value);

    std::cout << "remove(" << value << ") = " << std::boolalpha << removed;
    std::cout << "\nСтало: ";
    b.print();
    std::cout << '\n';
}

template<typename T>
void show_state(Set<T> b)
{
    std::cout << '\n' << std::string(46, '-');
    std::cout << "\nДемонстрація size, empty, clear для множини b:\n";
    std::cout << std::string(46, '-');

    std::cout << "\nДо clear: ";
    b.print();
    std::cout << "\nsize = " << b.size();
    std::cout << "\nempty = " << std::boolalpha << b.empty();

    b.clear();

    std::cout << "\n\nПісля clear: ";
    b.print();
    std::cout << "\nsize = " << b.size();
    std::cout << "\nempty = " << std::boolalpha << b.empty() << '\n';
}


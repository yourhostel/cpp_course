//
// Created by tysser on 12.04.26.
//

#include "DoublyLinkedList.h"
#include <iostream>
#include "Person.h"

template <typename T>
void print_list(const DoublyLinkedList<T>& list)
{
    std::cout << "[ ";

    for (std::size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list.get(static_cast<int>(i));
        (i + 1 < list.size()) && std::cout << ", ";
    }

    std::cout << " ]\n";
}

int main()
{
    DoublyLinkedList<Person> people;

    std::cout << "Початковий стан:\n";
    std::cout << "isEmpty = " << std::boolalpha << people.isEmpty() << '\n';
    std::cout << "size = " << people.size() << "\n\n";

    people.addLast({1, "Ivan", 20});
    people.addLast({2, "Olena", 21});
    people.addFirst({0, "Taras", 19});
    people.add(1, {5, "Marta", 22});

    std::cout << "Після addFirst, addLast, add(index):\n";
    print_list(people);
    std::cout << '\n';

    std::cout << "Перший елемент: " << people.getFirst() << '\n';
    std::cout << "Останній елемент: " << people.getLast() << '\n';
    std::cout << "Елемент за індексом 1: " << people.get(1) << "\n\n";

    people.set(1, {5, "Marta Updated", 23});
    std::cout << "Після set(1, ...):\n";
    print_list(people);
    std::cout << '\n';

    people.removeFirst();
    std::cout << "Після removeFirst():\n";
    print_list(people);
    std::cout << '\n';

    people.removeLast();
    std::cout << "Після removeLast():\n";
    print_list(people);
    std::cout << '\n';

    people.addLast({10, "Stepan", 30});
    people.addLast({11, "Iryna", 25});
    people.addLast({12, "Petro", 27});

    std::cout << "Після додаткових addLast():\n";
    print_list(people);
    std::cout << '\n';

    people.remove(1);
    std::cout << "Після remove(1):\n";
    print_list(people);
    std::cout << '\n';

    bool removed = people.remove(Person{11, "", 0});
    std::cout << "remove(Person{id=11}) = " << removed << '\n';
    print_list(people);
    std::cout << '\n';

    DoublyLinkedList<Person> copied(people);
    std::cout << "Скопійований список:\n";
    print_list(copied);
    std::cout << '\n';

    DoublyLinkedList<Person> moved(std::move(people));
    std::cout << "Після переміщення:\n";
    std::cout << "Початковий список:\n";
    print_list(people);
    std::cout << "Переміщений список:\n";
    print_list(moved);
    std::cout << '\n';

    moved.clear();
    std::cout << "Після clear():\n";
    print_list(moved);
    std::cout << "isEmpty = " << moved.isEmpty() << '\n';
    std::cout << "size = " << moved.size() << '\n';

    return 0;
}

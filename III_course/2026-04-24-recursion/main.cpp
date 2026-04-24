#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono_literals;
using namespace std::this_thread;
using namespace std::chrono;

// =======================================================================
void recursive_timer(int& i)
{
    i++;
    std::cout << "Крок №" << i << std::endl;

    if (i > 5) return;

    thread([&i](){
        sleep_for(seconds(1));

        recursive_timer(i);
    }).detach();
}

void imitation()
{
    int i = 0;
    recursive_timer(i);

    // тримаємо main 6 секунд, щоб усі потоки відпрацювали
    sleep_for(seconds(6));
}

// =======================================================================
int fact(int n)
{
    if (n <= 1) return 1;

    return n * fact(n - 1);
}

void factorial()
{
    int n = 5;
    std::cout << "Факторіал " << n << " = " << fact(n) << std::endl;
}

// =======================================================================

struct Node
{
    string value;
    Node* next;
};

void print_list(const Node* node)
{
    if (node == nullptr) return;

    std::cout << "Вхід: " << node->value << std::endl;

    print_list(node->next);

    std::cout << "Вихід: " << node->value << std::endl;
}

void l_list()
{
    Node c{"Кадр 1", nullptr};
    Node b{"Кадр 2", &c};
    Node a{"Кадр 3", &b};

    print_list(&a);
}

int main()
{
    // imitation();
    // factorial();
    l_list();
}

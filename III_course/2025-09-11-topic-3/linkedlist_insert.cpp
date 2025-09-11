// III_course/2025-09-11-topic-3/linkedlist_insert.cpp

#include <iostream>

using namespace std;

struct Node {
    double value;   // дійсне число
    Node* next;     // вказівник на наступний вузол
    explicit Node(double v) : value(v), next(nullptr) {}
};

class LinkedList {
    Node* head; // початок списку
    Node* tail; // кінець списку (щоб push_back був O(1))
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList() {
        while (head) { Node* t = head; head = head->next; delete t; }
    }

    // a) вставка в початок (O(1))
    void set_front(double x) {
        Node* n = new Node(x);
        n->next = head;
        head = n;
        if (!tail) tail = n;   // якщо це перший елемент
        ++size;
    }

    // б) вставка в кінець (O(1) з tail)
    void set_back(double x) {
        Node* n = new Node(x);
        if (!tail) {           // порожній список
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        ++size;
    }

    int get_size()
    {
        return size;
    }

    void print() const {
        cout << "{ ";
        for (Node* p = head; p != nullptr; p = p->next) {
            cout << p->value;
            if (p->next) cout << ", ";
        }
        cout << " }\n";
    }
};

int main() {
    LinkedList lst;

    // a) вставляємо в початок
    lst.set_front(3.14);
    lst.set_front(2.71);

    // б) вставляємо в кінець
    lst.set_back(9.81);
    lst.set_back(1.41);

    lst.print();
    cout << "Розмір списку: " << lst.get_size() << "\n";

    return 0;
}
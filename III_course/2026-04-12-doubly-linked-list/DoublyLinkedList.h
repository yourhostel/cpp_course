//
// Created by tysser on 12.04.26.
//

#pragma once
#include <cstddef>

template <typename T>
class DoublyLinkedList
{
public:

    // ==================================
    // Внутрішня структура вузла списку
    // ==================================
    struct Node
    {
        T data;
        Node* prev;
        Node* next;

        // Конструктор вузла
        explicit Node(const T& value, Node* previous = nullptr, Node* following = nullptr);
    };
    // ===================================
    // Конструктори та оператори
    // ===================================

    // Конструктор за замовчуванням
    DoublyLinkedList();

    // Деструктор
    ~DoublyLinkedList();

    // Конструктор копіювання
    DoublyLinkedList(const DoublyLinkedList& other);

    // Оператор копіювання
    DoublyLinkedList& operator=(const DoublyLinkedList& other);

    // Конструктор переміщення
    DoublyLinkedList(DoublyLinkedList&& other) noexcept;

    // Оператор переміщення
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;

    // ===================================
    // Додавання елементів
    // ===================================

    // Додати елемент за індексом
    void add(int index, const T& value);

    // Додати елемент на початок
    void addFirst(const T& value);

    // Додати елемент у кінець
    void addLast(const T& value);

    // ===================================
    // Доступ до елементів
    // ===================================

    // Отримати елемент за індексом
    T& get(int index);

    // Отримати елемент за індексом (const)
    const T& get(int index) const;

    // Отримати перший елемент
    T& getFirst();

    // Отримати перший елемент (const)
    const T& getFirst() const;

    // Отримати останній елемент
    T& getLast();

    // Отримати останній елемент (const)
    const T& getLast() const;

    // ===================================
    // Зміна елементів
    // ===================================

    // Встановити значення за індексом
    void set(int index, const T& value);

    // ===================================
    // Видалення елементів
    // ===================================

    // Видалити елемент за індексом
    T remove(int index);

    // Видалити перший знайдений елемент за значенням
    bool remove(const T& value);

    // Видалити перший елемент
    T removeFirst();

    // Видалити останній елемент
    T removeLast();

    // ===================================
    // Службові методи
    // ===================================

    // Отримати розмір списку
    [[nodiscard]] std::size_t size() const noexcept;

    // Перевірити чи список порожній
    [[nodiscard]] bool isEmpty() const noexcept;

    // Очистити список
    void clear() noexcept;

private:
    // ===================================
    // Допоміжні методи
    // ===================================

    // Отримати вузол за індексом
    Node* getNode(int index) const;

    // Перевірка індексу
    void checkIndex(int index) const;

    // Перевірка індексу для вставки
    void checkIndexForAdd(int index) const;

    // Перевірка що список не порожній
    void checkNotEmpty() const;

    // Копіювання з іншого списку
    void copyFrom(const DoublyLinkedList& other);

    // Переміщення з іншого списку
    void moveFrom(DoublyLinkedList& other) noexcept;

    // ===================================
    // Дані контейнера
    // ===================================

    Node* head_;
    Node* tail_;
    std::size_t size_;
};

#include "DoublyLinkedList.tpp"


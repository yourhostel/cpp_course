//
// Created by tysser on 12.04.26.
//

#include <stdexcept>
#include "DoublyLinkedList.h"

// Конструктор вузла
template <typename T>
DoublyLinkedList<T>::Node::Node(const T& value, Node* previous, Node* following)
    : data(value), prev(previous), next(following)
{}

// Конструктор за замовчуванням
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head_(nullptr), tail_(nullptr), size_(0)
{}

// Очистити список
template <typename T>
void DoublyLinkedList<T>::clear() noexcept
{
    Node* current = head_;

    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

// Деструктор
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

// Перевірити чи список порожній
template <typename T>
bool DoublyLinkedList<T>::isEmpty() const noexcept
{
    return size_ == 0;
}

// Отримати розмір списку
template <typename T>
std::size_t DoublyLinkedList<T>::size() const noexcept
{
    return size_;
}

// Додати елемент на початок
template <typename T>
void DoublyLinkedList<T>::addFirst(const T& value)
{
    Node* new_node = new Node(value, nullptr, head_);

    head_ && (head_->prev = new_node);
    head_ || (tail_ = new_node);

    head_ = new_node;
    ++size_;
}

// Додати елемент у кінець
template <typename T>
void DoublyLinkedList<T>::addLast(const T& value)
{
    Node* new_node = new Node(value, tail_, nullptr);

    tail_ && (tail_->next = new_node);
    tail_ || (head_ = new_node);

    tail_ = new_node;
    ++size_;
}

// Перевірка що список не порожній
template <typename T>
void DoublyLinkedList<T>::checkNotEmpty() const
{
    if (isEmpty()) throw std::logic_error("Список порожній");
}

// Видалити перший елемент
template <typename T>
T DoublyLinkedList<T>::removeFirst()
{
    checkNotEmpty();

    Node* node = head_;
    T value = node->data;

    head_ = head_->next;

    head_ && (head_->prev = nullptr); // виконується якщо (true) head_ != nullptr
    head_ || (tail_ = nullptr); // виконується якщо (false) head_ == nullptr

    delete node;
    --size_;

    return value;
}

// Видалити останній елемент
template <typename T>
T DoublyLinkedList<T>::removeLast()
{
    checkNotEmpty();

    Node* node = tail_;
    T value = node->data;

    tail_ = tail_->prev;

    tail_ && (tail_->next = nullptr);
    tail_ || (head_ = nullptr);

    delete node;
    --size_;

    return value;
}

// ================================
// База для всіх індексних операцій
// ================================

// Перевірка індексу
template <typename T>
void DoublyLinkedList<T>::checkIndex(const int index) const
{
    if (index < 0 || index >= static_cast<int>(size_))            // 0 ... size_ - 1
        throw std::out_of_range("Індекс поза діапазоном");
}

// Перевірка індексу для вставки
template <typename T>
void DoublyLinkedList<T>::checkIndexForAdd(const int index) const
{
    if (index < 0 || index > static_cast<int>(size_))             // 0 ... size_
        throw std::out_of_range("Індекс поза діапазоном");
}

// Отримати вузол за індексом
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::getNode(const int index) const
{
    checkIndex(index);

    Node* current = nullptr;

    if (index < static_cast<int>(size_ / 2))
    {
        current = head_;

        for (int i = 0; i < index; ++i) current = current->next;
    }
    else
    {
        current = tail_;

        for (int i = static_cast<int>(size_) - 1; i > index; --i) current = current->prev;
    }

    return current;
}

// ================================
// Операції доступу
// ================================

// Отримати елемент за індексом
template <typename T>
T& DoublyLinkedList<T>::get(const int index)
{
    return getNode(index)->data;
}

template <typename T>
const T& DoublyLinkedList<T>::get(const int index) const
{
    return getNode(index)->data;
}

// Отримати перший елемент
template <typename T>
T& DoublyLinkedList<T>::getFirst()
{
    checkNotEmpty();
    return head_->data;
}

template <typename T>
const T& DoublyLinkedList<T>::getFirst() const
{
    checkNotEmpty();
    return head_->data;
}

// Отримати останній елемент
template <typename T>
T& DoublyLinkedList<T>::getLast()
{
    checkNotEmpty();
    return tail_->data;
}

template <typename T>
const T& DoublyLinkedList<T>::getLast() const
{
    checkNotEmpty();
    return tail_->data;
}

// Встановити значення за індексом
template <typename T>
void DoublyLinkedList<T>::set(const int index, const T& value)
{
    getNode(index)->data = value;
}

// ================================
// Модифікації структури
// ================================

// Загальний варіант вставки за індексом
template <typename T>
void DoublyLinkedList<T>::add(const int index, const T& value)
{
    checkIndexForAdd(index);

    if (index == 0)
    {
        addFirst(value);
        return;
    }

    if (index == static_cast<int>(size_))
    {
        addLast(value);
        return;
    }

    Node* next_node = getNode(index);
    Node* prev_node = next_node->prev;

    Node* new_node = new Node(value, prev_node, next_node);

    prev_node->next = new_node;
    next_node->prev = new_node;

    ++size_;
}

// Видалити елемент за індексом
template <typename T>
T DoublyLinkedList<T>::remove(const int index)
{
    checkIndex(index);

    if (index == 0) return removeFirst();

    if (index == static_cast<int>(size_) - 1) return removeLast();

    Node* node = getNode(index);
    Node* prev_node = node->prev;
    Node* next_node = node->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    T value = node->data;

    delete node;
    --size_;

    return value;
}

// Видалити перший знайдений елемент за значенням
template <typename T>
bool DoublyLinkedList<T>::remove(const T& value)
{
    Node* current = head_;

    while (current != nullptr)
    {
        // Порівняння елементів
        // Якщо T це користувацький тип, має бути перевантажений operator==
        // Аналог equals() у Java
        if (current->data == value)
        {
            if (current == head_) return removeFirst(), true;
            if (current == tail_) return removeLast(), true;

            current->prev->next = current->next;
            current->next->prev = current->prev;

            delete current;
            --size_;

            return true;
        }

        current = current->next;
    }

    return false;
}

// ===================================
// Копіювання та переміщення
// ===================================

// Копіювання з іншого списку
template <typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList& other)
{
    Node* current = other.head_;

    while (current != nullptr)
    {
        addLast(current->data);
        current = current->next;
    }
}

// Переміщення з іншого списку O(1) операція
template <typename T>
void DoublyLinkedList<T>::moveFrom(DoublyLinkedList& other) noexcept
{
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

// Конструктор копіювання
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other)
    : head_(nullptr), tail_(nullptr), size_(0)
{
    copyFrom(other);
}

// Оператор копіювання
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other)
{
    if (this != &other) clear(), copyFrom(other);

    return *this;
}

// Конструктор переміщення
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& other) noexcept
    : head_(nullptr), tail_(nullptr), size_(0)
{
    moveFrom(other);
}

// Оператор переміщення
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& other) noexcept
{
    if (this != &other) clear(), moveFrom(other);

    return *this;
}









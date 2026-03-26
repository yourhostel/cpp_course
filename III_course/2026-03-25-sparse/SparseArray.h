//
// Created by tysser on 25.03.26.
//

#pragma once

#include <cstddef>
#include <list>
#include "SparseItem.h"

/**
 * Клас розрідженого одновимірного масиву.
 * Логічно має фіксований розмір, але фізично зберігає тільки задані елементи.
 *
 * @tparam T тип елементів масиву
 */
template<typename T>
class SparseArray
{
private:
    /**
     * Логічний розмір масиву.
     * Визначає допустимий діапазон індексів.
     */
    std::size_t logical_size_;

    /**
     * Фізичне зберігання елементів.
     * Містить тільки ті елементи, які були явно встановлені.
     */
    std::list<SparseItem<T>> data_;

    /**
     * Пошук елемента за логічним індексом.
     *
     * @param index індекс у логічному масиві
     * @return ітератор на знайдений елемент або data_.end()
     */
    typename std::list<SparseItem<T>>::iterator find_item(std::size_t index);

    /**
     * Константна версія пошуку елемента.
     *
     * @param index індекс у логічному масиві
     * @return константний ітератор на елемент або data_.cend()
     */
    typename std::list<SparseItem<T>>::const_iterator find_item(std::size_t index) const;

public:
    /**
     * Конструктор за замовчуванням.
     * Створює масив нульового розміру.
     */
    SparseArray();

    /**
     * Конструктор з логічним розміром.
     *
     * @param logical_size розмір масиву
     */
    explicit SparseArray(std::size_t logical_size);

    /**
     * Конструктор копіювання.
     */
    SparseArray(const SparseArray<T>& other);

    /**
     * Оператор присвоєння.
     *
     * @param other інший масив
     * @return посилання на поточний об’єкт
     */
    SparseArray<T>& operator=(const SparseArray<T>& other);

    /**
     * Повертає логічний розмір масиву.
     *
     * @return розмір масиву
     */
    [[nodiscard]] std::size_t logical_size() const;

    /**
     * Повертає кількість фактично збережених елементів.
     *
     * @return кількість елементів
     */
    [[nodiscard]] std::size_t physical_size() const;

    /**
     * Операція індексування.
     * Повертає посилання на елемент.
     * Якщо елемент відсутній, створює новий.
     *
     * @param index індекс елемента
     * @return посилання на значення
     */
    T& operator[](std::size_t index);

    /**
     * Доступ до існуючого елемента без створення.
     *
     * @param index індекс елемента
     * @return значення елемента
     */
    const T& at(std::size_t index) const;

    /**
     * Вивід збережених елементів масиву.
     */
    void show() const;
};

#include "SparseArray.tpp"
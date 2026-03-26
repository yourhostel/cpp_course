//
// Created by tysser on 25.03.26.
//

#pragma once

#include <cstddef>

/**
 * Клас елемента розрідженого масиву.
 * Зберігає пару: логічний індекс у масиві та відповідне значення.
 * Використовується як внутрішня одиниця зберігання в SparseArray.
 *
 * @tparam T тип значення, яке зберігається
 */
template<typename T>
class SparseItem
{
private:
    std::size_t logical_index_;
    T value_;

public:
    /**
     * Конструктор за замовчуванням.
     * Ініціалізує індекс нулем і значення типу T().
     */
    SparseItem();

    /**
     * Конструктор з параметрами.
     * Встановлює логічний індекс і значення елемента.
     *
     * @param logical_index індекс у логічному масиві
     * @param value значення елемента
     */
    SparseItem(std::size_t logical_index, const T& value);

    /**
     * Повертає логічний індекс елемента в масиві.
     *
     * @return індекс елемента
     */
    [[nodiscard]] std::size_t logical_index() const;

    /**
     * Повертає посилання на значення для зміни.
     *
     * @return значення елемента
     */
    T& value();

    /**
     * Повертає константне посилання на значення.
     *
     * @return значення елемента
     */
    const T& value() const;
};

#include "SparseItem.tpp"
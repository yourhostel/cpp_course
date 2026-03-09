//
// Created by tysser on 09.03.26.
//

#include "Configurations.h"

// Формує всі допустимі конфігурації (x1,...,xk)
std::vector<std::vector<long long>> Configurations::configurations(
    const std::vector<long long>& type_sizes, // N_i кількість об'єктів типу
    long long sample_count,                   // m розмір вибірки
    long long target_type,                    // j тип події
    long long min_count                       // h мінімум x_j
)
{
    std::vector<std::vector<long long>> result;                  // список конфігурацій
    std::vector<long long> current(type_sizes.size(),0);  // поточний вектор x

    generate(
        type_sizes,
        0,                    // початковий тип
        sample_count,         // залишок суми m
        target_type,
        min_count,
        current,
        result
    );

    return result;            // повернути конфігурації
}

// Рекурсивне побудування конфігурацій
void Configurations::generate(
    const std::vector<long long>& type_sizes,     // N_i обмеження
    long long index,                              // поточний індекс
    long long remaining,                          // залишок m
    long long target_type,                        // j тип
    long long min_count,                          // h мінімум
    std::vector<long long>& current,              // поточний x
    std::vector<std::vector<long long>>& result   // контейнер результату
)
{
    long long last = static_cast<long long>(type_sizes.size()) - 1; // останній тип

    if (index == last)                           // останній компонент
    {
        if (remaining >= 0 && remaining <= type_sizes[index]) // перевірка меж
        {
            current[index] = remaining;          // завершити суму

            if (current[target_type] >= min_count) // перевірка події
            {
                result.push_back(current);       // зберегти конфігурацію
            }
        }

        return;                                  // вихід рекурсії
    }

    long long max_value =
        remaining < type_sizes[index]
        ? remaining
        : type_sizes[index];                     // максимум x_i

    for (long long value = 0; value <= max_value; ++value) // перебір x_i
    {
        current[index] = value;                  // встановити x_i

        generate(
            type_sizes,
            index + 1,                           // наступний тип
            remaining - value,                   // новий залишок
            target_type,
            min_count,
            current,
            result
        );
    }
}
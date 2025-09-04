#include "utils.h"
#include <random>

// Реалізація генерації випадкових чисел в діапазоні [min_value; max_value]
std::vector<int> generate_random_numbers(int count, int min_value, int max_value) {
    std::vector<int> numbers;
    numbers.reserve(count);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min_value, max_value);

    for (int i = 0; i < count; ++i) {
        numbers.push_back(dist(gen));
    }

    return numbers;
}

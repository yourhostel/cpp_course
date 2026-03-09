#include "Validator.h"
#include <vector>

#include "Configurations.h"
#include "Probability.h"

void print(const std::vector<std::vector<long long>>& v)
{
    for (const auto& row : v)
    {
        for (auto x : row) std::cout << x << " ";
        std::cout << "\n";
    }
}

// Суматор для всіх конфігурацій
double sum_probability(
    long long total_count,                             // N
    long long sample_count,                            // m
    const std::vector<long long>& type_sizes,          // N_i
    const std::vector<std::vector<long long>>& configs // (x1,...,xk)
)
{
    double sum = 0.0;

    for (const auto& config : configs)
    {
        sum += Probability::probability(         // додати P(x)
            total_count,
            sample_count,
            type_sizes,
            config
        );
    }

    return sum;
}

int main()
{
    // N - загальна кількість об'єктів
    long long total_count = 12;

    // k - кількість типів об'єктів
    long long type_count = 2;

    // N_i - кількість об'єктів кожного типу
    // N₁ = 5 (телевізори з несправною електронікою)
    // N₂ = 7 (телевізори з пошкодженим корпусом)
    std::vector<long long> type_sizes = {5, 7};

    // m - кількість об'єктів, що вибираються з сукупності
    long long sample_count = 4;

    // x_i - кількість об'єктів i-го типу у вибірці
    // x₁ = 2 (два телевізори з несправною електронікою)
    // x₂ = 2 (два телевізори з пошкодженим корпусом)
    std::vector<long long> selected_counts = {2, 2};

    if (Validator<long long>::validate(
            total_count,
            type_count,
            type_sizes,
            sample_count,
            selected_counts))
    {
        std::cout << "Валідація пройшла успішно\n";

        double p = Probability::probability(
            total_count,
            sample_count,
            type_sizes,
            selected_counts
        );

        std::cout << "Основна модель розподілу обчислює лише одну конфігурацію.\n";
        std::cout << "Її задано статично: selected_counts = {2, 2}.\n";
        std::cout << "P(2, 2) = " << p << '\n';
    }
    else
    {
        std::cout << "Валідація не пройшла\n";
    }

    // генерація всіх конфігурацій для умови x_1 ≥ 2
    long long target_type = 0; // тип електроніки
    long long min_count = 2;   // хоча б 2

    auto configs =
        Configurations::configurations(
            type_sizes,
            sample_count,
            target_type,
            min_count
        );

    std::cout << "Генеруємо всі можливі комбінації за допомогою Configurations::configurations:\n";
    print(configs);

    double result =
    sum_probability(
        total_count,
        sample_count,
        type_sizes,
        configs
    );

    std::cout << "Застосовуємо модель до кожної конфігурації та підсумовуємо всі ймовірності.\n";
    std::cout << "P(x1 >= 2) = " << result << "\n";

    return 0;
}


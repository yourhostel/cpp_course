#include <iostream>
#include "stats.hpp"
#include "print.hpp"
#include "confidence_interval_known_sigma.hpp"
#include "confidence_interval_sigma.hpp"

using namespace stats;
using namespace print;
using namespace std;


void confidence_interval_1()
{
    std::ranges::for_each(
        confidence_interval_known_sigma::tasks,
        [](const auto& task)
        {
            const auto [lower, upper] =
                intervals::mean_confidence_interval_known_sigma(
                    task.x_bar,
                    task.sigma,
                    task.n,
                    task.gamma
                );
            cout
                << CYAN << "Задача: " << task.task_number << ". " << RESET;

            cout
                << "σ = " << task.sigma << ", "
                << "x̄ = " << task.x_bar << ", "
                << "n = " << task.n << ", "
                << "γ = " << task.gamma << '\n';

            cout
                << RED << lower << GREEN << " < a < " << RED << upper
                << RESET << '\n' << '\n';
        }
    );
}

void confidence_interval_2()
{
    std::ranges::for_each(
        confidence_interval_sigma::tasks,
        [](const auto& task)
        {
            const auto [lower, upper] =
                intervals::sigma_confidence_interval(
                    task.s,
                    task.n,
                    task.gamma
                );

            cout
                << CYAN << "Задача: " << task.task_number << ". " << RESET;

            cout
                << "s = " << task.s << ", "
                << "n = " << task.n << ", "
                << "γ = " << task.gamma << '\n';

            cout
                << RED << lower << GREEN << " < σ < " << RED << upper
                << RESET << '\n' << '\n';
        }
    );
}

int main()
{
    confidence_interval_2();
    return 0;
}

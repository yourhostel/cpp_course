#include "print.hpp"
#include "grouped_frequency_tasks.hpp"
#include <vector>
#include <ranges>
#include <functional>

using namespace print::charts;
using namespace std;
using namespace print::tables;

using namespace grouped_frequency;

std::vector<histogram_bar> to_relative_histogram_data(const grouped_frequency_task& task)
{
    const int total = std::ranges::fold_left(
        task.data | std::views::transform(&interval_frequency::frequency),
        0,
        std::plus{}
    );

    return task.data
        | std::views::transform([total](const auto& item)
        {
            return histogram_bar
            {
                .category = item.interval,
                .value = static_cast<double>(item.frequency) / total
            };
        })
        | std::ranges::to<std::vector<histogram_bar>>();
}

std::vector<table_row<std::string>> to_table_data(const grouped_frequency_task& task)
{
    return task.data
        | std::views::transform([](const auto& item)
        {
            return table_row<std::string>
            {
                .value_first = item.interval,
                .value_second = std::to_string(item.frequency)
            };
        })
        | std::ranges::to<std::vector<table_row<std::string>>>();
}

const grouped_frequency_task* find_task(const std::string& input)
{
    if (input.starts_with('i'))
    {
        const std::size_t index = std::stoul(input.substr(1));
        return index < tasks.size() ? &tasks[index] : nullptr;
    }

    const auto it = task_index.find(input);
    return it != task_index.end() ? &tasks.at(it->second) : nullptr;
}

std::unique_ptr<QChartView> show_task_chart(const grouped_frequency_task& task)
{
    const auto histogram_data = to_relative_histogram_data(task);
    const auto table_data = to_table_data(task);

    print_distribution_table(
        "Завдання",
        task.task_number,
        "interval",
        "n_i",
        table_data
    );

    const histogram_options options
    {
        .window_title = std::format("Завдання № {}", task.task_number),
        .set_name = "Відносна частота",
        .chart_title = "Гістограма відносних частот",
        .y_axis_title = "Частка",
        .x_axis_title = "Інтервали",
        .y_min = 0.0,
        .y_max = 0.4,
        .width = 800,
        .height = 600,
        .precision = 2
    };

    auto chart_view = create_histogram_chart_view(histogram_data, options);
    chart_view->show();

    return chart_view;
}

void test(int argc, char* argv[])
{
    QApplication app(argc, argv);

    while (true)
    {
        std::cout << "Введіть номер завдання 2.1 ... 2.11 або індекс i0 ... i10 або exit: \n" << std::flush;

        std::string input;
        std::cin >> input;

        if (input == "exit") break;

        const grouped_frequency_task* task = find_task(input);

        if (task == nullptr)
        {
            std::cout << "Завдання не знайдено\n\n";
            continue;
        }

        std::unique_ptr<QChartView> chart_view = show_task_chart(*task);

        app.exec();

        chart_view.reset();

        std::cout << "Побудувати новий графік? y/n: " << std::flush;

        std::string answer;
        std::cin >> answer;

        if (answer != "y") break;
    }
}

int main(const int argc, char* argv[])
{
    test(argc, argv);

    return 0;
}

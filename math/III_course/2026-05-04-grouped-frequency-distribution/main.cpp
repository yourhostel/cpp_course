#include "grouped_frequency_app.hpp"

void test(int argc, char* argv[])
{
    QApplication app(argc, argv);

    while (true)
    {
        std::cout << "Введіть номер завдання 2.1 ... 2.11 або індекс i0 ... i10 або exit: \n";

        std::string input;
        std::cin >> input;

        if (input == "exit") break;

        const auto* task = grouped_frequency::app::find_task(input);

        if (!task)
        {
            std::cout << "Завдання не знайдено\n\n";
            continue;
        }

        auto view = grouped_frequency::app::show_task_chart(*task);

        app.exec();
        view.reset();

        std::cout << "Побудувати новий графік? y/n: ";

        std::string answer;
        std::cin >> answer;

        if (answer != "y") break;
    }
}

int main(int argc, char* argv[])
{
    test(argc, argv);
}

#ifndef VALIDATE_H
#define VALIDATE_H


inline int validateMenuChoice(const int maxOption)
{
    int value;
    std::cin >> value;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Помилка: введіть число!");
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (value < 1 || value > maxOption)
    {
        throw std::out_of_range(
            "Помилка: пункт меню повинен бути в діапазоні 1.." + std::to_string(maxOption)
        );
    }

    return value;
}

inline double readDouble(const std::string& prompt)
{
    double value;
    std::cout << prompt;
    std::cin >> value;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Помилка: введіть число!");
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

#endif //VALIDATE_H

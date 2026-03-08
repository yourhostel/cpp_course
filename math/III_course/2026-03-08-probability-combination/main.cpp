#include "Validator.h"
#include <vector>

int main()
{
    long long total_count = 12;
    long long type_count = 2;
    std::vector<long long> type_sizes = {5, 7};
    long long sample_count = 4;
    std::vector<long long> selected_counts = {2, 2};

    if (Validator<long long>::validate(
            total_count,
            type_count,
            type_sizes,
            sample_count,
            selected_counts))
    {
        std::cout << "Валідація пройшла успішно\n";
    }
    else
    {
        std::cout << "Валідація не пройшла\n";
    }

    return 0;
}

// void prompt_loop()
// {
//
// }
//
// int main()
// {
//     prompt_loop();
//     return 0;
// }


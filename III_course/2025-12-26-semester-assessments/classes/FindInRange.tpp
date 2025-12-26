//
// Created by tysser on 26.12.25.
//

// cpp_course/III_course/2025-12-26-semester-assessments/classes/FindInRange.tpp

template <typename T>
std::vector<T> findInRange(const std::vector<T>& data,
                           const T& min,
                           const T& max)
{
    std::vector<T> result;

    for (const auto& value : data)
    {
        if (value >= min && value <= max)
        {
            result.push_back(value);
        }
    }

    return result;
}
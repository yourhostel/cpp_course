//
// Created by tysser on 26.12.25.
//

// cpp_course/III_course/2025-12-26-semester-assessments/classes/NumberPair.tpp

template <typename T, typename U>
NumberPair<T, U>::NumberPair(T first, U second)
    : first_(first), second_(second) {}

template <typename T, typename U>
T NumberPair<T, U>::first() const
{
    return first_;
}

template <typename T, typename U>
U NumberPair<T, U>::second() const
{
    return second_;
}

template <typename T, typename U>
void NumberPair<T, U>::print() const
{
    std::cout << "first=" << first_
              << ", second=" << second_ << '\n';
}

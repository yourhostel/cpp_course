//
// Created by tysser on 26.12.25.
//

// cpp_course/III_course/2025-12-26-semester-assessments/classes/FindInRange.h
#ifndef CPP_COURSE_FINDINRANGE_H
#define CPP_COURSE_FINDINRANGE_H

#include <vector>

template <typename T>
std::vector<T> findInRange(const std::vector<T>& data,
                           const T& min,
                           const T& max);

#include "FindInRange.tpp"

#endif //CPP_COURSE_FINDINRANGE_H
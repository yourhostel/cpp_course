//
// Created by tysser on 26.12.25.
//

// cpp_course/III_course/2025-12-26-semester-assessments/classes/NumberPair.h
#ifndef CPP_COURSE_NUMBERPAIR_H
#define CPP_COURSE_NUMBERPAIR_H

template <typename T, typename U>
class NumberPair {
public:
    NumberPair(T first, U second);

    T first() const;
    U second() const;
    void print() const;

private:
    T first_;
    U second_;
};

#include "NumberPair.tpp"

#endif //CPP_COURSE_NUMBERPAIR_H
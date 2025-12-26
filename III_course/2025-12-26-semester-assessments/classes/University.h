//
// Created by tysser on 26.12.25.
//

// cpp_course/III_course/2025-12-26-semester-assessments/classes/University.h
#ifndef CPP_COURSE_UNIVERSITY_H
#define CPP_COURSE_UNIVERSITY_H
#include <string>
#include <iostream>

class University {
public:
    explicit University(std::string name);
    virtual ~University() = default;
    virtual void printInfo() const;

protected:
    std::string name_;
};

class Faculty final : public University
{
public:
    explicit Faculty(std::string name);
    void printInfo() const override;
};

class Department final : public University {
public:
    explicit Department(std::string name);
    void printInfo() const override;
};

#endif //CPP_COURSE_UNIVERSITY_H
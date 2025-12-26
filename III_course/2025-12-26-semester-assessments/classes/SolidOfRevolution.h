//
// Created by tysser on 26.12.25.
//

// cpp_course/III_course/2025-12-26-semester-assessments/classes/SolidOfRevolution.h
#ifndef CPP_COURSE_SOLIDOFREVOLUTION_H
#define CPP_COURSE_SOLIDOFREVOLUTION_H

class SolidOfRevolution {
public:
    virtual ~SolidOfRevolution() = default;

    [[nodiscard]] virtual double volume() const = 0;
    virtual void printInfo() const = 0;
};

class Cone final : public SolidOfRevolution {
public:
    Cone(double radius, double height);

    [[nodiscard]] double volume() const override;

    void printInfo() const override;

private:
    double radius_;
    double height_;
};

class Cylinder final : public SolidOfRevolution {
public:
    Cylinder(double radius, double height);

    [[nodiscard]] double volume() const override;
    void printInfo() const override;

private:
    double radius_;
    double height_;
};

#endif //CPP_COURSE_SOLIDOFREVOLUTION_H
//
// Created by tysser on 10.11.25.
//

// III_course/2025-11-15-qt-practical-11-tree-parser-2/expressiontree.h
#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <cmath>

// Базовий клас (вершина дерева)
class Telement {
protected:
    Telement *left;
    Telement *right;
public:
    explicit Telement(Telement *l = nullptr, Telement *r = nullptr)
        : left(l), right(r) {}
    virtual ~Telement() { delete left; delete right; }

    [[nodiscard]] virtual double result(double x) const = 0; // абстрактна функція
};

// Клас числа або змінної
class Number final : public Telement {
    double value;
    bool isVariable;

public:
    explicit Number(const double val) : value(val), isVariable(false) {}
    Number() : value(0), isVariable(true) {} // для 'x'

    [[nodiscard]] double result(const double x) const override
    {
        return isVariable ? x : value;
    }
};

// Операція '+'
class Plus final : public Telement {

public:
    Plus(Telement *l, Telement *r) : Telement(l, r) {}
    [[nodiscard]] double result(const double x) const override
    {
        return left->result(x) + right->result(x);
    }
};

// Операція '-'
class Minus final : public Telement {

public:
    Minus(Telement *l, Telement *r) : Telement(l, r) {}
    [[nodiscard]] double result(const double x) const override {
        return left->result(x) - right->result(x);
    }
};

// Операція '*'
class Mult final : public Telement {

public:
    Mult(Telement *l, Telement *r) : Telement(l, r) {}
    [[nodiscard]] double result(const double x) const override
    {
        return left->result(x) * right->result(x);
    }
};

// Операція '/'
class Div final : public Telement {
public:
    Div(Telement* l, Telement* r) : Telement(l, r) {}
    [[nodiscard]] double result(double x) const override {
        const double denominator = right->result(x);
        if (denominator == 0.0)
            throw std::runtime_error("Ділення на нуль");
        return left->result(x) / denominator;
    }
};

// Операція '^'
class Power final : public Telement {

public:
    Power(Telement *l, Telement *r) : Telement(l, r) {}
    [[nodiscard]] double result(const double x) const override
    {
        return std::pow(left->result(x), right->result(x));
    }
};

#endif //EXPRESSIONTREE_H

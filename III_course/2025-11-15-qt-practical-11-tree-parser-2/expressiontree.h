//
// Created by tysser on 15.11.25.
//

// III_course/2025-11-15-qt-practical-11-tree-parser-2/expressiontree.h
#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <cmath>
#include <stdexcept>
#include <memory>

/**
 * Базовий вузол обчислювального дерева.
 *
 * Усі арифметичні оператори та операнди успадковуються від Telement.
 * Тримає два піддерева (left, right), які можуть бути відсутні.
 *
 * Основні задачі вузла:
 *   - result(): обчислення значення виразу
 *   - copy(): створення глибокої копії піддерева
 *   - differ(): побудова дерева похідної
 *   - setVar(x): рекурсивна передача значення змінної у всю структуру
 */
class Telement {
protected:
    // std::unique_ptr - розумний вказівник у C++,
    // володіє одним динамічно виділеним ресурсом і автоматично звільняє його
    // https://acode.com.ua/urok-201-rozumnyj-vkazivnyk-std-unique_ptr
    std::unique_ptr<Telement> left;
    std::unique_ptr<Telement> right;

public:
    explicit Telement(std::unique_ptr<Telement> l = nullptr,
             std::unique_ptr<Telement> r = nullptr)
        : left(std::move(l)), right(std::move(r)) {}

    virtual ~Telement() = default;

    /**
     * Обчислення значення поточного вузла.
     * Використовується під час фінальної оцінки f(x), f'(x), f''(x).
     */
    [[nodiscard]] virtual double result() const = 0;

    /**
     * Повертає повну копію піддерева.
     * Необхідно для побудови похідних:
     *   f'(x) часто містить копії частин оригінальної структури.
     */
    [[nodiscard]] virtual std::unique_ptr<Telement> copy() const = 0;

    /**
     * Повертає нове дерево, що є похідною даного вузла.
     * Математичні правила:
     *   +, -, *, / реалізовані в класах
     *   степінь працює лише для u^n, де n - Real
     */
    [[nodiscard]] virtual std::unique_ptr<Telement> differ() const = 0;

    /**
     * Поширює значення x на всі піддерева.
     * Використовується після парсингу f(x), f'(x), f''(x).
     */
    virtual void setVar(const double x)
    {
        if (left)  left->setVar(x);
        if (right) right->setVar(x);
    }
};

/**
 * Константа.
 *
 * Дійсний числовий літерал, наприклад 3.14 або 8.
 * Не має піддерев. Фіксоване значення.
 */
class Real final : public Telement {
    double value_;

public:
    explicit Real(const double v)
        : Telement(nullptr, nullptr),
          value_(v)
    {}

    [[nodiscard]] double value() const { return value_; }

    [[nodiscard]] double result() const override
    {
        return value_;
    }

    [[nodiscard]] std::unique_ptr<Telement> copy() const override
    {
        return std::make_unique<Real>(value_);
    }

    [[nodiscard]] std::unique_ptr<Telement> differ() const override
    {
        return std::make_unique<Real>(0.0);
    }
};

/**
 * Змінна x.
 *
 * Значення встановлюється setVar(x).
 */
class Var final : public Telement {
    double x_ = 0.0;

public:
    Var(): Telement(nullptr, nullptr){}

    [[nodiscard]] double result() const override { return x_; }

    [[nodiscard]] std::unique_ptr<Telement> copy() const override
    {
        // Оскільки Var не має піддерев, створюємо новий Var з тим самим x_.
        auto v = std::make_unique<Var>();
        v->setVar(x_);
        return v;
    }

    [[nodiscard]] std::unique_ptr<Telement> differ() const override
    {
        return std::make_unique<Real>(1.0);
    }

    void setVar(const double x) override
    {
        x_ = x;
    }
};

/*==============================================================================
    ОПЕРАТОРИ
==============================================================================*/

/**
 * Сума: u + v.
 */
class Plus final : public Telement {
public:
    Plus(std::unique_ptr<Telement> l, std::unique_ptr<Telement> r)
    : Telement(std::move(l), std::move(r)) {}

    [[nodiscard]] double result() const override
    {
        return left->result() + right->result();
    }

    [[nodiscard]] std::unique_ptr<Telement> copy() const override
    {
        return std::make_unique<Plus>(left->copy(), right->copy());
    }

    [[nodiscard]] std::unique_ptr<Telement> differ() const override
    {
        return std::make_unique<Plus>(left->differ(), right->differ());
    }
};

/**
 * Різниця: u - v.
 */
class Minus final : public Telement {
public:
    Minus(std::unique_ptr<Telement> l, std::unique_ptr<Telement> r)
        : Telement(std::move(l), std::move(r)){}

    [[nodiscard]] double result() const override
    {
        return left->result() - right->result();
    }

    [[nodiscard]] std::unique_ptr<Telement> copy() const override
    {
        return std::make_unique<Minus>(left->copy(), right->copy());
    }

    [[nodiscard]] std::unique_ptr<Telement> differ() const override
    {
        return std::make_unique<Minus>(left->differ(), right->differ());
    }
};

/**
 * Добуток: u * v.
 */
class Mult final : public Telement {
public:
    Mult(std::unique_ptr<Telement> l, std::unique_ptr<Telement> r)
        : Telement(std::move(l), std::move(r)){}

    [[nodiscard]] double result() const override
    {
        return left->result() * right->result();
    }

    [[nodiscard]] std::unique_ptr<Telement> copy() const override
    {
        return std::make_unique<Mult>(left->copy(), right->copy());
    }

    [[nodiscard]] std::unique_ptr<Telement> differ() const override
    {
        // (u * v)' = u' * v + u * v'
        return std::make_unique<Plus>
        (
            std::make_unique<Mult>(left->differ(), right->copy()),
            std::make_unique<Mult>(left->copy(), right->differ())
        );
    }
};

/**
 * Ділення: u / v.
 */
class Div final : public Telement {
public:
    Div(std::unique_ptr<Telement> l, std::unique_ptr<Telement> r)
        : Telement(std::move(l), std::move(r)){}

    [[nodiscard]] double result() const override
    {
        const double denom = right->result();
        if (denom == 0.0)
            throw std::runtime_error("Ділення на нуль");

        return left->result() / denom;
    }

    [[nodiscard]] std::unique_ptr<Telement> copy() const override
    {
        return std::make_unique<Div>(left->copy(), right->copy());
    }

    [[nodiscard]] std::unique_ptr<Telement> differ() const override
    {
        // (u / v)' = (u' * v - u * v') / (v^2)
        return std::make_unique<Div>(
            std::make_unique<Minus>(
                std::make_unique<Mult>(left->differ(), right->copy()),
                std::make_unique<Mult>(left->copy(), right->differ())
            ),
            std::make_unique<Mult>(right->copy(), right->copy())
        );
    }
};

/**
 * Піднесення до степеня: u^n.
 *
 * Обмеження реалізації:
 *   показник степеня має бути константою (Real).
 */
class Power final : public Telement {
public:
    Power(std::unique_ptr<Telement> l, std::unique_ptr<Telement> r)
        : Telement(std::move(l), std::move(r)) {}

    [[nodiscard]] double result() const override
    {
        return std::pow(left->result(), right->result());
    }

    [[nodiscard]] std::unique_ptr<Telement> copy() const override
    {
        return std::make_unique<Power>(left->copy(), right->copy());
    }

    [[nodiscard]] std::unique_ptr<Telement> differ() const override
    {   // Дозволяємо тільки ступінь з числовим показником
        const auto* exp = dynamic_cast<const Real*>(right.get());
        if (!exp)
            throw std::runtime_error("Ступінь дозволено лише з числовим показником");

        double n = exp->value();
        // (u^n)' = n * u^(n-1) * u'
        return std::make_unique<Mult>(
            std::make_unique<Real>(n),
            std::make_unique<Mult>(
                std::make_unique<Power>(
                    left->copy(),
                    std::make_unique<Real>(n - 1.0)
                ),
                left->differ()
            )
        );
    }
};

#endif //EXPRESSIONTREE_H

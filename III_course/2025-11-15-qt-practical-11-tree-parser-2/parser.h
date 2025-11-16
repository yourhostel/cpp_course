//
// Created by tysser on 15.11.25.
//

// III_course/2025-11-15-qt-practical-11-tree-parser-2/parser.h
#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <stdexcept>
#include <utility>
#include "expressiontree.h"

/**
 * Рекурсивний парсер арифметичних виразів.
 *
 * Підтримувана граматика:
 *     Expr   = Term { ('+' | '-') Term }
 *     Term   = Power { ('*' | '/') Power }
 *     Power  = Factor ['^' Factor]
 *     Factor = { '+' | '-' } Primary
 *     Primary = NUMBER | 'x' | '(' Expr ')'
 *
 * Реалізація базується на рекурсивному спуску.
 * Пробіли ігноруються.
 */
class StringParser {

    QString text_; // вихідний вираз
    int pos_;      // внутрішній курсор парсера

public:
    /**
     * Конструктор приймає вираз як QString.
     * Встановлює курсор на початок.
     */
    explicit StringParser(QString text) : text_(std::move(text)), pos_(0){}

    /**
     * Основний метод парсингу.
     *
     * Алгоритм:
     *   1) Пропустити пробіли.
     *   2) Перевірити, що рядок непорожній.
     *   3) Розпарсити вираз відповідно до граматики.
     *   4) Перевірити, що після парсингу не лишилось зайвих символів.
     *
     * @return дерево Telement у вигляді std::unique_ptr
     * @throw std::runtime_error При будь-якій синтаксичній помилці
     */
    std::unique_ptr<Telement> parse()
    {
        // skipSpaces();

        // if (text_.trimmed().isEmpty())
        //     throw std::runtime_error("Порожній вираз");
        // pos_ = 0;

        auto node = parseExpression();
        skipSpaces();

        if (!atEnd())
            throw std::runtime_error("Зайві символи в кінці виразу");

        return node;
    }

private:
    /**
     * Перевіряє, чи вичерпано рядок.
     *
     * @return true якщо pos_ >= text_.size()
     */
    [[nodiscard]] bool atEnd() const
    {
        return pos_ >= text_.size();
    }

    /**
     * Повертає символ під курсором, але без зсуву.
     * Якщо кінець рядка - повертає порожній QChar().
     */
    [[nodiscard]] QChar peek() const
    {
        if (atEnd()) return QChar();
        return text_[pos_];
    }

    /**
     * Повертає символ під курсором і зсуває курсор на 1 вперед.
     * Якщо кінець рядка - повертає QChar().
     */
    QChar get()
    {
        if (atEnd()) return QChar();
        return text_[pos_++];
    }

    /**
     * Пропускає всі пробільні символи: ' ', '\t', '\n', '\r', тощо.
     *
     * Пробіли не видаляє з тексту - лише пересуває курсор.
     */
    void skipSpaces()
    {
        while (!atEnd() && peek().isSpace())
        {
            ++pos_;
        }
    }

    /**
     * Перевіряє, чи наступний непорожній символ є ch.
     *
     * Якщо так - зсуває курсор і повертає true.
     * Якщо ні - нічого не змінює і повертає false.
     *
     * @param ch очікуваний символ
     */
    bool consume(const QChar ch)
    {
        skipSpaces();
        if (!atEnd() && peek() == ch)
        {
            ++pos_;
            return true;
        }
        return false;
    }

    /**
     * Expr = Term { ('+' | '-') Term }
     *
     * Це найнижчий пріоритет (сума і різниця).
     * По суті обробляє ліву асоціативність: a-b+c -> ((a-b)+c)
     */
    std::unique_ptr<Telement> parseExpression()
    {
        auto node = parseTerm();
        while (true)
        {
            if (consume('+'))
            {
                auto rhs = parseTerm();
                node = std::make_unique<Plus>(std::move(node), std::move(rhs));
            }
            else if (consume('-'))
            {
                std::unique_ptr<Telement> rhs = parseTerm();
                node = std::make_unique<Minus>(std::move(node), std::move(rhs));
            }
            else
            {
                break;
            }
        }
        return node;
    }

    /**
     * Term = Power { ('*' | '/') Power }
     *
     * Обробляє множення та ділення.
     * Ліва асоціативність: a*b/c → ((a*b)/c)
     */
    std::unique_ptr<Telement> parseTerm()
    {
        auto node = parsePower();
        while (true)
        {
            if (consume('*'))
            {
                auto rhs = parsePower();
                node = std::make_unique<Mult>(std::move(node), std::move(rhs));
            }
            else if (consume('/'))
            {
                auto rhs = parsePower();
                node = std::make_unique<Div>(std::move(node), std::move(rhs));
            }
            else
            {
                break;
            }
        }
        return node;
    }

    /**
     * Power = Factor ['^' Factor]
     *
     * Реалізує операцію піднесення до степеня.
     * Ступінь у цій реалізації не є правою асоціативною:
     *     a^b^c інтерпретується як (a^b)^c.
     */
    std::unique_ptr<Telement> parsePower()
    {
        auto base = parseFactor();

        // Один рівень ступеня
        if (consume('^'))
        {
            auto exp = parseFactor();
            return std::make_unique<Power>(std::move(base), std::move(exp));
        }

        return base;
    }

    /**
     * Factor = { '+' | '-' } Primary
     *
     * Обробляє унарні знаки:
     *     -x
     *     +x
     *     ---x
     *
     * Кілька знаків змінюють полярність: ---x => -( -( -(x))) => -x.
     */
    std::unique_ptr<Telement> parseFactor()
    {
        skipSpaces();

        bool negative = false;
        // Можемо мати кілька знаків підряд: ---x
        while (!atEnd() && (peek() == '+' || peek() == '-'))
        {
            if (peek() == '-')
            {
                negative = !negative;
            }
            ++pos_;
            skipSpaces();
        }

        auto node = parsePrimary();

        if (negative)
        {
            return std::make_unique<Mult>(
                std::make_unique<Real>(-1.0),
                std::move(node)
            );
        }

        return node;
    }

    /**
     * Primary = NUMBER | 'x' | '(' Expr ')'
     *
     * Найнижчий рівень:
     *   - число
     *   - змінна x / X
     *   - вираз у дужках
     */
    std::unique_ptr<Telement> parsePrimary()
    {
        skipSpaces();
        if (atEnd())
            throw std::runtime_error("Неочікуваний кінець виразу");

        const QChar c = peek();

        // Дужки
        if (c == '(') {
            get();            // прочитали '('
            skipSpaces();

            // Перевірка на порожній вираз: ()
            if (peek() == ')') {
                get();        // прочитали ')'
                throw std::runtime_error("Порожній вираз");
            }

            // Тут гарантовано є хоч щось
            auto node = parseExpression();

            if (!consume(')'))
                throw std::runtime_error("Немає закриваючої дужки");

            return node;
        }

        // Змінна x
        if (c == 'x' || c == 'X')
        {
            get();
            return std::make_unique<Var>();
        }

        // Число
        if (c.isDigit() || c == '.')
        {
            const double val = parseNumber();
            return std::make_unique<Real>(val);
        }

        throw std::runtime_error("Невірний символ у виразі");
    }

    /**
     * Парсить число у форматі:
     *     123
     *     3.14
     *     .5
     *
     * Перевіряє, що в числі лише одна крапка.
     *
     * @return значення числа
     * @throw std::runtime_error якщо число некоректне
     */
    double parseNumber()
    {
        skipSpaces();
        const int start = pos_;
        bool dotSeen = false;

        while (!atEnd())
        {
            if (QChar c = peek(); c.isDigit())
            {
                ++pos_;
            }
            else if (c == '.')
            {
                if (dotSeen)
                {
                    throw std::runtime_error("Некоректне число з двома крапками");
                }
                dotSeen = true;
                ++pos_;
            }
            else
            {
                break;
            }
        }

        const QString token = text_.mid(start, pos_ - start);
        bool ok = false;
        const double val = token.toDouble(&ok);
        if (!ok)
            throw std::runtime_error("Не вдалося перетворити число");

        return val;
    }
};

/**
 * Обгортка, щоб можна було викликати:
 *     auto tree = parseExpression("3*x+2");
 */
inline std::unique_ptr<Telement> parseExpression(const QString &expr)
{
    StringParser parser(expr);
    return parser.parse();
}

#endif //PARSER_H

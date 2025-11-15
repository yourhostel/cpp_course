//
// Created by tysser on 10.11.25.
//

// III_course/2025-11-15-qt-practical-11-tree-parser-2/parser.h
#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include "expressiontree.h"

// Будуємо дерево рекурсивно
inline Telement* parseExpression(const QString &expr) {
    QString s = expr;
    s.remove(' ');

    int paren = 0;

    // qsizetype - це тип індексації для всіх контейнерів Qt (QString, QVector, QList, QByteArray тощо)
    // Усі методи Qt типу:
    // QString::length(), QVector::size(), QByteArray::indexOf() - повертає qsizetype
    qsizetype opPos = -1;
    QChar op;

    // 1. пошук операцій низького пріоритету (+/-)

    // якщо компілятор лається на порівняння i >= 0, бо qsizetype беззнаковий:
    // for (qsizetype i = s.length(); i-- > 0; )
    for  (qsizetype i = s.length() - 1; i >= 0; --i)
    {
        if (s[i] == ')') paren++;
        else if (s[i] == '(') paren--;
        else if (!paren && (s[i] == '+' || s[i] == '-'))
        {
            opPos = i;
            op = s[i];
            break;
        }
    }

    // 2. якщо не знайдено — шукаємо * або /
    if (opPos == -1)
    {
        paren = 0;
        for (qsizetype i = s.length() - 1; i >= 0; --i)
        {
            if (s[i] == ')') paren++;
            else if (s[i] == '(') paren--;
            else if (!paren && (s[i] == '*' || s[i] == '/'))
            {
                opPos = i;
                op = s[i];
                break;
            }
        }
    }

    // 3. якщо не знайдено - шукаємо ^
    if (opPos == -1)
    {
        paren = 0;
        for (qsizetype i = s.length() - 1; i >= 0; --i)
        {
            if (s[i] == ')') paren++;
            else if (s[i] == '(') paren--;
            else if (!paren && s[i] == '^')
            {
                opPos = i;
                op = '^';
                break;
            }
        }
    }

    // 4. Якщо знайдена операція
    if (opPos != -1)
    {
        Telement* left = parseExpression(s.left(opPos));
        Telement* right = parseExpression(s.mid(opPos + 1));

        switch (op.unicode())
        {
        case '+': return new Plus(left, right);
        case '-': return new Minus(left, right);
        case '*': return new Mult(left, right);
        case '^': return new Power(left, right);
        case '/': return new Div(left, right);
        default:
            throw std::runtime_error("Невідомий оператор у виразі");
        }
    }

    // 5. Якщо в дужках - видаляємо їх
    if (s.startsWith('(') && s.endsWith(')'))
        return parseExpression(s.mid(1, s.length() - 2));

    // 6. Якщо x
    if (s == "x" || s == "X")
        return new Number();

    // 7. Якщо число
    bool ok = false;
    const double val = s.toDouble(&ok);
    if (ok) return new Number(val);

    throw std::runtime_error(("Невірний вираз: " + s).toStdString());
}

#endif //PARSER_H

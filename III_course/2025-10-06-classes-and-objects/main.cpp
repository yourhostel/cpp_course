// # III_course/2025-10-06-classes-and-objects/main.cpp
#include <array>
#include <iostream>
#include <iomanip>
#include <limits>

class Matrix4x4 {
public:
    // type alias
    using RowT = std::array<double, 4>;
    using DataT = std::array<RowT, 4>;

    Matrix4x4() { // Біжимо по строках
        for (auto& row : data_)
        {
            // Заповнюємо кожен елемент строки 0.0
            row.fill(0.0);
        }
    }

    // Ввід матриці
    void read(std::istream& in = std::cin) {
        for (auto& row : data_)
            for (auto& el : row)
                in >> el;
    }

    // Вивід матриці
    void print(std::ostream& out = std::cout) const {
        out << std::fixed << std::setprecision(2); // кількість знаків після коми
        for (const auto& row : data_) {
            for (const double el : row)
                out << std::setw(8) << el;
            out << '\n';
        }
    }

    // Пошук максимального елемента
    // nodiscard - якщо повернутий результат проігноровано, видасть попередження
    [[nodiscard]] double maxElement() const {
        // “нескінченність” для числових типів з плаваючою точкою −∞
        // починаємо з −∞ і шукаємо найбільший
        double maxVal = -std::numeric_limits<double>::infinity();
        for (const auto& row : data_)
            for (const double el : row)
                if (el > maxVal) maxVal = el;
        return maxVal;
    }

    // Дружні функції не члени класу, але з доступом до приватного поля data_.
    // Для симетрії, a + b / b + a
    // Перевантаження +
    friend Matrix4x4 operator+(const Matrix4x4& a, const Matrix4x4& b) {
        Matrix4x4 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r.data_[i][j] = a.data_[i][j] + b.data_[i][j];
        return r;
    }

    // Перевантаження -
    friend Matrix4x4 operator-(const Matrix4x4& a, const Matrix4x4& b) {
        Matrix4x4 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r.data_[i][j] = a.data_[i][j] - b.data_[i][j];
        return r;
    }

private:
    DataT data_{};
};

int main() {
    Matrix4x4 a, b;

    std::cout << "Введи 16 чисел для матриці A (4x4):\n";
    a.read();
    std::cout << "Введи 16 чисел для матриці B (4x4):\n";
    b.read();

    std::cout << "\nМатриця A:\n";
    a.print();
    std::cout << "Max A = " << a.maxElement() << "\n";

    std::cout << "\nМатриця B:\n";
    b.print();
    std::cout << "Max B = " << b.maxElement() << "\n";

    std::cout << "\nA + B:\n";
    (a + b).print();

    std::cout << "\nA - B:\n";
    (a - b).print();
}



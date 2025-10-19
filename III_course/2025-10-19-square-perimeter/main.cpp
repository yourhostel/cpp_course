// III_course/2025-10-19-square-perimeter/main.cpp
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>

using namespace std;

// Завдання 1: Периметр квадрата за площею
class Square {
private:
    double area_{0.0};;  // Площа квадрата
public:
    explicit Square(const double area = 0.0)
    {
        if (area < 0.0)
            throw invalid_argument("Square: area must be >= 0");
        area_ = area;
    }

    void setArea(const double area)
    {
        if (area < 0.0)
            throw invalid_argument("Square: area must be >= 0");
        area_ = area;
    }

    [[nodiscard]] double getPerimeter() const
    {
        return 4.0 * sqrt(area_);
    }

    void print() const
    {
        cout << "Площа квадрата: " << area_ << ", периметр: " << getPerimeter() << endl;
    }
};

void squarePerimeter()
{
    cout << "\n=== Завдання 1: Периметр квадрата за площею ===\n";
    try {
        cout << "Введіть площу квадрата: ";
        double area;
        cin >> area;
        const Square sq(area);
        sq.print();
    } catch (const invalid_argument& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
}

// Завдання 2: Площа кільця за зовнішнім і внутрішнім радіусами
class Ring {
private:
    double outerRadius_{0.0};
    double innerRadius_{0.0};

    static void validateRadii(const double outer, const double inner)
    {
        if (outer <= 0.0)
            throw invalid_argument("Ring: outer radius must be > 0");
        if (inner < 0.0)
            throw invalid_argument("Ring: inner radius must be >= 0");
        if (inner >= outer)
            throw invalid_argument("Ring: inner radius must be < outer radius");
    }

public:
    explicit Ring(const double outer = 1.0, const double inner = 0.0)
    {
        validateRadii(outer, inner);
        outerRadius_ = outer;
        innerRadius_ = inner;
    }

    void setRadii(const double outer, const double inner)
    {
        validateRadii(outer, inner);
        outerRadius_ = outer;
        innerRadius_ = inner;
    }

    [[nodiscard]] double getArea() const
    {
        return M_PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
    }

    void print() const
    {
        cout << "Зовнішній радіус: " << outerRadius_ << ", внутрішній радіус: " << innerRadius_
             << ", площа кільця: " << getArea() << endl;
    }
};

void ringArea()
{
    cout << "\n=== Завдання 2: Площа кільця ===\n";
    try {
        cout << "Введіть зовнішній та внутрішній радіуси: ";
        double outer, inner;
        cin >> outer >> inner;
        const Ring ring(outer, inner);
        ring.print();
    } catch (const invalid_argument& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
}

// Завдання 3: Периметр прямокутного трикутника за катетами
class RightTriangle {
private:
    double leg1_{0.0};
    double leg2_{0.0};

    static void validateLegs(double leg1, double leg2)
    {
        if (leg1 <= 0.0)
            throw invalid_argument("RightTriangle: leg1 must be > 0");
        if (leg2 <= 0.0)
            throw invalid_argument("RightTriangle: leg2 must be > 0");
    }

public:
    explicit RightTriangle(const double leg1 = 1.0, const double leg2 = 1.0)
    {
        validateLegs(leg1, leg2);
        leg1_ = leg1;
        leg2_ = leg2;
    }

    void setLegs(const double leg1, const double leg2)
    {
        validateLegs(leg1, leg2);
        leg1_ = leg1;
        leg2_ = leg2;
    }

    [[nodiscard]] double getHypotenuse() const
    {
        return sqrt(leg1_ * leg1_ + leg2_ * leg2_);
    }

    [[nodiscard]] double getPerimeter() const
    {
        return leg1_ + leg2_ + getHypotenuse();
    }

    void print() const
    {
        cout << "Катети: " << leg1_ << ", " << leg2_ << ", гіпотенуза: " << getHypotenuse()
            << ", периметр: " << getPerimeter() << endl;
    }
};

void rightTrianglePerimeter()
{
    cout << "\n=== Завдання 3: Периметр прямокутного трикутника ===\n";
    try {
        cout << "Введіть катети a та b: ";
        double a, b;
        cin >> a >> b;
        const RightTriangle tri(a, b);
        tri.print();
    } catch (const invalid_argument& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
}

// Завдання 4: Аналіз двоцифрового числа
class TwoDigitNumber {
private:
    int number_;
public:
    explicit TwoDigitNumber(int number = 10) : number_(number)
    {
        if (number_ < 10 || number_ > 99) throw invalid_argument("TwoDigitNumber: number must be two-digit (10-99)");
    }

    void setNumber(int number) {
        if (number < 10 || number > 99) throw invalid_argument("TwoDigitNumber: number must be two-digit (10-99)");
        number_ = number;
    }

    [[nodiscard]] int getTens() const
    {
        return number_ / 10;
    }

    [[nodiscard]] int getUnits() const
    {
        return number_ % 10;
    }

    [[nodiscard]] int getSum() const
    {
        return getTens() + getUnits();
    }

    [[nodiscard]] int getProduct() const
    {
        return getTens() * getUnits();
    }

    void print() const
    {
        cout << "Число: " << number_ << ", десятки: " << getTens() << ", одиниці: " << getUnits()
            << ", сума цифр: " << getSum() << ", добуток цифр: " << getProduct() << endl;
    }
};

void twoDigitAnalysis()
{
    cout << "\n=== Завдання 4: Аналіз двоцифрового числа ===\n";
    try
    {
        cout << "Введіть двоцифрове число: ";
        int num;
        cin >> num;
        const TwoDigitNumber numObj(num);
        numObj.print();
    }
    catch (const invalid_argument& e)
    {
        cerr << "Помилка: " << e.what() << endl;
    }
}

int main()
{
    squarePerimeter();
    ringArea();
    rightTrianglePerimeter();
    twoDigitAnalysis();
    return 0;
}

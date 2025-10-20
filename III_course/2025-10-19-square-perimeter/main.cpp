// III_course/2025-10-19-square-perimeter/main.cpp
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>

using namespace std;

//-------------------------------
// Dependency Inversion Principle
//-------------------------------

// Інтерфейс валідації значень
class IValueValidator {
public:
    virtual void checkFinite(double val, const std::string& what) const = 0;
    virtual void checkPositive(double val, const std::string& what) const = 0;
    virtual void checkNonNegative(double val, const std::string& what) const = 0;
    virtual void checkRange(int val, int min, int max, const std::string& what) const = 0;
    virtual ~IValueValidator() = default;
};

// Інтерфейс читача значень (generic)
template<typename T>
class IValueReader {
public:
    [[nodiscard]] virtual T readValue(const std::string& prompt) const = 0;
    virtual ~IValueReader() = default;
};

//-------------------------------
// Реалізації
//-------------------------------

// Конкретна реалізація валідації числових значень
class NumericValidator final : public IValueValidator {
public:
    void checkFinite(const double val, const std::string& what) const override
    {
        if (!std::isfinite(val))
            throw std::overflow_error(what + " не є скінченним (inf або NaN)");
    }

    void checkPositive(const double val, const std::string& what) const override
    {
        if (val <= 0.0)
            throw std::invalid_argument(what + " має бути > 0");
    }

    void checkNonNegative(const double val, const std::string& what) const override
    {
        if (val < 0.0)
            throw std::invalid_argument(what + " має бути ≥ 0");
    }

    void checkRange(const int val, const int min, const int max, const std::string& what) const override
    {
        if (val < min || val > max)
            throw std::invalid_argument(
                what + " має бути в межах [" + std::to_string(min) + ", " + std::to_string(max) + "]");
    }
};

// Реалізація вводу з консолі
template<typename T>
class ConsoleReader final : public IValueReader<T> {
public:
    [[nodiscard]] T readValue(const std::string& prompt) const override
    {
        std::cout << prompt;
        T value{};
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::string bad;
            std::getline(std::cin, bad);
            throw std::runtime_error("Некоректне введення (очікувалося число)");
        }
        return value;
    }
};


//---------------------------------------------
// Завдання 1: Периметр квадрата за площею
//---------------------------------------------
class Square {
private:
    double area_{0.0};;  // Площа квадрата
    const IValueValidator& validator_; // інжектемо інтерфейс замість реалізації

public:
    explicit Square(const double area, const IValueValidator& validator): validator_(validator)
    {
        setArea(area); // використовуємо готовий метод з валідацією
    }

    void setArea(const double area)
    {
        validator_.checkNonNegative(area, "Площа квадрата");
        area_ = area;
    }

    [[nodiscard]] double getPerimeter() const {
        const double p = 4.0 * sqrt(area_);
        validator_.checkFinite(p, "Периметр квадрата");
        return p;
    }

    void print() const {
        cout << "Площа квадрата: " << area_ << ", периметр: " << getPerimeter() << endl;
    }
};

void squarePerimeter(const IValueReader<double>& reader, const IValueValidator& validator) {
    cout << "\n=== Завдання 1: Периметр квадрата за площею ===\n";
    try {
        const double area = reader.readValue("Введіть площу квадрата: ");
        const Square sq(area, validator);
        sq.print();
    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
}

// Завдання 2: Площа кільця за зовнішнім і внутрішнім радіусами
class Ring {
private:
    double outerRadius_{0.0};
    double innerRadius_{0.0};
    const IValueValidator& validator_; // інжектемо інтерфейс замість реалізації

public:
    Ring(const double outer, const double inner, const IValueValidator& validator)
        : validator_(validator)
    {
        setRadii(outer, inner); // не дублюємо логіку, викликаємо сеттер
    }

    void setRadii(const double outer, const double inner)
    {
        validator_.checkPositive(outer, "Зовнішній радіус");
        validator_.checkNonNegative(inner, "Внутрішній радіус");
        if (inner >= outer)
            throw invalid_argument("Внутрішній радіус має бути меншим за зовнішній");

        outerRadius_ = outer;
        innerRadius_ = inner;
    }

    [[nodiscard]] double getArea() const
    {
        const double a = M_PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
        validator_.checkFinite(a, "Площа кільця");
        return a;
    }

    void print() const
    {
        cout << "Зовнішній радіус: " << outerRadius_
             << ", внутрішній радіус: " << innerRadius_
             << ", площа кільця: " << getArea() << endl;
    }
};

void ringArea(const IValueReader<double>& reader, const IValueValidator& validator) {
    cout << "\n=== Завдання 2: Площа кільця ===\n";
    try {
        const double outer = reader.readValue("Введіть зовнішній радіус: ");
        const double inner = reader.readValue("Введіть внутрішній радіус: ");
        const Ring ring(outer, inner, validator);
        ring.print();
    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
}

//---------------------------------------------
// Завдання 3: Периметр прямокутного трикутника
//---------------------------------------------
class RightTriangle {
private:
    double leg1_{0.0};
    double leg2_{0.0};
    const IValueValidator& validator_;

public:
    RightTriangle(const double a, const double b, const IValueValidator& validator)
        : validator_(validator)
    {
        setLegs(a, b);
    }

    void setLegs(const double a, const double b)
    {
        validator_.checkPositive(a, "Катет a");
        validator_.checkPositive(b, "Катет b");
        leg1_ = a;
        leg2_ = b;
    }

    [[nodiscard]] double getHypotenuse() const
    {
        const double h = sqrt(leg1_ * leg1_ + leg2_ * leg2_);
        validator_.checkFinite(h, "Гіпотенуза");
        return h;
    }

    [[nodiscard]] double getPerimeter() const
    {
        const double p = leg1_ + leg2_ + getHypotenuse();
        validator_.checkFinite(p, "Периметр трикутника");
        return p;
    }

    void print() const
    {
        cout << "Катети: " << leg1_ << ", " << leg2_
             << ", гіпотенуза: " << getHypotenuse()
             << ", периметр: " << getPerimeter() << endl;
    }
};

void rightTrianglePerimeter(const IValueReader<double>& reader, const IValueValidator& validator) {
    cout << "\n=== Завдання 3: Периметр прямокутного трикутника ===\n";
    try {
        const double a = reader.readValue("Введіть катет a: ");
        const double b = reader.readValue("Введіть катет b: ");
        const RightTriangle tri(a, b, validator);
        tri.print();
    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
}

//---------------------------------------------
// Завдання 4: Аналіз двоцифрового числа
//---------------------------------------------
class TwoDigitNumber {
private:
    int number_{0};
    const IValueValidator& validator_;

public:
    TwoDigitNumber(const int number, const IValueValidator& validator)
        : validator_(validator)
    {
        setNumber(number);
    }

    void setNumber(const int number)
    {
        validator_.checkRange(number, 10, 99, "TwoDigitNumber");
        number_ = number;
    }

    [[nodiscard]] int getTens() const { return number_ / 10; }
    [[nodiscard]] int getUnits() const { return number_ % 10; }
    [[nodiscard]] int getSum() const { return getTens() + getUnits(); }
    [[nodiscard]] int getProduct() const { return getTens() * getUnits(); }

    void print() const
    {
        cout << "Число: " << number_
             << ", десятки: " << getTens()
             << ", одиниці: " << getUnits()
             << ", сума: " << getSum()
             << ", добуток: " << getProduct() << endl;
    }
};

void twoDigitAnalysis(const IValueReader<int>& reader, const IValueValidator& validator) {
    cout << "\n=== Завдання 4: Аналіз двоцифрового числа ===\n";
    try {
        const int num = reader.readValue("Введіть двоцифрове число: ");
        const TwoDigitNumber numObj(num, validator);
        numObj.print();
    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
}

int main()
{
    const NumericValidator validator;
    const ConsoleReader<double> readerDouble;
    const ConsoleReader<int> readerInt;

    squarePerimeter(readerDouble, validator);
    ringArea(readerDouble, validator);
    rightTrianglePerimeter(readerDouble, validator);
    twoDigitAnalysis(readerInt, validator);

    return 0;
}

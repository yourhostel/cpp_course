// # III_course/2025-10-06-classes-and-objects-7/main.cpp
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <numbers>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Базовий клас: геометричне тіло з координатами однієї вершини.
// Використовуємо protected, щоб похідні класи могли звертатися до координат.
class GeometricBody {
protected:
    double x_;
    double y_;
    double z_;

public:
    explicit GeometricBody(const double x = 0,
                           const double y = 0,
                           const double z = 0)
        : x_(x), y_(y), z_(z) {}

    // Віртуальний деструктор: коректне видалення через вказівник на базовий клас
    virtual ~GeometricBody() = default;

    // Віртуальний друк інформації
    virtual void printInfo() const {
        std::cout << std::fixed << std::setprecision(2)
                  << "Координати вершини: (" << x_ << ", " << y_ << ", " << z_ << ")\n";
    }
};

////////////////////////////
// Піраміда: додає висоту
class Pyramid : public GeometricBody {
protected:
    double height_; // висота піраміди (> 0)

    // Перевірка інваріантів класу
    static void ensurePositive(const double v, const char* name) {
        if (!(v > 0.0)) {
            throw std::invalid_argument(std::string(name) + " має бути > 0");
        }
    }

public:
    // Конструктор зі списком ініціалізації; перевіряємо висоту
    Pyramid(const double x,
            const double y,
            const double z,
            const double height)
        : GeometricBody(x, y, z), height_(height) {
        ensurePositive(height_, "Висота");
    }

    void printInfo() const override {
        GeometricBody::printInfo();
        std::cout << "Висота: " << height_ << "\n";
    }
};

///////////////////////////////////////////
// Трикутна піраміда: додає площу основи
class TriangularPyramid final : public Pyramid { // final - забороняє подальше наслідування
private:
    double baseArea_; // площа основи (> 0)

public:
    TriangularPyramid(const double x,
                      const double y,
                      const double z,
                      const double height,
                      const double baseArea)
        : Pyramid(x, y, z, height), baseArea_(baseArea) {
        if (!(baseArea_ > 0.0)) {
            throw std::invalid_argument("Площа основи повинна бути > 0");
        }
    }

    void printInfo() const override {
        std::cout << "Трикутна піраміда:\n";
        Pyramid::printInfo();
        std::cout << "Площа основи: " << baseArea_ << "\n";
    }

    // [[nodiscard]] - якщо результат проігноровано, компілятор попередить
    [[nodiscard]] double volume() const {
        return (baseArea_ * height_) / 3.0; // V = Sосн * h / 3
    }
};

//////////////////////////////////////////////////////////////////////////////
// Чотирикутна (прямокутна) піраміда: основа — прямокутник зі сторонами a і b
class RectangularPyramid final : public Pyramid { // також final!
private:
    double sideA_; // довжина сторони a (> 0)
    double sideB_; // довжина сторони b (> 0)

public:
    RectangularPyramid(const double x,
                       const double y,
                       const double z,
                       const double height,
                       const double sideA,
                       const double sideB)
        : Pyramid(x, y, z, height), sideA_(sideA), sideB_(sideB) {
        if (!(sideA_ > 0.0)) throw std::invalid_argument("Сторона a повинна бути > 0");
        if (!(sideB_ > 0.0)) throw std::invalid_argument("Сторона b повинна бути > 0");
    }

    void printInfo() const override {
        std::cout << "Чотирикутна (прямокутна) піраміда:\n";
        Pyramid::printInfo();
        std::cout << "Сторони основи: " << sideA_ << " × " << sideB_ << "\n";
    }

    [[nodiscard]] double baseArea() const { return sideA_ * sideB_; } // S = a*b

    [[nodiscard]] double volume() const { return (baseArea() * height_) / 3.0; } // V = a*b*h/3
};

//////////////////////
// Куля: додає радіус
class Sphere final : public GeometricBody { // також final!
private:
    double radius_; // радіус (> 0)

public:
    Sphere(const double x,
           const double y,
           const double z,
           const double radius)
        : GeometricBody(x, y, z), radius_(radius) {
        if (!(radius_ > 0.0)) {
            throw std::invalid_argument("Радіус повинен бути > 0");
        }
    }

    void printInfo() const override {
        std::cout << "Куля:\n";
        GeometricBody::printInfo();
        std::cout << "Радіус: " << radius_ << "\n";
    }

    [[nodiscard]] double volume() const {
        // std::numbers::pi_v<double> джерело π (C++20)
        return (4.0 / 3.0) * std::numbers::pi_v<double> * radius_ * radius_ * radius_; // V = 4/3 π r^3
    }
};

///////////////////////////////////////
// Допоміжна функція для зчитування
double readDouble(const std::string& prompt,
                        std::istream& in = std::cin) {
    std::cout << prompt;
    double v{};
    if (!(in >> v)) {
        // Скидаємо стан потоку і чистимо буфер, щоб не зациклитися
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Очікувалось число: некоректне введення");
    }
    return v;
}

int main() {
    try {
        // Ввід даних користувача з базовою валідацією та винятками
        std::cout << "=== Створення фігур ===\n";

        // Трикутна піраміда
        // Другий параметр (std::cin) підставляється автоматично,
        // бо для нього задано значення за замовчуванням у сигнатурі функції.
        const double tx = readDouble("TP: x = ");
        const double ty = readDouble("TP: y = ");
        const double tz = readDouble("TP: z = ");
        const double th = readDouble("TP: висота = ");
        const double tS = readDouble("TP: площа основи = ");
        const TriangularPyramid tp(tx, ty, tz, th, tS);

        std::cout << "\n";

        // Чотирикутна (прямокутна) піраміда
        const double rx = readDouble("RP: x = ");
        const double ry = readDouble("RP: y = ");
        const double rz = readDouble("RP: z = ");
        const double rh = readDouble("RP: висота = ");
        const double ra = readDouble("RP: сторона a = ");
        const double rb = readDouble("RP: сторона b = ");
        const RectangularPyramid rp(rx, ry, rz, rh, ra, rb);

        std::cout << "\n";

        // Куля
        const double sx = readDouble("S:  x = ");
        const double sy = readDouble("S:  y = ");
        const double sz = readDouble("S:  z = ");
        const double sr = readDouble("S:  радіус = ");
        const Sphere s(sx, sy, sz, sr);

        // Вивід результатів
        std::cout << "\n--- Результати ---\n";
        tp.printInfo();
        std::cout << "Об'єм: " << tp.volume() << "\n\n";

        rp.printInfo();
        std::cout << "Об'єм: " << rp.volume() << "\n\n";

        s.printInfo();
        std::cout << "Об'єм: " << s.volume() << "\n";
    }
    catch (const std::exception& e) {
        // Обробка винятків:
        std::cerr << "Помилка: " << e.what() << "\n";
        return 1; // Невдале завершення
    }
}



//
// Created by tysser on 30.11.25.
//

// cpp_course/III_course/2025-11-30-inheritance-templates/

#include <iostream>
#include <string>
#include <vector>

// ---------------------------------------------------------
// Ієрархія "Будинок" – "Навчальний корпус"
// ---------------------------------------------------------
class Building {
protected:
    std::string name_;
    std::string address_;
    int floors_{};

public:
    Building(std::string name, std::string address, const int floors)
        : name_(std::move(name)), address_(std::move(address)), floors_(floors) {}

    // важливо для коректного видалення через вказівник на базовий клас
    virtual ~Building() = default;

    virtual void printInfo() const {
        std::cout << "[Будинок]\n"
                  << "  Назва: " << name_ << "\n"
                  << "  Адреса: " << address_ << "\n"
                  << "  Кількість поверхів: " << floors_ << "\n";
    }
};

class EducationalBuilding final : public Building {
    std::string faculty_;
    int classrooms_{};

public:
    EducationalBuilding(std::string name,
                        std::string address,
                        const int floors,
                        std::string faculty,
                        const int classrooms)
        : Building(std::move(name), std::move(address), floors),
          faculty_(std::move(faculty)),
          classrooms_(classrooms) {}

    void printInfo() const override
    {
        std::cout << "[Навчальний корпус]\n"
            << "  Назва: " << name_ << "\n"
            << "  Адреса: " << address_ << "\n"
            << "  Кількість поверхів: " << floors_ << "\n"
            << "  Факультет: " << faculty_ << "\n"
            << "  Кількість аудиторій: " << classrooms_ << "\n";
    }
};

// ---------------------------------------------------------
// 2. Ієрархія "Цифровий пристрій" – "Мобільний телефон"
// ---------------------------------------------------------
class DigitalDevice {
protected:
    std::string brand_;
    std::string model_;
    bool portable_{};
    // умовна потужність
    double powerWatts_{};

public:
    DigitalDevice(std::string brand,
                  std::string model,
                  const bool portable,
                  const double powerWatts)
        : brand_(std::move(brand)),
          model_(std::move(model)),
          portable_(portable),
          powerWatts_(powerWatts) {}

    virtual ~DigitalDevice() = default;

    virtual void printInfo() const
    {
        std::cout << "[Цифровий пристрій]\n"
            << "  Виробник: " << brand_ << "\n"
            << "  Модель: " << model_ << "\n"
            << "  Портативний: " << (portable_ ? "так" : "ні") << "\n"
            << "  Споживана потужність: " << powerWatts_ << " Вт\n";
    }
};

class MobilePhone final : public DigitalDevice {
    std::string os_;
    double screenInches_{};
    int simSlots_{};

public:
    MobilePhone(std::string brand,
                std::string model,
                const double powerWatts,
                std::string os,
                const double screenInches,
                const int simSlots)
        : DigitalDevice(std::move(brand), std::move(model), true, powerWatts),
          os_(std::move(os)),
          screenInches_(screenInches),
          simSlots_(simSlots) {}

    void printInfo() const override
    {
        std::cout << "[Мобільний телефон]\n"
            << "  Виробник: " << brand_ << "\n"
            << "  Модель: " << model_ << "\n"
            << "  ОС: " << os_ << "\n"
            << "  Діагональ екрана: " << screenInches_ << " \"\n"
            << "  Кількість SIM: " << simSlots_ << "\n"
            << "  Портативний: так\n"
            << "  Споживана потужність: " << powerWatts_ << " Вт\n";
    }
};

// ---------------------------------------------------------
// 3. Шаблонна функція пошуку елементів у діапазоні [low; high] (включно)
// ---------------------------------------------------------
template<typename T>
std::vector<T> findInRange(const std::vector<T>& data,
                           const T& low,
                           const T& high)
{
    std::vector<T> result;
    for (const auto& value : data)
    {
        if (value >= low && value <= high)
        {
            result.push_back(value);
        }
    }
    return result;
}

// Допоміжна функція друку вектора
template<typename T>
void printVector(const std::vector<T>& v, const std::string& title)
{
    std::cout << title << " [";
    bool first = true;
    for (const auto& el : v)
    {
        if (!first)
        {
            std::cout << ", ";
        }
        std::cout << el;
        first = false;
    }
    std::cout << "]\n";
}

// ---------------------------------------------------------
// 4. Шаблон класу для зберігання пари чисел різних типів
// ---------------------------------------------------------
template<typename T1, typename T2>
class NumberPair {
    T1 first_{};
    T2 second_{};

public:
    NumberPair() = default;

    NumberPair(const T1& first, const T2& second)
        : first_(first), second_(second) {}

    [[nodiscard]] const T1& first() const { return first_; }
    [[nodiscard]] const T2& second() const { return second_; }

    void setFirst(const T1& value) { first_ = value; }
    void setSecond(const T2& value) { second_ = value; }

    void print(const std::string& label = "Pair") const {
        std::cout << label << " = (" << first_ << ", " << second_ << ")\n";
    }
};

// ---------------------------------------------------------
// 5. Функції для тестування
// ---------------------------------------------------------
void testBuildings()
{
    std::cout << "=== 1. Ієрархія \"Будинок\" – \"Навчальний корпус\" ===\n\n";

    // Масив вказівників на базовий клас Building
    Building* buildings[3];

    buildings[0] = new Building("Житловий будинок №1", "вул. Шевченка, 10", 9);
    buildings[1] = new EducationalBuilding("Корпус А", "пр. Науки, 5", 4,
                                            "Факультет інформатики", 32);
    buildings[2] = new EducationalBuilding("Корпус Б", "пр. Науки, 7", 5,
                                            "Фізико-математичний факультет", 40);

    for (const Building* b : buildings)
    {
        b->printInfo();
        std::cout << "----------------------------------------\n";
    }

    // Звільняємо пам'ять
    for (const Building* b : buildings)
    {
        delete b;
    }
}

void testDigitalDevices()
{
    std::cout << "\n=== 2. Ієрархія \"Цифровий пристрій\" – \"Мобільний телефон\" ===\n\n";

    DigitalDevice* devices[3];

    devices[0] = new DigitalDevice("LG", "Smart TV 55\"", false, 120.0);
    devices[1] = new MobilePhone("Samsung", "Galaxy S24", 15.0, "Android", 6.5, 2);
    devices[2] = new MobilePhone("Apple", "iPhone 16", 18.0, "iOS", 6.3, 1);

    for (const DigitalDevice* d : devices)
    {
        d->printInfo();
        std::cout << "----------------------------------------\n";
    }

    // Звільняємо пам'ять
    for (const DigitalDevice* d : devices)
    {
        delete d;
    }
}

void testFindInRange()
{
    std::cout << "\n=== 3. Шаблонна функція findInRange ===\n\n";

    // int
    const std::vector<int> vi{ -10, -3, 0, 5, 12, 25 };
    const auto viRange = findInRange(vi, -3, 10);
    printVector(vi, "int:      ");
    printVector(viRange, "in range [-3;10]: ");

    std::cout << '\n';

    // double
    const std::vector<double> vd{ -1.5, 0.0, 0.1, 1.99, 2.0, 3.14, 5.01 };
    const auto vdRange = findInRange(vd, 0.0, 3.14);
    printVector(vd, "double:   ");
    printVector(vdRange, "in range [0;3.14]: ");

    std::cout << '\n';

    // std::string (лексикографічний діапазон)
    const std::vector<std::string> vs{ "apple", "banana", "kiwi", "orange", "pear" };
    const auto vsRange = findInRange(vs, std::string("b"), std::string("p"));
    printVector(vs, "string:   ");
    printVector(vsRange, R"(in range ["b";"p"]: )");
}

void testNumberPair()
{
    std::cout << "\n=== 4. Шаблонний клас NumberPair ===\n\n";

    NumberPair<int, double> p1(10, 3.14);
    const NumberPair<double, double> p2(2.5, 4.5);
    const NumberPair<long, long long> p3(100L, 10000000000LL);

    p1.print("p1");
    p2.print("p2");
    p3.print("p3");

    // Можна змінити значення
    p1.setFirst(42);
    p1.setSecond(2.71828);
    p1.print("p1 (updated)");

    std::cout << "\nГотово.\n";
}

int main()
{
    testBuildings();
    testDigitalDevices();
    testFindInRange();
    testNumberPair();

    return 0;
}

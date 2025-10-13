// III_course/2025-10-13-topic-8/main.cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
using namespace std;

////////////////////////////
// 1. Клас з двома змінними
class PairValues {
private:
    int x_;
    int y_;

public:
    explicit PairValues(const int x = 0, const int y = 0) : x_(x), y_(y) {}

    void print() const {
        cout << "x = " << x_ << ", y = " << y_ << endl;
    }

    void setValues(const int x, const int y) {
        x_ = x;
        y_ = y;
    }

    [[nodiscard]] int sum() const {
        return x_ + y_;
    }

    [[nodiscard]] int maxValue() const
    {
        return max(x_, y_);
    }
};

void pairValues()
{
    cout << "\n=== Завдання 1: Клас з двома змінними ===\n";
    PairValues p1(3, 7);
    p1.print();

    cout << "Сума: " << p1.sum() << endl;
    cout << "Максимум: " << p1.maxValue() << endl;

    p1.setValues(10, 5);
    p1.print();
    cout << "Сума: " << p1.sum() << endl;
    cout << "Максимум: " << p1.maxValue() << endl;
}

//////////////////////////////////
// 2. Клас десяткового лічильника
// Інваріанти: min_ <= max_, value_ ∈ [min_; max_]
class DecimalCounter {
private:
    int min_;
    int max_;
    int value_;

public:
    explicit DecimalCounter(const int min = 0, const int max = 9, const int value = 0)
        : min_(min), max_(max), value_(value)
    {
        if (min_ > max_) {
            throw invalid_argument("DecimalCounter: min > max");
        }
        if (value_ < min_ || value_ > max_) {
            throw invalid_argument("DecimalCounter: initial value out of range");
        }
    }

    void increment()
    {
        if (value_ < max_) ++value_; // на краю — тихо ігноруємо
    }

    void decrement()
    {
        if (value_ > min_) --value_; // на краю — тихо ігноруємо
    }

    [[nodiscard]] int getValue() const
    {
        return value_;
    }

    void print() const
    {
        cout << "Поточне значення лічильника: " << value_ << endl;
    }
};

void decimalCounter()
{
    cout << "\n=== Завдання 2: Десятковий лічильник ===\n";
    try
    {
        DecimalCounter c(0, 5, 2); // валідно
        c.print();
        c.increment();
        c.print();
        c.increment();
        c.print();
        c.increment();
        c.print(); // дійде до межі, далі ігнор
        c.decrement();
        c.print();
    }
    catch (const exception& e)
    {
        cerr << "Помилка ініціалізації лічильника: " << e.what() << '\n';
    }
}

///////////////////
// 3. Клас Employee
// Інваріанти: id_ > 0, salary_ >= 0
class Employee {
private:
    int id_;
    double salary_;

public:
    explicit Employee(const int id = 0, const double salary = 0.0)
        : id_(id), salary_(salary)
    {
        if (id_ <= 0)  throw invalid_argument("Employee: id must be > 0");
        if (salary_ < 0.0) throw invalid_argument("Employee: salary must be >= 0");
    }

    void print() const
    {
        cout << "Працівник #" << id_ << ", зарплата: " << salary_ << endl;
    }
};

void employee()
{
    cout << "\n=== Завдання 3: Клас Employee ===\n";
    int n;
    cout << "Введіть кількість працівників: ";
    if (!(cin >> n) || n <= 0)
    {
        cerr << "Некоректне N. Завершення.\n";
        return;
    }

    vector<Employee> staff;
    staff.reserve(n);

    for (int i = 0; i < n; /* ++i всередині */)
    {
        int id;
        double salary;
        cout << "Введіть id та зарплату працівника " << i + 1 << ": ";
        if (!(cin >> id >> salary))
        {
            cerr << "Некоректний ввід. Спробуйте ще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        try
        {
            staff.emplace_back(id, salary); // може кинути invalid_argument
            ++i; // додали успішно — рухаємось далі
        }
        catch (const invalid_argument& e)
        {
            cerr << "Помилка: " << e.what() << ". Спробуйте ще раз.\n";
            // i не інкрементуємо — повторюємо ітерацію
        }
    }

    cout << "\nСписок працівників:\n";
    for (const auto& e : staff) e.print();
}

int main() {
    pairValues();
    decimalCounter();
    employee();
}

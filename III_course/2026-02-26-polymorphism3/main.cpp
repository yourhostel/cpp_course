#include <iostream>
#include <string>

class Worker
{
protected:
    std::string name;

public:
    explicit Worker(std::string name) : name(std::move(name)) {}
    virtual ~Worker() = default;

    [[nodiscard]] virtual double salary() const = 0;

    virtual void print() const
    {
        std::cout << name;
    }
};

class HourlyWorker : public Worker
{
    double hours;
    double rate;

public:
    HourlyWorker(std::string name,
                 const double hours,
                 const double rate)
        : Worker(std::move(name)),
          hours(hours),
          rate(rate) {}

    [[nodiscard]] double salary() const override
    {
        return hours * rate;
    }

    void print() const override
    {
        Worker::print();
        std::cout << " (погодинно: "
                  << hours << " год, "
                  << rate << " грн/год)";
    }
};

class SalariedWorker : public Worker
{
    double monthly;

public:
    SalariedWorker(std::string name, double monthly)
        : Worker(std::move(name)),
          monthly(monthly) {}

    [[nodiscard]] double salary() const override
    {
        return monthly;
    }


    void print() const override
    {
        Worker::print();
        std::cout << " (оклад: "
                  << monthly << " грн)";
    }
};

int main()
{
    HourlyWorker w1("Іван", 120, 150);
    SalariedWorker w2("Олена", 25000);

    Worker* staff[2];
    staff[0] = &w1;
    staff[1] = &w2;

    for (Worker* p : staff)
    {
        p->print();
        std::cout << ", зарплата = "
                  << p->salary()
                  << std::endl;
    }
}
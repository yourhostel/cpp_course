#include <iostream>
#include <string>
#include <random>
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
    int hours;
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
    //HourlyWorker w1("Іван", 120, 150);
    // SalariedWorker w2("Олена", 25000);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> hoursDist(0, 21 * 24);
    // std::uniform_real_distribution<> rateDist(0, 300);

    constexpr double rate1 = 200.00;
    constexpr double rate2 = 300.00;
    constexpr double rate3 = 400.00;

    HourlyWorker w1("Іван", hoursDist(gen), rate1);
    HourlyWorker w2("Петро", hoursDist(gen), rate2);
    HourlyWorker w3("Микола", hoursDist(gen), rate3);
    HourlyWorker w4("Андрій", hoursDist(gen), rate1);


    // HourlyWorker w1("Іван", hoursDist(gen), rateDist(gen));
    // HourlyWorker w2("Петро", hoursDist(gen), rateDist(gen));
    // HourlyWorker w3("Микола", hoursDist(gen), rateDist(gen));
    // HourlyWorker w4("Андрій", hoursDist(gen), rateDist(gen));

    SalariedWorker w5("Олена", 25000);

    Worker* staff[5];
    staff[0] = &w1;
    staff[1] = &w2;
    staff[2] = &w3;
    staff[3] = &w4;
    staff[4] = &w5;

    for (Worker* p : staff)
    {
        p->print();
        std::cout << ", зарплата = "
                  << p->salary()
                  << std::endl;
    }
}
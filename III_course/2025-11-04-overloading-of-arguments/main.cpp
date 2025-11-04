//
// Created by tysser on 04.11.25.
//

#include <iostream>
#include <string>

//====================================================================
// Варіант 1 — Перевантаження за кількістю аргументів (Transaction) //
//====================================================================

enum class PayMethod { CASH, CARD, BANK };

// Базовий клас Transaction
class Transaction {
protected:
  double amount;
  PayMethod method;
public:
  virtual ~Transaction() = default;
  Transaction(const double a, const PayMethod m) : amount(a), method(m) {}

  // Віртуальна функція - динамічний поліморфізм
  virtual void process() const = 0;

  // Перевантаження за кількістю аргументів
  void print_summary() const
  {
    std::cout << "Сума: " << amount << "\n";
  }

  void print_summary(const bool includeMethod) const
  {
    std::cout << "Сума: " << amount;
    if (includeMethod)
    {
      std::cout << ", метод: ";
      switch (method)
      {
      case PayMethod::CASH: std::cout << "Готівка";
        break;
      case PayMethod::CARD: std::cout << "Карта";
        break;
      case PayMethod::BANK: std::cout << "Банк";
        break;
      }
    }
    std::cout << "\n";
  }
};

class Payment final : public Transaction {
public:
  Payment(const double a, const PayMethod m) : Transaction(a, m) {}

  void process() const override
  {
    std::cout << "Обробка оплати (" << amount << ")\n";
  }
};

class Expense final : public Transaction {
public:
  Expense(const double a, const PayMethod m) : Transaction(a, m) {}

  void process() const override
  {
    std::cout << "Витрата (" << amount << ")\n";
  }
};

//====================================================================
// Варіант 2 — Перевантаження за типом аргументів (Blacklist)       //
//====================================================================

class Guest {
public:
  std::string name;
  explicit Guest(std::string n) : name(std::move(n)) {}
};

class Staff {
public:
  std::string name;
  explicit Staff(std::string n) : name(std::move(n)) {}
};

class BlacklistManager {
public:
  // Перевантаження за типом аргументів
  static void add(const Guest& guest)
  {
    std::cout << "Додано гостя '" << guest.name << "' до чорного списку гостей.\n";
  }

  static void add(const Staff& staff)
  {
    std::cout << "Додано співробітника '" << staff.name << "' до чорного списку персоналу.\n";
  }
};


int main()
{
  const Payment pay(1200, PayMethod::CASH);
  const Expense exp(300, PayMethod::CARD);

  const Guest g("Іван Петренко");
  const Staff s("Оксана Бондар");

  // --- Transaction ---
  pay.process();
  pay.print_summary();
  pay.print_summary(true);

  exp.process();
  exp.print_summary(true);

  std::cout << "------------------\n";

  // --- Blacklist ---
  BlacklistManager::add(g);
  BlacklistManager::add(s);

  return 0;
}

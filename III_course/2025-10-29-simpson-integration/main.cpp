// III_course/2025-10-29-simpson-integration/main.cpp
#include <iostream>
#include "menus.h"
#include "math_functions.h"
#include "validate.h"
#include "messages.h"

void runMainMenu();
void runTabulationMenu();
void integrateSimpson(FuncPtr f);
void runSimpsonIntegration();

int main()
{
  runMainMenu();

  return 0;
}

void runMainMenu()
{
  while (true)
  {
    std::cout << MAIN_MENU;

    try
    {
      const int c = validateMenuChoice(3);
      if (c == 1) runTabulationMenu();
      if (c == 2) runSimpsonIntegration();
      if (c == 3) return;
    }
    catch (const std::exception& ex)
    {
      std::cout << ex.what() << "\n";
    }
  }
}

void tabulate(const FuncPtr f)
{
  while (true)
  {
    try
    {
      const double a = readDouble("Введіть a: ");
      const double b = readDouble("Введіть b: ");
      const double h = readDouble("Введіть крок h: ");

      if (h <= 0) throw std::invalid_argument("Крок h має бути > 0");
      if (a > b) throw std::invalid_argument("a має бути <= b");

      std::cout << "\n x\t|\tf(x)\n-----------------------\n";

      for (double x = a; x <= b; x += h)
      {
        std::cout << x << "\t|\t" << f(x) << "\n";
      }

      std::cout << "-----------------------\n\n";
      return; // нормальне завершення табуляції
    }
    catch (const std::exception& ex)
    {
      std::cout << "\n[Помилка] " << ex.what() << "\n";
      std::cout << INPUT_ERROR_MENU;

      try
      {
        const int c = validateMenuChoice(2);
        if (c == 2) return; // назад у меню
      }
      catch (...)
      {
        std::cout << "Некоректний вибір. Повернення у меню.\n";
        return;
      }
    }
  }
}

void runTabulationMenu()
{
  while (true)
  {
    std::cout << TABULATION_MENU;

    try
    {
      const int c = validateMenuChoice(4);

      if (c == 1) tabulate(funcSin);
      if (c == 2) tabulate(funcSquare);
      if (c == 3) tabulate(funcExp);
      if (c == 4) return;
    }
    catch (const std::exception& ex)
    {
      std::cout << ex.what() << "\n";
    }
  }
}

void integrateSimpson(const FuncPtr f)
{
  while (true)
  {
    try
    {
      const double a = readDouble("Введіть a: ");
      const double b = readDouble("Введіть b: ");
      const int n = static_cast<int>(readDouble("Введіть n (парне ціле число): "));

      if (a > b) throw std::invalid_argument("a має бути <= b");
      if (n <= 0 || n % 2 != 0) throw std::invalid_argument("n має бути парним цілим > 0");

      // Попередження про неточність якщо n замале
      if (n < 10)
      {
        std::cout << SIMPSON_N_WARNING;

        try
        {
          const int choice = validateMenuChoice(2);
          if (choice == 2) continue; // повернення до нового введення
        }
        catch (...)
        {
          std::cout << "Некоректний вибір. Повернення до введення n.\n";
          continue;
        }
      }

      const double result = simpson(a, b, n, f);

      std::cout << "\nРезультат інтегрування методом Сімпсона: " << result << "\n\n";
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << "\n[Помилка] " << ex.what() << "\n";
      std::cout << INPUT_ERROR_MENU;

      try
      {
        const int c = validateMenuChoice(2);
        if (c == 2) return;
      }
      catch (...)
      {
        std::cout << "Некоректний вибір. Повернення у меню.\n";
        return;
      }
    }
  }
}

void runSimpsonIntegration()
{
  while (true)
  {
    std::cout << SIMPSON_MENU;

    try
    {
      const int c = validateMenuChoice(4);

      if (c == 1) integrateSimpson(funcSin);
      if (c == 2) integrateSimpson(funcSquare);
      if (c == 3) integrateSimpson(funcExp);
      if (c == 4) return;
    }
    catch(const std::exception& ex)
    {
      std::cout << ex.what() << "\n";
    }
  }
}
